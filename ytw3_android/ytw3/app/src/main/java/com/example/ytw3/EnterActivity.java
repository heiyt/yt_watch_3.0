package com.example.ytw3;

import static java.lang.Math.abs;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.graphics.Typeface;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.provider.Settings;
import android.text.Html;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;
import androidx.recyclerview.widget.RecyclerView;
import androidx.swiperefreshlayout.widget.SwipeRefreshLayout;

import com.amap.api.location.AMapLocationClient;
import com.amap.api.location.AMapLocationClientOption;
import com.amap.api.location.AMapLocationListener;
import com.example.ytw3.DataBase.remindersDataBase;
import com.qweather.sdk.view.HeConfig;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

import pub.devrel.easypermissions.EasyPermissions;

public class EnterActivity extends AppCompatActivity implements EasyPermissions.PermissionCallbacks {
    //天气显示相关
    TextView textView_city = null;
    TextView textView_temperature = null;
    TextView textView_icon = null;
    String tubiaoDay = "{" +
            "'100':'&#xF101;','101':'&#xF102;','102':'&#xF103;'," +
            "'103':'&#xF104;','104':'&#xF105;','150':'&#xF106;'," +
            "'151':'&#xF107;','152':'&#xF108;','153':'&#xF109;'," +
            "'300':'&#xF10A;','301':'&#xF10B;','302':'&#xF10C;'," +
            "'304':'&#xF10E;','305':'&#xF10F;','306':'&#xF110;'," +
            "'307':'&#xF111;','308':'&#xF112;','309':'&#xF113;'," +
            "'310':'&#xF114;','311':'&#xF115;','312':'&#xF116;'," +
            "'313':'&#xF117;','314':'&#xF118;','315':'&#xF119;'," +
            "'316':'&#xF11A;','317':'&#xF11B;','318':'&#xF11C;'," +
            "'399':'&#xF11F;','400':'&#xF120;','401':'&#xF121;'," +
            "'402':'&#xF122;','403':'&#xF123;','404':'&#xF124;'," +
            "'405':'&#xF125;','406':'&#xF126;','407':'&#xF127;'," +
            "'408':'&#xF128;','409':'&#xF129;','410':'&#xF12A;'," +
            "'499':'&#xF12D;','500':'&#xF12E;','501':'&#xF12F;'," +
            "'502':'&#xF130;','503':'&#xF131;','504':'&#xF132;'," +
            "'507':'&#xF133;','508':'&#xF134;','509':'&#xF135;'," +
            "'510':'&#xF136;','511':'&#xF137;','512':'&#xF138;'," +
            "'513':'&#xF139;','514':'&#xF13A;','515':'&#xF13B;'," +
            "'303':'&#xF10D;','350':'&#xF11D;','351':'&#xF11E;'," +
            "'456':'&#xF12B;','457':'&#xF12C;','900':'&#xF144;','901':'&#xF145;'}";
    //天气对象
    Weather_Control weatherControl = null;
    //定位相关对象
    double latitude = 0;
    double longitude = 0;
    double latitude_last = 0;
    double longitude_last = 0;
    public AMapLocationClient mLocationClient = null;
    public AMapLocationListener mLocationListener = null;
    public AMapLocationClientOption mLocationOption = null;
    //设备搜索相关
    List<DeviceInfo> deviceListData = new ArrayList<>();
    List<DeviceInfo> deviceListDataShow = new ArrayList<>();
    DeviceAdapter listViewAdapter = null;
    AlertDialog.Builder connectDialog = null;
    AlertDialog dialog = null;
    String location = "";
    //代办事项相关显示
    RecyclerView remindersView = null;
    android.widget.Adapter reminderAdapter = null;
    List<remindersDataBase.remindersRecord> remindersRecordShow = new ArrayList<>();
    remindersDataBase remindersDataBase = null;

    @SuppressLint("SourceLockedOrientationActivity")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });
        //和风天气初始化
        HeConfig.init("HE2404211418291010", "3898021a61a54bf4bad49df553fb088c");
        HeConfig.switchToDevService();
        //定位初始化
        AMapLocationClient.updatePrivacyShow(this, true, true);
        AMapLocationClient.updatePrivacyAgree(this, true);
        try {
            Location_Init();
        } catch (Exception e) {
            showToast(e.getMessage());
        }
        //ui界面初始化
        uiInit();
    }
    @Override
    protected void onStart() {
        super.onStart();
        deviceListData.clear();
        deviceListDataShow.clear();
        listViewAdapter.notifyDataSetChanged();
        openBluetoothAdapter();
    }
    @Override
    protected void onStop() {
        super.onStop();
        mLocationClient.onDestroy();
        ECBLE.stopBluetoothDevicesDiscovery(this);
    }
    private boolean is_refresh_location = false;

    void uiInit() {
        //初始化设备搜索列表
        SwipeRefreshLayout swipeRefreshLayout = findViewById(R.id.swipe_layout);
        swipeRefreshLayout.setColorSchemeColors(0x01a4ef);
        swipeRefreshLayout.setOnRefreshListener(() -> {
            deviceListData.clear();
            deviceListDataShow.clear();
            listViewAdapter.notifyDataSetChanged();
            new Handler().postDelayed(() -> {
                swipeRefreshLayout.setRefreshing(false);
                openBluetoothAdapter();
            }, 300);
        });
        ListView listView = findViewById(R.id.list_view);
        listViewAdapter = new DeviceAdapter(this, R.layout.list_item, deviceListDataShow);
        listView.setAdapter(listViewAdapter);
        listView.setOnItemClickListener((parent, view, position, id) -> {
            showConnectDialog();
            DeviceInfo deviceInfo = (DeviceInfo) listView.getItemAtPosition(position);
            ECBLE.onBLEConnectionStateChange((boolean ok, int errCode, String errMsg) -> runOnUiThread(() -> {
                //点击搜索到的手表后
                hideConnectDialog();
                if (ok) {
                    ECBLE.stopBluetoothDevicesDiscovery(this);
                    startActivities(new Intent[]{new Intent().setClass(this, BLE_ControlActivity.class)});
                    overridePendingTransition(R.anim.jump_enter_anim, R.anim.jump_exit_anim);
                } else {
                    showToast("蓝牙连接失败,errCode=" + errCode + ",errMsg=" + errMsg);
                    showAlert("蓝牙连接失败,errCode=" + errCode + ",errMsg=" + errMsg, () -> {
                    });
                }
            }));
            ECBLE.createBLEConnection(this, deviceInfo.id);
        });
        listRefresh();
        //初始化天气UI
        textView_city = findViewById(R.id.cityName);
        textView_temperature = findViewById(R.id.temperature);
        textView_icon = findViewById(R.id.weather_icon);
        Typeface font = Typeface.createFromAsset(getAssets(), "qweather-icons.ttf");//加载图标字体
        textView_icon.setTypeface(font);//设置textView使用图标字体。
        weatherControl = new Weather_Control(EnterActivity.this);
        WeatherUIRefresh();
        //待办列表UI
        remindersView = findViewById(R.id.list_reminder);
        reminderAdapter = new Adapter(this, R.layout.list_reminder_item, remindersRecordShow);
        remindersView.setAdapter((RecyclerView.Adapter) reminderAdapter);
        remindersDataBase = new remindersDataBase(this);
        remindersRecordShow = remindersDataBase.getAllreminders();

    }
    //设备搜索UI刷新
    void listRefresh() {
        new Handler(Looper.getMainLooper()).postDelayed(() -> {
            deviceListDataShow.clear();
            for (DeviceInfo tempDevice : deviceListData) {
                deviceListDataShow.add(new DeviceInfo(tempDevice.id, tempDevice.name, tempDevice.mac, tempDevice.rssi));
            }
            listViewAdapter.notifyDataSetChanged();
            listRefresh();
        }, 300);
    }
    //天气UI刷新
    void WeatherUIRefresh() {
        new Handler().postDelayed(() -> {
            if (is_refresh_location) {
                location = String.format("%s,%s", String.format(Locale.getDefault(), "%.2f", longitude_last), String.format(Locale.getDefault(), "%.2f", latitude_last));
                if (!(location.equals(","))) {
                    weatherControl.WeatherRefresh(location);
                    weatherControl.CityFind(location);
                    if (weatherControl.getWeatherText() != null && weatherControl.getCityStrict() != null) {
                        is_refresh_location = false;
                        textView_city.setText(String.format("%s", weatherControl.getCityProvince() + weatherControl.getCityTown() + weatherControl.getCityStrict()));
                        textView_temperature.setText(String.format("%s℃", weatherControl.getTemperature()));
                        String b = "0";
                        try {
                            JSONObject jsonObjectALL = new JSONObject(tubiaoDay);
                            b = jsonObjectALL.getString(weatherControl.getIcon());
                        } catch (JSONException e) {
                            showToast(e.getMessage());
                        }
                        textView_icon.setText(String.format("%s", Html.fromHtml(b)));
                    }
                }
            }
            WeatherUIRefresh();
        }, 500);
    }
    //定位初始化
    void Location_Init() throws Exception {
        mLocationClient = new AMapLocationClient(getApplicationContext());
        mLocationOption = new AMapLocationClientOption();
        mLocationOption.setLocationMode(AMapLocationClientOption.AMapLocationMode.Hight_Accuracy);
        mLocationOption.setOnceLocation(true);
        mLocationOption.setInterval(3000);
        mLocationOption.setHttpTimeOut(8000);
        mLocationOption.setLocationCacheEnable(false);
        mLocationClient.setLocationOption(mLocationOption);
        mLocationListener = amapLocation -> {
            if (amapLocation != null) {
                if (amapLocation.getErrorCode() == 0) {
                    latitude = amapLocation.getLatitude();
                    longitude = amapLocation.getLongitude();
                    if (abs(latitude_last - latitude) > 0.1) {
                        latitude_last = latitude;
                        is_refresh_location = true;
                    }
                    if (abs(longitude_last - longitude) > 0.1) {
                        longitude_last = longitude;
                        is_refresh_location = true;
                    }
                } else {
                    showToast("location Error, ErrCode:"
                            + amapLocation.getErrorCode() + ", errInfo:"
                            + amapLocation.getErrorInfo());
                }
            }
        };
        mLocationClient.setLocationListener(mLocationListener);
        mLocationClient.startLocation();
    }
    //蓝牙相关函数
    void openBluetoothAdapter() {
        ECBLE.onBluetoothAdapterStateChange((boolean ok, int errCode, String errMsg) -> runOnUiThread(() -> {
            if (!ok) {
                showAlert("openBluetoothAdapter error,errCode=" + errCode + ",errMsg=" + errMsg, () -> runOnUiThread(() -> {
                    if (errCode == 10001) {
                        //蓝牙开关没有打开
                        startActivity(new Intent(Settings.ACTION_BLUETOOTH_SETTINGS));
                    }
                    if (errCode == 10002) {
                        //定位开关没有打开
                        startActivity(new Intent(Settings.ACTION_LOCATION_SOURCE_SETTINGS));
                    }
                    //获取定位权限失败
                    if (errCode == 10003) {
                        new AlertDialog.Builder(this)
                                .setTitle("提示")
                                .setMessage("请打开应用的定位权限")
                                .show();
                    }
                    //获取蓝牙连接附近设备的权限失败
                    if (errCode == 10004) {
                        new AlertDialog.Builder(this)
                                .setTitle("提示")
                                .setMessage("请打开应用的蓝牙权限，允许应用使用蓝牙连接附近的设备")
                                .show();
                    }
                }));
            } else {
                showToast("openBluetoothAdapter ok");
                startBluetoothDevicesDiscovery();
            }
        }));
        ECBLE.openBluetoothAdapter(this);
    }
    void startBluetoothDevicesDiscovery() {
        ECBLE.onBluetoothDeviceFound((String id, String name, String mac, int rssi) -> runOnUiThread(() -> {
            boolean isExist = false;
            for (DeviceInfo tempDevice : deviceListData) {
                if (tempDevice.id.equals(id)) {
                    tempDevice.rssi = rssi;
                    tempDevice.name = name;
                    isExist = true;
                    break;
                }
            }
            if (!isExist) {
                deviceListData.add(new DeviceInfo(id, name, mac, rssi));
            }
        }));
        ECBLE.startBluetoothDevicesDiscovery(this);
    }
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        EasyPermissions.onRequestPermissionsResult(requestCode, permissions, grantResults, this);
    }
    @Override
    public void onPermissionsGranted(int requestCode, @NonNull List<String> perms) {
        ECBLE.onPermissionsGranted(this, requestCode, perms);
    }
    @Override
    public void onPermissionsDenied(int requestCode, @NonNull List<String> perms) {
        ECBLE.onPermissionsDenied(requestCode, perms);
    }
    //一些显示dialog和提示信息的函数
    void showAlert(String content, Runnable callback) {
        new AlertDialog.Builder(this)
                .setTitle("提示")
                .setMessage(content)
                .setPositiveButton("OK", (dialogInterface, i) ->
                        new Thread(callback).start()
                )
                .setCancelable(false)
                .create().show();
    }
    void showConnectDialog() {
        if (connectDialog == null) {
            connectDialog = new AlertDialog.Builder(EnterActivity.this);
            connectDialog.setMessage("连接中...");
            connectDialog.setCancelable(false);
        }
        dialog = connectDialog.show();
    }
    void showAddremindersDialog() {
//        AlertDialog.Builder alertDialog = new AlertDialog.Builder(this);
//        LayoutInflater inflater = this.getLayoutInflater();
//        View dialogView = inflater.inflate(R.layout.dialog_add_reminder, null);
//        alertDialog.setView(dialogView);
//        EditText editText = dialogView.findViewById(R.id.edit_text);
//        alertDialog.setTitle("添加待办事项")
//                .setPositiveButton("OK", (dialog, which) -> {
//                    if (editText.getText() != null && !editText.getText().toString().isEmpty()) {
//                        remindersDataBase.insertreminderedThings(editText.getText().toString());
//                    }
//                })
//                .setNegativeButton("Cancel", (dialog, which) -> {
//                    // Do nothing
//                })
//                .create()
//                .show();
    }
    void hideConnectDialog() {
        if (dialog != null) {
            dialog.dismiss();
        }
    }
    void showToast(String text) {
        Toast.makeText(this, text, Toast.LENGTH_SHORT).show();
    }
}
//设备信息类
class DeviceInfo {
    String id;
    String name;
    String mac;
    int rssi;
    DeviceInfo(String id, String name, String mac, int rssi) {
        this.id = id;
        this.name = name;
        this.mac = mac;
        this.rssi = rssi;
    }
}
//设备信息的适配器
class DeviceAdapter extends ArrayAdapter<DeviceInfo> {
    private final int myResource;
    public DeviceAdapter(@NonNull Context context, int resource, List<DeviceInfo> deviceListData) {
        super(context, resource, deviceListData);
        myResource = resource;
    }
    @SuppressLint("DefaultLocale")
    @NonNull
    @Override
    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
        DeviceInfo deviceInfo = getItem(position);
        String name = "";
        int rssi = 0;
        if (deviceInfo != null) {
            name = deviceInfo.name;
            rssi = deviceInfo.rssi;
        }
        //检查是否是ytw3
        if (name.startsWith("YTW3")) {
            @SuppressLint("ViewHolder")
            View view = LayoutInflater.from(getContext()).inflate(myResource, parent, false);
            ImageView headImg = view.findViewById(R.id.iv_type);
            headImg.setImageResource(R.drawable.ytw_icon);
            ((TextView) view.findViewById(R.id.tv_name)).setText(name);
            ((TextView) view.findViewById(R.id.tv_rssi)).setText(String.format("%d", rssi));
            ImageView rssiImg = view.findViewById(R.id.iv_rssi);
            if (rssi >= -41) rssiImg.setImageResource(R.drawable.s5);
            else if (rssi >= -55) rssiImg.setImageResource(R.drawable.s4);
            else if (rssi >= -65) rssiImg.setImageResource(R.drawable.s3);
            else if (rssi >= -75) rssiImg.setImageResource(R.drawable.s2);
            else rssiImg.setImageResource(R.drawable.s1);
            return view;
        } else {
            View emptyView = new View(getContext());
            emptyView.setVisibility(View.GONE);
            return emptyView;
        }
    }
}

class Adapter extends ArrayAdapter<remindersDataBase.remindersRecord> {
    private final int myResource;
    private final Context context;
    public Adapter(@NonNull Context context, int resource, List<remindersDataBase.remindersRecord> remindersRecordListData) {
        super(context, resource, remindersRecordListData);
        myResource = resource;
        this.context = context;
    }
    @SuppressLint("DefaultLocale")
    @Override
    @NonNull
    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
        remindersDataBase.remindersRecord remindersRecord = getItem(position);
        String thing = "";
        if (remindersRecord != null) {
            thing = remindersRecord.getThings();
            View view = LayoutInflater.from(context).inflate(myResource, parent, false);
            TextView textView = view.findViewById(R.id.reminder_TextView);
            textView.setText(thing);
            return view;
        } else {
            View emptyView = new View(context);
            emptyView.setVisibility(View.GONE);
            return emptyView;
        }
    }
}
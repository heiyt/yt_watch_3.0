package com.example.ytw3;

import android.annotation.SuppressLint;
import android.content.pm.ActivityInfo;
import android.icu.util.Calendar;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import com.amap.api.location.AMapLocation;
import com.amap.api.location.AMapLocationClient;
import com.amap.api.location.AMapLocationClientOption;
import com.amap.api.location.AMapLocationListener;
import com.amap.api.maps.MapView;
import com.amap.api.maps.MapsInitializer;
import com.amap.apis.utils.core.api.AMapUtilCoreApi;

import java.text.SimpleDateFormat;
import java.util.Date;


public class BLE_ControlActivity extends AppCompatActivity{
    MapView mMapView = null;
    public AMapLocationClient mLocationClient = null;
    public AMapLocationListener mLocationListener = null;
    public AMapLocationClientOption mLocationOption = null;

    @SuppressLint("SourceLockedOrientationActivity")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_ble_control);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.activity_device), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        Map_Init(savedInstanceState);
        // 同步时间按钮,空格一个都不能改
        findViewById(R.id.bt_send_time).setOnClickListener((View view)->{
            String data = "01 " + new SimpleDateFormat("HH mm ss ").format(new Date(System.currentTimeMillis()));
            Calendar calendar = Calendar.getInstance();
            int dayOfWeek = calendar.get(Calendar.DAY_OF_WEEK); // 获取当前日期是星期几的数字表示（1-7，星期日到星期六）
            data = data + new SimpleDateFormat("yy yy MM dd").format(calendar.getTime()) + " 0" + dayOfWeek + " 00 00 00 00 00 00 00 00 00 00 00";
            data = data.replace(" ","").replace("\r","").replace("\n","");
            ECBLE.writeBLECharacteristicValue(data, true);
            Toast.makeText(this, "时间和天气同步开始",Toast.LENGTH_SHORT).show();
        });
        // 蓝牙断开连接
        ECBLE.onBLEConnectionStateChange((boolean ok, int errCode, String errMsg)-> runOnUiThread(()->{
            showAlert("蓝牙断开连接",()->{});
        }));
        // 接收到数据
        ECBLE.onBLECharacteristicValueChange((String str,String strHex)-> runOnUiThread(()->{
            if (str.equals("sync end")) {
                Toast.makeText(this, "时间和天气同步成功",Toast.LENGTH_SHORT).show();
            }
        }));
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        mMapView.onDestroy();
        ECBLE.onBLECharacteristicValueChange((str,strHex)->{});
        ECBLE.onBLEConnectionStateChange((ok,errCode,errMsg)->{});
        ECBLE.closeBLEConnection();
    }
    @Override
    protected void onResume() {
        super.onResume();
        mMapView.onResume();
    }
    @Override
    protected void onPause() {
        super.onPause();
        mMapView.onPause();
    }
    void Map_Init(Bundle savedInstanceState){
        MapsInitializer.updatePrivacyShow(this, true, true);
        MapsInitializer.updatePrivacyAgree(this,true);
        AMapLocationClient.updatePrivacyShow(this,true,true);
        AMapLocationClient.updatePrivacyAgree(this,true);
        mMapView = (MapView) findViewById(R.id.mapview);
        mMapView.onCreate(savedInstanceState);
        //声明定位回调监听器
        mLocationListener = new AMapLocationListener() {
            @Override
            public void onLocationChanged(AMapLocation aMapLocation) {
                
            }
        };
        //初始化定位
        try {
            mLocationClient = new AMapLocationClient(getApplicationContext());
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        //设置定位回调监听
        mLocationClient.setLocationListener(mLocationListener);
        //初始化AMapLocationClientOption对象
        mLocationOption = new AMapLocationClientOption();
        AMapUtilCoreApi.setCollectInfoEnable(true);
    }
    void showAlert(String content, Runnable callback){
        new AlertDialog.Builder(this)
                .setTitle("提示")
                .setMessage(content)
                .setPositiveButton("OK",  (dialogInterface , i)-> new Thread(callback).start())
                .setCancelable(false)
                .create().show();
    }
}
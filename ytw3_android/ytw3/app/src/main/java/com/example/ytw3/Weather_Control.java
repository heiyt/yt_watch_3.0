package com.example.ytw3;

import android.content.Context;
import android.os.Handler;
import android.widget.Toast;

import com.qweather.sdk.bean.base.Code;
import com.qweather.sdk.bean.base.Lang;
import com.qweather.sdk.bean.base.Unit;
import com.qweather.sdk.bean.geo.GeoBean;
import com.qweather.sdk.bean.weather.WeatherNowBean;
import com.qweather.sdk.view.QWeather;

import java.util.List;

public class Weather_Control {
    private Context context = null;
    private String weather_text;
    private String strict_name;
    private String town_name;
    private String province_name;
    private String temperature;
    private String icon;

    public Weather_Control(Context context) {
        this.context = context;
    }
    void WeatherRefresh(String location) {
        new Handler().postDelayed(() -> {
            QWeather.getWeatherNow(context, location, Lang.ZH_HANS, Unit.METRIC, new QWeather.OnResultWeatherNowListener() {
                @Override
                public void onError(Throwable e) {
                    showToast(e.toString());
                }
                @Override
                public void onSuccess(WeatherNowBean weatherBean) {
                    if (Code.OK == weatherBean.getCode()) {
                        WeatherNowBean.NowBaseBean now = weatherBean.getNow();
                        weather_text = now.getText();
                        temperature = now.getTemp();
                        now.getFeelsLike();
                        now.getCloud();
                        now.getDew();
                        now.getHumidity();
                        icon = now.getIcon();
                    } else {
                        Code code = weatherBean.getCode();
                        showToast(code.getCode());
                    }
                }
            });}, 200);
    }
    void CityFind(String location) {
        new Handler().postDelayed(() -> {
            QWeather.getGeoCityLookup(context, location, new QWeather.OnResultGeoListener() {
                @Override
                public void onError(Throwable e) {
                    showToast(e.toString());
                }
                @Override
                public void onSuccess(GeoBean geoBean) {
                    if (Code.OK == geoBean.getCode()) {
                        List<GeoBean.LocationBean> locationBeans = geoBean.getLocationBean();
                        strict_name = locationBeans.get(0).getName();
                        town_name = locationBeans.get(0).getAdm2();
                        province_name = locationBeans.get(0).getAdm1();
                    } else {
                        Code code = geoBean.getCode();
                        showToast(code.getCode());
                    }
                }
            });}, 200);
    }
    String getWeatherText(){
        return weather_text;//获取现在天气信息、晴朗下雨啥的
    }
    String getCityStrict(){
        return strict_name;//获取县的名字
    }
    String getCityTown(){
        return town_name;//获取地级市的名字
    }
    String getCityProvince(){
        return province_name;//获取省的名字
    }
    String getTemperature(){
        return temperature;//获取气温
    }
    String getIcon(){
        return icon;//获取图标
    }

    void showToast(String text) {
        Toast.makeText(context, text, Toast.LENGTH_SHORT).show();//发toast方便一些
    }
}

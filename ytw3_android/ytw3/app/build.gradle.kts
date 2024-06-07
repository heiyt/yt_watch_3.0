plugins {
    alias(libs.plugins.androidApplication)
}

android {
    namespace = "com.example.ytw3"
    compileSdk = 34

    defaultConfig {
        applicationId = "com.example.ytw3"
        minSdk = 31
        targetSdk = 34
        versionCode = 1
        versionName = "1.0"
        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(getDefaultProguardFile("proguard-android-optimize.txt"), "proguard-rules.pro")
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }
    buildFeatures {
        viewBinding = true
    }
}

dependencies {
    implementation(libs.appcompat)
    implementation(libs.material)
    implementation(libs.activity)
    implementation(libs.constraintlayout)
    implementation(libs.swiperefreshlayout)
    implementation("pub.devrel:easypermissions:3.0.0")
    implementation(files("src/main/libs/QWeather_Public_Android_V4.17.jar"))
    implementation("com.squareup.okhttp3:okhttp:3.12.12")
    implementation("com.google.code.gson:gson:2.10.1")
    implementation(libs.play.services.maps)
    implementation(files("src/main/libs/AMap3DMap_10.0.700_AMapSearch_9.7.2_AMapLocation_6.4.5_20240508.jar"))
    testImplementation(libs.junit)
    androidTestImplementation(libs.ext.junit)
    androidTestImplementation(libs.espresso.core)
}
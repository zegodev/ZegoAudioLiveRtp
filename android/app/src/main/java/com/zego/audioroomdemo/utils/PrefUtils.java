package com.zego.audioroomdemo.utils;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.SharedPreferences;
import android.text.TextUtils;

import com.zego.audioroomdemo.AudioApplication;

import static com.zego.audioroomdemo.utils.AppSignKeyUtils.UDP_APP_ID;

/**
 * Created by realuei on 2017/6/2.
 */

public class PrefUtils {
    static final private String KUserId = "userId";
    static final private String KUserName = "userName";

    static final private String KAudio_Prepare = "audio_prepare";
    static final private String KManual_Publish = "manual_publish";

    static final private String Pref_Business_Type = "Pref_Business_Type";
    static final private String Pref_key_App_Key = "zego_app_key";


    static private String KEY_APP_FLAVOR = "zego_app_flavor_index";

    static final private String Pref_key_App_Id = "zego_app_id";

    static final private String ZEGO_APP_TEST = "zego_app_test";

    static final private String ZEGO_APP_INTERNATIONAL = "zego_app_international";

    private static final String ZEGO_APP_WEBRTC = "zego_app_webRtc";

    static private PrefUtils sInst = new PrefUtils();

    private SharedPreferences mPref;

    private PrefUtils() {
        mPref = AudioApplication.sApplication.getSharedPreferences("app_data_v1", Context.MODE_PRIVATE);
    }

    static public void setUserId(String userId) {
        SharedPreferences.Editor editor = sInst.mPref.edit();
        editor.putString(KUserId, userId);
        editor.apply();
    }

    static public String getUserId() {
        return sInst.mPref.getString(KUserId, null);
    }

    static public void setUserName(String userName) {
        SharedPreferences.Editor editor = sInst.mPref.edit();
        editor.putString(KUserName, userName);
        editor.apply();
    }

    static public String getUserName() {
        return sInst.mPref.getString(KUserName, null);
    }

    static public void enableAudioPrepare(boolean enablePrepare) {
        SharedPreferences.Editor editor = sInst.mPref.edit();
        editor.putBoolean(KAudio_Prepare, enablePrepare);
        editor.apply();
    }

    static public boolean isEnableAudioPrepare() {
        return sInst.mPref.getBoolean(KAudio_Prepare, false);
    }

    static public void setManualPublish(boolean enableManual) {
        SharedPreferences.Editor editor = sInst.mPref.edit();
        editor.putBoolean(KManual_Publish, enableManual);
        editor.apply();
    }

    static public boolean isManualPublish() {
        return sInst.mPref.getBoolean(KManual_Publish, false);
    }

    static public void setAppId(long appId) {
        SharedPreferences.Editor editor = sInst.mPref.edit();
        editor.putLong(Pref_key_App_Id, appId);
        editor.apply();
    }

    static public long getAppId() {
        return sInst.mPref.getLong(Pref_key_App_Id, -1);
    }

    static public void setAppKey(byte[] signKey) {
        String strSignKey = AppSignKeyUtils.convertSignKey2String(signKey);
        SharedPreferences.Editor editor = sInst.mPref.edit();
        editor.putString(Pref_key_App_Key, strSignKey);
        editor.apply();
    }

    public static void setBusinessType(int businessType) {
        SharedPreferences.Editor editor = sInst.mPref.edit();
        editor.putInt(Pref_Business_Type, businessType);
        editor.apply();
    }

    public static int getBusinessType() {
        return sInst.mPref.getInt(Pref_Business_Type, 0);
    }

    public static void setInternational(boolean international) {
        sInst.setBooleanValue(ZEGO_APP_INTERNATIONAL, international);
    }

    public static int getCurrentAppFlavor() {
        return sInst.mPref.getInt(KEY_APP_FLAVOR, -1);
    }

    public static void setAppFlavor(int appFlavorIndex) {
        SharedPreferences.Editor editor = sInst.mPref.edit();
        editor.putInt(KEY_APP_FLAVOR, appFlavorIndex);
        editor.commit();
    }

    public void setBooleanValue(String key, boolean value) {
        SharedPreferences.Editor editor = sInst.mPref.edit();
        editor.putBoolean(key, value);
        editor.commit();
    }


    public boolean getBooleanValue(String key, boolean defaultValue) {
        return sInst.mPref.getBoolean(key, defaultValue);
    }

    static public String getAppKeyToString() {
        String strSignKey = sInst.mPref.getString(Pref_key_App_Key, null);
        if (TextUtils.isEmpty(strSignKey)) {
            return null;
        }
        return strSignKey;
    }

    static public byte[] getAppKey() {
        String strSignKey = sInst.mPref.getString(Pref_key_App_Key, null);
        if (TextUtils.isEmpty(strSignKey)) {
            return null;
        }
        try {
            return AppSignKeyUtils.parseSignKeyFromString(strSignKey);
        } catch (NumberFormatException e) {
        }
        return null;
    }


    public static void setUseTestEnv(boolean v) {
        sInst.setBooleanValue(ZEGO_APP_TEST, v);
    }

    public static boolean getUseTestEnv() {
        return sInst.getBooleanValue(ZEGO_APP_TEST, true);
    }


    public static void setAppWebRtc(boolean v) {
        sInst.setBooleanValue(ZEGO_APP_WEBRTC, v);
    }

    public static boolean getAppWebRtc() {
        return sInst.getBooleanValue(ZEGO_APP_WEBRTC, false);
    }

}

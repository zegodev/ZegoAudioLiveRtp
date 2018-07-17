package com.zego.audioroomdemo.utils;

import android.content.Context;
import android.content.SharedPreferences;
import android.text.TextUtils;

import com.zego.audioroomdemo.AudioApplication;

/**
 * Created by realuei on 2017/6/2.
 */

public class PrefUtils {
    static final private String KUserId = "userId";
    static final private String KUserName = "userName";

    static final private String KAudio_Prepare = "audio_prepare";
    static final private String KManual_Publish = "manual_publish";

    static final private String Pref_key_App_Id = "zego_app_id";
    static final private String Pref_key_App_Key = "zego_app_key";

    static private PrefUtils sInst = new PrefUtils();

    private SharedPreferences mPref;

    private PrefUtils() {
        mPref = AudioApplication.sApplication.getSharedPreferences("app_data", Context.MODE_PRIVATE);
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

}

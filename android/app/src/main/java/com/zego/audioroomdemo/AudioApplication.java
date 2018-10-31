package com.zego.audioroomdemo;

import android.annotation.SuppressLint;
import android.app.Application;
import android.os.Handler;
import android.os.Message;
import android.text.TextUtils;

import com.tencent.bugly.crashreport.CrashReport;
import com.zego.audioroomdemo.utils.PrefUtils;
import com.zego.audioroomdemo.utils.AppSignKeyUtils;
import com.zego.zegoaudioroom.ZegoAudioRoom;
import com.zego.zegoliveroom.ZegoLiveRoom;
import com.zego.zegoliveroom.constants.ZegoConstants;
import com.zego.zegoliveroom.entity.ZegoExtPrepSet;

import java.util.ArrayList;

/**
 * Created by realuei on 2017/4/13.
 */

public class AudioApplication extends Application {

    private ArrayList<String> logSet;
    private ZegoAudioRoom mZegoAudioRoom;

    static public AudioApplication sApplication;

    public interface ILogUpdateObserver {
        void onLogAdd(String logMessage);
    }

    @SuppressLint("HandlerLeak")
    private Handler logHandler = new Handler() {

        @Override
        public void handleMessage(Message message) {
            String logMessage = (String) message.obj;
            if (logSet.size() >= 1000) {
                logSet.remove(logSet.size() - 1);
            }
            logSet.add(0, logMessage);
            synchronized (AudioApplication.class) {
                for (ILogUpdateObserver observer : mLogObservers) {
                    observer.onLogAdd(logMessage);
                }
            }
        }
    };

    @Override
    public void onCreate() {
        super.onCreate();

        sApplication = this;
        initSDK();
        String userId = getUserId();
        CrashReport.initCrashReport(getApplicationContext(), "9a7c25a3f2", false);
        CrashReport.setUserId(userId);

    }

    private void initData() {
        logSet = new ArrayList<>();
    }

    private void initSDK() {
        initData();

        String userId = getUserId();
        String userName = getUserName();

        ZegoAudioRoom.setUser(userId, userName);
        ZegoAudioRoom.setUseTestEnv(PrefUtils.getUseTestEnv());
//        ZegoAudioRoom.enableAudioPrep(PrefUtils.isEnableAudioPrepare());
        ZegoExtPrepSet config = new ZegoExtPrepSet();
        config.encode = false;
        config.channel = 0;
        config.sampleRate = 0;
        config.samples = 1;
        ZegoAudioRoom.enableAudioPrep2(PrefUtils.isEnableAudioPrepare(), config);

        // 始终关闭回声消除，避免混音时人声卡顿
        //ZegoAudioRoom.setAudioDeviceMode(ZegoConstants.AudioDeviceMode.General);
        mZegoAudioRoom = new ZegoAudioRoom();
        mZegoAudioRoom.setManualPublish(PrefUtils.isManualPublish());
        long appId;
        byte[] signKey;
        int currentAppFlavor = PrefUtils.getCurrentAppFlavor();
        if (currentAppFlavor <= 1) {
            if (currentAppFlavor == -1 || currentAppFlavor == 0) {
                appId = AppSignKeyUtils.UDP_APP_ID;
                signKey = AppSignKeyUtils.requestSignKey(AppSignKeyUtils.UDP_APP_ID);
            } else {
                appId = AppSignKeyUtils.INTERNATIONAL_APP_ID;
                signKey = AppSignKeyUtils.requestSignKey(AppSignKeyUtils.INTERNATIONAL_APP_ID);
            }

        } else {
            appId = PrefUtils.getAppId();
            signKey = PrefUtils.getAppKey();
        }


        ZegoAudioRoom.setBusinessType(PrefUtils.getBusinessType());

        mZegoAudioRoom.initWithAppId(appId, signKey, this);

        mZegoAudioRoom.setLatencyMode(ZegoConstants.LatencyMode.Low3);

    }

    public void reInitZegoSDK() {
        if (mZegoAudioRoom != null) {
            mZegoAudioRoom.unInit();
        }

        initSDK();
    }

    private String getUserId() {
        String userId = PrefUtils.getUserId();
        if (TextUtils.isEmpty(userId)) {
            userId = System.currentTimeMillis() / 1000 + "";
            PrefUtils.setUserId(userId);
        }
        return userId;
    }

    private String getUserName() {
        String userName = PrefUtils.getUserName();
        if (TextUtils.isEmpty(userName)) {
            userName = android.os.Build.MODEL + getUserId();
            PrefUtils.setUserName(userName);
        }
        return userName;
    }

    public void appendLog(String str) {
        Message msg = Message.obtain(logHandler, 0, str);
        msg.sendToTarget();
    }

    public void appendLog(String format, Object... args) {
        String str = String.format(format, args);
        appendLog(str);
    }

    public ArrayList<String> getLogSet() {
        return logSet;
    }

    private ArrayList<ILogUpdateObserver> mLogObservers = new ArrayList<>();

    public synchronized void registerLogUpdateObserver(ILogUpdateObserver observer) {
        if (observer != null && !mLogObservers.contains(observer)) {
            mLogObservers.add(observer);
        }
    }

    public synchronized void unregisterLogUpdateObserver(ILogUpdateObserver observer) {
        if (mLogObservers.contains(observer)) {
            mLogObservers.remove(observer);
        }
    }

    private boolean useTestEnv = false;

    public boolean isUseTestEnv() {
        useTestEnv = PrefUtils.getUseTestEnv();
        return useTestEnv;
    }

    public void setUseTestEnv(boolean useTestEnv) {
        PrefUtils.setUseTestEnv(useTestEnv);
        this.useTestEnv = useTestEnv;
    }

    public ZegoAudioRoom getAudioRoomClient() {
        return mZegoAudioRoom;
    }
}

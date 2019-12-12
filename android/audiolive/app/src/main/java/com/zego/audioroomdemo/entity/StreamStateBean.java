package com.zego.audioroomdemo.entity;

public class StreamStateBean {

    public String userID;
    public String userName;
    public String streamID;   // 唯一识别
    public String extraInfo;

    public int soundLevel;

    public int connectState = ConnectState.COMMON; // 当前的网络连接状态，0代表正常，1代表disconnect，2代表重连中
    public boolean isMuteMic; // 是否 关闭了麦克风

    public double audioFps;
    public double akbps;
    public int rtt;
    public int pktLostRate;
    public int quality;
    public double audioBreakRate;

    @Override
    public boolean equals(Object obj) {
        return obj instanceof StreamStateBean && ((StreamStateBean) obj).streamID != null && ((StreamStateBean) obj).streamID.equals(streamID);
    }

    @Override
    public int hashCode() {
        return userID.hashCode();
    }

    // 当前连接状态
    public static class ConnectState {
        public final static int COMMON = 0;  // 正常状态
        public final static int DISCONNECT = 1;  // 断连状态
        public final static int RECONNECT = 2; // 重连状态
    }
}

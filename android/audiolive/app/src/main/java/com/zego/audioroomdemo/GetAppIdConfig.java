package com.zego.audioroomdemo;
/**
 * Created by zego on 2018/11/15.
 */

public class GetAppIdConfig {
		
    /**
     * 请提前在即构管理控制台获取 appID 与 appSign
     *  AppID 填写样式示例：
            public static final long appId = 123456789L;
     *  appSign 填写样式示例：
            public static final byte[] appSign = {
                (byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x00,
                (byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x00,
                (byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x00,
                (byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x00,
                (byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x00,
                (byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x00,
                (byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x00,
                (byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x00
            }
     *
     */

    static final public long RTMP_APP_ID = ;

    static final public long UDP_APP_ID = ;

    static final public long INTERNATIONAL_APP_ID = ;


    final static public byte[] appSign_rtmp = new byte[]{};


    final static public byte[] appSign_udp = new byte[]{};


    final static public byte[] appSign_international = new byte[]{};
    
    // 测试环境开关
    final static public boolean testEnv = true;
}

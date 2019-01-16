package com.zego.audioroomdemo.utils;

import android.content.Context;
import android.content.res.Resources;

import com.zego.audioroomdemo.R;

/**
 * App's Id and key utils.
 * <p>
 * <p>Copyright © 2017 Zego. All rights reserved.</p>
 *
 * @author realuei on 2017/7/11.
 */

public class AppSignKeyUtils {
    @SuppressWarnings("unused")

    /**  请开发者联系 ZEGO support 获取各自业务的 AppID 与 signKey
     Demo 默认使用 UDP 模式，请填充该模式下的 AppID 与 signKey,其他模式不需要可不用填
     AppID 填写样式示例：1234567890l
     signKey 填写样式示例：{(byte)0x00,(byte)0x01,(byte)0x02} **/

    static final private long RTMP_APP_ID = 1L;

    static final public long UDP_APP_ID = 544462288L;

    static final public long INTERNATIONAL_APP_ID = 1846777542L;


    final static private byte[] signData_rtmp = new byte[]{
            (byte) 0x91, (byte) 0x93, (byte) 0xcc, (byte) 0x66, (byte) 0x2a, (byte) 0x1c, (byte) 0x0e, (byte) 0xc1,
            (byte) 0x35, (byte) 0xec, (byte) 0x71, (byte) 0xfb, (byte) 0x07, (byte) 0x19, (byte) 0x4b, (byte) 0x38,
            (byte) 0x41, (byte) 0xd4, (byte) 0xad, (byte) 0x83, (byte) 0x78, (byte) 0xf2, (byte) 0x59, (byte) 0x90,
            (byte) 0xe0, (byte) 0xa4, (byte) 0x0c, (byte) 0x7f, (byte) 0xf4, (byte) 0x28, (byte) 0x41, (byte) 0xf7
    };


    final static private byte[] signData_udp = new byte[]{
            (byte) 0x11, (byte) 0x89, (byte) 0xec, (byte) 0x9f, (byte) 0x87, (byte) 0xa8, (byte) 0x5c, (byte) 0xae,
            (byte) 0x5b, (byte) 0x07, (byte) 0xdb, (byte) 0x7b, (byte) 0xa0, (byte) 0x45, (byte) 0x82, (byte) 0x7d,
            (byte) 0x05, (byte) 0xda, (byte) 0x48, (byte) 0x15, (byte) 0xb6, (byte) 0x73, (byte) 0x82, (byte) 0xa7,
            (byte) 0xec, (byte) 0x5c, (byte) 0x74, (byte) 0xf5, (byte) 0xc6, (byte) 0x3d, (byte) 0x6c, (byte) 0x26};


    final static private byte[] signData_international = new byte[]{
            (byte) 0x59, (byte) 0x5c, (byte) 0x36, (byte) 0x29, (byte) 0x53, (byte) 0xa7, (byte) 0xf9, (byte) 0x15,
            (byte) 0x3f, (byte) 0xbf, (byte) 0x7b, (byte) 0x4d, (byte) 0xe5, (byte) 0xca, (byte) 0x77, (byte) 0xe5,
            (byte) 0x89, (byte) 0xed, (byte) 0x91, (byte) 0x4e, (byte) 0xd3, (byte) 0x2c, (byte) 0x5f, (byte) 0x7d,
            (byte) 0x74, (byte) 0x1a, (byte) 0x1d, (byte) 0xbc, (byte) 0xb1, (byte) 0x7d, (byte) 0xca, (byte) 0x36};


    static public boolean isInternationalProduct(long appId) {
        return appId == INTERNATIONAL_APP_ID;
    }

    static public boolean isUdpProduct(long appId) {
        return appId == UDP_APP_ID;
    }

    static public byte[] requestSignKey(long appId) {
        if (appId == UDP_APP_ID) {
            return signData_udp;
        } else if (appId == INTERNATIONAL_APP_ID) {
            return signData_international;
        } else if (appId == RTMP_APP_ID) {
            return signData_rtmp;
        }
        return null;
    }

    static public String getAppTitle(long currentAppFlavor, Context context) {
        String appTitle;
        Resources resources = context.getResources();
        if (currentAppFlavor == 1) {   // International
            appTitle = resources.getString(R.string.zg_app_title, resources.getString(R.string.zg_text_app_flavor_intl));
        } else if (currentAppFlavor == 2) {    // Custom
            appTitle = resources.getString(R.string.zg_app_title, resources.getString(R.string.zg_text_app_flavor_customize));
        } else {   // UDP
            appTitle = resources.getString(R.string.zg_app_title, resources.getString(R.string.zg_text_app_flavor_china));
        }
        return appTitle;
    }


    static public String convertSignKey2String(byte[] signKey) {
        if (signKey != null) {
            StringBuilder buffer = new StringBuilder();
            for (int b : signKey) {
                buffer.append("0x").append(Integer.toHexString((b & 0x000000FF) | 0xFFFFFF00).substring(6)).append(",");
            }
            buffer.setLength(buffer.length() - 1);
            return buffer.toString();
        } else {
            return "";
        }
    }

    static public byte[] parseSignKeyFromString(String strSignKey) throws NumberFormatException {
        String[] keys = strSignKey.split(",");
        if (keys.length != 32) {
            throw new NumberFormatException("App Sign Key Illegal");
        }
        byte[] byteSignKey = new byte[32];
        for (int i = 0; i < 32; i++) {
            int data = Integer.valueOf(keys[i].trim().replace("0x", ""), 16);
            byteSignKey[i] = (byte) data;
        }
        return byteSignKey;
    }
}

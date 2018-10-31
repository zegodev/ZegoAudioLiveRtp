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
     AppID 填写样式示例：1234567890
     signKey 填写样式示例：{0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
     0x08,0x09,0x00,0x01,0x02,0x03,0x04,0x05,
     0x06,0x07,0x08,0x09,0x00,0x01,0x02,0x03,
     0x04,0x05,0x06,0x07,0x08,0x09,0x00,0x01} **/

    static final private long RTMP_APP_ID = ;

    static final public long UDP_APP_ID = ;

    static final public long INTERNATIONAL_APP_ID = ;


    final static private byte[] signData_rtmp = new byte[]{};


    final static private byte[] signData_udp = new byte[]{};


    final static private byte[] signData_international = new byte[]{};


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
        if (currentAppFlavor == 0) {   // UDP
            appTitle = resources.getString(R.string.zg_app_title, resources.getString(R.string.zg_text_app_flavor_china));
        } else if (currentAppFlavor == 1) {   // International
            appTitle = resources.getString(R.string.zg_app_title, resources.getString(R.string.zg_text_app_flavor_intl));
        } else {    // Custom
            appTitle = resources.getString(R.string.zg_app_title, resources.getString(R.string.zg_text_app_flavor_customize));
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

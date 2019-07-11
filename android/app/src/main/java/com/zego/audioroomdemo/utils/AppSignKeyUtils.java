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

    /**
     * 请提前在即构管理控制台获取 appID 与 appSign
     * Demo 默认使用 UDP 模式，请填充该模式下的 AppID 与 appSign,其他模式不需要可不用填
     * AppID 填写样式示例：1234567890l
     * appSign 填写样式示例：{(byte)0x00,(byte)0x01,(byte)0x02,(byte)0x03}
     **/

    static final private long RTMP_APP_ID = ;

    static final public long UDP_APP_ID = ;

    static final public long INTERNATIONAL_APP_ID = ;


    final static private byte[] appSign_rtmp = new byte[]{};

    final static private byte[] appSign_udp = new byte[]{};


    final static private byte[] appSign_international = new byte[]{};


    static public boolean isInternationalProduct(long appId) {
        return appId == INTERNATIONAL_APP_ID;
    }

    static public boolean isUdpProduct(long appId) {
        return appId == UDP_APP_ID;
    }

    static public byte[] requestSignKey(long appId) {
        if (appId == UDP_APP_ID) {
            return appSign_udp;
        } else if (appId == INTERNATIONAL_APP_ID) {
            return appSign_international;
        } else if (appId == RTMP_APP_ID) {
            return appSign_rtmp;
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


    static public String convertSignKey2String(byte[] appSign) {
        if (appSign != null) {
            StringBuilder buffer = new StringBuilder();
            for (int b : appSign) {
                buffer.append("0x").append(Integer.toHexString((b & 0x000000FF) | 0xFFFFFF00).substring(6)).append(",");
            }
            buffer.setLength(buffer.length() - 1);
            return buffer.toString();
        } else {
            return "";
        }
    }

    static public byte[] parseSignKeyFromString(String strAppSign) throws NumberFormatException {
        String[] keys = strAppSign.split(",");
        if (keys.length != 32) {
            throw new NumberFormatException("App Sign Illegal");
        }
        byte[] byteSignKey = new byte[32];
        for (int i = 0; i < 32; i++) {
            int data = Integer.valueOf(keys[i].trim().replace("0x", ""), 16);
            byteSignKey[i] = (byte) data;
        }
        return byteSignKey;
    }
}

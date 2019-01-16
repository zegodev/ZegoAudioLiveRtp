package com.zego.audioroomdemo.utils;

import com.zego.audioroomdemo.adapters.RecyclerGridViewAdapter;
import com.zego.zegoliveroom.entity.ZegoPlayStreamQuality;
import com.zego.zegoliveroom.entity.ZegoPublishStreamQuality;

/**
 * Created by zego on 2019/1/14.
 */

public class EntityConversion {


    public static RecyclerGridViewAdapter.CommonStreamQuality publishQualityToCommonStreamQuality(ZegoPublishStreamQuality zegoPlayStreamQuality) {
        RecyclerGridViewAdapter.CommonStreamQuality commonStreamQuality = new RecyclerGridViewAdapter.CommonStreamQuality();
        commonStreamQuality.audioFps = zegoPlayStreamQuality.anetFps;
        commonStreamQuality.videoFps = zegoPlayStreamQuality.vnetFps;
        commonStreamQuality.rtt = zegoPlayStreamQuality.rtt;
        commonStreamQuality.vkbps = zegoPlayStreamQuality.vkbps;
        commonStreamQuality.pktLostRate = zegoPlayStreamQuality.pktLostRate;
        commonStreamQuality.quality = zegoPlayStreamQuality.quality;
        commonStreamQuality.width = zegoPlayStreamQuality.width;
        commonStreamQuality.height = zegoPlayStreamQuality.height;
        commonStreamQuality.audioBreakRate = -1;
        return commonStreamQuality;
    }

    public static RecyclerGridViewAdapter.CommonStreamQuality playQualityToCommonStreamQuality(ZegoPlayStreamQuality zegoPlayStreamQuality) {
        RecyclerGridViewAdapter.CommonStreamQuality commonStreamQuality = new RecyclerGridViewAdapter.CommonStreamQuality();
        commonStreamQuality.audioFps = zegoPlayStreamQuality.anetFps;
        commonStreamQuality.videoFps = zegoPlayStreamQuality.vnetFps;
        commonStreamQuality.rtt = zegoPlayStreamQuality.rtt;
        commonStreamQuality.vkbps = zegoPlayStreamQuality.vkbps;
        commonStreamQuality.pktLostRate = zegoPlayStreamQuality.pktLostRate;
        commonStreamQuality.quality = zegoPlayStreamQuality.quality;
        commonStreamQuality.width = zegoPlayStreamQuality.width;
        commonStreamQuality.height = zegoPlayStreamQuality.height;
        commonStreamQuality.audioBreakRate = zegoPlayStreamQuality.audioBreakRate;
        return commonStreamQuality;
    }




}

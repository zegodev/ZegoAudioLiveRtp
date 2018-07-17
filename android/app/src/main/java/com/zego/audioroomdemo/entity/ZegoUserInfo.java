package com.zego.audioroomdemo.entity;


import com.zego.zegoliveroom.entity.ZegoUser;

/**
 * Created by zego on 2018/6/28.
 */

public class ZegoUserInfo extends ZegoUser {
    public String streamID;
    public boolean mute = true;
    public int progress;
    public int audioState = 0;

}

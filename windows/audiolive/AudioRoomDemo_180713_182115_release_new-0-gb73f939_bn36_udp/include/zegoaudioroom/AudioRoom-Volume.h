//
//  AudioRoom-Volume.h
//  zegoaudioroom
//
//  Copyright © 2017年 ZEGO. All rights reserved.
//

#ifndef AudioRoom_Volume_h
#define AudioRoom_Volume_h

#include "./AudioRoomDefines.h"

namespace ZEGO
{
    namespace AUDIOROOM
    {
#ifdef WIN32
        /**
         系统声卡声音采集开关
         
         @param bEnable true 打开，false 失败
         */
        ZEGO_API void EnableMixSystemPlayout(bool bEnable);
        
        /**
         获取麦克风音量
         
         @param deviceId 麦克风 deviceId
         @return -1: 获取失败，0~100 麦克风音量
         @note 切换麦克风后需要重新获取麦克风音量
         */
        ZEGO_API int GetMicDeviceVolume(const char *deviceId);
        
        /**
         设置麦克风音量
         
         @param deviceId 麦克风 deviceId
         @param volume 音量，取值(0,100)
         */
        ZEGO_API void SetMicDeviceVolume(const char *deviceId, int volume);
        
        /**
         获取扬声器音量
         
         @param deviceId 扬声器 deviceId
         @return -1: 获取失败，0~100 扬声器音量
         @note 切换扬声器后需要重新获取音量
         */
        ZEGO_API int GetSpeakerDeviceVolume(const char *deviceId);
        
        /**
         设置扬声器音量
         
         @param deviceId 扬声器 deviceId
         @param volume 音量，取值 (0，100)
         */
        ZEGO_API void SetSpeakerDeviceVolume(const char *deviceId, int volume);
        
        /**
         获取 App 中扬声器音量
         
         @param deviceId 扬声器 deviceId
         @return -1: 获取失败，0~100 扬声器音量
         */
        ZEGO_API int GetSpeakerSimpleVolume(const char *deviceId);
        
        /**
         设置 App 中扬声器音量
         
         @param deviceId 扬声器 deviceId
         @param volume 音量，取值 (0，100)
         */
        ZEGO_API void SetSpeakerSimpleVolume(const char *deviceId, int volume);
        
        /**
         获取扬声器是否静音
         
         @param deviceId 扬声器 deviceId
         @return true 静音，false 不静音
         */
        ZEGO_API bool GetSpeakerDeviceMute(const char *deviceId);
        
        /**
         设置扬声器静音
         
         @param deviceId 扬声器 deviceId
         @param mute true 静音，false 不静音
         */
        ZEGO_API void SetSpeakerDeviceMute(const char *deviceId, bool mute);
        
        /**
         获取 App 中扬声器是否静音
         
         @param deviceId 扬声器 deviceId
         @return true 静音，false 不静音
         */
        ZEGO_API bool GetSpeakerSimpleMute(const char *deviceId);
        
        /**
         设置 App 中扬声器静音
         
         @param deviceId 扬声器 deviceId
         @param mute true 静音，false 不静音
         */
        ZEGO_API void SetSpeakerSimpleMute(const char *deviceId, bool mute);
        
        /**
         获取默认的音频设备
         
         @param deviceType 音频类型
         @param deviceId 设备 Id
         @param deviceIdLength deviceId 字符串分配的长度
         @note 如果传入的字符串 buffer 长度小于默认 deviceId 的长度，则 deviceIdLength 返回实际需要的字符串长度
         */
        ZEGO_API void GetDefaultAudioDeviceId(AV::AudioDeviceType deviceType, char *deviceId, unsigned int *deviceIdLength);
        
        /**
         监听设备的音量变化
         
         @param deviceType 音频类型
         @param deviceId 设备 Id
         @return true 成功，false 失败
         @note 设置后如果有音量变化（包括 app 音量）通过 IZegoDeviceStateCallback::OnAudioVolumeChanged 回调
         */
        ZEGO_API bool SetAudioVolumeNotify(AV::AudioDeviceType deviceType, const char *deviceId);
        
        /**
         停止监听设备的音量变化
         
         @param deviceType 设备类型
         @param deviceId 设备 Id
         @return true 成功，false 失败
         */
        ZEGO_API bool StopAudioVolumeNotify(AV::AudioDeviceType deviceType, const char *deviceId);
        
#endif
    }
}
#endif /* AudioRoom_Volume_h */

//
//  AudioRoom-Publisher.h
//  zegoaudioroom
//
//  Copyright © 2017年 ZEGO. All rights reserved.
//

#ifndef AudioRoom_Publisher_h
#define AudioRoom_Publisher_h

#include "./AudioRoomDefines.h"
#include "./AudioRoomCallback-Publisher.h"

namespace AVE
{
    struct AudioFrame;
    struct ExtPrepSet;
    typedef void (*OnPrepCallback)(const AVE::AudioFrame& inFrame, AVE::AudioFrame& outFrame);
}

namespace ZEGO
{
    namespace AUDIOROOM
    {
        /**
         设置直播主播相关信息通知的回调
         
         @param pCB 回调对象指针
         @return true 成功，false 失败
         */
        
        ZEGO_API bool SetAudioLivePublisherCallback(IAudioLivePublisherCallback *pCB);
        
        ZEGO_API bool StartPublish();
        
        ZEGO_API bool StartPublish(const char *pszStreamID);
        
        ZEGO_API void StopPublish();
        
		/**
		设置或更新推流的附加信息

		@param pszStreamExtraInfo 流附加信息, 最大为 1024 字节
		@return 更新流附加信息成功后，同一房间内的其他人会收到 OnStreamExtraInfoUpdated 通知
		*/
		ZEGO_API bool SetPublishStreamExtraInfo(const char *pszStreamExtraInfo);

        /**
         开启麦克风
         
         @param bEnable true 打开，false 关闭。默认 false
         @return true 成功，false 失败
         @attention 推流时可调用本 API 进行参数配置
         */
        ZEGO_API bool EnableMic(bool bEnable);
        
        /**
         设置音频码率
         
         @param bitrate 码率
         @return true 成功，false 失败
         */
        ZEGO_API bool SetAudioBitrate(int bitrate);
        
        /**
         设置音频设备模式
         
         @param mode 模式，默认 ZEGO_AUDIO_DEVICE_MODE_AUTO
         @attention 确保在 Init 前调用
         */
        ZEGO_API void SetAudioDeviceMode(AV::ZegoAVAPIAudioDeviceMode mode);
        
        /**
         音频采集自动增益开关
         
         @param bEnable true 开启，false 关闭
         @return true 成功，false 失败
         */
        ZEGO_API bool EnableAGC(bool bEnable);
        
        /**
         回声消除开关
         
         @param bEnable true 开启，false 关闭
         @return true 成功，false 失败
         */
        ZEGO_API bool EnableAEC(bool bEnable);
        
        /**
         开启采集监听
         
         @param bEnable true 打开，false 关闭。默认 false
         @return true 成功，false 失败
         @attention 推流时可调用本 API 进行参数配置。连接耳麦时设置才实际生效。开启采集监听，主播方讲话后，会听到自己的声音。
         */
        ZEGO_API bool EnableLoopback(bool bEnable);
        
        /**
         设置监听音量
         
         @param volume 音量大小，取值（0, 100）。默认 100
         @attention 推流时可调用本 API 进行参数配置
         */
        ZEGO_API void SetLoopbackVolume(int volume);
        
        /**
         设置采集音量
         
         @param volume 音量大小，取值（0, 100）。默认 100
         @attention InitSDK成功之后调用
         */
        ZEGO_API void SetCaptureVolume(int volume);
        
        /**
         混音开关
         
         @param bEnable true 启用混音输入，false 关闭混音输入。默认 false
         @return true 成功，false 失败
         */
        ZEGO_API bool EnableAux(bool bEnable);
        
        /**
         混音静音开关
         
         @param bMute true: aux 输入播放静音，false: 不静音。默认 false
         @return true 成功，false 失败
         */
        ZEGO_API bool MuteAux(bool bMute);
        
        /**
         获取当前采集的音量
         
         @return 当前采集音量大小
         */
        ZEGO_API float GetCaptureSoundLevel();
        
        /**
         设置音频前处理函数
         
         @param prep 前处理函数指针
         */
        ZEGO_API void SetAudioPrep(void(*prep)(const short* inData, int inSamples, int sampleRate, short *outData));
        
        /**
         设置音频前处理函数
         
         @param prep 前处理函数指针
         @param set 预处理的采样率等参数设置
         */
        ZEGO_API void SetAudioPrep2(AVE::OnPrepCallback prep, const AVE::ExtPrepSet& set);
        
        /**
         设置延迟模式
         
         @param mode 延迟模式，默认 ZEGO_LATENCY_MODE_NORMAL
         @attention 确保在推流前调用
         */
        ZEGO_API void SetLatencyMode(AV::ZegoAVAPILatencyMode mode);
        
        /**
         设置混音音量
         
         @param volume 0~100
         */
        ZEGO_API void SetAuxVolume(int volume);
        
        /**
         是否开启离散音频包发送
         
         @param bEnable true 开启，此时关闭麦克风后，不会发送静音包；false 关闭，此时关闭麦克风后会发送静音包
         @attention 确保在推流前调用，只有纯 UDP 方案才可以调用此接口
         */
        ZEGO_API void EnableDTX(bool bEnable);

        /**
         是否开启语音活动检测

         @param enable true 开启; false 关闭, 默认关闭
         @attention 确保在推流前调用，只有纯 UDP 方案才可以调用此接口
         */
        ZEGO_API void EnableVAD(bool bEnable);

        /**
        OnPublishStateUpdate回调推流失败时，可以调用此函数再次进行推流
        @return true 调用推流成功，false 调用失败
        */
        ZEGO_API bool RestartPublishStream();
        
        
        /**
         设置是否开启音频流量控制

         @param bEnable true 开启; false 关闭
         */
        ZEGO_API void EnableAudioTrafficControl(bool bEnable);
    }
}
#endif /* AudioRoom_Publisher_h */

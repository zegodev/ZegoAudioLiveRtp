//
//  AudioRoom-Player.h
//  zegoaudioroom
//
//  Copyright © 2017年 ZEGO. All rights reserved.
//

#ifndef AudioRoom_Player_h
#define AudioRoom_Player_h

#include "./AudioRoomDefines.h"
#include "./AudioRoomCallback-Player.h"

namespace ZEGO
{
    namespace AUDIOROOM
    {
		/**
		开始播放流

		@param pszStreamID 播放流流 ID 
		@attention 设置手动播放时有效
		@return true 成功，false 失败
		*/
        ZEGO_API bool StartPlay(const char *pszStreamID);

		/**
		停止播放流

		@param pszStreamID 流 ID
		@attention 设置手动播放时有效
		*/
        ZEGO_API void StopPlay(const char *pszStreamID);

        /**
         获取 SDK 支持的最大同时播放流数
         
         @return 最大支持播放流数
         */
        ZEGO_API int GetMaxPlayChannelCount();
        
        /**
         设置直播观众相关信息通知的回调
         
         @param pCB 回调对象指针
         @return true 成功，false 失败
         */
        ZEGO_API bool SetAudioLivePlayerCallback(IAudioLivePlayerCallback *pCB);
        
        /**
         （声音输出）静音开关
         
         @param bEnable true 不静音，false 静音。默认 true
         @return true 成功，false 失败
         @attention 设置为关闭后，默认扬声器和耳机均无声音输出
         */
        ZEGO_API bool EnableSpeaker(bool bEnable);
       
        /**
         默认扬声器开关
         
         @param bOn true 打开，false 关闭。默认 true
         @return true 成功，false 失败
         @attention 设置为关闭后，扬声器无声音，耳机仍有声音输出
         */
        ZEGO_API bool SetBuiltInSpeakerOn(bool bOn);
        
        /**
         设置播放音量
         
         @param volume 音量取值范围为(0, 100)，数值越大，音量越大。默认 100
         @attention 直播时通过此 API 软件调整音量
         */
        ZEGO_API bool SetPlayVolume(int volume);
        
        /**
         获取当前播放视频的音量
         
         @param pszStreamID 播放流 ID
         @return 视频的音量值
         @attention 直播时通过此 API 获取当前音量。
         */
        ZEGO_API float GetSoundLevel(const char* pszStreamID);
        
        /**
         音频录制回调开关
         
         @param uMask 启用音频源选择，参考 ZegoAVAPIAudioRecordMask
         @param nSampleRate 采样率 8000, 16000, 22050, 24000, 32000, 44100, 48000
         @return true 成功，false 失败
         */
        ZEGO_API bool EnableSelectedAudioRecord(unsigned int uMask, int nSampleRate = 44100);
        
        /**
         设置音频录制回调
         
         @param pCB 回调实现实例
         @return true 成功，false 失败
         */
        ZEGO_API bool SetAudioRecordCallback(AV::IZegoAudioRecordCallback* pCB);
        
        /**
         音频录制回调开关
         
         @param bEnable true 开启，false 不开启
         @param nSampleRate 采样率
         @return true 成功，false 失败
         @warning 已废弃，请使用 EnableSelectedAudioRecord
         */
        ZEGO_API bool EnableAudioRecord(bool bEnable, int nSampleRate = 44100);

        /**
        onPlayStateUpdate返回拉流失败时，可以尝试再次拉流

        @param streamID 重新拉流流ID
        @return true 调用成功，false 调用失败
        */
        ZEGO_API bool RestartPlayStream(const char *streamID);

    }
}
#endif /* AudioRoom_Player_h */

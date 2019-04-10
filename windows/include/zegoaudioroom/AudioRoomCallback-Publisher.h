//
//  AudioRoomCallback-Publisher.h
//  zegoaudioroom
//
//  Copyright © 2017年 ZEGO. All rights reserved.
//

#ifndef AudioRoomCallback_Publisher_h
#define AudioRoomCallback_Publisher_h

#include "./AudioRoomDefines.h"

namespace ZEGO
{
    namespace AUDIOROOM
    {
        class IAudioLivePublisherCallback
        {
        public:
            /**
             推流状态更新
             
             @param stateCode 状态码
             @param pszStreamID 流 ID
             @param oStreamInfo 推流信息
             */
            virtual void OnPublishStateUpdate(int stateCode, const char *pszStreamID, const ZegoPublishingStreamInfo& oStreamInfo) = 0;
            
			/**
			推流质量更新

			@param pszStreamID 流 ID
			@param publishQuality ZegoPublishQuality 对象，内含各项推流质量数据
			*/
			virtual void OnPublishQualityUpdate(const char* pszStreamID, ZegoPublishQuality publishQuality) {}

			/**
			混音数据输入回调

			@param pData 混音数据
			<p><b>注意：</b>
			1. 每次必须返回 20ms 时长的音频数据；<br>
			2. 最大支持 48k 采样率、双声道、16位深的 PCM 音频数据；<br>
			3. 实际数据长度应根据当前音频数据的采样率及声道数决定；<br>
			4. 为确保混音效果，请不要在此 API 中执行耗时操作</p>
			20ms音频数据长度计算如下：
			长度 = 采样率 * 20 / 1000 * 位深字节数 * 通道数 位深字节数固定为2
			例如: 44.1K采样率双声道20ms数据的长度*pDataLen为：
			*pDataLen = 44100 * 20 / 1000 * 2 * 2 = 3528
			@param pDataLen 期望的数据长度（以 44.1k 采样率、双声道、16bit 位深、20ms 时长计算得来）
			@param pSampleRate 混音数据采样率，支持16k、32k、44.1k、48k
			@param pNumChannels 混音数据声道数，支持1、2
			@attention 用户调用该 API 将混音数据传递给 SDK
			@note 混音数据 bit depth 必须为 16
			*/
            virtual void OnAuxCallback(unsigned char *pData, int *pDataLen, int *pSampleRate, int *pNumChannels) {}
            
			/// \breif 转推CDN状态通知
            /// \param streamID 流ID
            /// \param statesInfo 转推CDN状态信息列表
            /// \param stateCount 状态信息列表个数
            virtual void OnRelayCDNStateUpdate(const char *streamID, AV::ZegoStreamRelayCDNInfo* statesInfo, unsigned int statesInfoCount) {}
			
            virtual ~IAudioLivePublisherCallback() {}
        };
    }
}

#endif /* AudioRoomCallback_Publisher_h */

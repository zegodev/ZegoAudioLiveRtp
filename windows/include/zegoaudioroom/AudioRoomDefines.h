//
//  AudioRoomDefines.h
//  zegoaudioroom
//
//  Copyright © 2017年 ZEGO. All rights reserved.
//

#ifndef AudioRoomDefines_h
#define AudioRoomDefines_h

#include "AVDefines.h"
#include "RoomDefines.h"

namespace ZEGO
{
    namespace AUDIOROOM
    {
        using namespace COMMON;
        using COMMON::ZEGONetType;

        using COMMON::ZegoStreamInfo;

        using COMMON::ZegoStreamUpdateType;

        using COMMON::ZegoPublishFlag;

        using COMMON::ZegoPublishingStreamInfo;

		struct ZegoPublishQuality
		{
			double fps;             ///< 视频帧率
			double kbps;            ///< 视频码率(kb/s)
			double akbps;           ///< 音频码率(kb/s)
			int rtt;                ///< 延时(ms)
			int pktLostRate;        ///< 丢包率(0~255)

			int quality;            ///< 质量(0~3)
		};

		struct ZegoPlayQuality
		{
			double fps;             ///< 视频帧率
			double kbps;            ///< 视频码率(kb/s)
			double akbps;           ///< 音频码率(kb/s)
			double audioBreakRate;  ///< 音频卡顿率(次/min)
			int rtt;                ///< 延时(ms)
			int pktLostRate;        ///< 丢包率(0~255)

			int quality;            ///< 质量(0~3)
		};
    }
}

#endif /* AudioRoomDefines_h */

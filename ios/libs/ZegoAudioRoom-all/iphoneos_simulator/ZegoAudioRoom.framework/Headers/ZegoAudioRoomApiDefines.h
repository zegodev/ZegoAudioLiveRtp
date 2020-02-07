//
//  ZegoAudioRoomApiDefines.h
//  ZegoAudioRoom
//
//  Created by Strong on 2017/3/15.
//  Copyright © 2017年 Zego. All rights reserved.
//

#ifndef ZegoAudioRoomApiDefines_h
#define ZegoAudioRoomApiDefines_h

#import "zego-api-defines-oc.h"

#ifndef ZEGO_EXTERN
#ifdef __cplusplus
#define ZEGO_EXTERN     extern "C"
#else
#define ZEGO_EXTERN     extern
#endif
#endif

/** 音频流类型 */
typedef enum : NSUInteger {
    /** 音频流新增 */
    ZEGO_AUDIO_STREAM_ADD,
    /** 音频流删除 */
    ZEGO_AUDIO_STREAM_DELETE,
} ZegoAudioStreamType;

/** 音频直播事件 */
typedef enum : NSUInteger {
    /** 音频拉流开始重试 */
    Audio_Play_BeginRetry = 1,
    /** 音频拉流重试成功 */
    Audio_Play_RetrySuccess = 2,
    
    /** 音频推流开始重试 */
    Audio_Publish_BeginRetry = 3,
    /** 音频推流重试成功 */
    Audio_Publish_RetrySuccess = 4,
    
    /** 拉流临时中断 */
    Audio_Play_TempDisconnected = 5,
    /** 推流临时中断 */
    Audio_Publish_TempDisconnected = 6,

    /** 音频卡顿开始 */
    Audio_Play_Break = 9,
    /** 音频卡顿结束 */
    Audio_Play_BreakEnd = 10,
} ZegoAudioLiveEvent;

/** 音频流 */
@interface ZegoAudioStream : NSObject

/** 用户 ID */
@property (nonatomic, copy) NSString *userID;
/** 用户名 */
@property (nonatomic, copy) NSString *userName;
/** 流 ID */
@property (nonatomic, copy) NSString *streamID;
/** 流附加信息 */
@property (nonatomic, copy) NSString *extraInfo;
/** 流在房间中的序号 */
@property (nonatomic, assign) int streamNID;

@end

/** AudioSession相关配置信息的key, 值为 NSString */
ZEGO_EXTERN NSString *const kZegoAudioRoomConfigKeepAudioSesionActive;

#ifndef ZegoLiveRoomApiDefines_IM_h

typedef enum
{
    /** 全量更新 */
    ZEGO_UPDATE_TOTAL = 1,
    /** 增量更新 */
    ZEGO_UPDATE_INCREASE,
}ZegoUserUpdateType;

typedef enum
{
    /** 新增 */
    ZEGO_USER_ADD  = 1,
    /** 删除 */
    ZEGO_USER_DELETE,
}ZegoUserUpdateFlag;

/** 用户状态 */
@interface ZegoUserState : NSObject

/** 用户 ID */
@property (nonatomic, copy) NSString *userID;
/** 用户名 */
@property (nonatomic, copy) NSString *userName;
/** 用户更新属性 */
@property (nonatomic, assign) ZegoUserUpdateFlag updateFlag;
/** 角色 */
@property (nonatomic, assign) int role;

@end

#endif

#endif /* ZegoAudioRoomApiDefines_h */

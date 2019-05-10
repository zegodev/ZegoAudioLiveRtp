//
//  ZegoAVKitManager.h
//  LiveDemo
//
//  Copyright © 2015年 Zego. All rights reserved.
//

#pragma once

#import <ZegoAudioRoom/ZegoAudioRoom.h>

typedef enum : NSUInteger {
    ZegoAppTypeUDP      = 0,    // 国内版
    ZegoAppTypeI18N     = 1,    // 国际版
    ZegoAppTypeCustom   = 2,    // 用户自定义
} ZegoAppType;

@interface ZegoAudioLive : NSObject

+ (ZegoAudioRoomApi *)api;
+ (void)releaseApi;

+ (void)setCustomAppID:(uint32_t)appid sign:(NSString *)sign;
+ (uint32_t)appID;

+ (void)setUsingTestEnv:(bool)testEnv;
+ (bool)usingTestEnv;

+ (bool)usingAlphaEnv;

+ (bool)manualPublish;
+ (void)setUsingManualPublish:(bool)manual;

+ (bool)enableMediaPlayer;
+ (void)setEnableMediaPlayer:(bool)enable;

+ (bool)enableAudioTrafficCtrl;
+ (void)setEnableAudioTrafficCtrl:(bool)enable;

+ (void)setUsingInternationDomain:(bool)bUse;
+ (bool)usingInternationDomain;

+ (void)setAppType:(ZegoAppType)type;
+ (ZegoAppType)appType;

+ (NSString *)customAppSign;

+ (NSData *)zegoAppSignFromServer;

+ (void)setBizTypeForCustomAppID:(int)bizType;

@end


//
//  ZegoAVKitManager.m
//  LiveDemo
//
//  Copyright © 2015年 Zego. All rights reserved.
//

#include "ZegoAVKitManager.h"
#import "ZegoSettings.h"

NSString *kZegoDemoAppTypeKey           = @"apptype";
NSString *kZegoDemoAppIDKey             = @"appid";
NSString *kZegoDemoAppSignKey           = @"appsign";
NSString *kZegoDemoAppBizType           = @"biztype";
NSString *kZegoDemoTestEnvKey           = @"test-env";

static ZegoAudioRoomApi *g_ZegoApi = nil;

// Demo 默认版本为 UDP
ZegoAppType g_appType = ZegoAppTypeUDP;

BOOL g_useTestEnv = NO;
BOOL g_useAlphaEnv = NO;

BOOL g_enableMediaPlayer = NO;
BOOL g_enableAudioTrafficCtrl = NO;
BOOL g_useManual = NO;

BOOL g_useInternationDomain = NO;

static Byte toByte(NSString* c);
static NSData* ConvertStringToSign(NSString* strSign);

@interface ZegoAudioLive () <ZegoAVEngineDelegate>

+ (NSData *)zegoAppSignFromServer;

@end

@implementation ZegoAudioLive

+ (ZegoAudioRoomApi *)api
{
    if (g_ZegoApi == nil)
    {
        /*if ([self appType] == ZegoAppTypeCustom) {
            //int bizType = (int)[[NSUserDefaults standardUserDefaults] integerForKey:kZegoDemoAppBizType];
            //[ZegoAudioRoomApi setBusinessType:bizType];
        }*/
//        [ZegoAudioRoomApi setBusinessType:0];
        
        g_useTestEnv = [self usingTestEnv];
        // 测试环境开关
        [ZegoAudioRoomApi setUseTestEnv:g_useTestEnv];
        [ZegoAudioRoomApi setBusinessType:0];
#ifdef DEBUG
        // 调试信息开关
        [ZegoAudioRoomApi setVerbose:YES];
#endif
        
        // 设置 UserID 和 UserName
        [ZegoAudioRoomApi setUserID:[ZegoSettings sharedInstance].userID userName:[ZegoSettings sharedInstance].userName];
        
        uint32_t appID = [self appID];
        if (appID > 0) {    // 手动输入为空的情况下容错
            NSData *appSign = [self zegoAppSignFromServer];
            if (appSign) {
                g_ZegoApi = [[ZegoAudioRoomApi alloc] initWithAppID:appID appSignature:appSign];
            }
        }
        
        // 设置引擎代理
        [g_ZegoApi setAVEngineDelegate:self];
    
        // 设置手动直播
        [g_ZegoApi setManualPublish:g_useManual];
        
        // 设置低延迟模式
        [g_ZegoApi setLatencyMode:ZEGOAPI_LATENCY_MODE_LOW3];
    }
    
    return g_ZegoApi;
}

+ (void)releaseApi
{
    g_ZegoApi = nil;
}

+ (void)setCustomAppID:(uint32_t)appid sign:(NSString *)sign
{
    NSData *d = ConvertStringToSign(sign);
    
    if (d.length == 32 && appid != 0)
    {
//        g_appID = appid;
//        g_signKey = [[NSData alloc] initWithData:d];
        
        // 本地持久化
        NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
        [ud setObject:@(appid) forKey:kZegoDemoAppIDKey];
        [ud setObject:sign forKey:kZegoDemoAppSignKey];
        
        g_ZegoApi = nil;
    }
}

#warning 请提前在即构管理控制台获取 appID 与 appSign
#warning Demo 默认使用 UDP 模式，请填充该模式下的 appID 与 appSign
#warning appID 填写样式示例：1234567890
#warning appSign 填写样式示例：{0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x00,0x01}
+ (uint32_t)appID
{
    switch ([self appType]) {
        case ZegoAppTypeCustom:
        {
            NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
            uint32_t appID = [[ud objectForKey:kZegoDemoAppIDKey] unsignedIntValue];
            
            if (appID != 0) {
                return appID;
            } else {
                return 0;
            }
        }
            break;
        case ZegoAppTypeUDP:
            return ;  // 国内版
            break;
        case ZegoAppTypeI18N:
            return 100;  // 国际版

            break;
    }
}

+ (void)setUsingTestEnv:(bool)testEnv
{
    [self releaseApi];
    [[NSUserDefaults standardUserDefaults] setBool:testEnv forKey:kZegoDemoTestEnvKey];
    g_useTestEnv = testEnv;
    [ZegoAudioRoomApi setUseTestEnv:testEnv];
}

+ (bool)usingTestEnv
{
    return [[NSUserDefaults standardUserDefaults] boolForKey:kZegoDemoTestEnvKey];
}

+ (bool)usingAlphaEnv
{
    return g_useAlphaEnv;
}

+ (bool)enableMediaPlayer {
    return g_enableMediaPlayer;
}

+ (void)setEnableMediaPlayer:(bool)enable {
    if (g_enableMediaPlayer != enable) {
        g_enableMediaPlayer = enable;
    }
}

+ (bool)enableAudioTrafficCtrl {
    return g_enableAudioTrafficCtrl;
}

+ (void)setEnableAudioTrafficCtrl:(bool)enable {
    if (g_enableAudioTrafficCtrl != enable) {
        g_enableAudioTrafficCtrl = enable;
    }
}

+ (void)setUsingManualPublish:(bool)manual
{
    if (g_useManual != manual)
    {
        g_useManual = manual;
        
        if (g_ZegoApi)
            [g_ZegoApi setManualPublish:manual];
    }
}

+ (bool)manualPublish
{
    return g_useManual;
}

+ (void)setUsingInternationDomain:(bool)bUse
{
    if (g_useInternationDomain == bUse)
        return;
    
    g_useInternationDomain = bUse;
}

+ (bool)usingInternationDomain
{
    return g_useInternationDomain;
}

+ (void)setAppType:(ZegoAppType)type {
    if (g_appType == type)
        return;
    
    // 本地持久化
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    [ud setInteger:type forKey:kZegoDemoAppTypeKey];
    
    g_appType = type;
    
    [self releaseApi];
    
    // 临时兼容 SDK 的 Bug，立即初始化 api 对象
    if ([self api] == nil) {
        [self api];
    }
}

+ (ZegoAppType)appType {
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    NSUInteger type = [ud integerForKey:kZegoDemoAppTypeKey];
    g_appType = (ZegoAppType)type;
    return (ZegoAppType)type;
}

+ (NSString *)customAppSign {
    ZegoAppType type = [self appType];
    
    if (type == ZegoAppTypeCustom) {
        NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
        NSString *appSign = [ud objectForKey:kZegoDemoAppSignKey];
        return appSign;
    } else {
        return nil;
    }
}

#pragma mark - private

#warning 请提前在即构管理控制台获取 appID 与 appSign
#warning Demo 默认使用 UDP 模式，请填充该模式下的 appID 与 appSign
#warning appID 填写样式示例：1234567890
#warning appSign 填写样式示例：{0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x00,0x01}
+ (NSData *)zegoAppSignFromServer
{
   
    ZegoAppType type = [self appType];
    
    if (type == ZegoAppTypeUDP)
    {

        Byte signkey[] = ;

        return [NSData dataWithBytes:signkey length:32];
    }
    else if (type == ZegoAppTypeI18N)
    {

        Byte signkey[] = {0x00};

        return [NSData dataWithBytes:signkey length:32];
    }
    else
    {
        // 自定义模式下从本地持久化文件中加载
        NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
        NSString *appSign = [ud objectForKey:kZegoDemoAppSignKey];
        if (appSign) {
            return ConvertStringToSign(appSign);
        } else {
            return nil;
        }
    }
}

+ (void)setBizTypeForCustomAppID:(int)bizType {
    [[NSUserDefaults standardUserDefaults] setInteger:bizType forKey:kZegoDemoAppBizType];
}

#pragma mark ZegoAVEngineDelegate
- (void)onAVEngineStop
{
    NSLog(@"onAVEngineStop");
}

@end

Byte toByte(NSString* c)
{
    NSString *str = @"0123456789abcdef";
    Byte b = [str rangeOfString:c].location;
    return b;
}

NSData* ConvertStringToSign(NSString* strSign)
{
    if(strSign == nil || strSign.length == 0)
        return nil;
    strSign = [strSign lowercaseString];
    strSign = [strSign stringByReplacingOccurrencesOfString:@" " withString:@""];
    strSign = [strSign stringByReplacingOccurrencesOfString:@"0x" withString:@""];
    NSArray* szStr = [strSign componentsSeparatedByString:@","];
    int nLen = (int)[szStr count];
    Byte szSign[32];
    for(int i = 0; i < nLen; i++)
    {
        NSString *strTmp = [szStr objectAtIndex:i];
        if(strTmp.length == 1)
            szSign[i] = toByte(strTmp);
        else
        {
            szSign[i] = toByte([strTmp substringWithRange:NSMakeRange(0, 1)]) << 4 | toByte([strTmp substringWithRange:NSMakeRange(1, 1)]);
        }
    }
    
    NSData *sign = [NSData dataWithBytes:szSign length:32];
    return sign;
}



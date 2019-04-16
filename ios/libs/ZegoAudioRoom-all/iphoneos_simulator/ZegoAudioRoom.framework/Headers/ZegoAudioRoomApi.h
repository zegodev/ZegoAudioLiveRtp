//
//  ZegoAudioRoomApi.h
//  ZegoAudioRoom
//
//  Created by Strong on 2017/3/15.
//  Copyright © 2017年 Zego. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZegoAudioRoomApiDefines.h"
#import "ZegoAudioRoomApiDefines-IM.h"

@protocol ZegoAudioRoomDelegate;
@protocol ZegoAudioLiveEventDelegate;
@protocol ZegoAudioDeviceEventDelegate;
@protocol ZegoAVEngineDelegate;

typedef void(^ZegoAudioRoomBlock)(int errorCode);
typedef void(^ZegoCustomCommandBlock)(int errorCode, NSString *roomID);

@interface ZegoAudioRoomApi : NSObject

+ (NSString *)version;
+ (NSString *)version2;

/**
 是否启用测试环境
 
 @param useTestEnv 是否使用测试环境
 */
+ (void)setUseTestEnv:(bool)useTestEnv;

/**
 调试信息开关
 
 @param bOnVerbose 是否使用测试环境
 @discussion 建议在调试阶段打开此开关，方便调试。默认关闭
 */
+ (void)setVerbose:(bool)bOnVerbose;

/**
 设置业务类型
 
 @param type 业务类型。默认为2 (实时语音类型), 可以取值0 (直播类型)
 @discussion 确保在创建接口对象前调用
 */
+ (void)setBusinessType:(int)type;

/**
 触发日志上报
 
 @discussion 在初始化 SDK 成功后调用
 */
+ (void)uploadLog;

/**
 设置用户ID及用户名
 
 @param userID 用户ID
 @param userName 用户名
 @return 设置结果
 */
+ (bool)setUserID:(NSString *)userID userName:(NSString *)userName;

/**
 初始化SDK
 
 @param appID Zego派发的数字ID, 各个开发者的唯一标识
 @param appSignature Zego派发的签名, 用来校验对应appID的合法性
 @return api 实例，nil 表示初始化失败
 */
- (instancetype)initWithAppID:(unsigned int)appID appSignature:(NSData*)appSignature;

/**
 设置房间的 delegate
 
 @param roomDelegate 房间 delegate
 */
- (void)setAudioRoomDelegate:(id<ZegoAudioRoomDelegate>)roomDelegate;

/**
 设置是否需要手动发布直播
 
 @param manual 是否手动发布直播，YES：手动发布直播，NO：进入房间后自动发布直播。默认为 NO
 @discussion 必须在登录房间前调用
 */
- (void)setManualPublish:(bool)manual;


/**
 设置是否需要手动播放

 @param manual 是否手动播放，YES：手动播放，NO：收到流更新后自动播放。默认为 NO
 @discussion 必须在登录房间前调用
 */
- (void)setManualPlay:(bool)manual;

/**
 登录房间
 
 @param roomID 房间唯一ID
 @param block 房间登录结果回调
 @return 调用登录房间的结果
 */
- (bool)loginRoom:(NSString *)roomID completionBlock:(ZegoAudioRoomBlock)block;

/**
 退出房间
 
 @return true 成功，false 失败
 @discussion 会停止所有的推拉流
 */
- (bool)logoutRoom;

/**
 设置直播事件代理对象
 
 @param liveEventDelegate 遵循 ZegoAudioLiveEventDelegate 协议的代理对象
 @discussion 设置代理对象成功后，在 [ZegoAudioLiveEventDelegate -zego_onLiveEvent:info:] 中获取直播状态，状态参考 ZegoLiveEvent 定义。未设置代理对象，或对象设置错误，可能导致无法正常收到相关回调
 */
- (void)setAudioLiveEventDelegate:(id<ZegoAudioLiveEventDelegate>)liveEventDelegate;

#if TARGET_OS_IPHONE

/**
 设置音视频设备错误回调代理对象
 
 @param deviceEventDelegate 遵循 ZegoAudioDeviceEventDelegate 协议的代理对象
 @discussion 开发者获取音视频设备错误，需要先设置此代理对象。未设置代理对象，或对象设置错误，可能导致无法正常收到相关回调
 */
- (void)setAudioDeviceEventDelegate:(id<ZegoAudioDeviceEventDelegate>)deviceEventDelegate;

/**
 暂停模块
 
 @discussion 用于需要暂停指定模块的场合，例如来电时暂定音频模块。暂停指定模块后，注意在合适时机下恢复模块
 */
- (void)pauseAudioModule;

/**
 恢复模块
 
 @discussion 用于需要恢复指定模块的场合，例如来电结束后恢复音频模块。暂停指定模块后，注意在合适时机下恢复模块
 */
- (void)resumeAudioModule;

/**
 设置是否允许SDK使用麦克风设备
 
 @param enable YES 表示允许使用麦克风，NO 表示禁止使用麦克风，此时如果SDK在占用麦克风则会立即释放。
 @return YES 调用成功 NO 调用失败
 @discussion 调用时机为引擎创建后的任意时刻。
 @note 接口由于涉及对设备的操作，极为耗时，不建议随便调用，只在真正需要让出麦克风给其他应用的时候才调用
 */
- (BOOL)enableMicDevice:(BOOL)enable;

#endif

/**
 Engine停止回调
 
 @param engineDelegate engine Delegate
 */
- (void)setAVEngineDelegate:(id<ZegoAVEngineDelegate>)engineDelegate;

/**
 设置配置信息
 
 @param config 配置信息
 @discussion 必须在Init SDK前调用
 */
+ (void)setConfig:(NSString *)config;

/**
 设置用户进入/退出房间是否通知其他用户
 
 @param userStateUpdate 是否需要通知其他用户
 @discussion 默认不通知
 */
- (void)setUserStateUpdate:(bool)userStateUpdate;

/**
 发送自定义信令
 
 @param memberList 发送对象列表
 @param content 消息内容
 @param block 消息发送结果
 @return true 成功，false 失败
 @discussion 信令内容由用户自定义。发送结果通过 block 回调
 */
- (bool)sendCustomCommand:(NSArray<ZegoUser*> *)memberList content:(NSString *)content completion:(ZegoCustomCommandBlock)block;

@end

@protocol ZegoAudioRoomDelegate <NSObject>

@optional

/**
 用户被踢出聊天室
 
 @param reason 原因，16777219 表示该账户多点登录被踢出，16777220 表示该账户是被手动踢出，16777221 表示房间会话错误被踢出。
 @param roomID 房间 ID
 @discussion 可在该回调中处理用户被踢出房间后的下一步处理（例如报错、重新登录提示等）
 */
- (void)onKickOut:(int)reason roomID:(NSString *)roomID;

/**
 与 server 断开通知
 
 @param errorCode 错误码，0 表示无错误
 @param roomID 房间 ID
 @discussion 建议开发者在此通知中进行重新登录、推/拉流、报错、友好性提示等其他恢复逻辑。与 server 断开连接后，SDK 会进行重试，重试失败抛出此错误。请注意，此时 SDK 与服务器的所有连接均会断开
 */
- (void)onDisconnect:(int)errorCode roomID:(NSString *)roomID;

/**
 流更新消息，此时sdk会开始拉流/停止拉流
 
 @param type 增加/删除流
 @param stream 流信息
 */
- (void)onStreamUpdated:(ZegoAudioStreamType)type stream:(ZegoAudioStream*)stream;

/**
 流附加信息更新
 
 @param streamList 附加信息更新的流列表
 @param roomID 房间 ID
 @discussion 主播推流成功后调用 [ZegoAudioRoomApi (Publisher) -updateStreamExtraInfo:] 更新附加信息，在此回调中通知房间内其他成员。调用 [ZegoAudioRoomApi (Publisher) -updateStreamExtraInfo:] 更新信息的调用方，不会收到此回调
 */
- (void)onStreamExtraInfoUpdated:(NSArray<ZegoAudioStream *> *)streamList roomID:(NSString *)roomID;

/**
 房间成员更新回调
 
 @param userList 成员更新列表
 @param type  更新类型(增量，全量)
 @discussion 当房间成员变化（例如用户进入、退出房间）时，会触发此通知
 */
- (void)onUserUpdate:(NSArray<ZegoUserState *> *)userList updateType:(ZegoUserUpdateType)type;

/**
 收到自定义消息
 
 @param fromUserID 消息来源 UserID
 @param fromUserName 消息来源 UserName
 @param content 消息内容
 @param roomID 房间 ID
 @discussion 调用 [ZegoLiveRoomApi -sendCustomCommand:content:completion:] 发送自定义消息后，消息列表中的用户会收到此通知
 */
- (void)onReceiveCustomCommand:(NSString *)fromUserID userName:(NSString *)fromUserName content:(NSString*)content roomID:(NSString *)roomID;

@end

@protocol ZegoAudioLiveEventDelegate <NSObject>

/**
 直播事件回调
 
 @param event 直播事件状态，参考 ZegoLiveEvent 定义
 @param info 信息，目前为空
 @discussion 调用 [ZegoLiveRoomApi -setLiveEventDelegate] 设置直播事件代理对象后，在此回调中获取直播事件状态
 */
- (void)zego_onAudioLiveEvent:(ZegoAudioLiveEvent)event info:(NSDictionary<NSString*, NSString*>*)info;

@end

@protocol ZegoAudioDeviceEventDelegate <NSObject>

/**
 设备事件回调
 
 @param deviceName 设备名，取值 "audio_device"
 @param errorCode 错误码。
 @discussion 调用 [ZegoLiveRoomApi -setDeviceEventDelegate] 设置设备事件代理对象后，在此回调中获取设备状态或错
 */
- (void)zego_onAudioDevice:(NSString *)deviceName error:(int)errorCode;

@end

@protocol ZegoAVEngineDelegate <NSObject>

/**
 音视频引擎启动时回调
 */
- (void)onAVEngineStart;

/**
 音视频引擎停止时回调
 */
- (void)onAVEngineStop;

@end

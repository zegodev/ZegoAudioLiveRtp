//
//  ZegoAudioRoomApi-IM.h
//  ZegoAudioRoom
//
//  Created by Strong on 2017/7/25.
//  Copyright © 2017年 Zego. All rights reserved.
//

#import "ZegoAudioRoomApiDefines-IM.h"

@protocol ZegoAudioIMDelegate;

typedef void(^ZegoRoomMessageCompletion)(int errorCode, NSString *roomId, unsigned long long messageId);
typedef void(^ZegoBigRoomMessageCompletion)(int errorCode, NSString *roomId, NSString *messageId);

@interface ZegoAudioRoomApi (IM)

/**
 设置 IM 代理对象
 
 @param imDelegate 遵循 ZegoAudioIMDelegate 协议的代理对象
 @discussion 使用 IM 功能，初始化相关视图控制器时需要设置代理对象。未设置代理对象，或对象设置错误，可能导致无法正常收到相关回调
 */
- (void)setAudioIMDelegate:(id<ZegoAudioIMDelegate>)imDelegate;

/**
 房间发送广播消息
 
 @param content 消息内容, 不超过 512 字节
 @param type 消息类型，可以自定义
 @param category 消息分类，可以自定义
 @param priority 消息优先级
 @param completionBlock 消息发送结果，回调 server 下发的 messageId
 @return true 成功，false 失败
 @discussion 实现点赞主播、评论、送礼物等 IM 功能时，需要调用本 API
 @deprecated 请使用 sendRoomMessage:type:category:completion
 */
- (bool)sendRoomMessage:(NSString *)content type:(ZegoMessageType)type category:(ZegoMessageCategory)category priority:(ZegoMessagePriority)priority completion:(ZegoRoomMessageCompletion)completionBlock;

/**
 房间发送广播消息
 
 @param content 消息内容, 不超过 512 字节
 @param type 消息类型，可以自定义
 @param category 消息分类，可以自定义
 @param completionBlock 消息发送结果，回调 server 下发的 messageId
 @return true 成功，false 失败
 @discussion 实现点赞主播、评论、送礼物等 IM 功能时，需要调用本 API
 */
- (bool)sendRoomMessage:(NSString *)content type:(ZegoMessageType)type category:(ZegoMessageCategory)category completion:(ZegoRoomMessageCompletion)completionBlock;

/**
 发送房间内不可靠信道的广播消息，用于高并发情景下，服务端会根据高并发情况有策略的丢弃一些消息。
 
 @param content 消息内容, 不超过 512 字节
 @param type 消息类型，可以自定义
 @param category 消息分类，可以自定义
 @param completionBlock 消息发送结果，回调 server 下发的 messageId
 @return true 成功，false 失败
 */
- (bool)sendBigRoomMessage:(NSString *)content type:(ZegoMessageType)type category:(ZegoMessageCategory)category completion:(ZegoBigRoomMessageCompletion)completionBlock;


@end

@protocol ZegoAudioIMDelegate <NSObject>

@optional

/**
 收到房间的广播消息
 
 @param roomId 房间 Id
 @param messageList 消息列表，包括消息内容，消息分类，消息类型，发送者等信息
 @discussion 调用 [ZegoAudioRoomApi (IM) -sendRoomMessage:type:category:priority:completion:] 发送消息，会触发此通知
 */
- (void)onRecvAudioRoomMessage:(NSString *)roomId messageList:(NSArray<ZegoRoomMessage*> *)messageList;

/**
 收到在线人数更新
 
 @param onlineCount 在线人数
 @param roomId 房间 Id
 */
- (void)onUpdateOnlineCount:(int)onlineCount room:(NSString *)roomId;

/**
 收到房间的不可靠广播消息
 
 @param roomId 房间 Id
 @param messageList 消息列表，包括消息内容，消息分类，消息类型，发送者等信息
 @discussion 调用 [ZegoAudioRoomApi (IM) -sendBigRoomMessage:type:category:completion:] 发送消息，会触发此通知
 */
- (void)onRecvBigAudioRoomMessage:(NSString *)roomId messageList:(NSArray<ZegoBigRoomMessage*> *)messageList;

@end

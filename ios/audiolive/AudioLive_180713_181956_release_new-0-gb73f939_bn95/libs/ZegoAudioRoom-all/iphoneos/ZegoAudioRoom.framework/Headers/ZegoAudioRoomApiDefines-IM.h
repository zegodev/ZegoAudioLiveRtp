//
//  ZegoAudioRoomDefines-IM.h
//  ZegoAudioRoom
//
//  Created by Strong on 2017/7/25.
//  Copyright © 2017年 Zego. All rights reserved.
//

#ifndef ZegoAudioRoomApiDefines_IM_h
#define ZegoAudioRoomApiDefines_IM_h

#ifndef ZegoLiveRoomApiDefines_IM_h

/** 消息类型 */
typedef enum
{
    /** 文字 */
    ZEGO_TEXT = 1,
    /** 图片 */
    ZEGO_PICTURE,
    /** 文件 */
    ZEGO_FILE,
    /** 其他 */
    ZEGO_OTHER_TYPE = 100,
} ZegoMessageType;

/** 消息优先级 */
typedef enum
{
    /** 默认优先级 */
    ZEGO_DEFAULT = 2,
    /** 高优先级 */
    ZEGO_HIGH = 3,
} ZegoMessagePriority;

/** 消息类别 */
typedef enum
{
    /** 聊天 */
    ZEGO_CHAT = 1,
    /** 系统 */
    ZEGO_SYSTEM,
    /** 点赞 */
    ZEGO_LIKE,
    /** 送礼物 */
    ZEGO_GIFT,
    /** 其他 */
    ZEGO_OTHER_CATEGORY = 100,
} ZegoMessageCategory;

/** 房间消息 */
@interface ZegoRoomMessage : NSObject

/** 来源用户 Id */
@property (nonatomic, copy) NSString *fromUserId;
/** 来源用户名 */
@property (nonatomic, copy) NSString *fromUserName;
/** 消息 Id */
@property (nonatomic, assign) unsigned long long messageId;
/** 内容 */
@property (nonatomic, copy) NSString *content;
/** 消息类型 */
@property (nonatomic, assign) ZegoMessageType type;
/** 消息优先级 */
@property (nonatomic, assign) ZegoMessagePriority priority;
/** 消息类别 */
@property (nonatomic, assign) ZegoMessageCategory category;

@end

/** 会话消息 */
@interface ZegoConversationMessage : NSObject

/** 来源用户 Id */
@property (nonatomic, copy) NSString *fromUserId;
/** 来源用户名 */
@property (nonatomic, copy) NSString *fromUserName;
/** 消息 Id */
@property (nonatomic, assign) unsigned long long messageId;
/** 内容 */
@property (nonatomic, copy) NSString *content;
/** 消息类型 */
@property (nonatomic, assign) ZegoMessageType type;
/** 发送时间 */
@property (nonatomic, assign) unsigned int sendTime;

@end

/** 房间不可靠消息 */
@interface ZegoBigRoomMessage : NSObject

/** 来源用户 Id */
@property (nonatomic, copy) NSString *fromUserId;
/** 来源用户名 */
@property (nonatomic, copy) NSString *fromUserName;
/** 消息 Id */
@property (nonatomic, copy) NSString *messageId;
/** 内容 */
@property (nonatomic, copy) NSString *content;
/** 消息类型 */
@property (nonatomic, assign) ZegoMessageType type;
/** 消息优先级 */
@property (nonatomic, assign) ZegoMessagePriority priority;
/** 消息类别 */
@property (nonatomic, assign) ZegoMessageCategory category;

@end

/** 用户 */
@interface ZegoUser : NSObject

/** 用户 Id */
@property (nonatomic, copy) NSString *userId;
/** 用户名 */
@property (nonatomic, copy) NSString *userName;

@end

/** 会话信息 */
@interface ZegoConversationInfo : NSObject

/** 会话名称 */
@property (nonatomic, copy) NSString *conversationName;
/** 会话创建者 Id */
@property (nonatomic, copy) NSString *creatorId;
/** 创建时间 */
@property (nonatomic, assign) unsigned int createTime;
/** 会话成员列表 */
@property (nonatomic, strong) NSArray<ZegoUser*>* members;

@end

#endif

#endif /* ZegoAudioRoomDefines_IM_h */

//
//  AudioRoom-Player.h
//  zegoaudioroom
//
//  Copyright © 2017年 ZEGO. All rights reserved.
//

#ifndef AudioRoom_IM_h
#define AudioRoom_IM_h

#include "./AudioRoomDefines-IM.h"
#include "./AudioRoomCallback-IM.h"

namespace ZEGO
{
    namespace AUDIOROOM
    {
        /**
        设置 IM 信息通知的回调对象

        @param pCB 回调对象指针
        @return true 成功，false 失败
        */
        ZEGO_API bool SetAudioIMCallback(IAudioIMCallback *pCB);

        /**
        发送聊天室消息

        @param type 消息类型
        @param category 消息分类
        @param priority 消息优先级
        @param messageContent 消息内容
        @return 消息 seq
        */
        ZEGO_API int SendRoomMessage(ROOM::ZegoMessageType type, ROOM::ZegoMessageCategory category, ROOM::ZegoMessagePriority priority, const char *messageContent);

        /**
        在房间中创建一个会话

        @param conversationName 会话名称
        @param memberList 会话成员列表
        @param memberCount 会话成员数量
        @return 消息 seq
        */
        ZEGO_API int CreateConversation(const char *conversationName, ROOM::ZegoUser *memberList, unsigned int memberCount);

        /**
        获取会话相关信息

        @param conversationId 会话 Id
        @return true 成功，false 失败
        */
        ZEGO_API bool GetConversationInfo(const char *conversationId);

        /**
        在会话中发送一条消息

        @param conversationId 会话 Id
        @param type 会话类型
        @param messageContent 消息内容
        @return 消息 seq
        */
        ZEGO_API int SendConversationMessage(const char *conversationId, ROOM::ZegoMessageType type, const char *messageContent);
    }
}

#endif /* AudioRoom_IM_h */

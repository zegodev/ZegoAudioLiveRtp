//
//  AudioRoomCallback.h
//  zegoaudioroom
//
//  Copyright © 2017年 ZEGO. All rights reserved.
//

#ifndef AudioRoomCallback_IM_h
#define AudioRoomCallback_IM_h

#include "./AudioRoomDefines.h"
#include "./AudioRoomDefines-IM.h"

namespace ZEGO
{
    namespace AUDIOROOM
    {
        class IAudioIMCallback
        {
        public:
            /**
            发送房间消息结果

            @param errorCode 错误码，0 表示无错误
            @param pszRoomID 房间 ID
            @param sendSeq 发送消息 seq
            @param messageId 消息 Id
            */
            virtual void OnSendRoomMessage(int errorCode, const char *pszRoomID, int sendSeq, unsigned long long messageId) {}

            /**
            创建会话消息结果

            @param errorCode 错误码，0 表示无错误
            @param pszRoomID 房间 ID
            @param sendSeq 消息 seq
            @param pszConversationID 会话 ID
            */
            virtual void OnCreateConversation(int errorCode, const char *pszRoomID, int sendSeq, const char *pszConversationID) {}

            /**
            获取会话信息结果

            @param errorCode 错误码，0 表示无错误
            @param pszRoomID 房间 ID
            @param pszConverID 会话 ID
            @param pConverInfo 会话信息
            @param pMemberList 会话成员列表
            @param memberCount 会话成员数量
            */
            virtual void OnGetConversationInfo(int errorCode, const char *pszRoomID, const char *pszConverID, ROOM::ZegoConverInfo *pConverInfo, ROOM::ZegoUser *pMemberList, unsigned int memberCount) {}

            /**
            发送会话消息

            @param errorCode 错误码，0 表示无错误
            @param pszRoomID 房间 ID
            @param pszConverID 会话 ID
            @param sendSeq 消息 seq
            @param messageId 消息 Id
            */
            virtual void OnSendConversationMessage(int errorCode, const char *pszRoomID, const char *pszConverID, int sendSeq, unsigned long long messageId) {}

            /**
            收到房间消息回调

            @param pMessageInfo 消息信息
            @param messageCount 消息内容
            @param pszRoomID 房间 ID
            */
            virtual void OnRecvRoomMessage(ROOM::ZegoRoomMessage *pMessageInfo, unsigned int messageCount, const char *pszRoomID) {}

            /**
            收到会话消息

            @param pMessageInfo 消息信息
            @param pszConversationID 会话 ID
            @param pszRoomID 房间 ID
            */
            virtual void OnRecvConversationMessage(ROOM::ZegoConversationMessage *pMessageInfo, const char *pszConversationID, const char *pszRoomID) {}

            virtual ~IAudioIMCallback() {}
        };
    }
}

#endif /*AudioRoomCallback_IM_h*/


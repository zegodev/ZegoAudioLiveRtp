//
//  AudioRoom.h
//  zegoaudioroom
//
//  Copyright © 2017年 ZEGO. All rights reserved.
//

#ifndef AudioRoom_h
#define AudioRoom_h

#include "./AudioRoomDefines.h"
#include "./AudioRoomCallback.h"

namespace ZEGO
{
    namespace AUDIOROOM
    {
        ZEGO_API const char* GetSDKVersion();
        ZEGO_API const char* GetSDKVersion2();
        ZEGO_API bool SetLogDir(const char* pszLogDir);
        ZEGO_API void UploadLog();
        ZEGO_API void SetVerbose(bool bVerbose);
        ZEGO_API void SetUseTestEnv(bool bTestEnv);
        ZEGO_API void SetPlatformInfo(const char* pszInfo);
                
        /**
         设置用户信息
         
         @param pszUserID 用户唯一 ID
         @param pszUserName 用户名字
         @return true 成功，false 失败
         */
        ZEGO_API bool SetUser(const char* pszUserID, const char* pszUserName);
        
        /**
         初始化 SDK
         
         @param uiAppID Zego 派发的数字 ID, 各个开发者的唯一标识
         @param pBufAppSignature Zego 派发的签名, 用来校验对应 appID 的合法性
         @param nSignatureSize 签名长度（字节）
         @return true 成功，false 失败
         @note 初始化 SDK 失败可能导致 SDK 功能异常
         */
        ZEGO_API bool InitSDK(unsigned int uiAppID, unsigned char* pBufAppSignature, int nSignatureSize);
        
        /**
         反初始化 SDK
         
         @return true 成功，false 失败
         */
        ZEGO_API bool UnInitSDK();
        
        /**
         设置登录房间成功后是否需要手动发布直播
         @param bManual 手动发布直播
         */
        ZEGO_API void SetManualPublish(bool bManual);
        
        /**
         设置登录房间成功后是否需要手动播放直播
         @param bManual 手动播放直播
         */
        ZEGO_API void SetManualPlay(bool bManual);

        /**
         设置用户进入/退出房间是否通知其他用户
         @param bUserStateUpdate 用户状态是否通知
         @note 在InitSDK之后调用
         */
        ZEGO_API void SetUserStateUpdate(bool bUserStateUpdate);
        
        /**
         设置直播房间相关信息通知的回调
         
         @param pCB 回调对象指针
         @return true 成功，false 失败
         */
        ZEGO_API bool SetAudioRoomCallback(IAudioRoomCallback *pCB);
        
        /**
         登录房间
         
         @param pszRoomID 房间 ID
         @param role 成员角色
         @param pszRoomName 房间名称
         @return true 成功，false 失败
         */
        ZEGO_API bool LoginRoom(const char* pszRoomID);
        
        /**
         退出房间
         
         @return 成功，false 失败
         @attention 退出登录后，等待 IRoomCallback::OnLogoutRoom 回调
         @note 退出房间会停止所有的推拉流
         */
        ZEGO_API bool LogoutRoom();
        
        /**
         设置直播事件回调
         
         @param pCB 回调对象指针
         */
        ZEGO_API void SetAudioLiveEventCallback(AV::IZegoLiveEventCallback *pCB);
        
        /**
         设置音频视频设备变化的回调
         
         @param pCB 回调对象指针
         */
        ZEGO_API void SetAudioDeviceStateCallback(AV::IZegoDeviceStateCallback *pCB);
        
        /**
         获取音频设备列表
         
         @param deviceType 设备类型
         @param device_count 设备数量
         @return 音频设备列表
         */
        ZEGO_API AV::DeviceInfo* GetAudioDeviceList(AV::AudioDeviceType deviceType, int& device_count);
        
        /**
         设置选用音频设备
         
         @param deviceType 设备类型
         @param pszDeviceID 设备 ID
         @return true 成功，false 失败
         */
        ZEGO_API bool SetAudioDevice(AV::AudioDeviceType deviceType, const char* pszDeviceID);
        
        /**
         释放设备列表
         
         @param parrDeviceList 设备列表
         */
        ZEGO_API void FreeDeviceList(AV::DeviceInfo* parrDeviceList);
        
        /**
         设置“音视频引擎状态通知”的回调
         
         @param pCB 回调对象指针
         @return true 成功，false 失败
         */
        ZEGO_API bool SetAudioEngineCallback(IAudioEngineCallback *pCB);
        
        /**
         设置配置信息
         
         @param config config 配置信息
         @attention 确保在 Init SDK 前调用
         */
        ZEGO_API void SetConfig(const char *pConfig);

        /**
        发送自定义信令

        @param memberList 信令发送成员列表
        @param memberCount 成员个数
        @param content 信令内容
        @return 消息 seq
        */
        ZEGO_API int SendCustomCommand(ROOM::ZegoUser *memberList, unsigned int memberCount, const char *content);
    }
}

#endif /* AudioRoom_h */

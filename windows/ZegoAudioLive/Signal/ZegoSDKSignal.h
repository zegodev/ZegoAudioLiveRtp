#pragma once

#include "Model/ZegoStreamModel.h"
#include "AudioRoomCallback.h"
#include "AudioRoomCallback-Player.h"
#include "AudioRoomCallback-Publisher.h"
#include "zego-api-sound-level.h"
#include <QObject>
#include <QVector>

using namespace ZEGO;

class QZegoSDKSignal : public QObject,
	public AUDIOROOM::IAudioRoomCallback,
	public AUDIOROOM::IAudioEngineCallback,
	public AUDIOROOM::IAudioLivePublisherCallback,
	public AUDIOROOM::IAudioLivePlayerCallback,
	public AV::IZegoDeviceStateCallback,
	public AV::IZegoAudioRecordCallback,
	public AV::IZegoLiveEventCallback,
	public SOUNDLEVEL::IZegoSoundLevelCallback
{
    Q_OBJECT

public:
	QZegoSDKSignal();
	~QZegoSDKSignal();

signals:
	void sigLoginRoom(int errorCode, const QString& roomID);
	void sigDisconnect(int errorCode, const QString& roomID);
	void sigKickOut(int reason, const QString& roomID);
	void sigStreamUpdate(const QString& strRoomID, StreamPtr pStream, AUDIOROOM::ZegoStreamUpdateType type);
	void sigUserUpdate(QVector <QString> userIDs, QVector <QString> userNames, QVector <int> userFlags, QVector <int> userRoles, unsigned int userCount, AUDIOROOM::ZegoUserUpdateType type);
	void sigPublishStateUpdate(int stateCode, const QString& strStreamID, StreamPtr pStream);
	void sigPlayStateUpdate(int stateCode, StreamPtr pStream);
	void sigAudioDeviceChanged(AV::AudioDeviceType deviceType, const QString& strDeviceId, const QString& strDeviceName, AV::DeviceState state);
	void sigPublishQualityUpdate(const QString& streamId, double akbps, int rtt, int pktLostRate);
	void sigPlayQualityUpdate(const QString& streamId, double akbps, double audioBreakRate, int rtt, int pktLostRate);
	void sigSoundLevelUpdate(QVector< QPair<QString, float> > soundLevelList);
	void sigCaptureSoundLevelUpdate(QString streamId, float soundLevel);
	void sigStreamExtraInfoUpdated(QVector<StreamPtr> streamList, QString strRoomId);
	void sigAVKitEvent(int event);

protected:
	//IAudioRoomCallback
	void OnLoginRoom(int errorCode, const char *pszRoomID);
	void OnLogoutRoom(int errorCode, const char *pszRoomID){}
	void OnKickout(int reason, const char *pszRoomID);
    void OnDisconnect(int errorCode, const char *pszRoomID);
	void OnStreamUpdate(AUDIOROOM::ZegoStreamUpdateType type, const AUDIOROOM::ZegoStreamInfo& pStreamInfo, const char *pszRoomID);
	void OnUserUpdate(const AUDIOROOM::ZegoUserInfo *pUserInfo, unsigned int userCount, AUDIOROOM::ZegoUserUpdateType type);
	void OnStreamExtraInfoUpdated(AUDIOROOM::ZegoStreamInfo *pStreamInfo, unsigned int streamCount, const char *pszRoomID);

	//IAudioEngineCallback
	//void OnAudioEngineStop() = 0;
	void OnAudioEngineStart() override{}
	void OnAudioEngineStop(){}

	//IAudioLivePublisherCallback
	void OnPublishStateUpdate(int stateCode, const char *pszStreamID, const AUDIOROOM::ZegoPublishingStreamInfo& oStreamInfo);
	void OnPublishQualityUpdate(const char* pszStreamID, AUDIOROOM::ZegoPublishQuality publishQuality);
	void OnAuxCallback(unsigned char *pData, int *pDataLen, int *pSampleRate, int *pNumChannels) {}

	//IAudioLivePlayerCallback
	void OnPlayStateUpdate(int stateCode, const AUDIOROOM::ZegoStreamInfo& pStreamInfo);
	void OnPlayQualityUpdate(const char* pszStreamID, AUDIOROOM::ZegoPlayQuality playQuality);

	//IZegoDeviceStateCallback
	void OnAudioDeviceStateChanged(AV::AudioDeviceType deviceType, AV::DeviceInfo *deviceInfo, AV::DeviceState state);
	void OnAudioVolumeChanged(AV::AudioDeviceType deviceType, const char *deviceId, AV::VolumeType volumeType, unsigned int volume, bool bMuted) {}
    void OnDeviceError(const char* deviceName, int errorCode) {}

	//IZegoAudioRecordCallback
	//录制结果回调
	void OnAudioRecordCallback(const unsigned char *pData, int data_len, int sample_rate, int num_channels, int bit_depth, unsigned int type) {}
	//录制回调
    void OnAudioRecordCallback(const unsigned char *pData, int data_len, int sample_rate, int num_channels, int bit_depth) {}

	//IZegoLiveEventCallback
	void OnAVKitEvent(int event, AV::EventInfo* pInfo);

	//IZegoSoundLevelCallback
	void OnSoundLevelUpdate(SOUNDLEVEL::ZegoSoundLevelInfo *pSoundLevelList, unsigned int soundLevelCount);
	void OnCaptureSoundLevelUpdate(SOUNDLEVEL::ZegoSoundLevelInfo *pCaptureSoundLevel);

};
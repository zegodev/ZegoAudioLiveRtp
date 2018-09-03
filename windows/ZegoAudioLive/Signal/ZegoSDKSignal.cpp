#include "ZegoSDKSignal.h"
#include "Base/IncludeZegoAudioRoomApi.h"
#include <QMetaType>

QZegoSDKSignal::QZegoSDKSignal()
{
	qRegisterMetaType<AUDIOROOM::ZegoStreamUpdateType>("AUDIOROOM::ZegoStreamUpdateType");
	qRegisterMetaType<StreamPtr>("StreamPtr");
	qRegisterMetaType<AV::AudioDeviceType>("AV::AudioDeviceType");
	qRegisterMetaType<AV::DeviceState>("AV::DeviceState");
	qRegisterMetaType<QVector <QString>>("QVector <QString>");
	qRegisterMetaType<QVector <int>>("QVector <int>");
	qRegisterMetaType<AUDIOROOM::ZegoUserUpdateType>("AUDIOROOM::ZegoUserUpdateType");
	qRegisterMetaType< QVector<QPair<QString, float>> >("QVector<QPair<QString,float>>");
	qRegisterMetaType<QVector <StreamPtr>>("QVector <StreamPtr>");
}

QZegoSDKSignal::~QZegoSDKSignal()
{

}

void QZegoSDKSignal::OnLoginRoom(int errorCode, const char *pszRoomID)
{
	log_string_notice(qtoc(QStringLiteral("[%1]: errorCode: %2, roomID: %3").arg(__FUNCTION__).arg(errorCode).arg(pszRoomID)));
	QString strRoomID = pszRoomID ? pszRoomID : "";

	emit sigLoginRoom(errorCode, strRoomID);
}

void QZegoSDKSignal::OnKickout(int reason, const char *pszRoomID)
{
	log_string_notice(qtoc(QStringLiteral("[%1]: reason: %2, roomID: %3").arg(__FUNCTION__).arg(reason)));
	QString strRoomID = pszRoomID ? pszRoomID : "";

	emit sigDisconnect(reason, strRoomID);
}
void QZegoSDKSignal::OnDisconnect(int errorCode, const char *pszRoomID)
{
	log_string_notice(qtoc(QStringLiteral("[%1]: errorCode: %2, roomID: %3").arg(__FUNCTION__).arg(errorCode)));
	QString strRoomID = pszRoomID ? pszRoomID : "";

	emit sigKickOut(errorCode, strRoomID);
}

void QZegoSDKSignal::OnStreamUpdate(AUDIOROOM::ZegoStreamUpdateType type, const AUDIOROOM::ZegoStreamInfo& pStreamInfo, const char *pszRoomID)
{
	
	QString strRoomID = pszRoomID ? pszRoomID : "";
	AUDIOROOM::ZegoStreamInfo zegoStreamInfo = pStreamInfo;
	QString streamID = zegoStreamInfo.szStreamId;
	QString userID = zegoStreamInfo.szUserId;
	QString userName = zegoStreamInfo.szUserName;
	QString ExtraInfo = zegoStreamInfo.szExtraInfo;

	log_string_notice(qtoc(QStringLiteral("[%1]: stream id: %2, update type: %3, user id: %4, user name: %5")
		.arg(__FUNCTION__)
		.arg(streamID)
		.arg(type)
		.arg(userID)
		.arg(userName)
	));

	StreamPtr pStream(new QZegoStreamModel(streamID, userID, userName, ExtraInfo));
	
	emit sigStreamUpdate(strRoomID, pStream, type);
}

void QZegoSDKSignal::OnUserUpdate(const AUDIOROOM::ZegoUserInfo *pUserInfo, unsigned int userCount, AUDIOROOM::ZegoUserUpdateType type)
{
	QVector<QString> userIDs;
	QVector<QString> userNames;
	QVector<int> userFlags;
	QVector<int> userRoles;

	log_string_notice(qtoc(QStringLiteral("[%1]: user update count: %2").arg(__FUNCTION__).arg(userCount)));
	for (int i = 0; i < userCount; i++)
	{
		QString strUserId = pUserInfo[i].szUserId;
		QString strUserName = pUserInfo[i].szUserName;
		int userFlag = pUserInfo[i].udapteFlag;
		int userRole = pUserInfo[i].role;

		userIDs.push_back(strUserId);
		userNames.push_back(strUserName);
		userFlags.push_back(userFlag);
		userRoles.push_back(userRole);

		log_string_notice(qtoc(QStringLiteral("[%1]:updated user id: %2, user name: %3, user role: %4, user flag: %5")
			.arg(__FUNCTION__)
			.arg(strUserId)
			.arg(strUserName)
			.arg(userFlag)
			.arg(userRole)
		));
	}

	emit sigUserUpdate(userIDs, userNames, userFlags, userRoles, userCount, type);
}



void QZegoSDKSignal::OnPublishStateUpdate(int stateCode, const char *pszStreamID, const AUDIOROOM::ZegoPublishingStreamInfo& oStreamInfo)
{
	log_string_notice(qtoc(QStringLiteral("[%1]: stateCode: %2, streamID: %3").arg(__FUNCTION__).arg(stateCode).arg(pszStreamID)));
	QString strStreamID = pszStreamID ? pszStreamID : "";

	StreamPtr pStream(new QZegoStreamModel(strStreamID, "", "", "", true));

	for (unsigned int i = 0; i < oStreamInfo.uiRtmpURLCount; i++)
	{
		pStream->m_vecRtmpUrls.push_back(oStreamInfo.arrRtmpURLs[i]);
	}

	for (unsigned int i = 0; i < oStreamInfo.uiFlvURLCount; i++)
	{
		pStream->m_vecFlvUrls.push_back(oStreamInfo.arrFlvURLs[i]);
	}

	for (unsigned int i = 0; i < oStreamInfo.uiHlsURLCount; i++)
	{
		pStream->m_vecHlsUrls.push_back(oStreamInfo.arrHlsURLs[i]);
	}

	emit sigPublishStateUpdate(stateCode, strStreamID, pStream);
}

void QZegoSDKSignal::OnPublishQualityUpdate(const char* pszStreamID, AUDIOROOM::ZegoPublishQuality publishQuality)
{
	QString streamId = pszStreamID ? pszStreamID : "";
	double akbps = publishQuality.akbps;
	int rtt = publishQuality.rtt;
	int pktLostRate = publishQuality.pktLostRate;
	int quality = publishQuality.quality;

	emit sigPublishQualityUpdate(streamId, akbps, rtt, pktLostRate);
}

void QZegoSDKSignal::OnPlayStateUpdate(int stateCode, const AUDIOROOM::ZegoStreamInfo& pStreamInfo)
{
	AUDIOROOM::ZegoStreamInfo zegoStreamInfo = pStreamInfo;
	QString streamID = zegoStreamInfo.szStreamId;
	QString userID = zegoStreamInfo.szUserId;
	QString userName = zegoStreamInfo.szUserName;
	QString ExtraInfo = zegoStreamInfo.szExtraInfo;
	log_string_notice(qtoc(QStringLiteral("[%1]: stateCode: %2, streamID: %3, userID: %4, userName: %5")
		.arg(__FUNCTION__)
		.arg(stateCode)
		.arg(streamID)
		.arg(userID)
		.arg(userName)
	));

	StreamPtr pStream(new QZegoStreamModel(streamID, userID, userName, ExtraInfo));

	emit sigPlayStateUpdate(stateCode, pStream);
}

void QZegoSDKSignal::OnPlayQualityUpdate(const char* pszStreamID, AUDIOROOM::ZegoPlayQuality playQuality)
{
	QString streamId = pszStreamID ? pszStreamID : "";
	double akbps = playQuality.akbps;
	double audioBreakRate = playQuality.audioBreakRate;
	int rtt = playQuality.rtt;
	int pktLostRate = playQuality.pktLostRate;

	emit sigPlayQualityUpdate(streamId, akbps, audioBreakRate, rtt, pktLostRate);
}

void QZegoSDKSignal::OnAudioDeviceStateChanged(AV::AudioDeviceType deviceType, AV::DeviceInfo *deviceInfo, AV::DeviceState state)
{
	if (deviceInfo == nullptr)
	{
		log_string_notice(qtoc(QStringLiteral("[%1]: deviceType: %2, deviceID: null, deviceName: null, deviceState: %3")
			.arg(__FUNCTION__)
			.arg(deviceType)
			.arg(state)
		));

		return;
	}

	QString strDeviceId = deviceInfo->szDeviceId;
	QString strDeviceName = deviceInfo->szDeviceName;

	log_string_notice(qtoc(QStringLiteral("[%1]: deviceType: %2, deviceID: %3, deviceName: %4, deviceState: %5")
		.arg(__FUNCTION__)
		.arg(deviceType)
		.arg(strDeviceId)
		.arg(strDeviceName)
		.arg(state)
	));

	emit sigAudioDeviceChanged(deviceType, strDeviceId, strDeviceName, state);
}

void QZegoSDKSignal::OnAVKitEvent(int event, AV::EventInfo* pInfo)
{
	//QVector<>
	log_string_notice(qtoc(QStringLiteral("[%1]: avkit event: %2").arg(__FUNCTION__).arg(event)));
	emit sigAVKitEvent(event);
}

void QZegoSDKSignal::OnSoundLevelUpdate(SOUNDLEVEL::ZegoSoundLevelInfo *pSoundLevelList, unsigned int soundLevelCount)
{
	if (soundLevelCount == 0)
		return;

	QVector< QPair<QString, float> >soundLevelList;

	for (int i = 0; i < soundLevelCount; i++)
	{
		QString streamId = pSoundLevelList[i].szStreamID;
		float soundLevel = pSoundLevelList[i].soundLevel;
		QPair<QString, float> p;

		p.first = streamId;
		p.second = soundLevel;
		soundLevelList.push_back(p);
	}

	emit sigSoundLevelUpdate(soundLevelList);
}

void QZegoSDKSignal::OnCaptureSoundLevelUpdate(SOUNDLEVEL::ZegoSoundLevelInfo *pCaptureSoundLevel)
{
	if (pCaptureSoundLevel == nullptr)
		return;

	QString streamId = pCaptureSoundLevel->szStreamID;
	float soundLevel = pCaptureSoundLevel->soundLevel;

	emit sigCaptureSoundLevelUpdate(streamId, soundLevel);
}

void QZegoSDKSignal::OnStreamExtraInfoUpdated(AUDIOROOM::ZegoStreamInfo *pStreamInfo, unsigned int streamCount, const char *pszRoomID)
{
	QString strRoomId = pszRoomID ? pszRoomID : "";
	log_string_notice(qtoc(QStringLiteral("[%1]: stream list count: %2, roomId: %3")
		.arg(__FUNCTION__)
		.arg(streamCount)
		.arg(strRoomId)
	));

	QVector<StreamPtr> vStreamList;
	for (int i = 0; i < streamCount; i++)
	{
		StreamPtr pStream(new QZegoStreamModel(pStreamInfo[i].szStreamId, pStreamInfo[i].szUserId, pStreamInfo[i].szUserName, pStreamInfo[i].szExtraInfo));
		vStreamList.push_back(pStream);
	}

	emit sigStreamExtraInfoUpdated(vStreamList, strRoomId);
}
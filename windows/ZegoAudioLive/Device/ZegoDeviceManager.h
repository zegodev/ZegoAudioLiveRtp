#pragma once

#include <QObject>
#include <QVector>
#include "AVDefines.h"
#include "AudioRoom.h"

using namespace ZEGO;

struct QDeviceInfo
{
	QString deviceId;
	QString deviceName;
};

enum QDeviceType
{
	TYPE_AUDIO_INPUT = 0,
	TYPE_AUDIO_OUTPUT
};

enum QDeviceState
{
	STATE_ERROR = -1,
	STATE_NORMAL,
	STATE_SWAP
};

class ZegoDeviceManager : public QObject
{
	Q_OBJECT

signals:
	void sigDeviceAdded(int type, QString deviceName);
	void sigDeviceDeleted(int type, int index);

	void sigDeviceNone(int type);
	void sigDeviceExist(int type);

	void sigMicVolumeMute(bool bIsMute);
	void sigSpeakerVolumeMute(bool bIsMute);

public:
	ZegoDeviceManager();
	~ZegoDeviceManager();

	void EnumAudioDeviceList();
	QDeviceState SetMicrophoneIdByIndex(int index);
	QDeviceState SetSpeakerIdByIndex(int index);

	int GetAudioInputDeviceIndex();
	int GetAudioOutputDeviceIndex();

	void SetMicVolume(int volume);
	int GetMicVolume();
	void SetMicEnabled(bool isUse);
	bool GetMicEnabled();

	void SetPlayVolume(int volume);
	int GetPlayVolume();
	void SetSpeakerEnabled(bool isUse);
	bool GetSpeakerEnabled();

	QVector<QDeviceInfo> GetAudioInputDeviceList();
	QVector<QDeviceInfo> GetAudioOutputDeviceList();

	const QString& GetAudioInputDeviceId();
	const QString& GetAudioOutputDeviceId();
signals:
	void sigMicIdChanged(QString deviceId);
	void sigSpeakerIdChanged(QString deviceId);

protected slots:
	void OnAudioDeviceStateChanged(AV::AudioDeviceType deviceType, const QString& strDeviceId, const QString& strDeviceName, AV::DeviceState state);

private:
	void RefreshMicIndex();
	void RefreshSpeakerIndex();

private:
	QVector<QDeviceInfo> m_audioInputDeviceList;
	QVector<QDeviceInfo> m_audioOutputDeviceList;

	QString m_audioInputDeviceId;
	QString m_audioOutputDeviceId;

	int m_micVolume = 100;
    bool m_micEnabled = true;

	int m_playVolume = 100;
	bool m_SpeakerEnabled = true;

	int m_micListIndex = -1;
	int m_speakerListIndex = -1;
};

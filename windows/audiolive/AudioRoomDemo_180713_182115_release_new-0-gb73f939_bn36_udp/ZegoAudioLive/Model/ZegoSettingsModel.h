#pragma once

#include <QString>
#include <QSharedPointer>
#include "AVDefines.h"
#include "AudioRoom.h"

using namespace ZEGO;

//App参数
typedef struct _AppVersion
{
	int m_versionMode;
	unsigned long m_strAppID;
	QString m_strAppSign;

	_AppVersion& operator=(const _AppVersion& s)//重载运算符
	{
		this->m_strAppID = s.m_strAppID;
		this->m_strAppSign = s.m_strAppSign;
		this->m_versionMode = s.m_versionMode;
		return *this;
	}

}AppVersion;

class QZegoSettingsModel
{
public:
	QZegoSettingsModel();
	~QZegoSettingsModel();

	QString GetMircophoneId(void);
	void SetMicrophoneId(const QString& microphoneId);

	QString GetSpeakerId(void);
	void SetSpeakerId(const QString& speakerId);

	void InitDeviceId(void);

private:

	QString m_strMicrophoneId;
	QString m_strSpeakerId;
};

using SettingsPtr = QSharedPointer< QZegoSettingsModel >;
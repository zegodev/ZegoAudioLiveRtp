#pragma once

#include "Model/ZegoSettingsModel.h"
#include <QFile>
#include <QSettings>

class QZegoUserConfig
{
public:
	QZegoUserConfig();
	~QZegoUserConfig();

	void LoadConfig(void);
	void SaveConfig(void);

	QString GetUserId(void);
	void SetUserId(const QString strUserId);
	
	QString GetUserName(void);
	void SetUserName(const QString strUserName);

	SettingsPtr GetAudioSettings(void);
	void SetAudioSettings(SettingsPtr curSettings);

	//保存当前设置的App版本信息，默认为UDP
	void setAppVersion(AppVersion appVersion);
	AppVersion getAppVersion(void);

	bool GetUseTestEnv();
	void SetUseTestEnv(bool isUseTestEnv);

private:
	bool LoadConfigInternal(void);

private:
	QString m_strIniPath;

	QString m_strUserId;
	QString m_strUserName;

	SettingsPtr m_pAudioSettings;

	AppVersion m_appVersion;

	bool m_isUseTestEnv;
};
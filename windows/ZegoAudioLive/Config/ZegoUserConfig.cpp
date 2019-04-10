#include "ZegoUserConfig.h"
#include "Base/IncludeZegoAudioRoomApi.h"
#include "Base/ZegoBase.h"
#include <random>


QZegoUserConfig::QZegoUserConfig()
{
	//生成ini文件,用于在本地保存用户配置信息
	m_strIniPath = QStringLiteral("Config/ZegoUserConfig.ini");
	//生成配置时默认用UDP
	m_appVersion.m_versionMode = ZEGO_PROTOCOL_UDP;
}

QZegoUserConfig::~QZegoUserConfig()
{

}

void QZegoUserConfig::LoadConfig(void)
{
	log_string_notice(qtoc(QStringLiteral("[%1]: load config enter.").arg(__FUNCTION__)));

	if (LoadConfigInternal())
	{
		return;
	}

	//随机生成编号为10000000-99999999的用户ID
	std::random_device rd;
	std::uniform_int_distribution<int> dist(10000000, 99999999);
	//int to QString
	m_strUserId = QString::number(dist(rd), 10);
	m_strUserName = QStringLiteral("windows-") + m_strUserId;

	m_isUseTestEnv = true;

	m_appVersion.m_versionMode = ZEGO_PROTOCOL_UDP;
	m_appVersion.m_strAppID = 0;
	m_appVersion.m_strAppSign = "";

	if (m_pAudioSettings == nullptr)
	{
		m_pAudioSettings = SettingsPtr::create();
	}

	log_string_notice(qtoc(QStringLiteral("[%1]: new user. user id: %1, user name: %2")
		.arg(__FUNCTION__)
		.arg(m_strUserId)
		.arg(m_strUserName)));

	SaveConfig();
}

bool QZegoUserConfig::LoadConfigInternal(void)
{
	QSettings *configIni = new QSettings(m_strIniPath, QSettings::IniFormat);
	if (configIni == nullptr)
	{
		log_string_notice(qtoc(QStringLiteral("[%1]: load user failed. config file is not exists.")));
		return false;
	}

	QString strUserId = configIni->value("/sUserRecords/kUserId").toString();
	QString strUserName = configIni->value("/sUserRecords/kUserName").toString();

	bool nIsUseTest = configIni->value("/sUserRecords/kIsTestEnv").toBool();

	int nAppVer = configIni->value("/sUserRecords/kAppVersion").toInt();
	unsigned int nAppId = configIni->value("/sUserRecords/kAppId").toLongLong();
	QString nAppSign = configIni->value("/sUserRecords/kAppSign").toString();
	//读ini文件完毕后释放指针
	delete configIni;

	if (strUserId.isEmpty() || strUserName.isEmpty())
	{
		log_string_notice(qtoc(QStringLiteral("[%1]: load user failed. user id or user name is empty.")));
		return false;
	}

	m_strUserId = strUserId;
	m_strUserName = strUserName;

	m_isUseTestEnv = nIsUseTest;

	m_appVersion.m_versionMode = nAppVer;
	m_appVersion.m_strAppID = nAppId;
	m_appVersion.m_strAppSign = nAppSign;

	if (m_pAudioSettings == nullptr)
	{
		m_pAudioSettings = SettingsPtr::create();
	}
	
	log_string_notice(qtoc(QStringLiteral("[%1]: load user success. user id: %1, user name: %2")
		.arg(__FUNCTION__)
		.arg(strUserId)
		.arg(strUserName)));

	return true;
}
void QZegoUserConfig::SaveConfig()
{
	log_string_notice(qtoc(QStringLiteral("[%1]: save config enter.").arg(__FUNCTION__)));

	QSettings *configIni = new QSettings(m_strIniPath, QSettings::IniFormat);
	if (m_strUserId.isEmpty() || m_strUserName.isEmpty() || m_pAudioSettings == nullptr)
	{
		log_string_notice(qtoc(QStringLiteral("[%1]: save config error. user config or video quality prams incorrect").arg(__FUNCTION__)));
		return;
	}

	configIni->setValue("/sUserRecords/kUserId", m_strUserId);
	configIni->setValue("/sUserRecords/kUserName", m_strUserName);

	configIni->setValue("/sUserRecords/kIsTestEnv", m_isUseTestEnv);
	configIni->setValue("/sUserRecords/kAppVersion", m_appVersion.m_versionMode);
	if (m_appVersion.m_versionMode == ZEGO_PROTOCOL_CUSTOM)
	{
		configIni->setValue("/sUserRecords/kAppId", (qlonglong)m_appVersion.m_strAppID);
		configIni->setValue("/sUserRecords/kAppSign", m_appVersion.m_strAppSign);
	}

	delete configIni;

	log_string_notice(qtoc(QStringLiteral("[%1]: save user config success.").arg(__FUNCTION__)));
}

QString QZegoUserConfig::GetUserId(void)
{
	return m_strUserId;
}

void QZegoUserConfig::SetUserId(QString strUserId)
{
	if (!strUserId.isEmpty())
	{
		m_strUserId = strUserId;
	}
}

QString QZegoUserConfig::GetUserName(void)
{
	return m_strUserName;
}

void QZegoUserConfig::SetUserName(QString strUserName)
{
	if (!strUserName.isEmpty())
	{
		m_strUserName = strUserName;
	}
}


SettingsPtr QZegoUserConfig::GetAudioSettings(void)
{
	return m_pAudioSettings;
}

void QZegoUserConfig::SetAudioSettings(SettingsPtr curSettings)
{
	
	m_pAudioSettings->SetMicrophoneId(curSettings->GetMircophoneId());

}

void QZegoUserConfig::setAppVersion(AppVersion appVersion)
{
	m_appVersion = appVersion;
}

AppVersion QZegoUserConfig::getAppVersion(void)
{
	return m_appVersion;
}

bool QZegoUserConfig::GetUseTestEnv()
{
	return m_isUseTestEnv;
}

void QZegoUserConfig::SetUseTestEnv(bool isUseTestEnv)
{
	m_isUseTestEnv = isUseTestEnv;
}

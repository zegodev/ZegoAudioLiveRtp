#pragma once

#include <QObject>
#include <QVector>
#include "Signal/ZegoSDKSignal.h"
#include "Model/ZegoSettingsModel.h"
#include "ZegoAudioLiveVersion.h"

//demo版本的枚举类型
typedef enum _Version
{
	ZEGO_PROTOCOL_UDP = 0,
	ZEGO_PROTOCOL_UDP_INTERNATIONAL = 1,
	ZEGO_PROTOCOL_CUSTOM = 2
}Version;

class QZegoBase
{
public :
	QZegoBase();
	~QZegoBase();

	bool InitAVSDK(SettingsPtr pSetting, QString userID, QString userName);
	bool InitAVSDKofCustom(SettingsPtr pCurSetting, QString userID, QString userName, unsigned long appID, unsigned char *appSign, int signLen);
	void UninitAVSDK(void);
	bool IsAVSdkInited(void);
	void setKey(int pKey);
	int getKey();
	void setIsTestEnv(bool isTest);
	bool getUseTestEnv();

	void setUseAudioBitrateControll(bool bUse);
	bool getUseAudioBitrateControll();

	QZegoSDKSignal* GetAVSignal(void);
	unsigned long GetAppID(void);
	unsigned long GetAppIDwithKey(int key);
	unsigned char* GetAppSign();

	void setCustomAppID(unsigned long appid);
	void setCustomAppSign(unsigned char *appsign);

private :
	bool m_isInitedSDK;

	QZegoSDKSignal* m_pAVSignal;

	//默认不使用测试环境
	bool isTestEnv = false;
	//默认使用音频流控
	bool isAudioBitrateControll = true;

	//appid、appsign默认为UDP版本
	int key = Version::ZEGO_PROTOCOL_UDP;

	QVector <unsigned int> appIDs;
	QVector <unsigned char *> appSigns;
};
#pragma once

#include "Base/ZegoBase.h"
#include "Config/ZegoUserConfig.h"

class QZegoAudioDemoApp
{
public:
	QZegoAudioDemoApp();

public:
	QZegoBase &GetBase();
	QZegoUserConfig &GetConfig();

private:
	QZegoBase m_base;
	QZegoUserConfig m_config;
};

extern QZegoAudioDemoApp theApp;

QZegoSDKSignal * GetAVSignal(void);
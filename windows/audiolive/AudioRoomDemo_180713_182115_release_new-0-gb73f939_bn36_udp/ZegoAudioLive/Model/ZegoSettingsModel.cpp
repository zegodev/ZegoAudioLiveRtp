#include "ZegoSettingsModel.h"



QZegoSettingsModel::QZegoSettingsModel()
{
	//InitDeviceId();
}

QZegoSettingsModel::~QZegoSettingsModel()
{

}

void QZegoSettingsModel::SetMicrophoneId(const QString& microphoneId)
{
	m_strMicrophoneId = microphoneId;
}

QString QZegoSettingsModel::GetMircophoneId(void)
{
	return m_strMicrophoneId;
}

QString QZegoSettingsModel::GetSpeakerId(void)
{
	return m_strSpeakerId;
}

void QZegoSettingsModel::SetSpeakerId(const QString& speakerId)
{
	m_strSpeakerId = speakerId;
}

void QZegoSettingsModel::InitDeviceId(void)
{
	int nDeviceCount(0);
	AV::DeviceInfo* pDeviceList(NULL);

	pDeviceList = AUDIOROOM::GetAudioDeviceList(ZEGO::AV::AudioDevice_Input, nDeviceCount);
	if (nDeviceCount > 0 && pDeviceList != NULL)
		m_strMicrophoneId = pDeviceList[0].szDeviceId;
	AUDIOROOM::FreeDeviceList(pDeviceList);
	pDeviceList = NULL;

	
}

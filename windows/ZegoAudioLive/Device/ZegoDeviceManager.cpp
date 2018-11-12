#include "ZegoDeviceManager.h"
#include "Signal/ZegoSDKSignal.h"
#include "ZegoAudioDemo.h"
#include "Base/IncludeZegoAudioRoomApi.h"

ZegoDeviceManager::ZegoDeviceManager()
{
	log_string_notice(qtoc(QStringLiteral("[%1]: device manager module create").arg(__FUNCTION__)));
	connect(GetAVSignal(), &QZegoSDKSignal::sigAudioDeviceChanged, this, &ZegoDeviceManager::OnAudioDeviceStateChanged);

	//初始化允许使用麦克风，扬声器
	AUDIOROOM::EnableMic(m_micEnabled);
	AUDIOROOM::EnableSpeaker(m_SpeakerEnabled);
}

ZegoDeviceManager::~ZegoDeviceManager()
{
	log_string_notice(qtoc(QStringLiteral("[%1]: device manager module destroy").arg(__FUNCTION__)));
}

//设备初始化
void ZegoDeviceManager::EnumAudioDeviceList()
{
	int nDeviceCount = 0;
	AV::DeviceInfo* pDeviceList(NULL);

	m_audioInputDeviceList.clear();
	//获取音频输入设备
	pDeviceList = AUDIOROOM::GetAudioDeviceList(AV::AudioDeviceType::AudioDevice_Input, nDeviceCount);
	log_string_notice(qtoc(QStringLiteral("[%1]: get audio input device list, device count: %2")
		.arg(__FUNCTION__)
		.arg(nDeviceCount)
	));

	for (int i = 0; i < nDeviceCount; i++)
	{
		QDeviceInfo info;
		info.deviceId = pDeviceList[i].szDeviceId;
		info.deviceName = pDeviceList[i].szDeviceName;

		m_audioInputDeviceList.append(info);
	}

	if (m_audioInputDeviceList.size() > 0)
	{
		m_micListIndex = 0;

		unsigned int *id_len = new unsigned int;
		*id_len = 1024;
		char *mic_id = new char[*id_len];
		AUDIOROOM::GetDefaultAudioDeviceId(AV::AudioDeviceType::AudioDevice_Input, mic_id, id_len);
		QString defaultId = mic_id;

		//设置默认麦克风与系统一致
		for (int i = 0; i < m_audioInputDeviceList.size(); i++)
		{
			if (m_audioInputDeviceList.at(i).deviceId == defaultId)
			{
				m_micListIndex = i;
				break;
			}
		}

		m_audioInputDeviceId = m_audioInputDeviceList.at(m_micListIndex).deviceId;
		
		emit sigMicIdChanged(m_audioInputDeviceId);
	}
	else
	{
		m_audioInputDeviceId = "";
	}

	AUDIOROOM::FreeDeviceList(pDeviceList);
	pDeviceList = NULL;

	//获取音频输出设备
	nDeviceCount = 0;
	pDeviceList = AUDIOROOM::GetAudioDeviceList(AV::AudioDeviceType::AudioDevice_Output, nDeviceCount);
	log_string_notice(qtoc(QStringLiteral("[%1]: get audio output device list, device count: %2")
		.arg(__FUNCTION__)
		.arg(nDeviceCount)
	));

	for (int i = 0; i < nDeviceCount; i++)
	{
		QDeviceInfo info;
		info.deviceId = pDeviceList[i].szDeviceId;
		info.deviceName = pDeviceList[i].szDeviceName;

		m_audioOutputDeviceList.append(info);
	}

	if (m_audioOutputDeviceList.size() > 0)
	{
		m_speakerListIndex = 0;

		unsigned int *id_len = new unsigned int;
		*id_len = 1024;
		char *speaker_id = new char[*id_len];
		AUDIOROOM::GetDefaultAudioDeviceId(AV::AudioDeviceType::AudioDevice_Output, speaker_id, id_len);
		QString defaultId = speaker_id;

		//设置默认麦克风与系统一致
		for (int i = 0; i < m_audioOutputDeviceList.size(); i++)
		{
			if (m_audioOutputDeviceList.at(i).deviceId == defaultId)
			{
				m_speakerListIndex = i;
				break;
			}
		}
		m_audioOutputDeviceId = m_audioOutputDeviceList.at(m_speakerListIndex).deviceId;

		emit sigSpeakerIdChanged(m_audioOutputDeviceId);
	}
	else
	{
		m_audioOutputDeviceId = "";
	}

	AUDIOROOM::FreeDeviceList(pDeviceList);
	pDeviceList = NULL;
}

void ZegoDeviceManager::RefreshMicIndex()
{
	m_micListIndex = -1;
	for (int i = 0; i < m_audioInputDeviceList.size(); i++)
		if (m_audioInputDeviceList.at(i).deviceId == m_audioInputDeviceId)
			m_micListIndex = i;
}

void ZegoDeviceManager::RefreshSpeakerIndex()
{
	m_speakerListIndex = -1;
	for (int i = 0; i < m_audioOutputDeviceList.size(); i++)
		if (m_audioOutputDeviceList.at(i).deviceId == m_audioOutputDeviceId)
			m_speakerListIndex = i;
}

//音频设备切换
QDeviceState ZegoDeviceManager::SetMicrophoneIdByIndex(int index)
{
	if (index >= m_audioInputDeviceList.size())
		return STATE_ERROR;

	m_micListIndex = index;
	m_audioInputDeviceId = m_audioInputDeviceList.at(m_micListIndex).deviceId;
	emit sigMicIdChanged(m_audioInputDeviceId);

	log_string_notice(qtoc(QStringLiteral("[%1]: set microphone deviceId: %2 by index %3")
		.arg(__FUNCTION__)
		.arg(m_audioInputDeviceId)
		.arg(index)
	));

	return STATE_NORMAL;
}

QDeviceState ZegoDeviceManager::SetSpeakerIdByIndex(int index)
{
	if (index >= m_audioOutputDeviceList.size())
		return STATE_ERROR;

	m_speakerListIndex = index;
	m_audioOutputDeviceId = m_audioOutputDeviceList.at(m_speakerListIndex).deviceId;
	emit sigSpeakerIdChanged(m_audioOutputDeviceId);

	log_string_notice(qtoc(QStringLiteral("[%1]: set speaker deviceId: %2 by index %3")
		.arg(__FUNCTION__)
		.arg(m_audioOutputDeviceId)
		.arg(index)
	));

	return STATE_NORMAL;
}

int ZegoDeviceManager::GetAudioInputDeviceIndex()
{
	return m_micListIndex;
}

int ZegoDeviceManager::GetAudioOutputDeviceIndex()
{
	return m_speakerListIndex;
}

//音量切换
void ZegoDeviceManager::SetMicVolume(int volume)
{
	m_micVolume = volume;

    //log_string_notice(tr("SetMicVolume: %1").arg(volume).toStdString().c_str());
    AUDIOROOM::SetMicDeviceVolume(qtoc(m_audioInputDeviceId), volume);
    if (volume == 0 && m_micEnabled)
    {
        m_micEnabled = false;

        AUDIOROOM::EnableMic(m_micEnabled);
		emit sigMicVolumeMute(!m_micEnabled);
    }
    else if (!m_micEnabled && volume > 0)
    {
        m_micEnabled = true;

        AUDIOROOM::EnableMic(m_micEnabled);
		emit sigMicVolumeMute(!m_micEnabled);
    }
    
	
}

int ZegoDeviceManager::GetMicVolume()
{
	return m_micVolume;
}

void ZegoDeviceManager::SetMicEnabled(bool isUse)
{
	m_micEnabled = isUse;
	AUDIOROOM::EnableMic(isUse);
}

bool ZegoDeviceManager::GetMicEnabled()
{
	return m_micEnabled;
}

//拉流音量切换
void ZegoDeviceManager::SetPlayVolume(int volume)
{
	m_playVolume = volume;

	AUDIOROOM::SetPlayVolume(m_playVolume);
	if (volume == 0 && m_SpeakerEnabled)
	{
		m_SpeakerEnabled = false;

		AUDIOROOM::EnableSpeaker(m_SpeakerEnabled);
		emit sigSpeakerVolumeMute(!m_SpeakerEnabled);
	}
	else if (volume > 0 && !m_SpeakerEnabled)
	{
		m_SpeakerEnabled = true;

		AUDIOROOM::EnableSpeaker(m_SpeakerEnabled);
		emit sigSpeakerVolumeMute(!m_SpeakerEnabled);
	}
}

int ZegoDeviceManager::GetPlayVolume()
{
	return m_playVolume;
}

void ZegoDeviceManager::SetSpeakerEnabled(bool isUse)
{
	m_SpeakerEnabled = isUse;
	AUDIOROOM::EnableSpeaker(m_SpeakerEnabled);
}

bool ZegoDeviceManager::GetSpeakerEnabled()
{
	return m_SpeakerEnabled;
}

QVector<QDeviceInfo> ZegoDeviceManager::GetAudioInputDeviceList()
{
	return m_audioInputDeviceList;
}

QVector<QDeviceInfo> ZegoDeviceManager::GetAudioOutputDeviceList()
{
	return m_audioOutputDeviceList;
}

const QString& ZegoDeviceManager::GetAudioInputDeviceId()
{
	return m_audioInputDeviceId;
}

const QString& ZegoDeviceManager::GetAudioOutputDeviceId()
{
	return m_audioOutputDeviceId;
}

void ZegoDeviceManager::OnAudioDeviceStateChanged(AV::AudioDeviceType deviceType, const QString& strDeviceId, const QString& strDeviceName, AV::DeviceState state)
{
	if (deviceType == AV::AudioDeviceType::AudioDevice_Output)
		return;

	if (state == AV::DeviceState::Device_Added)
	{
		QDeviceInfo added_device;
		added_device.deviceId = strDeviceId;
		added_device.deviceName = strDeviceName;
		m_audioInputDeviceList.append(added_device);

		//从0到1
		if (m_audioInputDeviceList.size() == 1)
		{
			m_micListIndex = 0;
			m_audioInputDeviceId = m_audioInputDeviceList.at(m_micListIndex).deviceId;
			emit sigMicIdChanged(m_audioInputDeviceId);

			//emit sigDeviceExist(TYPE_AUDIO);
		}

		emit sigDeviceAdded(TYPE_AUDIO_INPUT, added_device.deviceName);
	}
	else if (state == AV::DeviceState::Device_Deleted)
	{
		
		for (int i = 0; i < m_audioInputDeviceList.size(); ++i)
		{
			if (m_audioInputDeviceList.at(i).deviceId != strDeviceId)
				continue;

			m_audioInputDeviceList.takeAt(i);

			if (m_micListIndex == i)
			{
				if (m_audioInputDeviceList.size() > 0)
				{
					m_audioInputDeviceId = m_audioInputDeviceList.at(0).deviceId;
					
				}
				else
				{
					m_audioInputDeviceId = "";
					emit sigDeviceNone(TYPE_AUDIO_INPUT);
				}

				RefreshMicIndex();
				emit sigMicIdChanged(m_audioInputDeviceId);
			}

			emit sigDeviceDeleted(TYPE_AUDIO_INPUT, i);
		}

	}

}

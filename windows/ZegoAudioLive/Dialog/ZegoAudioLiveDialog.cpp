#include "ZegoAudioLiveDialog.h"
#include "Base/IncludeZegoAudioRoomApi.h"
#include "Base/ZegoAudioLiveDefines.h"
#include "Signal/ZegoSDKSignal.h"
#include "ZegoAudioDemo.h"
#include "AudioRoom.h"
#include <QJsonObject>
#include <QJsonDocument>
#include "zego-api-defines.h"

#define MAX_PLAY_COUNT AUDIOROOM::GetMaxPlayChannelCount()

ZegoAudioLiveDialog::ZegoAudioLiveDialog(RoomPtr chatRoom, QDialog *lastDialog, QWidget *parent)
	: ZegoDialog(parent), 
	  m_pChatRoom(chatRoom), 
	  m_lastDialog(lastDialog)
{
	ui.setupUi(this);

	log_string_notice(qtoc(QStringLiteral("[%1]: audio live dialog create").arg(__FUNCTION__)));

	//通过sdk的信号连接到本类的槽函数中
	connect(GetAVSignal(), &QZegoSDKSignal::sigLoginRoom, this, &ZegoAudioLiveDialog::OnLoginRoom);
	connect(GetAVSignal(), &QZegoSDKSignal::sigStreamUpdate, this, &ZegoAudioLiveDialog::OnStreamUpdated);
	connect(GetAVSignal(), &QZegoSDKSignal::sigPublishStateUpdate, this, &ZegoAudioLiveDialog::OnPublishStateUpdate);
	connect(GetAVSignal(), &QZegoSDKSignal::sigPlayStateUpdate, this, &ZegoAudioLiveDialog::OnPlayStateUpdate);
	connect(GetAVSignal(), &QZegoSDKSignal::sigDisconnect, this, &ZegoAudioLiveDialog::OnDisconnect);
	connect(GetAVSignal(), &QZegoSDKSignal::sigKickOut, this, &ZegoAudioLiveDialog::OnKickOut);
	connect(GetAVSignal(), &QZegoSDKSignal::sigPublishQualityUpdate, this, &ZegoAudioLiveDialog::OnPublishQualityUpdate);
	connect(GetAVSignal(), &QZegoSDKSignal::sigPlayQualityUpdate, this, &ZegoAudioLiveDialog::OnPlayQualityUpdate);
	connect(GetAVSignal(), &QZegoSDKSignal::sigUserUpdate, this, &ZegoAudioLiveDialog::OnUserUpdate);
	connect(GetAVSignal(), &QZegoSDKSignal::sigCaptureSoundLevelUpdate, this, &ZegoAudioLiveDialog::OnCaptureSoundLevelUpdate);
	connect(GetAVSignal(), &QZegoSDKSignal::sigSoundLevelUpdate, this, &ZegoAudioLiveDialog::OnSoundLevelUpdate);
	connect(GetAVSignal(), &QZegoSDKSignal::sigStreamExtraInfoUpdated, this, &ZegoAudioLiveDialog::OnStreamExtraInfoUpdated);
	connect(GetAVSignal(), &QZegoSDKSignal::sigAVKitEvent, this, &ZegoAudioLiveDialog::OnAVKitEvent);

	//设备变更（改变）
	connect(ui.m_cbMicroPhone, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchAudioInputDevice(int)));
	connect(ui.m_cbSpeaker, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchAudioOutputDevice(int)));

	connect(ui.m_sliderMic, SIGNAL(valueChanged(int)), this, SLOT(OnMicVolumeChanged(int)));
	connect(ui.m_sliderSpeaker, SIGNAL(valueChanged(int)), this, SLOT(OnSpeakerVolumeChanged(int)));

	//初始化重试线程
	m_retryThread = new QThread;

	//在VideoTalk中均以SettingsPtr操作
	m_pAVSettings = mConfig.GetAudioSettings();
	//读取配置中用户ID和用户名
	m_strCurUserID = mConfig.GetUserId();
	m_strCurUserName = mConfig.GetUserName();
	
	this->installEventFilter(this);
	//初始化网格布局
	m_gridLayout = new QGridLayout;

	m_device = new ZegoDeviceManager;
	connect(m_device, &ZegoDeviceManager::sigMicVolumeMute, this, &ZegoAudioLiveDialog::OnMicVolumeMute);
	connect(m_device, &ZegoDeviceManager::sigSpeakerVolumeMute, this, [this](bool isMute) {ui.m_switchSpeaker->setChecked(!isMute); });
	connect(m_device, &ZegoDeviceManager::sigDeviceAdded, this, &ZegoAudioLiveDialog::OnDeviceAdded);
	connect(m_device, &ZegoDeviceManager::sigDeviceDeleted, this, &ZegoAudioLiveDialog::OnDeviceDeleted);
	connect(m_device, &ZegoDeviceManager::sigMicIdChanged, this, &ZegoAudioLiveDialog::OnMicIdChanged);
	connect(m_device, &ZegoDeviceManager::sigSpeakerIdChanged, this, &ZegoAudioLiveDialog::OnSpeakerIdChanged);
}

ZegoAudioLiveDialog::~ZegoAudioLiveDialog()
{
	log_string_notice(qtoc(QStringLiteral("[%1]: audio live dialog destroy").arg(__FUNCTION__)));

	AudioViewList.clear();
	playViewList.clear();

	delete m_device;
	m_device = nullptr;

	
	delete m_gridLayout;
	m_gridLayout = nullptr;
	
	delete m_retryThread;
	m_retryThread = nullptr;

	emit sigCloseView();
}

void ZegoAudioLiveDialog::initDialog()
{
	log_string_notice(qtoc(QStringLiteral("[%1]: audio live dialog init").arg(__FUNCTION__)));

	initButtonIcon();
	//初始化麦克风扬声器的ComboBox
	initComboBox();

	ui.m_lbRetryPublish->setVisible(false);

	//成员列表初始化
	m_memberModel = new QStringListModel(this);
	ui.m_listMember->setModel(m_memberModel);
	ui.m_listMember->setItemDelegate(new NoFocusFrameDelegate(this));
	ui.m_listMember->setEditTriggers(QAbstractItemView::NoEditTriggers);

	//日志列表初始化
	m_logModel = new QStandardItemModel(this);
	ui.m_listLog->setModel(m_logModel);
	ui.m_listLog->horizontalHeader()->setVisible(false);
	ui.m_listLog->verticalHeader()->setVisible(false);
	ui.m_listLog->verticalHeader()->setDefaultSectionSize(21);
	ui.m_listLog->setColumnWidth(0, 300);
	//读取标题内容
	QString strTitle = QString(tr("当前房间号：%1")).arg(m_pChatRoom->getRoomId());
	ui.m_lbRoomName->setText(strTitle);

	ui.m_edInput->setEnabled(false);
	//剩余能用的AVView
	for (int i = MAX_PLAY_COUNT; i >= 0; i--)
		m_avaliableView.push_front(i);

	//枚举音频设备
	GetAudioDevice();

	//设置手动推流
	//AUDIOROOM::SetManualPublish(true);

	ui.m_sliderMic->setValue(m_device->GetMicVolume());
	ui.m_sliderSpeaker->setValue(m_device->GetPlayVolume());

	//开启麦克风声音监听
	SOUNDLEVEL::StartSoundLevelMonitor();

	m_strRoomID = m_pChatRoom->getRoomId();
	if (!AUDIOROOM::LoginRoom(qtoc(m_strRoomID)))
	{
		QMessageBox::information(NULL, tr("提示"), tr("进入房间失败"));
	}
	
	addLogString(tr("开始登陆房间"));

}

void ZegoAudioLiveDialog::initButtonIcon()
{
	ui.m_bClose->setButtonIcon("close");
	ui.m_bMin->setButtonIcon("min");
	ui.m_bMax->setButtonIcon("max");

	ui.m_switchMic->setButtonIcon("mic_icon");
	ui.m_switchSpeaker->setButtonIcon("speaker_icon");
}

void ZegoAudioLiveDialog::GetAudioDevice()
{
	//枚举音频输入以及输出设备
	m_device->EnumAudioDeviceList();

	//音频输入设备
	m_vecAudioInputDeviceList = m_device->GetAudioInputDeviceList();

	for (int i = 0; i < m_vecAudioInputDeviceList.size(); i++)
	{
		insertStringListModelItem(m_cbMircoPhoneModel, m_vecAudioInputDeviceList.at(i).deviceName, m_cbMircoPhoneModel->rowCount());
	}

	int mic_index = m_device->GetAudioInputDeviceIndex();
	if (mic_index >= 0)
		ui.m_cbMicroPhone->setCurrentIndex(m_device->GetAudioInputDeviceIndex());


	//音频输出设备
	m_vecAudioOutputDeviceList = m_device->GetAudioOutputDeviceList();

	for (int i = 0; i < m_vecAudioOutputDeviceList.size(); i++)
	{
		insertStringListModelItem(m_cbSpeakerModel, m_vecAudioOutputDeviceList.at(i).deviceName, m_cbSpeakerModel->rowCount());
	}

	int speaker_index = m_device->GetAudioOutputDeviceIndex();
	if (speaker_index >= 0)
		ui.m_cbSpeaker->setCurrentIndex(m_device->GetAudioOutputDeviceIndex());
	
}

void ZegoAudioLiveDialog::StartPublishStream()
{
	log_string_notice(qtoc(QStringLiteral("[%1]: enter start publishing").arg(__FUNCTION__)));

	QString strStreamId;
#ifdef Q_OS_WIN
	strStreamId = QString("s-windows-audio-%1").arg(m_strCurUserID);
#else
	strStreamId = QString("s-mac-audio-%1").arg(m_strCurUserID);
#endif

	StreamPtr pPublishStream(new QZegoStreamModel(m_strPublishStreamID, m_strCurUserID, m_strCurUserName, "", true));

	m_pChatRoom->addStream(pPublishStream);

	//推流前调用双声道
	//AUDIOROOM::SetAudioChannelCount(2);

	int nIndex = -1;
	if (m_avaliableView.size() > 0)
	{

		nIndex = takeLeastAvaliableViewIndex();
		pPublishStream->setPlayView(nIndex);
		ZegoAudioView * view = addAudioView(m_strCurUserName, nIndex, true, m_bCKEnableMic);
		m_publishView = view;
		
		m_anchorStreamInfo = pPublishStream;
		
		m_bIsPublishing = true;
		addLogString(tr("开始推流"));
		
	}

	log_string_notice(qtoc(QStringLiteral("[%1]: start publish stream. play view index: %2, play stream ID: %3")
		.arg(__FUNCTION__)
		.arg(nIndex)
		.arg(strStreamId)
	));
}

void ZegoAudioLiveDialog::StopPublishStream(const QString& streamID)
{
	if (streamID.size() == 0)
	{ 
		log_string_notice(qtoc(QStringLiteral("[%1]: stop publish stream failed, stream ID is empty").arg(__FUNCTION__)));
		return;
	}

	log_string_notice(qtoc(QStringLiteral("[%1]: enter stop publishing").arg(__FUNCTION__)));
	
	int nIndex = m_anchorStreamInfo->getPlayView();
	ZegoAudioView *view = removeAudioView(nIndex);
	view->deleteLater();

	AUDIOROOM::StopPublish();
	m_bIsPublishing = false;
	StreamPtr pStream = m_pChatRoom->removeStream(streamID);
	FreeAudioView(pStream);

	m_strPublishStreamID = "";

	log_string_notice(qtoc(QStringLiteral("[%1]: stop publish stream. play view index: %2, play stream ID: %3")
		.arg(nIndex)
		.arg(streamID)
	));
}

void ZegoAudioLiveDialog::StartPlayStream(StreamPtr stream)
{
	if (stream == nullptr) 
	{ 
		log_string_notice(qtoc(QStringLiteral("[%1]: start playing stream failed, stream is empty").arg(__FUNCTION__)));
		return;
	}

	log_string_notice(qtoc(QStringLiteral("[%1]: enter start playing").arg(__FUNCTION__)));
	m_pChatRoom->addStream(stream);

	int nIndex = -1;
	QString streamId = stream->getStreamId();
	QString extraInfo = stream->getExtraInfo();

	if (m_avaliableView.size() > 0)
	{
		int nIndex = takeLeastAvaliableViewIndex();
		stream->setPlayView(nIndex);

		QJsonDocument jsonDocument = QJsonDocument::fromJson(extraInfo.toLocal8Bit().data());
		bool mic_enabled = true;
		if (!jsonDocument.isNull())
		{
			QJsonObject jsonObject = jsonDocument.object();
			QJsonObject enable_mic = jsonObject["stream_state"].toObject();
			mic_enabled = enable_mic["enable_mic"].toBool();
		}

		ZegoAudioView *view = addAudioView(stream->getUserName(), nIndex, false, mic_enabled);
		playViewList[stream->getStreamId()] = view;
	}

	log_string_notice(qtoc(QStringLiteral("[%1]: start playing stream. play view index: %2, play stream ID: %3, play stream extraInfo: %4")
		.arg(__FUNCTION__)
		.arg(nIndex)
		.arg(streamId)
		.arg(extraInfo)
	));
}

void ZegoAudioLiveDialog::StopPlayStream(const QString& streamID)
{
	if (streamID.size() == 0) 
	{ 
		log_string_notice(qtoc(QStringLiteral("[%1]: stop playing stream failed, stream ID is empty").arg(__FUNCTION__)));
		return; 
	}

	log_string_notice(qtoc(QStringLiteral("[%1]: enter stop playing").arg(__FUNCTION__)));
	StreamPtr curStream;
	for (auto stream : m_pChatRoom->getStreamList())
	{
		if (streamID == stream->getStreamId())
			curStream = stream;
	}

	int nIndex = curStream->getPlayView();
    if (curStream)
    {
		ZegoAudioView *view = removeAudioView(nIndex);
		view->deleteLater();
    }

	//LIVEROOM::StopPlayingStream(streamID.toStdString().c_str());

	StreamPtr pStream = m_pChatRoom->removeStream(streamID);
	FreeAudioView(pStream);

	log_string_notice(qtoc(QStringLiteral("[%1]: stop playing stream. play view index: %2, play stream ID: %3")
	.arg(nIndex)
	.arg(streamID)
	));
}

void ZegoAudioLiveDialog::addLogString(QString log)
{
	QDateTime dateTime;
	QTime time;
	QDate date;
	dateTime.setTime(time.currentTime());
	dateTime.setDate(date.currentDate());
	QString strDate = dateTime.toString("[hh-mm-ss-zzz]: ");

	QStandardItem *item = new QStandardItem;
	m_logModel->insertRow(0, item);
	QModelIndex index = m_logModel->indexFromItem(item);

	ZegoLogLabel *label = new ZegoLogLabel;
	label->setTextContent(strDate, log);
	
	
	ui.m_listLog->setIndexWidget(index, label);

	if (label->getHeightNum() > 1)
	    ui.m_listLog->resizeRowToContents(0);

	qDebug() << log;
	
}

void ZegoAudioLiveDialog::initComboBox()
{

	m_cbMircoPhoneModel = new QStringListModel(this);

	m_cbMircoPhoneModel->setStringList(m_MircoPhoneList);

	m_cbMircoPhoneListView = new QListView(this);
	ui.m_cbMicroPhone->setView(m_cbMircoPhoneListView);
	ui.m_cbMicroPhone->setModel(m_cbMircoPhoneModel);
	ui.m_cbMicroPhone->setItemDelegate(new NoFocusFrameDelegate(this));

	m_cbSpeakerModel = new QStringListModel(this);

	m_cbSpeakerModel->setStringList(m_speakerList);

	m_cbSpeakerListView = new QListView(this);
	ui.m_cbSpeaker->setView(m_cbSpeakerListView);
	ui.m_cbSpeaker->setModel(m_cbSpeakerModel);
	ui.m_cbSpeaker->setItemDelegate(new NoFocusFrameDelegate(this));
}

void ZegoAudioLiveDialog::insertStringListModelItem(QStringListModel * model, QString name, int size)
{
	if (model == nullptr)
		return;

	int row = size;
	model->insertRows(row, 1);
	QModelIndex index = model->index(row);
	model->setData(index, name);

}

void ZegoAudioLiveDialog::removeStringListModelItem(QStringListModel * model, QString name)
{
	if (model == nullptr)
		return;

	if (model->rowCount() > 0)
	{
		int curIndex = -1;
		QStringList list = model->stringList();
		for (int i = 0; i < list.size(); i++)
		{
			if (list[i] == name)
				curIndex = i;
		}

		model->removeRows(curIndex, 1);
	}

}

int ZegoAudioLiveDialog::takeLeastAvaliableViewIndex()
{
	int min = m_avaliableView[0];
	int minIndex = 0;
	for (int i = 1; i < m_avaliableView.size(); i++)
	{
		if (m_avaliableView[i] < min)
		{
			min = m_avaliableView[i];
			minIndex = i;
		}
	}

	m_avaliableView.takeAt(minIndex);
	return min;
}

ZegoAudioView * ZegoAudioLiveDialog::addAudioView(const QString& userName, int addViewIndex, bool isPublisher, bool isMicEnabled)
{
	ZegoAudioView *newView = new ZegoAudioView(userName, isPublisher, isMicEnabled);
	
	newView->setViewIndex(addViewIndex);
	AudioViewList.push_back(newView);

	updateViewLayout(AudioViewList.size());

	return newView;
}

ZegoAudioView * ZegoAudioLiveDialog::removeAudioView(int removeViewIndex)
{
	int viewIndex = -1;
	for (int i = 0; i < AudioViewList.size(); i++)
	{
		if (AudioViewList[i]->getViewIndex() == removeViewIndex)
		{
			viewIndex = i;
			break;
		}
	}

	ZegoAudioView *popView = AudioViewList.takeAt(viewIndex);
	//popView->deleteLater();

	updateViewLayout(AudioViewList.size());

	return popView;
}

void ZegoAudioLiveDialog::updateViewLayout(int viewCount)
{

	for (int i = 0; i < viewCount; i++)
		m_gridLayout->removeWidget(AudioViewList[i]);

	m_gridLayout->deleteLater();

	m_gridLayout = new QGridLayout();
	m_gridLayout->setSpacing(5);
    m_gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);

    ui.zoneLiveViewHorizontalLayout->addLayout(m_gridLayout);

	for (int i = 0; i < viewCount; i++)
	{
		int row, col;
		row = i / 4;
		col = i % 4;
		
		qDebug() << "current row = " << row << " col = " << col;
		m_gridLayout->addWidget(AudioViewList[i], row, col, 1, 1);
	}
	//剩余空间补空白
	for (int i = viewCount; i < 12; i++)
	{
		int row, col;
		row = i / 4;
		col = i % 4;

		m_gridLayout->setRowStretch(row, 1);
		m_gridLayout->setColumnStretch(col, 1);
	}

}

void ZegoAudioLiveDialog::FreeAudioView(StreamPtr stream)
{
	if (stream == nullptr)
	{
		return;
	}

	int nIndex = stream->getPlayView();

	m_avaliableView.push_front(nIndex);

}

void ZegoAudioLiveDialog::UninitDialog()
{
	log_string_notice(qtoc(QStringLiteral("[%1]: audio live dialog uninit").arg(__FUNCTION__)));

	for (auto& stream : m_pChatRoom->getStreamList())
	{
		if (stream != nullptr){
			if (stream->isCurUserCreated())
			{
				StopPublishStream(stream->getStreamId());
			}
			else
			{
				StopPlayStream(stream->getStreamId());
			}
		}
	}

	roomMemberDelete(m_strCurUserName);

	//关闭麦克风声音监听
	SOUNDLEVEL::StopSoundLevelMonitor();

	AUDIOROOM::LogoutRoom();

	//释放堆内存
	delete m_cbMircoPhoneListView;
	delete m_memberModel;
	delete m_cbMircoPhoneModel;
	delete m_gridLayout;
	//指针置为空
	m_cbMircoPhoneListView = nullptr;
	m_memberModel = nullptr;
	m_cbMircoPhoneModel = nullptr;
	m_gridLayout = nullptr;
}

void ZegoAudioLiveDialog::roomMemberAdd(QString userName)
{
	if (m_memberModel == nullptr)
		return;

	insertStringListModelItem(m_memberModel, userName, m_memberModel->rowCount());
	ui.m_tabCommonAndUserList->setTabText(1, QString(tr("成员(%1)").arg(m_memberModel->rowCount())));
}

void ZegoAudioLiveDialog::roomMemberDelete(QString userName)
{
	if (m_memberModel == nullptr)
		return;

	removeStringListModelItem(m_memberModel, userName);
	ui.m_tabCommonAndUserList->setTabText(1, QString(tr("成员(%1)").arg(m_memberModel->rowCount())));
}

//-----------------------------------------------UI回调----------------------------------------------------------
void ZegoAudioLiveDialog::on_m_bClose_clicked()
{
	this->close(); 
}

void ZegoAudioLiveDialog::on_m_bMax_clicked()
{
	if (m_isMax)
	{
		this->showNormal();
		m_isMax = false;
	}
	else
	{
		this->showMaximized();
		m_isMax = true;
	}
}

void ZegoAudioLiveDialog::on_m_bMin_clicked()
{
	this->showMinimized();
}

void ZegoAudioLiveDialog::OnProgChange()
{
	//ui.m_bProgMircoPhone->setProgValue(AUDIOROOM::GetCaptureSoundLevel());
	//ui.m_bProgMircoPhone->update();
}

void ZegoAudioLiveDialog::OnSwitchAudioInputDevice(int id)
{
	log_string_notice(qtoc(QStringLiteral("[%1]: switch audio input device, index: %2").arg(__FUNCTION__).arg(id)));

	if (id < 0)
		return;

	if (id < m_vecAudioInputDeviceList.size())
	{
		m_device->SetMicrophoneIdByIndex(id);
		QString microphoneId = m_device->GetAudioInputDeviceId();

		AUDIOROOM::SetAudioDevice(AV::AudioDevice_Input, qtoc(microphoneId));
		m_pAVSettings->SetMicrophoneId(microphoneId);
		//QString strElidedText = ui.m_cbMicroPhone->fontMetrics().elidedText(microphoneId, Qt::ElideRight, 240, Qt::TextShowMnemonic);
		//ui.m_cbMicroPhone->setEditText(strElidedText);
		//ui.m_cbMicroPhone->setCurrentIndexWithoutSignal(id);
	}
}

void ZegoAudioLiveDialog::OnSwitchAudioOutputDevice(int id)
{
	log_string_notice(qtoc(QStringLiteral("[%1]: switch audio output device, index: %2").arg(__FUNCTION__).arg(id)));

	if (id < 0)
		return;

	if (id < m_vecAudioOutputDeviceList.size())
	{
		m_device->SetSpeakerIdByIndex(id);
		QString speakerId = m_device->GetAudioOutputDeviceId();

		AUDIOROOM::SetAudioDevice(AV::AudioDevice_Output, qtoc(speakerId));
		m_pAVSettings->SetSpeakerId(speakerId);
		//QString strElidedText = ui.m_cbMicroPhone->fontMetrics().elidedText(speakerId, Qt::ElideRight, 240, Qt::TextShowMnemonic);
		//ui.m_cbSpeaker->setEditText(strElidedText);
		//ui.m_cbSpeaker->setCurrentIndexWithoutSignal(id);
	}
}

void ZegoAudioLiveDialog::OnMicIdChanged(const QString& micId)
{
	QString curDeviceId = micId;

	if (curDeviceId.isEmpty())
	{
		AUDIOROOM::SetAudioDevice(ZEGO::AV::AudioDeviceType::AudioDevice_Input, nullptr);
	}
	else
	{
		AUDIOROOM::SetAudioDevice(ZEGO::AV::AudioDeviceType::AudioDevice_Input, qtoc(curDeviceId));
	}

	m_pAVSettings->SetMicrophoneId(curDeviceId);

}

void ZegoAudioLiveDialog::OnSpeakerIdChanged(const QString& speakerId)
{
	QString curDeviceId = speakerId;

	if (curDeviceId.isEmpty())
	{
		AUDIOROOM::SetAudioDevice(ZEGO::AV::AudioDeviceType::AudioDevice_Output, nullptr);
	}
	else
	{
		AUDIOROOM::SetAudioDevice(ZEGO::AV::AudioDeviceType::AudioDevice_Output, qtoc(curDeviceId));
	}

	m_pAVSettings->SetSpeakerId(curDeviceId);
}

void ZegoAudioLiveDialog::OnMicVolumeMute(bool isMute)
{
	ui.m_switchMic->setChecked(!isMute);
	m_bCKEnableMic = m_device->GetMicEnabled();

	m_publishView->SetMicEnabled(!isMute);
}

void ZegoAudioLiveDialog::OnMicVolumeChanged(int v)
{
	m_device->SetMicVolume(v);
}

void ZegoAudioLiveDialog::OnSpeakerVolumeChanged(int v)
{
	m_device->SetPlayVolume(v);
}

void ZegoAudioLiveDialog::OnDeviceAdded(int type, QString deviceName)
{
	if (type == TYPE_AUDIO_OUTPUT)
		return;

	int row = m_cbMircoPhoneModel->rowCount();
	m_cbMircoPhoneModel->insertRows(row, 1);
	QModelIndex index = m_cbMircoPhoneModel->index(row);
	m_cbMircoPhoneModel->setData(index, deviceName);
}

void ZegoAudioLiveDialog::OnDeviceDeleted(int type, int index)
{
	if (type == TYPE_AUDIO_OUTPUT)
		return;

	m_cbMircoPhoneModel->removeRow(index);
}

void ZegoAudioLiveDialog::on_m_switchMic_clicked()
{
	if (ui.m_switchMic->isChecked())
	{

		m_bCKEnableMic = true;
	}
	else
	{

		m_bCKEnableMic = false;
	}

	m_device->SetMicEnabled(m_bCKEnableMic);
	m_publishView->SetMicEnabled(m_bCKEnableMic);
	log_string_notice(qtoc(QStringLiteral("[%1]: set microphone enabled: %2").arg(__FUNCTION__).arg(m_bCKEnableMic)));

	//同步该用户的麦克风状态到房间的其他人里
	QJsonObject stream_state;
	QJsonObject mic_state;
	mic_state.insert("enable_mic", m_bCKEnableMic);
	stream_state.insert("stream_state", mic_state);
	QString json = QString(QJsonDocument(stream_state).toJson()).simplified();

	AUDIOROOM::SetPublishStreamExtraInfo(qtoc(json));
}

void ZegoAudioLiveDialog::on_m_switchSpeaker_clicked()
{

	if (ui.m_switchSpeaker->isChecked())
	{

		m_bCKEnableSpeaker = true;
	}
	else
	{

		m_bCKEnableSpeaker = false;
	}

	m_device->SetSpeakerEnabled(m_bCKEnableSpeaker);
	log_string_notice(qtoc(QStringLiteral("[%1]: set speaker enabled: %2").arg(__FUNCTION__).arg(m_bCKEnableSpeaker)));

}

//-----------------------------------------------SDK回调-------------------------------------------------------------
void ZegoAudioLiveDialog::OnLoginRoom(int errorCode, const QString& strRoomID)
{
	
	if (errorCode != 0)
	{
		addLogString(tr("登陆房间失败. error: %1").arg(errorCode));
		QMessageBox::information(NULL, tr("提示"), tr("登陆房间失败. error: %1").arg(errorCode));
		this->close();
		return;
	}

	addLogString(tr("登陆房间成功. roomID: %1").arg(strRoomID));

	//加入房间列表
	roomMemberAdd(m_strCurUserName);
	//登录房间成功即推流以及拉流
	StartPublishStream();
}

void ZegoAudioLiveDialog::OnStreamUpdated(const QString& strRoomID, StreamPtr pStream, AUDIOROOM::ZegoStreamUpdateType type)
{
	if (pStream == nullptr)
		return;

	if (type == AUDIOROOM::ZegoStreamUpdateType::StreamAdded)
	{
		StartPlayStream(pStream);
		addLogString(tr("新增一条流，流ID: %1").arg(pStream->getStreamId()));
		//insertStringListModelItem(m_memberListModel, QStringLiteral("%1").arg(pStream->getStreamId()), m_memberListModel->rowCount());
		
	}

	if (type == AUDIOROOM::ZegoStreamUpdateType::StreamDeleted)
	{
		StopPlayStream(pStream->getStreamId());
		addLogString(tr("删除一条流，流ID: %1").arg(pStream->getStreamId()));
	}


}

void ZegoAudioLiveDialog::OnPublishStateUpdate(int stateCode, const QString& streamId, StreamPtr streamInfo)
{
	m_strPublishStreamID = streamId;

	if (stateCode == 0)
	{
		
		if (streamInfo != nullptr)
		{

			QString strUrl;
			QString strRtmpUrl = (streamInfo->m_vecRtmpUrls.size() > 0) ?
				streamInfo->m_vecRtmpUrls[0] : "";

			if (!strRtmpUrl.isEmpty())
			{
				strUrl.append("1. ");
				strUrl.append(strRtmpUrl);
				strUrl.append("\r\n");
			}

			
			addLogString(QString("Rtp %1").arg(strRtmpUrl));
			addLogString(tr("推流成功，流ID: %1").arg(streamId));

		}

	}
	else
	{
		addLogString(tr("推流失败,流ID: %1, error: %2").arg(streamId).arg(stateCode));
		
		// 停止预览, 回收view
		//removeAVView(streamInfo->getPlayView());
		StreamPtr pStream = m_pChatRoom->removeStream(streamId);
		//FreeAVView(pStream);
	}
}

void ZegoAudioLiveDialog::OnPlayStateUpdate(int stateCode, StreamPtr pStream)
{
	
	QString streamId = pStream->getStreamId();

	if (stateCode != 0)
	{
		addLogString(tr("播放流失败，流ID: %1, error: %2").arg(streamId).arg(stateCode));
		// 回收view
		StreamPtr pStream = m_pChatRoom->removeStream(streamId);
		//view->SetNetworkEnabled(false);
		//removeAVView(pStream->getPlayView());
		//FreeAVView(pStream);
		return;
	}

	/*QString extraInfo = pStream->getExtraInfo();
	qDebug() << "extraInfo: " << extraInfo;

	QJsonDocument jsonDocument = QJsonDocument::fromJson(extraInfo.toLocal8Bit().data());
	if (!jsonDocument.isNull()) 
	{
		QJsonObject jsonObject = jsonDocument.object();
		QJsonObject enable_mic = jsonObject["stream_state"].toObject();
		bool mic_enabled = enable_mic["enable_mic"].toBool();

		ZegoAudioView *view = playViewList[streamId];
		view->SetMicEnabled(mic_enabled);
	}*/
	
	addLogString(tr("播放流成功，流ID: %1").arg(streamId));
}

void ZegoAudioLiveDialog::OnUserUpdate(QVector<QString> userIDs, QVector<QString> userNames, QVector<int> userFlags, QVector<int> userRoles, unsigned int userCount, AUDIOROOM::ZegoUserUpdateType type)
{
	qDebug() << "onUserUpdate!";

	//全量更新
	if (type == AUDIOROOM::ZegoUserUpdateType::UPDATE_TOTAL){
		//removeAll
		m_memberModel->removeRows(0, m_memberModel->rowCount());

		insertStringListModelItem(m_memberModel, m_strCurUserName, 0);
		for (int i = 0; i < userCount; i++)
		{
			insertStringListModelItem(m_memberModel, userNames[i], m_memberModel->rowCount());
		}
	}
	//增量更新
	else
	{

		for (int i = 0; i < userCount; i++)
		{

			if (userFlags[i] == AUDIOROOM::USER_ADDED)
				insertStringListModelItem(m_memberModel, userNames[i], m_memberModel->rowCount());
			else
				removeStringListModelItem(m_memberModel, userNames[i]);
		}
	}

	ui.m_tabCommonAndUserList->setTabText(1, QString(tr("成员(%1)").arg(m_memberModel->rowCount())));
	ui.m_listMember->update();
}

void ZegoAudioLiveDialog::OnDisconnect(int errorCode, const QString& roomId)
{
	if (m_pChatRoom->getRoomId() == roomId)
	{
		if (ui.m_ProgRetryPublish->isAnimated())
			ui.m_ProgRetryPublish->stopAnimation();

		QMessageBox::information(NULL, tr("提示"), tr("连接失败，error: %1").arg(errorCode));
		this->close();
	}
}

void ZegoAudioLiveDialog::OnKickOut(int reason, const QString& roomId)
{
	if (m_pChatRoom->getRoomId() == roomId)
	{
		QMessageBox::information(NULL, tr("提示"), tr("您已被踢出房间"));
		this->close();
	}
}

void ZegoAudioLiveDialog::OnPlayQualityUpdate(const QString& streamId, double audioKBS, double audioBreakRate, int rtt, int lostRate)
{
	/*StreamPtr pStream = m_pChatRoom->getStreamById(streamId);

	if (pStream == nullptr)
		return;

	int nIndex = pStream->getPlayView();

	if (nIndex < 0 || nIndex > 11)
		return;
		*/
	//AVViews[nIndex]->setCurrentQuality(quality);

	//QVector<QString> q = { QStringLiteral("优"), QStringLiteral("良"), QStringLiteral("中"), QStringLiteral("差") };
	//qDebug() << QStringLiteral("当前窗口") << nIndex << QStringLiteral("的直播质量为") << q[quality];
	ZegoAudioView *playView = playViewList[streamId];
	if (audioKBS == 0)
	{
		if (playView->IsNetworkEnabeld())
		{
			playView->IncreaseWeakNetCount();
			if (playView->GetCurrentWeakCount() == 3)
			{
				playView->SetNetworkEnabled(false);
				playView->ResetWeakNetCount();
			}
		}
	}
	else
	{
		if (!playView->IsNetworkEnabeld())
		{
			playView->ResetWeakNetCount();
			playView->SetNetworkEnabled(true);
		}
	}
	playView->updatePlayQuality(audioKBS, audioBreakRate, rtt, lostRate);

	qDebug() << "play streamId" << streamId << " akbps: " << audioKBS << " audio break: " << audioBreakRate << " rtt: " << rtt << " lost rate:" << lostRate;
}

void ZegoAudioLiveDialog::OnPublishQualityUpdate(const QString& streamId, double audioKBS, int rtt, int lostRate)
{
	/*StreamPtr pStream = m_pChatRoom->getStreamById(streamId);

	if (pStream == nullptr)
		return;

	int nIndex = pStream->getPlayView();

	if (nIndex < 0 || nIndex > 11)
		return;
		*/
	//AVViews[nIndex]->setCurrentQuality(quality);

	//QVector<QString> q = { QStringLiteral("优"), QStringLiteral("良"), QStringLiteral("中"), QStringLiteral("差") };
	//qDebug() << QStringLiteral("当前窗口") << nIndex << QStringLiteral("的直播质量为") << q[quality];

	if (m_strPublishStreamID != streamId)
		return;

	m_publishView->updatePublishQuality(audioKBS, rtt, lostRate);
	//qDebug() << "publish streamId" << streamId << " akbps: " << audioKBS << " rtt: " << rtt << " lost rate:" << lostRate;
}

void ZegoAudioLiveDialog::OnCaptureSoundLevelUpdate(QString streamId, float soundLevel)
{
	
	if (!m_publishView)
		return;

	if (m_strPublishStreamID != streamId)
		return;

	if (m_bCKEnableMic)
		m_publishView->SetProgValue((int)soundLevel);
	else
		m_publishView->SetProgValue(0);

	//ui.m_bProgMircoPhone->setProgValue(soundLevel);
	//ui.m_bProgMircoPhone->update();
}

void ZegoAudioLiveDialog::OnSoundLevelUpdate(QVector< QPair<QString, float> > soundLevelList)
{
	//qDebug() << "soundlevel count: " << soundLevelList.size();

	for (int i = 0; i < soundLevelList.size(); i++)
	{
		QString streamId = soundLevelList.at(i).first;
		int value = soundLevelList.at(i).second;

		ZegoAudioView *view = playViewList[streamId];
		view->SetProgValue(value);
	}
}

void ZegoAudioLiveDialog::OnStreamExtraInfoUpdated(QVector<StreamPtr> streamList, QString strRoomId)
{
	if (strRoomId != m_strRoomID)
		return;

	for (int i = 0; i < streamList.size(); i++)
	{
		QString extraInfo = streamList.at(i)->getExtraInfo();
		if (extraInfo.isEmpty())
			continue;

		QJsonDocument jsonDocument = QJsonDocument::fromJson(extraInfo.toLocal8Bit().data());
		QJsonObject stream_state = jsonDocument.object();

		QJsonObject mic_state = stream_state["stream_state"].toObject();
		bool mic_enabled = mic_state["enable_mic"].toBool();

		QString streamId = streamList.at(i)->getStreamId();
		ZegoAudioView * view = playViewList[streamId];
		view->SetMicEnabled(mic_enabled);
	}
}

void ZegoAudioLiveDialog::OnAVKitEvent(int event)
{
	qDebug() << "event = " << event;
	if (event == AV::Publish_TempDisconnected)
	{
		ui.m_lbRetryPublish->setVisible(true);

		if(!ui.m_ProgRetryPublish->isAnimated())
		    ui.m_ProgRetryPublish->startAnimation();
	}

	if (event == AV::Publish_RetrySuccess)
	{
		if(ui.m_ProgRetryPublish->isAnimated())
			ui.m_ProgRetryPublish->stopAnimation();

		ui.m_lbRetryPublish->setVisible(false);
	}
}

void ZegoAudioLiveDialog::closeEvent(QCloseEvent *event)
{
	UninitDialog();
	ZegoDialog::closeEvent(event);
}

bool ZegoAudioLiveDialog::eventFilter(QObject *target, QEvent *event)
{
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
		//避免按了ESC之后直接退出程序
		if (keyEvent->key() == Qt::Key_Escape) {
			return true;
		}
	}

	return QDialog::eventFilter(target, event);
}
#include "ZegoSettingsDialog.h"
#include "Base/ZegoAudioLiveDefines.h"
#include "Base/IncludeZegoAudioRoomApi.h"

ZegoSettingsDialog::ZegoSettingsDialog(QWidget *parent)
	: ZegoDialog(parent)
{
	ui.setupUi(this);
	
	//只要更改了设置，均触发该信号槽
	connect(this, &ZegoSettingsDialog::sigChangedSettingsConfig, this, &ZegoSettingsDialog::OnChangedSettingsConfig);
}

ZegoSettingsDialog::~ZegoSettingsDialog()
{
	;
}

void ZegoSettingsDialog::initDialog()
{
	initButtonIcon();

	//获取sdk版本号
	ui.m_lbSdkVersion->setText(QString(QLatin1String(AUDIOROOM::GetSDKVersion())));
	ui.m_lbSdkVersion->adjustSize();

	ui.m_bSaveSettings->setEnabled(false);

	m_pCurSettings = mConfig.GetAudioSettings();
	if (m_pCurSettings == nullptr)
	{
		QMessageBox::warning(NULL, tr("警告"), tr("设置页面初始化失败"));
		return;
	}
	m_tmpCurSettings = SettingsPtr::create();
	copySettings(m_tmpCurSettings, m_pCurSettings);

	m_strEdUserId = mConfig.GetUserId();
	m_strEdUserName = mConfig.GetUserName();

	ui.m_strEdUserId->setText(m_strEdUserId);
	ui.m_strEdUserName->setText(m_strEdUserName);
	//Account输入框
	connect(ui.m_strEdUserId, &QLineEdit::textChanged, this, &ZegoSettingsDialog::OnChangedSettingsConfig);
	connect(ui.m_strEdUserName, &QLineEdit::textChanged, this, &ZegoSettingsDialog::OnChangedSettingsConfig);

	m_versionMode = mConfig.getAppVersion().m_versionMode;

	m_tmpVersionMode = m_versionMode;
	m_tmpUseTestEnv = mBase.getUseTestEnv();

	//高级设置app版本为UDP,RTMP，国际版时，不用设置appid和appsign，默认为UDP
	if (m_versionMode == Version::ZEGO_PROTOCOL_UDP || m_versionMode == Version::ZEGO_PROTOCOL_UDP_INTERNATIONAL)
	{
		ui.m_strEdAPPID->setText(QString("%1").arg(mBase.GetAppID()));
		ui.m_strEdAPPSign->setText(tr("AppSign 已设置"));
		ui.m_strEdAPPID->setEnabled(false);
		ui.m_strEdAPPSign->setEnabled(false);
	}
	else if (m_versionMode == Version::ZEGO_PROTOCOL_CUSTOM)
	{
		unsigned long customAppID = mConfig.getAppVersion().m_strAppID;
		QString customAppSign = mConfig.getAppVersion().m_strAppSign;
		if (customAppID == 0 && customAppSign.isEmpty())
		{
			ui.m_strEdAPPID->setText("");
			ui.m_strEdAPPSign->setText("");

		}
		else
		{
			ui.m_strEdAPPID->setText(QString::number(customAppID, 10));
			ui.m_strEdAPPSign->setText(customAppSign);
		}
	}

	if (mBase.getUseTestEnv())
		ui.m_switchTestEnv->setChecked(true);

	qDebug() << "当前App版本为：" << m_versionMode << " AppID: " << theApp.GetBase().GetAppID() << "是否使用测试环境：" << theApp.GetBase().getUseTestEnv();
	
	//初始化app版本的ComboBox
	ui.m_cbAppVersion->addItem(tr("国内版"));
	ui.m_cbAppVersion->addItem(tr("国际版"));
	ui.m_cbAppVersion->addItem(tr("自定义"));
	ui.m_cbAppVersion->setCurrentIndex(m_versionMode);
	//ComboBox选中APP版本
	connect(ui.m_cbAppVersion, SIGNAL(currentIndexChanged(int)), this, SLOT(OnComboBoxCheckAppVersion(int)));


}

void ZegoSettingsDialog::initButtonIcon()
{
	ui.m_bClose->setButtonIcon("close");
	ui.m_bMin->setButtonIcon("min");

	ui.m_switchTestEnv->setButtonIcon("switch");
}

QVector<QString> ZegoSettingsDialog::handleAppSign(QString appSign)
{
	QVector<QString> vecAppSign;
	appSign = appSign.simplified();
	appSign.remove(",");
	appSign.remove(" ");
	
	for (int i = 0; i < appSign.size(); i += 4)
	{
		QString hexSign = appSign.mid(i, 4);
		hexSign.remove("0x");
		hexSign.toUpper();
		vecAppSign.append(hexSign);
	}
	
	return vecAppSign;
}

void ZegoSettingsDialog::copySettings(SettingsPtr dst, SettingsPtr src)
{
	if (dst == nullptr || src == nullptr)
		return;

	dst->SetMicrophoneId(src->GetMircophoneId());
}

//UI信号槽回调
void ZegoSettingsDialog::OnChangedSettingsConfig()
{
	ui.m_bSaveSettings->setEnabled(true);
	m_isConfigChanged = true;
}

void ZegoSettingsDialog::on_m_bUploadLog_clicked()
{
	AUDIOROOM::UploadLog();
	QMessageBox::information(NULL, tr("提示"), tr("日志上传成功"));
}

void ZegoSettingsDialog::on_m_bClose_clicked()
{
	this->close();
}

void ZegoSettingsDialog::on_m_bMin_clicked()
{
	this->showMinimized();
}

void ZegoSettingsDialog::on_m_bSaveSettings_clicked()
{
	//log_string_notice(qtoc(QStringLiteral("[%1]: save settings changes.").arg(__FUNCTION__)));

	//若无设置更改，直接返回
	if (!m_isConfigChanged)
		return;

	//先卸载SDK
	if (m_isNeedReInstallSDK)
	mBase.UninitAVSDK();

	m_strEdUserId = ui.m_strEdUserId->text();
	m_strEdUserName = ui.m_strEdUserName->text();

	mConfig.SetUserId(m_strEdUserId);
	mConfig.SetUserName(m_strEdUserName);

	
	//若更改了测试环境按钮设置,需要重新设置参数
	if (m_tmpUseTestEnv != m_isUseTestEnv)
	{
		mBase.setIsTestEnv(m_tmpUseTestEnv);
		m_isUseTestEnv = m_tmpUseTestEnv;
	}

	mConfig.SetUseTestEnv(m_isUseTestEnv);

	mConfig.SetAudioSettings(m_tmpCurSettings);
	copySettings(m_pCurSettings, m_tmpCurSettings);

	unsigned long appId = 0;
	unsigned char *appSign = NULL;
	int signLen = 0;
	//若更改了App版本，或者在本文中重新输入了自定义appid，则在保存时尝试重新InitSDK
	if (m_tmpVersionMode != m_versionMode || m_isCustomAppTextChanged)
	{
		m_isCustomAppTextChanged = false;
		AppVersion saveVersion = mConfig.getAppVersion();
		mBase.setKey(m_tmpVersionMode);

		if (m_tmpVersionMode == ZEGO_PROTOCOL_UDP || m_tmpVersionMode == ZEGO_PROTOCOL_UDP_INTERNATIONAL)
		{
			//saveVersion.m_strAppID = 0;
			//saveVersion.m_strAppSign = "";	
		}
		else if (m_tmpVersionMode == ZEGO_PROTOCOL_CUSTOM)
	    {
		    appId = ui.m_strEdAPPID->text().toUInt();
		    QString strAppSign = ui.m_strEdAPPSign->text();
		    QVector<QString> vecAppSign = handleAppSign(strAppSign);

			int len = vecAppSign.size() > 32 ? 32 : vecAppSign.size();
			signLen = vecAppSign.size();

		    appSign = new unsigned char[32];
		    for (int i = 0; i < len; i++)
		    {
			    bool ok;
			    appSign[i] = (unsigned char)vecAppSign[i].toInt(&ok, 16);
		    }
		   
			saveVersion.m_strAppID = appId;
			saveVersion.m_strAppSign = strAppSign;

			mBase.setCustomAppID(appId);
			mBase.setCustomAppSign(appSign);
	    }
		saveVersion.m_versionMode = m_tmpVersionMode;
		mConfig.setAppVersion(saveVersion);
	}

	//根据用户所改变的设定重新InitSDK
	if (m_isNeedReInstallSDK)
	{
		if (m_tmpVersionMode == ZEGO_PROTOCOL_UDP || m_tmpVersionMode == ZEGO_PROTOCOL_UDP_INTERNATIONAL)
			theApp.GetBase().InitAVSDK(mConfig.GetAudioSettings(), m_strEdUserId, m_strEdUserName);
		else if(m_tmpVersionMode == ZEGO_PROTOCOL_CUSTOM && signLen == 32)
			theApp.GetBase().InitAVSDKofCustom(mConfig.GetAudioSettings(), m_strEdUserId, m_strEdUserName, appId, appSign, signLen);
	}

	mConfig.SaveConfig();

	m_isConfigChanged = false;
	m_versionMode = m_tmpVersionMode;
	m_isUseTestEnv = m_tmpUseTestEnv;
	//ui.m_lbTitle->setText(tr("设置"));

	//释放临时堆空间
	if (appSign != NULL)
	{
		delete[]appSign;
		appSign = NULL;
	}

	QMessageBox::information(NULL, tr("提示"), tr("保存配置成功"));
	ui.m_bSaveSettings->setEnabled(false);
}

void ZegoSettingsDialog::on_m_switchTestEnv_clicked()
{
	if (ui.m_switchTestEnv->isChecked())
	{
		qDebug() << "TestEnv checked!";
		m_tmpUseTestEnv = true;

	}
	else
	{
		qDebug() << "TestEnv unChecked!";
		m_tmpUseTestEnv = false;

	}

	m_isNeedReInstallSDK = true;
	emit sigChangedSettingsConfig();
}

void ZegoSettingsDialog::OnComboBoxCheckAppVersion(int id)
{
	if (id == ZEGO_PROTOCOL_UDP || id == ZEGO_PROTOCOL_UDP_INTERNATIONAL)
	{
		ui.m_strEdAPPID->setText(QString("%1").arg(mBase.GetAppIDwithKey(id)));
		ui.m_strEdAPPSign->setText(tr("AppSign 已设置"));
		ui.m_strEdAPPID->setEnabled(false);
		ui.m_strEdAPPSign->setEnabled(false);
		
	}
	else
	{
		unsigned long customAppID = mConfig.getAppVersion().m_strAppID;
		QString customAppSign = mConfig.getAppVersion().m_strAppSign;
		if (customAppID == 0 && customAppSign.isEmpty())
		{
			ui.m_strEdAPPID->setText("");
			ui.m_strEdAPPSign->setText("");
		}
		else
		{
			ui.m_strEdAPPID->setText(QString::number(customAppID, 10));
			ui.m_strEdAPPSign->setText(customAppSign);
			ui.m_strEdAPPID->setFocus();
		}

		ui.m_strEdAPPID->setEnabled(true);
		ui.m_strEdAPPSign->setEnabled(true);
		ui.m_strEdAPPID->setFocus();
	}


	//暂时保存设置
	m_tmpVersionMode = (Version)id;

	m_isNeedReInstallSDK = true;
	emit sigChangedSettingsConfig();
}



void ZegoSettingsDialog::closeEvent(QCloseEvent *event)
{
	if (m_isConfigChanged)
	{
		QMessageBox::StandardButton button;
		button = QMessageBox::question(this, tr("退出设置"),
			QString(tr("确认不保存设置吗?")),
			QMessageBox::Yes | QMessageBox::No);
		if (button == QMessageBox::No) {
			event->ignore();  //忽略退出信号，程序继续运行
		}
		else if (button == QMessageBox::Yes) {
			event->accept();  //接受退出信号，程序退出
		}
	}
	
}


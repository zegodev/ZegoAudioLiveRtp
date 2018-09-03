#include "ZegoMainDialog.h"
#include "Base/IncludeZegoAudioRoomApi.h"
#include "Base/ZegoAudioLiveDefines.h"
#include "Dialog/ZegoSettingsDialog.h"
#include "Dialog/ZegoAudioLiveDialog.h"

#include <QDesktopServices>

ZegoMainDialog::ZegoMainDialog(QWidget *parent)
	: ZegoDialog(parent)
{
	ui.setupUi(this);
	log_string_notice(qtoc(QStringLiteral("[%1]: main dialog create").arg(__FUNCTION__)));

	//不输入房间号不能进入房间
	ui.m_bEnterRoom->setEnabled(false);
	connect(ui.m_edRoomID, &QLineEdit::textChanged, this, [this] { emit sigCheckEnterRoom(); });

	connect(this, &ZegoMainDialog::sigCheckEnterRoom, this, &ZegoMainDialog::OnCheckEnterRoom);

	ui.m_lbVersion->setText(QStringLiteral("v %1").arg(APP_VERSION));
}

ZegoMainDialog::~ZegoMainDialog()
{
	log_string_notice(qtoc(QStringLiteral("[%1]: main dialog destroy").arg(__FUNCTION__)));
	mBase.UninitAVSDK();
}

void ZegoMainDialog::initDialog()
{
	log_string_notice(qtoc(QStringLiteral("[%1]: main dialog init").arg(__FUNCTION__)));

	initButtonIcon();

	//从用户配置文件中读取配置信息，若找不到则新建配置文件
	mConfig.LoadConfig();

	m_strEdUserId = mConfig.GetUserId();
	m_strEdUserName = mConfig.GetUserName();

	bool isUseTestEnv = mConfig.GetUseTestEnv();
	mBase.setIsTestEnv(isUseTestEnv);

	AppVersion appVersion = mConfig.getAppVersion();
	mBase.setKey(appVersion.m_versionMode);

	updateAppVersionTitle();

	//对于AudioSettings来说，属性只有userID，userName和mircoPhoneID
	SettingsPtr pCurSettings = mConfig.GetAudioSettings();

	if (!pCurSettings)
		return;

	if (appVersion.m_versionMode == ZEGO_PROTOCOL_CUSTOM)
	{
		QVector<QString> vecAppSign = handleAppSign(mConfig.getAppVersion().m_strAppSign);
		unsigned long appId = mConfig.getAppVersion().m_strAppID;
		unsigned char *appSign = NULL;
		int signLen = 0;

		int len = vecAppSign.size() > 32 ? 32 : vecAppSign.size();
		signLen = vecAppSign.size();

		appSign = new unsigned char[32];
		for (int i = 0; i < len; i++)
		{
			bool ok;
			appSign[i] = (unsigned char)vecAppSign[i].toInt(&ok, 16);
		}

		mBase.InitAVSDKofCustom(pCurSettings, m_strEdUserId, m_strEdUserName, appId, appSign, signLen);
	}
	else
	{
		mBase.InitAVSDK(pCurSettings, m_strEdUserId, m_strEdUserName);
	}
}

void ZegoMainDialog::updateAppVersionTitle()
{
	AppVersion appVersion = mConfig.getAppVersion();
	switch (appVersion.m_versionMode)
	{
	case ZEGO_PROTOCOL_UDP:
		ui.m_title->setText(tr("AudioLive (国内版)"));
		break;
	case ZEGO_PROTOCOL_UDP_INTERNATIONAL:
		ui.m_title->setText(tr("AudioLive (国际版)"));
		break;
	case ZEGO_PROTOCOL_CUSTOM:
		ui.m_title->setText(tr("AudioLive (自定义)"));
		break;
	default:
		ui.m_title->setText(tr("AudioLive (未知)"));
		break;
	}
}

QVector<QString> ZegoMainDialog::handleAppSign(QString appSign)
{
	QVector<QString> vecAppSign;
	appSign = appSign.simplified();
	appSign.remove(",");
	appSign.remove(" ");

	for (int i = 0; i < appSign.size(); i += 4)
	{
		//qDebug() << "curString = " << appSign.mid(i, 4);
		QString hexSign = appSign.mid(i, 4);
		hexSign.remove("0x");
		hexSign.toUpper();
		vecAppSign.append(hexSign);
	}

	return vecAppSign;
}

void ZegoMainDialog::initButtonIcon()
{
	ui.m_bClose->setButtonIcon("close");
	ui.m_bMin->setButtonIcon("min");

	ui.m_bJumpToNet->setButtonIcon("official");
	ui.m_bJumpToNet->setToolTip(tr("关于我们"));
}

void ZegoMainDialog::OnCheckEnterRoom()
{
	QString roomId = ui.m_edRoomID->text();
	roomId = roomId.simplified();

	if (!roomId.isEmpty())
		ui.m_bEnterRoom->setEnabled(true);
	else
		ui.m_bEnterRoom->setEnabled(false);
}

void ZegoMainDialog::on_m_bEnterRoom_clicked()
{
	QString strRoomID = ui.m_edRoomID->text();
	log_string_notice(qtoc(QStringLiteral("[%1]: enter audio live dialog, roomId: %2").arg(__FUNCTION__).arg(strRoomID)));

	RoomPtr pRoom = RoomPtr::create(strRoomID, QString("audio-room"), m_strEdUserId, m_strEdUserName);

	ZegoAudioLiveDialog dialog(pRoom, this);
	connect(&dialog, &ZegoAudioLiveDialog::sigCloseView, this, [this] {this->show(); });

	dialog.initDialog();
	this->hide();
	dialog.exec();
}

void ZegoMainDialog::on_m_bSettings_clicked()
{
	log_string_notice(qtoc(QStringLiteral("[%1]: enter settings dialog").arg(__FUNCTION__)));

	ZegoSettingsDialog settings;
	settings.initDialog();
	settings.exec();

	updateAppVersionTitle();
}


void ZegoMainDialog::on_m_bClose_clicked()
{
	this->close();
}

void ZegoMainDialog::on_m_bMin_clicked()
{
	this->showMinimized();
}

void ZegoMainDialog::on_m_bJumpToNet_clicked()
{
	QDesktopServices::openUrl(QUrl(QLatin1String("https://www.zego.im")));
}

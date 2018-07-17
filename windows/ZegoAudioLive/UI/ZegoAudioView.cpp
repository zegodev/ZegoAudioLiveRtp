#include "ZegoAudioView.h"

ZegoAudioView::ZegoAudioView(const QString& userName, bool isMySelf, QWidget * parent) : m_isCurrentUser(isMySelf), QFrame(parent)
{
	this->setStyleSheet("background-color: #ffffff; border: 1px solid #0e88eb;");
	this->setFixedSize(QSize(250, 150));
	
	m_mainLayout = new QVBoxLayout;


	auto vSpacer1 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
	m_mainLayout->addItem(vSpacer1);

	m_lbUserName = new QLabel;
	m_lbUserName->setStyleSheet("font-family:Î¢ÈíÑÅºÚ;font-size:14px;color:#333333; border:none;");
	if (isMySelf)
	{
		//QString srcStr = tr("ÓÃ»§Ãû: %1(×Ô¼º)").arg(userName);
		//QString strElidText = m_lbUserName->fontMetrics().elidedText(srcStr, Qt::ElideRight, 200, Qt::TextShowMnemonic);
		m_lbUserName->setText(tr("ÓÃ»§Ãû: %1(×Ô¼º)").arg(userName));
	}
	else
		m_lbUserName->setText(tr("ÓÃ»§Ãû: %1").arg(userName));

	//m_lbUserName->setFixedWidth(200);
	//m_title->setWordWrap(true);
	//m_title->setAlignment(Qt::AlignTop);
	m_mainLayout->addWidget(m_lbUserName);

	auto vSpacer2 = new QSpacerItem(16, 16, QSizePolicy::Fixed, QSizePolicy::Fixed);
	m_mainLayout->addItem(vSpacer2);


	auto gLayout = new QGridLayout;
	
	m_lbAudioKBS = new QLabel;
	m_lbAudioKBS->setStyleSheet("font-family:Î¢ÈíÑÅºÚ;font-size:12px;color:#666666; border:none;");
	m_lbAudioKBS->setText(tr("ÒôÆµÂëÂÊ: 0kb/s"));

	m_lbAudioBreakRate = new QLabel;
	m_lbAudioBreakRate->setStyleSheet("font-family:Î¢ÈíÑÅºÚ;font-size:12px;color:#666666; border:none;");
	m_lbAudioBreakRate->setText(tr("ÒôÆµ¿¨¶ÙÂÊ: 0´Î/min"));

	m_lbRTT = new QLabel;
	m_lbRTT->setStyleSheet("font-family:Î¢ÈíÑÅºÚ;font-size:12px;color:#666666; border:none;");
	m_lbRTT->setText(tr("RTT: 0ms"));

	m_lbLostRate = new QLabel;
	m_lbLostRate->setStyleSheet("font-family:Î¢ÈíÑÅºÚ;font-size:12px;color:#666666; border:none;");
	m_lbLostRate->setText(tr("¶ª°üÂÊ: 0%"));

	gLayout->addWidget(m_lbAudioKBS, 0, 0, 1, 1);
	gLayout->addWidget(m_lbRTT, 0, 1, 1, 1);
	gLayout->addWidget(m_lbLostRate, 1, 0, 1, 1);
	if(!isMySelf)
	    gLayout->addWidget(m_lbAudioBreakRate, 1, 1, 1, 1);
	
	m_mainLayout->addLayout(gLayout);

	auto vSpacer4 = new QSpacerItem(12, 12, QSizePolicy::Fixed, QSizePolicy::Fixed);
	m_mainLayout->addItem(vSpacer4);

	auto hLayout = new QHBoxLayout;

	auto fLayout = new QFormLayout;
	m_micIcon = new ZegoLabel(this);
	m_micIcon->setFixedSize(QSize(16, 16));
	m_micIcon->setButtonIcon("mic_icon_on");
	m_micIcon->setStyleSheet("border: none;");

	m_progVolume = new QProgressBar;
	m_progVolume->setMaximum(100);
	m_progVolume->setMinimum(0);
	m_progVolume->setValue(0);
	m_progVolume->setFormat("");
	m_progVolume->setFixedSize(QSize(150, 16));
	m_progVolume->setStyleSheet("QProgressBar {"
		                        "border: none;"
		                        "border-radius: 3px;"
		                        "background-color: #ffffff;}"
                                "QProgressBar::chunk{"
	                            "background-color: #0e88eb;"
		                        "border-radius: 3px;}" );

	fLayout->setWidget(0, QFormLayout::LabelRole, m_micIcon);
	fLayout->setWidget(0, QFormLayout::FieldRole, m_progVolume);
	hLayout->addLayout(fLayout);

	auto hSpacer = new QSpacerItem(12, 12, QSizePolicy::Fixed, QSizePolicy::Fixed);
	hLayout->addItem(hSpacer);

	/*m_stateIcon = new ZegoLabel(this);
	m_stateIcon->setFixedSize(QSize(20, 20));
	m_stateIcon->setStyleSheet("border: none;");
	m_stateIcon->setButtonIcon("disconnect");
	m_stateIcon->setVisible(false);*/
	m_indicator = new ZegoProgressIndicator;
	hLayout->addWidget(m_indicator);

	m_mainLayout->addLayout(hLayout);

	auto vSpacer5 = new QSpacerItem(12, 12, QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_mainLayout->addItem(vSpacer5);

	m_mainLayout->setContentsMargins(10, 0, 10, 0);
	this->setLayout(m_mainLayout);
	
}

ZegoAudioView::~ZegoAudioView()
{
	//m_title->deleteLater();
	//m_bSendQuestion->deleteLater();
	//m_bSendStatistics->deleteLater();
	//m_countDownLabel->deleteLater();
	m_mainLayout->deleteLater();

	//for (int i = 0; i < m_answers.size(); i++)
		//m_answers[i]->deleteLater();
}

void ZegoAudioView::setViewIndex(int index)
{
	m_viewIndex = index;
}

int ZegoAudioView::getViewIndex()
{
	return m_viewIndex;
}

bool ZegoAudioView::IsCurrentUser()
{
	return m_isCurrentUser;
}

void ZegoAudioView::SetProgValue(int v)
{
	m_progVolume->setValue(v);
	m_progVolume->update();
}

void ZegoAudioView::updatePublishQuality(double akbs, int rtt, int lostRate)
{
	if (!m_isCurrentUser)
		return;

	m_lbAudioKBS->setText(tr("ÒôÆµÂëÂÊ : %1kb/s").arg(QString::number(akbs, 10, 0)));
	m_lbLostRate->setText(tr("¶ª°üÂÊ : %1%").arg(QString::number((lostRate*1.0 / 255) * 100, 10, 2)));
	m_lbRTT->setText(tr("RTT : %1ms").arg(QString::number(rtt, 10)));
}

void ZegoAudioView::updatePlayQuality(double akbs, double breakRate, int rtt, int lostRate)
{
	if (m_isCurrentUser)
		return;

	m_lbAudioKBS->setText(tr("ÒôÆµÂëÂÊ : %1kb/s").arg(QString::number(akbs, 10, 0)));
	m_lbLostRate->setText(tr("¶ª°üÂÊ : %1%").arg(QString::number((lostRate*1.0 / 255) * 100, 10, 2)));
	m_lbRTT->setText(tr("RTT : %1ms").arg(QString::number(rtt, 10)));
	m_lbAudioBreakRate->setText(tr("ÒôÆµ¿¨¶ÙÂÊ : %1´Î/min").arg(QString::number(breakRate, 10, 0)));
}

void ZegoAudioView::SetMicEnabled(bool isEnabled)
{
	if (isEnabled)
		m_micIcon->setButtonIcon("mic_icon_on");
	else
		m_micIcon->setButtonIcon("mic_icon_off");

}

void ZegoAudioView::SetNetworkEnabled(bool isEnabled)
{
	//m_stateIcon->setVisible(!isEnabled);
	m_isNetworkEnabled = isEnabled;

	if (isEnabled)
		m_indicator->stopAnimation();
	else
		m_indicator->startAnimation();
}

bool ZegoAudioView::IsNetworkEnabeld()
{
	return m_isNetworkEnabled;
}

void ZegoAudioView::IncreaseWeakNetCount()
{
	++m_weakNetworkCount;
}

void ZegoAudioView::ResetWeakNetCount()
{
	m_weakNetworkCount = 0;
}

unsigned int ZegoAudioView::GetCurrentWeakCount()
{
	return m_weakNetworkCount;
}

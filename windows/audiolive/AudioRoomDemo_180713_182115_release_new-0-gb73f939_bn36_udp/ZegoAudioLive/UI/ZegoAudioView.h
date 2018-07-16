#pragma once
#pragma execution_character_set("utf-8")

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QFormLayout>
#include <QProgressBar>

#include "ZegoLabel.h"
#include "ZegoProgressIndicator.h"

class ZegoAudioView : public QFrame
{
	Q_OBJECT

public:
	ZegoAudioView(const QString& userName, bool isMySelf, QWidget * parent = 0);
	~ZegoAudioView();

	void setViewIndex(int index);
	int getViewIndex();

	bool IsCurrentUser();
	void SetProgValue(int v);

	void updatePublishQuality(double akbs, int rtt, int lostRate);
	void updatePlayQuality(double akbs, double breakRate, int rtt, int lostRate);

	void SetMicEnabled(bool isEnabled);
	void SetNetworkEnabled(bool isEnabled);

	bool IsNetworkEnabeld();

	void IncreaseWeakNetCount();
	void ResetWeakNetCount();
	unsigned int GetCurrentWeakCount();

signals:
	

public slots:

private slots:

private:
	QLabel *m_lbUserName;
	QLabel *m_lbAudioKBS;
	QLabel *m_lbAudioBreakRate;
	QLabel *m_lbRTT;
	QLabel *m_lbLostRate;
	ZegoLabel *m_micIcon;
	QProgressBar *m_progVolume;
	ZegoLabel *m_stateIcon;
	ZegoProgressIndicator *m_indicator;
	QVBoxLayout *m_mainLayout;

	int m_viewIndex = -1;

	bool m_isCurrentUser;
	bool m_isNetworkEnabled = true;

	unsigned int m_weakNetworkCount = 0;
};
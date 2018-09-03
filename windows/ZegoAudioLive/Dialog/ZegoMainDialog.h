#ifndef ZEGOMAINDIALOG_H
#define ZEGOMAINDIALOG_H

#include <QtWidgets/QDialog>
#include <QStringListModel>
#include <QTime>
#include <QMessageBox>
#include "ui_ZegoMainDialog.h"
#include "Config/ZegoUserConfig.h"
#include "Model/ZegoStreamModel.h"
#include "Base/ZegoBase.h"
#include "Base/ZegoDialog.h"
#include "ZegoAudioDemo.h"

class ZegoMainDialog : public ZegoDialog
{
	Q_OBJECT

public:
	ZegoMainDialog(QWidget *parent = 0);
	~ZegoMainDialog();

	void initDialog();
	
signals:
	void sigCheckEnterRoom();

private slots:
    void OnCheckEnterRoom();

private slots:
    void on_m_bEnterRoom_clicked();
	void on_m_bSettings_clicked();

	void on_m_bClose_clicked();
	void on_m_bMin_clicked();
	void on_m_bJumpToNet_clicked();

private:
	void initButtonIcon();
	void updateAppVersionTitle();
	QVector<QString> handleAppSign(QString appSign);

private:
	Ui::ZegoMainDialog ui;
	//”√ªß≈‰÷√

	//User
	QString m_strEdUserId;
	QString m_strEdUserName;
	
};

#endif // ZEGOMAINDIALOG_H

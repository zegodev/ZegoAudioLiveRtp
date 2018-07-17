#pragma execution_character_set("utf-8")

#ifndef ZEGOSETTINGSDIALOG_H
#define ZEGOSETTINGSDIALOG_H

#include <QtWidgets/QDialog>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QMessageBox>
#include <QMetaType>
#include "ui_ZegoSettingsDialog.h"
#include "Base/ZegoBase.h"
#include "Base/ZegoDialog.h"
#include "Config/ZegoUserConfig.h"
#include "ZegoAudioDemo.h"
#include "Model/ZegoSettingsModel.h"


class ZegoSettingsDialog : public ZegoDialog
{
	Q_OBJECT

public:
	ZegoSettingsDialog(QWidget *parent = 0);
	~ZegoSettingsDialog();
	void initDialog();

signals:
	void sigChangedSettingsConfig();

private slots:
    //Button槽
    void on_m_bClose_clicked();
    void on_m_bMin_clicked();

	void on_m_bSaveSettings_clicked();
	void on_m_bUploadLog_clicked();
	void on_m_switchTestEnv_clicked();
	
	//全局槽
	void OnChangedSettingsConfig();
	//ComboBox槽
	void OnComboBoxCheckAppVersion(int id);

protected:
	virtual void closeEvent(QCloseEvent *event);

private:
	void initButtonIcon();
	QVector<QString> handleAppSign(QString appSign);
	void copySettings(SettingsPtr dst, SettingsPtr src);

private:
	Ui::ZegoSettingsDialog ui;

	//处理是否保存了设置的逻辑
	bool m_isConfigChanged = false;
	bool m_isSaveConfig = false;

	QString m_strEdUserId;
	QString m_strEdUserName;
	//直播属性为UDP,RTMP,国际版或自定义（0,1,2,3）
	int m_versionMode = Version::ZEGO_PROTOCOL_UDP;

	

	//是否使用测试环境，默认不使用
	bool m_isUseTestEnv;
	//当前配置参数
	SettingsPtr m_pCurSettings;
	//用户更改配置后是否需要重新InitSDK，默认否
	bool m_isNeedReInstallSDK = false;

	//暂时保存当前设置的App版本(不一定保存)
	int m_tmpVersionMode;
	//暂时保存切换测试环境(不一定保存)
	bool m_tmpUseTestEnv = false;
	//暂时保存切换SurfaceMerge(不一定保存)
	bool m_tmpUseSurfaceMerge = false;
	//暂时保存VideoSettings(不一定保存)
	SettingsPtr m_tmpCurSettings;

	bool m_isCustomAppTextChanged = false;
};

#endif // ZEGOSETTINGSDIALOG_H
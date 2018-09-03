#pragma execution_character_set("utf-8")

#ifndef ZEGOVIDEOTALKDIALOG_H
#define ZEGOVIDEOTALKDIALOG_H

#include <QtWidgets/QDialog>
#include <QTimer>
#include <QStringListModel>
#include <QMessageBox>
#include <QFileDialog>
#include <QTime>
#include <QThread>
#include <QDateTime>
#include <QStandardItemModel>
#include <QGridLayout>
#include "ui_ZegoAudioLiveDialog.h"
#include "Config/ZegoUserConfig.h"
#include "Delegate/NoFocusFrameDelegate.h"
#include "Model/ZegoSettingsModel.h"
#include "Model/ZegoRoomModel.h"
#include "Model/ZegoStreamModel.h"
#include "Base/ZegoDialog.h"
#include "Device/ZegoDeviceManager.h"
#include "ZegoLogLabel.h"
#include "ZegoAudioView.h"
#include "ZegoAudioDemo.h"

class ZegoAudioLiveDialog : public ZegoDialog
{
	Q_OBJECT

public:
	ZegoAudioLiveDialog(RoomPtr chatRoom, QDialog *lastDialog, QWidget *parent = 0);
	~ZegoAudioLiveDialog();
	void initDialog();

	//sdk回调槽
protected slots:
	void OnLoginRoom(int errorCode, const QString& strRoomID);
	void OnStreamUpdated(const QString& strRoomID, StreamPtr pStream, AUDIOROOM::ZegoStreamUpdateType type);
	void OnPublishStateUpdate(int stateCode, const QString& streamId, StreamPtr streamInfo);
	void OnPlayStateUpdate(int stateCode, StreamPtr pStream);
	void OnDisconnect(int errorCode, const QString& roomId);
	void OnKickOut(int reason, const QString& roomId);
	void OnPlayQualityUpdate(const QString& streamId, double audioKBS, double audioBreakRate, int rtt, int lostRate);
	void OnPublishQualityUpdate(const QString& streamId, double audioKBS, int rtt, int lostRate);
	void OnUserUpdate(QVector <QString> userIDs, QVector <QString> userNames, QVector <int> userFlags, QVector <int> userRoles, unsigned int userCount, AUDIOROOM::ZegoUserUpdateType type);
	void OnCaptureSoundLevelUpdate(QString streamId, float soundLevel);
	void OnSoundLevelUpdate(QVector< QPair<QString, float> > soundLevelList);
	void OnStreamExtraInfoUpdated(QVector<StreamPtr> streamList, QString strRoomId);
	void OnAVKitEvent(int event);

signals:
	void sigCloseView();

	//UI回调槽
private slots:
	//Button槽
	void on_m_bClose_clicked();
	void on_m_bMax_clicked();
	void on_m_bMin_clicked();
	void on_m_switchMic_clicked();
	void on_m_switchSpeaker_clicked();
	
	//Timer槽
	void OnProgChange();
	//ComboBox槽
	void OnSwitchAudioInputDevice(int id);
	void OnSwitchAudioOutputDevice(int id);

	void OnMicIdChanged(const QString& micId);
	void OnSpeakerIdChanged(const QString& speakerId);

	void OnMicVolumeChanged(int v);
	void OnSpeakerVolumeChanged(int v);

	void OnDeviceAdded(int type, QString deviceName);
	void OnDeviceDeleted(int type, int index);

	void OnMicVolumeMute(bool bEnabled);

protected:
	virtual void closeEvent(QCloseEvent *event);
	virtual bool eventFilter(QObject *target, QEvent *event);

private:
	//推拉流
	void StartPublishStream();
	void StopPublishStream(const QString& streamID);
	void StartPlayStream(StreamPtr stream);
	void StopPlayStream(const QString& streamID);

	void GetAudioDevice();

	//退出前清理
	void UninitDialog();

	//初始化
	void initComboBox();
	//操作model增删的函数
	void insertStringListModelItem(QStringListModel * model, QString name, int size);
	void removeStringListModelItem(QStringListModel * model, QString name);
	
	//AudioView 布局
	int takeLeastAvaliableViewIndex();
	ZegoAudioView *addAudioView(const QString& userName, int addViewIndex, bool isPublisher, bool isMicEnabled);
	void updateViewLayout(int viewCount);
	ZegoAudioView *removeAudioView(int removeViewIndex);
	void FreeAudioView(StreamPtr stream);
	
	//成员列表增删函数
	void roomMemberAdd(QString userName);
	void roomMemberDelete(QString userName);
	//打印日志
	void addLogString(QString log);

	void initButtonIcon();

private:
	Ui::ZegoAudioLiveDialog ui;

	//当前房间号
	QString m_roomID;
	QVector<unsigned int> m_avaliableView;
	QVector<ZegoAudioView *> AudioViewList;

	ZegoAudioView * m_publishView = nullptr;
	QMap<QString, ZegoAudioView*>playViewList;

	bool m_isMax = false;

	bool m_bCKEnableMic = true;
	bool m_bCKEnableSpeaker = true;

	bool m_bIsPublishing = false;
	bool m_isVideoCustom = false;
	bool m_isLiveFullScreen = false;
	SettingsPtr m_pAVSettings;
	RoomPtr m_pChatRoom;

	//int m_publishViewIndex = 0;

	QString m_strPublishStreamID;
	QString m_strCurUserID;
	QString m_strCurUserName;
	QString m_strRoomID;

	QVector<QDeviceInfo> m_vecAudioInputDeviceList;
	QVector<QDeviceInfo> m_vecAudioOutputDeviceList;

	//List
	QStringList m_MircoPhoneList;
	QStringList m_speakerList;
	//Model
	QStringListModel *m_cbMircoPhoneModel;
	QStringListModel *m_cbSpeakerModel;
	QStringListModel *m_memberModel;
	QStandardItemModel *m_logModel;

	//自定义的ComboBox下拉式页面
	QListView *m_cbMircoPhoneListView;
	QListView *m_cbSpeakerListView;

	//保存上一个界面的指针，用于退出该页面时显示它
	QDialog *m_lastDialog;

	//audio view的网格动态布局
	QGridLayout *m_gridLayout;

	//保留自己的流信息
	StreamPtr m_anchorStreamInfo;

	ZegoDeviceManager *m_device;

	QThread *m_retryThread = nullptr;
	QTimer *m_retryTimer = nullptr;
};

#endif // ZEGOVIDEOTALKDIALOG_H
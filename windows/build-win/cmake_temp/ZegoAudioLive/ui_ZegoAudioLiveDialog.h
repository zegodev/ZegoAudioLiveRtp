/********************************************************************************
** Form generated from reading UI file 'ZegoAudioLiveDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZEGOAUDIOLIVEDIALOG_H
#define UI_ZEGOAUDIOLIVEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <ZegoComboBox.h>
#include <ZegoImageButton.h>
#include <ZegoProgressIndicator.h>
#include <ZegoSlider.h>
#include <ZegoSwitchButton.h>

QT_BEGIN_NAMESPACE

class Ui_ZegoAudioLiveDialog
{
public:
    QVBoxLayout *verticalLayout_5;
    QWidget *m_zoneTitle;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_lbRoomName;
    QHBoxLayout *horizontalLayout_9;
    ZegoImageButton *m_bMin;
    ZegoImageButton *m_bMax;
    ZegoImageButton *m_bClose;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QWidget *m_zoneLiveView;
    QHBoxLayout *zoneLiveViewHorizontalLayout;
    QFrame *line;
    QWidget *m_zoneSettings;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_11;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_10;
    QLabel *m_lbEquipment_2;
    QSpacerItem *verticalSpacer_11;
    QFormLayout *formLayout;
    QLabel *m_lbMircoPhone;
    ZegoComboBox *m_cbMicroPhone;
    QLabel *m_lbSpeaker;
    ZegoComboBox *m_cbSpeaker;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_12;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_12;
    QLabel *m_lbOperation_2;
    QSpacerItem *verticalSpacer_13;
    QFormLayout *formLayout_2;
    ZegoSlider *m_sliderSpeaker;
    ZegoSlider *m_sliderMic;
    ZegoSwitchButton *m_switchMic;
    ZegoSwitchButton *m_switchSpeaker;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_lbRetryPublish;
    QSpacerItem *horizontalSpacer_2;
    ZegoProgressIndicator *m_ProgRetryPublish;
    QSpacerItem *horizontalSpacer_17;
    QFrame *m_lineBetweenViewAndList;
    QVBoxLayout *verticalLayout_4;
    QWidget *m_zoneCommonAndUserList;
    QVBoxLayout *verticalLayout_15;
    QTabWidget *m_tabCommonAndUserList;
    QWidget *m_tabContact;
    QVBoxLayout *verticalLayout_16;
    QFrame *m_lineContact;
    QFrame *m_lineLongContact;
    QTableView *m_listLog;
    QWidget *m_tabMember;
    QVBoxLayout *verticalLayout_17;
    QFrame *m_lineMember;
    QFrame *m_lineLongMember;
    QListView *m_listMember;
    QFrame *line_2;
    QWidget *m_zoneInput;
    QVBoxLayout *verticalLayout_13;
    QVBoxLayout *verticalLayout_14;
    QTextEdit *m_edInput;
    QSpacerItem *verticalSpacer_17;
    QHBoxLayout *horizontalLayout_14;
    QSpacerItem *horizontalSpacer_18;
    QSpacerItem *verticalSpacer_18;

    void setupUi(QDialog *ZegoAudioLiveDialog)
    {
        if (ZegoAudioLiveDialog->objectName().isEmpty())
            ZegoAudioLiveDialog->setObjectName(QStringLiteral("ZegoAudioLiveDialog"));
        ZegoAudioLiveDialog->resize(1092, 643);
        ZegoAudioLiveDialog->setMinimumSize(QSize(0, 0));
        ZegoAudioLiveDialog->setStyleSheet(QStringLiteral("background-color: #ffffff;"));
        verticalLayout_5 = new QVBoxLayout(ZegoAudioLiveDialog);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        m_zoneTitle = new QWidget(ZegoAudioLiveDialog);
        m_zoneTitle->setObjectName(QStringLiteral("m_zoneTitle"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_zoneTitle->sizePolicy().hasHeightForWidth());
        m_zoneTitle->setSizePolicy(sizePolicy);
        m_zoneTitle->setMinimumSize(QSize(0, 40));
        m_zoneTitle->setMaximumSize(QSize(16777215, 40));
        m_zoneTitle->setStyleSheet(QStringLiteral("background-color: #0e88eb;"));
        horizontalLayout_3 = new QHBoxLayout(m_zoneTitle);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        m_lbRoomName = new QLabel(m_zoneTitle);
        m_lbRoomName->setObjectName(QStringLiteral("m_lbRoomName"));
        m_lbRoomName->setStyleSheet(QString::fromUtf8("padding-left: 20px;\n"
"font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 14px;\n"
"color: #ffffff;\n"
"border: none;"));

        horizontalLayout_3->addWidget(m_lbRoomName);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(0);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, -1, -1, -1);
        m_bMin = new ZegoImageButton(m_zoneTitle);
        m_bMin->setObjectName(QStringLiteral("m_bMin"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_bMin->sizePolicy().hasHeightForWidth());
        m_bMin->setSizePolicy(sizePolicy1);
        m_bMin->setMinimumSize(QSize(30, 40));
        m_bMin->setMaximumSize(QSize(30, 40));
        m_bMin->setFocusPolicy(Qt::NoFocus);
        m_bMin->setStyleSheet(QLatin1String("QPushButton{\n"
"    border: 1px solid #0e88eb;\n"
"    background-color: #0e88eb;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"    border: 1px solid #0d80de;\n"
"    background-color: #0d80de;\n"
"}\n"
"\n"
"QPushButton:hover:pressed{\n"
"    border: 1px solid #0d79d1;\n"
"    background-color: #0d79d1;\n"
"}"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Resources/images/min.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_bMin->setIcon(icon);
        m_bMin->setFlat(true);

        horizontalLayout_9->addWidget(m_bMin);

        m_bMax = new ZegoImageButton(m_zoneTitle);
        m_bMax->setObjectName(QStringLiteral("m_bMax"));
        sizePolicy1.setHeightForWidth(m_bMax->sizePolicy().hasHeightForWidth());
        m_bMax->setSizePolicy(sizePolicy1);
        m_bMax->setMinimumSize(QSize(30, 40));
        m_bMax->setMaximumSize(QSize(30, 40));
        m_bMax->setFocusPolicy(Qt::NoFocus);
        m_bMax->setStyleSheet(QLatin1String("QPushButton{\n"
"    border: 1px solid #0e88eb;\n"
"    background-color: #0e88eb;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"    border: 1px solid #0d80de;\n"
"    background-color: #0d80de;\n"
"}\n"
"\n"
"QPushButton:hover:pressed{\n"
"    border: 1px solid #0d79d1;\n"
"    background-color: #0d79d1;\n"
"}"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Resources/images/max.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_bMax->setIcon(icon1);
        m_bMax->setCheckable(true);
        m_bMax->setFlat(true);

        horizontalLayout_9->addWidget(m_bMax);

        m_bClose = new ZegoImageButton(m_zoneTitle);
        m_bClose->setObjectName(QStringLiteral("m_bClose"));
        m_bClose->setEnabled(true);
        sizePolicy1.setHeightForWidth(m_bClose->sizePolicy().hasHeightForWidth());
        m_bClose->setSizePolicy(sizePolicy1);
        m_bClose->setMinimumSize(QSize(30, 40));
        m_bClose->setMaximumSize(QSize(30, 40));
        m_bClose->setFocusPolicy(Qt::NoFocus);
        m_bClose->setLayoutDirection(Qt::LeftToRight);
        m_bClose->setStyleSheet(QLatin1String("QPushButton{\n"
"    border: 1px solid #0e88eb;\n"
"    background-color: #0e88eb;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"    border: 1px solid #0d80de;\n"
"    background-color: #0d80de;\n"
"}\n"
"\n"
"QPushButton:hover:pressed{\n"
"    border: 1px solid #0d79d1;\n"
"    background-color: #0d79d1;\n"
"}"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Resources/images/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_bClose->setIcon(icon2);
        m_bClose->setFlat(true);

        horizontalLayout_9->addWidget(m_bClose);


        horizontalLayout_3->addLayout(horizontalLayout_9);


        verticalLayout_5->addWidget(m_zoneTitle);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        m_zoneLiveView = new QWidget(ZegoAudioLiveDialog);
        m_zoneLiveView->setObjectName(QStringLiteral("m_zoneLiveView"));
        m_zoneLiveView->setEnabled(true);
        sizePolicy.setHeightForWidth(m_zoneLiveView->sizePolicy().hasHeightForWidth());
        m_zoneLiveView->setSizePolicy(sizePolicy);
        m_zoneLiveView->setMinimumSize(QSize(765, 460));
        m_zoneLiveView->setMaximumSize(QSize(16777215, 16777215));
        m_zoneLiveView->setAutoFillBackground(false);
        m_zoneLiveView->setStyleSheet(QLatin1String("background-color: #cccccc;\n"
"border: none;"));
        zoneLiveViewHorizontalLayout = new QHBoxLayout(m_zoneLiveView);
        zoneLiveViewHorizontalLayout->setSpacing(0);
        zoneLiveViewHorizontalLayout->setObjectName(QStringLiteral("zoneLiveViewHorizontalLayout"));
        zoneLiveViewHorizontalLayout->setContentsMargins(0, 0, 0, 0);

        verticalLayout->addWidget(m_zoneLiveView);

        line = new QFrame(ZegoAudioLiveDialog);
        line->setObjectName(QStringLiteral("line"));
        line->setMinimumSize(QSize(0, 1));
        line->setMaximumSize(QSize(16777215, 1));
        line->setStyleSheet(QLatin1String("border: none;\n"
"background-color: #e6e6e6;"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        m_zoneSettings = new QWidget(ZegoAudioLiveDialog);
        m_zoneSettings->setObjectName(QStringLiteral("m_zoneSettings"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_zoneSettings->sizePolicy().hasHeightForWidth());
        m_zoneSettings->setSizePolicy(sizePolicy2);
        m_zoneSettings->setMinimumSize(QSize(0, 138));
        m_zoneSettings->setMaximumSize(QSize(16777215, 138));
        m_zoneSettings->setStyleSheet(QStringLiteral("background-color: #ffffff;"));
        horizontalLayout_4 = new QHBoxLayout(m_zoneSettings);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_11 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_11);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer_10 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_10);

        m_lbEquipment_2 = new QLabel(m_zoneSettings);
        m_lbEquipment_2->setObjectName(QStringLiteral("m_lbEquipment_2"));
        m_lbEquipment_2->setMinimumSize(QSize(18, 0));
        m_lbEquipment_2->setMaximumSize(QSize(16777215, 18));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        m_lbEquipment_2->setFont(font);
        m_lbEquipment_2->setStyleSheet(QString::fromUtf8("font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 14px;\n"
"color: #666666;"));

        verticalLayout_2->addWidget(m_lbEquipment_2);

        verticalSpacer_11 = new QSpacerItem(20, 14, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_11);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setHorizontalSpacing(10);
        formLayout->setVerticalSpacing(10);
        m_lbMircoPhone = new QLabel(m_zoneSettings);
        m_lbMircoPhone->setObjectName(QStringLiteral("m_lbMircoPhone"));
        m_lbMircoPhone->setStyleSheet(QString::fromUtf8("QLabel:!enabled{\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"    font-size: 14px;\n"
"    color: #cccccc;\n"
" }\n"
" \n"
"QLabel:enabled{\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"    font-size: 14px;\n"
"    color: #666666;\n"
" }"));

        formLayout->setWidget(0, QFormLayout::LabelRole, m_lbMircoPhone);

        m_cbMicroPhone = new ZegoComboBox(m_zoneSettings);
        m_cbMicroPhone->setObjectName(QStringLiteral("m_cbMicroPhone"));
        m_cbMicroPhone->setMinimumSize(QSize(260, 32));
        m_cbMicroPhone->setMaximumSize(QSize(260, 32));
        m_cbMicroPhone->setFrame(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, m_cbMicroPhone);

        m_lbSpeaker = new QLabel(m_zoneSettings);
        m_lbSpeaker->setObjectName(QStringLiteral("m_lbSpeaker"));
        m_lbSpeaker->setStyleSheet(QString::fromUtf8("QLabel:!enabled{\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"    font-size: 14px;\n"
"    color: #cccccc;\n"
" }\n"
" \n"
"QLabel:enabled{\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"    font-size: 14px;\n"
"    color: #666666;\n"
" }"));

        formLayout->setWidget(1, QFormLayout::LabelRole, m_lbSpeaker);

        m_cbSpeaker = new ZegoComboBox(m_zoneSettings);
        m_cbSpeaker->setObjectName(QStringLiteral("m_cbSpeaker"));
        m_cbSpeaker->setMinimumSize(QSize(260, 32));
        m_cbSpeaker->setMaximumSize(QSize(260, 32));
        m_cbSpeaker->setFrame(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, m_cbSpeaker);


        verticalLayout_2->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_4->addLayout(verticalLayout_2);

        horizontalSpacer_12 = new QSpacerItem(30, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_12);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalSpacer_12 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_12);

        m_lbOperation_2 = new QLabel(m_zoneSettings);
        m_lbOperation_2->setObjectName(QStringLiteral("m_lbOperation_2"));
        m_lbOperation_2->setMinimumSize(QSize(0, 18));
        m_lbOperation_2->setMaximumSize(QSize(16777215, 18));
        m_lbOperation_2->setFont(font);
        m_lbOperation_2->setStyleSheet(QString::fromUtf8("font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 14px;\n"
"color: #666666;"));

        verticalLayout_3->addWidget(m_lbOperation_2);

        verticalSpacer_13 = new QSpacerItem(20, 14, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_13);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        formLayout_2->setHorizontalSpacing(10);
        formLayout_2->setVerticalSpacing(25);
        formLayout_2->setContentsMargins(-1, 8, -1, -1);
        m_sliderSpeaker = new ZegoSlider(m_zoneSettings);
        m_sliderSpeaker->setObjectName(QStringLiteral("m_sliderSpeaker"));
        m_sliderSpeaker->setMinimumSize(QSize(200, 0));
        m_sliderSpeaker->setMaximumSize(QSize(200, 16777215));
        m_sliderSpeaker->setMaximum(100);
        m_sliderSpeaker->setSingleStep(0);
        m_sliderSpeaker->setOrientation(Qt::Horizontal);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, m_sliderSpeaker);

        m_sliderMic = new ZegoSlider(m_zoneSettings);
        m_sliderMic->setObjectName(QStringLiteral("m_sliderMic"));
        m_sliderMic->setMinimumSize(QSize(200, 0));
        m_sliderMic->setMaximumSize(QSize(200, 16777215));
        m_sliderMic->setMaximum(100);
        m_sliderMic->setSingleStep(0);
        m_sliderMic->setOrientation(Qt::Horizontal);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, m_sliderMic);

        m_switchMic = new ZegoSwitchButton(m_zoneSettings);
        m_switchMic->setObjectName(QStringLiteral("m_switchMic"));
        m_switchMic->setMinimumSize(QSize(16, 16));
        m_switchMic->setMaximumSize(QSize(16, 16));
        m_switchMic->setCursor(QCursor(Qt::PointingHandCursor));
        m_switchMic->setCheckable(true);
        m_switchMic->setChecked(true);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, m_switchMic);

        m_switchSpeaker = new ZegoSwitchButton(m_zoneSettings);
        m_switchSpeaker->setObjectName(QStringLiteral("m_switchSpeaker"));
        m_switchSpeaker->setMinimumSize(QSize(16, 16));
        m_switchSpeaker->setMaximumSize(QSize(16, 16));
        m_switchSpeaker->setCursor(QCursor(Qt::PointingHandCursor));
        m_switchSpeaker->setCheckable(true);
        m_switchSpeaker->setChecked(true);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, m_switchSpeaker);


        verticalLayout_3->addLayout(formLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        horizontalLayout_4->addLayout(verticalLayout_3);

        horizontalSpacer = new QSpacerItem(16, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        m_lbRetryPublish = new QLabel(m_zoneSettings);
        m_lbRetryPublish->setObjectName(QStringLiteral("m_lbRetryPublish"));
        m_lbRetryPublish->setStyleSheet(QString::fromUtf8("QLabel:!enabled{\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"    font-size: 12px;\n"
"    color: #cccccc;\n"
" }\n"
" \n"
"QLabel:enabled{\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"    font-size: 12px;\n"
"    color: #666666;\n"
" }"));
        m_lbRetryPublish->setWordWrap(true);

        horizontalLayout_2->addWidget(m_lbRetryPublish);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        m_ProgRetryPublish = new ZegoProgressIndicator(m_zoneSettings);
        m_ProgRetryPublish->setObjectName(QStringLiteral("m_ProgRetryPublish"));
        m_ProgRetryPublish->setMinimumSize(QSize(20, 20));
        m_ProgRetryPublish->setMaximumSize(QSize(20, 20));

        horizontalLayout_2->addWidget(m_ProgRetryPublish);


        horizontalLayout_4->addLayout(horizontalLayout_2);

        horizontalSpacer_17 = new QSpacerItem(17, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_17);


        verticalLayout->addWidget(m_zoneSettings);


        horizontalLayout->addLayout(verticalLayout);

        m_lineBetweenViewAndList = new QFrame(ZegoAudioLiveDialog);
        m_lineBetweenViewAndList->setObjectName(QStringLiteral("m_lineBetweenViewAndList"));
        m_lineBetweenViewAndList->setMinimumSize(QSize(1, 0));
        m_lineBetweenViewAndList->setMaximumSize(QSize(1, 16777215));
        m_lineBetweenViewAndList->setStyleSheet(QLatin1String("border: none;\n"
"background-color: #e6e6e6;"));
        m_lineBetweenViewAndList->setFrameShape(QFrame::VLine);
        m_lineBetweenViewAndList->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(m_lineBetweenViewAndList);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        m_zoneCommonAndUserList = new QWidget(ZegoAudioLiveDialog);
        m_zoneCommonAndUserList->setObjectName(QStringLiteral("m_zoneCommonAndUserList"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(m_zoneCommonAndUserList->sizePolicy().hasHeightForWidth());
        m_zoneCommonAndUserList->setSizePolicy(sizePolicy3);
        m_zoneCommonAndUserList->setMinimumSize(QSize(320, 0));
        m_zoneCommonAndUserList->setMaximumSize(QSize(320, 16777215));
        m_zoneCommonAndUserList->setStyleSheet(QStringLiteral("background-color: #ffffff;"));
        verticalLayout_15 = new QVBoxLayout(m_zoneCommonAndUserList);
        verticalLayout_15->setSpacing(0);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        verticalLayout_15->setContentsMargins(0, 0, 0, 0);
        m_tabCommonAndUserList = new QTabWidget(m_zoneCommonAndUserList);
        m_tabCommonAndUserList->setObjectName(QStringLiteral("m_tabCommonAndUserList"));
        m_tabCommonAndUserList->setStyleSheet(QString::fromUtf8("QTabWidget::pane{\n"
"	border: none;\n"
"}\n"
"\n"
"QTabWidget::tab-bar{\n"
"    left: 0px;\n"
"}\n"
"\n"
"QTabBar::tab{\n"
"    width: 160px;\n"
"    height: 40px;\n"
"    margin: 0 0 0 0;\n"
"	font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"	font-size: 16px;\n"
"	color: #333333;\n"
"	background-color: #ffffff;\n"
"}\n"
"\n"
"QTabBar::tab:selected{\n"
"	width: 160px;\n"
"	height: 40px;\n"
"	font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"	font-size: 16px;\n"
"	color: #0e88eb;\n"
"	background-color: #ffffff;\n"
"}"));
        m_tabContact = new QWidget();
        m_tabContact->setObjectName(QStringLiteral("m_tabContact"));
        verticalLayout_16 = new QVBoxLayout(m_tabContact);
        verticalLayout_16->setSpacing(0);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        verticalLayout_16->setContentsMargins(0, 0, 0, 0);
        m_lineContact = new QFrame(m_tabContact);
        m_lineContact->setObjectName(QStringLiteral("m_lineContact"));
        m_lineContact->setMinimumSize(QSize(0, 2));
        m_lineContact->setMaximumSize(QSize(16777215, 2));
        m_lineContact->setStyleSheet(QLatin1String("border: none;\n"
"background-color: #0e88eb;\n"
"margin-right: 160px;"));
        m_lineContact->setFrameShape(QFrame::HLine);
        m_lineContact->setFrameShadow(QFrame::Sunken);

        verticalLayout_16->addWidget(m_lineContact);

        m_lineLongContact = new QFrame(m_tabContact);
        m_lineLongContact->setObjectName(QStringLiteral("m_lineLongContact"));
        m_lineLongContact->setMinimumSize(QSize(0, 1));
        m_lineLongContact->setMaximumSize(QSize(16777215, 1));
        m_lineLongContact->setStyleSheet(QLatin1String("border: none;\n"
"background-color: #e6e6e6;"));
        m_lineLongContact->setFrameShape(QFrame::HLine);
        m_lineLongContact->setFrameShadow(QFrame::Sunken);

        verticalLayout_16->addWidget(m_lineLongContact);

        m_listLog = new QTableView(m_tabContact);
        m_listLog->setObjectName(QStringLiteral("m_listLog"));
        m_listLog->setStyleSheet(QString::fromUtf8("QTableView{\n"
"font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 14px;\n"
"color: #666666;\n"
"padding-top: 5px;\n"
"padding-left: 14px;\n"
"}\n"
"\n"
"QTableView::item{\n"
"    border: none;\n"
"    padding-top: 10px;\n"
"}\n"
"\n"
"QScrollBar:vertical {                 \n"
"    background:transparent;  \n"
"    width:9px;  \n"
"    margin: 0px 0px 2px 0px;  \n"
"}  \n"
"  \n"
"QScrollBar::handle:vertical {  \n"
"    background: rgb(195, 195, 195);  \n"
"    min-height: 20px;  \n"
"    border-radius: 3px;  \n"
"}  \n"
"  \n"
"QScrollBar::handle:vertical:hover{  \n"
"    background:rgba(0,0,0,30%);  \n"
"}  \n"
"  \n"
"QScrollBar::add-line:vertical {  \n"
"    height: 0px;  \n"
"    subcontrol-position: bottom;  \n"
"    subcontrol-origin: margin;  \n"
"}  \n"
"  \n"
"QScrollBar::sub-line:vertical {  \n"
"    height: 0px;  \n"
"    subcontrol-position: top;  \n"
"    subcontrol-origin: margin;  \n"
"}"));
        m_listLog->setFrameShape(QFrame::NoFrame);
        m_listLog->setShowGrid(false);

        verticalLayout_16->addWidget(m_listLog);

        m_tabCommonAndUserList->addTab(m_tabContact, QString());
        m_tabMember = new QWidget();
        m_tabMember->setObjectName(QStringLiteral("m_tabMember"));
        verticalLayout_17 = new QVBoxLayout(m_tabMember);
        verticalLayout_17->setSpacing(0);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        verticalLayout_17->setContentsMargins(0, 0, 0, 0);
        m_lineMember = new QFrame(m_tabMember);
        m_lineMember->setObjectName(QStringLiteral("m_lineMember"));
        m_lineMember->setMinimumSize(QSize(0, 2));
        m_lineMember->setMaximumSize(QSize(16777215, 2));
        m_lineMember->setStyleSheet(QLatin1String("border: none;\n"
"background-color: #0e88eb;\n"
"margin-left: 160px;"));
        m_lineMember->setFrameShape(QFrame::HLine);
        m_lineMember->setFrameShadow(QFrame::Sunken);

        verticalLayout_17->addWidget(m_lineMember);

        m_lineLongMember = new QFrame(m_tabMember);
        m_lineLongMember->setObjectName(QStringLiteral("m_lineLongMember"));
        m_lineLongMember->setMinimumSize(QSize(0, 1));
        m_lineLongMember->setMaximumSize(QSize(16777215, 1));
        m_lineLongMember->setStyleSheet(QLatin1String("border: none;\n"
"background-color: #e6e6e6;"));
        m_lineLongMember->setFrameShape(QFrame::HLine);
        m_lineLongMember->setFrameShadow(QFrame::Sunken);

        verticalLayout_17->addWidget(m_lineLongMember);

        m_listMember = new QListView(m_tabMember);
        m_listMember->setObjectName(QStringLiteral("m_listMember"));
        m_listMember->setStyleSheet(QString::fromUtf8("QListView{\n"
"font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 14px;\n"
"color: #666666;\n"
"padding-left: 14px;\n"
"border: none;\n"
"padding-top: 5px;\n"
"}\n"
"\n"
"QListView::item{\n"
"    width: 290px;\n"
"    min-height: 8px;\n"
"    margin-top: 10px;\n"
"}\n"
"\n"
"QScrollBar:vertical {                 \n"
"    background:transparent;  \n"
"    width:9px;  \n"
"    margin: 0px 0px 2px 0px;  \n"
"}  \n"
"  \n"
"QScrollBar::handle:vertical {  \n"
"    background: rgb(195, 195, 195);  \n"
"    min-height: 20px;  \n"
"    border-radius: 3px;  \n"
"}  \n"
"  \n"
"QScrollBar::handle:vertical:hover{  \n"
"    background:rgba(0,0,0,30%);  \n"
"}  \n"
"  \n"
"QScrollBar::add-line:vertical {  \n"
"    height: 0px;  \n"
"    subcontrol-position: bottom;  \n"
"    subcontrol-origin: margin;  \n"
"}  \n"
"  \n"
"QScrollBar::sub-line:vertical {  \n"
"    height: 0px;  \n"
"    subcontrol-position: top;  \n"
"    subcontrol-origin: margin;  \n"
"}"));
        m_listMember->setSelectionMode(QAbstractItemView::NoSelection);
        m_listMember->setSpacing(0);

        verticalLayout_17->addWidget(m_listMember);

        m_tabCommonAndUserList->addTab(m_tabMember, QString());

        verticalLayout_15->addWidget(m_tabCommonAndUserList);


        verticalLayout_4->addWidget(m_zoneCommonAndUserList);

        line_2 = new QFrame(ZegoAudioLiveDialog);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setMinimumSize(QSize(0, 1));
        line_2->setMaximumSize(QSize(16777215, 1));
        line_2->setStyleSheet(QLatin1String("border: none;\n"
"background-color: #e6e6e6;"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line_2);

        m_zoneInput = new QWidget(ZegoAudioLiveDialog);
        m_zoneInput->setObjectName(QStringLiteral("m_zoneInput"));
        sizePolicy3.setHeightForWidth(m_zoneInput->sizePolicy().hasHeightForWidth());
        m_zoneInput->setSizePolicy(sizePolicy3);
        m_zoneInput->setMinimumSize(QSize(320, 138));
        m_zoneInput->setMaximumSize(QSize(320, 138));
        m_zoneInput->setStyleSheet(QStringLiteral("background-color: #ffffff;"));
        verticalLayout_13 = new QVBoxLayout(m_zoneInput);
        verticalLayout_13->setSpacing(0);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(0, 0, 0, 0);
        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(0);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        m_edInput = new QTextEdit(m_zoneInput);
        m_edInput->setObjectName(QStringLiteral("m_edInput"));
        m_edInput->setStyleSheet(QString::fromUtf8("QTextEdit{\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"    font-size: 14px;\n"
"    padding-left: 10px;\n"
"    color: #333333;\n"
"}\n"
"\n"
"QScrollBar:vertical{\n"
"    border:0px solid grey;\n"
"    width: 10px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical{\n"
"     background-color: #dbdbdb;\n"
"     border-radius: 5px;\n"
"     min-height: 20px;\n"
"     \n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover{\n"
"     background-color: #d0d0d0;\n"
"}"));
        m_edInput->setFrameShape(QFrame::NoFrame);

        verticalLayout_14->addWidget(m_edInput);

        verticalSpacer_17 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_14->addItem(verticalSpacer_17);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(0);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_18);


        verticalLayout_14->addLayout(horizontalLayout_14);

        verticalSpacer_18 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_14->addItem(verticalSpacer_18);


        verticalLayout_13->addLayout(verticalLayout_14);


        verticalLayout_4->addWidget(m_zoneInput);


        horizontalLayout->addLayout(verticalLayout_4);


        verticalLayout_5->addLayout(horizontalLayout);


        retranslateUi(ZegoAudioLiveDialog);

        m_tabCommonAndUserList->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ZegoAudioLiveDialog);
    } // setupUi

    void retranslateUi(QDialog *ZegoAudioLiveDialog)
    {
        ZegoAudioLiveDialog->setWindowTitle(QApplication::translate("ZegoAudioLiveDialog", "ZegoAudioLive", Q_NULLPTR));
        m_lbRoomName->setText(QApplication::translate("ZegoAudioLiveDialog", "Mode", Q_NULLPTR));
        m_bMin->setText(QString());
        m_bMax->setText(QString());
        m_bClose->setText(QString());
        m_lbEquipment_2->setText(QApplication::translate("ZegoAudioLiveDialog", "Equipment", Q_NULLPTR));
        m_lbMircoPhone->setText(QApplication::translate("ZegoAudioLiveDialog", "\351\272\246\345\205\213\351\243\216", Q_NULLPTR));
        m_lbSpeaker->setText(QApplication::translate("ZegoAudioLiveDialog", "\346\211\254\345\243\260\345\231\250", Q_NULLPTR));
        m_lbOperation_2->setText(QApplication::translate("ZegoAudioLiveDialog", "Operation", Q_NULLPTR));
        m_switchMic->setText(QString());
        m_switchSpeaker->setText(QString());
        m_lbRetryPublish->setText(QApplication::translate("ZegoAudioLiveDialog", "\347\275\221\347\273\234\344\270\255\346\226\255\357\274\214\346\255\243\345\234\250\345\260\235\350\257\225 \351\207\215\346\226\260\350\277\236\346\216\245", Q_NULLPTR));
        m_tabCommonAndUserList->setTabText(m_tabCommonAndUserList->indexOf(m_tabContact), QApplication::translate("ZegoAudioLiveDialog", "\346\227\245\345\277\227", Q_NULLPTR));
        m_tabCommonAndUserList->setTabText(m_tabCommonAndUserList->indexOf(m_tabMember), QApplication::translate("ZegoAudioLiveDialog", "\346\210\220\345\221\230(0)", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ZegoAudioLiveDialog: public Ui_ZegoAudioLiveDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZEGOAUDIOLIVEDIALOG_H

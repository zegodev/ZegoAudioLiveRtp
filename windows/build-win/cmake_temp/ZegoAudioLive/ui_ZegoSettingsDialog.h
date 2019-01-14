/********************************************************************************
** Form generated from reading UI file 'ZegoSettingsDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZEGOSETTINGSDIALOG_H
#define UI_ZEGOSETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <ZegoImageButton.h>
#include <ZegoSwitchButton.h>

QT_BEGIN_NAMESPACE

class Ui_ZegoSettingsDialog
{
public:
    QVBoxLayout *verticalLayout_11;
    QVBoxLayout *verticalLayout_9;
    QWidget *m_zoneTitle;
    QHBoxLayout *horizontalLayout_15;
    QHBoxLayout *horizontalLayout_14;
    QSpacerItem *horizontalSpacer_4;
    QLabel *m_lbTitle;
    QSpacerItem *horizontalSpacer_5;
    ZegoImageButton *m_bMin;
    ZegoImageButton *m_bClose;
    QSpacerItem *verticalSpacer_11;
    QVBoxLayout *verticalLayout_7;
    QWidget *m_zoneSdkVersion;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_5;
    QLabel *m_lbSdkTitle;
    QLabel *m_lbSdkVersion;
    QFrame *m_hLine;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_7;
    QWidget *m_zoneUserConfig;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_10;
    QSpacerItem *verticalSpacer_7;
    QLabel *m_lbAccount;
    QSpacerItem *verticalSpacer_10;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_16;
    QLabel *m_lbUserId;
    QSpacerItem *horizontalSpacer_17;
    QLineEdit *m_strEdUserId;
    QHBoxLayout *horizontalLayout_17;
    QLabel *m_lbUserName;
    QSpacerItem *horizontalSpacer_18;
    QLineEdit *m_strEdUserName;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QLabel *label_4;
    QSpacerItem *verticalSpacer_9;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_22;
    QComboBox *m_cbAppVersion;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_12;
    ZegoSwitchButton *m_switchTestEnv;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_18;
    QLabel *m_lbAPPID_2;
    QSpacerItem *horizontalSpacer_19;
    QLineEdit *m_strEdAPPID;
    QHBoxLayout *horizontalLayout_19;
    QLabel *m_lbAPPSign_2;
    QSpacerItem *horizontalSpacer_20;
    QLineEdit *m_strEdAPPSign;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *m_bUploadLog;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *m_bSaveSettings;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *verticalSpacer_19;

    void setupUi(QDialog *ZegoSettingsDialog)
    {
        if (ZegoSettingsDialog->objectName().isEmpty())
            ZegoSettingsDialog->setObjectName(QStringLiteral("ZegoSettingsDialog"));
        ZegoSettingsDialog->resize(350, 500);
        ZegoSettingsDialog->setMinimumSize(QSize(350, 500));
        ZegoSettingsDialog->setMaximumSize(QSize(350, 500));
        ZegoSettingsDialog->setStyleSheet(QStringLiteral("background-color: #fafafa;"));
        verticalLayout_11 = new QVBoxLayout(ZegoSettingsDialog);
        verticalLayout_11->setSpacing(0);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(0);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(-1, -1, -1, 0);
        m_zoneTitle = new QWidget(ZegoSettingsDialog);
        m_zoneTitle->setObjectName(QStringLiteral("m_zoneTitle"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_zoneTitle->sizePolicy().hasHeightForWidth());
        m_zoneTitle->setSizePolicy(sizePolicy);
        m_zoneTitle->setMinimumSize(QSize(0, 40));
        m_zoneTitle->setMaximumSize(QSize(16777215, 40));
        m_zoneTitle->setStyleSheet(QStringLiteral("background-color: #0e88eb;"));
        horizontalLayout_15 = new QHBoxLayout(m_zoneTitle);
        horizontalLayout_15->setSpacing(0);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(0);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_4);

        m_lbTitle = new QLabel(m_zoneTitle);
        m_lbTitle->setObjectName(QStringLiteral("m_lbTitle"));
        m_lbTitle->setStyleSheet(QString::fromUtf8("font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"	 font-size: 16px;\n"
"     color: #ffffff;"));

        horizontalLayout_14->addWidget(m_lbTitle);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_5);

        m_bMin = new ZegoImageButton(m_zoneTitle);
        m_bMin->setObjectName(QStringLiteral("m_bMin"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_bMin->sizePolicy().hasHeightForWidth());
        m_bMin->setSizePolicy(sizePolicy1);
        m_bMin->setMinimumSize(QSize(40, 40));
        m_bMin->setMaximumSize(QSize(40, 40));
        m_bMin->setStyleSheet(QLatin1String("QPushButton:!hover{\n"
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

        horizontalLayout_14->addWidget(m_bMin);

        m_bClose = new ZegoImageButton(m_zoneTitle);
        m_bClose->setObjectName(QStringLiteral("m_bClose"));
        sizePolicy1.setHeightForWidth(m_bClose->sizePolicy().hasHeightForWidth());
        m_bClose->setSizePolicy(sizePolicy1);
        m_bClose->setMinimumSize(QSize(50, 40));
        m_bClose->setMaximumSize(QSize(50, 40));
        m_bClose->setStyleSheet(QLatin1String("QPushButton:!hover{\n"
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
        icon1.addFile(QStringLiteral(":/Resources/images/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_bClose->setIcon(icon1);

        horizontalLayout_14->addWidget(m_bClose);


        horizontalLayout_15->addLayout(horizontalLayout_14);


        verticalLayout_9->addWidget(m_zoneTitle);

        verticalSpacer_11 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_9->addItem(verticalSpacer_11);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        m_zoneSdkVersion = new QWidget(ZegoSettingsDialog);
        m_zoneSdkVersion->setObjectName(QStringLiteral("m_zoneSdkVersion"));
        horizontalLayout_7 = new QHBoxLayout(m_zoneSdkVersion);
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, -1, 0, -1);
        m_lbSdkTitle = new QLabel(m_zoneSdkVersion);
        m_lbSdkTitle->setObjectName(QStringLiteral("m_lbSdkTitle"));
        m_lbSdkTitle->setMinimumSize(QSize(80, 0));
        m_lbSdkTitle->setMaximumSize(QSize(80, 16777215));
        m_lbSdkTitle->setStyleSheet(QString::fromUtf8("font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 16px;\n"
"color: #666666;"));

        horizontalLayout_5->addWidget(m_lbSdkTitle);

        m_lbSdkVersion = new QLabel(m_zoneSdkVersion);
        m_lbSdkVersion->setObjectName(QStringLiteral("m_lbSdkVersion"));
        m_lbSdkVersion->setStyleSheet(QString::fromUtf8("font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 16px;\n"
"color: #666666;"));
        m_lbSdkVersion->setWordWrap(true);

        horizontalLayout_5->addWidget(m_lbSdkVersion);


        horizontalLayout_7->addLayout(horizontalLayout_5);


        verticalLayout_7->addWidget(m_zoneSdkVersion);

        m_hLine = new QFrame(ZegoSettingsDialog);
        m_hLine->setObjectName(QStringLiteral("m_hLine"));
        m_hLine->setMinimumSize(QSize(0, 1));
        m_hLine->setMaximumSize(QSize(16777215, 1));
        m_hLine->setStyleSheet(QLatin1String("border: none;\n"
"background-color: #0e88eb;"));
        m_hLine->setFrameShape(QFrame::HLine);
        m_hLine->setFrameShadow(QFrame::Sunken);

        verticalLayout_7->addWidget(m_hLine);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(0);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(0, -1, 0, -1);
        horizontalSpacer_7 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_7);

        m_zoneUserConfig = new QWidget(ZegoSettingsDialog);
        m_zoneUserConfig->setObjectName(QStringLiteral("m_zoneUserConfig"));
        verticalLayout_3 = new QVBoxLayout(m_zoneUserConfig);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(0);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        verticalSpacer_7 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_10->addItem(verticalSpacer_7);

        m_lbAccount = new QLabel(m_zoneUserConfig);
        m_lbAccount->setObjectName(QStringLiteral("m_lbAccount"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        m_lbAccount->setFont(font);
        m_lbAccount->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        verticalLayout_10->addWidget(m_lbAccount);

        verticalSpacer_10 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_10->addItem(verticalSpacer_10);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(15);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(0);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        m_lbUserId = new QLabel(m_zoneUserConfig);
        m_lbUserId->setObjectName(QStringLiteral("m_lbUserId"));
        m_lbUserId->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        horizontalLayout_16->addWidget(m_lbUserId);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_17);

        m_strEdUserId = new QLineEdit(m_zoneUserConfig);
        m_strEdUserId->setObjectName(QStringLiteral("m_strEdUserId"));
        m_strEdUserId->setMinimumSize(QSize(230, 32));
        m_strEdUserId->setMaximumSize(QSize(230, 32));
        m_strEdUserId->setFocusPolicy(Qt::ClickFocus);
        m_strEdUserId->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"     padding-left: 10px;\n"
" }\n"
"\n"
" QLineEdit:!hover{\n"
"     border: 1px solid #e6e6e6;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #fdfdfd;\n"
"	 color: #666666;\n"
" }\n"
"\n"
" QLineEdit:hover:!focus{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #fdfdfd;\n"
"	 color: #666666;\n"
" }\n"
"\n"
" QLineEdit:focus{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #ffffff;\n"
" }"));

        horizontalLayout_16->addWidget(m_strEdUserId);


        verticalLayout_8->addLayout(horizontalLayout_16);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(0);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        m_lbUserName = new QLabel(m_zoneUserConfig);
        m_lbUserName->setObjectName(QStringLiteral("m_lbUserName"));
        m_lbUserName->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        horizontalLayout_17->addWidget(m_lbUserName);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_18);

        m_strEdUserName = new QLineEdit(m_zoneUserConfig);
        m_strEdUserName->setObjectName(QStringLiteral("m_strEdUserName"));
        m_strEdUserName->setMinimumSize(QSize(230, 32));
        m_strEdUserName->setMaximumSize(QSize(230, 32));
        m_strEdUserName->setFocusPolicy(Qt::StrongFocus);
        m_strEdUserName->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"     padding-left: 10px;\n"
" }\n"
"\n"
" QLineEdit:!hover{\n"
"     border: 1px solid #e6e6e6;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #fdfdfd;\n"
"	 color: #666666;\n"
" }\n"
"\n"
" QLineEdit:hover:!focus{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #fdfdfd;\n"
"	 color: #666666;\n"
" }\n"
"\n"
" QLineEdit:focus{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #ffffff;\n"
" }"));

        horizontalLayout_17->addWidget(m_strEdUserName);


        verticalLayout_8->addLayout(horizontalLayout_17);


        verticalLayout_10->addLayout(verticalLayout_8);


        verticalLayout_3->addLayout(verticalLayout_10);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        label_4 = new QLabel(m_zoneUserConfig);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8("font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;"));

        verticalLayout_2->addWidget(label_4);

        verticalSpacer_9 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_9);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, -1, 0, -1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_7 = new QLabel(m_zoneUserConfig);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setStyleSheet(QString::fromUtf8("font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;"));

        horizontalLayout->addWidget(label_7);

        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_22);

        m_cbAppVersion = new QComboBox(m_zoneUserConfig);
        m_cbAppVersion->setObjectName(QStringLiteral("m_cbAppVersion"));
        m_cbAppVersion->setMinimumSize(QSize(120, 30));
        m_cbAppVersion->setMaximumSize(QSize(120, 30));
        m_cbAppVersion->setStyleSheet(QString::fromUtf8(" QComboBox{\n"
"     padding-left: 10px;\n"
" }\n"
"\n"
" QComboBox:!enabled{\n"
"    border: 1px solid #e6e6e6;\n"
"    border-radius: 2px;\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"    font-size: 16px;\n"
"	background-color: #fdfdfd;\n"
"	color: #cccccc;\n"
" }\n"
"\n"
" QComboBox:enabled:!hover{\n"
"    border: 1px solid #e6e6e6;\n"
"    border-radius: 2px;\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"    font-size: 16px;\n"
"	background-color: #fdfdfd;\n"
"	color: #666666;\n"
"}\n"
"QComboBox:enabled:hover{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #fdfdfd;\n"
"	 color: #666666;\n"
"}\n"
"\n"
"QComboBox::drop-down{\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 20px;\n"
" \n"
"    border-left-width: 1px;\n"
"\n"
"    border-top-right-radius: 2px; /* same radi"
                        "us as the QComboBox */\n"
"    border-bottom-right-radius: 2px;\n"
"\n"
" }\n"
"\n"
" QComboBox::down-arrow{\n"
"\n"
"     border-image: url(:/Resources/images/down_arrow.png);\n"
" }\n"
"\n"
" \n"
"  QComboBox QAbstractItemView{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"     border: 1px solid #0e88eb;\n"
"	 background-color: #ffffff;\n"
"	 border-radius: 2px;\n"
"	 \n"
"  }\n"
"\n"
" QComboBox QAbstractItemView::item{\n"
"     \n"
"     height: 32px;\n"
"	 font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
"	 background-color: #ffffff;\n"
"	 padding-left: 10px;\n"
"	 padding-right: 10px;\n"
" }\n"
"\n"
" QComboBox QAbstractItemView::item:hover{\n"
"     \n"
"     height: 32px;\n"
"	 font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #ffffff;\n"
"	 background-color: #0e88eb;\n"
"	 padding-left: 10px;\n"
"	 padding-right: 10px;\n"
" }"));

        horizontalLayout->addWidget(m_cbAppVersion);


        horizontalLayout_3->addLayout(horizontalLayout);

        horizontalSpacer_3 = new QSpacerItem(10, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_8 = new QLabel(m_zoneUserConfig);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setStyleSheet(QString::fromUtf8("font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;"));

        horizontalLayout_2->addWidget(label_8);

        horizontalSpacer_12 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_12);

        m_switchTestEnv = new ZegoSwitchButton(m_zoneUserConfig);
        m_switchTestEnv->setObjectName(QStringLiteral("m_switchTestEnv"));
        m_switchTestEnv->setMinimumSize(QSize(32, 16));
        m_switchTestEnv->setMaximumSize(QSize(32, 16));
        m_switchTestEnv->setStyleSheet(QLatin1String("QPushButton:!checked{\n"
"     border-image: url(:/Resources/images/switch_off.png);\n"
" }\n"
"\n"
" QPushButton:checked{\n"
"     border-image: url(:/Resources/images/switch_on.png);\n"
" }"));
        m_switchTestEnv->setCheckable(true);

        horizontalLayout_2->addWidget(m_switchTestEnv);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(0);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        m_lbAPPID_2 = new QLabel(m_zoneUserConfig);
        m_lbAPPID_2->setObjectName(QStringLiteral("m_lbAPPID_2"));
        m_lbAPPID_2->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        horizontalLayout_18->addWidget(m_lbAPPID_2);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_19);

        m_strEdAPPID = new QLineEdit(m_zoneUserConfig);
        m_strEdAPPID->setObjectName(QStringLiteral("m_strEdAPPID"));
        m_strEdAPPID->setMinimumSize(QSize(230, 32));
        m_strEdAPPID->setMaximumSize(QSize(230, 32));
        m_strEdAPPID->setFocusPolicy(Qt::ClickFocus);
        m_strEdAPPID->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"     padding-left: 10px;\n"
" }\n"
"\n"
" QLineEdit:!hover{\n"
"     border: 1px solid #e6e6e6;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #fdfdfd;\n"
"	 color: #666666;\n"
" }\n"
"\n"
" QLineEdit:hover:!focus{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #fdfdfd;\n"
"	 color: #666666;\n"
" }\n"
"\n"
" QLineEdit:focus{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #ffffff;\n"
" }"));

        horizontalLayout_18->addWidget(m_strEdAPPID);


        verticalLayout->addLayout(horizontalLayout_18);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(0);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        m_lbAPPSign_2 = new QLabel(m_zoneUserConfig);
        m_lbAPPSign_2->setObjectName(QStringLiteral("m_lbAPPSign_2"));
        m_lbAPPSign_2->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        horizontalLayout_19->addWidget(m_lbAPPSign_2);

        horizontalSpacer_20 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_20);

        m_strEdAPPSign = new QLineEdit(m_zoneUserConfig);
        m_strEdAPPSign->setObjectName(QStringLiteral("m_strEdAPPSign"));
        m_strEdAPPSign->setMinimumSize(QSize(230, 32));
        m_strEdAPPSign->setMaximumSize(QSize(230, 32));
        m_strEdAPPSign->setFocusPolicy(Qt::StrongFocus);
        m_strEdAPPSign->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"     padding-left: 10px;\n"
" }\n"
"\n"
" QLineEdit:!hover{\n"
"     border: 1px solid #e6e6e6;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #fdfdfd;\n"
"	 color: #666666;\n"
" }\n"
"\n"
" QLineEdit:hover:!focus{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #fdfdfd;\n"
"	 color: #666666;\n"
" }\n"
"\n"
" QLineEdit:focus{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #ffffff;\n"
" }"));

        horizontalLayout_19->addWidget(m_strEdAPPSign);


        verticalLayout->addLayout(horizontalLayout_19);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_4);


        verticalLayout_3->addLayout(verticalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        m_bUploadLog = new QPushButton(m_zoneUserConfig);
        m_bUploadLog->setObjectName(QStringLiteral("m_bUploadLog"));
        m_bUploadLog->setMinimumSize(QSize(100, 32));
        m_bUploadLog->setMaximumSize(QSize(100, 32));
        m_bUploadLog->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"    padding-left: 10px;\n"
"    padding-right: 10px;\n"
"}\n"
"\n"
"QPushButton:!hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 border-radius: 4px;\n"
"     border: 1px solid #0e88eb;\n"
"     background-color: #ffffff;\n"
"     color: #0e88eb;\n"
" }\n"
"\n"
" QPushButton:hover:!pressed{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 border-radius: 4px;\n"
"     border: 1px solid #0e88eb;\n"
"     background-color: #0e88eb;\n"
"     color: #ffffff;\n"
" }\n"
"\n"
" QPushButton:hover:pressed{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 border-radius: 4px;\n"
"     border: 1px solid #0d80de;\n"
"     background-color: #0d80de;\n"
"     color: #ffffff;\n"
" }"));

        horizontalLayout_4->addWidget(m_bUploadLog);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);

        m_bSaveSettings = new QPushButton(m_zoneUserConfig);
        m_bSaveSettings->setObjectName(QStringLiteral("m_bSaveSettings"));
        sizePolicy1.setHeightForWidth(m_bSaveSettings->sizePolicy().hasHeightForWidth());
        m_bSaveSettings->setSizePolicy(sizePolicy1);
        m_bSaveSettings->setMinimumSize(QSize(100, 32));
        m_bSaveSettings->setMaximumSize(QSize(100, 32));
        m_bSaveSettings->setStyleSheet(QString::fromUtf8("QPushButton:!enabled{\n"
"		font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"		font-size: 16px;\n"
"		border: 1px solid #cccccc;\n"
"		border-radius: 4px;\n"
"		background-color: #ffffff;\n"
"		color: #cccccc;\n"
"}\n"
"\n"
"QPushButton:enabled:!hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 border-radius: 4px;\n"
"     border: 1px solid #0e88eb;\n"
"     background-color: #ffffff;\n"
"     color: #0e88eb;\n"
" }\n"
"\n"
" QPushButton:enabled:hover:!pressed{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 border-radius: 4px;\n"
"     border: 1px solid #0e88eb;\n"
"     background-color: #0e88eb;\n"
"     color: #ffffff;\n"
" }\n"
"\n"
" QPushButton:enabled:hover:pressed{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 border-radius: 4px;\n"
"     border: 1px solid #0d80de;\n"
"     background-color: #0d80de;\n"
"     co"
                        "lor: #ffffff;\n"
" }"));

        horizontalLayout_4->addWidget(m_bSaveSettings);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);


        verticalLayout_3->addLayout(horizontalLayout_4);


        horizontalLayout_13->addWidget(m_zoneUserConfig);

        horizontalSpacer_10 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_10);


        verticalLayout_7->addLayout(horizontalLayout_13);

        verticalLayout_7->setStretch(0, 1);
        verticalLayout_7->setStretch(2, 6);

        verticalLayout_9->addLayout(verticalLayout_7);

        verticalSpacer_19 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_9->addItem(verticalSpacer_19);


        verticalLayout_11->addLayout(verticalLayout_9);


        retranslateUi(ZegoSettingsDialog);

        QMetaObject::connectSlotsByName(ZegoSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *ZegoSettingsDialog)
    {
        ZegoSettingsDialog->setWindowTitle(QApplication::translate("ZegoSettingsDialog", "ZegoAudioLive", Q_NULLPTR));
        m_lbTitle->setText(QApplication::translate("ZegoSettingsDialog", "\350\256\276\347\275\256", Q_NULLPTR));
        m_bMin->setText(QString());
        m_bClose->setText(QString());
        m_lbSdkTitle->setText(QApplication::translate("ZegoSettingsDialog", "SDK\347\211\210\346\234\254\357\274\232", Q_NULLPTR));
        m_lbSdkVersion->setText(QApplication::translate("ZegoSettingsDialog", "Version", Q_NULLPTR));
        m_lbAccount->setText(QApplication::translate("ZegoSettingsDialog", "Account", Q_NULLPTR));
        m_lbUserId->setText(QApplication::translate("ZegoSettingsDialog", "\347\224\250\346\210\267ID", Q_NULLPTR));
        m_lbUserName->setText(QApplication::translate("ZegoSettingsDialog", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        label_4->setText(QApplication::translate("ZegoSettingsDialog", "Environment", Q_NULLPTR));
        label_7->setText(QApplication::translate("ZegoSettingsDialog", "App \347\211\210\346\234\254", Q_NULLPTR));
        label_8->setText(QApplication::translate("ZegoSettingsDialog", "\346\265\213\350\257\225\347\216\257\345\242\203", Q_NULLPTR));
        m_switchTestEnv->setText(QString());
        m_lbAPPID_2->setText(QApplication::translate("ZegoSettingsDialog", "APP ID", Q_NULLPTR));
        m_lbAPPSign_2->setText(QApplication::translate("ZegoSettingsDialog", "APP Sign", Q_NULLPTR));
        m_bUploadLog->setText(QApplication::translate("ZegoSettingsDialog", "\344\270\212\344\274\240\346\227\245\345\277\227", Q_NULLPTR));
        m_bSaveSettings->setText(QApplication::translate("ZegoSettingsDialog", "\344\277\235\345\255\230\350\256\276\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ZegoSettingsDialog: public Ui_ZegoSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZEGOSETTINGSDIALOG_H

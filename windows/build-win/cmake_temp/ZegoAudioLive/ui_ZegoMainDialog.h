/********************************************************************************
** Form generated from reading UI file 'ZegoMainDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZEGOMAINDIALOG_H
#define UI_ZEGOMAINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <ZegoImageButton.h>

QT_BEGIN_NAMESPACE

class Ui_ZegoMainDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QWidget *m_zoneTitle;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_6;
    QLabel *m_title;
    QSpacerItem *horizontalSpacer_5;
    QLabel *m_lbVersion;
    QSpacerItem *horizontalSpacer_7;
    ZegoImageButton *m_bJumpToNet;
    ZegoImageButton *m_bMin;
    ZegoImageButton *m_bClose;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QLabel *m_lbTitle;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLineEdit *m_edRoomID;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_bSettings;
    QPushButton *m_bEnterRoom;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QDialog *ZegoMainDialog)
    {
        if (ZegoMainDialog->objectName().isEmpty())
            ZegoMainDialog->setObjectName(QStringLiteral("ZegoMainDialog"));
        ZegoMainDialog->resize(500, 250);
        ZegoMainDialog->setMinimumSize(QSize(500, 250));
        ZegoMainDialog->setMaximumSize(QSize(500, 250));
        ZegoMainDialog->setStyleSheet(QStringLiteral("background-color: #fafafa;"));
        verticalLayout_3 = new QVBoxLayout(ZegoMainDialog);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        m_zoneTitle = new QWidget(ZegoMainDialog);
        m_zoneTitle->setObjectName(QStringLiteral("m_zoneTitle"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_zoneTitle->sizePolicy().hasHeightForWidth());
        m_zoneTitle->setSizePolicy(sizePolicy);
        m_zoneTitle->setMinimumSize(QSize(0, 40));
        m_zoneTitle->setMaximumSize(QSize(16777215, 40));
        m_zoneTitle->setStyleSheet(QStringLiteral("background-color: #0e88eb;"));
        horizontalLayout_5 = new QHBoxLayout(m_zoneTitle);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        m_title = new QLabel(m_zoneTitle);
        m_title->setObjectName(QStringLiteral("m_title"));
        m_title->setStyleSheet(QString::fromUtf8("font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"	 font-size: 16px;\n"
"     color: #ffffff;"));

        horizontalLayout_4->addWidget(m_title);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        m_lbVersion = new QLabel(m_zoneTitle);
        m_lbVersion->setObjectName(QStringLiteral("m_lbVersion"));
        m_lbVersion->setStyleSheet(QString::fromUtf8("font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 12px;\n"
"color: #dddddd;"));

        horizontalLayout_4->addWidget(m_lbVersion);

        horizontalSpacer_7 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        m_bJumpToNet = new ZegoImageButton(m_zoneTitle);
        m_bJumpToNet->setObjectName(QStringLiteral("m_bJumpToNet"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_bJumpToNet->sizePolicy().hasHeightForWidth());
        m_bJumpToNet->setSizePolicy(sizePolicy1);
        m_bJumpToNet->setMinimumSize(QSize(40, 40));
        m_bJumpToNet->setMaximumSize(QSize(40, 40));
        m_bJumpToNet->setFocusPolicy(Qt::NoFocus);
        m_bJumpToNet->setStyleSheet(QLatin1String("QPushButton:!hover{\n"
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
        icon.addFile(QStringLiteral(":/Resources/images/official.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_bJumpToNet->setIcon(icon);

        horizontalLayout_4->addWidget(m_bJumpToNet);

        m_bMin = new ZegoImageButton(m_zoneTitle);
        m_bMin->setObjectName(QStringLiteral("m_bMin"));
        sizePolicy1.setHeightForWidth(m_bMin->sizePolicy().hasHeightForWidth());
        m_bMin->setSizePolicy(sizePolicy1);
        m_bMin->setMinimumSize(QSize(40, 40));
        m_bMin->setMaximumSize(QSize(40, 40));
        m_bMin->setFocusPolicy(Qt::NoFocus);
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
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Resources/images/min.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_bMin->setIcon(icon1);

        horizontalLayout_4->addWidget(m_bMin);

        m_bClose = new ZegoImageButton(m_zoneTitle);
        m_bClose->setObjectName(QStringLiteral("m_bClose"));
        sizePolicy1.setHeightForWidth(m_bClose->sizePolicy().hasHeightForWidth());
        m_bClose->setSizePolicy(sizePolicy1);
        m_bClose->setMinimumSize(QSize(50, 40));
        m_bClose->setMaximumSize(QSize(50, 40));
        m_bClose->setFocusPolicy(Qt::NoFocus);
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
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Resources/images/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_bClose->setIcon(icon2);

        horizontalLayout_4->addWidget(m_bClose);


        horizontalLayout_5->addLayout(horizontalLayout_4);


        verticalLayout_2->addWidget(m_zoneTitle);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 0, -1, 0);
        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_3);

        m_lbTitle = new QLabel(ZegoMainDialog);
        m_lbTitle->setObjectName(QStringLiteral("m_lbTitle"));
        sizePolicy.setHeightForWidth(m_lbTitle->sizePolicy().hasHeightForWidth());
        m_lbTitle->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        m_lbTitle->setFont(font);
        m_lbTitle->setStyleSheet(QString::fromUtf8("font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 30px;\n"
"color: #666666;"));
        m_lbTitle->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(m_lbTitle);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        m_edRoomID = new QLineEdit(ZegoMainDialog);
        m_edRoomID->setObjectName(QStringLiteral("m_edRoomID"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_edRoomID->sizePolicy().hasHeightForWidth());
        m_edRoomID->setSizePolicy(sizePolicy2);
        m_edRoomID->setMinimumSize(QSize(240, 40));
        m_edRoomID->setMaximumSize(QSize(240, 16777215));
        m_edRoomID->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
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

        horizontalLayout_2->addWidget(m_edRoomID);

        horizontalSpacer_2 = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        m_bSettings = new QPushButton(ZegoMainDialog);
        m_bSettings->setObjectName(QStringLiteral("m_bSettings"));
        m_bSettings->setMinimumSize(QSize(100, 30));
        m_bSettings->setFocusPolicy(Qt::NoFocus);
        m_bSettings->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
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

        horizontalLayout->addWidget(m_bSettings);

        m_bEnterRoom = new QPushButton(ZegoMainDialog);
        m_bEnterRoom->setObjectName(QStringLiteral("m_bEnterRoom"));
        m_bEnterRoom->setMinimumSize(QSize(100, 30));
        m_bEnterRoom->setStyleSheet(QString::fromUtf8("QPushButton:!enabled{\n"
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

        horizontalLayout->addWidget(m_bEnterRoom);


        horizontalLayout_3->addLayout(horizontalLayout);

        horizontalSpacer_4 = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_4);


        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(ZegoMainDialog);

        QMetaObject::connectSlotsByName(ZegoMainDialog);
    } // setupUi

    void retranslateUi(QDialog *ZegoMainDialog)
    {
        ZegoMainDialog->setWindowTitle(QApplication::translate("ZegoMainDialog", "ZegoAudioLive", Q_NULLPTR));
        m_title->setText(QApplication::translate("ZegoMainDialog", "AudioLive (\345\233\275\345\206\205\347\211\210)", Q_NULLPTR));
        m_lbVersion->setText(QApplication::translate("ZegoMainDialog", "version", Q_NULLPTR));
        m_bJumpToNet->setText(QString());
        m_bMin->setText(QString());
        m_bClose->setText(QString());
        m_lbTitle->setText(QApplication::translate("ZegoMainDialog", "ZegoAudioLive", Q_NULLPTR));
        m_edRoomID->setPlaceholderText(QApplication::translate("ZegoMainDialog", "\350\257\267\350\276\223\345\205\245\346\210\277\351\227\264\345\217\267", Q_NULLPTR));
        m_bSettings->setText(QApplication::translate("ZegoMainDialog", "\350\256\276\347\275\256", Q_NULLPTR));
        m_bEnterRoom->setText(QApplication::translate("ZegoMainDialog", "\347\241\256\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ZegoMainDialog: public Ui_ZegoMainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZEGOMAINDIALOG_H

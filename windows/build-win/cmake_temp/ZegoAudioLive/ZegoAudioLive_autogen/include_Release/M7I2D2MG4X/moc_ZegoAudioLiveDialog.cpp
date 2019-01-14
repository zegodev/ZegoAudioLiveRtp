/****************************************************************************
** Meta object code from reading C++ file 'ZegoAudioLiveDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../ZegoAudioLive/Dialog/ZegoAudioLiveDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ZegoAudioLiveDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ZegoAudioLiveDialog_t {
    QByteArrayData data[68];
    char stringdata0[969];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZegoAudioLiveDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZegoAudioLiveDialog_t qt_meta_stringdata_ZegoAudioLiveDialog = {
    {
QT_MOC_LITERAL(0, 0, 19), // "ZegoAudioLiveDialog"
QT_MOC_LITERAL(1, 20, 12), // "sigCloseView"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 11), // "OnLoginRoom"
QT_MOC_LITERAL(4, 46, 9), // "errorCode"
QT_MOC_LITERAL(5, 56, 9), // "strRoomID"
QT_MOC_LITERAL(6, 66, 15), // "OnStreamUpdated"
QT_MOC_LITERAL(7, 82, 9), // "StreamPtr"
QT_MOC_LITERAL(8, 92, 7), // "pStream"
QT_MOC_LITERAL(9, 100, 31), // "AUDIOROOM::ZegoStreamUpdateType"
QT_MOC_LITERAL(10, 132, 4), // "type"
QT_MOC_LITERAL(11, 137, 20), // "OnPublishStateUpdate"
QT_MOC_LITERAL(12, 158, 9), // "stateCode"
QT_MOC_LITERAL(13, 168, 8), // "streamId"
QT_MOC_LITERAL(14, 177, 10), // "streamInfo"
QT_MOC_LITERAL(15, 188, 17), // "OnPlayStateUpdate"
QT_MOC_LITERAL(16, 206, 12), // "OnDisconnect"
QT_MOC_LITERAL(17, 219, 6), // "roomId"
QT_MOC_LITERAL(18, 226, 9), // "OnKickOut"
QT_MOC_LITERAL(19, 236, 6), // "reason"
QT_MOC_LITERAL(20, 243, 19), // "OnPlayQualityUpdate"
QT_MOC_LITERAL(21, 263, 8), // "audioKBS"
QT_MOC_LITERAL(22, 272, 14), // "audioBreakRate"
QT_MOC_LITERAL(23, 287, 3), // "rtt"
QT_MOC_LITERAL(24, 291, 8), // "lostRate"
QT_MOC_LITERAL(25, 300, 22), // "OnPublishQualityUpdate"
QT_MOC_LITERAL(26, 323, 12), // "OnUserUpdate"
QT_MOC_LITERAL(27, 336, 16), // "QVector<QString>"
QT_MOC_LITERAL(28, 353, 7), // "userIDs"
QT_MOC_LITERAL(29, 361, 9), // "userNames"
QT_MOC_LITERAL(30, 371, 12), // "QVector<int>"
QT_MOC_LITERAL(31, 384, 9), // "userFlags"
QT_MOC_LITERAL(32, 394, 9), // "userRoles"
QT_MOC_LITERAL(33, 404, 9), // "userCount"
QT_MOC_LITERAL(34, 414, 29), // "AUDIOROOM::ZegoUserUpdateType"
QT_MOC_LITERAL(35, 444, 25), // "OnCaptureSoundLevelUpdate"
QT_MOC_LITERAL(36, 470, 10), // "soundLevel"
QT_MOC_LITERAL(37, 481, 18), // "OnSoundLevelUpdate"
QT_MOC_LITERAL(38, 500, 30), // "QVector<QPair<QString,float> >"
QT_MOC_LITERAL(39, 531, 14), // "soundLevelList"
QT_MOC_LITERAL(40, 546, 24), // "OnStreamExtraInfoUpdated"
QT_MOC_LITERAL(41, 571, 18), // "QVector<StreamPtr>"
QT_MOC_LITERAL(42, 590, 10), // "streamList"
QT_MOC_LITERAL(43, 601, 9), // "strRoomId"
QT_MOC_LITERAL(44, 611, 12), // "OnAVKitEvent"
QT_MOC_LITERAL(45, 624, 5), // "event"
QT_MOC_LITERAL(46, 630, 19), // "on_m_bClose_clicked"
QT_MOC_LITERAL(47, 650, 17), // "on_m_bMax_clicked"
QT_MOC_LITERAL(48, 668, 17), // "on_m_bMin_clicked"
QT_MOC_LITERAL(49, 686, 22), // "on_m_switchMic_clicked"
QT_MOC_LITERAL(50, 709, 26), // "on_m_switchSpeaker_clicked"
QT_MOC_LITERAL(51, 736, 12), // "OnProgChange"
QT_MOC_LITERAL(52, 749, 24), // "OnSwitchAudioInputDevice"
QT_MOC_LITERAL(53, 774, 2), // "id"
QT_MOC_LITERAL(54, 777, 25), // "OnSwitchAudioOutputDevice"
QT_MOC_LITERAL(55, 803, 14), // "OnMicIdChanged"
QT_MOC_LITERAL(56, 818, 5), // "micId"
QT_MOC_LITERAL(57, 824, 18), // "OnSpeakerIdChanged"
QT_MOC_LITERAL(58, 843, 9), // "speakerId"
QT_MOC_LITERAL(59, 853, 18), // "OnMicVolumeChanged"
QT_MOC_LITERAL(60, 872, 1), // "v"
QT_MOC_LITERAL(61, 874, 22), // "OnSpeakerVolumeChanged"
QT_MOC_LITERAL(62, 897, 13), // "OnDeviceAdded"
QT_MOC_LITERAL(63, 911, 10), // "deviceName"
QT_MOC_LITERAL(64, 922, 15), // "OnDeviceDeleted"
QT_MOC_LITERAL(65, 938, 5), // "index"
QT_MOC_LITERAL(66, 944, 15), // "OnMicVolumeMute"
QT_MOC_LITERAL(67, 960, 8) // "bEnabled"

    },
    "ZegoAudioLiveDialog\0sigCloseView\0\0"
    "OnLoginRoom\0errorCode\0strRoomID\0"
    "OnStreamUpdated\0StreamPtr\0pStream\0"
    "AUDIOROOM::ZegoStreamUpdateType\0type\0"
    "OnPublishStateUpdate\0stateCode\0streamId\0"
    "streamInfo\0OnPlayStateUpdate\0OnDisconnect\0"
    "roomId\0OnKickOut\0reason\0OnPlayQualityUpdate\0"
    "audioKBS\0audioBreakRate\0rtt\0lostRate\0"
    "OnPublishQualityUpdate\0OnUserUpdate\0"
    "QVector<QString>\0userIDs\0userNames\0"
    "QVector<int>\0userFlags\0userRoles\0"
    "userCount\0AUDIOROOM::ZegoUserUpdateType\0"
    "OnCaptureSoundLevelUpdate\0soundLevel\0"
    "OnSoundLevelUpdate\0QVector<QPair<QString,float> >\0"
    "soundLevelList\0OnStreamExtraInfoUpdated\0"
    "QVector<StreamPtr>\0streamList\0strRoomId\0"
    "OnAVKitEvent\0event\0on_m_bClose_clicked\0"
    "on_m_bMax_clicked\0on_m_bMin_clicked\0"
    "on_m_switchMic_clicked\0"
    "on_m_switchSpeaker_clicked\0OnProgChange\0"
    "OnSwitchAudioInputDevice\0id\0"
    "OnSwitchAudioOutputDevice\0OnMicIdChanged\0"
    "micId\0OnSpeakerIdChanged\0speakerId\0"
    "OnMicVolumeChanged\0v\0OnSpeakerVolumeChanged\0"
    "OnDeviceAdded\0deviceName\0OnDeviceDeleted\0"
    "index\0OnMicVolumeMute\0bEnabled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZegoAudioLiveDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  159,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    2,  160,    2, 0x09 /* Protected */,
       6,    3,  165,    2, 0x09 /* Protected */,
      11,    3,  172,    2, 0x09 /* Protected */,
      15,    2,  179,    2, 0x09 /* Protected */,
      16,    2,  184,    2, 0x09 /* Protected */,
      18,    2,  189,    2, 0x09 /* Protected */,
      20,    5,  194,    2, 0x09 /* Protected */,
      25,    4,  205,    2, 0x09 /* Protected */,
      26,    6,  214,    2, 0x09 /* Protected */,
      35,    2,  227,    2, 0x09 /* Protected */,
      37,    1,  232,    2, 0x09 /* Protected */,
      40,    2,  235,    2, 0x09 /* Protected */,
      44,    1,  240,    2, 0x09 /* Protected */,
      46,    0,  243,    2, 0x08 /* Private */,
      47,    0,  244,    2, 0x08 /* Private */,
      48,    0,  245,    2, 0x08 /* Private */,
      49,    0,  246,    2, 0x08 /* Private */,
      50,    0,  247,    2, 0x08 /* Private */,
      51,    0,  248,    2, 0x08 /* Private */,
      52,    1,  249,    2, 0x08 /* Private */,
      54,    1,  252,    2, 0x08 /* Private */,
      55,    1,  255,    2, 0x08 /* Private */,
      57,    1,  258,    2, 0x08 /* Private */,
      59,    1,  261,    2, 0x08 /* Private */,
      61,    1,  264,    2, 0x08 /* Private */,
      62,    2,  267,    2, 0x08 /* Private */,
      64,    2,  272,    2, 0x08 /* Private */,
      66,    1,  277,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    4,    5,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 7, 0x80000000 | 9,    5,    8,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, 0x80000000 | 7,   12,   13,   14,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,   12,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    4,   17,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   19,   17,
    QMetaType::Void, QMetaType::QString, QMetaType::Double, QMetaType::Double, QMetaType::Int, QMetaType::Int,   13,   21,   22,   23,   24,
    QMetaType::Void, QMetaType::QString, QMetaType::Double, QMetaType::Int, QMetaType::Int,   13,   21,   23,   24,
    QMetaType::Void, 0x80000000 | 27, 0x80000000 | 27, 0x80000000 | 30, 0x80000000 | 30, QMetaType::UInt, 0x80000000 | 34,   28,   29,   31,   32,   33,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::Float,   13,   36,
    QMetaType::Void, 0x80000000 | 38,   39,
    QMetaType::Void, 0x80000000 | 41, QMetaType::QString,   42,   43,
    QMetaType::Void, QMetaType::Int,   45,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   53,
    QMetaType::Void, QMetaType::Int,   53,
    QMetaType::Void, QMetaType::QString,   56,
    QMetaType::Void, QMetaType::QString,   58,
    QMetaType::Void, QMetaType::Int,   60,
    QMetaType::Void, QMetaType::Int,   60,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   10,   63,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   65,
    QMetaType::Void, QMetaType::Bool,   67,

       0        // eod
};

void ZegoAudioLiveDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZegoAudioLiveDialog *_t = static_cast<ZegoAudioLiveDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigCloseView(); break;
        case 1: _t->OnLoginRoom((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->OnStreamUpdated((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< StreamPtr(*)>(_a[2])),(*reinterpret_cast< AUDIOROOM::ZegoStreamUpdateType(*)>(_a[3]))); break;
        case 3: _t->OnPublishStateUpdate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< StreamPtr(*)>(_a[3]))); break;
        case 4: _t->OnPlayStateUpdate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< StreamPtr(*)>(_a[2]))); break;
        case 5: _t->OnDisconnect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->OnKickOut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 7: _t->OnPlayQualityUpdate((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 8: _t->OnPublishQualityUpdate((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 9: _t->OnUserUpdate((*reinterpret_cast< QVector<QString>(*)>(_a[1])),(*reinterpret_cast< QVector<QString>(*)>(_a[2])),(*reinterpret_cast< QVector<int>(*)>(_a[3])),(*reinterpret_cast< QVector<int>(*)>(_a[4])),(*reinterpret_cast< uint(*)>(_a[5])),(*reinterpret_cast< AUDIOROOM::ZegoUserUpdateType(*)>(_a[6]))); break;
        case 10: _t->OnCaptureSoundLevelUpdate((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 11: _t->OnSoundLevelUpdate((*reinterpret_cast< QVector<QPair<QString,float> >(*)>(_a[1]))); break;
        case 12: _t->OnStreamExtraInfoUpdated((*reinterpret_cast< QVector<StreamPtr>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 13: _t->OnAVKitEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->on_m_bClose_clicked(); break;
        case 15: _t->on_m_bMax_clicked(); break;
        case 16: _t->on_m_bMin_clicked(); break;
        case 17: _t->on_m_switchMic_clicked(); break;
        case 18: _t->on_m_switchSpeaker_clicked(); break;
        case 19: _t->OnProgChange(); break;
        case 20: _t->OnSwitchAudioInputDevice((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->OnSwitchAudioOutputDevice((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->OnMicIdChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 23: _t->OnSpeakerIdChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 24: _t->OnMicVolumeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->OnSpeakerVolumeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->OnDeviceAdded((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 27: _t->OnDeviceDeleted((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 28: _t->OnMicVolumeMute((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QString> >(); break;
            case 3:
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ZegoAudioLiveDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoAudioLiveDialog::sigCloseView)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ZegoAudioLiveDialog::staticMetaObject = {
    { &ZegoDialog::staticMetaObject, qt_meta_stringdata_ZegoAudioLiveDialog.data,
      qt_meta_data_ZegoAudioLiveDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ZegoAudioLiveDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZegoAudioLiveDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ZegoAudioLiveDialog.stringdata0))
        return static_cast<void*>(const_cast< ZegoAudioLiveDialog*>(this));
    return ZegoDialog::qt_metacast(_clname);
}

int ZegoAudioLiveDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ZegoDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    }
    return _id;
}

// SIGNAL 0
void ZegoAudioLiveDialog::sigCloseView()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE

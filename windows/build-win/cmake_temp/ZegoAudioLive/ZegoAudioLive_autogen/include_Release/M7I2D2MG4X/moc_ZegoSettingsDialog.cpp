/****************************************************************************
** Meta object code from reading C++ file 'ZegoSettingsDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../ZegoAudioLive/Dialog/ZegoSettingsDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ZegoSettingsDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ZegoSettingsDialog_t {
    QByteArrayData data[11];
    char stringdata0[214];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZegoSettingsDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZegoSettingsDialog_t qt_meta_stringdata_ZegoSettingsDialog = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ZegoSettingsDialog"
QT_MOC_LITERAL(1, 19, 24), // "sigChangedSettingsConfig"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 19), // "on_m_bClose_clicked"
QT_MOC_LITERAL(4, 65, 17), // "on_m_bMin_clicked"
QT_MOC_LITERAL(5, 83, 26), // "on_m_bSaveSettings_clicked"
QT_MOC_LITERAL(6, 110, 23), // "on_m_bUploadLog_clicked"
QT_MOC_LITERAL(7, 134, 26), // "on_m_switchTestEnv_clicked"
QT_MOC_LITERAL(8, 161, 23), // "OnChangedSettingsConfig"
QT_MOC_LITERAL(9, 185, 25), // "OnComboBoxCheckAppVersion"
QT_MOC_LITERAL(10, 211, 2) // "id"

    },
    "ZegoSettingsDialog\0sigChangedSettingsConfig\0"
    "\0on_m_bClose_clicked\0on_m_bMin_clicked\0"
    "on_m_bSaveSettings_clicked\0"
    "on_m_bUploadLog_clicked\0"
    "on_m_switchTestEnv_clicked\0"
    "OnChangedSettingsConfig\0"
    "OnComboBoxCheckAppVersion\0id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZegoSettingsDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    1,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,

       0        // eod
};

void ZegoSettingsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZegoSettingsDialog *_t = static_cast<ZegoSettingsDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigChangedSettingsConfig(); break;
        case 1: _t->on_m_bClose_clicked(); break;
        case 2: _t->on_m_bMin_clicked(); break;
        case 3: _t->on_m_bSaveSettings_clicked(); break;
        case 4: _t->on_m_bUploadLog_clicked(); break;
        case 5: _t->on_m_switchTestEnv_clicked(); break;
        case 6: _t->OnChangedSettingsConfig(); break;
        case 7: _t->OnComboBoxCheckAppVersion((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ZegoSettingsDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoSettingsDialog::sigChangedSettingsConfig)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ZegoSettingsDialog::staticMetaObject = {
    { &ZegoDialog::staticMetaObject, qt_meta_stringdata_ZegoSettingsDialog.data,
      qt_meta_data_ZegoSettingsDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ZegoSettingsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZegoSettingsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ZegoSettingsDialog.stringdata0))
        return static_cast<void*>(const_cast< ZegoSettingsDialog*>(this));
    return ZegoDialog::qt_metacast(_clname);
}

int ZegoSettingsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ZegoDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ZegoSettingsDialog::sigChangedSettingsConfig()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE

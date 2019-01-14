/****************************************************************************
** Meta object code from reading C++ file 'ZegoMainDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../ZegoAudioLive/Dialog/ZegoMainDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ZegoMainDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ZegoMainDialog_t {
    QByteArrayData data[9];
    char stringdata0[160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZegoMainDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZegoMainDialog_t qt_meta_stringdata_ZegoMainDialog = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ZegoMainDialog"
QT_MOC_LITERAL(1, 15, 17), // "sigCheckEnterRoom"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 16), // "OnCheckEnterRoom"
QT_MOC_LITERAL(4, 51, 23), // "on_m_bEnterRoom_clicked"
QT_MOC_LITERAL(5, 75, 22), // "on_m_bSettings_clicked"
QT_MOC_LITERAL(6, 98, 19), // "on_m_bClose_clicked"
QT_MOC_LITERAL(7, 118, 17), // "on_m_bMin_clicked"
QT_MOC_LITERAL(8, 136, 23) // "on_m_bJumpToNet_clicked"

    },
    "ZegoMainDialog\0sigCheckEnterRoom\0\0"
    "OnCheckEnterRoom\0on_m_bEnterRoom_clicked\0"
    "on_m_bSettings_clicked\0on_m_bClose_clicked\0"
    "on_m_bMin_clicked\0on_m_bJumpToNet_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZegoMainDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ZegoMainDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZegoMainDialog *_t = static_cast<ZegoMainDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigCheckEnterRoom(); break;
        case 1: _t->OnCheckEnterRoom(); break;
        case 2: _t->on_m_bEnterRoom_clicked(); break;
        case 3: _t->on_m_bSettings_clicked(); break;
        case 4: _t->on_m_bClose_clicked(); break;
        case 5: _t->on_m_bMin_clicked(); break;
        case 6: _t->on_m_bJumpToNet_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ZegoMainDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoMainDialog::sigCheckEnterRoom)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ZegoMainDialog::staticMetaObject = {
    { &ZegoDialog::staticMetaObject, qt_meta_stringdata_ZegoMainDialog.data,
      qt_meta_data_ZegoMainDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ZegoMainDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZegoMainDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ZegoMainDialog.stringdata0))
        return static_cast<void*>(const_cast< ZegoMainDialog*>(this));
    return ZegoDialog::qt_metacast(_clname);
}

int ZegoMainDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ZegoDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ZegoMainDialog::sigCheckEnterRoom()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE

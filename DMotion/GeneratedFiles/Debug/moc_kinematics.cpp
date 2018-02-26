/****************************************************************************
** Meta object code from reading C++ file 'kinematics.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../inc/kinematics.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kinematics.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_kinematics_t {
    QByteArrayData data[8];
    char stringdata0[78];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_kinematics_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_kinematics_t qt_meta_stringdata_kinematics = {
    {
QT_MOC_LITERAL(0, 0, 10), // "kinematics"
QT_MOC_LITERAL(1, 11, 14), // "finishedThread"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 11), // "sendProcess"
QT_MOC_LITERAL(4, 39, 1), // "m"
QT_MOC_LITERAL(5, 41, 13), // "sendCaseCount"
QT_MOC_LITERAL(6, 55, 5), // "count"
QT_MOC_LITERAL(7, 61, 16) // "setStopCondition"

    },
    "kinematics\0finishedThread\0\0sendProcess\0"
    "m\0sendCaseCount\0count\0setStopCondition"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_kinematics[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    2,   40,    2, 0x06 /* Public */,
       3,    1,   45,    2, 0x26 /* Public | MethodCloned */,
       5,    1,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Char, QMetaType::QString,    2,    4,
    QMetaType::Void, QMetaType::Char,    2,
    QMetaType::Void, QMetaType::Int,    6,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void kinematics::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        kinematics *_t = static_cast<kinematics *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finishedThread(); break;
        case 1: _t->sendProcess((*reinterpret_cast< char(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->sendProcess((*reinterpret_cast< char(*)>(_a[1]))); break;
        case 3: _t->sendCaseCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setStopCondition(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (kinematics::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&kinematics::finishedThread)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (kinematics::*_t)(char , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&kinematics::sendProcess)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (kinematics::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&kinematics::sendCaseCount)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject kinematics::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_kinematics.data,
      qt_meta_data_kinematics,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *kinematics::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *kinematics::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_kinematics.stringdata0))
        return static_cast<void*>(const_cast< kinematics*>(this));
    return QThread::qt_metacast(_clname);
}

int kinematics::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void kinematics::finishedThread()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void kinematics::sendProcess(char _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 3
void kinematics::sendCaseCount(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE

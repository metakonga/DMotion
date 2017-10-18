/****************************************************************************
** Meta object code from reading C++ file 'DynaMic.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../inc/DynaMic.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DynaMic.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DynaMic_t {
    QByteArrayData data[8];
    char stringdata0[57];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DynaMic_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DynaMic_t qt_meta_stringdata_DynaMic = {
    {
QT_MOC_LITERAL(0, 0, 7), // "DynaMic"
QT_MOC_LITERAL(1, 8, 14), // "finishedThread"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 11), // "sendProcess"
QT_MOC_LITERAL(4, 36, 1), // "m"
QT_MOC_LITERAL(5, 38, 12), // "sendPlotData"
QT_MOC_LITERAL(6, 51, 2), // "xv"
QT_MOC_LITERAL(7, 54, 2) // "yv"

    },
    "DynaMic\0finishedThread\0\0sendProcess\0"
    "m\0sendPlotData\0xv\0yv"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DynaMic[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    2,   35,    2, 0x06 /* Public */,
       3,    1,   40,    2, 0x26 /* Public | MethodCloned */,
       5,    2,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Char, QMetaType::QString,    2,    4,
    QMetaType::Void, QMetaType::Char,    2,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    6,    7,

       0        // eod
};

void DynaMic::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DynaMic *_t = static_cast<DynaMic *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finishedThread(); break;
        case 1: _t->sendProcess((*reinterpret_cast< char(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->sendProcess((*reinterpret_cast< char(*)>(_a[1]))); break;
        case 3: _t->sendPlotData((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DynaMic::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DynaMic::finishedThread)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DynaMic::*_t)(char , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DynaMic::sendProcess)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (DynaMic::*_t)(double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DynaMic::sendPlotData)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject DynaMic::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_DynaMic.data,
      qt_meta_data_DynaMic,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DynaMic::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DynaMic::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DynaMic.stringdata0))
        return static_cast<void*>(const_cast< DynaMic*>(this));
    return QThread::qt_metacast(_clname);
}

int DynaMic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DynaMic::finishedThread()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void DynaMic::sendProcess(char _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 3
void DynaMic::sendPlotData(double _t1, double _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE

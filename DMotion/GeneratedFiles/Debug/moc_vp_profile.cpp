/****************************************************************************
** Meta object code from reading C++ file 'vp_profile.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../inc/vp_profile.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vp_profile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_vp_profile_t {
    QByteArrayData data[15];
    char stringdata0[256];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vp_profile_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vp_profile_t qt_meta_stringdata_vp_profile = {
    {
QT_MOC_LITERAL(0, 0, 10), // "vp_profile"
QT_MOC_LITERAL(1, 11, 12), // "finishDialog"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 25), // "clickRadioButton_Velocity"
QT_MOC_LITERAL(4, 51, 29), // "clickRadioButton_Acceleration"
QT_MOC_LITERAL(5, 81, 23), // "clickRadioButton_Stroke"
QT_MOC_LITERAL(6, 105, 33), // "clickRadioButton_RelativeVelo..."
QT_MOC_LITERAL(7, 139, 30), // "clickRadioButton_VelocityRatio"
QT_MOC_LITERAL(8, 170, 14), // "changeCellItem"
QT_MOC_LITERAL(9, 185, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(10, 203, 13), // "doubleClicked"
QT_MOC_LITERAL(11, 217, 10), // "exportData"
QT_MOC_LITERAL(12, 228, 10), // "importData"
QT_MOC_LITERAL(13, 239, 12), // "changeSeries"
QT_MOC_LITERAL(14, 252, 3) // "idx"

    },
    "vp_profile\0finishDialog\0\0"
    "clickRadioButton_Velocity\0"
    "clickRadioButton_Acceleration\0"
    "clickRadioButton_Stroke\0"
    "clickRadioButton_RelativeVelocity\0"
    "clickRadioButton_VelocityRatio\0"
    "changeCellItem\0QTableWidgetItem*\0"
    "doubleClicked\0exportData\0importData\0"
    "changeSeries\0idx"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vp_profile[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x08 /* Private */,
       3,    0,   72,    2, 0x08 /* Private */,
       4,    0,   73,    2, 0x08 /* Private */,
       5,    0,   74,    2, 0x08 /* Private */,
       6,    0,   75,    2, 0x08 /* Private */,
       7,    0,   76,    2, 0x08 /* Private */,
       8,    1,   77,    2, 0x08 /* Private */,
      10,    1,   80,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    1,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,

       0        // eod
};

void vp_profile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        vp_profile *_t = static_cast<vp_profile *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finishDialog((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->clickRadioButton_Velocity(); break;
        case 2: _t->clickRadioButton_Acceleration(); break;
        case 3: _t->clickRadioButton_Stroke(); break;
        case 4: _t->clickRadioButton_RelativeVelocity(); break;
        case 5: _t->clickRadioButton_VelocityRatio(); break;
        case 6: _t->changeCellItem((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->doubleClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 8: _t->exportData(); break;
        case 9: _t->importData(); break;
        case 10: _t->changeSeries((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject vp_profile::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_vp_profile.data,
      qt_meta_data_vp_profile,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *vp_profile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vp_profile::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_vp_profile.stringdata0))
        return static_cast<void*>(const_cast< vp_profile*>(this));
    return QDialog::qt_metacast(_clname);
}

int vp_profile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'view.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../inc/view.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_view_t {
    QByteArrayData data[22];
    char stringdata0[169];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_view_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_view_t qt_meta_stringdata_view = {
    {
QT_MOC_LITERAL(0, 0, 4), // "view"
QT_MOC_LITERAL(1, 5, 16), // "selectionChanged"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 6), // "fitAll"
QT_MOC_LITERAL(4, 30, 7), // "fitArea"
QT_MOC_LITERAL(5, 38, 4), // "zoom"
QT_MOC_LITERAL(6, 43, 3), // "pan"
QT_MOC_LITERAL(7, 47, 9), // "globalPan"
QT_MOC_LITERAL(8, 57, 5), // "front"
QT_MOC_LITERAL(9, 63, 4), // "back"
QT_MOC_LITERAL(10, 68, 3), // "top"
QT_MOC_LITERAL(11, 72, 6), // "bottom"
QT_MOC_LITERAL(12, 79, 4), // "left"
QT_MOC_LITERAL(13, 84, 5), // "right"
QT_MOC_LITERAL(14, 90, 3), // "axo"
QT_MOC_LITERAL(15, 94, 8), // "rotation"
QT_MOC_LITERAL(16, 103, 5), // "reset"
QT_MOC_LITERAL(17, 109, 5), // "hlrOn"
QT_MOC_LITERAL(18, 115, 6), // "hlrOff"
QT_MOC_LITERAL(19, 122, 12), // "onBackground"
QT_MOC_LITERAL(20, 135, 16), // "onEnvironmentMap"
QT_MOC_LITERAL(21, 152, 16) // "onRaytraceAction"

    },
    "view\0selectionChanged\0\0fitAll\0fitArea\0"
    "zoom\0pan\0globalPan\0front\0back\0top\0"
    "bottom\0left\0right\0axo\0rotation\0reset\0"
    "hlrOn\0hlrOff\0onBackground\0onEnvironmentMap\0"
    "onRaytraceAction"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_view[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,  115,    2, 0x0a /* Public */,
       4,    0,  116,    2, 0x0a /* Public */,
       5,    0,  117,    2, 0x0a /* Public */,
       6,    0,  118,    2, 0x0a /* Public */,
       7,    0,  119,    2, 0x0a /* Public */,
       8,    0,  120,    2, 0x0a /* Public */,
       9,    0,  121,    2, 0x0a /* Public */,
      10,    0,  122,    2, 0x0a /* Public */,
      11,    0,  123,    2, 0x0a /* Public */,
      12,    0,  124,    2, 0x0a /* Public */,
      13,    0,  125,    2, 0x0a /* Public */,
      14,    0,  126,    2, 0x0a /* Public */,
      15,    0,  127,    2, 0x0a /* Public */,
      16,    0,  128,    2, 0x0a /* Public */,
      17,    0,  129,    2, 0x0a /* Public */,
      18,    0,  130,    2, 0x0a /* Public */,
      19,    0,  131,    2, 0x0a /* Public */,
      20,    0,  132,    2, 0x0a /* Public */,
      21,    0,  133,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void view::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        view *_t = static_cast<view *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->selectionChanged(); break;
        case 1: _t->fitAll(); break;
        case 2: _t->fitArea(); break;
        case 3: _t->zoom(); break;
        case 4: _t->pan(); break;
        case 5: _t->globalPan(); break;
        case 6: _t->front(); break;
        case 7: _t->back(); break;
        case 8: _t->top(); break;
        case 9: _t->bottom(); break;
        case 10: _t->left(); break;
        case 11: _t->right(); break;
        case 12: _t->axo(); break;
        case 13: _t->rotation(); break;
        case 14: _t->reset(); break;
        case 15: _t->hlrOn(); break;
        case 16: _t->hlrOff(); break;
        case 17: _t->onBackground(); break;
        case 18: _t->onEnvironmentMap(); break;
        case 19: _t->onRaytraceAction(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (view::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&view::selectionChanged)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject view::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_view.data,
      qt_meta_data_view,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *view::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *view::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_view.stringdata0))
        return static_cast<void*>(const_cast< view*>(this));
    return QWidget::qt_metacast(_clname);
}

int view::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void view::selectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE

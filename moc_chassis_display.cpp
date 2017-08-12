/****************************************************************************
** Meta object code from reading C++ file 'chassis_display.h'
**
** Created: Tue Apr 4 11:57:44 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "chassis_display.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chassis_display.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_chassis_display[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,
      41,   16,   16,   16, 0x08,
      55,   16,   16,   16, 0x08,
      83,   16,   16,   16, 0x08,
     108,   16,   16,   16, 0x08,
     133,   16,   16,   16, 0x08,
     157,   16,   16,   16, 0x08,
     182,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_chassis_display[] = {
    "chassis_display\0\0on_OPENButton_clicked()\0"
    "timerupdate()\0on_AIMNUM_editingFinished()\0"
    "on_STARTButton_clicked()\0"
    "on_CLOSEButton_clicked()\0"
    "on_PLANButton_clicked()\0"
    "on_TRACKButton_clicked()\0"
    "on_STOPButton_clicked()\0"
};

void chassis_display::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        chassis_display *_t = static_cast<chassis_display *>(_o);
        switch (_id) {
        case 0: _t->on_OPENButton_clicked(); break;
        case 1: _t->timerupdate(); break;
        case 2: _t->on_AIMNUM_editingFinished(); break;
        case 3: _t->on_STARTButton_clicked(); break;
        case 4: _t->on_CLOSEButton_clicked(); break;
        case 5: _t->on_PLANButton_clicked(); break;
        case 6: _t->on_TRACKButton_clicked(); break;
        case 7: _t->on_STOPButton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData chassis_display::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject chassis_display::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_chassis_display,
      qt_meta_data_chassis_display, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &chassis_display::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *chassis_display::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *chassis_display::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_chassis_display))
        return static_cast<void*>(const_cast< chassis_display*>(this));
    return QDialog::qt_metacast(_clname);
}

int chassis_display::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

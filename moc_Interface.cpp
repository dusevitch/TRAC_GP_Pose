/****************************************************************************
** Meta object code from reading C++ file 'Interface.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Interface.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Interface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Interface[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      29,   10,   10,   10, 0x08,
      46,   10,   10,   10, 0x08,
      68,   65,   10,   10, 0x08,
      88,   10,   10,   10, 0x08,
     110,  105,   10,   10, 0x08,
     129,   10,   10,   10, 0x08,
     144,   10,   10,   10, 0x08,
     169,   10,   10,   10, 0x08,
     210,  202,   10,   10, 0x08,
     242,   10,   10,   10, 0x08,
     264,   10,   10,   10, 0x08,
     285,   10,   10,   10, 0x08,
     309,   10,   10,   10, 0x08,
     338,  202,   10,   10, 0x08,
     368,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Interface[] = {
    "Interface\0\0EnterFullScreen()\0"
    "ExitFullScreen()\0ToggleFullScreen()\0"
    "fs\0SetFullScreen(bool)\0ToggleSettings()\0"
    "show\0ShowSettings(bool)\0UpdateStatus()\0"
    "on_alignCamera_clicked()\0"
    "on_updateStaticMarkers_clicked()\0"
    "checked\0on_hide_show_base_toggled(bool)\0"
    "on_zoom_out_clicked()\0on_zoom_in_clicked()\0"
    "on_pushButton_clicked()\0"
    "on_load_gp_phantom_clicked()\0"
    "on_scale_button_toggled(bool)\0"
    "on_export_path_file_clicked()\0"
};

void Interface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Interface *_t = static_cast<Interface *>(_o);
        switch (_id) {
        case 0: _t->EnterFullScreen(); break;
        case 1: _t->ExitFullScreen(); break;
        case 2: _t->ToggleFullScreen(); break;
        case 3: _t->SetFullScreen((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->ToggleSettings(); break;
        case 5: _t->ShowSettings((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->UpdateStatus(); break;
        case 7: _t->on_alignCamera_clicked(); break;
        case 8: _t->on_updateStaticMarkers_clicked(); break;
        case 9: _t->on_hide_show_base_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_zoom_out_clicked(); break;
        case 11: _t->on_zoom_in_clicked(); break;
        case 12: _t->on_pushButton_clicked(); break;
        case 13: _t->on_load_gp_phantom_clicked(); break;
        case 14: _t->on_scale_button_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->on_export_path_file_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Interface::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Interface::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Interface,
      qt_meta_data_Interface, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Interface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Interface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Interface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Interface))
        return static_cast<void*>(const_cast< Interface*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Interface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'controller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SeriesScraperApp/src/controller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Controller_t {
    QByteArrayData data[19];
    char stringdata0[205];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Controller_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Controller_t qt_meta_stringdata_Controller = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Controller"
QT_MOC_LITERAL(1, 11, 11), // "sendMessage"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 8), // "Message&"
QT_MOC_LITERAL(4, 33, 3), // "msg"
QT_MOC_LITERAL(5, 37, 19), // "initializeDirectory"
QT_MOC_LITERAL(6, 57, 6), // "rename"
QT_MOC_LITERAL(7, 64, 10), // "undoRename"
QT_MOC_LITERAL(8, 75, 6), // "notify"
QT_MOC_LITERAL(9, 82, 12), // "directorySet"
QT_MOC_LITERAL(10, 95, 11), // "initialized"
QT_MOC_LITERAL(11, 107, 10), // "renameDone"
QT_MOC_LITERAL(12, 118, 7), // "success"
QT_MOC_LITERAL(13, 126, 14), // "undoRenameDone"
QT_MOC_LITERAL(14, 141, 20), // "renameProgressUpdate"
QT_MOC_LITERAL(15, 162, 12), // "totalObjects"
QT_MOC_LITERAL(16, 175, 13), // "currentObject"
QT_MOC_LITERAL(17, 189, 7), // "oldName"
QT_MOC_LITERAL(18, 197, 7) // "newName"

    },
    "Controller\0sendMessage\0\0Message&\0msg\0"
    "initializeDirectory\0rename\0undoRename\0"
    "notify\0directorySet\0initialized\0"
    "renameDone\0success\0undoRenameDone\0"
    "renameProgressUpdate\0totalObjects\0"
    "currentObject\0oldName\0newName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Controller[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       5,    1,   62,    2, 0x06 /* Public */,
       6,    0,   65,    2, 0x06 /* Public */,
       7,    0,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   67,    2, 0x0a /* Public */,
       9,    1,   70,    2, 0x0a /* Public */,
      11,    1,   73,    2, 0x0a /* Public */,
      13,    1,   76,    2, 0x0a /* Public */,
      14,    4,   79,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::QString,   15,   16,   17,   18,

       0        // eod
};

void Controller::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Controller *_t = static_cast<Controller *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendMessage((*reinterpret_cast< Message(*)>(_a[1]))); break;
        case 1: _t->initializeDirectory((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->rename(); break;
        case 3: _t->undoRename(); break;
        case 4: _t->notify((*reinterpret_cast< Message(*)>(_a[1]))); break;
        case 5: _t->directorySet((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 6: _t->renameDone((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 7: _t->undoRenameDone((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 8: _t->renameProgressUpdate((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Controller::*_t)(Message & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Controller::sendMessage)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Controller::*_t)(const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Controller::initializeDirectory)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Controller::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Controller::rename)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Controller::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Controller::undoRename)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject Controller::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Controller.data,
      qt_meta_data_Controller,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Controller::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Controller::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Controller.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Controller::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Controller::sendMessage(Message & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Controller::initializeDirectory(const QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Controller::rename()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Controller::undoRename()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

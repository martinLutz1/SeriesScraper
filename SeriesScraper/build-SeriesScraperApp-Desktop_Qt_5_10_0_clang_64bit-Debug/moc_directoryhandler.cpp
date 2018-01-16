/****************************************************************************
** Meta object code from reading C++ file 'directoryhandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SeriesScraperApp/src/directoryhandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'directoryhandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DirectoryHandler_t {
    QByteArrayData data[10];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DirectoryHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DirectoryHandler_t qt_meta_stringdata_DirectoryHandler = {
    {
QT_MOC_LITERAL(0, 0, 16), // "DirectoryHandler"
QT_MOC_LITERAL(1, 17, 20), // "directoryInitialized"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 10), // "renameDone"
QT_MOC_LITERAL(4, 50, 14), // "undoRenameDone"
QT_MOC_LITERAL(5, 65, 20), // "updateRenameProgress"
QT_MOC_LITERAL(6, 86, 19), // "initializeDirectory"
QT_MOC_LITERAL(7, 106, 4), // "path"
QT_MOC_LITERAL(8, 111, 6), // "rename"
QT_MOC_LITERAL(9, 118, 10) // "undoRename"

    },
    "DirectoryHandler\0directoryInitialized\0"
    "\0renameDone\0undoRenameDone\0"
    "updateRenameProgress\0initializeDirectory\0"
    "path\0rename\0undoRename"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DirectoryHandler[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       3,    1,   52,    2, 0x06 /* Public */,
       4,    1,   55,    2, 0x06 /* Public */,
       5,    4,   58,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   67,    2, 0x0a /* Public */,
       8,    0,   70,    2, 0x0a /* Public */,
       9,    0,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::QString,    2,    2,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DirectoryHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DirectoryHandler *_t = static_cast<DirectoryHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->directoryInitialized((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 1: _t->renameDone((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 2: _t->undoRenameDone((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 3: _t->updateRenameProgress((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 4: _t->initializeDirectory((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->rename(); break;
        case 6: _t->undoRename(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (DirectoryHandler::*_t)(const bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DirectoryHandler::directoryInitialized)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DirectoryHandler::*_t)(const bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DirectoryHandler::renameDone)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (DirectoryHandler::*_t)(const bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DirectoryHandler::undoRenameDone)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (DirectoryHandler::*_t)(const int , const int , const QString , const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DirectoryHandler::updateRenameProgress)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject DirectoryHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DirectoryHandler.data,
      qt_meta_data_DirectoryHandler,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DirectoryHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DirectoryHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DirectoryHandler.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DirectoryHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void DirectoryHandler::directoryInitialized(const bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DirectoryHandler::renameDone(const bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DirectoryHandler::undoRenameDone(const bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DirectoryHandler::updateRenameProgress(const int _t1, const int _t2, const QString _t3, const QString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SeriesScraperApp/src/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[45];
    char stringdata0[768];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 11), // "sendMessage"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 8), // "Message&"
QT_MOC_LITERAL(4, 33, 3), // "msg"
QT_MOC_LITERAL(5, 37, 9), // "updateRow"
QT_MOC_LITERAL(6, 47, 3), // "row"
QT_MOC_LITERAL(7, 51, 12), // "EpisodeName&"
QT_MOC_LITERAL(8, 64, 11), // "episodeName"
QT_MOC_LITERAL(9, 76, 14), // "noColorization"
QT_MOC_LITERAL(10, 91, 10), // "clearTable"
QT_MOC_LITERAL(11, 102, 13), // "openDirectory"
QT_MOC_LITERAL(12, 116, 17), // "onUpdateDirectory"
QT_MOC_LITERAL(13, 134, 26), // "startSeriesTextChangeTimer"
QT_MOC_LITERAL(14, 161, 19), // "onSeriesTextChanged"
QT_MOC_LITERAL(15, 181, 15), // "onSeasonChanged"
QT_MOC_LITERAL(16, 197, 5), // "index"
QT_MOC_LITERAL(17, 203, 23), // "onSeriesLanguageChanged"
QT_MOC_LITERAL(18, 227, 21), // "onRenameButtonPressed"
QT_MOC_LITERAL(19, 249, 19), // "onNameSchemeChanged"
QT_MOC_LITERAL(20, 269, 19), // "onTableEntryChanged"
QT_MOC_LITERAL(21, 289, 7), // "coloumn"
QT_MOC_LITERAL(22, 297, 25), // "onPathLineEditTextChanged"
QT_MOC_LITERAL(23, 323, 4), // "path"
QT_MOC_LITERAL(24, 328, 23), // "onDirectoryEntryClicked"
QT_MOC_LITERAL(25, 352, 8), // "QAction*"
QT_MOC_LITERAL(26, 361, 13), // "clickedAction"
QT_MOC_LITERAL(27, 375, 32), // "onDirectoryComboBox1EntryClicked"
QT_MOC_LITERAL(28, 408, 9), // "selection"
QT_MOC_LITERAL(29, 418, 32), // "onDirectoryComboBox2EntryClicked"
QT_MOC_LITERAL(30, 451, 32), // "onDirectoryComboBox3EntryClicked"
QT_MOC_LITERAL(31, 484, 32), // "onDirectoryComboBox4EntryClicked"
QT_MOC_LITERAL(32, 517, 31), // "onDirectoryComboBoxEntryClicked"
QT_MOC_LITERAL(33, 549, 5), // "level"
QT_MOC_LITERAL(34, 555, 23), // "toggleDirectorySelector"
QT_MOC_LITERAL(35, 579, 15), // "clearStatusText"
QT_MOC_LITERAL(36, 595, 10), // "savePoster"
QT_MOC_LITERAL(37, 606, 12), // "undoRenaming"
QT_MOC_LITERAL(38, 619, 15), // "showAboutDialog"
QT_MOC_LITERAL(39, 635, 18), // "showSettingsWindow"
QT_MOC_LITERAL(40, 654, 16), // "toggleFullScreen"
QT_MOC_LITERAL(41, 671, 35), // "onPathStructureContentButtonC..."
QT_MOC_LITERAL(42, 707, 28), // "slideOutRenameProgressWidget"
QT_MOC_LITERAL(43, 736, 24), // "hideRenameProgressWidget"
QT_MOC_LITERAL(44, 761, 6) // "notify"

    },
    "MainWindow\0sendMessage\0\0Message&\0msg\0"
    "updateRow\0row\0EpisodeName&\0episodeName\0"
    "noColorization\0clearTable\0openDirectory\0"
    "onUpdateDirectory\0startSeriesTextChangeTimer\0"
    "onSeriesTextChanged\0onSeasonChanged\0"
    "index\0onSeriesLanguageChanged\0"
    "onRenameButtonPressed\0onNameSchemeChanged\0"
    "onTableEntryChanged\0coloumn\0"
    "onPathLineEditTextChanged\0path\0"
    "onDirectoryEntryClicked\0QAction*\0"
    "clickedAction\0onDirectoryComboBox1EntryClicked\0"
    "selection\0onDirectoryComboBox2EntryClicked\0"
    "onDirectoryComboBox3EntryClicked\0"
    "onDirectoryComboBox4EntryClicked\0"
    "onDirectoryComboBoxEntryClicked\0level\0"
    "toggleDirectorySelector\0clearStatusText\0"
    "savePoster\0undoRenaming\0showAboutDialog\0"
    "showSettingsWindow\0toggleFullScreen\0"
    "onPathStructureContentButtonClicked\0"
    "slideOutRenameProgressWidget\0"
    "hideRenameProgressWidget\0notify"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  164,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    3,  167,    2, 0x08 /* Private */,
      10,    0,  174,    2, 0x08 /* Private */,
      11,    0,  175,    2, 0x08 /* Private */,
      12,    0,  176,    2, 0x08 /* Private */,
      13,    0,  177,    2, 0x08 /* Private */,
      14,    0,  178,    2, 0x08 /* Private */,
      15,    1,  179,    2, 0x08 /* Private */,
      17,    1,  182,    2, 0x08 /* Private */,
      18,    0,  185,    2, 0x08 /* Private */,
      19,    1,  186,    2, 0x08 /* Private */,
      20,    2,  189,    2, 0x08 /* Private */,
      22,    1,  194,    2, 0x08 /* Private */,
      24,    1,  197,    2, 0x08 /* Private */,
      27,    1,  200,    2, 0x08 /* Private */,
      29,    1,  203,    2, 0x08 /* Private */,
      30,    1,  206,    2, 0x08 /* Private */,
      31,    1,  209,    2, 0x08 /* Private */,
      32,    2,  212,    2, 0x08 /* Private */,
      34,    0,  217,    2, 0x08 /* Private */,
      35,    0,  218,    2, 0x08 /* Private */,
      36,    0,  219,    2, 0x08 /* Private */,
      37,    0,  220,    2, 0x08 /* Private */,
      38,    0,  221,    2, 0x08 /* Private */,
      39,    0,  222,    2, 0x08 /* Private */,
      40,    0,  223,    2, 0x08 /* Private */,
      41,    0,  224,    2, 0x08 /* Private */,
      42,    0,  225,    2, 0x08 /* Private */,
      43,    0,  226,    2, 0x08 /* Private */,
      44,    1,  227,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7, QMetaType::Bool,    6,    8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,   21,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Void, 0x80000000 | 25,   26,
    QMetaType::Void, QMetaType::Int,   28,
    QMetaType::Void, QMetaType::Int,   28,
    QMetaType::Void, QMetaType::Int,   28,
    QMetaType::Void, QMetaType::Int,   28,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   33,   28,
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
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendMessage((*reinterpret_cast< Message(*)>(_a[1]))); break;
        case 1: _t->updateRow((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< EpisodeName(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 2: _t->clearTable(); break;
        case 3: _t->openDirectory(); break;
        case 4: _t->onUpdateDirectory(); break;
        case 5: _t->startSeriesTextChangeTimer(); break;
        case 6: _t->onSeriesTextChanged(); break;
        case 7: _t->onSeasonChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->onSeriesLanguageChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->onRenameButtonPressed(); break;
        case 10: _t->onNameSchemeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->onTableEntryChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->onPathLineEditTextChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->onDirectoryEntryClicked((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 14: _t->onDirectoryComboBox1EntryClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->onDirectoryComboBox2EntryClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->onDirectoryComboBox3EntryClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->onDirectoryComboBox4EntryClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->onDirectoryComboBoxEntryClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 19: _t->toggleDirectorySelector(); break;
        case 20: _t->clearStatusText(); break;
        case 21: _t->savePoster(); break;
        case 22: _t->undoRenaming(); break;
        case 23: _t->showAboutDialog(); break;
        case 24: _t->showSettingsWindow(); break;
        case 25: _t->toggleFullScreen(); break;
        case 26: _t->onPathStructureContentButtonClicked(); break;
        case 27: _t->slideOutRenameProgressWidget(); break;
        case 28: _t->hideRenameProgressWidget(); break;
        case 29: _t->notify((*reinterpret_cast< Message(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MainWindow::*_t)(Message & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sendMessage)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 30)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 30;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::sendMessage(Message & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

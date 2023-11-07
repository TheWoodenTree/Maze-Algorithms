/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../mainwindow.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_MainWindow_t {
    uint offsetsAndSizes[28];
    char stringdata0[11];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[5];
    char stringdata5[12];
    char stringdata6[22];
    char stringdata7[5];
    char stringdata8[17];
    char stringdata9[17];
    char stringdata10[11];
    char stringdata11[19];
    char stringdata12[21];
    char stringdata13[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MainWindow_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 14),  // "boardGenerated"
        QT_MOC_LITERAL(26, 0),  // ""
        QT_MOC_LITERAL(27, 4),  // "quit"
        QT_MOC_LITERAL(32, 4),  // "sync"
        QT_MOC_LITERAL(37, 11),  // "tileClicked"
        QT_MOC_LITERAL(49, 21),  // "std::shared_ptr<Tile>"
        QT_MOC_LITERAL(71, 4),  // "tile"
        QT_MOC_LITERAL(76, 16),  // "tileRightClicked"
        QT_MOC_LITERAL(93, 16),  // "setAdjacentTiles"
        QT_MOC_LITERAL(110, 10),  // "clearWalls"
        QT_MOC_LITERAL(121, 18),  // "breadthFirstSearch"
        QT_MOC_LITERAL(140, 20),  // "revealConnectedTiles"
        QT_MOC_LITERAL(161, 7)   // "message"
    },
    "MainWindow",
    "boardGenerated",
    "",
    "quit",
    "sync",
    "tileClicked",
    "std::shared_ptr<Tile>",
    "tile",
    "tileRightClicked",
    "setAdjacentTiles",
    "clearWalls",
    "breadthFirstSearch",
    "revealConnectedTiles",
    "message"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   75,    2, 0x08,    2 /* Private */,
       4,    0,   76,    2, 0x08,    3 /* Private */,
       5,    1,   77,    2, 0x08,    4 /* Private */,
       8,    1,   80,    2, 0x08,    6 /* Private */,
       9,    0,   83,    2, 0x08,    8 /* Private */,
      10,    0,   84,    2, 0x08,    9 /* Private */,
      11,    0,   85,    2, 0x08,   10 /* Private */,
      12,    1,   86,    2, 0x08,   11 /* Private */,
      13,    1,   89,    2, 0x108,   13 /* Private | MethodIsConst  */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QString,   13,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSizes,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'boardGenerated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'quit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sync'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'tileClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::shared_ptr<Tile> &, std::false_type>,
        // method 'tileRightClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::shared_ptr<Tile> &, std::false_type>,
        // method 'setAdjacentTiles'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearWalls'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'breadthFirstSearch'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'revealConnectedTiles'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::shared_ptr<Tile> &, std::false_type>,
        // method 'message'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->boardGenerated(); break;
        case 1: _t->quit(); break;
        case 2: _t->sync(); break;
        case 3: _t->tileClicked((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Tile>>>(_a[1]))); break;
        case 4: _t->tileRightClicked((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Tile>>>(_a[1]))); break;
        case 5: _t->setAdjacentTiles(); break;
        case 6: _t->clearWalls(); break;
        case 7: _t->breadthFirstSearch(); break;
        case 8: _t->revealConnectedTiles((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Tile>>>(_a[1]))); break;
        case 9: _t->message((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)();
            if (_t _q_method = &MainWindow::boardGenerated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::boardGenerated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

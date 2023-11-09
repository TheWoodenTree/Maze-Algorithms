/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainwindow.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
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
    "callDepthFirstSearch",
    "depthFirstSearch",
    "revealConnectedTiles",
    "message",
    "setupTiles",
    "QWidget*",
    "parent"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[38];
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
    char stringdata13[17];
    char stringdata14[21];
    char stringdata15[8];
    char stringdata16[11];
    char stringdata17[9];
    char stringdata18[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
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
        QT_MOC_LITERAL(140, 20),  // "callDepthFirstSearch"
        QT_MOC_LITERAL(161, 16),  // "depthFirstSearch"
        QT_MOC_LITERAL(178, 20),  // "revealConnectedTiles"
        QT_MOC_LITERAL(199, 7),  // "message"
        QT_MOC_LITERAL(207, 10),  // "setupTiles"
        QT_MOC_LITERAL(218, 8),  // "QWidget*"
        QT_MOC_LITERAL(227, 6)   // "parent"
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
    "callDepthFirstSearch",
    "depthFirstSearch",
    "revealConnectedTiles",
    "message",
    "setupTiles",
    "QWidget*",
    "parent"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   92,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   93,    2, 0x08,    2 /* Private */,
       4,    0,   94,    2, 0x08,    3 /* Private */,
       5,    1,   95,    2, 0x08,    4 /* Private */,
       8,    1,   98,    2, 0x08,    6 /* Private */,
       9,    0,  101,    2, 0x08,    8 /* Private */,
      10,    0,  102,    2, 0x08,    9 /* Private */,
      11,    0,  103,    2, 0x08,   10 /* Private */,
      12,    0,  104,    2, 0x08,   11 /* Private */,
      13,    1,  105,    2, 0x08,   12 /* Private */,
      14,    1,  108,    2, 0x08,   14 /* Private */,
      15,    1,  111,    2, 0x108,   16 /* Private | MethodIsConst  */,
      16,    1,  114,    2, 0x08,   18 /* Private */,

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
    QMetaType::Void,
    QMetaType::Bool, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, 0x80000000 | 17,   18,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
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
        // method 'callDepthFirstSearch'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'depthFirstSearch'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::shared_ptr<Tile> &, std::false_type>,
        // method 'revealConnectedTiles'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::shared_ptr<Tile> &, std::false_type>,
        // method 'message'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'setupTiles'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QWidget *, std::false_type>
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
        case 8: _t->callDepthFirstSearch(); break;
        case 9: { bool _r = _t->depthFirstSearch((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Tile>>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->revealConnectedTiles((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Tile>>>(_a[1]))); break;
        case 11: _t->message((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->setupTiles((*reinterpret_cast< std::add_pointer_t<QWidget*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QWidget* >(); break;
            }
            break;
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
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::boardGenerated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP

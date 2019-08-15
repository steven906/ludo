/****************************************************************************
** Meta object code from reading C++ file 'ludo_player_gen_alg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ludo_player_gen_alg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ludo_player_gen_alg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ludo_player_gen_alg_t {
    QByteArrayData data[10];
    char stringdata0[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ludo_player_gen_alg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ludo_player_gen_alg_t qt_meta_stringdata_ludo_player_gen_alg = {
    {
QT_MOC_LITERAL(0, 0, 19), // "ludo_player_gen_alg"
QT_MOC_LITERAL(1, 20, 12), // "select_piece"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 13), // "turn_complete"
QT_MOC_LITERAL(4, 48, 10), // "start_turn"
QT_MOC_LITERAL(5, 59, 18), // "positions_and_dice"
QT_MOC_LITERAL(6, 78, 8), // "relative"
QT_MOC_LITERAL(7, 87, 18), // "post_game_analysis"
QT_MOC_LITERAL(8, 106, 16), // "std::vector<int>"
QT_MOC_LITERAL(9, 123, 12) // "relative_pos"

    },
    "ludo_player_gen_alg\0select_piece\0\0"
    "turn_complete\0start_turn\0positions_and_dice\0"
    "relative\0post_game_analysis\0"
    "std::vector<int>\0relative_pos"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ludo_player_gen_alg[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       3,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   40,    2, 0x0a /* Public */,
       7,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void ludo_player_gen_alg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ludo_player_gen_alg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->select_piece((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->turn_complete((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->start_turn((*reinterpret_cast< positions_and_dice(*)>(_a[1]))); break;
        case 3: _t->post_game_analysis((*reinterpret_cast< std::vector<int>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ludo_player_gen_alg::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ludo_player_gen_alg::select_piece)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ludo_player_gen_alg::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ludo_player_gen_alg::turn_complete)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ludo_player_gen_alg::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ludo_player_gen_alg.data,
    qt_meta_data_ludo_player_gen_alg,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ludo_player_gen_alg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ludo_player_gen_alg::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ludo_player_gen_alg.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ludo_player_gen_alg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void ludo_player_gen_alg::select_piece(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ludo_player_gen_alg::turn_complete(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

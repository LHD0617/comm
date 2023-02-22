/****************************************************************************
** Meta object code from reading C++ file 'serialtool.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../comm_test/serialtool.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialtool.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SerialTool_t {
    QByteArrayData data[11];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SerialTool_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SerialTool_t qt_meta_stringdata_SerialTool = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SerialTool"
QT_MOC_LITERAL(1, 11, 9), // "LogSignal"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 7), // "Message"
QT_MOC_LITERAL(4, 30, 16), // "CleanStatsSignal"
QT_MOC_LITERAL(5, 47, 11), // "RefreshPort"
QT_MOC_LITERAL(6, 59, 10), // "SwitchPort"
QT_MOC_LITERAL(7, 70, 20), // "SendCleanStatsSignal"
QT_MOC_LITERAL(8, 91, 11), // "WriteConfig"
QT_MOC_LITERAL(9, 103, 5), // "index"
QT_MOC_LITERAL(10, 109, 10) // "ReadConfig"

    },
    "SerialTool\0LogSignal\0\0Message\0"
    "CleanStatsSignal\0RefreshPort\0SwitchPort\0"
    "SendCleanStatsSignal\0WriteConfig\0index\0"
    "ReadConfig"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SerialTool[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    0,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   53,    2, 0x08 /* Private */,
       6,    0,   54,    2, 0x08 /* Private */,
       7,    0,   55,    2, 0x08 /* Private */,
       8,    1,   56,    2, 0x08 /* Private */,
      10,    0,   59,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,

       0        // eod
};

void SerialTool::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SerialTool *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->LogSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->CleanStatsSignal(); break;
        case 2: _t->RefreshPort(); break;
        case 3: _t->SwitchPort(); break;
        case 4: _t->SendCleanStatsSignal(); break;
        case 5: _t->WriteConfig((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->ReadConfig(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SerialTool::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SerialTool::LogSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SerialTool::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SerialTool::CleanStatsSignal)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SerialTool::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_SerialTool.data,
    qt_meta_data_SerialTool,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SerialTool::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SerialTool::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SerialTool.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SerialTool::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void SerialTool::LogSignal(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SerialTool::CleanStatsSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

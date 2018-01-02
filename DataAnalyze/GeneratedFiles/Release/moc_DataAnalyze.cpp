/****************************************************************************
** Meta object code from reading C++ file 'DataAnalyze.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DataAnalyze.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DataAnalyze.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WorkerRead_t {
    QByteArrayData data[6];
    char stringdata0[46];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WorkerRead_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WorkerRead_t qt_meta_stringdata_WorkerRead = {
    {
QT_MOC_LITERAL(0, 0, 10), // "WorkerRead"
QT_MOC_LITERAL(1, 11, 8), // "showData"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 11), // "WorkerRead*"
QT_MOC_LITERAL(4, 33, 6), // "worker"
QT_MOC_LITERAL(5, 40, 5) // "index"

    },
    "WorkerRead\0showData\0\0WorkerRead*\0"
    "worker\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WorkerRead[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,

       0        // eod
};

void WorkerRead::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WorkerRead *_t = static_cast<WorkerRead *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showData((*reinterpret_cast< WorkerRead*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< WorkerRead* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WorkerRead::*_t)(WorkerRead * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WorkerRead::showData)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject WorkerRead::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_WorkerRead.data,
      qt_meta_data_WorkerRead,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WorkerRead::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WorkerRead::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WorkerRead.stringdata0))
        return static_cast<void*>(const_cast< WorkerRead*>(this));
    return QThread::qt_metacast(_clname);
}

int WorkerRead::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void WorkerRead::showData(WorkerRead * _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_WorkerWrite_t {
    QByteArrayData data[3];
    char stringdata0[25];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WorkerWrite_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WorkerWrite_t qt_meta_stringdata_WorkerWrite = {
    {
QT_MOC_LITERAL(0, 0, 11), // "WorkerWrite"
QT_MOC_LITERAL(1, 12, 11), // "showMessage"
QT_MOC_LITERAL(2, 24, 0) // ""

    },
    "WorkerWrite\0showMessage\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WorkerWrite[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void WorkerWrite::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WorkerWrite *_t = static_cast<WorkerWrite *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showMessage(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WorkerWrite::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WorkerWrite::showMessage)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject WorkerWrite::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_WorkerWrite.data,
      qt_meta_data_WorkerWrite,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WorkerWrite::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WorkerWrite::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WorkerWrite.stringdata0))
        return static_cast<void*>(const_cast< WorkerWrite*>(this));
    return QThread::qt_metacast(_clname);
}

int WorkerWrite::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void WorkerWrite::showMessage()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
struct qt_meta_stringdata_DataAnalyze_t {
    QByteArrayData data[23];
    char stringdata0[308];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataAnalyze_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataAnalyze_t qt_meta_stringdata_DataAnalyze = {
    {
QT_MOC_LITERAL(0, 0, 11), // "DataAnalyze"
QT_MOC_LITERAL(1, 12, 13), // "on_export_one"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 7), // "checked"
QT_MOC_LITERAL(4, 35, 13), // "on_export_two"
QT_MOC_LITERAL(5, 49, 15), // "on_export_three"
QT_MOC_LITERAL(6, 65, 10), // "on_run_old"
QT_MOC_LITERAL(7, 76, 13), // "on_open_click"
QT_MOC_LITERAL(8, 90, 14), // "on_ui_showData"
QT_MOC_LITERAL(9, 105, 11), // "WorkerRead*"
QT_MOC_LITERAL(10, 117, 6), // "worker"
QT_MOC_LITERAL(11, 124, 5), // "index"
QT_MOC_LITERAL(12, 130, 14), // "on_start_click"
QT_MOC_LITERAL(13, 145, 15), // "on_start2_click"
QT_MOC_LITERAL(14, 161, 15), // "on_js_click_one"
QT_MOC_LITERAL(15, 177, 15), // "on_js_click_two"
QT_MOC_LITERAL(16, 193, 15), // "on_dr_click_one"
QT_MOC_LITERAL(17, 209, 15), // "on_dr_click_two"
QT_MOC_LITERAL(18, 225, 15), // "on_dc_click_two"
QT_MOC_LITERAL(19, 241, 15), // "show_ui_Message"
QT_MOC_LITERAL(20, 257, 16), // "table_delete_one"
QT_MOC_LITERAL(21, 274, 16), // "table_delete_two"
QT_MOC_LITERAL(22, 291, 16) // "table_delete_avg"

    },
    "DataAnalyze\0on_export_one\0\0checked\0"
    "on_export_two\0on_export_three\0on_run_old\0"
    "on_open_click\0on_ui_showData\0WorkerRead*\0"
    "worker\0index\0on_start_click\0on_start2_click\0"
    "on_js_click_one\0on_js_click_two\0"
    "on_dr_click_one\0on_dr_click_two\0"
    "on_dc_click_two\0show_ui_Message\0"
    "table_delete_one\0table_delete_two\0"
    "table_delete_avg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataAnalyze[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  159,    2, 0x0a /* Public */,
       1,    0,  162,    2, 0x2a /* Public | MethodCloned */,
       4,    1,  163,    2, 0x0a /* Public */,
       4,    0,  166,    2, 0x2a /* Public | MethodCloned */,
       5,    1,  167,    2, 0x0a /* Public */,
       5,    0,  170,    2, 0x2a /* Public | MethodCloned */,
       6,    1,  171,    2, 0x0a /* Public */,
       6,    0,  174,    2, 0x2a /* Public | MethodCloned */,
       7,    1,  175,    2, 0x0a /* Public */,
       7,    0,  178,    2, 0x2a /* Public | MethodCloned */,
       8,    2,  179,    2, 0x0a /* Public */,
      12,    1,  184,    2, 0x0a /* Public */,
      12,    0,  187,    2, 0x2a /* Public | MethodCloned */,
      13,    1,  188,    2, 0x0a /* Public */,
      13,    0,  191,    2, 0x2a /* Public | MethodCloned */,
      14,    1,  192,    2, 0x0a /* Public */,
      14,    0,  195,    2, 0x2a /* Public | MethodCloned */,
      15,    1,  196,    2, 0x0a /* Public */,
      15,    0,  199,    2, 0x2a /* Public | MethodCloned */,
      16,    1,  200,    2, 0x0a /* Public */,
      16,    0,  203,    2, 0x2a /* Public | MethodCloned */,
      17,    1,  204,    2, 0x0a /* Public */,
      17,    0,  207,    2, 0x2a /* Public | MethodCloned */,
      18,    1,  208,    2, 0x0a /* Public */,
      18,    0,  211,    2, 0x2a /* Public | MethodCloned */,
      19,    0,  212,    2, 0x0a /* Public */,
      20,    1,  213,    2, 0x0a /* Public */,
      21,    1,  216,    2, 0x0a /* Public */,
      22,    1,  219,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Int,   10,   11,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void, QMetaType::QModelIndex,   11,

       0        // eod
};

void DataAnalyze::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DataAnalyze *_t = static_cast<DataAnalyze *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_export_one((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_export_one(); break;
        case 2: _t->on_export_two((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_export_two(); break;
        case 4: _t->on_export_three((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_export_three(); break;
        case 6: _t->on_run_old((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_run_old(); break;
        case 8: _t->on_open_click((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_open_click(); break;
        case 10: _t->on_ui_showData((*reinterpret_cast< WorkerRead*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->on_start_click((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->on_start_click(); break;
        case 13: _t->on_start2_click((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->on_start2_click(); break;
        case 15: _t->on_js_click_one((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->on_js_click_one(); break;
        case 17: _t->on_js_click_two((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->on_js_click_two(); break;
        case 19: _t->on_dr_click_one((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: _t->on_dr_click_one(); break;
        case 21: _t->on_dr_click_two((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->on_dr_click_two(); break;
        case 23: _t->on_dc_click_two((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->on_dc_click_two(); break;
        case 25: _t->show_ui_Message(); break;
        case 26: _t->table_delete_one((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 27: _t->table_delete_two((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 28: _t->table_delete_avg((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< WorkerRead* >(); break;
            }
            break;
        }
    }
}

const QMetaObject DataAnalyze::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_DataAnalyze.data,
      qt_meta_data_DataAnalyze,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DataAnalyze::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataAnalyze::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DataAnalyze.stringdata0))
        return static_cast<void*>(const_cast< DataAnalyze*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int DataAnalyze::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

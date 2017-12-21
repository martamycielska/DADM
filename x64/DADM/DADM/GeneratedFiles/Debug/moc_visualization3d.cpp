/****************************************************************************
** Meta object code from reading C++ file 'visualization3d.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../visualization3d.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'visualization3d.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VisualizationWorker_t {
    QByteArrayData data[4];
    char stringdata0[56];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VisualizationWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VisualizationWorker_t qt_meta_stringdata_VisualizationWorker = {
    {
QT_MOC_LITERAL(0, 0, 19), // "VisualizationWorker"
QT_MOC_LITERAL(1, 20, 17), // "ModelCreationDone"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 16) // "CuttingPlaneDone"

    },
    "VisualizationWorker\0ModelCreationDone\0"
    "\0CuttingPlaneDone"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VisualizationWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VisualizationWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VisualizationWorker *_t = static_cast<VisualizationWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ModelCreationDone(); break;
        case 1: _t->CuttingPlaneDone(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VisualizationWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisualizationWorker::ModelCreationDone)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (VisualizationWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisualizationWorker::CuttingPlaneDone)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject VisualizationWorker::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_VisualizationWorker.data,
      qt_meta_data_VisualizationWorker,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *VisualizationWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VisualizationWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VisualizationWorker.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int VisualizationWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void VisualizationWorker::ModelCreationDone()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void VisualizationWorker::CuttingPlaneDone()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_Visualization3D_t {
    QByteArrayData data[8];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Visualization3D_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Visualization3D_t qt_meta_stringdata_Visualization3D = {
    {
QT_MOC_LITERAL(0, 0, 15), // "Visualization3D"
QT_MOC_LITERAL(1, 16, 7), // "Brain3D"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 15), // "AcceptThreshold"
QT_MOC_LITERAL(4, 41, 18), // "SliderValueChanged"
QT_MOC_LITERAL(5, 60, 24), // "ShrinkSliderValueChanged"
QT_MOC_LITERAL(6, 85, 16), // "CutEnableChanged"
QT_MOC_LITERAL(7, 102, 25) // "AddRendererAndPlaneWidget"

    },
    "Visualization3D\0Brain3D\0\0AcceptThreshold\0"
    "SliderValueChanged\0ShrinkSliderValueChanged\0"
    "CutEnableChanged\0AddRendererAndPlaneWidget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Visualization3D[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    1,   46,    2, 0x08 /* Private */,
       5,    1,   49,    2, 0x08 /* Private */,
       6,    1,   52,    2, 0x08 /* Private */,
       7,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,

       0        // eod
};

void Visualization3D::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Visualization3D *_t = static_cast<Visualization3D *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Brain3D(); break;
        case 1: _t->AcceptThreshold(); break;
        case 2: _t->SliderValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->ShrinkSliderValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->CutEnableChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->AddRendererAndPlaneWidget(); break;
        default: ;
        }
    }
}

const QMetaObject Visualization3D::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Visualization3D.data,
      qt_meta_data_Visualization3D,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Visualization3D::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Visualization3D::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Visualization3D.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Visualization3D::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

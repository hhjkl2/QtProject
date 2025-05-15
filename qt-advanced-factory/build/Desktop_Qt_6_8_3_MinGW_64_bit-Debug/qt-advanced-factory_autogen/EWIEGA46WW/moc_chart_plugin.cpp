/****************************************************************************
** Meta object code from reading C++ file 'chart_plugin.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../chart_plugin.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCharts/qlineseries.h>
#include <QtCharts/qabstractbarseries.h>
#include <QtCharts/qvbarmodelmapper.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCharts/qcandlestickseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qxyseries.h>
#include <QtCharts/qxyseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qxyseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chart_plugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.3. It"
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
struct qt_meta_tag_ZN12ChartProductE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN12ChartProductE = QtMocHelpers::stringData(
    "ChartProduct"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN12ChartProductE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject ChartProduct::staticMetaObject = { {
    QMetaObject::SuperData::link<IProduct::staticMetaObject>(),
    qt_meta_stringdata_ZN12ChartProductE.offsetsAndSizes,
    qt_meta_data_ZN12ChartProductE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN12ChartProductE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ChartProduct, std::true_type>
    >,
    nullptr
} };

void ChartProduct::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ChartProduct *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *ChartProduct::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChartProduct::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN12ChartProductE.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "com.qt.example.IProduct/1.0"))
        return static_cast< IProduct*>(this);
    return IProduct::qt_metacast(_clname);
}

int ChartProduct::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IProduct::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN12ChartFactoryE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN12ChartFactoryE = QtMocHelpers::stringData(
    "ChartFactory",
    "",
    "parent"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN12ChartFactoryE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       2,   18, // constructors
       0,       // flags
       0,       // signalCount

 // constructors: parameters
    0x80000000 | 1, QMetaType::QObjectStar,    2,
    0x80000000 | 1,

 // constructors: name, argc, parameters, tag, flags, initial metatype offsets
       0,    1,   14,    1, 0x0e,    1 /* Public */,
       0,    0,   17,    1, 0x2e,    2 /* Public | MethodCloned */,

       0        // eod
};

Q_CONSTINIT const QMetaObject ChartFactory::staticMetaObject = { {
    QMetaObject::SuperData::link<IFactory::staticMetaObject>(),
    qt_meta_stringdata_ZN12ChartFactoryE.offsetsAndSizes,
    qt_meta_data_ZN12ChartFactoryE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN12ChartFactoryE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ChartFactory, std::true_type>,
        // constructor 'ChartFactory'
        QtPrivate::TypeAndForceComplete<QObject *, std::false_type>
    >,
    nullptr
} };

void ChartFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ChartFactory *>(_o);
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { ChartFactory *_r = new ChartFactory((*reinterpret_cast<std::add_pointer_t<QObject*>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        case 1: { ChartFactory *_r = new ChartFactory();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    }
    if (_c == QMetaObject::ConstructInPlace) {
        switch (_id) {
        case 0: { new (_a[0]) ChartFactory((*reinterpret_cast<std::add_pointer_t<QObject*>>(_a[1]))); } break;
        case 1: { new (_a[0]) ChartFactory(); } break;
        default: break;
        }
    }
    (void)_t;
}

const QMetaObject *ChartFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChartFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN12ChartFactoryE.stringdata0))
        return static_cast<void*>(this);
    return IFactory::qt_metacast(_clname);
}

int ChartFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IFactory::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP

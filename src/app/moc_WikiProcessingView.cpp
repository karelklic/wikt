/****************************************************************************
** Meta object code from reading C++ file 'WikiProcessingView.h'
**
** Created: Wed Jul 29 19:20:28 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Debug/WikiProcessingView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WikiProcessingView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WikiProcessingView[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_WikiProcessingView[] = {
    "WikiProcessingView\0\0onXmlButtonClicked()\0"
};

const QMetaObject WikiProcessingView::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_WikiProcessingView,
      qt_meta_data_WikiProcessingView, 0 }
};

const QMetaObject *WikiProcessingView::metaObject() const
{
    return &staticMetaObject;
}

void *WikiProcessingView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WikiProcessingView))
        return static_cast<void*>(const_cast< WikiProcessingView*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int WikiProcessingView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onXmlButtonClicked(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

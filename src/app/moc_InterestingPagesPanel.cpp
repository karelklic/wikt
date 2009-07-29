/****************************************************************************
** Meta object code from reading C++ file 'InterestingPagesPanel.h'
**
** Created: Wed Jul 29 19:20:33 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "InterestingPages/InterestingPagesPanel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InterestingPagesPanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InterestingPages__Panel[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      31,   25,   24,   24, 0x05,

 // slots: signature, parameters, type, tag, flags
      57,   24,   24,   24, 0x08,
      78,   72,   24,   24, 0x08,
     101,   72,   24,   24, 0x08,
     123,   72,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_InterestingPages__Panel[] = {
    "InterestingPages::Panel\0\0entry\0"
    "localLinkClicked(QString)\0modelChanged()\0"
    "index\0collapsed(QModelIndex)\0"
    "expanded(QModelIndex)\0activated(QModelIndex)\0"
};

const QMetaObject InterestingPages::Panel::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_InterestingPages__Panel,
      qt_meta_data_InterestingPages__Panel, 0 }
};

const QMetaObject *InterestingPages::Panel::metaObject() const
{
    return &staticMetaObject;
}

void *InterestingPages::Panel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InterestingPages__Panel))
        return static_cast<void*>(const_cast< Panel*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int InterestingPages::Panel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: localLinkClicked((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: modelChanged(); break;
        case 2: collapsed((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: expanded((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: activated((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void InterestingPages::Panel::localLinkClicked(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

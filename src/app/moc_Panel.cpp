/****************************************************************************
** Meta object code from reading C++ file 'Panel.h'
**
** Created: Wed Jul 29 19:20:45 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "RelatedPages/Panel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Panel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RelatedPages__Panel[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      27,   21,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      53,   20,   20,   20, 0x08,
      74,   68,   20,   20, 0x08,
      97,   68,   20,   20, 0x08,
     119,   68,   20,   20, 0x08,
     142,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RelatedPages__Panel[] = {
    "RelatedPages::Panel\0\0entry\0"
    "localLinkClicked(QString)\0modelChanged()\0"
    "index\0collapsed(QModelIndex)\0"
    "expanded(QModelIndex)\0activated(QModelIndex)\0"
    "allowOpeningUrl()\0"
};

const QMetaObject RelatedPages::Panel::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_RelatedPages__Panel,
      qt_meta_data_RelatedPages__Panel, 0 }
};

const QMetaObject *RelatedPages::Panel::metaObject() const
{
    return &staticMetaObject;
}

void *RelatedPages::Panel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RelatedPages__Panel))
        return static_cast<void*>(const_cast< Panel*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int RelatedPages::Panel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        case 5: allowOpeningUrl(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void RelatedPages::Panel::localLinkClicked(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

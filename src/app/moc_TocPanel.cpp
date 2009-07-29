/****************************************************************************
** Meta object code from reading C++ file 'TocPanel.h'
**
** Created: Wed Jul 29 19:20:46 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "TableOfContents/TocPanel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TocPanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TableOfContents__Panel[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      34,   24,   23,   23, 0x05,

 // slots: signature, parameters, type, tag, flags
      53,   23,   23,   23, 0x08,
      74,   68,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TableOfContents__Panel[] = {
    "TableOfContents::Panel\0\0headingId\0"
    "activated(QString)\0modelChanged()\0"
    "index\0itemActivated(QModelIndex)\0"
};

const QMetaObject TableOfContents::Panel::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_TableOfContents__Panel,
      qt_meta_data_TableOfContents__Panel, 0 }
};

const QMetaObject *TableOfContents::Panel::metaObject() const
{
    return &staticMetaObject;
}

void *TableOfContents::Panel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TableOfContents__Panel))
        return static_cast<void*>(const_cast< Panel*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int TableOfContents::Panel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: modelChanged(); break;
        case 2: itemActivated((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void TableOfContents::Panel::activated(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

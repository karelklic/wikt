/****************************************************************************
** Meta object code from reading C++ file 'LookupPanel.h'
**
** Created: Wed Jul 29 19:20:36 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MainWindow/LookupPanel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LookupPanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LookupPanel[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      18,   13,   12,   12, 0x05,
      43,   39,   12,   12, 0x05,
      66,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      82,   12,   12,   12, 0x08,
     100,   12,   12,   12, 0x08,
     117,   12,   12,   12, 0x08,
     130,   12,   12,   12, 0x08,
     139,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LookupPanel[] = {
    "LookupPanel\0\0word\0wordEntered(QString)\0"
    "url\0historyActivated(QUrl)\0homeActivated()\0"
    "editingFinished()\0historyChanged()\0"
    "goPrevious()\0goNext()\0goHome()\0"
};

const QMetaObject LookupPanel::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_LookupPanel,
      qt_meta_data_LookupPanel, 0 }
};

const QMetaObject *LookupPanel::metaObject() const
{
    return &staticMetaObject;
}

void *LookupPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LookupPanel))
        return static_cast<void*>(const_cast< LookupPanel*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int LookupPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: wordEntered((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: historyActivated((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 2: homeActivated(); break;
        case 3: editingFinished(); break;
        case 4: historyChanged(); break;
        case 5: goPrevious(); break;
        case 6: goNext(); break;
        case 7: goHome(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void LookupPanel::wordEntered(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LookupPanel::historyActivated(const QUrl & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LookupPanel::homeActivated()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'Coordinator.h'
**
** Created: Wed Jul 29 19:20:34 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MainWindow/Coordinator.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Coordinator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Coordinator[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      18,   13,   12,   12, 0x0a,
      57,   47,   12,   12, 0x0a,
      93,   89,   12,   12, 0x0a,
     128,  122,   12,   12, 0x0a,
     166,  122,   12,   12, 0x0a,
     211,  122,   12,   12, 0x0a,
     253,   12,   12,   12, 0x0a,
     269,   89,   12,   12, 0x0a,
     292,   12,   12,   12, 0x0a,
     331,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Coordinator[] = {
    "Coordinator\0\0text\0textEnteredToLookup(QString)\0"
    "headingId\0tableOfContentsClicked(QString)\0"
    "url\0localLinkClickedInView(QUrl)\0entry\0"
    "interestingPagesPanelClicked(QString)\0"
    "localLinkClickedInRelatedPagesPanel(QString)\0"
    "categoryClickedInCategoriesPanel(QString)\0"
    "homeActivated()\0historyActivated(QUrl)\0"
    "userSettingChanged_SectionVisibility()\0"
    "userSettingChanged_Translations()\0"
};

const QMetaObject Coordinator::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Coordinator,
      qt_meta_data_Coordinator, 0 }
};

const QMetaObject *Coordinator::metaObject() const
{
    return &staticMetaObject;
}

void *Coordinator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Coordinator))
        return static_cast<void*>(const_cast< Coordinator*>(this));
    return QObject::qt_metacast(_clname);
}

int Coordinator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: textEnteredToLookup((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: tableOfContentsClicked((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: localLinkClickedInView((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 3: interestingPagesPanelClicked((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: localLinkClickedInRelatedPagesPanel((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: categoryClickedInCategoriesPanel((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: homeActivated(); break;
        case 7: historyActivated((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 8: userSettingChanged_SectionVisibility(); break;
        case 9: userSettingChanged_Translations(); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

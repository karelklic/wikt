/****************************************************************************
** Meta object code from reading C++ file 'MenuBar.h'
**
** Created: Wed Jul 29 19:20:38 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MainWindow/MenuBar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MenuBar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MenuBar[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x08,
      16,    8,    8,    8, 0x08,
      27,    8,    8,    8, 0x08,
      45,   37,    8,    8, 0x08,
      72,   37,    8,    8, 0x08,
     103,   37,    8,    8, 0x08,
     132,   37,    8,    8, 0x08,
     162,   37,    8,    8, 0x08,
     197,   37,    8,    8, 0x08,
     229,   37,    8,    8, 0x08,
     255,    8,    8,    8, 0x08,
     266,    8,    8,    8, 0x08,
     276,    8,    8,    8, 0x08,
     287,    8,    8,    8, 0x08,
     313,    8,    8,    8, 0x08,
     331,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MenuBar[] = {
    "MenuBar\0\0find()\0findNext()\0options()\0"
    "checked\0viewEtymologyToggled(bool)\0"
    "viewPronunciationToggled(bool)\0"
    "viewInflectionsToggled(bool)\0"
    "viewTranslationsToggled(bool)\0"
    "viewSemanticRelationsToggled(bool)\0"
    "viewRelatedDerivedToggled(bool)\0"
    "viewAnagramsToggled(bool)\0pageHtml()\0"
    "wordXml()\0wordWiki()\0algorithmWikiProcessing()\0"
    "profilerResults()\0about()\0"
};

const QMetaObject MenuBar::staticMetaObject = {
    { &QMenuBar::staticMetaObject, qt_meta_stringdata_MenuBar,
      qt_meta_data_MenuBar, 0 }
};

const QMetaObject *MenuBar::metaObject() const
{
    return &staticMetaObject;
}

void *MenuBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MenuBar))
        return static_cast<void*>(const_cast< MenuBar*>(this));
    return QMenuBar::qt_metacast(_clname);
}

int MenuBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMenuBar::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: find(); break;
        case 1: findNext(); break;
        case 2: options(); break;
        case 3: viewEtymologyToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: viewPronunciationToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: viewInflectionsToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: viewTranslationsToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: viewSemanticRelationsToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: viewRelatedDerivedToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: viewAnagramsToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: pageHtml(); break;
        case 11: wordXml(); break;
        case 12: wordWiki(); break;
        case 13: algorithmWikiProcessing(); break;
        case 14: profilerResults(); break;
        case 15: about(); break;
        default: ;
        }
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

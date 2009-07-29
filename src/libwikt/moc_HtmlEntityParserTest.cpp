/****************************************************************************
** Meta object code from reading C++ file 'HtmlEntityParserTest.h'
**
** Created: Wed Jul 29 16:30:55 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Wiki/Parser/Html/HtmlEntityParserTest.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HtmlEntityParserTest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HtmlEntityParserTest[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_HtmlEntityParserTest[] = {
    "HtmlEntityParserTest\0\0nbsp()\0"
};

const QMetaObject HtmlEntityParserTest::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_HtmlEntityParserTest,
      qt_meta_data_HtmlEntityParserTest, 0 }
};

const QMetaObject *HtmlEntityParserTest::metaObject() const
{
    return &staticMetaObject;
}

void *HtmlEntityParserTest::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HtmlEntityParserTest))
        return static_cast<void*>(const_cast< HtmlEntityParserTest*>(this));
    return QObject::qt_metacast(_clname);
}

int HtmlEntityParserTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: nbsp(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

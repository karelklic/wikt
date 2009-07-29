/****************************************************************************
** Meta object code from reading C++ file 'BoldItalicParserTest.h'
**
** Created: Wed Jul 29 16:30:54 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Wiki/Parser/BoldItalic/BoldItalicParserTest.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BoldItalicParserTest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BoldItalicParserTest[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x08,
      34,   21,   21,   21, 0x08,
      46,   21,   21,   21, 0x08,
      58,   21,   21,   21, 0x08,
      70,   21,   21,   21, 0x08,
      82,   21,   21,   21, 0x08,
      94,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BoldItalicParserTest[] = {
    "BoldItalicParserTest\0\0embedded0()\0"
    "embedded1()\0embedded2()\0embedded3()\0"
    "embedded4()\0embedded5()\0embedded6()\0"
};

const QMetaObject BoldItalicParserTest::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_BoldItalicParserTest,
      qt_meta_data_BoldItalicParserTest, 0 }
};

const QMetaObject *BoldItalicParserTest::metaObject() const
{
    return &staticMetaObject;
}

void *BoldItalicParserTest::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BoldItalicParserTest))
        return static_cast<void*>(const_cast< BoldItalicParserTest*>(this));
    return QObject::qt_metacast(_clname);
}

int BoldItalicParserTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: embedded0(); break;
        case 1: embedded1(); break;
        case 2: embedded2(); break;
        case 3: embedded3(); break;
        case 4: embedded4(); break;
        case 5: embedded5(); break;
        case 6: embedded6(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

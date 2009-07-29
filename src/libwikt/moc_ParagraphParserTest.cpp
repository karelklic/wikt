/****************************************************************************
** Meta object code from reading C++ file 'ParagraphParserTest.h'
**
** Created: Wed Jul 29 16:30:58 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Wiki/Parser/Paragraph/ParagraphParserTest.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ParagraphParserTest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ParagraphParserTest[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x08,
      40,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ParagraphParserTest[] = {
    "ParagraphParserTest\0\0startingWithLink()\0"
    "parse()\0"
};

const QMetaObject ParagraphParserTest::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ParagraphParserTest,
      qt_meta_data_ParagraphParserTest, 0 }
};

const QMetaObject *ParagraphParserTest::metaObject() const
{
    return &staticMetaObject;
}

void *ParagraphParserTest::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ParagraphParserTest))
        return static_cast<void*>(const_cast< ParagraphParserTest*>(this));
    return QObject::qt_metacast(_clname);
}

int ParagraphParserTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: startingWithLink(); break;
        case 1: parse(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'TemplateSolverTest.h'
**
** Created: Wed Jul 29 17:53:51 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "TemplateSolverTest.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TemplateSolverTest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TemplateSolverTest[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x08,
      44,   19,   19,   19, 0x08,
      57,   19,   19,   19, 0x08,
      66,   19,   19,   19, 0x08,
      84,   19,   19,   19, 0x08,
     112,   19,   19,   19, 0x08,
     139,   19,   19,   19, 0x08,
     150,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TemplateSolverTest[] = {
    "TemplateSolverTest\0\0declaringDefaultValue()\0"
    "moreBraces()\0formOf()\0isValidPageName()\0"
    "evaluatedWikiSyntaxSimple()\0"
    "newlineAddingInTemplates()\0pluralOf()\0"
    "embeddedLink()\0"
};

const QMetaObject TemplateSolverTest::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TemplateSolverTest,
      qt_meta_data_TemplateSolverTest, 0 }
};

const QMetaObject *TemplateSolverTest::metaObject() const
{
    return &staticMetaObject;
}

void *TemplateSolverTest::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TemplateSolverTest))
        return static_cast<void*>(const_cast< TemplateSolverTest*>(this));
    return QObject::qt_metacast(_clname);
}

int TemplateSolverTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: declaringDefaultValue(); break;
        case 1: moreBraces(); break;
        case 2: formOf(); break;
        case 3: isValidPageName(); break;
        case 4: evaluatedWikiSyntaxSimple(); break;
        case 5: newlineAddingInTemplates(); break;
        case 6: pluralOf(); break;
        case 7: embeddedLink(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'MediaDownloader.h'
**
** Created: Wed Jul 29 19:07:52 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MediaDownloader.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MediaDownloader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MediaDownloader[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      28,   16,   16,   16, 0x08,
      49,   43,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MediaDownloader[] = {
    "MediaDownloader\0\0finished()\0processEntry()\0"
    "reply\0downloadFinished(QNetworkReply*)\0"
};

const QMetaObject MediaDownloader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MediaDownloader,
      qt_meta_data_MediaDownloader, 0 }
};

const QMetaObject *MediaDownloader::metaObject() const
{
    return &staticMetaObject;
}

void *MediaDownloader::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MediaDownloader))
        return static_cast<void*>(const_cast< MediaDownloader*>(this));
    return QObject::qt_metacast(_clname);
}

int MediaDownloader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: finished(); break;
        case 1: processEntry(); break;
        case 2: downloadFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MediaDownloader::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE

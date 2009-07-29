/****************************************************************************
** Meta object code from reading C++ file 'WebView.h'
**
** Created: Wed Jul 29 19:20:41 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MainWindow/WebView/WebView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WebView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WebView[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      13,    9,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      48,   42,    8,    8, 0x08,
      93,   85,    8,    8, 0x08,
     130,    9,    8,    8, 0x08,
     153,  150,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_WebView[] = {
    "WebView\0\0url\0localLinkClickedInView(QUrl)\0"
    "reply\0onUnsupportedContent(QNetworkReply*)\0"
    "request\0onDownloadRequested(QNetworkRequest)\0"
    "onLinkClicked(QUrl)\0ok\0onLoadFinished(bool)\0"
};

const QMetaObject WebView::staticMetaObject = {
    { &QWebView::staticMetaObject, qt_meta_stringdata_WebView,
      qt_meta_data_WebView, 0 }
};

const QMetaObject *WebView::metaObject() const
{
    return &staticMetaObject;
}

void *WebView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WebView))
        return static_cast<void*>(const_cast< WebView*>(this));
    return QWebView::qt_metacast(_clname);
}

int WebView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWebView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: localLinkClickedInView((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 1: onUnsupportedContent((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 2: onDownloadRequested((*reinterpret_cast< const QNetworkRequest(*)>(_a[1]))); break;
        case 3: onLinkClicked((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 4: onLoadFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void WebView::localLinkClickedInView(const QUrl & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

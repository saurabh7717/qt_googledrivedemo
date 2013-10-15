/****************************************************************************
** Meta object code from reading C++ file 'googled.h'
**
** Created: Mon Jul 29 22:12:09 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "googled.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'googled.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_googled[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,    8,    8,    8, 0x0a,
      63,    8,    8,    8, 0x0a,
      93,    8,    8,    8, 0x0a,
     127,    8,    8,    8, 0x0a,
     162,    8,    8,    8, 0x0a,
     189,    8,    8,    8, 0x0a,
     223,    8,    8,    8, 0x0a,
     254,    8,    8,    8, 0x0a,
     280,    8,    8,    8, 0x0a,
     309,    8,    8,    8, 0x0a,
     342,    8,    8,    8, 0x0a,
     374,    8,    8,    8, 0x0a,
     411,    8,    8,    8, 0x0a,
     446,    8,    8,    8, 0x0a,
     493,    8,    8,    8, 0x0a,
     525,    8,    8,    8, 0x0a,
     563,    8,    8,    8, 0x0a,
     596,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_googled[] = {
    "googled\0\0finished(QNetworkReply*)\0"
    "finishedSlot(QNetworkReply*)\0"
    "finishedSlot1(QNetworkReply*)\0"
    "drivefinishedSlot(QNetworkReply*)\0"
    "uploadfinishedSlot(QNetworkReply*)\0"
    "uploadSlot(QNetworkReply*)\0"
    "newuploadSettings(QNetworkReply*)\0"
    "folderlistSlot(QNetworkReply*)\0"
    "getfolder(QNetworkReply*)\0"
    "createfolder(QNetworkReply*)\0"
    "foldercreateSlot(QNetworkReply*)\0"
    "resumableUpload(QNetworkReply*)\0"
    "resumableUploadReply(QNetworkReply*)\0"
    "tryMultipartUpload(QNetworkReply*)\0"
    "tryMultipartUploadInsideFolder(QNetworkReply*)\0"
    "tryFolderCreate(QNetworkReply*)\0"
    "tryFolderCreateInside(QNetworkReply*)\0"
    "tryFolderListing(QNetworkReply*)\0"
    "tryGettingUserName(QNetworkReply*)\0"
};

void googled::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        googled *_t = static_cast<googled *>(_o);
        switch (_id) {
        case 0: _t->finished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 1: _t->finishedSlot((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 2: _t->finishedSlot1((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 3: _t->drivefinishedSlot((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 4: _t->uploadfinishedSlot((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 5: _t->uploadSlot((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 6: _t->newuploadSettings((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 7: _t->folderlistSlot((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 8: _t->getfolder((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 9: _t->createfolder((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 10: _t->foldercreateSlot((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 11: _t->resumableUpload((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 12: _t->resumableUploadReply((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 13: _t->tryMultipartUpload((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 14: _t->tryMultipartUploadInsideFolder((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 15: _t->tryFolderCreate((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 16: _t->tryFolderCreateInside((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 17: _t->tryFolderListing((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 18: _t->tryGettingUserName((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData googled::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject googled::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_googled,
      qt_meta_data_googled, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &googled::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *googled::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *googled::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_googled))
        return static_cast<void*>(const_cast< googled*>(this));
    return QObject::qt_metacast(_clname);
}

int googled::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void googled::finished(QNetworkReply * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

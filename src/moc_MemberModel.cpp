/****************************************************************************
** Meta object code from reading C++ file 'MemberModel.h'
**
** Created: Wed Oct 5 18:36:09 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MemberModel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MemberModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MemberModel[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      28,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MemberModel[] = {
    "MemberModel\0\0appendMember()\0submitMember()\0"
};

const QMetaObject MemberModel::staticMetaObject = {
    { &QAbstractTableModel::staticMetaObject, qt_meta_stringdata_MemberModel,
      qt_meta_data_MemberModel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MemberModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MemberModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MemberModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MemberModel))
        return static_cast<void*>(const_cast< MemberModel*>(this));
    return QAbstractTableModel::qt_metacast(_clname);
}

int MemberModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: appendMember(); break;
        case 1: submitMember(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

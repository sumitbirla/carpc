/****************************************************************************
** VolumeControl meta object code from reading C++ file 'VolumeControl.h'
**
** Created: Sun Nov 23 20:32:05 2003
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.1.2   edited Feb 24 09:29 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "VolumeControl.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *VolumeControl::className() const
{
    return "VolumeControl";
}

QMetaObject *VolumeControl::metaObj = 0;
static QMetaObjectCleanUp cleanUp_VolumeControl( "VolumeControl", &VolumeControl::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString VolumeControl::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "VolumeControl", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString VolumeControl::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "VolumeControl", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* VolumeControl::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QObject::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"muteToggled", 1, param_slot_0 };
    static const QMetaData slot_tbl[] = {
	{ "muteToggled(int)", &slot_0, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"volumeChanged", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "volumeChanged(int)", &signal_0, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"VolumeControl", parentObject,
	slot_tbl, 1,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_VolumeControl.setMetaObject( metaObj );
    return metaObj;
}

void* VolumeControl::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "VolumeControl" ) )
	return this;
    return QObject::qt_cast( clname );
}

// SIGNAL volumeChanged
void VolumeControl::volumeChanged( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 0, t0 );
}

bool VolumeControl::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: muteToggled((int)static_QUType_int.get(_o+1)); break;
    default:
	return QObject::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool VolumeControl::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: volumeChanged((int)static_QUType_int.get(_o+1)); break;
    default:
	return QObject::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool VolumeControl::qt_property( int id, int f, QVariant* v)
{
    return QObject::qt_property( id, f, v);
}

bool VolumeControl::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES

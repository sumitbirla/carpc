/****************************************************************************
** VolumeDisplayWidget meta object code from reading C++ file 'volumedisplay.h'
**
** Created: Sun Nov 23 20:32:15 2003
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.1.2   edited Feb 24 09:29 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "volumedisplay.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *VolumeDisplayWidget::className() const
{
    return "VolumeDisplayWidget";
}

QMetaObject *VolumeDisplayWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_VolumeDisplayWidget( "VolumeDisplayWidget", &VolumeDisplayWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString VolumeDisplayWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "VolumeDisplayWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString VolumeDisplayWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "VolumeDisplayWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* VolumeDisplayWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"volumeChanged", 1, param_slot_0 };
    static const QUMethod slot_1 = {"timeout", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "volumeChanged(int)", &slot_0, QMetaData::Public },
	{ "timeout()", &slot_1, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"VolumeDisplayWidget", parentObject,
	slot_tbl, 2,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_VolumeDisplayWidget.setMetaObject( metaObj );
    return metaObj;
}

void* VolumeDisplayWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "VolumeDisplayWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool VolumeDisplayWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: volumeChanged((int)static_QUType_int.get(_o+1)); break;
    case 1: timeout(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool VolumeDisplayWidget::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool VolumeDisplayWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool VolumeDisplayWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES

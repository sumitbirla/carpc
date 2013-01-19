/****************************************************************************
** ID3Tag meta object code from reading C++ file 'id3tag.h'
**
** Created: Sun Nov 23 20:30:50 2003
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.1.2   edited Feb 24 09:29 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "id3tag.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *ID3Tag::className() const
{
    return "ID3Tag";
}

QMetaObject *ID3Tag::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ID3Tag( "ID3Tag", &ID3Tag::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString ID3Tag::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ID3Tag", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ID3Tag::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ID3Tag", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ID3Tag::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QObject::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"ID3Tag", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ID3Tag.setMetaObject( metaObj );
    return metaObj;
}

void* ID3Tag::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ID3Tag" ) )
	return this;
    return QObject::qt_cast( clname );
}

bool ID3Tag::qt_invoke( int _id, QUObject* _o )
{
    return QObject::qt_invoke(_id,_o);
}

bool ID3Tag::qt_emit( int _id, QUObject* _o )
{
    return QObject::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool ID3Tag::qt_property( int id, int f, QVariant* v)
{
    return QObject::qt_property( id, f, v);
}

bool ID3Tag::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES

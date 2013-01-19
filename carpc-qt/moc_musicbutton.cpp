/****************************************************************************
** MusicButton meta object code from reading C++ file 'musicbutton.h'
**
** Created: Sun Nov 23 20:31:23 2003
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.1.2   edited Feb 24 09:29 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "musicbutton.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MusicButton::className() const
{
    return "MusicButton";
}

QMetaObject *MusicButton::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MusicButton( "MusicButton", &MusicButton::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MusicButton::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MusicButton", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MusicButton::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MusicButton", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MusicButton::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"clicked", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "clicked(int)", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"MusicButton", parentObject,
	0, 0,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MusicButton.setMetaObject( metaObj );
    return metaObj;
}

void* MusicButton::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MusicButton" ) )
	return this;
    return QWidget::qt_cast( clname );
}

// SIGNAL clicked
void MusicButton::clicked( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 0, t0 );
}

bool MusicButton::qt_invoke( int _id, QUObject* _o )
{
    return QWidget::qt_invoke(_id,_o);
}

bool MusicButton::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: clicked((int)static_QUType_int.get(_o+1)); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool MusicButton::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool MusicButton::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES

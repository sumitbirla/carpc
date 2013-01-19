/****************************************************************************
** FlatButton meta object code from reading C++ file 'flatbutton.h'
**
** Created: Sun Nov 23 20:30:39 2003
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.1.2   edited Feb 24 09:29 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "flatbutton.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *FlatButton::className() const
{
    return "FlatButton";
}

QMetaObject *FlatButton::metaObj = 0;
static QMetaObjectCleanUp cleanUp_FlatButton( "FlatButton", &FlatButton::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString FlatButton::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "FlatButton", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString FlatButton::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "FlatButton", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* FlatButton::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod signal_0 = {"clicked", 0, 0 };
    static const QUParameter param_signal_1[] = {
	{ 0, &static_QUType_ptr, "float", QUParameter::In }
    };
    static const QUMethod signal_1 = {"stationSelected", 1, param_signal_1 };
    static const QUParameter param_signal_2[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_2 = {"toggled", 1, param_signal_2 };
    static const QMetaData signal_tbl[] = {
	{ "clicked()", &signal_0, QMetaData::Public },
	{ "stationSelected(float)", &signal_1, QMetaData::Public },
	{ "toggled(int)", &signal_2, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"FlatButton", parentObject,
	0, 0,
	signal_tbl, 3,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_FlatButton.setMetaObject( metaObj );
    return metaObj;
}

void* FlatButton::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "FlatButton" ) )
	return this;
    return QWidget::qt_cast( clname );
}

// SIGNAL clicked
void FlatButton::clicked()
{
    activate_signal( staticMetaObject()->signalOffset() + 0 );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL stationSelected
void FlatButton::stationSelected( float t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 1 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,&t0);
    activate_signal( clist, o );
}

// SIGNAL toggled
void FlatButton::toggled( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 2, t0 );
}

bool FlatButton::qt_invoke( int _id, QUObject* _o )
{
    return QWidget::qt_invoke(_id,_o);
}

bool FlatButton::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: clicked(); break;
    case 1: stationSelected((float)(*((float*)static_QUType_ptr.get(_o+1)))); break;
    case 2: toggled((int)static_QUType_int.get(_o+1)); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool FlatButton::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool FlatButton::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES

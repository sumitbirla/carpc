/****************************************************************************
** PhotoWidget meta object code from reading C++ file 'photowidget.h'
**
** Created: Sun Nov 23 20:31:33 2003
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.1.2   edited Feb 24 09:29 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "photowidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *PhotoWidget::className() const
{
    return "PhotoWidget";
}

QMetaObject *PhotoWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_PhotoWidget( "PhotoWidget", &PhotoWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString PhotoWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "PhotoWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString PhotoWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "PhotoWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* PhotoWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"beginClicked", 0, 0 };
    static const QUMethod slot_1 = {"previousClicked", 0, 0 };
    static const QUParameter param_slot_2[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"slideshowToggled", 1, param_slot_2 };
    static const QUMethod slot_3 = {"nextClicked", 0, 0 };
    static const QUMethod slot_4 = {"endClicked", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "beginClicked()", &slot_0, QMetaData::Public },
	{ "previousClicked()", &slot_1, QMetaData::Public },
	{ "slideshowToggled(int)", &slot_2, QMetaData::Public },
	{ "nextClicked()", &slot_3, QMetaData::Public },
	{ "endClicked()", &slot_4, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"PhotoWidget", parentObject,
	slot_tbl, 5,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_PhotoWidget.setMetaObject( metaObj );
    return metaObj;
}

void* PhotoWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "PhotoWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool PhotoWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: beginClicked(); break;
    case 1: previousClicked(); break;
    case 2: slideshowToggled((int)static_QUType_int.get(_o+1)); break;
    case 3: nextClicked(); break;
    case 4: endClicked(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool PhotoWidget::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool PhotoWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool PhotoWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES

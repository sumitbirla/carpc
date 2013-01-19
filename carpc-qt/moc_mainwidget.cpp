/****************************************************************************
** MainWidget meta object code from reading C++ file 'mainwidget.h'
**
** Created: Sun Nov 23 20:31:00 2003
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.1.2   edited Feb 24 09:29 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "mainwidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MainWidget::className() const
{
    return "MainWidget";
}

QMetaObject *MainWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MainWidget( "MainWidget", &MainWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MainWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MainWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MainWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MainWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MainWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"upClicked", 0, 0 };
    static const QUMethod slot_1 = {"downClicked", 0, 0 };
    static const QUMethod slot_2 = {"leftClicked", 0, 0 };
    static const QUMethod slot_3 = {"rightClicked", 0, 0 };
    static const QUMethod slot_4 = {"menuClicked", 0, 0 };
    static const QUMethod slot_5 = {"radioClicked", 0, 0 };
    static const QUMethod slot_6 = {"mp3Clicked", 0, 0 };
    static const QUMethod slot_7 = {"gpsClicked", 0, 0 };
    static const QUMethod slot_8 = {"obdiiClicked", 0, 0 };
    static const QUMethod slot_9 = {"photoClicked", 0, 0 };
    static const QUMethod slot_10 = {"linuxClicked", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "upClicked()", &slot_0, QMetaData::Public },
	{ "downClicked()", &slot_1, QMetaData::Public },
	{ "leftClicked()", &slot_2, QMetaData::Public },
	{ "rightClicked()", &slot_3, QMetaData::Public },
	{ "menuClicked()", &slot_4, QMetaData::Public },
	{ "radioClicked()", &slot_5, QMetaData::Public },
	{ "mp3Clicked()", &slot_6, QMetaData::Public },
	{ "gpsClicked()", &slot_7, QMetaData::Public },
	{ "obdiiClicked()", &slot_8, QMetaData::Public },
	{ "photoClicked()", &slot_9, QMetaData::Public },
	{ "linuxClicked()", &slot_10, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"MainWidget", parentObject,
	slot_tbl, 11,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MainWidget.setMetaObject( metaObj );
    return metaObj;
}

void* MainWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MainWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool MainWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: upClicked(); break;
    case 1: downClicked(); break;
    case 2: leftClicked(); break;
    case 3: rightClicked(); break;
    case 4: menuClicked(); break;
    case 5: radioClicked(); break;
    case 6: mp3Clicked(); break;
    case 7: gpsClicked(); break;
    case 8: obdiiClicked(); break;
    case 9: photoClicked(); break;
    case 10: linuxClicked(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MainWidget::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MainWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool MainWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES

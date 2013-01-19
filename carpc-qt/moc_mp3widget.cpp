/****************************************************************************
** MP3Widget meta object code from reading C++ file 'mp3widget.h'
**
** Created: Sun Nov 23 20:31:12 2003
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.1.2   edited Feb 24 09:29 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "mp3widget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MP3Widget::className() const
{
    return "MP3Widget";
}

QMetaObject *MP3Widget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MP3Widget( "MP3Widget", &MP3Widget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MP3Widget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MP3Widget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MP3Widget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MP3Widget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MP3Widget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"mp3selected", 1, param_slot_0 };
    static const QUMethod slot_1 = {"firstPageClicked", 0, 0 };
    static const QUMethod slot_2 = {"lastPageClicked", 0, 0 };
    static const QUMethod slot_3 = {"nextPageClicked", 0, 0 };
    static const QUMethod slot_4 = {"prevPageClicked", 0, 0 };
    static const QUParameter param_slot_5[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"randomToggled", 1, param_slot_5 };
    static const QMetaData slot_tbl[] = {
	{ "mp3selected(int)", &slot_0, QMetaData::Public },
	{ "firstPageClicked()", &slot_1, QMetaData::Public },
	{ "lastPageClicked()", &slot_2, QMetaData::Public },
	{ "nextPageClicked()", &slot_3, QMetaData::Public },
	{ "prevPageClicked()", &slot_4, QMetaData::Public },
	{ "randomToggled(int)", &slot_5, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"MP3Widget", parentObject,
	slot_tbl, 6,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MP3Widget.setMetaObject( metaObj );
    return metaObj;
}

void* MP3Widget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MP3Widget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool MP3Widget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: mp3selected((int)static_QUType_int.get(_o+1)); break;
    case 1: firstPageClicked(); break;
    case 2: lastPageClicked(); break;
    case 3: nextPageClicked(); break;
    case 4: prevPageClicked(); break;
    case 5: randomToggled((int)static_QUType_int.get(_o+1)); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MP3Widget::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MP3Widget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool MP3Widget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES

/****************************************************************************
** RadioWidget meta object code from reading C++ file 'radiowidget.h'
**
** Created: Sun Nov 23 20:31:44 2003
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.1.2   edited Feb 24 09:29 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "radiowidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *RadioWidget::className() const
{
    return "RadioWidget";
}

QMetaObject *RadioWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_RadioWidget( "RadioWidget", &RadioWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString RadioWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "RadioWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString RadioWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "RadioWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* RadioWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"nextClicked", 0, 0 };
    static const QUMethod slot_1 = {"previousClicked", 0, 0 };
    static const QUParameter param_slot_2[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"scanForwardToggled", 1, param_slot_2 };
    static const QUParameter param_slot_3[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"scanBackwardToggled", 1, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"scanToggled", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ 0, &static_QUType_ptr, "float", QUParameter::In }
    };
    static const QUMethod slot_5 = {"stationSelected", 1, param_slot_5 };
    static const QMetaData slot_tbl[] = {
	{ "nextClicked()", &slot_0, QMetaData::Public },
	{ "previousClicked()", &slot_1, QMetaData::Public },
	{ "scanForwardToggled(int)", &slot_2, QMetaData::Public },
	{ "scanBackwardToggled(int)", &slot_3, QMetaData::Public },
	{ "scanToggled(int)", &slot_4, QMetaData::Public },
	{ "stationSelected(float)", &slot_5, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_double, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"freqChanged", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "freqChanged(double)", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"RadioWidget", parentObject,
	slot_tbl, 6,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_RadioWidget.setMetaObject( metaObj );
    return metaObj;
}

void* RadioWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "RadioWidget" ) )
	return this;
    if ( !qstrcmp( clname, "QThread" ) )
	return (QThread*)this;
    return QWidget::qt_cast( clname );
}

// SIGNAL freqChanged
void RadioWidget::freqChanged( double t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 0, t0 );
}

bool RadioWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: nextClicked(); break;
    case 1: previousClicked(); break;
    case 2: scanForwardToggled((int)static_QUType_int.get(_o+1)); break;
    case 3: scanBackwardToggled((int)static_QUType_int.get(_o+1)); break;
    case 4: scanToggled((int)static_QUType_int.get(_o+1)); break;
    case 5: stationSelected((float)(*((float*)static_QUType_ptr.get(_o+1)))); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool RadioWidget::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: freqChanged((double)static_QUType_double.get(_o+1)); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool RadioWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool RadioWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES

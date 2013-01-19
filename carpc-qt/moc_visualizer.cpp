/****************************************************************************
** VisualizerWidget meta object code from reading C++ file 'visualizer.h'
**
** Created: Sun Nov 23 20:35:19 2003
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.1.2   edited Feb 24 09:29 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "visualizer.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *VisualizerWidget::className() const
{
    return "VisualizerWidget";
}

QMetaObject *VisualizerWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_VisualizerWidget( "VisualizerWidget", &VisualizerWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString VisualizerWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "VisualizerWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString VisualizerWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "VisualizerWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* VisualizerWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"VisualizerWidget", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_VisualizerWidget.setMetaObject( metaObj );
    return metaObj;
}

void* VisualizerWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "VisualizerWidget" ) )
	return this;
    if ( !qstrcmp( clname, "QThread" ) )
	return (QThread*)this;
    return QWidget::qt_cast( clname );
}

bool VisualizerWidget::qt_invoke( int _id, QUObject* _o )
{
    return QWidget::qt_invoke(_id,_o);
}

bool VisualizerWidget::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool VisualizerWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool VisualizerWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES

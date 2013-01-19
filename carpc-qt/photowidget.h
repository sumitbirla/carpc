#ifndef PHOTOWIDGET_H
#define PHOTOWIDGET_H

#include "flatbutton.h"

#include <qdir.h>
#include <qimage.h>


class PhotoWidget : public QWidget
{
   Q_OBJECT

   public:
      PhotoWidget( QWidget *parent=0, const char *name=0 );

   public slots:
	   void beginClicked();
	   void previousClicked();
	   void slideshowToggled(int);
	   void nextClicked();
	   void endClicked();

   protected:
      void resizeEvent(QResizeEvent *);
      void paintEvent(QPaintEvent *);

   private:

   private:
      QDir dir;
	  QImage img;
      int curImageIndex;
      bool isRandom;
};


#endif

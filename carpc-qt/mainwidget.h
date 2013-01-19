#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <qwidget.h>
#include "VolumeControl.h"
#include "volumedisplay.h"
#include "radiowidget.h"
#include "mp3widget.h"
#include "photowidget.h"


class MainWidget : public QWidget{
   Q_OBJECT

   public:
      MainWidget( int w, int h, QWidget *parent=0, const char *name=0 );

   public slots:
      void upClicked();
      void downClicked();
      void leftClicked();
      void rightClicked();
      void menuClicked();
      void radioClicked();
      void mp3Clicked();
      void gpsClicked();
      void obdiiClicked();
	  void photoClicked();
	  void linuxClicked();

   private:
      VolumeControl *vol;
      VolumeDisplayWidget *vol_disp;
      QWidget *apps_widget;
      RadioWidget *radio_widget;
      MP3Widget *mp3_widget;
	  PhotoWidget *photo_widget;
      int button_width, button_height;
};


#endif



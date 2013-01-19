#ifndef VOLUMEDISPLAY_H
#define VOLUMEDISPLAY_H

#include <qwidget.h>
#include <qprogressbar.h>
#include <qtimer.h>
#include <qlabel.h>

class VolumeDisplayWidget : public QWidget
{
   Q_OBJECT

   public:
      VolumeDisplayWidget( QWidget *parent=0, const char *name=0 );

   public slots:
      void volumeChanged(int);
      void timeout();

   private:
      QTimer *timer;
      QLabel *label;
      QFont font;

   public:
      QProgressBar *bar;
};


#endif


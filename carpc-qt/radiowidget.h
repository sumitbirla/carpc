#ifndef RADIOWIDGET_H
#define RADIOWIDGET_H

#include <qwidget.h>
#include <qthread.h>
#include <qlcdnumber.h>
#include "visualizer.h"
#include "flatbutton.h"


class RadioWidget : public QWidget, public QThread
{
   Q_OBJECT

   public:
      RadioWidget( QWidget *parent=0, const char *name=0 );
      void setFrequency(float freq);
      int getSignalStrength();
      void activate();
      void deactivate();

   signals:
      void freqChanged(double);

   public slots:
      void nextClicked();
      void previousClicked();
      void scanForwardToggled(int);
      void scanBackwardToggled(int);
      void scanToggled(int);
      void stationSelected(float);

   protected:
      void resizeEvent(QResizeEvent *);
	  void showEvent ( QShowEvent * );
      void hideEvent ( QHideEvent * );
      void run();

   private:
      FlatButton *preset[9];
      FlatButton *scan, *scanForward, *scanBackward;
      QLCDNumber *lcd;
      VisualizerWidget *visualizer;
      float frequency, freq_factor;
      int fd;
      bool threadRunning;
      int scanDirection;
};


#endif


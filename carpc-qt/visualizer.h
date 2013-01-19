#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <qwidget.h>
#include <qthread.h>
#include "fft.h"


#define NUM_SAMPLES 2048        /* size of the buffer */
#define SAMPLE_RATE 44100       /* the sampling rate */
#define SAMPLE_SIZE 16          /* sample size: 8 or 16 bits */
#define CHANNELS 1              /* 1 = mono 2 = stereo */
#define NUM_BUCKETS 16          /* number of spectral bars */


class VisualizerWidget : public QWidget, public QThread
{
   Q_OBJECT

   public:
      VisualizerWidget( QWidget *parent=0, const char *name=0 );
	  void stop();

   protected:
      void paintEvent(QPaintEvent *);
      int openDSP();
      void run();

   private:
      FFT fft;
      unsigned short buf[NUM_SAMPLES];
      float in_wavedata[NUM_SAMPLES];
      float out_spectraldata[NUM_BUCKETS];
      int display_data[NUM_BUCKETS];
	  bool threadRunning;
	  void paint();
};


#endif


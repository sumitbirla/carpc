#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/videodev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "radiowidget.h"

 
/*
 * The constructor instantiates all the necessary widgets used for controlling
 * the radio.  This includes the 9 preset buttons, scan buttons and the 
 * next/prev buttons.  The VisualizerWidget is also created which uses FFT to 
 * display a frequency spectrum in real time.  This is done by reading in 
 * sound samples from /dev/dsp (line in)
 */ 
RadioWidget::RadioWidget( QWidget *parent, const char *name )
: QWidget( parent, name )
{
   setBackgroundColor(Qt::black);

   // instantiate the LCD to display the current radio frequency
   lcd = new QLCDNumber(5, this, 0);
   lcd->setSegmentStyle(QLCDNumber::Filled);
   QPalette palette = lcd->palette();
   palette.setColor(QPalette::Normal, QColorGroup::Foreground, Qt::red);
   palette.setColor(QPalette::Normal, QColorGroup::Background, Qt::black);
   palette.setColor(QPalette::Normal, QColorGroup::Light, Qt::red);
   palette.setColor(QPalette::Normal, QColorGroup::Dark, Qt::black);
   lcd->setPalette(palette);
   //lcd->setWFlags(Qt::WStyle_NoBorder);
   connect(this, SIGNAL(freqChanged(double)), lcd, SLOT(display(double)));

   // create buttons for tuning the radio
   scanBackward = new FlatButton(FlatButton::Toggle, "|<", this,0);
   scanBackward->setNormalColor(64, 164, 64);
   scanBackward->setHiliteColor(200, 94, 94);
   scanBackward->setToggleColor(200, 94, 94);
   scanBackward->setGeometry(0, 430, 100, 50);
   connect(scanBackward, SIGNAL(toggled(int)), this, SLOT(scanBackwardToggled(int)));

   FlatButton *button = new FlatButton(FlatButton::Text, "<<", this,0);
   button->setNormalColor(64, 164, 64);
   button->setHiliteColor(100, 230, 100);
   button->setGeometry(100, 430, 100, 50);
   connect(button, SIGNAL(clicked()), this, SLOT(previousClicked()));

   scan = new FlatButton(FlatButton::Toggle, "Scan", this,0);
   scan->setNormalColor(64, 164, 64);
   scan->setHiliteColor(200, 94, 94);
   scan->setToggleColor(200, 94, 94);
   scan->setGeometry(200, 430, 160, 50);
   connect(scan, SIGNAL(toggled(int)), this, SLOT(scanToggled(int)));

   button = new FlatButton(FlatButton::Text, ">>", this,0);
   button->setNormalColor(64, 164, 64);
   button->setHiliteColor(100, 230, 100);
   button->setGeometry(360, 430, 100, 50);
   connect(button, SIGNAL(clicked()), this, SLOT(nextClicked()));

   scanForward = new FlatButton(FlatButton::Toggle, ">|", this,0);
   scanForward->setNormalColor(64, 164, 64);
   scanForward->setHiliteColor(200, 94, 94);
   scanForward->setToggleColor(200, 94, 94);
   scanForward->setGeometry(460, 430, 100, 50);
   connect(scanForward, SIGNAL(toggled(int)), this, SLOT(scanForwardToggled(int)));

   // create the presets
   // TO DO:  Read presets from a file
   preset[0] = new FlatButton(FlatButton::Radio, "89.7", this,0); 
   preset[1] = new FlatButton(FlatButton::Radio, "93.3", this,0);
   preset[2] = new FlatButton(FlatButton::Radio, "94.9", this,0); 
   preset[3] = new FlatButton(FlatButton::Radio, "95.7", this,0);
   preset[4] = new FlatButton(FlatButton::Radio, "97.9", this,0);
   preset[5] = new FlatButton(FlatButton::Radio, "101.5", this,0);   
   preset[6] = new FlatButton(FlatButton::Radio, "102.5", this,0);
   preset[7] = new FlatButton(FlatButton::Radio, "105.1", this,0);
   preset[8] = new FlatButton(FlatButton::Radio, "107.9", this,0);

   // connect every preset button's clicked signal to stationSelected slot
   for (int i = 0; i < 9; i++)
      connect(preset[i], SIGNAL(stationSelected(float)), 
              this, SLOT(stationSelected(float)));


   // Initialize the radio device
   frequency = 89.7;
   struct video_tuner tuner;
   fd = open("/dev/radio0", O_TRUNC);
   if (fd > 0)
   {
      tuner.tuner = 0;  
      if (ioctl(fd, VIDIOCGTUNER , &tuner) == 0)
         freq_factor = (tuner.flags&VIDEO_TUNER_LOW ? 16000.0 : 16.0);
      setFrequency(93.3);
   }

   deactivate();

   threadRunning = FALSE;

   visualizer = new VisualizerWidget(this, 0);
}


// radio was resized, so resize children appropriately 
void RadioWidget::resizeEvent ( QResizeEvent * )
{
   QRect r  = rect();
   int w = r.right()/3;
   int h = (r.bottom()-180)/3;
   int i, j;

   for (i = 0; i < 3; i++)
   {
      for (j=0; j < 3; j++)
      {
         preset[i*3+j]->setFontSize(36);
         preset[i*3+j]->setGeometry(j*w, i*h, w, h); 
      }
   }
   lcd->setGeometry(r.right()-200, r.bottom()-180, 200, 130);
   visualizer->setGeometry(0, r.bottom()-180, r.right()-200, 130);
   visualizer->start();
}


void RadioWidget::showEvent( QShowEvent *)
{
	QRect r = rect();
	// create the frequency spectrum display widget
}

void RadioWidget::hideEvent( QHideEvent *)
{
	// hide() will kill the thread
	visualizer->stop();
}

/*
 * Scan backwards until a radio station is found.  If a scan thread is 
 * already running, then cancel the scan operation by setting threadRunning 
 * to FALSE.  This will make the thread leave its loop.
 */
void RadioWidget::scanBackwardToggled(int toggleState)
{
   if (toggleState == 0)
      threadRunning = FALSE;
   else
   {
      scanDirection = -1;
      QThread::start();     
   }
}


/*
 * Scan backwards until a radio station is found.  If a scan thread is 
 * already running, then cancel the scan operation by setting threadRunning 
 * to FALSE.  This will make the thread leave its loop.
 */
void RadioWidget::scanForwardToggled(int toggleState)
{
   if (toggleState == 0)
      threadRunning = FALSE;
   else
   {
      scanDirection = 1;
      QThread::start();
   }
}


/*
 * Start a continuous scan (non stop loop).  If this scan thread is 
 * already running, then cancel the scan operation by setting threadRunning 
 * to FALSE.  This will make the thread leave its loop.
 */
void RadioWidget::scanToggled(int toggleState)
{
   if (toggleState == 0)
      threadRunning = FALSE;
   else
   {
      scanDirection = 0;
      QThread::start();
   }
}


/*
 * Tune to a frequency 0.2 MHz less than the current.  If a scan thread is 
 * already running, then cancel the scan operation by setting threadRunning 
 * to FALSE.  This will make the thread leave its loop.
 */
void RadioWidget::previousClicked()
{
   if (threadRunning == TRUE)
   {
      threadRunning = FALSE;
      return;
   }
   setFrequency(frequency - 0.2);
}

/*
 * Tune to a frequency 0.2 MHz greater than the current.  If a scan thread is 
 * already running, then cancel the scan operation by setting threadRunning 
 * to FALSE.  This will make the thread leave its loop.
 */
void RadioWidget::nextClicked()
{
   if (threadRunning == TRUE)
   {
      threadRunning = FALSE;
      return;
   }
   setFrequency(frequency + 0.2);
}


/* 
 * A station was selected or the button was pressed simply to stop a scan 
 * operation in progress
 */
void RadioWidget::stationSelected(float freq)
{
   if (threadRunning == TRUE)
   {
      threadRunning = FALSE;
      QThread::msleep(300);
   }
   setFrequency(freq);
}


// tunes the radio to the requested frequency and emits freqChanged*()
void RadioWidget::setFrequency(float freq)
{
   unsigned long f;

   frequency = freq;
   f = (unsigned long)(freq*freq_factor);
   ioctl(fd, VIDIOCSFREQ, &f);

   emit freqChanged((double)freq);
}


// returns the radio signal strength
int RadioWidget::getSignalStrength()
{
   struct video_tuner tuner;
   tuner.tuner = 0;
   tuner.signal = 0;
   ioctl(fd, VIDIOCGTUNER , &tuner);
   return tuner.signal;
}


/* 
 * This thread performs a scan operation based on the scanDirection value.
 *
 * scanDirection = 0: scan forward continuously, pausing at each found station
 * scanDirection = 1: scan forward until a station is found
 * scanDirection = -1: scan backward until a station is found
 */
void RadioWidget::run()
{
   threadRunning = TRUE;

   int signal = 0;

   // loop while no station found or the mode is 'continuous scan'
   while ((signal <= 0) || (scanDirection == 0))
   {
      if (scanDirection >= 0)
      {
         frequency = frequency + 0.2;
         if (frequency > 107.9)
            frequency = 87.9;
      } else
      {
         frequency = frequency - 0.2;
         if (frequency < 87.9)
            frequency = 107.9;
      }
      
      setFrequency(frequency);
      
      // don't know why, but lcd must be told to repaint to show the freq.
      QThread::postEvent( lcd, new QPaintEvent( QRect(0, 0, 580, 300) ) );
      
      // check it thread cancel was requested
      if (threadRunning == FALSE) break;

      // pause is necessary for a correct reading of the signal strength
      QThread::msleep(200);  
      signal = getSignalStrength();
      
      // if in 'continuous scan' mode and station pause, stay here for 3 sec.
      if ((scanDirection == 0) && (signal > 0))
         QThread::sleep(3);
      
      // check again to see if thread cancel was requested
      if (threadRunning == FALSE) break;
   }

   // untoggle all the control buttons
   scan->untoggle();
   scanForward->untoggle();
   scanBackward->untoggle();

   threadRunning = FALSE;
}


/*
 * The Radio screen has been activated.  So unmute the tuner by setting the 
 * flags to 0 which clears the VIDEO_AUDIO_MUTE flag.
 */
void RadioWidget::activate()
{
   struct video_audio va;
   va.audio = 0;
   va.flags = 0;

   ioctl(fd, VIDIOCSAUDIO, &va);
}


/*
 * The Radio screen has been deactivated.  Mute the tuner so that other 
 * applications can play their sounds.  The code below sets the 
 * VIDEO_AUDIO_MUTE flag.
 */
void RadioWidget::deactivate()
{
   struct video_audio va;
   va.audio = 0;
   va.flags = VIDEO_AUDIO_MUTE;

   ioctl(fd, VIDIOCSAUDIO, &va);   
}









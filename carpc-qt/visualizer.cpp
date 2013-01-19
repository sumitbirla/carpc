#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/soundcard.h>
#include <qpainter.h>
#include <qpixmap.h>

#include "visualizer.h"


// The constructor does not do much other than starting the thread
VisualizerWidget::VisualizerWidget( QWidget *parent, const char *name )
: QWidget( parent, name )
{
   setBackgroundColor(Qt::green);
   threadRunning = false;
}

void VisualizerWidget::paintEvent(QPaintEvent *)
{
   QPainter qpainter;
   QPixmap pm(size());

   //qDebug("Inside paintEvent()");
   pm.fill(Qt::black);
   qpainter.begin(&pm);

   QRect r = rect();

   int width = r.right() / NUM_BUCKETS;
   int i, val;

   qpainter.setBrush(Qt::white);
   for (i = 0; i < NUM_BUCKETS; i++)
   { 
      val = (int)(out_spectraldata[i]*10.0);
            
      if (val > r.bottom())
         display_data[i] = r.bottom()-20;
      else if (display_data[i] > val)
         display_data[i] -= 5;
      else
         display_data[i] = val;
     
      qpainter.drawRect(i*width, 0, width, display_data[i]);
   }

   qpainter.end();

   bitBlt(this, 0, 0, &pm);

   //printf("%d \n", display_data[NUM_BUCKETS-1]);
   //printf("\n");
}

void VisualizerWidget::paint()
{
	QPainter qpainter;
   QPixmap pm(size());

   qDebug("Inside paint()");
   pm.fill(Qt::black);
   qpainter.begin(&pm);

   QRect r = rect();

   int width = r.right() / NUM_BUCKETS;
   int i, val;

   qpainter.setBrush(Qt::white);
   for (i = 0; i < NUM_BUCKETS; i++)
   { 
      val = (int)(out_spectraldata[i]*10.0);
            
      if (val > r.bottom())
         display_data[i] = r.bottom()-20;
      else if (display_data[i] > val)
         display_data[i] -= 5;
      else
         display_data[i] = val;
     
      qpainter.drawRect(i*width, 0, width, display_data[i]);
   }

   qpainter.end();

   bitBlt(this, 0, 0, &pm);
}


int VisualizerWidget::openDSP()
{
   int arg;       /* argument for ioctl calls */
   int status;
   int fd;

   /* open sound device */
   fd = open("/dev/dsp", O_RDWR);
   if (fd < 0)
   {
      perror("open of /dev/dsp failed");
      return fd;
   }

   /* get sampling parameters */
   arg = SAMPLE_SIZE;
   status = ioctl(fd, SOUND_PCM_WRITE_BITS, &arg);

   /* Audio channels (mono or stereo) */
   arg = 1;
   status = ioctl(fd, SOUND_PCM_WRITE_CHANNELS, &arg);

   /* sampling rate */
   arg = SAMPLE_RATE;
   status = ioctl(fd, SOUND_PCM_WRITE_RATE, &arg);

   return fd;
}


/*
 * This method runs continuously until the widget is destroyed. The loop is 
 * paused when the widget becomes hidden.  It is reawakened by the showEvent 
 * method which reopens /dev/dsp and calls mycond.wakeOne().
 */
void VisualizerWidget::run()
{
   int status;    /* return status of system calls */
   int i;
   int fd;        /* file descriptor of /dev/dsp */

   threadRunning = true;

   qDebug("About to call fft.Init()");
   fft.Init(NUM_SAMPLES, NUM_BUCKETS);
   qDebug("About to call openDSP()");
   fd = openDSP();

   while (TRUE)
   {
      if (!threadRunning) {
         qDebug("Exiting loop");
		 break;
      }

      status = read(fd, buf, sizeof(buf)); /* record some sound */
      if (status != sizeof(buf)) {
         qDebug("Error reading from /dev/dsp");
      }
      else
      {
         for (i = 0; i < NUM_SAMPLES; i++)
             in_wavedata[i] = (float)buf[i];

         fft.time_to_frequency_domain(in_wavedata, out_spectraldata);
		 //qDebug("About to call paintEvent()");    
		 
		 //QThread::postEvent(this, new QPaintEvent(new QRect()));
		 repaint(FALSE);
		 //paint();

         QThread::msleep(50);
      }
   }

   close(fd);

   fft.CleanUp();

   qDebug("Cleaned up FFT");
}


void VisualizerWidget::stop()
{
	threadRunning = false;
	wait();
}









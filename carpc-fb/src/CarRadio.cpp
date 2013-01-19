/*****************************************************************************
 *                                                                           *
 * Car PC User Interface                                                     *
 *                                                                           *
 * Copyright (C) 2003 Sumit Birla <sbirla@users.sourceforge.net>             *
 *                                                                           *
 *                                                                           *
 * This program is free software; you can redistribute it and/or modify      *
 * it under the terms of the GNU General Public License as published by      *
 * the Free Software Foundation; either version 2 of the License, or         *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU General Public License for more details.                              *
 *                                                                           *
 * You should have received a copy of the GNU General Public License         *
 * along with this program; if not, write to the Free Software               *
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA  *
 *                                                                           *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/videodev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "CarRadio.hpp"


/* eventually replace this to read in from a file */
const char * CarRadio::channels[] = { "89.7", "93.3", "94.9", "95.7",
"97.9","101.5","102.5","105.5",
"", ""};

/*
* The constructor creates the necesary fonts and initializes the radio 
* tuner.  The multiply factor for setting the tuner frequency is also 
* obtained after opening the radio device (/dev/radio0).
*/ 
CarRadio::CarRadio(CarApp *main, Logger *log):CarModule(main,log)
{
   logger->log(DEBUG, "CarRadio::CarRadio", "start");

   char str[128];
   struct video_tuner tuner;

   status_height = 30;
   item_width = width / 2;
   item_height = (height - status_height) / 5; 
   channel = -1;

   sprintf(str, "item_width=%d, item_height=%d", item_width, item_height);
   logger->log(DEBUG, "CarRadio::CarRadio", str);

   fd = open("/dev/radio0", O_TRUNC);
   if (fd < 0)
      logger->log(ERROR, "CarRadio::CarRadio", "Unable to open /dev/radio0");
   else {
      deactivated();  // Radio is unmuted on start, so, mute it
      tuner.tuner = 0;  
      if (ioctl(fd, VIDIOCGTUNER , &tuner) == 0)
         freq_factor = (tuner.flags&VIDEO_TUNER_LOW ? 16000.0 : 16.0);
   }

   logger->log(DEBUG, "CarRadio::CarRadio", "end");
}


/*
* The Radio screen has been surfaced.  So unmute the tuner by setting the 
* flags to 0 which clears the VIDEO_AUDIO_MUTE flag.
*/
void CarRadio::activated()
{
   logger->log(DEBUG, "CarRadio::activated", "start");

   struct video_audio va;
   va.audio = 0;
   va.flags = 0;

   if (ioctl(fd, VIDIOCSAUDIO, &va) < 0)
      logger->log(ERROR, "CarRadio::activated", "Unable to set volume");

   logger->log(DEBUG, "CarRadio::activated", "end");
}


/*
* The Radio screen has gone in the background.  Mute the tuner so that 
* other applications can play their sounds.  The code below sets the 
* VIDEO_AUDIO_MUTE flag.
*/
void CarRadio::deactivated()
{
   logger->log(DEBUG, "CarRadio::deactivated", "end");

   struct video_audio va;
   va.audio = 0;
   va.flags = VIDEO_AUDIO_MUTE;

   if (ioctl(fd, VIDIOCSAUDIO, &va) < 0)
      logger->log(ERROR, "CarRadio::deactivated", "Unable to mute");

   logger->log(DEBUG, "CarRadio::deactivated", "end");

}


/*
* Draw the screen to allow user to select a channel.
*/
void CarRadio::draw()
{
   logger->log(DEBUG, "CarRadio::draw", "start");

   int i, top, left, ret, color;
   int brect[8];
   char str[64];
   unsigned long freq;
   char *font = conf->get_value("font");

   /* If radio hardware was not found, try to open again */
   if (fd < 0) {

      draw_string(0, 0, width, height, gdTrueColor(250,250,250), 
                  font, 18, "Radio hardware not found");
      update();

      logger->log(DEBUG, "CarRadio::draw", "end");
      return;
   }

   /* draw the buttons */
   for (i=0; i < 10; i++) {

      top = item_height*(i%5);
      left = (i<5)?0:item_width;
      color = gdTrueColor(77, 96, 136);

      if (i == channel) {
         /* set the radio channel if changed */
         if (channel != prev_channel) {
            freq = (unsigned long)(atof(channels[i])*freq_factor);
            ret = ioctl(fd, VIDIOCSFREQ, &freq);
            sprintf(str, "Set frequency=%s, return=%d", channels[i], ret);  
            logger->log(INFORMATION, "CarRadio::draw", str);

            prev_channel = channel;
         }
         color = gdTrueColor(120, 130, 236);
      }

      gdImageFilledRectangle(img, left+1, top+1, left+item_width-2, 
         top+item_height-2, color);

      color = gdTrueColor(190, 190, 20);
      gdImageStringFT(img, &brect[0], color, font, 18, 0.0, 
         left + 10, top + 35, (char *)channels[i]);
   }

   // draw the status bar
   color = gdTrueColor(128,128,128);
   gdImageFilledRectangle(img, 1, height-30, width - 2, 
      height-2, color);

   update();

   logger->log(DEBUG, "CarRadio::draw", "end");
}


/*
* Highlight the selected channel based on the mouse coordinates.
*/
void CarRadio::mouse_pressed(int x, int y) 
{
   logger->log(DEBUG, "CarRadio::mouse_pressed", "start");

   int i, top, left;

   for (i=0; i < 10; i++) 
   {  
      top = (item_height + MARGIN)*(i%5) + MARGIN;
      left = (i<5)?MARGIN:item_width + 2*MARGIN;

      if ( (y > top) && ( y < top + item_height) &&
         (x > left) && (x < left + item_width)) 
      {
         channel = i;
         draw();  

         break;
      }
   }

   logger->log(DEBUG, "CarRadio::mouse_pressed", "end");
}


/*
* Move to the next channel
*/
void CarRadio::action_right() 
{
   logger->log(DEBUG, "CarRadio::action_right", "start");

   if (channel < 9)
      ++channel;

   logger->log(DEBUG, "CarRadio::action_right", "end");
}


/*
* Move to the previous channel
*/
void CarRadio::action_left()
{
   logger->log(DEBUG, "CarRadio::action_left", "start");

   if (channel > 0)
      --channel;

   logger->log(DEBUG, "CarRadio::action_left", "end");
}


/*
* The destructor closes the open device - /dev/radio0
*/
CarRadio::~CarRadio()
{
   logger->log(DEBUG, "CarRadio::~CarRadio", "start");

   close(fd);

   logger->log(DEBUG, "CarRadio::~CarRadio", "end");
}

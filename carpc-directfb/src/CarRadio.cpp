/*---------------------------------------------------------------------------*
 *                                                                           *
 *                               CarPC Software                              *
 *                                                                           *
 *                                                                           *
 *         (c) Copyright 2003 Sumit Birla (birla@tampabay.rr.com), and       *
 *                   Matthew Willis (mwilli88@tampabay.rr.com), and          *
 *                   John Egan (johne87@hotmail.com)                         *
 *                                                                           *
 *                                                                           *
 *   This work is protected by United States and International Copyright     *
 *   laws and contains certain trade secret information.  All use of this    *
 *   work is governed by the terms of agreements between Sumit Birla,        *
 *   Matthew Willis, John Egan and its licensees or potential licensees.     *
 *   Disclosure or disassembly of the contents of embodied programs or       *
 *   algorithms is prohibited.                                               *
 *                                                                           *
 *   All rights are reserved worldwide.                                      *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#include <directfb.h>
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
CarRadio::CarRadio(CarApp *main,Logger *logger):CarModule(main,logger)
{
   logger->log(DEBUG, "CarRadio::CarRadio", "start");

   int width, height;
   DFBFontDescription font_dsc;
   struct video_tuner tuner;
   
   font_dsc.flags = DFDESC_HEIGHT;
   font_dsc.height = 42;
   app->dfb->CreateFont(app->dfb, "decker.ttf", &font_dsc, &radio_font);   
  
   surface->GetSize(surface, &width, &height);
   
   item_width = (width - (MARGIN*3))/2;
   item_height = (height - 0 - (MARGIN*5))/5; 

   channel = -1;

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

   int i, top, left, ret;
   char str[64];
   unsigned long freq;
  
   /* draw the buttons */
   surface->SetFont(surface, radio_font);
   for (i=0; i < 10; i++) {
      
      top = (item_height + MARGIN)*(i%5) + MARGIN;
      left = (i<5)?MARGIN:item_width + 2*MARGIN;
      
      if (i == channel) {
         /* set the radio channel if changed */
         if (channel != prev_channel) {
            freq = (unsigned long)(atof(channels[i])*freq_factor);
            ret = ioctl(fd, VIDIOCSFREQ, &freq);
            sprintf(str, "Set frequency=%s, return code=%d", channels[i], ret);  
            logger->log(INFORMATION, "CarRadio::draw", str);
            
            prev_channel = channel;
         }
         surface->SetColor(surface, 60, 60, 140, 0xff);
      }
      else
         surface->SetColor(surface, 0x00, 0x22, 0x33, 0xff);
      surface->FillRectangle(surface, left, top, item_width, item_height);

      surface->SetColor(surface, 190, 190, 20, 0xff);
      surface->DrawString(surface, channels[i], -1, left + item_width/2, 
                          top + item_height/2 + 10, DSTF_CENTER);
   }
    
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
         app->draw_skeleton();
         app->draw_buttons(-1);
         draw();  
         surface->Flip(surface, NULL, (DFBSurfaceFlipFlags) 0);       
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

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

#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <usb.h>
#include <sys/ioctl.h>

#include "CarApp.hpp"
#include "CarModule.hpp"
#include "CarMenu.hpp"
#include "CarMP3.hpp"
#include "CarOBDII.hpp"
#include "CarRadio.hpp"
#include "CarGPS.hpp"
#include "VolumeControl.hpp"
#include "FrameBuffer.hpp"
#include "ConfigFile.hpp"
#include "TouchScreen.hpp"


#define TOUCHKIT_DOWN                   0x01
#define TOUCHKIT_POINT_TOUCH            0x81
#define TOUCHKIT_POINT_NOTOUCH          0x80

#define TOUCHKIT_GET_TOUCHED(dat)       ((((dat)[0]) & TOUCHKIT_DOWN) ? 1 : 0)
#define TOUCHKIT_GET_Y(dat)             (((dat)[3] << 7) | (dat)[4])
#define TOUCHKIT_GET_X(dat)             (((dat)[1] << 7) | (dat)[2])


int main(int argc, char **argv)
{
   // start the CarPC application
   CarApp app(argc, argv);
   app.run_event_loop();

   return 0;
}


CarApp::CarApp(int argc, char *argv[]) 
{
   logger = new Logger();

   // must read config file before loading any module
   conf = new ConfigFile("/etc/carpc.conf", logger);
   logger->set_log_level(atoi(conf->get_value("log_level")));

   logger->log(DEBUG, "CarApp::CarApp", "start");

   fb = new FrameBuffer(logger);
   button_height = fb->height / 6;
   button_width = button_height;  // buttons are square

   // set the client area where various modules will be drawn
   client_offset_x = button_width;
   client_offset_y = 0;
   client_width = fb->width - client_offset_x;
   client_height = fb->height - client_offset_y;

   // construct all modules. 
   sound = new VolumeControl(logger);
   carMenu = new CarMenu(this, logger);
   carRadio = new CarRadio(this, logger);
   carMp3 = new CarMP3(this, logger);
   carGps = new CarGPS(this, logger);
   carObdii = new CarOBDII(this, logger);
   touchScreen = new TouchScreen(logger);

   quit = FALSE;
   carDefault = new CarModule(this, logger);
   currentModule = carMenu;

   draw_buttons(-1);
   set_current_selection(MENU);
   draw_current_selection();

   // disable console blanking
   char ioctlarg[2];
	ioctlarg[0] = 10;	// powersave 
	ioctlarg[1] = 0;  // disable console balnking
	if (ioctl(0,TIOCLINUX,ioctlarg))
      logger->log(ERROR, "CarApp::CarApp", "Cannot disable console blanking");
   
   logger->log(DEBUG, "CarApp::CarApp", "end");
}


int CarApp::get_current_selection()
{
   return current_selection;
}


void CarApp::set_current_selection(int selection)
{
   logger->log(DEBUG, "CarApp::set_current_selection", "start");

   current_selection = selection;

   switch(current_selection)
   {
   case MENU:
      // must deactivate what was running previously
      currentModule->deactivated();
      currentModule = carMenu;
      break;

   case RADIO:
      currentModule = carRadio;
      break;

   case MP3:
      currentModule = carMp3;
      break;

   case GPS:
      currentModule = carGps;
      break;

   case OBDII:
      currentModule = carObdii;
      break;

   case SYSTEM:
      quit = TRUE;
      return;

   default:
      currentModule = carDefault;
      break;
   }

   currentModule->activated();
   currentModule->draw();

   logger->log(DEBUG, "CarApp::set_current_selection", "end");
}


void CarApp::draw_current_selection()
{
   logger->log(DEBUG, "CarApp::draw_current_selection", "start");

   currentModule->draw();

   logger->log(DEBUG, "CarApp::draw_current_selection", "end");
}


void CarApp::draw_buttons(int selection)
{
   logger->log(DEBUG, "CarApp::draw_buttons", "start");

   int i, top, col, blue;
   gdPoint points[3];
   int brect[8];
   int white = gdTrueColor(255,255,255);
   char *font = conf->get_value("font");

   col = gdTrueColor(64,64,198);
   blue = gdTrueColor(64,64,198);

   for(i=0; i<6; i++) 
   {  
      top = i * button_height;
      if (i == selection)
         col = gdTrueColor(100, 110, 216);  
      else
         col = gdTrueColor(57, 76, 116);

      /* special colors for the mute button) */
      if (sound->is_mute() && (i == MUTE) && (i != selection))
         col = gdTrueColor(200, 94, 94);
      else if (sound->is_mute() && (i == MUTE) && (i == selection))   
         col = gdTrueColor(255, 120, 120);

      gdImageFilledRectangle(fb->img, 1, top+1, button_width - 2, 
         top + button_height - 2, col);   

      if (i == MUTE)
      {
         gdImageStringFT(fb->img, &brect[0], white, font, 14, 0.0, 20, 45, 
            "Mute");
      }
      else if (i == UP) {
         col = gdTrueColor(180, 60, 60);
         points[0].x = MARGIN + (button_width / 2);
         points[0].y = top + 20;
         points[1].x = MARGIN + 20;
         points[1].y = top + button_height - 20;
         points[2].x = MARGIN + button_width - 20;
         points[2].y = top + button_height - 20;
         gdImageFilledPolygon(fb->img, points, 3, col);
         gdImagePolygon(fb->img, points, 3, 0);
      }	
      else if (i ==DOWN) {
         col = gdTrueColor(180, 60, 60);
         points[0].x = MARGIN + 20;
         points[0].y = top + 20;
         points[1].x = MARGIN + button_width - 20;
         points[1].y = top + 20;
         points[2].x = MARGIN + (button_width / 2);
         points[2].y = top + button_height - 20;
         gdImageFilledPolygon(fb->img, points, 3, col);
         gdImagePolygon(fb->img, points, 3, 0);
      }	
      else if (i == RIGHT) {
         col = gdTrueColor(100, 160, 100);
         points[0].x = MARGIN + 20;
         points[0].y = top + 20;
         points[1].x = MARGIN + button_width - 20;
         points[1].y = top + (button_height) / 2;
         points[2].x = MARGIN + 20;
         points[2].y = top + button_height - 20;
         gdImageFilledPolygon(fb->img, points, 3, col);
         gdImagePolygon(fb->img, points, 3, 0);
      }
      else if (i == LEFT) {
         col = gdTrueColor(100, 160, 100);
         points[0].x = MARGIN + button_width - 20;
         points[0].y = top + 20;
         points[1].x = MARGIN +  20;
         points[1].y = top + (button_height) / 2;
         points[2].x = MARGIN + button_width - 20;
         points[2].y = top + button_height - 20;
         gdImageFilledPolygon(fb->img, points, 3, col);
         gdImagePolygon(fb->img, points, 3, 0);
      }
      else if (i == MENU) 
      {
         gdImageStringFT(fb->img, &brect[0], white, font, 14, 0.0, 17, 445, 
            "Menu");
      }
   }

   fb->update(0, 0, button_width, fb->height-1);

   logger->log(DEBUG, "CarApp::draw_buttons", "end");
}


void CarApp::mouse_pressed(int x, int y)
{
   logger->log(DEBUG, "CarApp::mouse_pressed", "start");

   int i, top;
   top = MARGIN;

   for (i=0; i<=7; i++)
   {
      if (y > top && y < top+button_height)
      {
         draw_buttons(i);
         //draw_current_selection();

         return;
      }

      top += MARGIN + button_height;
   } 

   logger->log(DEBUG, "CarApp::mouse_pressed", "end");
}


void CarApp::mouse_released(int x, int y)
{
   logger->log(DEBUG, "CarApp::mouse_released", "start");

   int i, top;
   top = MARGIN;

   for (i=0; i<=7; i++)
   {
      if (y > top && y < top+button_height)
      {
         if (i == MENU)
            set_current_selection(MENU);
         else if (i == UP)
            sound->volume_up();
         else if (i == DOWN)
            sound->volume_down();
         else if (i == MUTE)
            sound->toggle_mute();
         else if (i == RIGHT)
            currentModule->action_right();
         else if (i == LEFT)
            currentModule->action_left();

         draw_buttons(-1);
         //draw_current_selection();      

         return;
      }
      top += MARGIN + button_height;
   } 

   logger->log(DEBUG, "CarApp::mouse_released", "end");
}


void CarApp::run_event_loop()
{
   logger->log(DEBUG, "CarApp::run_event_loop", "start");

   TouchData *pData;
   int prev_x, prev_y;

   touchScreen->start();

   while(quit == FALSE)
   {
      pData = touchScreen->dequeue();
      if (pData == NULL) {
         usleep(20000);  // yield CPU for 20ms
         continue;
      }

      if (pData->state == 1)
      {
         if (pData->x < button_width)
            mouse_pressed(pData->x, pData->y);
         else
            currentModule->mouse_pressed(pData->x, pData->y);

         prev_x = pData->x;
         prev_y = pData->y;

      } else {
         if (prev_x < button_width)
            mouse_released(prev_x, prev_y);
         else
            currentModule->mouse_released(prev_x, prev_y);  
      }

      free(pData);
   }

   logger->log(DEBUG, "CarApp::run_event_loop", "end");
}


CarApp::~CarApp()
{
   logger->log(DEBUG, "CarApp::~CarApp", "start/end");              

   touchScreen->stop();

   delete touchScreen;
   delete carDefault;
   delete carMenu;
   delete carRadio;
   delete carMp3;
   delete carObdii;
   delete carGps;
   delete sound;
   delete fb;
   delete conf;
   delete logger;

   sleep(3);
}


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

#include <stdio.h>	
#include <stdlib.h>	
#include <string.h>	

#include "CarMenu.hpp"

const char * CarMenu::menu[3][3] = { {"Radio", "mp3", "Photos"},
{"GPS", "OBDII", "Phone"},
{"Console", "Calibrate", "-"} }; 


CarMenu::CarMenu(CarApp *main, Logger *log):CarModule(main, log)
{
   logger->log(DEBUG, "CarMenu::CarMenu", "start");

   item_width = width /3;
   item_height = height / 3;

   logger->log(DEBUG, "CarMenu::CarMenu", "end");
}


/* draws the menu on the surface with the selection highlighted */
void CarMenu::draw(int i, int j) 
{
   logger->log(DEBUG, "CarMenu::draw(i,j)", "start");

   int top, left, color, white;
   char *font = conf->get_value("font");

   color = gdTrueColor(100, 230, 100);
   white = gdTrueColor(255,255,255);

   top = item_height * j;
   left = item_width * i; 

   gdImageFilledRectangle(img, left+1, top+1, left+item_width-2, 
      top+item_height-2, color);

   draw_string(left, top, item_width, item_height, white, font, 24, 
      (char *)menu[i][j]);

   update(left, top, item_width, item_height);
   //update();

   logger->log(DEBUG, "CarMenu::draw(i,j)", "end");
}


void CarMenu::activated()
{
   //system("play menu.wav &");
}


void CarMenu::draw()
{
   logger->log(DEBUG, "CarMenu::draw", "start");

   int x, y, top, left, green, white;
   char *font = conf->get_value("font");

   green = gdTrueColor(60, 140, 60);
   white = gdTrueColor(255,255,255);

   for (x = 0; x < 3; x++)
      for (y = 0; y < 3; y++)
      {
         top = item_height * y;
         left = item_width * x; 

         gdImageFilledRectangle(img, left+1, top+1, left+item_width-2, 
            top+item_height-2, green);

         draw_string(left, top, item_width, item_height, white, font, 24, 
            (char *)menu[x][y]);
      }

      update();

      logger->log(DEBUG, "CarMenu::draw", "start");
}


void CarMenu::mouse_pressed(int x, int y)
{
   logger->log(DEBUG, "CarMenu::mouse_pressed", "start");

   int i, j, top, left;
   char str[128];

   for (i = 0; i < 3; i++)
      for (j = 0; j < 3; j++)
      {
         top = item_height*j;
         left = item_width*i; 

         if ((x > left) && (x < left + item_width) && 
            (y > top) && (y < top + item_height))
         {
            sprintf(str, "selected (%d, %d)", i, j);
            logger->log(DEBUG, "CarMenu::mouse_pressed", str);
            draw(i,j);   

            return;         
         }
      }

      logger->log(DEBUG, "CarMenu::mouse_pressed", "end");
}


void CarMenu::mouse_released(int x, int y)
{
   logger->log(DEBUG, "CarMenu::mouse_released", "start");

   int i, j, top, left;

   for (i = 0; i < 3; i++)
      for (j = 0; j < 3; j++)
      {
         top = item_height*j;
         left = item_width*i; 

         if ((x > left) && (x < left + item_width) && 
            (y > top) && (y < top + item_height))
         {
            if (!strcmp(menu[i][j], "Blank")) 
               app->set_current_selection(BLANK);            
            else if (!strcmp(menu[i][j], "Radio")) 
               app->set_current_selection(RADIO);
            else if (!strcmp(menu[i][j], "mp3")) 
               app->set_current_selection(MP3);
            else if (!strcmp(menu[i][j], "Photos"))
               app->set_current_selection(PHOTOS);
            else if (!strcmp(menu[i][j], "Phone"))
               app->set_current_selection(PHONE);
            else if (!strcmp(menu[i][j], "GPS")) 
               app->set_current_selection(GPS);
            else if (!strcmp(menu[i][j], "OBDII")) 
               app->set_current_selection(OBDII);
            else if (!strcmp(menu[i][j], "Console"))
               app->set_current_selection(SYSTEM);
            else
               return;

            return;  
         }
      }

      logger->log(DEBUG, "CarMenu::mouse_released", "end");
}


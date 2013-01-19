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

#include "CarModule.hpp"


CarModule::CarModule(CarApp *main, Logger *log)
{
   logger = log;
   logger->log(DEBUG, "CarModule::CarModule", "start");

   app = main;
   fb = app->fb;
   conf = app->conf;
   width = app->client_width;
   height = app->client_height;
   img = gdImageCreateTrueColor(width, height);

   logger->log(DEBUG, "CarModule::CarModule", "end");
}


void CarModule::draw() {

   int color;

   color = gdTrueColor(0, 0, 0);
   gdImageFilledRectangle(img, 0, 0, width, height, color);

   color = gdTrueColor(250, 250, 250);
   draw_string(0, 0, width, height, color, conf->get_value("font"), 18, "Not implemented");

   update();
}


void CarModule::update()
{
   logger->log(DEBUG, "CarModule::update", "start");

   gdImageCopy(fb->img, img, app->client_offset_x, app->client_offset_y, 
      0, 0, width, height);
   fb->update();

   logger->log(DEBUG, "CarModule::update", "end");
}

void CarModule::update(int x, int y, int w, int h)
{
   logger->log(DEBUG, "CarModule::update2", "start");

   gdImageCopy(fb->img, img, app->client_offset_x + x, 
      app->client_offset_y + y, x, y, w, h);
   fb->update(app->client_offset_x + x, app->client_offset_y + y, w, h);

   logger->log(DEBUG, "CarModule::update2", "end");
}

/**
* Draws a strings centered in the rectangle specified by x, y, w, and h
*/
void CarModule::draw_string(int x, int y, int w, int h, int col,
                            char *font, int size, char *str)
{
   int brect[8];

   gdImageStringFT(NULL, &brect[0], col, font, size, 0.0, 0, 0, str);
   gdImageStringFT(img, &brect[0], col, font, size, 0.0, 
      x + (w - brect[2] - brect[0])/2, 
      y + (h - brect[1] - brect[7])/2, 
      str);
}


CarModule::~CarModule()
{
   logger->log(DEBUG, "CarModule::~CarModule", "start");

   gdImageDestroy(img);

   logger->log(DEBUG, "CarModule::~CarModule", "end");
}






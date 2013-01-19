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
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include "CarOBDII.hpp"


CarOBDII::CarOBDII(CarApp *main, Logger *log):CarModule(main,log)
{
   logger->log(DEBUG, "CarOBDII::CarOBDII", "start");

   logger->log(DEBUG, "CarOBDII::CarOBDII", "end");
}


/**
* Draw the obdii GUI.
*/
void CarOBDII::draw()
{
   logger->log(DEBUG, "CarOBDII::draw", "start");

   int color;

   color = gdTrueColor(0, 0, 0);
   gdImageFilledRectangle(img, 0, 0, width, height, color);

   color = gdTrueColor(250, 250, 250);
   draw_string(0, 0, width, height, color, conf->get_value("font"), 18, "Not implemented");

   update();

   logger->log(DEBUG, "CarOBDII::end", "start");
}


void CarOBDII::mouse_pressed(int x, int y) 
{
}


void CarOBDII::mouse_released(int x, int y) 
{
}


void CarOBDII::action_right() 
{
}


void CarOBDII::action_left()
{
}


CarOBDII::~CarOBDII()
{
   logger->log(DEBUG, "CarOBDII::~CarOBDII", "start");

   logger->log(DEBUG, "CarOBDII::~CarOBDII", "end");
}

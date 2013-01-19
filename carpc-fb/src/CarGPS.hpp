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

#ifndef _CAR_GPS
#define _CAR_GPS

#include "CarApp.hpp"
#include "CarModule.hpp"
#include "GPSSensor.hpp"

#define WIDTH           568
#define HEIGHT          416 
#define SENSOR_READOUT  1
#define MAP             2

#include <pthread.h>


class CarGPS: public CarModule
{
public:
   CarGPS(CarApp *main, Logger *log);
   ~CarGPS();
   void draw();
   void draw_readout(struct gpf_data *data);
   void draw_map(struct gpf_data *data);
   void activated();
   void deactivated();
   void action_right();
   void action_left();
   void run_monitor_loop();

private:
   GPSSensor   *sensor;
   pthread_t   threadID;
   int         display_type;
   gdImagePtr  graphic;
};

#endif



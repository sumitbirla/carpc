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

#ifndef _CAR_RADIO
#define _CAR_RADIO

#include "CarApp.hpp"
#include "CarModule.hpp"

class CarRadio: public CarModule {
private:
   int item_width, item_height, status_height;
   int prev_channel, channel;
   int fd;
   float freq_factor;
   static const char * channels[];

public:
   CarRadio(CarApp *main, Logger *log);
   ~CarRadio();
   void activated();
   void deactivated();
   void draw();
   void mouse_pressed(int x, int y);
   void action_right();
   void action_left();
};

#endif


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

#ifndef _CAR_MENU
#define _CAR_MENU

#include "CarApp.hpp"
#include "CarModule.hpp"

#define MENU_ITEM_WIDTH  (SCREEN_WIDTH - BUTTON_WIDTH - (MARGIN*5))/3
#define MENU_ITEM_HEIGHT (SCREEN_HEIGHT - 60 - (MARGIN*4))/3

#define BLANK           101
#define RADIO           102
#define MP3             103
#define PHOTOS          104
#define GPS             105
#define OBDII           106
#define SYSTEM          107
#define PHONE           108


class CarMenu: public CarModule {
private:
   int item_width, item_height;
   static const char *menu[3][3];

public:
   CarMenu(CarApp *main, Logger *log);
   void draw();
   void activated();
   void mouse_pressed(int x, int y);
   void mouse_released(int x, int y);

private:
   void draw(int i, int j); 
};

#endif


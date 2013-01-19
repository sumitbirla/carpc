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

#ifndef _CAR_MODULE
#define _CAR_MODULE

#include "CarApp.hpp"
#include "ConfigFile.hpp"
#include "Logger.hpp"
#include "FrameBuffer.hpp"
#include "gd.h"


class CarModule {
public:
   CarModule(CarApp *main, Logger *log);
   ~CarModule();
   virtual void draw();
   virtual void mouse_pressed(int x, int y) {};
   virtual void mouse_released(int x, int y) {};
   virtual void action_right() {};
   virtual void action_left() {};
   virtual void activated() {};
   virtual void deactivated() {};
   virtual int get_status() { return INACTIVE; }

protected:
   int bActive;
   int width;
   int height;
   gdImagePtr img;
   CarApp *app;
   ConfigFile *conf;
   Logger *logger;

private:
   FrameBuffer *fb;

protected:
    void update();
    void update(int x, int y, int w, int h);
    void draw_string(int x, int y, int w, int h, int col,
                     char *font, int size, char *str);
};

#endif


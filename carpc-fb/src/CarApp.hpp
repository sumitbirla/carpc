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
 *                                                                            *
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

#ifndef _CAR_APP
#define _CAR_APP

#define MARGIN           2

/* left column button constants */
#define MUTE            0
#define UP              1
#define DOWN            2
#define RIGHT           3
#define LEFT            4
#define MENU            5
#define QUIT            6

/* module status codes */
#define INACTIVE        0
#define ACTIVE          1
//#define ERROR           2

/* Global booleans for readibility */
#define TRUE            1
#define FALSE           0

class CarApp {
public:
   class FrameBuffer *fb;
   class ConfigFile *conf;
   int client_offset_x;
   int client_offset_y;
   int client_width;
   int client_height;
   int button_width, button_height;

private:
   int current_selection;
   int mouse_x, mouse_y;
   int quit;
   
   class Logger    *logger;
   class CarModule *currentModule;
   class CarModule *carDefault;
   class CarMenu   *carMenu;
   class CarRadio  *carRadio;
   class CarMP3    *carMp3;
   class CarOBDII  *carObdii;
   class CarGPS    *carGps;
   class VolumeControl  *sound;
   class TouchScreen    *touchScreen;
   
public:
   CarApp::CarApp(int argc, char *argv[]);
   CarApp::~CarApp();
   void run_event_loop();
   void draw_buttons(int selection);
   void set_current_selection(int selection);
   int get_current_selection();
   void draw_current_selection();

private:
   void mouse_pressed(int x, int y);
   void mouse_released(int x, int y);
};

#endif

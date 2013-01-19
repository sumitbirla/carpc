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

#ifndef _CAR_MENU
#define _CAR_MENU

#include "CarApp.hpp"
#include "CarModule.hpp"

#define MENU_ITEM_WIDTH  (SCREEN_WIDTH - BUTTON_WIDTH - (MARGIN*5))/3
#define MENU_ITEM_HEIGHT (SCREEN_HEIGHT - 60 - (MARGIN*4))/3

#define BLANK           101
#define RADIO           102
#define MP3             103
#define VIDEO           104
#define GPS             105
#define OBDII           106
#define SYSTEM          107


class CarMenu: public CarModule {
private:
   int item_width, item_height;
   static const char *menu[3][3];
   IDirectFBFont *menu_font;  

public:
   CarMenu(CarApp *main, Logger *log);
   void draw();
   void mouse_pressed(int x, int y);
   void mouse_released(int x, int y);

private:
   void draw(int i, int j); 
};

#endif


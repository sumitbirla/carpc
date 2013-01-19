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

#ifndef _CAR_RADIO
#define _CAR_RADIO

#include "CarApp.hpp"
#include "CarModule.hpp"
 
class CarRadio: public CarModule {
private:
   int item_width, item_height;
   int prev_channel, channel;
   int fd;
   float freq_factor;
   IDirectFBFont *radio_font;
   static const char * channels[];
     
public:
   CarRadio(CarApp *main, Logger *logger);
   ~CarRadio();
   void activated();
   void deactivated();
   void draw();
   void mouse_pressed(int x, int y);
   void action_right();
   void action_left();
};

#endif


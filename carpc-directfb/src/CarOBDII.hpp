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

#ifndef _CAR_OBDII
#define _CAR_OBDII

#include "CarApp.hpp"
#include "CarModule.hpp"

class CarOBDII: public CarModule {
private:
   IDirectFBFont *obdii_font;
   char     speed[4];
   char     speed_display[9];
   char     units[6];
   char     rpm[6];
   int      isBrit;
   int      isObdiiRunning;
   char     units_brit[6];
   char     units_metric[6];
   //CarOBDII *parent_carObdii, *tgt_carObdii;
  
public:
   pthread_t obdii_interface_thread;
   CarOBDII(CarApp *main, Logger *logger);
   ~CarOBDII();
   void draw();
   void mouse_pressed(int x, int y);
   void mouse_released(int x, int y);
   void action_right();
   void action_left();
   void start_obdii_interface();
   void request_ecu_data();
   void wakeup_ecu(Logger *logger);
   //   void process();
   //void *poll_ecu(void *tgt_carObdii);
};

#endif


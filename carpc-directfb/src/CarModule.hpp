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

#ifndef _CAR_MODULE
#define _CAR_MODULE

#include "CarApp.hpp"
#include "Logger.hpp"

class CarModule {
public:
   CarModule(CarApp *main, Logger *logger);
   virtual void draw();
   virtual void mouse_pressed(int x, int y) {};
   virtual void mouse_released(int x, int y) {};
   virtual void action_right() {};
   virtual void action_left() {};
   virtual void activated() {};
   virtual void deactivated() {};
   virtual int get_status() { return INACTIVE; }

protected:
   IDirectFBSurface *surface;
   CarApp *app;
   Logger *logger;

private:
   IDirectFBFont *font;
};

#endif


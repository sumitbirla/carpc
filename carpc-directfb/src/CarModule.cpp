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

#include <directfb.h>

#include "CarModule.hpp"


CarModule::CarModule(CarApp *main, Logger *log)
{
   logger = log;

   logger->log(DEBUG, "CarModule::CarModule", "start");

   app = main;
   
   surface = app->client_surface;

   DFBFontDescription font_dsc;

   font_dsc.flags = DFDESC_HEIGHT;
   font_dsc.height = 36;
   app->dfb->CreateFont(app->dfb, "decker.ttf", &font_dsc, &font);

   logger->log(DEBUG, "CarModule::CarModule", "end");
}


void CarModule::draw()
{
   logger->log(DEBUG, "CarModule::draw", "start");

   surface->SetFont(surface, font);
   surface->SetColor(surface, 190, 190, 20, 0xff);
   surface->DrawString(surface, "Under Development", -1, 302, 50,DSTF_CENTER);

   logger->log(DEBUG, "CarModule::draw", "end");
}

/**
* Non-drawing related processing.
*/
//void CarModule::process()
//{
//    fprintf(stdout, "CarModule::process : Start \n");
//    fprintf(stdout, "CarModule::process : End \n");
//}
   


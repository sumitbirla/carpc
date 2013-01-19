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

#include <unistd.h>
#include <time.h>
#include <directfb.h>
#include <stdlib.h>
#include <stdio.h>

#include "CarModule.hpp"
#include "CarMenu.hpp"
#include "CarMP3.hpp"
#include "CarOBDII.hpp"
#include "CarRadio.hpp"
#include "CarGPS.hpp"
#include "VolumeControl.hpp"
#include "Logger.hpp"

                       
int main(int argc, char **argv)
{
   CarApp app(argc, argv);
   app.run_event_loop();
   return 0;
}


CarApp::CarApp(int argc, char *argv[]) 
{
   DFBSurfaceDescription dsc;
   DFBFontDescription font_dsc;
   IDirectFBImageProvider *provider;   
   DFBRectangle client_rect = {2*MARGIN + BUTTON_WIDTH, MARGIN, 
                               SCREEN_WIDTH - (2*MARGIN + BUTTON_WIDTH), 
                               SCREEN_HEIGHT - 2*MARGIN - 60};

   DirectFBInit(&argc, &argv);
   DirectFBCreate(&dfb);

   dfb->GetDisplayLayer( dfb, DLID_PRIMARY, &layer );

//   dfb->SetCooperativeLevel(dfb, DFSCL_NORMAL);
   dsc.flags = DSDESC_CAPS;
   dsc.caps  = (DFBSurfaceCapabilities) (DSCAPS_PRIMARY | DSCAPS_FLIPPING | DSCAPS_SYSTEMONLY);
   dfb->CreateSurface(dfb, &dsc, &primary);
   primary->GetSubSurface(primary, &client_rect, &client_surface);

   dfb->CreateImageProvider(dfb, "splash.png", &provider);
   provider->GetSurfaceDescription(provider, &dsc);
   dfb->CreateSurface(dfb, &dsc, &background);
   provider->RenderTo(provider, background, NULL);
   provider->Release(provider);

   /* Create the fonts */
   font_dsc.flags = DFDESC_HEIGHT;
   font_dsc.height = 18;
   dfb->CreateFont(dfb, "decker.ttf", &font_dsc, &button_font);

   /* Construct all modules. */
   sound = new VolumeControl();
   logger = new Logger();
   logger->set_log_level(ERROR);
   carDefault = new CarModule(this, logger);
   carMenu = new CarMenu(this, logger);
   carRadio = new CarRadio(this, logger);
   carMp3 = new CarMP3(this, logger);
   carGps = new CarGPS(this, logger);
   carObdii = new CarOBDII(this, logger);
   carObdii->start_obdii_interface();           // Start the obdii interface thread.

   draw_skeleton();
   draw_buttons(-1);
   set_current_selection(MENU);
   draw_current_selection();
   primary->Flip(primary, NULL, (DFBSurfaceFlipFlags)0);

   quit = 0;
}


void CarApp::draw_skeleton() 
{
   logger->log(DEBUG, "CarApp::draw_skeleton", "start");

   time_t now;
   struct tm local_time;
   char str[64];

   /* blank out the background */
   primary->SetColor(primary, 0x00, 0x00, 0x00, 0xff);
   primary->FillRectangle(primary, 0, 0, 640, 480);

   /* draw the status bar */
   primary->SetColor(primary, 90, 90, 90, 0xff);
   primary->FillRectangle(primary, 72, 420, 568, 60);
   now = time(0);
   local_time = *localtime(&now);
   strftime(str, sizeof(str), "%I:%M %P", &local_time);
   primary->SetColor(primary, 0xff, 0xff, 0x00, 0xff);
   primary->SetFont(primary, button_font);
   primary->DrawString(primary, str, -1, 550, 470, DSTF_LEFT);
   sprintf(str, "Volume: %d %%", sound->get_volume());
   primary->DrawString(primary, str, -1, BUTTON_WIDTH + 2*MARGIN + 10, 470, DSTF_LEFT);

   logger->log(DEBUG, "CarApp::draw_skeleton", "end");
}


int CarApp::get_current_selection()
{
    return current_selection;
}


void CarApp::set_current_selection(int selection)
{
   logger->log(DEBUG, "CarApp::set_current_selection", "Start");

   current_selection = selection;
   
   switch(current_selection)
   {
   case MENU:
      currentModule = carMenu;
      break;

   case RADIO:
      currentModule = carRadio;
      break;
   
   case MP3:
      currentModule = carMp3;
      break;

   case GPS:
      currentModule = carGps;
      break;

   case OBDII:
      currentModule = carObdii;
//      carObdii->process();
      break;
	
   default:
      currentModule = carDefault;
      break;
   }
         
   logger->log(DEBUG, "CarApp::set_current_selection", "End");
}


void CarApp::draw_current_selection()
{
   logger->log(DEBUG, "CarApp::draw_current_selection", "Start");

   currentModule->draw();
      
   logger->log(DEBUG, "CarApp::draw_current_selection", "End");
}


void CarApp::draw_buttons(int selection)
{
   logger->log(DEBUG, "CarApp::draw_buttons", "Start");

   int i, top;
   
   top = MARGIN;
   primary->SetFont(primary, button_font); 
   for(i=0; i<=7; i++) 
   {  
      if (i == selection)
         primary->SetColor(primary, 100, 110, 216, 0xff);  
      else
         primary->SetColor(primary, 57, 76, 116, 0xff);
      
      /* special colors for the mute button) */
      if (sound->is_mute() && (i == MUTE) && (i != selection))
         primary->SetColor(primary, 128, 64, 64, 0xff);
      else if (sound->is_mute() && (i == MUTE) && (i == selection))   
         primary->SetColor(primary, 192, 90, 90, 0xff);
         
      primary->FillRectangle(primary, MARGIN, top, BUTTON_WIDTH, BUTTON_HEIGHT);
      
      if (i == MUTE)
      {
         primary->SetColor(primary, 180, 180, 180, 0xff);
		  primary->DrawString(primary, "Mute", -1, (BUTTON_WIDTH/2)+2, 
                           top + (BUTTON_HEIGHT/2) + 5, DSTF_CENTER);
      }
	  else if (i == UP) {
		  primary->SetColor(primary, 180, 60, 60, 0xff);
		  primary->FillTriangle(primary,
							MARGIN+(BUTTON_WIDTH/2), top+20,
							MARGIN+20, top+BUTTON_HEIGHT-20,
							MARGIN+BUTTON_WIDTH-20, top+BUTTON_HEIGHT-20);
	  }	
	  else if (i ==DOWN) {
		  primary->SetColor(primary, 180, 60, 60, 0xff);
		  primary->FillTriangle(primary,
							MARGIN+20, top+20,
							MARGIN+BUTTON_WIDTH-20, top+20,
							MARGIN+(BUTTON_WIDTH/2), top+BUTTON_HEIGHT-20);
	  }	
	  else if (i == RIGHT) {
		  primary->SetColor(primary, 100, 160, 100, 0xff);
		  primary->FillTriangle(primary,
							MARGIN+20, top+20,
							MARGIN+BUTTON_WIDTH-20, top+(BUTTON_HEIGHT/2),
							MARGIN+20, top+BUTTON_HEIGHT-20);
	  }
	  else if (i == LEFT) {
		  primary->SetColor(primary, 100, 160, 100, 0xff);
		  primary->FillTriangle(primary,
							MARGIN+BUTTON_WIDTH-20, top+20,
							MARGIN+20, top+(BUTTON_HEIGHT/2),
							MARGIN+BUTTON_WIDTH-20, top+BUTTON_HEIGHT-20);
	  }
      else if (i == MENU) {
		  primary->SetColor(primary, 180, 180, 180, 0xff);
		  primary->DrawString(primary, "Menu", -1, (BUTTON_WIDTH/2)+2, 
                           top + (BUTTON_HEIGHT/2) + 5, DSTF_CENTER);
	  }

	  else {
		  primary->SetColor(primary, 180, 180, 180, 0xff);
		  primary->DrawString(primary, "Quit", -1, (BUTTON_WIDTH/2)+2, 
                           top + (BUTTON_HEIGHT/2) + 5, DSTF_CENTER);
	  }
          
      top += MARGIN + BUTTON_HEIGHT;
   }

   logger->log(DEBUG, "CarApp::draw_buttons", "End");
}


void CarApp::mouse_pressed(int x, int y)
{
   logger->log(DEBUG, "CarApp::mouse_pressed", "Start");

   int i, top;

   top = MARGIN;
   primary->SetFont(primary, button_font); 

   for (i=0; i<=7; i++)
   {
      if (y > top && y < top+BUTTON_HEIGHT)
      {
         draw_skeleton();
         draw_buttons(i);
         draw_current_selection();
         primary->Flip(primary, NULL, (DFBSurfaceFlipFlags)0); 
         
         return;
      }

      top += MARGIN + BUTTON_HEIGHT;
   } 
   
   logger->log(DEBUG, "CarApp::mouse_pressed", "End");
}


void CarApp::mouse_released(int x, int y)
{
   logger->log(DEBUG, "CarApp::mouse_released", "Start");

   int i, top;

   top = MARGIN;
   primary->SetFont(primary, button_font); 

   for (i=0; i<=7; i++)
   {
      if (y > top && y < top+BUTTON_HEIGHT)
      {
         if (i == QUIT) {
            quit = 1;
            return;
         }
         else if (i == MENU)
            set_current_selection(MENU);
         else if (i == UP)
            sound->volume_up();
         else if (i == DOWN)
            sound->volume_down();
         else if (i == MUTE)
            sound->toggle_mute();
         else if (i == RIGHT)
            currentModule->action_right();
         else if (i == LEFT)
            currentModule->action_left();
         draw_skeleton();
         draw_buttons(-1);
         draw_current_selection();      
         primary->Flip(primary, NULL, (DFBSurfaceFlipFlags)0);

         return;
      }
      top += MARGIN + BUTTON_HEIGHT;
   } 
   
   logger->log(DEBUG, "CarApp::mouse_released", "End");
}


void CarApp::run_event_loop()
{
   logger->log(DEBUG, "CarApp::run_event_loop", "Start");

   IDirectFBInputDevice *mouse;
   IDirectFBEventBuffer *buffer;

   dfb->GetInputDevice(dfb, DIDID_MOUSE, &mouse);
   mouse->CreateEventBuffer(mouse, &buffer);

   while (!quit)
   {
      DFBInputEvent event;
      buffer->WaitForEvent(buffer);

      while (buffer->GetEvent(buffer, DFB_EVENT(&event)) == DFB_OK)
      {
         if ((event.type != DIET_BUTTONPRESS) && (event.type != DIET_BUTTONRELEASE))
            continue;

         layer->GetCursorPosition(layer, &mouse_x, &mouse_y);
         //fprintf(stderr, "x = %d, y = %d \n", mouse_x, mouse_y);

         if (mouse_x < MARGIN + BUTTON_WIDTH)
         {
            if (event.type == DIET_BUTTONPRESS)
               mouse_pressed(mouse_x, mouse_y);
            else
               mouse_released(mouse_x, mouse_y);
         } 
         else {
            if (event.type == DIET_BUTTONPRESS)
               currentModule->mouse_pressed(mouse_x - 2*MARGIN - BUTTON_WIDTH, mouse_y - MARGIN);
            else
               currentModule->mouse_released(mouse_x - 2*MARGIN - BUTTON_WIDTH, mouse_y - MARGIN);              
         }  
      }
   }

   buffer->Release(buffer);
   mouse->Release(mouse); 

   logger->log(DEBUG, "CarApp::run_event_loop", "End");
}


CarApp::~CarApp()
{
   logger->log(DEBUG, "CarApp::~CarApp", "Start");              

   primary->Release(primary);
   dfb->Release(dfb);

   delete carDefault;
   delete carMenu;
   delete carRadio;
   delete carMp3;
   delete carObdii;
   delete carGps;
   delete sound;
   delete logger;

   sleep(1);

   logger->log(DEBUG, "CarApp::draw_buttons", "End");
}


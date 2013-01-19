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

#include <string.h>
#include <directfb.h>

#include "CarMenu.hpp"

const char * CarMenu::menu[3][3] = { {"Radio", "mp3", "TV"},
                        {"GPS", "OBDII", "Wireless"},
                        {"Blank", "System", "-"} }; 
                     

CarMenu::CarMenu(CarApp *main, Logger *logger):CarModule(main,logger)
{
   logger->log(DEBUG, "CarMenu::CarMenu", "start");

   int width, height;
   DFBFontDescription font_dsc;
   
   font_dsc.flags = DFDESC_HEIGHT;
   font_dsc.height = 34;
   app->dfb->CreateFont(app->dfb, "decker.ttf", &font_dsc, &menu_font);     
   
   surface->GetSize(surface, &width, &height);
   
   item_width = (width - (MARGIN*4))/3;
   item_height = (height - (MARGIN*4))/3;

   logger->log(DEBUG, "CarMenu::CarMenu", "end");
}


/* draws the menu on the surface with the selection highlighted */
void CarMenu::draw(int i, int j) 
{
   logger->log(DEBUG, "CarMenu::draw(i,j)", "start");

   int x, y, top, left;
   
   surface->SetFont(surface, menu_font);
  
   for (x = 0; x < 3; x++)
      for (y = 0; y < 3; y++)
      {
         top = MARGIN*(x+1) + item_height*x;
         left = 1 + MARGIN*(y+1) + item_width*y; 
         
         if ((x == i) && (y == j))
            surface->SetColor(surface, 100, 110, 216, 0xff);
         else
            surface->SetColor(surface, 60, 60, 140, 0xff);
         surface->FillRectangle(surface, left, top, item_width-1, item_height-1);
      
         surface->SetColor(surface, 190, 190, 20, 0xff);
         surface->DrawString(surface, menu[x][y], -1, left+(item_width/2), 
                              top + (item_height/2) + 10, DSTF_CENTER);
      }

   logger->log(DEBUG, "CarMenu::draw(i,j)", "end");
}


void CarMenu::draw()
{
   logger->log(DEBUG, "CarMenu::draw", "start");

   draw(-1,-1);

   logger->log(DEBUG, "CarMenu::draw", "start");
}


void CarMenu::mouse_pressed(int x, int y)
{
   logger->log(DEBUG, "CarMenu::mouse_pressed", "start");

   int i, j, top, left;
   
   for (i = 0; i < 3; i++)
      for (j = 0; j < 3; j++)
      {
         top = MARGIN*(i+1) + item_height*i;
         left = 1 + MARGIN*(j+1) + item_width*j; 
         
         if ((x > left) && (x < left + item_width) && 
             (y > top) && (y < top + item_height))
         {
            app->draw_skeleton();
            app->draw_buttons(-1);
            draw(i,j);   
            surface->Flip(surface, NULL, (DFBSurfaceFlipFlags)0);

            logger->log(DEBUG, "CarMenu::CarMenu", "end");
            return;         
         }
      }

   logger->log(DEBUG, "CarMenu::CarMenu", "end");
}


void CarMenu::mouse_released(int x, int y)
{
   logger->log(DEBUG, "CarMenu::mouse_released", "start");

   int i, j, top, left;
      
   for (i = 0; i < 3; i++)
      for (j = 0; j < 3; j++)
      {
         top = MARGIN*(i+1) + item_height*i;
         left = 1 + MARGIN*(j+1) + item_width*j; 
         
         if ((x > left) && (x < left + item_width) && 
             (y > top) && (y < top + item_height))
         {
            
            app->draw_skeleton();
            app->draw_buttons(-1);

            if (!strcmp(menu[i][j], "Blank")) 
               app->set_current_selection(BLANK);            
            else if (!strcmp(menu[i][j], "Radio")) 
               app->set_current_selection(RADIO);
            else if (!strcmp(menu[i][j], "mp3")) 
               app->set_current_selection(MP3);
            else if (!strcmp(menu[i][j], "TV"))
               app->set_current_selection(VIDEO);
            else if (!strcmp(menu[i][j], "GPS")) 
               app->set_current_selection(GPS);
            else if (!strcmp(menu[i][j], "OBDII")) 
               app->set_current_selection(OBDII);
            else if (!strcmp(menu[i][j], "System"))
               app->set_current_selection(SYSTEM);
            else
               return;

            //else
            //   surface->DrawString(surface, "Under Development", -1, 290, 50,DSTF_CENTER);
            
            app->draw_current_selection();
            surface->Flip(surface, NULL, (DFBSurfaceFlipFlags)0);

            return;  
         }
      }

   logger->log(DEBUG, "CarMenu::mouse_released", "end");
}


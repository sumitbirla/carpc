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
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <id3.h>

#include "CarMP3.hpp"


CarMP3::CarMP3(CarApp *main, Logger *logger):CarModule(main,logger)
{
   logger->log(DEBUG, "CarMP3::CarMP3", "start");

   int width, height;
   DFBFontDescription font_dsc;
   DIR *dir;
   struct dirent *entry;

   page_num = 0;
   num_songs = 0;
   cur_song = -1;
   head = NULL;
   strcpy(music_dir, "/home/sumit/music");
   
   font_dsc.flags = DFDESC_HEIGHT;
   font_dsc.height = 32;
   app->dfb->CreateFont(app->dfb, "decker.ttf", &font_dsc, &font_title);     
   font_dsc.height = 18;
   app->dfb->CreateFont(app->dfb, "decker.ttf", &font_dsc, &font_artist);

   surface->GetSize(surface, &width, &height);
   
   item_width = (width - (MARGIN*3))/2;
   item_height = (height - 0 - (MARGIN*5))/5; 
   
   if ((dir = opendir(music_dir)) == NULL)
   {
      logger->log(ERROR, "CarMP3::CarMP3", "Unable to open MP3 directory");
      return;
   }

   while ((entry = readdir(dir)) != NULL)
   {
      if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
         continue;
         
      ptr = (MP3File *)malloc(sizeof(MP3File));
      strcpy(ptr->name, entry->d_name);
      ptr->next = NULL;
      if (head == NULL) {
         head = ptr;
      } else {
         cur->next = ptr;  
      }
      cur = ptr;
      ++num_songs;

      read_id3tag(ptr);
   }

   closedir(dir);
   
   logger->log(DEBUG, "CarMP3::CarMP3", "end");
}


void CarMP3::activated()
{
   logger->log(DEBUG, "CarMP3::activated", "start");

   logger->log(DEBUG, "CarMP3::activated", "end");
}


void CarMP3::deactivated()
{
   logger->log(DEBUG, "CarMP3::deactivated", "start");

   system("killall mpg123");

   logger->log(DEBUG, "CarMP3::deactivated", "end");
}


void CarMP3::draw()
{
   logger->log(DEBUG, "CarMP3::draw", "start");

   draw(cur_song - 10*page_num);

   logger->log(DEBUG, "CarMP3::draw", "end");
}


void CarMP3::draw(int selection)
{
   logger->log(DEBUG, "CarMP3::draw(i)", "start");

   int i, top, left;
   
   /* move the pointer ahead to the beginning of the current page */
   i=0;
   cur = head;
   while (cur && (i < (page_num*10)))
   {
      cur = cur->next;
      ++i;
   }
   
   /* draw the buttons */
   for (i=0; i < 10; i++) {
      
      top = (item_height + MARGIN)*(i%5) + MARGIN;
      left = (i<5)?MARGIN:item_width + 2*MARGIN;
      
      if (i == selection)          
         surface->SetColor(surface, 60, 60, 140, 0xff);
      else
         surface->SetColor(surface, 0x00, 0x22, 0x33, 0xff);
      surface->FillRectangle(surface, left, top, item_width, item_height);

      if (cur != NULL) {
         surface->SetColor(surface, 190, 190, 20, 0xff);
         if (cur->tag_valid == TRUE) {
            surface->SetColor(surface, 190, 190, 20, 0xff);
            surface->SetFont(surface, font_title);
            surface->DrawString(surface, cur->title, -1, left + 10, 
                                 top + 35, DSTF_LEFT);

            surface->SetColor(surface, 128, 128, 128, 0xff);
            surface->SetFont(surface, font_artist);
            surface->DrawString(surface, cur->artist, -1, left + 10, 
                                 top + 55, DSTF_LEFT);
         }
         else {
            surface->SetColor(surface, 190, 190, 20, 0xff);
            surface->SetFont(surface, font_title);
            surface->DrawString(surface, cur->name, -1, left + 10, 
                                 top + 35, DSTF_LEFT);
         }
         cur = cur->next;
      }  
   }
    
   logger->log(DEBUG, "CarMP3::draw(i)", "end");
}


void CarMP3::mouse_pressed(int x, int y) 
{
   logger->log(DEBUG, "CarMP3::mouse_pressed", "start");

   int i, top, left;
   
   for (i=0; i < 10; i++) 
   {  
      top = (item_height + MARGIN)*(i%5) + MARGIN;
      left = (i<5)?MARGIN:item_width + 2*MARGIN;
      
      if ( (y > top) && ( y < top + item_height) &&
           (x > left) && (x < left + item_width)) 
      {
           app->draw_skeleton();
           app->draw_buttons(-1);
           cur_song = page_num*10 + i;
           play(cur_song);
           draw(i);  
           surface->Flip(surface, NULL, (DFBSurfaceFlipFlags)0);       
           break;
      }
   }

   logger->log(DEBUG, "CarMP3::mouse_pressed", "end");
}


void CarMP3::action_left()
{
   logger->log(DEBUG, "CarMP3::action_left", "start");

   if (page_num > 0)
      --page_num;

   logger->log(DEBUG, "CarMP3::action_left", "end");
}


void CarMP3::action_right()
{
   logger->log(DEBUG, "CarMP3::action_right", "start");

   if (page_num < num_songs/10)
      ++page_num;

   logger->log(DEBUG, "CarMP3::action_right", "end");
}


int CarMP3::get_status()
{
   return ACTIVE;
}


void CarMP3::read_id3tag(MP3File *file)
{
  logger->log(INFORMATION, "CarMP3::read_id3tag", "start");

  char filename[256], str[256];
  ID3Tag *tag;
  
  sprintf(filename, "%s/%s", music_dir, file->name);
  
  file->tag_valid = FALSE;

  if ((tag = ID3Tag_New()) != NULL)
  {
    ID3Frame *frame;

    ID3Tag_Link(tag, filename);
    if ((frame = ID3Tag_FindFrameWithID(tag, ID3FID_TITLE)) != NULL)
    {
      ID3Field *field;
      if ((field = ID3Frame_GetField(frame, ID3FN_TEXT)) != NULL)
      {
        ID3Field_GetASCII(field, file->title, 32);
        file->tag_valid = TRUE;
      }
    }
    
    if ((frame = ID3Tag_FindFrameWithID(tag, ID3FID_LEADARTIST)) != NULL)
    {
      ID3Field *field;
      if ((field = ID3Frame_GetField(frame, ID3FN_TEXT)) != NULL)
      {
        ID3Field_GetASCII(field, file->artist, 32);
      }
    }

    sprintf(str, "File  : %s", file->name);
    logger->log(INFORMATION, "CarMP3::read_id3tag", str);
    sprintf(str, "Title : %s", file->title);
    logger->log(INFORMATION, "CarMP3::read_id3tag", str);
    sprintf(str, "Artist: %s", file->artist);
    logger->log(INFORMATION, "CarMP3::read_id3tag", str);
  }

  logger->log(DEBUG, "CarMP3::read_id3tag", "end");
}


void CarMP3::play(int selection)
{
   logger->log(DEBUG, "CarMP3::play", "start");

   int i = 0;
   char str[256];
   
   cur = head;
   while (cur && (i < selection))
   {
      cur = cur->next;
      ++i;
   }
   
   sprintf(str, "mpg123 \"%s/%s\" &", music_dir, cur->name);
   system("killall mpg123");
   system(str);
    
   logger->log(DEBUG, "CarMP3::play", "end");
}


CarMP3::~CarMP3()
{
   logger->log(DEBUG, "CarMP3::~CarMP3", "start");

   /* delete the linked linst of songs */
   ptr = head;
   while (head != NULL)
   {
      ptr = head->next;
      free(head);
      head = ptr;
   }

   /* stop any playing music */
   system("killall mpg123");

   logger->log(DEBUG, "CarMP3::~CarMP3", "end");
}

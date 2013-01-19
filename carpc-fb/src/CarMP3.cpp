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

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "CarMP3.hpp"


CarMP3::CarMP3(CarApp *main, Logger *log):CarModule(main,log)
{
   logger->log(DEBUG, "CarMP3::CarMP3", "start");

   DIR *dir;
   struct dirent *entry;

   // initialize variables
   page_num = 0;
   num_songs = 0;
   cur_song = -1;
   head = NULL;
   strcpy(music_dir, conf->get_value("music_dir"));

   status_height = 30;
   item_width = width / 2;
   item_height = (height - status_height) / 5; 

   // open the directory that contains the mp3 files
   if ((dir = opendir(music_dir)) == NULL)
   {
      logger->log(ERROR, "CarMP3::CarMP3", "Unable to open MP3 directory");
      return;
   }

   // read each filename and add to linked list
   while ((entry = readdir(dir)) != NULL)
   {
      if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
         continue;

      ptr = (MP3File *)calloc(sizeof(MP3File), 1);
      strcpy(ptr->name, entry->d_name);
      ptr->next = NULL;
      if (head == NULL) {
         head = ptr;
      } else {
         cur->next = ptr;  
      }
      cur = ptr;
      ++num_songs;

      // read in the artist, album information if available
      read_id3tag(ptr);
   }

   closedir(dir);

   logger->log(DEBUG, "CarMP3::CarMP3", "end");
}


void CarMP3::activated()
{
   logger->log(DEBUG, "CarMP3::activated", "start");

   //system("play mp3.wav &");

   logger->log(DEBUG, "CarMP3::activated", "end");
}


void CarMP3::deactivated()
{
   logger->log(DEBUG, "CarMP3::deactivated", "start");

   //system("killall mpg123");

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

   int i, color, top, left;
   int brect[8];
   char str[32];
   char *font = conf->get_value("font");

   // move the pointer ahead to the beginning of the current page
   i=0;
   cur = head;
   while (cur && (i < (page_num*10)))
   {
      cur = cur->next;
      ++i;
   }

   // draw the buttons
   for (i=0; i < 10; i++) {

      top = item_height*(i%5);
      left = (i<5)?0:item_width;

      if (i == selection)          
         color = gdTrueColor(120, 130, 236);
      else
         color = gdTrueColor(77, 96, 136);

      gdImageFilledRectangle(img, left+1, top+1, left+item_width-2, 
         top+item_height-2, color);

      if (cur != NULL) {
         if (cur->tag_valid == TRUE) {
            color = gdTrueColor(190, 190, 20);
            gdImageStringFT(img, &brect[0], color, font, 18, 0.0, 
               left + 10, top + 35, cur->title);

            color = gdTrueColor(196, 196, 196);
            gdImageStringFT(img, &brect[0], color, font, 12, 0.0, 
               left + 10, top + 65, cur->artist);
         }
         else {
            color = gdTrueColor(190, 190, 20);
            gdImageStringFT(img, &brect[0], color, font, 14, 0.0, 
               left + 10, top + 35, cur->name);
         }
         cur = cur->next;
      }  
   }

   // draw the status bar
   color = gdTrueColor(128,128,128);
   sprintf(str, "- Page %d -", page_num+1);
   gdImageFilledRectangle(img, 1, height-status_height, width - 2, 
      height-2, color);
   color = gdTrueColor(255, 255, 255);
   draw_string(0, height - status_height, width, status_height, color, 
      font, 14, str);

   update();

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
         //app->draw_buttons(-1);
         cur_song = page_num*10 + i;
         play(cur_song);
         draw(i);        
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


/**
* This function reads ID3v1 tag information located in the last 128 bytes of 
* each mp3 file.  If a valid TAG is found, then the MP3File structure is 
* populated.
*/
void CarMP3::read_id3tag(MP3File *file)
{
   logger->log(INFORMATION, "CarMP3::read_id3tag", "start");

   char filename[512], str[256];
   struct ID3Tag tag;
   FILE *fp;

   sprintf(filename, "%s/%s", music_dir, file->name);

   file->tag_valid = FALSE;
   fp = fopen(filename, "rb");
   if (fp == NULL) {
      logger->log(ERROR, "CarMP3::read_id3tag", "unable to open file");   
      return;
   }

   // read in the last 128 bytes of the file
   fseek(fp, -int(sizeof(tag)), SEEK_END);
   fread(&tag, sizeof(tag), 1, fp);
   fclose(fp);

   // copy data over only if there is a valid tag
   if (memcmp(tag.tag, "TAG", 3) == 0)
   {
      memcpy(file->title, tag.title, sizeof(tag.title));
      memcpy(file->artist, tag.artist, sizeof(tag.artist));
      memcpy(file->album, tag.album, sizeof(tag.album));
      memcpy(file->year, tag.year, sizeof(tag.year));
      memcpy(file->comment, tag.comment, sizeof(tag.comment));
      file->genre = tag.genre;

      if (strlen(file->title) > 0) 
         file->tag_valid = TRUE;

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

   sprintf(str, "/mpg123 \"%s/%s\" &", music_dir, cur->name);
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

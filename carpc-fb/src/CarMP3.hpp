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

#ifndef _CAR_MP3
#define _CAR_MP3

#include "CarApp.hpp"
#include "CarModule.hpp"

#pragma pack(1) /* align on 1-byte boundaries */
struct ID3Tag
{
   char tag[3];
   char title[30];
   char artist[30];
   char album[30];
   char year[4];
   char comment[30];
   char genre;
};
#pragma pack()


typedef struct mp3file
{
   int  tag_valid;
   char name[256];
   char title[31];
   char artist[31];
   char album[31];
   char year[5];
   char comment[31];
   char genre;
   struct mp3file *next; 
} MP3File;


class CarMP3: public CarModule {
private:
   int item_width, item_height, status_height;
   int page_num, num_songs, cur_song;
   MP3File *ptr, *cur, *head;
   char music_dir[32];

public:
   CarMP3(CarApp *main, Logger *log);
   ~CarMP3();
   void activated();
   void deactivated();
   void draw();
   void mouse_pressed(int x, int y);
   void action_right();
   void action_left();
   int get_status();

private:
   void draw(int selection);
   void read_id3tag(MP3File *file);
   void play(int selection);
};

#endif


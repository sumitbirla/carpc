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

#ifndef _CAR_MP3
#define _CAR_MP3

#include "CarApp.hpp"
#include "CarModule.hpp"

typedef struct mp3file
{
   int      tag_valid;
   char     name[256];
   char     artist[32];
   char     title[32];
   struct mp3file *next; 
} MP3File;


class CarMP3: public CarModule {
private:
   int item_width, item_height;
   int page_num, num_songs, cur_song;
   IDirectFBFont *font_title, *font_artist;
   MP3File *ptr, *cur, *head;
   char music_dir[32];
     
public:
   CarMP3(CarApp *main, Logger *logger);
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


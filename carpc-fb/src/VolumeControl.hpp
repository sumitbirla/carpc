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

#ifndef _VOLUME_CONTROL
#define _VOLUME_CONTROL

#define DEV_MIXER       "/dev/mixer"
#define MAX_VOLUME      95
#define MIN_VOLUME      00

#include "Logger.hpp"


typedef struct stereovolume
{
   unsigned char left;
   unsigned char right;
} StereoVolume;


class VolumeControl {
private:
   StereoVolume volume;
   int mixer_fd, mute;
   int master_vol;
   Logger *logger;

public:
   VolumeControl(Logger *log);
   ~VolumeControl();
   void toggle_mute();
   int is_mute();
   void volume_up();
   void volume_down();
   void set_volume(int vol);
   int get_volume();
};

#endif


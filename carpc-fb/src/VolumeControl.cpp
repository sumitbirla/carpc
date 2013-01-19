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

#include <fcntl.h>
#include <linux/soundcard.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include "VolumeControl.hpp"


VolumeControl::VolumeControl(Logger *log)
{
   logger = log;
   logger->log(DEBUG, "VolumeControl::VolumeControl", "start");

   mute = 0;

   if ( (mixer_fd=open(DEV_MIXER, O_RDWR, 0)) < 0 ) 
   {
      logger->log(ERROR, "VolumeControl::VolumeControl", "Error opening /dev/mixer");
   }

   logger->log(DEBUG, "VolumeControl::VolumeControl", "end");
}

void VolumeControl::toggle_mute()
{
   static int normal_volume;

   if (mute == 0)
   {
      /* store current volume levels for future restore */
      normal_volume = get_volume();
      //fprintf(stderr, "volume is %d \n", normal_volume);
      set_volume(0);
      mute = 1;   
   } else {
      set_volume(normal_volume);
      mute = 0;
   } 
}

int VolumeControl::is_mute()
{
   //return 1;
   return mute;
}

void VolumeControl::volume_up() 
{
   set_volume(volume.left + 5);
}

void VolumeControl::volume_down()
{
   set_volume(volume.left - 5);
}


int VolumeControl::get_volume()
{ 
   logger->log(DEBUG, "VolumeControl::get_volume", "start");

   if ( ioctl(mixer_fd, MIXER_READ(SOUND_MIXER_VOLUME), &volume) < 0 ) 
   {
      logger->log(ERROR, "VolumeControl::get_volume", "Unable to get volume");
      return 0;
   }

   logger->log(DEBUG, "VolumeControl::get_volume", "end");

   return volume.left;
}


void VolumeControl::set_volume(int vol)
{ 
   logger->log(DEBUG, "VolumeControl::set_volume", "start");

   if ((vol > MAX_VOLUME) || (vol < MIN_VOLUME))
      return;

   volume.left = vol;
   volume.right = vol;

   if ( ioctl(mixer_fd, MIXER_WRITE(SOUND_MIXER_VOLUME), &volume) < 0 ) {
      logger->log(ERROR, "VolumeControl::set_volume", "Unable to set volume");
   }   

   logger->log(DEBUG, "VolumeControl::set_volume", "end");
}


VolumeControl::~VolumeControl()
{
   logger->log(DEBUG, "VolumeControl::~VolumeControl", "start");

   close(mixer_fd);   

   logger->log(DEBUG, "VolumeControl::~VolumeControl", "end");
}

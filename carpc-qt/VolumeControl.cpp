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

#include <fcntl.h>
#include <linux/soundcard.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include "VolumeControl.h"
   
   
VolumeControl::VolumeControl() : QObject( 0, 0 )
{
   isMute = 0;

   if ( (mixer_fd=open(DEV_MIXER, O_RDWR, 0)) < 0 ) 
   {
      fprintf(stderr, "Can't open %s: \n", DEV_MIXER);
   }
   get_volume();
}


void VolumeControl::muteToggled(int toggleState)
{
   if (toggleState == 1)
      mute();
   else
      unmute();
}


void VolumeControl::mute()
{   
   normal_volume = get_volume();
   set_volume(0);
   isMute = 1;   
}

void VolumeControl::unmute()
{
   if (normal_volume < 30)
      normal_volume = 30;
   set_volume(normal_volume);
   isMute = 0;
}

int VolumeControl::is_mute()
{
   return isMute;
}

void VolumeControl::volume_up() 
{
   set_volume(volume.left + 5);
   emit volumeChanged(volume.left + 5);
}

void VolumeControl::volume_down()
{
   set_volume(volume.left - 5);
   emit volumeChanged(volume.left - 5);
}


int VolumeControl::get_volume()
{   
   if ( ioctl(mixer_fd, MIXER_READ(SOUND_MIXER_VOLUME), &volume) < 0 ) 
   {
      fprintf(stderr, "Can't obtain current volume settings \n");
      return 0;
   }
   
   return volume.left;
}


void VolumeControl::set_volume(int vol)
{ 
   if ((vol > MAX_VOLUME) || (vol < MIN_VOLUME))
      return;
      
   volume.left = vol;
   volume.right = vol;
   
   if ( ioctl(mixer_fd, MIXER_WRITE(SOUND_MIXER_VOLUME), &volume) < 0 ) {
      fprintf(stderr, "Can't set current volume settings \n");
   } 
}


VolumeControl::~VolumeControl()
{
   close(mixer_fd);   
}

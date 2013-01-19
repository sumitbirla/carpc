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

#ifndef _VOLUME_CONTROL
#define _VOLUME_CONTROL

#define DEV_MIXER       "/dev/mixer"
#define MAX_VOLUME      100
#define MIN_VOLUME      00

#include <qobject.h>


typedef struct stereovolume
{
   unsigned char left;
   unsigned char right;
} StereoVolume;


class VolumeControl : public QObject {
   Q_OBJECT

signals:
   void volumeChanged(int);

public slots:
   void muteToggled(int);

private:
   StereoVolume volume;
   int mixer_fd, isMute;
   int master_vol, normal_volume;
     
public:
   VolumeControl();
   ~VolumeControl();
   void mute();
   void unmute();
   int is_mute();
   void volume_up();
   void volume_down();
   void set_volume(int vol);
   int get_volume();
};

#endif


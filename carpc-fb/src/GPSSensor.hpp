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


#ifndef _GPS_SENSOR
#define _GPS_SENSOR

#define DEV_GPS   "/dev/ttyUSB0"
#define TRUE      1
#define FALSE     0

#include "Logger.hpp"


/* Information about each satellite in view */
struct satellite_info
{
   int   id;
   int   elevation;
   int   azimuth;
   int   snr;  // signal-to-noise ratio
};


/* Global Position Fix Data */
struct gpf_data
{
   float    time;          // time in UTC of fix
   float    latitude;      // positive indicates north
   char     latitude_ns;   // north or south
   float    longitude;     // positive indicates east
   char     longitude_ew;  // east or west
   float    altitude;      // meters above sea level
   char     fix_quality;   // 0 - invalid, 1 GPS, 2 DGPS
   char     satellites_used; // how many were used to obtain the FIX
   char     new_info;      // indicate whether this is new information
   char     num_satellites;// number of satellites in view
   struct   satellite_info satellite[24]; 
};


class GPSSensor {
private:
   pthread_t         threadID;
   pthread_mutex_t   mutex;
   int               fd;
   int               bStop;
   struct gpf_data   data;
   Logger            *logger;

public:
   GPSSensor(Logger *log);
   ~GPSSensor();
   void start();
   void stop();
   int is_connected();
   void ReceiveData();
   void get_data(struct gpf_data *a);

private:
   int checksum(char *sentence);
   void parse_gpgga(char *sentence);
   void parse_gpgsv(char *sentence);
};

#endif



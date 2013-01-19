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


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h> 

#include "GPSSensor.hpp"


GPSSensor::GPSSensor(Logger *log)
{
   logger = log;
   logger->log(DEBUG, "GPSSensor::GPSSensor", "start");

   fd = -1;
   pthread_mutex_init(&mutex, NULL);

   logger->log(DEBUG, "GPSSensor::GPSSensor", "end");
}


extern "C" void * _GPSThread(void *);

void* _GPSThread(void* arg) 
{
   class GPSSensor *obj = (GPSSensor *) arg;
   obj->ReceiveData();
}


void GPSSensor::start()
{
   logger->log(DEBUG, "GPSSensor::start", "start");
   
   bStop = FALSE;
   pthread_create ( &threadID, NULL, _GPSThread, (void*) this );

   logger->log(DEBUG, "GPSSensor::start", "end");
}


void GPSSensor::stop()
{
   logger->log(DEBUG, "GPSSensor::stop", "start/end");
   bStop = TRUE;
}


int GPSSensor::is_connected()
{
   logger->log(DEBUG, "GPSSensor::is_connected", "start/end");

   if (fd > 0) return TRUE;
   return FALSE;
} 


void GPSSensor::ReceiveData()
{
   logger->log(DEBUG, "GPSSensor::ReceiveData", "start");

   int res;
   struct termios newtio;
   char buf[82];  // each NMEA sentence cannot be longer than 80 chars

   fd = open(DEV_GPS, O_RDWR | O_NOCTTY ); 
   if (fd <0) {
      logger->log(ERROR, "GPSSensor::ReceiveData", "Open failed /dev/ttyUSB0"); 
      return; 
   }

   bzero(&newtio, sizeof(newtio));
   newtio.c_cflag = B4800 | CRTSCTS | CS8 | CLOCAL | CREAD;
   newtio.c_iflag = IGNPAR; ICRNL;
   newtio.c_oflag = 0;
   newtio.c_lflag = ICANON;
   newtio.c_cc[VMIN]=10;
   newtio.c_cc[VTIME]=0;

   tcflush(fd, TCIFLUSH);
   tcsetattr(fd,TCSANOW,&newtio);

   while (bStop == FALSE)
   {
      res = read(fd,buf,sizeof(buf)); 
      if (res < 0) break;  // check for errors

      buf[res-1] = 0;  // get rid of the '\n' at the end
      if (res > 6)
      {
         if (checksum(buf) == FALSE) continue;

         logger->log(INFORMATION, "GPSSensor::ReceiveData", buf);
         
         if (!strncmp(buf, "$GPGGA", 6)) // print only Global Position Fix data
            parse_gpgga(buf);
         else if (!strncmp(buf, "$GPGSV", 6))
            parse_gpgsv(buf);
      }
   }

   close(fd);
   fd = -1;

   logger->log(DEBUG, "GPSSensor::ReceiveData", "end");

   return;
}

int GPSSensor::checksum(char *sentence)
{
   logger->log(DEBUG, "GPSSensor::checksum", "start");

   char str[3], sum = 0;
   int i, end_found = 0;

   // sentences must begin with '$'
   if (sentence[0] != '$') return FALSE;

   for (i = 1; i < strlen(sentence); i++)
   {
      if (sentence[i] == '*') {
         end_found = 1;
         break;
      }
      sum ^= sentence[i];
   }

   // if the '*' was not found, there is an error
   if (end_found == 0) return FALSE;

   sprintf(str, "%2X", sum);
   if (!strncmp(str, &sentence[i+1], 2)) return TRUE;

   logger->log(DEBUG, "GPSSensor::checksum", "start");

   return FALSE;
}


/*  Example of an NMEA sentence:
$GPGGA,120757,5152.985,N,00205.733,W,1,06,2.5,121.9,M,49.4,M,,*52
*/
void GPSSensor::parse_gpgga(char *sentence)
{
   logger->log(DEBUG, "GPSSensor::parse_gpgga", "start");

   char *ptr, *start, *end, str[32];
   float val;
   int val2;
   struct gpf_data tempData;

   memcpy(&tempData, &data, sizeof(struct gpf_data));

   /* extract the time of fix */
   ptr = strchr(sentence, ',');
   start = ptr + 1;
   end = strchr(start, ',');
   tempData.time = atof(start);

   /* get the latitude */
   start = end + 1;
   end = strchr(start, ',');
   tempData.latitude = atof(start);
   tempData.latitude_ns = *(end + 1);

   /* get the longitude */
   start = end + 3;
   end = strchr(start, ',');
   tempData.longitude = atof(start);
   tempData.longitude_ew = *(end + 1);

   /* quality of fix */
   tempData.fix_quality = atoi(end + 3);

   /* Number of satellites used to obtain fix */
   start = end + 5;
   end = strchr(start, ',');
   tempData.satellites_used = atoi(start);

   /* skip horizontal dilution of position */
   start = end + 1;
   end = strchr(start, ',');

   /* get the altitude */
   start = end + 1;
   tempData.altitude = atof(start);

   // CRITICAL SECTION
   pthread_mutex_lock(&mutex);
   memcpy(&data, &tempData, sizeof(struct gpf_data));
   pthread_mutex_unlock(&mutex);
   
   logger->log(DEBUG, "GPSSensor::parse_gpgga", "end");
}


void GPSSensor::parse_gpgsv(char *sentence)
{
   logger->log(DEBUG, "GPSSensor::parse_gpgsv", "start");

   char *ptr, *start, *end, str[64];
   int num_msgs, seq_num, num_sats; 
   int start_index, end_index;
   static int prev_seq_num;
   static struct satellite_info sat[24];

   // number of messages 
   ptr = strchr(sentence, ',');
   start = ptr + 1;
   end = strchr(start, ',');
   num_msgs = atoi(start);

   // sequence number 
   start = end + 1;
   end = strchr(start, ',');
   seq_num = atoi(start);
  
   // number of satellites in view
   start = end + 1;
   end = strchr(start, ',');
   num_sats =  atoi(start);

   // figure out which satellites are contained in this sentence
   start_index = (seq_num-1)*4;
   if ((start_index+4) < num_sats) 
      end_index = start_index+4;
   else
      end_index = num_sats;

   for (int i = start_index; i < end_index; i++)
   {
      // satellite ID
      start = end + 1;
      end = strchr(start, ',');
      sat[i].id = atoi(start);

      // elevation
      start = end + 1;
      end = strchr(start, ',');
      sat[i].elevation = atoi(start);

      // azimuth
      start = end + 1;
      end = strchr(start, ',');
      sat[i].azimuth = atoi(start);

      // signal-to-noise ratio
      start = end + 1;
      end = strchr(start, ',');
   }

   // copy the data if this is the final message
   if (num_msgs == seq_num) 
   {
      // CRITICAL SECTION
      pthread_mutex_lock(&mutex);
      data.new_info = 1;
      data.num_satellites = num_sats;
      memcpy(&data.satellite[0], sat, num_sats*(sizeof(struct satellite_info)));
      pthread_mutex_unlock(&mutex);

      /*for (int i = 0; i < num_sats; i++)
      {
         sprintf(str, "ID=%d, Elevation=%d, Azimuth=%d, SNR=%d", sat[i].id, 
               sat[i].elevation, sat[i].azimuth, sat[i].snr);
         logger->log(INFORMATION, "GPSSensor::parse_gpgsv", str);
      }*/
   }

   logger->log(DEBUG, "GPSSensor::parse_gpgsv", "end");
}


void GPSSensor::get_data(struct gpf_data *a)
{
   logger->log(DEBUG, "GPSSensor::get_data", "start");

   // CRITICAL SECTION
   pthread_mutex_lock(&mutex);
   memcpy(a, &data, sizeof(struct gpf_data));
   data.new_info = 0;
   pthread_mutex_unlock(&mutex);

   logger->log(DEBUG, "GPSSensor::get_data", "end");
}


GPSSensor::~GPSSensor()
{
   bStop = TRUE;
}


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
   
   
GPSSensor::GPSSensor()
{
}


extern "C" void * _ThreadRoutine(void *);

void* _ThreadRoutine(void* arg) 
{
      class GPSSensor *obj = (GPSSensor *) arg;
      obj->ReceiveData();
}


void GPSSensor::start()
{
   bStop = FALSE;
   pthread_create ( &threadID, NULL, _ThreadRoutine, (void*) this );
}


void GPSSensor::stop()
{
   bStop = TRUE;
}


void GPSSensor::ReceiveData()
{
   int fd, res, i = 0;
   struct termios newtio;
   char buf[255];

   fd = open(DEV_GPS, O_RDWR | O_NOCTTY ); 
   if (fd <0) {perror(DEV_GPS); return; }

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
      res = read(fd,buf,255); 
      buf[res]=0;  /* set end of string, so we can printf */
      if (res > 40)
      {
         if (!strncmp(buf, "$GPGGA", 6)) // print only Global Position Fix data
         {
            //fprintf(stderr, "%s", buf);
            parse_nmea(buf);
         }
      }
      
      ++i;
   }

   close(fd);

   fprintf(stderr, "EXITING THREAD\n");

   return;
}

/*  Example of an NMEA sentence:
      $GPGGA,120757,5152.985,N,00205.733,W,1,06,2.5,121.9,M,49.4,M,,*52
*/
void GPSSensor::parse_nmea(char *sentence)
{
   char *ptr, *start, *end, str[32];
   float val;
   int val2;

   /* extract the time of fix */
   ptr = strchr(sentence, ',');
   start = ptr + 1;
   end = strchr(start, ',');
   data.time = atof(start);

   /* get the latitude */
   start = end + 1;
   end = strchr(start, ',');
   data.latitude = atof(start);
   data.latitude_ns = *(end + 1);
   
   /* get the longitude */
   start = end + 3;
   end = strchr(start, ',');
   data.longitude = atof(start);
   data.longitude_ew = *(end + 1);
   
   /* quality of fix */
   data.fix_quality = atoi(end + 3);
   
   /* Number of satellites in view */
   start = end + 5;
   end = strchr(start, ',');
   data.num_satellites = atoi(start);
   
   /* skip horizontal dilution of position */
   start = end + 1;
   end = strchr(start, ',');

   /* get the altitude */
   start = end + 1;
   data.altitude = atof(start);
   
   /*
   fprintf(stderr, "Time of Fix = %f \n", data.time);
   fprintf(stderr, "Latitude    = %f %c \n", data.latitude, data.latitude_ns);
   fprintf(stderr, "Longitude   = %f %c \n", data.longitude, data.longitude_ew);
   fprintf(stderr, "Altitude    = %d \n", data.altitude);
   fprintf(stderr, "Quality     = %d \n", data.fix_quality);
   fprintf(stderr, "Satellites  = %d \n", data.num_satellites);*/
}


void GPSSensor::get_data(GPFData *a)
{
   memcpy(a, &data, sizeof(GPFData));
}


GPSSensor::~GPSSensor()
{
   bStop = TRUE;
}


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
#include <string.h>	
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <math.h>

#include "CarGPS.hpp"


extern "C" void * _GPSMonitorThread(void *);

void* _GPSMonitorThread(void* arg) 
{
   class CarGPS *obj = (CarGPS *) arg;
   obj->run_monitor_loop();
}


CarGPS::CarGPS(CarApp *main, Logger *log):CarModule(main, log)
{
   logger->log(DEBUG, "CarGPS::CarGPS", "start");

   FILE *fp;

   fp = fopen("gps.jpg", "rb");
   if (fp != NULL) {
      graphic = gdImageCreateFromJpeg(fp);
      fclose(fp);
      gdImageCopy(img, graphic, 0, img->sy - graphic->sy, 0, 0, graphic->sx, 
                  graphic->sy);
   }

   sensor = new GPSSensor(logger);
   display_type = SENSOR_READOUT;
   
   logger->log(DEBUG, "CarGPS::CarGPS", "end");
}


void CarGPS::activated()
{
   logger->log(DEBUG, "CarGPS::activated", "start");

   bActive = TRUE;
   sensor->start();
   pthread_create (&threadID, NULL, _GPSMonitorThread, (void*) this );

   logger->log(DEBUG, "CarGPS::activated", "end");
}


void CarGPS::deactivated()
{
   logger->log(DEBUG, "CarGPS::deactivated", "start");

   bActive = FALSE;
   sensor->stop();

   logger->log(DEBUG, "CarGPS::deactivated", "end");
}


void CarGPS::run_monitor_loop()
{
   logger->log(DEBUG, "CarGPS::run_monitor_loop", "start");

   while (bActive == TRUE)
   {
      draw();
      sleep(3);
   }

   logger->log(DEBUG, "CarGPS::run_monitor_loop", "end");
}


void CarGPS::draw()
{
   logger->log(DEBUG, "CarGPS::draw", "start");

   struct gpf_data data;

   if (sensor->is_connected()) {
      sensor->get_data(&data);

      if (display_type == SENSOR_READOUT)
         draw_readout(&data);
      else
         draw_map(&data);

      return;
   } 

   // sensor is not connected
   draw_string(0, 0, width, height-100, gdTrueColor(250,250,250), 
      conf->get_value("font"), 18, "GPS Receiver not connected");
   gdImageCopy(img, graphic, 0, img->sy - graphic->sy, 0, 0, graphic->sx, 
      graphic->sy);
   update();

   logger->log(DEBUG, "CarGPS::draw", "end");
}


void CarGPS::draw_readout(struct gpf_data *data)
{
   logger->log(DEBUG, "CarGPS::draw_readout", "start");

   char str[128];
   char *f = conf->get_value("font");
   int white = gdTrueColor(250,250,250);
   int gray = gdTrueColor(200, 250, 200);
   int black = gdTrueColor(0,0,0);
   int cx, cy;

   // time
   int time = (int)data->time;
   int hour = time/10000;
   int minute  = time/100 - (hour*100);
   int second = time - (hour*10000) - (minute*100);
   sprintf(str, "Time: %.2d:%.2d:%.2d UTC", hour, minute, second); 
   gdImageFilledRectangle(img, 0, height - 80, width, height, black);
   draw_string(0, height-40, width, 40, white, f, 18, str);

   // position
   sprintf(str, "Position: %.2f %c, %.2f %c", data->latitude/100.0, 
      data->latitude_ns, data->longitude/100.0, data->longitude_ew);
   gdImageFilledRectangle(img, 0, 0, width, 40, black);
   draw_string(0, 0, width, 40, white, f, 18, str);

   // altitude
   sprintf(str, "Altitude: %d m", data->altitude); 
   //draw_string(0, 150, width, 30, white, f, 18, str);

   // altitude
   sprintf(str, "Satellites in view: %d", data->num_satellites); 
   //draw_string(0, 200, width, 30, white, f, 18, str);

   // draw the new satellite map only if new data is available
   if (data->new_info) 
   {
      gdImageFilledRectangle(img, 0, 40, width, height-80, black);

      //initialize useful variables
      cx = width / 2;
      cy = height / 2;

      // draw the concentric circles
      gdImageArc(img, cx, cy, 100, 100, 0, 360, gray);
      gdImageArc(img, cx, cy, 200, 200, 0, 360, gray);
      gdImageArc(img, cx, cy, 300, 300, 0, 360, gray);

      // crosshair
      gdImageLine(img, cx-150, cy, cx+150, cy, gray);
      gdImageLine(img, cx, cy-150, cx, cy+150, gray);

      // label the directions
      draw_string(cx-20, cy-185, 40, 40, gray, f, 14, "N");
      draw_string(cx+150, cy-20, 40, 40, gray, f, 14, "E");
      draw_string(cx-20, cy+150, 40, 40, gray, f, 14, "S");
      draw_string(cx-185, cy-20, 40, 40, gray, f, 14, "W");

      // draw the satellites
      int x, y;
      float r, theta;

      for (int i = 0; i < data->num_satellites; i++)
      {
         r = 150.0 - (float)data->satellite[i].elevation * 150.0 / 90.0;
         theta = (float)(data->satellite[i].azimuth-90) * 2.0 * 3.14159 / 360.0;

         x = (int)(r * cos(theta)) + cx;
         y = (int)(r * sin(theta)) + cy;

         sprintf(str, "%d", data->satellite[i].id);
         gdImageFilledArc(img, x, y, 5, 5, 0, 360, white, gdArc);
         draw_string(x, y, 18, 18, gray, f, 10, str);
      }
   }

   update();
   logger->log(DEBUG, "CarGPS::draw_readout", "end");
}


void CarGPS::draw_map(struct gpf_data *data)
{
   logger->log(DEBUG, "CarGPS::draw_map", "start");

   char str[128], *map_data;
   int sockfd, len, bytes, tot_bytes, map_size;
   struct sockaddr_un address;

   // open a stream socket to TMRS
   sockfd = socket (AF_UNIX, SOCK_STREAM, 0);
   address.sun_family = AF_UNIX;
   strcpy (address.sun_path, "/var/tmrs_socket");

   if (connect (sockfd, (struct sockaddr *) &address, sizeof(address)) == -1)
   {
      gdImageFilledRectangle(img, 0, 0, width, height-100, gdTrueColor(0,0,0));
      gdImageCopy(img, graphic, 0, img->sy - graphic->sy, 0, 0, graphic->sx, 
         graphic->sy);
      draw_string(0, 0, width, height-100, gdTrueColor(250,250,250), 
         conf->get_value("font"), 18, "Mapping Engine is not running");
      update();
      return;
   }

   // send a 'draw map' request to TMRS
   sprintf(str, "M,RAW,%d,%d,100,27971864,-82561903\n", width, height);
   //sprintf(str, "M,RAW,%d,%d,100,27592354,-82226377\n", width, height);
   write (sockfd, str, strlen(str));

   // allocate memory to hold returned image
   map_size = width*height*4; // 4 bytes per pixel
   map_data = (char *) malloc(map_size);  

   // read in data
   tot_bytes = 0;
   do {
      bytes = read(sockfd, &map_data[tot_bytes], map_size-tot_bytes);
      tot_bytes += bytes;
   } while (bytes > 0);

   // close the socket
   close (sockfd);

   // draw the received data to screen buffer
   for (int y = 0; y < height; y++)
      memcpy(&img->tpixels[y][0], &map_data[y*width*4], width*4); 

   update();

   logger->log(DEBUG, "CarGPS::draw_map", "end");
}


void CarGPS::action_left()
{
   logger->log(DEBUG, "CarGPS::action_left", "start");

   if (display_type == SENSOR_READOUT) 
      display_type = MAP;
   else
      display_type = SENSOR_READOUT;

   logger->log(DEBUG, "CarGPS::action_left", "end");
}


void CarGPS::action_right()
{
   logger->log(DEBUG, "CarGPS::action_right", "start");

   if (display_type == SENSOR_READOUT) 
      display_type = MAP;
   else
      display_type = SENSOR_READOUT;

   logger->log(DEBUG, "CarGPS::action_right", "end");
}


CarGPS::~CarGPS()
{
   logger->log(DEBUG, "CarGPS::~CarGPS", "start");

   sensor->stop();

   logger->log(DEBUG, "CarGPS::~CarGPS", "end");
}



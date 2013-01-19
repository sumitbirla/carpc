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
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h> 
#include <usb.h>

#include "TouchScreen.hpp"


TouchScreen::TouchScreen(Logger *log)
{
   logger = log;
   logger->log(DEBUG, "TouchScreen::TouchScreen", "start");

   pHead = NULL;
   pTail = NULL;
   pthread_mutex_init(&mutex, NULL);

   logger->log(DEBUG, "TouchScreen::TouchScreen", "end");
}


extern "C" void * _TouchScreenThread(void *);

void* _TouchScreenThread(void* arg) 
{
   class TouchScreen *obj = (TouchScreen *) arg;
   obj->ReceiveData();
}


void TouchScreen::start()
{
   logger->log(DEBUG, "TouchScreen::start", "start/end");
   bStop = FALSE;
   pthread_create ( &threadID, NULL, _TouchScreenThread, (void*) this );
}


void TouchScreen::stop()
{
   logger->log(DEBUG, "TouchScreen::stop", "start/end");
   bStop = TRUE;
}


void TouchScreen::ReceiveData()
{
   logger->log(DEBUG, "TouchScreen::ReceiveData", "start");

   int i,ret,x,y,x1,y1,s,prev_s;
   char str[256];
   struct usb_bus *bus;
   struct usb_device *dev;
   usb_dev_handle *udev;

   usb_init();
   usb_find_busses();
   usb_find_devices();

   for (bus = usb_busses; bus; bus = bus->next) {
      for(dev = bus->devices; dev; dev = dev->next) {
         if (dev->descriptor.idVendor == VENDOR_ID && 
            dev->descriptor.idProduct == PRODUCT_ID)
         {
            udev = usb_open(dev);

            ret = usb_get_string_simple(udev, dev->descriptor.iManufacturer, str, sizeof(str));
            if (ret > 0) logger->log(INFORMATION, "TouchScreen::ReceiveData", str);

            ret = usb_claim_interface(udev,0);
            if (ret < 0) {
               logger->log(ERROR, "TouchScreen::ReceiveData", usb_strerror());
               return;
            }

            while (bStop == FALSE)
            {
               ret = usb_interrupt_read(udev, 1, str, 8, 50000);
               if (ret < 0)
                  logger->log(DEBUG, "TouchScreen::ReceiveData", usb_strerror());
               else  {
                  s = TOUCHKIT_GET_TOUCHED(str);

                  //handle only if new state is different from previous
                  if (s != prev_s) {

                     x1 = TOUCHKIT_GET_X(str);
                     y1 = TOUCHKIT_GET_Y(str);

                     // sanity check
                     if ((x1 < 0) || (x1 > 2047) || (y1 < 0) || (y1 > 2047))
                        continue;

                     x = (int)((float)(x1 - 108) *  0.3494);
                     y = 480 - (int)((float)(y1 - 136) * 0.2809);

                     enqueue(s, x, y);
                     prev_s = s;
                  } 
               }
            }

            ret = usb_release_interface(udev,0);
            if (ret < 0) printf("release_stat=%d,%s\n",ret,usb_strerror());
            ret = usb_close(udev);
            if (ret < 0) printf("close_stat=%d,%s\n",ret,usb_strerror());
         }
      }
   }

   logger->log(DEBUG, "TouchScreen::ReceiveData", "end");

   return;
}

void TouchScreen::enqueue(int state, int x, int y)
{
   logger->log(DEBUG, "TouchScreen::enqueue", "start");

   char str[128];
   TouchData *pData;

   sprintf(str, "%d: (%d,%d)", state, x, y);
   logger->log(DEBUG, "TouchScreen::enqueue", str);

   pData = (TouchData *)malloc(sizeof(TouchData));
   pData->next = NULL;
   pData->state = state;
   pData->x = x;
   pData->y = y;

   // CRITICAL SECTION
   pthread_mutex_lock(&mutex);
   if (pHead == NULL) pHead = pData;
   if (pTail != NULL) pTail->next = pData;
   pTail = pData;
   pthread_mutex_unlock(&mutex);

   logger->log(DEBUG, "TouchScreen::enqueue", "end");
}

// Caller must free the memory pointed to by *ptr
TouchData *TouchScreen::dequeue()
{
   //logger->log(DEBUG, "TouchScreen::dequeue", "start");

   TouchData *ptr;

   // CRITICAL SECTION
   pthread_mutex_lock(&mutex);
   ptr = pHead;
   if (pHead != NULL) pHead = pHead->next;
   if (pHead == NULL) pTail = NULL;
   pthread_mutex_unlock(&mutex);

   //logger->log(DEBUG, "TouchScreen::dequeue", "end");

   return ptr;
}


TouchScreen::~TouchScreen()
{
   bStop = TRUE;
}


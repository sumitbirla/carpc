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


#ifndef _TOUCHSCREEN
#define _TOUCHSCREEN

#define TRUE        1
#define FALSE       0

// USB parameters for eGalax USB Touchkit controller
#define VENDOR_ID   0x0eef
#define PRODUCT_ID  0x0001

#define TOUCHKIT_DOWN                   0x01
#define TOUCHKIT_GET_TOUCHED(dat)       ((((dat)[0]) & TOUCHKIT_DOWN) ? 1 : 0)
#define TOUCHKIT_GET_Y(dat)             (((dat)[3] << 7) | (dat)[4])
#define TOUCHKIT_GET_X(dat)             (((dat)[1] << 7) | (dat)[2])

#include <pthread.h>
#include "Logger.hpp"


/* Structure to hold data read in my touchscreen */
typedef struct touch_data
{
    struct touch_data *next;    // used for linked list
    int  state;         // 1 if pressed, 0 otherwise 
    int  x;             // X coordinate of touch point
    int  y;             // Y coordinate of touch point
} TouchData;



class TouchScreen {
private:
   pthread_t         threadID;
   pthread_mutex_t   mutex;
   int               bStop;
   Logger            *logger;
   TouchData         *pHead;
   TouchData         *pTail;

public:
   TouchScreen(Logger *log);
   ~TouchScreen();
   void start();
   void stop();
   void ReceiveData();
   TouchData *dequeue();

private:
   void enqueue(int state, int x, int y);

};

#endif



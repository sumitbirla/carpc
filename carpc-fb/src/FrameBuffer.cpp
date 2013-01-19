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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include "FrameBuffer.hpp"

#define RGB565(r,g,b) (((r >> 3) & 31) << 11) | (((g >> 2) & 63) << 5) | ((b >> 3) & 31) 


FrameBuffer::FrameBuffer(Logger *log)
{
   logger = log;
   logger->log(DEBUG, "FrameBuffer::FrameBuffer", "start");

   struct fb_var_screeninfo vinfo;
   struct fb_fix_screeninfo finfo;
   long int len = 0;
   int x, y;
   char str[64];

   // Open the file for reading and writing
   fd = open(FB_DEV, O_RDWR);
   if (!fd) {
      logger->log(ERROR, "FrameBuffer::FrameBuffer", "Cannot open /dev/fb0");
      exit(1);
   }

   logger->log(INFORMATION, "FrameBuffer::FrameBuffer", "/dev/fb0 opened");

   // Get fixed screen information
   if (ioctl(fd, FBIOGET_FSCREENINFO, &finfo)) {
      logger->log(ERROR, "FrameBuffer::FrameBuffer", "Cannot read fixed info");
      close(fd);
      exit(2);
   }

   // Get variable screen information
   if (ioctl(fd, FBIOGET_VSCREENINFO, &vinfo)) {
      logger->log(ERROR, "FrameBuffer::FrameBuffer", "Cannot read variable info");
      close(fd);
      exit(3);
   }

   //if (vinfo.bits_per_pixel != 32) {
   //   logger->log(ERROR, "FrameBuffer::FrameBuffer", "Framebuffer is not 32bpp");
   //   close(fd);
   //   exit(3);
   //}

   // Figure out the size of the screen in bytes
   width = vinfo.xres;
   height = vinfo.yres;
   bpp = vinfo.bits_per_pixel;
   len = width * height * vinfo.bits_per_pixel / 8;

   sprintf(str, "%dx%d %dbpp", width, height, vinfo.bits_per_pixel);
   logger->log(INFORMATION, "FrameBuffer::FrameBuffer", str);

   // Map the device to memory
   fbp = (char *)mmap(0, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
   if ((int)fbp == -1) {
      logger->log(ERROR, "FrameBuffer::FrameBuffer", "mmap() failed");
      exit(4);
   }

   logger->log(INFORMATION, "FrameBuffer::FrameBuffer", "memory mapped");

   // Create the gdImage.  This is the surface on which all the drawing 
   // operation will be performed
   img = gdImageCreateTrueColor(width, height);

   logger->log(DEBUG, "FrameBuffer::FrameBuffer", "end");
}


/* Draws the passed image onto the screen buffer */
void FrameBuffer::draw_image(int **src, int x, int y, int w, int h)
{
   for (int i = 0; i < h; i++)
      memcpy(&img->tpixels[y+i][x], src[i], w*sizeof(int));
}


/* Copies the specified rectangular region from screen buffer to 
* framebuffer device (/dev/fb0) 
*/
void FrameBuffer::update(int x1, int y1, int w, int h)
{
   logger->log(DEBUG, "FrameBuffer::update2", "start");

   short pix16;
   char r, g, b;

   //   for (int i = y1; i < y1+h; i++)
   //      memcpy(&fbp[4*(i*width + x1)], &img->tpixels[i][x1], sizeof(int)*w);

   for (int i = y1; i < y1+h; i++)
      for (int j = x1; j < x1+w; j++)
      {
         r = (img->tpixels[i][j] >> 16) & 255;
         g = (img->tpixels[i][j] >> 8) & 255;
         b = img->tpixels[i][j] & 255;
         pix16 = RGB565(r, g, b);
         memcpy(&fbp[2*(i*width + j)], &pix16, 2);
      }

      logger->log(DEBUG, "FrameBuffer::update2", "end");
}

/* Copies the specified rectangular region from screen buffer to 
* framebuffer device (/dev/fb0) 
*/
void FrameBuffer::update()
{
   logger->log(DEBUG, "FrameBuffer::update", "start");

   update(0, 0, width, height);

   logger->log(DEBUG, "FrameBuffer::update", "end");
}

void FrameBuffer::save_jpeg(char *filename)
{
   logger->log(DEBUG, "FrameBuffer::save_jpeg", "start");
   logger->log(INFORMATION, "FrameBuffer::save_jpeg", filename);

   FILE *fp;

   fp = fopen(filename, "wb");
   if (fd < 0) {
      logger->log(ERROR, "FrameBuffer::save_jpeg", "Cannot open file");
      return;
   }

   gdImageJpeg(img, fp, -1);
   fclose(fp);

   logger->log(DEBUG, "FrameBuffer::save_jpeg", "end");
}

FrameBuffer::~FrameBuffer()
{
   logger->log(DEBUG, "FrameBuffer::~FrameBuffer", "start");

   // close file handle to /dev/fb0
   close(fd);
   gdImageDestroy(img);

   logger->log(DEBUG, "FrameBuffer::~FrameBuffer", "end");
}

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

#ifndef _LOGGER
#define _LOGGER

#define LOG_FILE     "/var/log/carpc.log"

/* logging level constants */
#define ERROR        0x01
#define INFORMATION  0x02
#define DEBUG        0x04

/* possible logging destinations */
#define CONSOLE      0
//#define FILE         1


class Logger {

public:
   Logger();
   ~Logger();
   void set_log_level(char level);
   void set_log_to(char destination);
   void log(char level, char *method, char *text);

private:
   char log_level;
   int fd;
   static char * log_level_str[];
};


#endif


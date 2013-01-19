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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "Logger.hpp"


char * Logger::log_level_str[] = { "", "warning", "info", "",
"debug","","","","error"};

Logger::Logger()
{
   log_level = 0;

   fd = open(LOG_FILE, O_WRONLY | O_CREAT);
   if (fd == -1)
      fprintf(stdout, "Logger::Logger: Unable to open log file for writing.\n");

   /*strcpy(&log_level_str[DEBUG][0], "debug");
   strcpy(&log_level_str[INFORMATION][0], "info");
   strcpy(&log_level_str[WARNING][0], "warning");
   strcpy(&log_level_str[ERROR][0], "error");*/
}


void Logger::set_log_level(char level)
{
   log_level = level;
}


void Logger::set_log_to(char destination)
{
}


void Logger::log(char level, char *method, char *text)
{
   char str[256], timestamp[32];
   time_t now;
   struct tm local_time;

   if (log_level & level)  // bitwise operation to check
   {
      now = time(0);
      local_time = *localtime(&now);
      strftime(timestamp, sizeof(str), "%T", &local_time);
      sprintf(str, "%s: %s :%s: %s\n", timestamp, log_level_str[level], method, text);
      fprintf(stdout, str);  fflush(stdout);
      //write(fd, str, strlen(str));
   }
}


Logger::~Logger()
{
   close(fd);
}


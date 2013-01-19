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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "Logger.hpp"


char * Logger::log_level_str[] = { "", "debug", "info", "",
                     "warning","","","","error"};

Logger::Logger()
{
   log_level = 0;

   fd = open(LOG_FILE, O_WRONLY | O_CREAT);
   if (fd == -1)
      fprintf(stderr, "Logger::Logger: Unable to open log file for writing.\n");

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
      fprintf(stderr, str);
   }
}


Logger::~Logger()
{
   close(fd);
}


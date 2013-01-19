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

#include "ConfigFile.hpp"


ConfigFile::ConfigFile(char *filename, Logger *log)
{
   logger = log;

   logger->log(DEBUG, "ConfigFile::ConfigFile", "start");

   FILE *fp;
   char line[128], *pstr;
   int i = 0;

   fp = fopen(filename, "r");
   if (fp == NULL)
   {
      logger->log(ERROR, "ConfigFile::ConfigFile", "Cannot open config file");
      return;
   }

   while (fgets(line, sizeof(line), fp) != NULL)
   {
      if (line[0] == '#')  continue;   // skip comment lines

      pstr = strchr(line, '=');
      if (pstr == NULL) {
         logger->log(ERROR, "ConfigFile::ConfigFile", "Invalid config line");
         continue;
      }

      line[strlen(line)-1] = '\0';   // get rid of newline
      *pstr = '\0';
      ++pstr;

      strcpy(settings[i].key, line);
      strcpy(settings[i].val, pstr);
      ++i;

      if (i == MAX_SETTINGS) {
         logger->log(ERROR, "ConfigFile::ConfigFile", "Max lines reached");
         break;
      }
   }

   num_settings = i;
   sprintf(line, "Read %d settings from %s", num_settings, filename);
   logger->log(INFORMATION, "ConfigFile::ConfigFile", line);
   logger->log(INFORMATION, "ConfigFile::ConfigFile", get_value("music_dir"));

   fclose(fp);

   logger->log(DEBUG, "ConfigFile::ConfigFile", "end");
}


char * ConfigFile::get_value(char *key)
{
   for (int i = 0; i < num_settings; i++)
      if (!strcmp(settings[i].key, key)) 
         return settings[i].val;

   return NULL;
}


ConfigFile::~ConfigFile()
{
   logger->log(DEBUG, "ConfigFile::~ConfigFile", "start/end");
}

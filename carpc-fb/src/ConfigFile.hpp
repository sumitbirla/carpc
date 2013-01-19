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

#ifndef _CONFIG_FILE
#define _CONFIG_FILE

#define MAX_SETTINGS    32

#include "Logger.hpp"


struct _keyval {
   char key[32];
   char val[128];
};

class ConfigFile {
public:


private:
   struct _keyval settings[MAX_SETTINGS];
   int num_settings;
   
public:
   ConfigFile::ConfigFile(char *filename, Logger *log);
   ConfigFile::~ConfigFile();
   char *get_value(char *key);

private:
   Logger *logger;
   
};

#endif

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

#ifndef _LOGGER
#define _LOGGER

#define LOG_FILE     "/tmp/carpc.log"

/* logging level constants */
#define DEBUG        0x01
#define INFORMATION  0x02
#define WARNING      0x04
#define ERROR        0x08

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


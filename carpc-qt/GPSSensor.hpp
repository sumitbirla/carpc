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


#ifndef _GPS_SENSOR
#define _GPS_SENSOR

#define DEV_GPS   "/dev/ttyUSB0"
#define TRUE      1
#define FALSE     0


/* Global Position Fix Data */
typedef struct gpf_data
{
   float    time;          // time in UTC of fix
   float    latitude;      // positive indicates north
   char     latitude_ns;   // north or south
   float    longitude;     // positive indicates east
   char     longitude_ew;  // east or west
   float    altitude;      // meters above sea level
   char     fix_quality;   // 0 - invalid, 1 GPS, 2 DGPS
   char     num_satellites;// number of satellites in view
} GPFData;


class GPSSensor {
private:
   pthread_t   threadID;
   int         bStop;
   GPFData     data;
  
public:
   GPSSensor();
   ~GPSSensor();
   void start();
   void stop();
   void ReceiveData();
   void get_data(GPFData *a);

private:
   void parse_nmea(char *sentence);
};

#endif



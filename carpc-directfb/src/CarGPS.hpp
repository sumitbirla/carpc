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

#ifndef _CAR_GPS
#define _CAR_GPS

#include "CarApp.hpp"
#include "CarModule.hpp"
#include "GPSSensor.hpp"

#define WIDTH 568
#define HEIGHT 416 


class CarGPS: public CarModule
{
	public:
   	CarGPS(CarApp *main, Logger *logger);
	   ~CarGPS();
   	void draw();

	private:
   	IDirectFBFont *font;
	   GPSSensor sensor;

		long x1, y1, offset ;

	
	//use freads are much faster so read in whole struct at a time
	// stuff arrays will be changed later
		struct	_RT1
		{
			char stuff1[ 5 ] ;
			char TLID[ 10 ] ;
			char stuff2[ 175 ] ;
			char FRLONG[ 10 ] ;
			char FRLAT[ 9 ] ;					
			char TOLONG[ 10 ] ;
			char TOLAT[ 9 ] ;					
			char whoknows[ 2 ] ;	//space & newline
		} sRT1;


	//for struct _RT2
		struct _sP
		{
			char LONG[ 10 ] ;
			char LAT[ 9 ] ;
		} ;	//shape points


		struct _RT2
		{
			char stuff1[ 5 ] ;
			char TLID[ 10 ] ;
			char RTSQ[ 3 ] ;

		//fill this up with longs and lats		
		// will have to look at this implementation a closer
			struct _sP sP[ 10 ] ;

			char whoknows[ 2 ] ;	//space & newline
		} sRT2;

	//struct to hold the data now, if not too big
		struct _SNumOfTLIDs
		{
		//major key
			unsigned long	TLID ;

		//need to implement better scheme
			bool b_within_window ;

		//struct to hold lats and longs
			struct _SBearings
			{
          	long latitude ;
				long longitude ;
			} sFR, sTO, *sShapePoints ;

		//no of points to hold chain segments
			unsigned int numOfShapePoints ;

		} *sNumOfTLIDs ;	//or chains

	//no of Chains in this county
		unsigned long numOfTLIDs ;	//or chains
			
			
	//read in files given from census into own struct
		void load_RT1() ;
		void load_RT2() ;

	//add to carpc struct
		void addToSmallerTLIDStruct( const int & index, const struct _RT1 & sRT1 ) ;
		void addToSmallerTLIDStruct( FILE *fp ) ;
		void countNumOfShapePoints( FILE *fp, int & count, const int & beginning ) ;
		void fillInShapePoints( FILE *fp, int & count, const unsigned long & beginning, struct _SNumOfTLIDs & bob ) ;


	//for drawing
		void setPointsToDraw( const GPFData & data ) ;
		void translateScalePoints( long & lon1, long & lat1, long &lon2, long &lat2 ) ;
		void verifyWithinWindow( const long & x1, const long & y1, const long & x2, const long & y2 ) ;
		void drawMap() ;

};

#endif



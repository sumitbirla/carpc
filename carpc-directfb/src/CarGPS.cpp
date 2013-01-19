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

#include <stdio.h>	//FILE *
#include <stdlib.h>	//strtol()
#include <string.h>	//strncpy()

#include <directfb.h>

#include "CarGPS.hpp"


CarGPS::CarGPS(CarApp *main, Logger *logger):CarModule(main,logger)
{
   logger->log(DEBUG, "CarGPS::CarGPS", "start");

   sensor.start();
   
   DFBFontDescription font_dsc;

   font_dsc.flags = DFDESC_HEIGHT;
   font_dsc.height = 24;
   app->dfb->CreateFont(app->dfb, "decker.ttf", &font_dsc, &font);


	//load rt1 info, if error here do not want to continue, should be bool function
	// file is not sorted
		load_RT1() ;

	//load rt2 info
	// file is not sorted
		load_RT2() ;


   logger->log(DEBUG, "CarGPS::CarGPS", "end");
}



void CarGPS::load_RT1()
{
	//log
		logger->log(DEBUG, "CarGPS::load_RT1", "start");

	//vars
		FILE *fp ;
		int i, length ;
		

	//count how many TLIDS exist
		//open
		fp = fopen( "TGR12103.RT1", "r" ) ;
		if( !fp )
		{
		   logger->log(DEBUG, "CarGPS::load_RT1", "cannot open file");			
			return ;
		}
				
		//goto end of file
		fseek( fp, 0, SEEK_END ) ;
		
		//get length of file
		length = ftell( fp ) ;

		//go back to beginning of file
		fseek( fp, 0, SEEK_SET ) ;		

		//get num of TLIDS
		numOfTLIDs = length / sizeof(	struct _RT1 ) ;
		if( ( length % sizeof(	struct _RT1 ) ) )
		{
		   logger->log(DEBUG, "CarGPS::load_RT1", "file is not evenly divisible");			
			fclose( fp ) ;
			return ;
		}



	//load TLIDs && start lat_longs and end lat_longs into structure for now
		//allocate memory for struct
		sNumOfTLIDs = new	struct _SNumOfTLIDs[ numOfTLIDs ] ;	//or chains		
		if( !sNumOfTLIDs  )
		{
		   logger->log(DEBUG, "CarGPS::load_RT1", "not enough memory to hold sNumoftlid structure");			
			fclose( fp ) ;
			return ;
		}


	//get the info
		for( i=0; i<numOfTLIDs; i++ )
		{
       	fread( &sRT1, sizeof( struct _RT1 ), 1, fp ) ;

			addToSmallerTLIDStruct( i, sRT1 ) ;
		}

	//close file
		fclose( fp ) ;


	//log
		logger->log(DEBUG, "CarGPS::load_RT1", "end");

}



//for record type 1
void CarGPS::addToSmallerTLIDStruct( const int & index, const struct _RT1 & sRT1 )
{

	//vars
		char str[ 222 ] ;
		char buf[ 11 ] ;//magic number



	//copy TLID
		memset( buf, 0, 11 ) ;
		strncpy( buf, sRT1.TLID, 10 ) ;	//copy 10 bytes
		sNumOfTLIDs[ index ].TLID = strtoul( buf, (char **)NULL, 10 ) ;

		if( index < 14 )
		{
			sprintf( str, "\n\nindex = %ld, tlid = %s", index, buf ) ;
			logger->log(DEBUG, "CarGPS::addToSmallerTLIDStruct", str);
		}

	//copy from lats and longs
		memset( buf, 0, 11 ) ;
		strncpy( buf, sRT1.FRLONG, 10 ) ;//copy 10 bytes

		if( index < 14 )
		{
			sprintf( str, "fr long = %s", buf ) ;
			logger->log(DEBUG, "CarGPS::addToSmallerTLIDStruct", str);
		}
		sNumOfTLIDs[ index ].sFR.longitude = strtol( buf, (char **)NULL, 10 ) ;


		memset( buf, 0, 11 ) ;
		strncpy( buf, sRT1.FRLAT, 9 ) ;	//copy 9 bytes
		if( index < 14 )
		{
			sprintf( str, "fr lat = %s", buf ) ;
			logger->log(DEBUG, "CarGPS::addToSmallerTLIDStruct", str);
		}
		sNumOfTLIDs[ index ].sFR.latitude = strtol( buf, (char **)NULL, 10 ) ;


	 	
	//copy to lats and longs
		memset( buf, 0, 11 ) ;
		strncpy( buf, sRT1.TOLONG, 10 ) ;//copy 10 bytes
		if( index < 14 )
		{
			sprintf( str, "to long = %s", buf ) ;
			logger->log(DEBUG, "CarGPS::addToSmallerTLIDStruct", str);
		}
		sNumOfTLIDs[ index ].sTO.longitude = strtol( buf, (char **)NULL, 10 ) ;


		memset( buf, 0, 11 ) ;
		strncpy( buf, sRT1.TOLAT, 9 ) ;	//copy 9 bytes
		if( index < 14 )
		{
			sprintf( str, "to lat = %s", buf ) ;
			logger->log(DEBUG, "CarGPS::addToSmallerTLIDStruct", str);
		}
		sNumOfTLIDs[ index ].sTO.latitude = strtol( buf, (char **)NULL, 10 ) ;

		
		if( index < 14 )
		{
			sprintf( str, "index = %ld, tlid = %ld", index, sNumOfTLIDs[ index ].TLID ) ;
			logger->log(DEBUG, "CarGPS::addToSmallerTLIDStruct", str);

			sprintf( str, "fr lat = %ld. fr long = %ld", sNumOfTLIDs[ index ].sFR.latitude, sNumOfTLIDs[ index ].sFR.longitude ) ;
			logger->log(DEBUG, "CarGPS::addToSmallerTLIDStruct", str);
			sprintf( str, "to lat = %ld. to long = %ld", sNumOfTLIDs[ index ].sTO.latitude, sNumOfTLIDs[ index ].sTO.longitude ) ;
			logger->log(DEBUG, "CarGPS::addToSmallerTLIDStruct", str);
		}
}



	//load rt2 info
void CarGPS::load_RT2()
{
	//log
		logger->log(DEBUG, "CarGPS::load_RT2", "start");


	//vars
		int length ;

		FILE *fp ;

	//count how many TLIDS exist
		//open
		fp = fopen( "TGR12103.RT2", "r" ) ;
		if( !fp )
		{
		   logger->log(DEBUG, "CarGPS::load_RT2", "cannot open file");			
			return ;
		}
				
		//goto end of file
		fseek( fp, 0, SEEK_END ) ;
		
		//get length of file
		length = ftell( fp ) ;

		//go back to beginning of file
		fseek( fp, 0, SEEK_SET ) ;		

		//verify file is of correct size
		if( ( length % sizeof( struct _RT2 ) )  )
		{
		   logger->log(DEBUG, "CarGPS::load_RT2", "file is not evenly divisible");			
			fclose( fp ) ;
			return ;
		}


	//put into smaller tlid struct
		addToSmallerTLIDStruct( fp ) ;


	//close file
		fclose( fp ) ;

	//log
		logger->log(DEBUG, "CarGPS::load_RT2", "end");
}


//record type 2
void CarGPS::addToSmallerTLIDStruct( FILE *fp )
{
	//vars
		char 				buf[ 11 ] ;
		int				count = 0 ;
		unsigned long 	tlid,
							beginning,
							index ;


	//go back to beginning of file
		fseek( fp, 0, SEEK_SET ) ;		
		beginning = ftell( fp ) ;

	//read in struct
		fread( &sRT2, sizeof( struct _RT2 ), 1, fp ) ;

	//get TLID
		memset( buf, 0, 11 ) ;
		strncpy( buf, sRT2.TLID, 10 ) ;	//copy 10 bytes
		tlid = strtoul( buf, (char **)NULL, 10 ) ;
                            	

	//set to zero
		index = 0 ;

	//loop, go through each TLID structure to see if any shape points apply to it 
  	   do
		{

        
			if( sNumOfTLIDs[ index ].TLID == tlid )
			{

				count = 0 ;

  	    	//count num of shape points
				countNumOfShapePoints( fp, count, beginning ) ;

	
			//fill in shape points
				fillInShapePoints( fp, count, beginning, sNumOfTLIDs[ index ] ) ;
				

			//read in next part of file and match it from record type one
			//  make sure not eof here
				if( !feof( fp ) )
				{
				//mark beginning of new entry
					beginning = ftell( fp ) ;
					fread( &sRT2, sizeof( struct _RT2 ), 1, fp ) ;
				//get TLID
					memset( buf, 0, 11 ) ;
					strncpy( buf, sRT2.TLID, 10 ) ;	//copy 10 bytes
					tlid = strtoul( buf, (char **)NULL, 10 ) ;
				}


			}
			else
			{
			//set shape points to zero



				sNumOfTLIDs[ index ].numOfShapePoints = 0 ;
			//also, zero out pointer
				sNumOfTLIDs[ index ].sShapePoints = 0 ;


			//get next index or tlid
				index++ ;
     		}

      }while( ( index<numOfTLIDs )&& !feof( fp ) ) ;
}




//count num of shape points
void CarGPS::countNumOfShapePoints( FILE *fp, int & count, const int & beginning )
{
	//vars
		bool	b_done = false ;
		char 	buf[ 11 ] ;
      int  	rtsq,
				i ;
		unsigned long 	prev,
							anum ;

		char str[222];

	//beginning

	//set file pointer back one entry, bad idea, need to improve this
		fseek( fp, beginning, SEEK_SET ) ;
		
		do
		{
			prev = ftell( fp ) ;
			
		//fread one more time to get to next entry
			fread( &sRT2, sizeof( struct _RT2 ), 1, fp ) ;

		//this entry, i can read rtsq
			if( !feof( fp ) )
			{
				fread( &sRT2, sizeof( struct _RT2 ), 1, fp ) ;
			//convert RTSQ to int
			//get TLID
				memset( buf, 0, 11 ) ;			
				strncpy( buf, sRT2.RTSQ, 3 ) ;	//copy 3 bytes

				rtsq = strtoul( buf, (char **)NULL, 10 ) ;//base 10
			}
			else
			{
				rtsq = 1 ;
			}


		//sluggishly go through till the end of this entry until getting a zero long
		//  look at one entry ahead, if = 1 then go back to previous entry and fill pts
			if( rtsq == 1 )
			{
			//go back 1 step, entry
				fseek( fp, prev, SEEK_SET ) ;	


			//re-read this info, need to improve this section as well
			//  okay, cost can be amortized over use
				fread( &sRT2, sizeof( struct _RT2 ), 1, fp ) ;

				for( i=0; i<10; i++ )
				{
					memset( buf, 0, 11 ) ;
					strncpy( buf, sRT2.sP[ i ].LAT, 9 ) ;	//copy 9 bytes
					anum = strtoul( buf, (char **)NULL, 10 ) ;//base 10
					if( anum == 0 )
					{
					//no more numbers to retrieve
                	break ;
					}//if
				}//for

			//inc count again
				count += i ;

			//break out of this function
				b_done = true ;
			}//if( rtsq == 1 )
			else
			{
   	   //inc count, the shape points continue for this tlid
			//  get next entry
				count += 10 ;
			}//else


		}while( !feof( fp ) && !b_done )	;

}



 
//fill in shape points
void CarGPS::fillInShapePoints( FILE *fp, int & count, const unsigned long & beginning, struct _SNumOfTLIDs & bob )
{
	//vars
		char 	buf[ 11 ] ;
		int 	i,
				index = 0 ; ;
		long 	alat,
				along ;
		char str[222];

	//set shape points, num of
		bob.numOfShapePoints = count ;

		//sprintf( str, "count = %d", count ) ;
		//logger->log(DEBUG, "CarGPS::fillInShapePoints", str ) ;			

	//allocate memory for these lat longs
	// it looks a little awkward with the scope operator, needed to define struct within a struct
		bob.sShapePoints = new struct _SNumOfTLIDs::_SBearings[ count ] ; 
		if( !bob.sShapePoints )
		{
			logger->log(DEBUG, "CarGPS::fillInShapePoints", "not enough memory for bob");			
			return ;
		}


	//set to file ptr to beginning of this run, again
		fseek( fp, beginning, SEEK_SET ) ;		

	//get shape points
		do
		{
      //read in entry
			fread( &sRT2, sizeof( struct _RT2 ), 1, fp ) ;
			

		//check count
			if( ( count / 10 ) == 0 )
			{
				for( i=0; i<count; i++ )
				{
				//get Long info
					memset( buf, 0, 11 ) ;
					strncpy( buf, sRT2.sP[ i ].LONG, 10 ) ;	//copy 9 bytes
					along = strtoul( buf, (char **)NULL, 10 ) ;//base 10

				//get Lat info
					memset( buf, 0, 11 ) ;
					strncpy( buf, sRT2.sP[ i ].LAT, 9 ) ;	//copy 9 bytes
					alat = strtoul( buf, (char **)NULL, 10 ) ;//base 10
	
				//put into structure
					bob.sShapePoints[ index ].longitude = along ;
					bob.sShapePoints[ index ].latitude  = alat ;
				
				//inc index
					index++ ;

				}

			//all done
				count = 0 ;
			}
			else	//more than 10
			{

				for( i=0; i<10; i++ )
				{
				//get Long info
					memset( buf, 0, 11 ) ;
					strncpy( buf, sRT2.sP[ i ].LONG, 10 ) ;	//copy 9 bytes
					along = strtoul( buf, (char **)NULL, 10 ) ;//base 10

				//get Lat info
					memset( buf, 0, 11 ) ;
					strncpy( buf, sRT2.sP[ i ].LAT, 9 ) ;	//copy 9 bytes

					alat = strtoul( buf, (char **)NULL, 10 ) ;//base 10
	
				//put into structure
					bob.sShapePoints[ index ].longitude = along ;
					bob.sShapePoints[ index ].latitude  = alat ;
				
				//inc index
					index++ ;

				}


			//subtract 10 from count
				count -= 10 ;
      	}

		}while( ( count != 0 )&&( !feof( fp ) ) ) ;

}


void CarGPS::draw()
{
   logger->log(DEBUG, "CarGPS::draw", "start");
   char str[128];
   GPFData data;
   sensor.get_data(&data);


   surface->SetFont(surface, font);
   surface->SetColor(surface, 190, 190, 20, 0xff);



	//set any of the structs to true or false ;
		setPointsToDraw( data ) ;


   sprintf(str, "before drawMap, jje" );
   surface->DrawString(surface, str, -1, 100, 10, DSTF_LEFT);


	//draw map
		drawMap() ;

   sprintf(str, "after drawMap, jje" );
   surface->DrawString(surface, str, -1, 100, 50, DSTF_LEFT);

/*
   sprintf(str, "still in early stages, jje" );
   surface->DrawString(surface, str, -1, 100, 0, DSTF_LEFT);
   
   sprintf(str, "Time of Fix : %6.0f", data.time);
   surface->DrawString(surface, str, -1, 100, 50, DSTF_LEFT);
                  
   sprintf(str, "   Latitude : %.4f %c", data.latitude, data.latitude_ns);
   surface->DrawString(surface, str, -1, 100, 80, DSTF_LEFT);

   sprintf(str, "  Longitude : %.4f %c", data.longitude, data.longitude_ew);
   surface->DrawString(surface, str, -1, 100, 110, DSTF_LEFT);

   sprintf(str, "   Altitude : %d", data.altitude);
   surface->DrawString(surface, str, -1, 100, 140, DSTF_LEFT);

*/
   sprintf(str, "    Quality : %d", data.fix_quality);
   surface->DrawString(surface, str, -1, 100, 170, DSTF_LEFT);

   sprintf(str, " Satellites : %d", data.num_satellites);
	surface->DrawString(surface, str, -1, 100, 200, DSTF_LEFT);


   surface->SetColor(surface, 0, 255, 0, 0xff);
	surface->DrawLine( surface, 0, 0, 568, 416 ) ;



   logger->log(DEBUG, "CarGPS::draw", "end");
}



	//set any of the structs to true or false ;
void CarGPS::setPointsToDraw( const GPFData & data )
{
   logger->log(DEBUG, "CarGPS::setPointsToDraw", "start");

   //vars
		long 	x1, y1, x2, y2,
				latitude,
				longitude,
				offset ;

		char str[ 128 ];


	
		latitude 	= +27900000 ; //data.latitude * 1000000 ;//six decimal places
		longitude 	= -82740000 ; //data.longitude * 1000000 ;//six decimal places

	//zoom offset
		offset = 290000 ; //

	
		//x1 = longitude - getZoomOffset() ;
		x1 = longitude - offset ;
		y1 = latitude	- offset ;

		
		x2 = longitude + offset ;
		y2 = latitude	+ offset ;


	//verify points within range
		verifyWithinWindow( x1, y1, x2, y2 ) ;




	//copy need info for translation and scaling
		this->x1 = x1 ;
		this->y1 = y1 ;
		this->offset = offset ;	




   logger->log(DEBUG, "CarGPS::setPointsToDraw", "end");

}




void CarGPS::translateScalePoints( long & lat1, long & lon1, long &lat2, long &lon2 )
{
	//var
		long d_offset = offset * 2 ;	


	//translate points first
		lon1 -= x1 ;
		lat1 -= y1 ;

		lon2 -= x1 ;
		lat2 -= y1 ;


	//scale points
	//understand why not to use -1 on longitudes
		lat1 = 		( lat1 * HEIGHT )/ d_offset ;		
		lon1 = 	( lon1 * WIDTH ) / d_offset ;		

		lat2 = 		( lat2 * HEIGHT )/ d_offset ;		
		lon2 = 	( lon2 * WIDTH ) / d_offset ;		

}



void CarGPS::verifyWithinWindow( const long & x1, const long & y1, const long & x2, const long & y2 )
{
   logger->log(DEBUG, "CarGPS::verifyWithinWindow", "start");

   //vars
		char str[228];
		bool found ;
		long i, j ;
		long 	lat1,
				lon1,
				lat2,
				lon2 ;

		long countin=0, countout=0 ;

		sprintf( str, "x1 = %ld, y1 = %ld, x2 = %ld, y2=%ld", x1,y1,x2,y2) ;
	   logger->log(DEBUG, "CarGPS::verifyWithinWindow", str);

	//first pass through struct
		for( i=0; i<numOfTLIDs; i++ )
		{
		//reinit to false
			found = false ;

		//make more readable
			lat1 = sNumOfTLIDs[ i ].sFR.latitude ;         
			lon1 = sNumOfTLIDs[ i ].sFR.longitude ;

			lat2 = sNumOfTLIDs[ i ].sTO.latitude ;         
			lon2 = sNumOfTLIDs[ i ].sTO.longitude ;

		//print 70 or so , lats lons
			if( !( i%10000 ) )
			{
				sprintf( str, "lat1= %ld, lon1 = %ld, lat2 = %ld, lon2=%ld", lat1,lon1,lat2,lon2);
	   		logger->log(DEBUG, "CarGPS::verifyWithinWindow", str);
			}         

		//check from points
			if( lat1 > y1 && lat1 < y2 && lon1 > x1 && lon1 < x2 )
			{
				found = true ;
			}
		//check to points
			else if( lat2 > y1 && lat2 < y2 && lon2 > x1 && lon2 < x2 )
			{
				found = true ;
			}
		//now, if any of the shape points are within window, still draw the chain out
			else
			{
            for( j=0; j<sNumOfTLIDs[ i ].numOfShapePoints; j++ )
				{
					lat1 = sNumOfTLIDs[ i ].sShapePoints[ j ].latitude ;
					lon1 = sNumOfTLIDs[ i ].sShapePoints[ j ].longitude ;
		
					if( !( lat1 > y1 && lat1 < y2 && lon1 > x1 && lon1 < x2 ) )
					{
						;
					}
					else
					{
						found = true ;
						break ;
					}
				}//for
			}//else


		//!found -> should occur more frequently
			if( !found )
			{
				countout++;
				sNumOfTLIDs[ i ].b_within_window = false ;
			}
			else
			{
				countin++;
				sNumOfTLIDs[ i ].b_within_window = true ;			
			}

		}//for loop

	sprintf( str, "outside = %ld, inside of window = %ld  ***************", countout, countin ) ;
   logger->log(DEBUG, "CarGPS::verifyWithinWindow", str);


   logger->log(DEBUG, "CarGPS::verifyWithinWindow", "end");
}


//draw map
void CarGPS::drawMap()
{
   logger->log(DEBUG, "CarGPS::drawMap", "start");
	//var
		unsigned long i, j ;

		long 	lat1,
				lon1,
				lat2,
				lon2,
				orig_lat2,
				orig_lon2 ;



		char str[ 222 ] ;

//		bool finished = false ;





	//second pass through struct
		for( i=0; i<numOfTLIDs; i++ )
		{
		//verify inside window before drawing
			if( sNumOfTLIDs[ i ].b_within_window )
			{
/*            
      		if( !finished )
				{		
					finished = true ;	//draw one line

*/
//					sprintf( str, "within window, tlid = %ld", sNumOfTLIDs[ i ].TLID ) ;
//	   			logger->log(DEBUG, "CarGPS::drawMap", str ) ;



			//make more readable
				lat1 = sNumOfTLIDs[ i ].sFR.latitude ;         
				lon1 = sNumOfTLIDs[ i ].sFR.longitude ;

				
//				sprintf( str, "shape points -> no of = %ld", sNumOfTLIDs[ i ].numOfShapePoints ) ;
//   			logger->log(DEBUG, "CarGPS::drawMap", str ) ;

	   		for( j=0; j<sNumOfTLIDs[ i ].numOfShapePoints; j++ )
				{
					orig_lat2 = lat2 = sNumOfTLIDs[ i ].sShapePoints[ j ].latitude ;
					orig_lon2 = lon2 = sNumOfTLIDs[ i ].sShapePoints[ j ].longitude ;

					//sprintf( str, "shape points -> before lat1= %ld, lon1 = %ld, lat2 = %ld, lon2=%ld", lat1,lon1,lat2,lon2);
		   		//logger->log(DEBUG, "CarGPS::drawMap", str);

					translateScalePoints( lat1, lon1, lat2, lon2 ) ;

					//sprintf( str, "shape points -> after lat1= %ld, lon1 = %ld, lat2 = %ld, lon2=%ld", lat1,lon1,lat2,lon2);
		   		//logger->log(DEBUG, "CarGPS::drawMap", str);


					surface->DrawLine( surface, lon1, lat1, lon2, lat2 ) ;		

				//prepare for next set of points
					lat1 = orig_lat2 ;
					lon1 = orig_lon2 ;
				}//for


			//last set of points
				lat2 = sNumOfTLIDs[ i ].sTO.latitude ;         
				lon2 = sNumOfTLIDs[ i ].sTO.longitude ;
		
//	      	if( i<10 )
//				{
				//tlid

//					sprintf( str, "before lat1= %ld, lon1 = %ld, lat2 = %ld, lon2=%ld", lat1,lon1,lat2,lon2);
//		   		logger->log(DEBUG, "CarGPS::drawMap", str);
//				}

				//sprintf( str, "shape points -> before lat1= %ld, lon1 = %ld, lat2 = %ld, lon2=%ld", lat1,lon1,lat2,lon2);
	   		//logger->log(DEBUG, "CarGPS::drawMap", str);


			//draw last line
				translateScalePoints( lat1, lon1, lat2, lon2 ) ;


				//sprintf( str, "shape points -> after lat1= %ld, lon1 = %ld, lat2 = %ld, lon2=%ld", lat1,lon1,lat2,lon2);
	   		//logger->log(DEBUG, "CarGPS::drawMap", str);

//	      	if( i<100 )
//				{
//					sprintf( str, "after lat1= %ld, lon1 = %ld, lat2 = %ld, lon2=%ld\n\n", lat1,lon1,lat2,lon2);
//		   		logger->log(DEBUG, "CarGPS::drawMap", str);
//				}


				surface->DrawLine( surface, lon1, lat1, lon2, lat2 ) ;		
//				}
     
			}//if within window

		}//the for loop

   logger->log(DEBUG, "CarGPS::drawMap", "end");
}






CarGPS::~CarGPS()
{
   logger->log(DEBUG, "CarGPS::~CarGPS", "start");


	//var
		int i ;

	//delete shape points
		for( i=0; i<numOfTLIDs; i++ )
		{                 
			if( sNumOfTLIDs[ i ].numOfShapePoints != 0 )
			{

				delete [] sNumOfTLIDs[ i ].sShapePoints ;
				sNumOfTLIDs[ i ].sShapePoints = 0 ;
			}
		}


	//delete TLIDs
		if( numOfTLIDs != 0 )
		{
			delete [] sNumOfTLIDs ; 		
			sNumOfTLIDs = 0 ;
		}



   logger->log(DEBUG, "CarGPS::~CarGPS", "end");
}








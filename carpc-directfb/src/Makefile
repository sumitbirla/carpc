CFLAGS=-I/include/directfb
LIBS=-L/lib -O -Wall -ldirectfb -lpthread -ldl -lid3 -lz
OBJS=CarApp.o CarModule.o CarMenu.o CarRadio.o CarMP3.o CarOBDII.o CarGPS.o VolumeControl.o GPSSensor.o Logger.o OBDIIBaseCom.o


all: ${OBJS} 
	g++ ${LIBS} ${OBJS} -o carpc

CarApp.o: CarApp.cpp CarApp.hpp
	g++ ${CFLAGS} -c CarApp.cpp -o CarApp.o

CarModule.o: CarModule.cpp CarModule.hpp 
	g++ ${CFLAGS} -c CarModule.cpp -o CarModule.o

CarMenu.o: CarMenu.cpp CarMenu.hpp 
	g++ ${CFLAGS} -c CarMenu.cpp -o CarMenu.o 

CarRadio.o: CarRadio.cpp CarRadio.hpp 
	g++ ${CFLAGS} -c CarRadio.cpp -o CarRadio.o

CarMP3.o: CarMP3.cpp CarMP3.hpp
	g++ ${CFLAGS} -c CarMP3.cpp -o CarMP3.o
        
CarOBDII.o: CarOBDII.cpp CarOBDII.hpp
	g++ ${CFLAGS} -c CarOBDII.cpp -o CarOBDII.o

CarGPS.o: CarGPS.cpp CarGPS.hpp
	g++ ${CFLAGS} -c CarGPS.cpp -o CarGPS.o
	
VolumeControl.o: VolumeControl.cpp VolumeControl.hpp  
	g++ -c VolumeControl.cpp -o VolumeControl.o

GPSSensor.o: GPSSensor.cpp GPSSensor.hpp
	g++ -c GPSSensor.cpp -o GPSSensor.o

Logger.o: Logger.cpp Logger.hpp
	g++ -c Logger.cpp -o Logger.o
	
OBDIIBaseCom.o: OBDIIBaseCom.cpp OBDIIBaseCom.hpp
	g++ ${CFLAGS} -c OBDIIBaseCom.cpp -o OBDIIBaseCom.o
clean:
	rm -f carpc *.o
 

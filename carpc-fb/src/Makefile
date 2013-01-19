CFLAGS=
LIBS=-L/usr/local/lib -O -Wall -lpthread -lgd -lusb
OBJS=ConfigFile.o CarApp.o CarModule.o CarMenu.o CarRadio.o CarMP3.o CarOBDII.o CarGPS.o VolumeControl.o GPSSensor.o Logger.o FrameBuffer.o TouchScreen.o CarPhoto.o

all: ${OBJS} 
	g++ ${LIBS} ${OBJS} -o carpc

ConfigFile.o: ConfigFile.cpp ConfigFile.hpp
	g++ ${CFLAGS} -c ConfigFile.cpp -o ConfigFile.o
	
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
	
CarPhoto.o: CarPhoto.cpp CarPhoto.hpp
	g++ ${CFLAGS} -c CarPhoto.cpp -o CarPhoto.o
	
VolumeControl.o: VolumeControl.cpp VolumeControl.hpp  
	g++ ${CFLAGS} -c VolumeControl.cpp -o VolumeControl.o

GPSSensor.o: GPSSensor.cpp GPSSensor.hpp
	g++ ${CFLAGS} -c GPSSensor.cpp -o GPSSensor.o

Logger.o: Logger.cpp Logger.hpp
	g++ ${CFLAGS} -c Logger.cpp -o Logger.o
	
FrameBuffer.o: FrameBuffer.cpp FrameBuffer.hpp
	g++ ${CFLAGS} -c FrameBuffer.cpp -o FrameBuffer.o

TouchScreen.o: TouchScreen.cpp TouchScreen.hpp
	g++ ${CFLAGS} -c TouchScreen.cpp -o TouchScreen.o
	
clean:
	rm -f carpc *.o

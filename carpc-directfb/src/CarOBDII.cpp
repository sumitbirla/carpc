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

#include <directfb.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include "CarOBDII.hpp"
#include "OBDIIBaseCom.hpp"


CarOBDII::CarOBDII(CarApp *main, Logger *logger):CarModule(main,logger)
{
     logger->log(DEBUG, "CarOBDII::CarOBDII", "start");
     
     /* Read OBDII Config Information (Eventually from file or OBD interface)*/
     strcpy(units_brit, "mi/hr");
     strcpy(units_metric, "km/hr");
     isBrit = 1;
     isObdiiRunning = 0;

     DFBFontDescription font_dsc;

     font_dsc.flags = DFDESC_HEIGHT;
     font_dsc.height = 50;
     app->dfb->CreateFont(app->dfb, "decker.ttf", &font_dsc, &obdii_font);
     
     logger->log(DEBUG, "CarOBDII::CarOBDII", "end");
}


CarOBDII::~CarOBDII()
{
    logger->log(DEBUG, "CarOBDII::~CarOBDII", "start");

    int status;
    char str[256];

    // Stop the obdii interface thread.
    status = pthread_cancel(obdii_interface_thread);
    if (status) {
        sprintf(str, "obdii_interface_thread cancelled with status = %d", status);
        logger->log(INFORMATION, "CarOBDII::~CarOBDII", str);
    }
    else {
        logger->log(INFORMATION, "CarOBDII::~CarOBDII", "obdii_interface_thread closed successfuly");
    }
    //obdii_interface_thread->done = 1;

    logger->log(DEBUG, "CarOBDII::~CarOBDII", "end");
}

extern "C" void * do_scan(void *);

/**
* This method will run as a thread.
* It will perform an initial diagnostic scan.
* This MUST be done prior to monitoring diagnostics.
*/
void *do_scan(void *tgt_carObdii)
{
    // Create a new logger instance since we might want logs from
    // this thread to go to a different location.
    class Logger *logger;

    logger = new Logger();
    logger->set_log_level(DEBUG | INFORMATION | WARNING | ERROR);

    logger->log(DEBUG, "CarOBDII::do_scan", "start");

    // Need a reference to the obdii module so that the thread
    // can update GUI state, etc.
    class CarOBDII *parent_carObdii;
    parent_carObdii = (CarOBDII *)tgt_carObdii;  

    // Start the scan
    class OBDIIBaseCom *obdiiCom;
    int return_state;
    int fd;
    int read_timeout = 5;                    //5ms;
    u_int8_t buf[8];
    ssize_t return_value;
    SerialPortState *original_serial_state;  //Serial port state prior to scan.
    SerialPortState *current_serial_state;   //Maintains serial port state while carpc running.  (TO DO:  Change scope.)

    obdiiCom = new OBDIIBaseCom(logger);

    /*************************************************************
    **                                                          **
    **       Add code to setup real time scheduling here.       **
    **                                                          **
    *************************************************************/

    // Synchronous open...waits for data to be sent.
    current_serial_state->fd = open(current_serial_state->device_name, O_RDWR | O_SYNC);
    if (current_serial_state->fd < 0) {
        perror(current_serial_state->device_name);
        return NULL;
    }

    logger->log(INFORMATION, "CarOBDII::do_scan", "Opened serial device.");

    logger->log(DEBUG, "CarOBDII::do_scan", "Trying to initialize serial device.");
    return_state = obdiiCom->get_serial_state(fd, original_serial_state);
    if (return_state < 0) {
        logger->log(ERROR, "CarOBDII::do_scan", "Error initializing state.");
        return NULL;
    }

    //To start, copy "original" serial port state into the "current" serial port state.
    memcpy(&current_serial_state->serial_info, &original_serial_state->serial_info, sizeof(original_serial_state->serial_info));

    //Now set DTR and RTS flags.
    current_serial_state->dtr = 1;
    current_serial_state->rts = 0;
    return_state = obdiiCom->set_serial_state_control(fd, current_serial_state);
    if (return_state < 0) {
        logger->log(ERROR, "CarOBDII::do_scan", "Error setting set/clear for DTR and RTS.");
    }
    
    //Finally, read any leftover junk off the serial port.
    return_value = obdiiCom->serial_read(current_serial_state->fd, buf, sizeof(buf), read_timeout);
    
    logger->log(DEBUG, "CarOBDII::do_scan", "end");

    pthread_exit(NULL);
}

#define BAUDRATE B600
#define MODEMDEVICE "/dev/ttyS0"
#define _POSIX_SOURCE 1

#define FALSE 0
#define TRUE 1

/**
* This function performs the initial wakeup protocol
* for the obdii ecu.
*/
void CarOBDII::wakeup_ecu(Logger *logger)
{
    logger->log(DEBUG, "CarOBDII::wakeup_ecu", "start");

    volatile int STOP=FALSE;
    int fd;
    int c;
    int res;
    char buf[255];
    struct termios oldtio;
    struct termios newtio;

    char str[256];

    fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY);
    if (fd < 0) {
        perror(MODEMDEVICE);
    }
    else {
        logger->log(INFORMATION, "CarOBDII::wakeup_ecu", "Serial port opened successfully.");
    }

    tcgetattr(fd, &oldtio);
    bzero(&newtio, sizeof(newtio));
    
    //newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;    
    newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;         //Hardware flow control off
    //newtio.c_iflag = IGNPAR | ICRNL;
    newtio.c_iflag = IGNPAR | ICRNL | IXON | IXOFF | IXANY;   //Test xon/xoff flow control
    newtio.c_oflag = 0;
    newtio.c_lflag = ICANON;

    newtio.c_cc[VINTR]   = 0;
    newtio.c_cc[VQUIT]   = 0;
    newtio.c_cc[VERASE]   = 0;
    newtio.c_cc[VKILL]   = 0;
    newtio.c_cc[VEOF]   = 4;
    newtio.c_cc[VTIME]   = 0;
    newtio.c_cc[VMIN]   = 1;
    newtio.c_cc[VSWTC]   = 0;
    newtio.c_cc[VSTART]   = 0;
    newtio.c_cc[VSTOP]   = 0;
    newtio.c_cc[VSUSP]   = 0;
    newtio.c_cc[VEOL]   = 0;
    newtio.c_cc[VREPRINT]   = 0;
    newtio.c_cc[VDISCARD]   = 0;
    newtio.c_cc[VWERASE]   = 0;
    newtio.c_cc[VLNEXT]   = 0;
    newtio.c_cc[VEOL2]   = 0;

    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &newtio);
    logger->log(INFORMATION, "CarOBDII:wakeup_ecu", "Configured serial port.");

    while(STOP == FALSE) {
        res = read(fd, buf, 255);
        logger->log(INFORMATION, "CarOBDII:wakeup_ecu", "Read from serial port.");
        buf[res] = 0;
        sprintf(str, "Read:  %s:%d\n", buf, res);
        logger->log(INFORMATION, "CarOBDII::wakeup_ecu", str);
        if (buf[0] == 'z') {
            STOP = TRUE;
        }
    }

    tcsetattr(fd, TCSANOW, &oldtio);

    logger->log(DEBUG, "CarOBDII::wakeup_ecu", "end");
}


/**
* Request specified data from the ecu.
*/
void CarOBDII::request_ecu_data()
{
      logger->log(DEBUG, "CarOBDII::request_ecu_data", "start");

      logger->log(DEBUG, "CarOBDII::request_ecu_data", "end");
}


/**
* Starts up the obdii interface thread if necessary.
*/
void CarOBDII::start_obdii_interface()
{
    logger->log(DEBUG, "CarOBDII::start_obdii_interface", "start");

    if (!isObdiiRunning) {
        logger->log(INFORMATION, "CarOBDII::start_obdii_interface", "starting obdii_interface_thread");

        // Now we can create the OBDII Interface Thread that will
        // maintain an interface with the ECU.
        pthread_t obdii_interface_thread;
        int rc;                                // Return code for obdii interface thread.

        //rc = pthread_create(&obdii_interface_thread, NULL, do_scan, (void *)this);
        if (rc) {
            logger->log(ERROR, "CarOBDII::start_obdii_interface", "Error creating obdii_interface_thread");
        }
        else {
            isObdiiRunning = 1;
            logger->log(INFORMATION, "CarOBDII::start_obdii_interface", "obdii_interface_thread started successfully");
        }
    }
    else {
        logger->log(ERROR, "CarOBDII::start_obdii_interface", "obdii_interface_thread already running");
    }

    logger->log(DEBUG, "CarOBDII::start_obdii_interface", "end");
}


/**
* Draw the obdii GUI.
*/
void CarOBDII::draw()
{
     logger->log(DEBUG, "CarOBDII::draw", "start");
     
     strcpy(speed, "200");
     fprintf(stdout, "CarOBDII::draw : speed = %s\n", speed);
     
     // Set the units to display depending on measuring system.
     fprintf(stdout, "CarOBDII::draw : Checking units... \n");
     if (isBrit) {
        strcpy(units, units_brit);
     }
     else {
        strcpy(units, units_metric);
     }
     fprintf(stdout, "CarOBDII::draw : units = %s\n", units);

     // Set the speed text to be displayed.
     strcpy(speed_display, speed);
     fprintf(stdout, "CarOBDII::draw : speed_display = %s\n", speed_display);

     strcat(speed_display, units);
     fprintf(stdout, "CarOBDII::draw : speed_display = %s\n", speed_display);

     surface->SetFont(surface, obdii_font);
     surface->SetColor(surface, 190, 190, 20, 0xff);
     surface->DrawString(surface, speed_display, -1, 302, 50, DSTF_CENTER);

     logger->log(DEBUG, "CarOBDII::end", "start");
}


void CarOBDII::mouse_pressed(int x, int y) 
{
}


void CarOBDII::mouse_released(int x, int y) 
{
}


void CarOBDII::action_right() 
{
}


void CarOBDII::action_left()
{
}


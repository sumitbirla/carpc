
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
#ifndef _OBDIIBaseCom
#define _OBDIIBaseCom

#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <linux/serial.h>
#include <errno.h>
//#include <sched.h>

#include "Logger.hpp"

//Error Codes.
#define NONSPECIFIC_ERROR   -1
#define TIMEOUT_ERROR       -8

/*
 * Structure for maintaining Serial port state.
 */
typedef struct serial_port_state
{
	struct serial_struct serial_info;
	struct termios termios_info;
    char device_name[1024];
	int modem_flags;
    int dtr;
    int rts;
    int speed;
    int bits;
    int stop_bits;
    int par_flag;
    int fd;
} SerialPortState;

/**
* This class wraps basic ioctl system calls for the OBDII interface.
*/ 
class OBDIIBaseCom {

public:
   OBDIIBaseCom(Logger *logger);
   ~OBDIIBaseCom();

   /* Get current serial port state. */
   int get_serial_state(int fd, SerialPortState *serial_port_state);

   /* Restore serial port state to pre-scan state */
   int set_serial_state(int fd, SerialPortState *serial_port_state);

   /**
   * Set the "Set" and "Clear" Serial DTR and RTS Pins with passed values.
   * Note:  DTR is Data Transmission Read.  This pin is used to tell
   *        the device to which we're connected whether we're ready to .
   *        RTS is Request to Send.  This pin is used to indicate
   *        to the device to which we're connected whether we're ready to send.
   */
   int set_serial_state_control(int fd, SerialPortState *serial_port_state);
   
   /**
   * Reads from the serial port.
   * Note:  This read is non-interruptible and has a timeout in ms.
   *        If timout is 0, read is non-blocking.
   */
   ssize_t serial_read(int fd, void *buf, size_t count, int timeout);

private:
    class Logger *logger;
};


#endif


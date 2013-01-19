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

#include "OBDIIBaseCom.hpp"


OBDIIBaseCom::OBDIIBaseCom(Logger *logger)
{
    this->logger = logger;
    logger->log(DEBUG, "OBDIIBaseCom::OBDIIBaseCom", "Entering");


    logger->log(DEBUG, "OBDIIBaseCom::OBDIIBaseCom", "Exiting");
}

OBDIIBaseCom::~OBDIIBaseCom()
{
    logger->log(DEBUG, "OBDIIBaseCom::~OBDIIBaseCom", "Entering");


    logger->log(DEBUG, "OBDIIBaseCom::~OBDIIBaseCom", "Exiting");
}

/************************************************************************
*                              Timer Methods                            *
*************************************************************************/


/************************************************************************
*                          Serial Port Methods                          *
*************************************************************************/

/**
* Gets the current state of the serial device.
**/
int OBDIIBaseCom::get_serial_state(int fd, SerialPortState *serial_port_state)
{
    logger->log(DEBUG, "OBDIIBaseCom::get_serial_state", "Entering");

    // Serial
	if (ioctl(fd, TIOCGSERIAL, &serial_port_state->serial_info) < 0) {
        logger->log(ERROR, "OBDIIBaseCom::get_serial_state", "TIOCGSERIAL failed.");
		return (-1);
	}

    // Termios
	if (ioctl(fd, TIOCMGET, &serial_port_state->modem_flags) < 0) {
        logger->log(ERROR, "OBDIIBaseCom::get_serial_state", "TIOCMGET failed.");
		return (-1);
	}

	if (ioctl(fd, TCGETS, &serial_port_state->termios_info) < 0) {
        logger->log(ERROR, "OBDIIBaseCom::get_serial_state", "TCGETS failed.");
		return (-1);
	}

    logger->log(DEBUG, "OBDIIBaseCom::serial_state_init", "Exiting");

	return(0);
}

/* Sets the current serial port state. */
int OBDIIBaseCom::set_serial_state(int fd, SerialPortState *serial_port_state)
{
    logger->log(DEBUG, "OBDIIBaseCom::set_serial_state", "Entering");

    //Serial
	ioctl(fd, TIOCSSERIAL, &serial_port_state->serial_info);

    //Termios
	ioctl(fd, TCSETS, &serial_port_state->termios_info);
    ioctl(fd, TIOCMSET, &serial_port_state->modem_flags);

    logger->log(DEBUG, "OBDIIBaseCom::set_serial_state", "Exiting");

	return(0);
}

/**
* Set/Clear DTR and RTS lines as specified
*/
int OBDIIBaseCom::set_serial_state_control(int fd, SerialPortState *serial_port_state)
{
    logger->log(DEBUG, "OBDIIBaseCom::set_serial_state_control", "Entering");

	int setflags = 0, clearflags = 0;

	if (&serial_port_state->dtr) {
        setflags = TIOCM_DTR;
    }   	
    else {
        clearflags = TIOCM_DTR;
    }
	if (&serial_port_state->rts) {
        setflags = TIOCM_RTS;
    }	
    else {
        clearflags = TIOCM_RTS;
    }

    // Clear
	if (ioctl(fd, TIOCMBIC, &clearflags) < 0) {
        logger->log(ERROR, "OBDIIBaseCom::set_serial_state_control", "TIOCMBIC failed.");
		return (-1);
	}

    // Set
	if (ioctl(fd, TIOCMBIS, &setflags) < 0) {
        logger->log(ERROR, "OBDIIBaseCom::set_serial_state_control", "TIOCMBIS failed.");
		return (-1);
	}

    logger->log(DEBUG, "OBDIIBaseCom::set_serial_state_control", "Exiting");

	return(0);
}

/**
* Reads from the serial port.
* Note:  This read is non-interruptible and has a timeout in ms.
*        If timout is 0, read is non-blocking.
*/
ssize_t OBDIIBaseCom::serial_read(int fd, void *buf, size_t count, int timeout)
{
	fd_set set;
	int rv;
	struct timeval tv;

	FD_ZERO(&set);
	FD_SET(fd, &set);
	tv.tv_sec = timeout / 1000;
	tv.tv_usec = (timeout % 1000) * 1000;

	/**
	* Do a select() with a timeout
	* - Portability :- select on linux updates the timeout when
	* it is interrupted.  It does get interrupted because of the timer
	* running regularly.
	*/
	while ((rv = select(fd + 1, &set, NULL, NULL, &tv)) < 0 )
	{
		if (errno == EINTR)
			continue;
	}
	switch (rv)
	{
	case 0:
		/* Timeout */
		return(TIMEOUT_ERROR);
	case 1:
		/* Ready for read */
		rv = 0;
		if (count)
			rv = read(fd, buf, count);
		return(rv);

	default:
		/* Non-specific Error */
		return(NONSPECIFIC_ERROR);
	}
}



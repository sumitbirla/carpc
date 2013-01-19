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

#ifndef _CAR_APP
#define _CAR_APP

/* Main screen size constants */
#define SCREEN_WIDTH     640
#define SCREEN_HEIGHT    480
#define MARGIN           2
#define BUTTON_WIDTH     68
#define BUTTON_HEIGHT    68

/* left column button constants */
#define MUTE            0
#define UP              1
#define DOWN            2
#define RIGHT           3
#define LEFT            4
#define MENU            5
#define QUIT            6

/* module status codes */
#define INACTIVE        0
#define ACTIVE          1
//#define ERROR           2

/* Global booleans for readibility */
#define TRUE            1
#define FALSE           0


class CarApp {
public:
   IDirectFB *dfb;
   IDirectFBSurface *client_surface; 

private:
    IDirectFBSurface *background, *primary;
    IDirectFBDisplayLayer  *layer;
    IDirectFBFont *button_font;  
    int current_selection;
    int mouse_x, mouse_y;
    int quit;
    class CarModule *currentModule;
    class CarModule *carDefault;
    class CarMenu   *carMenu;
    class CarRadio  *carRadio;
    class CarMP3    *carMp3;
    class CarOBDII  *carObdii;
    class CarGPS    *carGps;
    class VolumeControl *sound;
    class Logger    *logger;

public:
    CarApp::CarApp(int argc, char *argv[]);
    CarApp::~CarApp();
    void run_event_loop();
    void draw_skeleton();
	void draw_buttons(int selection);
    void set_current_selection(int selection);
    int get_current_selection();
    void draw_current_selection();

private:
	void mouse_pressed(int x, int y);
    void mouse_released(int x, int y);
};

#endif

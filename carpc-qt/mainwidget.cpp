#include <qapplication.h>
#include "mainwidget.h"
#include "flatbutton.h"


MainWidget::MainWidget( int width, int height, QWidget *parent, const char *name )
        : QWidget( parent, name )
{
    button_width = height / 6;
	button_height = button_width;

    vol = new VolumeControl();
    
	/* Create the common button in the left column */
    FlatButton *button = new FlatButton(FlatButton::Toggle, "Mute", this,0);
    button->setToggleColor(200, 94, 94);
    button->setHiliteColor(255, 120, 120);
    button->setGeometry(0, 0, button_width, button_height);
    connect(button, SIGNAL(toggled(int)), vol, SLOT(muteToggled(int)));
        
    button = new FlatButton(FlatButton::Up, "", this, 0);
    button->setGeometry(0, button_width, button_width, button_height); 
    connect(button, SIGNAL(clicked()), this, SLOT(upClicked()));

    button = new FlatButton(FlatButton::Down, "", this, 0);
    button->setGeometry(0, button_width * 2, button_width, button_height);
    connect(button, SIGNAL(clicked()), this, SLOT(downClicked()));
    
    button = new FlatButton(FlatButton::Left, "", this, 0);
    button->setGeometry(0,button_width * 3, button_width, button_height);
    connect(button, SIGNAL(clicked()), this, SLOT(leftClicked()));

    button = new FlatButton(FlatButton::Right, "", this, 0);
    button->setGeometry(0, button_width * 4, button_width, button_height);
    connect(button, SIGNAL(clicked()), this, SLOT(rightClicked()));

    button = new FlatButton(FlatButton::Text, "Menu", this, 0);
    button->setGeometry(0, button_width * 5, button_width, button_height);
    connect(button, SIGNAL(clicked()), this, SLOT(menuClicked()));

	/* Create the application widgets */
    radio_widget = new RadioWidget(this, "radio_widget");
    radio_widget->hide();
    radio_widget->setGeometry(button_width, 0, width - button_width, height);

    mp3_widget = new MP3Widget(this, "mp3_widget");
    mp3_widget->hide();
    mp3_widget->setGeometry(button_width, 0, width - button_width, height);

	photo_widget = new PhotoWidget(this, "photo_widget");
    photo_widget->hide();
    photo_widget->setGeometry(button_width, 0, width - button_width, height);

    apps_widget = new QWidget(this, 0);
    apps_widget->setGeometry(button_width, 0, width - button_width, height);
	apps_widget->setBackgroundColor(Qt::black);
    int app_width = (width - button_width) / 3;
    int app_height = (height - 0)/ 3;

	// Create the application launch buttons
    button = new FlatButton(FlatButton::Text, "Radio", apps_widget, "radio");
    button->setGeometry(0, 0, app_width, app_height);
    connect(button, SIGNAL(clicked()), this, SLOT(radioClicked()));

    button = new FlatButton(FlatButton::Text, "mp3", apps_widget, "mp3");
    button->setGeometry(0 + app_width, 0, app_width, app_height);
    connect(button, SIGNAL(clicked()), this, SLOT(mp3Clicked()));

    button = new FlatButton(FlatButton::Text, "GPS", apps_widget, "gps");
    button->setGeometry(0 + app_width*2, 0, app_width, app_height);
    connect(button, SIGNAL(clicked()), this, SLOT(gpsClicked()));

    button = new FlatButton(FlatButton::Text, "OBDII", apps_widget, "obdii");
    button->setGeometry(0, app_height, app_width, app_height);
    connect(button, SIGNAL(clicked()), this, SLOT(obdiiClicked()));

    button = new FlatButton(FlatButton::Text, "Internet", apps_widget, "internet");
    button->setGeometry(0 + app_width, app_height, app_width, app_height);

    button = new FlatButton(FlatButton::Text, "Phone", apps_widget, "phone");
    button->setGeometry(0 + app_width*2, app_height, app_width, app_height);
    
    button = new FlatButton(FlatButton::Text, "Contacts", apps_widget, "contacts");
    button->setGeometry(0, app_height*2, app_width, app_height);

	button = new FlatButton(FlatButton::Text, "Photos", apps_widget, "photos");
    button->setGeometry(0 + app_width, app_height*2, app_width, app_height);
	connect(button, SIGNAL(clicked()), this, SLOT(photoClicked()));
	
	button = new FlatButton(FlatButton::Text, "Linux", apps_widget, "linux");
    button->setGeometry(0 + app_width*2, app_height*2, app_width, app_height);
	connect(button, SIGNAL(clicked()), this, SLOT(linuxClicked()));

    setBackgroundColor(Qt::black);

    vol_disp = new VolumeDisplayWidget(this, 0);
    connect(vol, SIGNAL(volumeChanged(int)), vol_disp, SLOT(volumeChanged(int)));
    connect(vol, SIGNAL(volumeChanged(int)), vol_disp->bar, SLOT(setProgress(int)));
}

void MainWidget::menuClicked()
{
   radio_widget->hide();
   mp3_widget->hide();
   photo_widget->hide();
   apps_widget->show();
}

void MainWidget::upClicked()
{
   vol->volume_up();
}

void MainWidget::downClicked()
{
   vol->volume_down();
}

void MainWidget::leftClicked()
{
   QPoint pt(10,10);
   QMouseEvent evt(QEvent::MouseButtonPress, pt, Qt::NoButton, Qt::LeftButton);
   QApplication::postEvent(this, &evt);
}

void MainWidget::rightClicked()
{
   QApplication::exit( 0 );
}

void MainWidget::radioClicked()
{
   system("killall mpg123");
   apps_widget->hide();
   radio_widget->show();
   radio_widget->activate();
}

void MainWidget::mp3Clicked()
{
   radio_widget->deactivate();
   apps_widget->hide();
   mp3_widget->show();
}

void MainWidget::photoClicked()
{
   apps_widget->hide();
   mp3_widget->hide();
   photo_widget->show();
}

void MainWidget::gpsClicked()
{
}

void MainWidget::obdiiClicked()
{
}

void MainWidget::linuxClicked()
{
	QApplication::exit(0);
}








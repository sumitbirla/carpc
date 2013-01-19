#include "photowidget.h"

#include <qpainter.h>

/* 
 * The constructor instantiates all the children widgets and reads in the 
 * directory containing mp3s.  The list of files is stored in 'dir' which is 
 * a object of type QDir.
 */
PhotoWidget::PhotoWidget( QWidget *parent, const char *name )
: QWidget( parent, name )
{
   setBackgroundColor(Qt::black);

   // instantiate the buttons used for navigating mp3s

   // create buttons for tuning the radio
   FlatButton *button = new FlatButton(FlatButton::Text, "|<", this,0);
   button->setNormalColor(64, 164, 64);
   button->setHiliteColor(200, 94, 94);
   button->setGeometry(0, 430, 100, 50);
   connect(button, SIGNAL(clicked()), this, SLOT(beginClicked()));

   button = new FlatButton(FlatButton::Text, "<<", this,0);
   button->setNormalColor(64, 164, 64);
   button->setHiliteColor(100, 230, 100);
   button->setGeometry(100, 430, 100, 50);
   connect(button, SIGNAL(clicked()), this, SLOT(previousClicked()));

   button = new FlatButton(FlatButton::Toggle, "Slide Show", this,0);
   button->setNormalColor(64, 164, 64);
   button->setHiliteColor(200, 94, 94);
   button->setToggleColor(200, 94, 94);
   button->setGeometry(200, 430, 160, 50);
   connect(button, SIGNAL(toggled(int)), this, SLOT(slideshowToggled(int)));

   button = new FlatButton(FlatButton::Text, ">>", this,0);
   button->setNormalColor(64, 164, 64);
   button->setHiliteColor(100, 230, 100);
   button->setGeometry(360, 430, 100, 50);
   connect(button, SIGNAL(clicked()), this, SLOT(nextClicked()));

   button = new FlatButton(FlatButton::Text, ">|", this,0);
   button->setNormalColor(64, 164, 64);
   button->setHiliteColor(200, 94, 94);
   button->setGeometry(460, 430, 100, 50);
   connect(button, SIGNAL(clicked()), this, SLOT(endClicked()));
 
   // read in the directory containing the mp3s
   dir.setPath("/home/sumit/photos");    
   dir.setNameFilter("*.jpg");
   dir.setFilter( QDir::Files | QDir::NoSymLinks );
   dir.setSorting( QDir::Name );
   curImageIndex = 0;
}


// widget has been resized, so resize all the children appropriately
void PhotoWidget::resizeEvent ( QResizeEvent *e )
{

}


void PhotoWidget::paintEvent( QPaintEvent *)
{
	char str[256];
	QImage i;
	
	sprintf(str, "/home/sumit/photos/%s", dir[curImageIndex].ascii()); 
	i.load(str);
	img = i.smoothScale(size(), QImage::ScaleMin);
	QPainter painter(this);
    painter.drawImage(0, 0, img);
}


void PhotoWidget::beginClicked()
{
	curImageIndex = 0;
	update();
}

void PhotoWidget::previousClicked()
{
	--curImageIndex;
	if (curImageIndex < 0) 
		curImageIndex = dir.count() -1;
	update();
}

void PhotoWidget::slideshowToggled(int toggleState)
{
}

void PhotoWidget::nextClicked()
{
	++curImageIndex;
	if (curImageIndex >= dir.count())
		curImageIndex = 0;
	update();
}

void PhotoWidget::endClicked()
{
	curImageIndex = dir.count() - 1;
	update();
}

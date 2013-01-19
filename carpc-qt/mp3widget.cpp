#include "mp3widget.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "id3tag.h"


/* 
 * The constructor instantiates all the children widgets and reads in the 
 * directory containing mp3s.  The list of files is stored in 'dir' which is 
 * a object of type QDir.
 */
MP3Widget::MP3Widget( QWidget *parent, const char *name )
: QWidget( parent, name )
{
   setBackgroundColor(Qt::black);

   // instantiate the buttons used for navigating mp3s

   FlatButton *button = new FlatButton(FlatButton::Text, "|<", this,0);
   button->setNormalColor(64, 164, 64);
   button->setHiliteColor(100, 230, 100);
   button->setGeometry(0, 430, 100, 50);
   connect(button, SIGNAL(clicked()), this, SLOT(firstPageClicked()));

   button = new FlatButton(FlatButton::Text, "<<", this,0);
   button->setNormalColor(64, 164, 64);
   button->setHiliteColor(100, 230, 100);
   button->setGeometry(100, 430, 100, 50);
   connect(button, SIGNAL(clicked()), this, SLOT(prevPageClicked()));

   button = new FlatButton(FlatButton::Toggle, "Random", this,0);
   button->setNormalColor(64, 164, 64);
   button->setHiliteColor(200, 94, 94);
   button->setToggleColor(200, 94, 94);
   button->setGeometry(200, 430, 160, 50);
   connect(button, SIGNAL(toggled(int)), this, SLOT(randomToggled(int)));

   button = new FlatButton(FlatButton::Text, ">>", this,0);
   button->setNormalColor(64, 164, 64);
   button->setHiliteColor(100, 230, 100);
   button->setGeometry(360, 430, 100, 50);
   connect(button, SIGNAL(clicked()), this, SLOT(nextPageClicked()));

   button = new FlatButton(FlatButton::Text, ">|", this,0);
   button->setNormalColor(64, 164, 64);
   button->setHiliteColor(100, 230, 100);
   button->setToggleColor(200, 94, 94);
   button->setGeometry(460, 430, 100, 50);
   connect(button, SIGNAL(clicked()), this, SLOT(lastPageClicked()));

   // instantiate the MusicButtons and connect the clicked() signal
   for (int i = 0; i < 10; i++)
   {
      mbutton[i] = new MusicButton(i, this, 0);
      connect(mbutton[i], SIGNAL(clicked(int)), this, SLOT(mp3selected(int)));
   }

   // read in the directory containing the mp3s
   dir.setPath("/home/sumit/music");    
   dir.setNameFilter("*.mp3");
   dir.setFilter( QDir::Files | QDir::NoSymLinks );
   dir.setSorting( QDir::Name );

   // initialize class variables
   //process.setWorkingDirectory(dir);
   curPage = 0;
   numPages = dir.count()/10; 
   isRandom = FALSE;

   // display the first page of mp3s
   displayCurrentPage();
}


// widget has been resized, so resize all the children appropriately
void MP3Widget::resizeEvent ( QResizeEvent * )
{
   QRect r  = rect();
   int w = r.right()/2;
   int h = (r.bottom()-50)/5;
   int row, col;

   for (col=0; col < 2; col++)
   {
      for (row = 0; row < 5; row++)
      {
         mbutton[col*5+row]->setGeometry(col*w, row*h, w, h); 
      }
   }
}


// a song was selected, so play it
// TO DO:  use QProcess instead of system()
void MP3Widget::mp3selected(int i)
{
   char str[256];
   sprintf(str, "mpg123 \"/home/sumit/music/%s\" &", dir[curPage*10+i].ascii());
   system("killall mpg123");
   system(str);
}


// diplay the first page of songs
void MP3Widget::firstPageClicked()
{
   curPage = 0;
   displayCurrentPage();
}


// diplay the last page of songs
void MP3Widget::lastPageClicked()
{
   curPage = numPages;
   displayCurrentPage();
}


// set flag to indicate that songs must be played in random order
void MP3Widget::randomToggled(int toggleState)
{
   if (toggleState == 1)
      isRandom = TRUE;
   else
      isRandom = FALSE;
}


// display the previous page if not at the first page
void MP3Widget::prevPageClicked()
{
   if (curPage == 0) return;

   --curPage;
   displayCurrentPage();
}


// display the next page if not already at the last page
void MP3Widget::nextPageClicked()
{
   if (curPage == numPages)  return;
   
   ++curPage;
   displayCurrentPage();
}


/*
 * This method displays the titles of 10 songs per page based on the current 
 * page number (curPage). It uses the ID3Tag class to read the artist and 
 * title information of each mp3 and displays it in individual MusicButtons. 
 * If ID3 information is not present, the filename is displayed instead. 
 */
void MP3Widget::displayCurrentPage()
{
   char str[256];
   int fd, btn_index = 0;
   bool isGood;
   ID3Tag tag;

   // loop through the 10 songs to be displayed on this page
   for (int i=curPage*10; i < curPage*10 + 10; i++)
   {
      // if past the last song, then fill MusicButton with blanks
      if (i > dir.count()-1)
      {
         mbutton[btn_index]->setTitle("");
         mbutton[btn_index]->setArtist("");
      }
      else 
      {
         // open the file for reading the ID3 tags
         sprintf(str, "/home/sumit/music/%s", dir[i].ascii()); 
         fd = open(str, O_RDONLY);
         if (fd > 0)
         {
            isGood = tag.read(fd);
            if (isGood == TRUE)
            {
               mbutton[btn_index]->setTitle((const char *)tag.title());
               mbutton[btn_index]->setArtist((const char *)tag.artist());
            }
            // if tags were unreadable, print filename instead
            else   
            {
               mbutton[btn_index]->setTitle(dir[i]);
               mbutton[btn_index]->setArtist("");
            }
         }
         // File read failed for unknown reason
         else
         {
            mbutton[btn_index]->setTitle("File read error");
            mbutton[btn_index]->setArtist("");
         }
      }

      //repaint the MusicButton
      mbutton[btn_index]->update();
      ++btn_index;
   }
}

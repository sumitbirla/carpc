#ifndef MP3WIDGET_H
#define MP3WIDGET_H

#include "musicbutton.h"
#include "flatbutton.h"

#include <qdir.h>


class MP3Widget : public QWidget
{
   Q_OBJECT

   public:
      MP3Widget( QWidget *parent=0, const char *name=0 );

   public slots:
      void mp3selected(int);
      void firstPageClicked();
      void lastPageClicked();
      void nextPageClicked();
      void prevPageClicked();
      void randomToggled(int);

   protected:
      void resizeEvent(QResizeEvent *);

   private:
      void displayCurrentPage();

   private:
      MusicButton *mbutton[10];
      QDir dir;
      int curPage, numPages;
      bool isRandom;
};


#endif


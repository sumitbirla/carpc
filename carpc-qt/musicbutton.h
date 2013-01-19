#ifndef MUSICBUTTON_H
#define MUSICBUTTON_H

#include <qwidget.h>
#include <qcolor.h>


class MusicButton : public QWidget{
   Q_OBJECT

   public:
      MusicButton( int i, QWidget *parent=0, const char *name=0 );
      void setArtist( QString _artist);
      void setTitle( QString _title);
      void setLength( QString _len);
   
   signals:
      void clicked(int);
      
   protected:
      void paintEvent(QPaintEvent *);
      void mousePressEvent(QMouseEvent *);
      void mouseReleaseEvent(QMouseEvent *);

   private:
      enum State {Released, Pressed};
      State currentState;
      QColor normalColor, hiliteColor, titleColor;
      QColor subtitleColor, infoColor;
      QFont small_font, large_font;
      QString artist, title, len;
      int index;
};


#endif


#include "musicbutton.h"
#include <qpainter.h>

MusicButton::MusicButton( int i, QWidget *parent, const char *name )
        : QWidget( parent, name )
{
   currentState = Released;
   index = i;

   normalColor.setRgb(77, 96, 136);
   hiliteColor.setRgb(120, 130, 236);
   large_font.setPointSize(24);
   large_font.setBold(true);
   small_font.setPointSize(14);
   setFont(large_font);

   artist = "";
   title = "";
   len = "";
}

void MusicButton::setArtist(QString _artist)
{
   artist = _artist;
}

void MusicButton::setTitle(QString _title)
{
   title = _title;
}

void MusicButton::setLength(QString _len)
{
   len = _len;
}

void MusicButton::paintEvent(QPaintEvent *)
{
   QPainter qpainter( this );
   
   QRect r = rect();
   
   if (currentState == Pressed)
      qpainter.setBrush(hiliteColor);
   else
      qpainter.setBrush(normalColor);

   qpainter.drawRect(r);
   
   setFont(large_font);
   qpainter.setPen(Qt::yellow);
   qpainter.drawText(10, 30, title, 0, -1);
   //setFont(small_font);
   qpainter.setPen(Qt::white);
   qpainter.drawText(10, 65, artist, 0, -1);   
   //qpainter.drawText(r.right()-55, 75, len, 0, -1);
}


void MusicButton::mousePressEvent(QMouseEvent *)
{
   currentState = Pressed;
   repaint(false);
}

void MusicButton::mouseReleaseEvent(QMouseEvent *)
{
   currentState = Released;
   repaint(false);
   emit clicked(index);
}





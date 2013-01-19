#include "flatbutton.h"
#include <qpainter.h>

FlatButton::FlatButton( Type _type, QString _label, QWidget *parent, const char *name )
        : QWidget( parent, name )
{
   currentState = Released;
   toggleState = Off;
   buttonType = _type;
   label = _label;
   normalColor.setRgb(77, 96, 136);
   hiliteColor.setRgb(120, 130, 236);
   upDownColor.setRgb(180, 60, 60);
   leftRightColor.setRgb(100, 160, 100);
   font.setPointSize(18);
   font.setBold(true);
   setFont(font);
}


void FlatButton::paintEvent(QPaintEvent *)
{
   QPainter qpainter( this );
   
   QRect r = rect();
   
   if (currentState == Pressed)
   {
      qpainter.setBrush(hiliteColor);
   }
   else
   {
      if ((buttonType == Toggle) && (toggleState == On))
         qpainter.setBrush(toggleColor);
      else
         qpainter.setBrush(normalColor);
   }
   qpainter.drawRect(r);
   

   switch (buttonType)
   {
   case Text:
   case Toggle:
   case Radio:
      qpainter.setPen(Qt::white);
      qpainter.drawText(0, 0, r.right(), r.bottom(), AlignCenter, label, -1, 0, 0);
      break;

   case Up:
   case Down:
      qpainter.setBrush(upDownColor);
      qpainter.drawPolygon(points, false, 0, 3);
      break;

   case Left:
   case Right:
      qpainter.setBrush(leftRightColor);
      qpainter.drawPolygon(points, false, 0, 3);
      break;
   }
}


void FlatButton::mousePressEvent(QMouseEvent *)
{
   currentState = Pressed;
   if (buttonType == Toggle)
   {
      if (toggleState == Off)
         toggleState = On;
      else 
         toggleState = Off;

      emit toggled(toggleState);
   }
   repaint(false);
}

void FlatButton::mouseReleaseEvent(QMouseEvent *)
{
   currentState = Released;
   repaint(false);
   if (buttonType == Radio)
   {
      bool ok;
      emit stationSelected(label.toFloat(&ok));
   }
   else
      emit clicked();
}


void FlatButton::resizeEvent ( QResizeEvent * )
{
   QRect r = rect();
   switch (buttonType)
   {
   case Up:
      points.setPoints(3, r.right()/2, 20, 
                          20, r.bottom()-20, 
                          r.right()-20, r.bottom()-20); 
      break;

   case Down:
      points.setPoints(3, r.right()/2, r.bottom()-20, 
                          20, 20, 
                          r.right()-20, 20); 
      break;

   case Left:
      points.setPoints(3, 20, r.bottom()/2, 
                          r.right()-20, 20, 
                          r.right()-20, r.bottom()-20); 
      break;

   case Right:
      points.setPoints(3, 20,20, 
                          r.right()-20,r.bottom()/2, 
                          20,r.bottom()-20); 
      break;

   default:
      break;
   }
   
   repaint();
}

void FlatButton::untoggle()
{
   toggleState = Off;
   repaint(false);
}


void FlatButton::setNormalColor(int r, int g, int b)
{
   normalColor.setRgb(r, g, b);
}

void FlatButton::setHiliteColor(int r, int g, int b)
{
   hiliteColor.setRgb(r, g, b);
}

void FlatButton::setToggleColor(int r, int g, int b)
{
   toggleColor.setRgb(r, g, b);
}

void FlatButton::setFontSize(int size)
{
   font.setPointSize(size);
   setFont(font);
}


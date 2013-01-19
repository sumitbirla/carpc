#ifndef FLATBUTTON_H
#define FLATBUTTON_H

#include <qwidget.h>
#include <qcolor.h>
#include <qpointarray.h>


class FlatButton : public QWidget{
   Q_OBJECT

   public:
      enum Type {Text, Up, Down, Right, Left, Toggle, Radio};
      FlatButton( Type _type, QString _label, QWidget *parent=0, const char *name=0 );
      void setNormalColor(int r, int g, int b);
      void setHiliteColor(int r, int g, int b);
      void setToggleColor(int r, int g, int b);
      void setFontSize(int size);
      void untoggle();

   signals:
      void clicked();
      void stationSelected(float);
      void toggled(int);

   protected:
      void paintEvent(QPaintEvent *);
      void mousePressEvent(QMouseEvent *);
      void mouseReleaseEvent(QMouseEvent *);
      void resizeEvent(QResizeEvent *);

   private:
      enum State {Released, Pressed};
      State currentState;
      enum ToggleState {Off=0, On=1};
      ToggleState toggleState;
      Type buttonType;
      QString label;
      QColor normalColor, hiliteColor, upDownColor, leftRightColor, toggleColor;
      QFont font;
      QPointArray points;
};


#endif


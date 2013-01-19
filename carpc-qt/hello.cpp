#include <qapplication.h>              

#include "mainwidget.h"


int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    MainWidget main(640, 480, 0, 0);
    main.setGeometry(0,0,640,480);
    a.setMainWidget( &main );
    main.show();

    return a.exec();
}



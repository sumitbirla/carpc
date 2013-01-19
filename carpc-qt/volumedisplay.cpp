#include "volumedisplay.h"


VolumeDisplayWidget::VolumeDisplayWidget( QWidget *parent, const char *name )
        : QWidget( parent, name )
{
   setBackgroundColor(QColor(200, 64, 64));
   setGeometry(200, 200, 300, 100);
   bar = new QProgressBar(100, this, 0, 0);
   bar->setGeometry(20, 50, 260, 30);
   QPalette palette = bar->palette();
   palette.setColor(QPalette::Normal, QColorGroup::Foreground, Qt::white);
   palette.setColor(QPalette::Normal, QColorGroup::Background, QColor(200, 64, 64));
   palette.setColor(QPalette::Normal, QColorGroup::Light, QColor(200, 64, 64));
   palette.setColor(QPalette::Normal, QColorGroup::Dark, QColor(200, 64, 64));
   bar->setPalette(palette);
   font.setPointSize(14);
   font.setBold(true);
   bar->setFont(font);


   font.setPointSize(24);
   font.setBold(true);

   label = new QLabel("Volume", this, 0, 0);
   label->setGeometry(10, 10, 200, 30);
   label->setFont(font);

   palette = label->palette();
   palette.setColor(QPalette::Normal, QColorGroup::Foreground, Qt::white);
   palette.setColor(QPalette::Normal, QColorGroup::Background, QColor(200, 64, 64));
   label->setPalette(palette);

   timer = new QTimer(0, 0);
   connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));

   hide();
}


void VolumeDisplayWidget::volumeChanged(int new_vol)
{
   timer->stop();
   show();
   timer->start(3000, TRUE);
}

void VolumeDisplayWidget::timeout()
{
   hide();
}

#include "displayturntable.h"
#include "ui_displayturntable.h"

DisplayTurntable::DisplayTurntable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayTurntable)
{
    ui->setupUi(this);

    //Set Geometry (-60,-60) from Right-Buttom, size is 180*180
    //this->setGeometry(QApplication::desktop()->width()-240,QApplication::desktop()->height()-240,180,180);

    //Set Window Background Color R0:G0:B0 (BLACK), Opacity is 0.8
    this->setPalette(QPalette( QColor(0, 0, 0)) );
    this->setWindowOpacity(0.8);

    //Set Window Flag : Tool | Frameless | Stay On Top
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);


}

DisplayTurntable::~DisplayTurntable()
{
    delete ui;
}

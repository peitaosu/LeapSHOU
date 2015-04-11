#include "ctrl.h"
#include "ui_ctrl.h"
#include "data.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>
#include <X11/extensions/shape.h>
#include <X11/extensions/XTest.h>
#include <QtX11Extras/QX11Info>

ctrl::ctrl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ctrl)
{
    ui->setupUi(this);

    //Set Geometry (-60,-60) from Right-Buttom, size is 180*180
    this->setGeometry(QApplication::desktop()->width()-240,QApplication::desktop()->height()-240,180,180);

    //Set Window Background Color R0:G0:B0 (BLACK), Opacity is 0
    this->setPalette(QPalette( QColor(0, 0, 0)) );
    this->setWindowOpacity(0);

    //Set Window Flag : Tool | Frameless | Stay On Top
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    //New a Timer to Update PaintEvent, time is 20ms
    QTimer *mouseTimer = new QTimer(this);
    connect(mouseTimer,SIGNAL(timeout()),this,SLOT(showCTRL()));
    mouseTimer->start(20);

    //XTestFakeMotionEvent(QX11Info::display(),-1,1920,1000,0);


}

ctrl::~ctrl()
{
    delete ui;
}

void ctrl::showCTRL(){
    if(gesStatus == 123){
        //XTestFakeMotionEvent(QX11Info::display(),-1,70,50,0);
        this->setGeometry(screen_x-90,screen_y-90,180,180);
        this->setWindowOpacity(0.5);
    }else if(gesStatus == 122){
        this->setGeometry(screen_x-90,screen_y-90,180,180);
        this->setWindowOpacity(0.3);
    }else if(gesStatus == 121){
        this->setGeometry(screen_x-90,screen_y-90,180,180);
        this->setWindowOpacity(0.1);
    }else{
        this->setWindowOpacity(0);
    }
}

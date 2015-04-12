#include "ctrl.h"
#include "ui_ctrl.h"
#include "data.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>
#include <X11/extensions/shape.h>
#include <X11/extensions/XTest.h>
#include <QtX11Extras/QX11Info>

//New 2 variable to make a gesture status change event
int CTRL_c;
int CTRL_p;
//New 2 variable to save the prev mouse ptr
int mouse_x_p;
int mouse_y_p;

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
    //gesture Statu change event
    CTRL_p = CTRL_c;
    CTRL_c = gesStatus;

    //make a visual window change
    if(gesStatus == 123){
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

    //When the CTRL change from 122 to 123, save the mouse ptr
    if(CTRL_c == 123 && CTRL_p == 122){
        //in Linux/X11, it`s screen pix
        mouse_x_p = screen_x;
        mouse_y_p = screen_y;
    }else if(CTRL_c == 120 && CTRL_p == 123){
        //Mouse Motion Event
        XTestFakeMotionEvent(QX11Info::display(),-1,mouse_x_p,mouse_y_p,0);
    }
}

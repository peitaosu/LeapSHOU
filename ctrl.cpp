#include "ctrl.h"
#include "ui_ctrl.h"
#include "data.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>
#include <X11/extensions/shape.h>
#include <X11/extensions/XTest.h>
#include <QtX11Extras/QX11Info>
#include "getwmname.h"
//New 2 variable to make a gesture status change event
int CTRL_c;
int CTRL_p;
//New 2 variable to save the prev mouse ptr
int mouse_x_p;
int mouse_y_p;

ctrl::ctrl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ctrl){

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

    //GetWMName
    int g = GetWMName();
    std::cout<<g<<std::endl;

}

ctrl::~ctrl(){
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
        //XTestFakeMotionEvent(QX11Info::display(),-1,mouse_x_p,mouse_y_p,0);

        //Judge the direction
        int slope = (screen_y - mouse_y_p)/(screen_x - mouse_x_p);
        //Left & Right
        if(slope < 1 && slope > -1){
            if(screen_x - mouse_x_p > 0){
                //RIGHT
                //Move the mouse to Prev position
                //XTestFakeMotionEvent(QX11Info::display(),-1,mouse_x_p,mouse_y_p,0);
                //Press and Release the Left button
                /* 1,Left botton   *
                 * 2,Middle botton *
                 * 3,Right botton  */
                //XTestFakeButtonEvent(QX11Info::display(),3,true,0);
                //XTestFakeButtonEvent(QX11Info::display(),3,false,0);
            }else{
                //LEFT
                //Move the mouse to Prev position
                //XTestFakeMotionEvent(QX11Info::display(),-1,mouse_x_p,mouse_y_p,0);
                //Press and Release the Left button
                //XTestFakeButtonEvent(QX11Info::display(),1,true,0);
                //XTestFakeButtonEvent(QX11Info::display(),1,false,0);

            }
        //Top & Bottom
        }else if(slope > 1 || slope < -1){
            if(screen_y - mouse_y_p > 0){
                //TOP
                this->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0.5 rgba(255, 0, 0, 255), stop:0.501 rgba(64, 0, 255, 255));");

            }else{
                //BOTTOM
                this->setStyleSheet("background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:0, stop:0.5 rgba(255, 0, 0, 255), stop:0.501 rgba(64, 0, 255, 255));");

            }
        }
    }
}

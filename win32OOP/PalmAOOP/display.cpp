#include "display.h"
#include "ui_display.h"
#include <Windows.h>
#include <iostream>
#include <QApplication>
#include <QDesktopWidget>


#define GRABSTART_SHOW 111
#define GRABKEEP_SHOW 112
#define GRABSTOP_SHOW 110
#define PINCHSTART_SHOW 121
#define PINCHKEEP_SHOW 122
#define PINCHSTOP_SHOW 120
#define HOLDSTART_SHOW 131
#define HOLDKEEP_SHOW 132
#define HOLDDONE_SHOW 133
#define HOLDSTOP_SHOW 130
#define CIRCLESTART_SHOW 141
#define CIRCLEKEEP_SHOW 142
#define CIRCLESTOP_SHOW 140
#define CIRCLEANTISTART_SHOW 151
#define CIRCLEANTIKEEP_SHOW 152
#define CIRCLEANTISTOP_SHOW 150

Display::Display(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Display)
{
    ui->setupUi(this);
    //Set Geometry (-60,-60) from Right-Buttom, size is 180*180
    this->setGeometry(QApplication::desktop()->width()-240,QApplication::desktop()->height()-240,180,180);

    //Set Window Background Color R0:G0:B0 (BLACK), Opacity is 0.8
    this->setPalette(QPalette( QColor(0, 0, 0)) );
    this->setWindowOpacity(0.8);

    //Set Window Flag : Tool | Frameless | Stay On Top
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    SetWindowLong((HWND)winId(), GWL_EXSTYLE, GetWindowLong((HWND)winId(), GWL_EXSTYLE) |
                  WS_EX_TRANSPARENT | WS_EX_LAYERED);

    connect(this,SIGNAL(delayShowS()),this,SLOT(delayShow()));
    connect(this,SIGNAL(delayHideS()),this,SLOT(delayHide()));
    current_time = QTime::currentTime();

    DS.show();

}

Display::~Display()
{
    delete ui;
}

void Display::DTTurntableShow(){
    dt.show();
}
void Display::DTTurntableHide(){
    dt.hide();
}
void Display::DTTurntableChange(int x, int y, int width, int height, float Opa){
    dt.setGeometry(x,y,width,height);
    dt.setWindowOpacity(Opa);
}

void Display::showGesture(int x){
    switch(x){
    case GRABSTART_SHOW:
        this->setStyleSheet("#gesture_show_label{border-image: url(:/png/gesture/fist.png);}");
        std::cout<<"GRABSTART"<<std::endl;
        break;
    case GRABKEEP_SHOW:
        this->setStyleSheet("#gesture_show_label{border-image: url(:/png/gesture/fist.png);}");
        std::cout<<"GRABKEEP"<<std::endl;
        break;
    case GRABSTOP_SHOW:
        this->setStyleSheet("#gesture_show_label{border-image: url(:/png/gesture/hand.png);}");
        std::cout<<"GRABSTOP"<<std::endl;
        break;
    case PINCHSTART_SHOW:
        this->setStyleSheet("#gesture_show_label{border-image: url(:/png/gesture/pinch.png);}");
        std::cout<<"PINCHSTART"<<std::endl;
        break;
    case PINCHKEEP_SHOW:
        this->setStyleSheet("#gesture_show_label{border-image: url(:/png/gesture/pinch.png);}");
        std::cout<<"PINCHKEEP"<<std::endl;
        break;
    case PINCHSTOP_SHOW:
        this->setStyleSheet("#gesture_show_label{border-image: url(:/png/gesture/pinche.png);}");
        std::cout<<"PINCHSTOP"<<std::endl;
        break;
    case HOLDSTART_SHOW:
        this->setStyleSheet("#gesture_show_label{border-image: url(:/png/gesture/hold.png);}");
        std::cout<<"HOLDSTART"<<std::endl;
        break;
    case HOLDKEEP_SHOW:
        this->setStyleSheet("#gesture_show_label{border-image: url(:/png/gesture/hold2.png);}");
        std::cout<<"HOLDKEEP"<<std::endl;
        break;
    case HOLDDONE_SHOW:
        this->setStyleSheet("#gesture_show_label{border-image: url(:/png/gesture/hold3.png);}");
        std::cout<<"HOLDDONE"<<std::endl;
        break;
    case HOLDSTOP_SHOW:
        this->setStyleSheet("#gesture_show_label{border-image: url(:/png/gesture/hand.png);}");
        std::cout<<"HOLDSTOP"<<std::endl;
        break;
    case CIRCLESTART_SHOW:
        this->setStyleSheet("#gesture_show_label{border-image: url(:/png/gesture/circle.png);}");
        std::cout<<"CIRCLESTART"<<std::endl;
        break;
    case CIRCLEKEEP_SHOW:
        this->setStyleSheet("#gesture_show_label{border-image: url(:/png/gesture/circle.png);}");
        std::cout<<"CIRCLEKEEP"<<std::endl;
        break;
    case CIRCLESTOP_SHOW:
        this->setStyleSheet("#gesture_show_label{border-image: url(:/png/gesture/hand.png);}");
        std::cout<<"CIRCLESTOP"<<std::endl;
        break;
    case CIRCLEANTISTART_SHOW:
        this->setStyleSheet("#gesture_show_label{border-image: url(:/png/gesture/circle.png);}");
        break;
    case CIRCLEANTIKEEP_SHOW:
        this->setStyleSheet("#gesture_show_label{border-image: url(:/png/gesture/circle.png);}");
        break;
    case CIRCLEANTISTOP_SHOW:
        this->setStyleSheet("#gesture_show_label{border-image: url(:/png/gesture/hand.png);}");
        break;
    default:
        emit delayShowS();
        break;
    }
}

void Display::delayShow(){
    for(float opa = 0;opa<0.8;){
        if(current_time.msec()%20 == 0){
            this->setWindowOpacity(opa);
            opa += 0.01;
        }
    }
}

void Display::delayHide(){
    for(float opa = 0;opa<0.8;){
        if(current_time.msec()%20 == 0){
            this->setWindowOpacity(opa);
            opa -= 0.01;
        }
    }
}


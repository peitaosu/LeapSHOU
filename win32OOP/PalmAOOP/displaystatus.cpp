#include "displaystatus.h"
#include "ui_displaystatus.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QTimer>
#include <iostream>
#include "Windows.h"
#include "lmlistenner.h"
DisplayStatus::DisplayStatus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayStatus)
{
    ui->setupUi(this);

    //Set Geometry (-60,-60) from Right-Buttom, size is 180*180
    this->setGeometry(QApplication::desktop()->width()-240,QApplication::desktop()->height()-285,180,30);

    //Set Window Background Color R0:G0:B0 (BLACK), Opacity is 0.8
    this->setPalette(QPalette( QColor(0, 0, 0)) );
    this->setWindowOpacity(0.5);

    //Set Window Flag : Tool | Frameless | Stay On Top
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    SetWindowLong((HWND)winId(), GWL_EXSTYLE, GetWindowLong((HWND)winId(), GWL_EXSTYLE) |
                  WS_EX_TRANSPARENT | WS_EX_LAYERED);

    QTimer *updateStatus = new QTimer(this);
    connect(updateStatus,SIGNAL(timeout()),this,SLOT(setStatusDisplay()));
    updateStatus->start(20);

}

DisplayStatus::~DisplayStatus()
{
    delete ui;
}

void DisplayStatus::setStatusDisplay(){
    if(!Status[0] && !Status[1] && !Status[2]){
        this->setStyleSheet("#frame_status1{background-color: rgb(0, 0, 0);}#frame_status2{background-color: rgb(0, 0, 0);}#frame_status3{background-color: rgb(0, 0, 0);}");
    }
    if(!Status[0] && !Status[1] && Status[2]){
        this->setStyleSheet("#frame_status1{background-color: rgb(0, 0, 0);}#frame_status2{background-color: rgb(0, 0, 0);}#frame_status3{background-color: rgb(0, 0, 0);}");
    }
    if(!Status[0] && Status[1] && !Status[2]){
        this->setStyleSheet("#frame_status1{background-color: rgb(0, 0, 0);}#frame_status2{background-color: rgb(0, 240, 0);}#frame_status3{background-color: rgb(0, 0, 0);}");
    }
    if(!Status[0] && Status[1] && Status[2]){
        this->setStyleSheet("#frame_status1{background-color: rgb(0, 0, 0);}#frame_status2{background-color: rgb(0, 240, 0);}#frame_status3{background-color: rgb(0, 0, 0);}");
    }
    if(Status[0] && !Status[1] && !Status[2]){
        this->setStyleSheet("#frame_status1{background-color: rgb(0, 240, 0);}#frame_status2{background-color: rgb(0, 0, 0);}#frame_status3{background-color: rgb(0, 0, 0);}");
    }
    if(Status[0] && !Status[1] && Status[2]){
        this->setStyleSheet("#frame_status1{background-color: rgb(0, 240, 0);}#frame_status2{background-color: rgb(0, 0, 0);}#frame_status3{background-color: rgb(0, 240, 0);}");
    }
    if(Status[0] && Status[1] && !Status[2]){
        this->setStyleSheet("#frame_status1{background-color: rgb(0, 240, 0);}#frame_status2{background-color: rgb(0, 240, 0);}#frame_status3{background-color: rgb(0, 0, 0);}");
    }
    if(Status[0] && Status[1] && Status[2]){
        this->setStyleSheet("#frame_status1{background-color: rgb(0, 240, 0);}#frame_status2{background-color: rgb(0, 240, 0);}#frame_status3{background-color: rgb(0, 240, 0);}");
    }
    //std::cout<<Status[0]<<Status[1]<<Status[2]<<std::endl;
}

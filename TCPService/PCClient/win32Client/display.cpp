#include "display.h"
#include "ui_display.h"
#include <QApplication>
#include <QDesktopWidget>
#include <Windows.h>
#include <QTimer>
#include <iostream>
#include "vmouse.h"
display::display(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::display)
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

//    opacityInc = 0.02;
//    maxOpacity = 0.8;
//    timerInterval = 50;
//    displayInterval = 2000;
//    isDisplay = false;
//    displayTime = 0;

//    QTimer *delayShowTimer = new QTimer(this);
//    connect(delayShowTimer,SIGNAL(timeout()),this,SLOT(delayShow()));
//    delayShowTimer->start(50);
    QTimer *Show = new QTimer(this);
    connect(Show,SIGNAL(timeout()),this,SLOT(Show()));
    Show->start(50);
}

display::~display()
{
    delete ui;
}

void display::Show()
{
    switch(vbuf[0]){
    case 48:
        ui->nolabel->setText(QString::number(0));
        break;
    case 49:
        ui->nolabel->setText(QString::number(1));
        break;
    case 50:
        ui->nolabel->setText(QString::number(2));
        break;
    case 51:
        ui->nolabel->setText(QString::number(3));
        break;
    case 52:
        ui->nolabel->setText(QString::number(4));
        break;
    case 53:
        ui->nolabel->setText(QString::number(5));
        break;
    default:
        ui->nolabel->setText(QString(""));
        break;
    }
    switch (Status) {
    case 524:
        ui->nolabel->setText(QString("U"));
        break;
    case 423:
        ui->nolabel->setText(QString("D"));
    default:
        break;
    }
}

//void display::delayShow(){
//    std::cout<<this->windowOpacity()<<","<<displayTime<<std::endl;
//    if(this->isVisible()){
//        if(!isDisplay){
//            if(this->windowOpacity() < maxOpacity){
//                this->setWindowOpacity(this->windowOpacity() + opacityInc);
//            }
//            else
//            {
//                displayTime += timerInterval;
//                if (displayTime >= displayInterval)
//                {
//                    displayTime = 0;
//                    isDisplay = true;
//                }
//            }
//        }
//        else
//        {
//            if(this->windowOpacity() > 0.0)
//            {
//                this->setWindowOpacity(this->windowOpacity() - opacityInc);
//            }
//            else
//            {
//                this->hide();
//            }
//        }
//    }
//}


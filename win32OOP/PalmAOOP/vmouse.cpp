#include "vmouse.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QPalette>
#include <QColor>
#include <QPainter>
#include <QPoint>
#include <QTimer>
#include <Windows.h>
#include <iostream>
VMouse::VMouse(QWidget *parent) : QWidget(parent)
{
    UserDeviceScreenWidth = QApplication::desktop()->width();
    UserDeviceScreenHeight= QApplication::desktop()->height();

    this->setGeometry(0,0,QApplication::desktop()->width(),QApplication::desktop()->height());
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    SetWindowLong((HWND)winId(), GWL_EXSTYLE, GetWindowLong((HWND)winId(), GWL_EXSTYLE) |
                  WS_EX_TRANSPARENT | WS_EX_LAYERED);

    QTimer *vmousePaintTimer = new QTimer(this);
    connect(vmousePaintTimer,SIGNAL(timeout()),this,SLOT(update()));
    vmousePaintTimer->start(20);
    QTimer *vmouseUpdateTimer = new QTimer(this);
    connect(vmouseUpdateTimer,SIGNAL(timeout()),this,SLOT(updateMouse()));
    vmouseUpdateTimer->start(20);


//    QTimer *screenUpdateTimer = new QTimer(this);
//    connect(screenUpdateTimer,SIGNAL(timeout()),this,SLOT(updateScreen()));
//    screenUpdateTimer->start(20);



}

VMouse::~VMouse()
{

}
void VMouse::updateMouse(){
    VMouse vm;
    LMListener ls;
    vm.mouseUpdate(ls);
    vm.screenUpdate(ls);
    std::cout<<ls.handCenter_x<<std::endl;
}

void VMouse::mouseUpdate(LMListener ls){
    mouse_x = ls.handCenter_x*65535;
    mouse_y = 65535 - ls.handCenter_y * 65535;
    std::cout<<mouse_x<<","<<mouse_y<<std::endl;
}
void VMouse::screenUpdate(LMListener ls){
    screen_x = ls.handCenter_x*UserDeviceScreenWidth;
    screen_y = (1-ls.handCenter_y)*UserDeviceScreenHeight;
}
void VMouse::paintEvent(QPaintEvent *event){
    //New painter
    QPainter painter(this);

    //Clear
    painter.fillRect(this->rect(), QColor(0,0,0,0));

    //Set Pen and Brush, Brush color is R160:G255:B200 (BLUE)
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor(00,160,255,200)));

    //Draw Ellipse, size is 50*50, position is (screen_x - 25, screen_y - 25)
    painter.drawEllipse(screen_x-15 ,screen_y-15,30,30);
}



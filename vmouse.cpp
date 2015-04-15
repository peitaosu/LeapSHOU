/***********************************************************************\
* Copyright (C) 2014-2015 Shanghai Ocean University. All rights reserved.                         *
* This is a Human-Computer Interaction System based on LEAP MOTION CONTROLLER. *
* The system can be applied on different platforms, such as Windows, Linux and Mac,    *
* programmed in C/C+, combined with Qt. It contains System API, TCP/IP, Digital Picture*
* Processing Technique and Embedded Developing and can be applied in AR/VR, Robots*
* and the Internet of things.                                                                           --TONY SU          *
\************************************************************************/

#include "vmouse.h"
#include "ui_vmouse.h"
#include <QCursor>
#include <QDesktopWidget>
#include <QPalette>
#include <QColor>
#include <QPainter>
#include <QPoint>
#include <QTimer>
#include <X11/extensions/shape.h>
#include <X11/extensions/XTest.h>
#include <QtX11Extras/QX11Info>

vmouse::vmouse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vmouse)
{
    ui->setupUi(this);

    //Set Geometry Full Sreen, Flag : Tool | Frameless | Stay On Top
    this->setGeometry(0,0,QApplication::desktop()->width(),QApplication::desktop()->height());
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    //Set Mouse Shape Input when the window stay on top, in X11/Linux
    XShapeCombineRectangles(QX11Info::display(), winId(), ShapeInput,0,0, NULL, 0, ShapeSet, YXBanded);

    //New a Timer to Update PaintEvent, time is 20ms
    QTimer *mouseTimer = new QTimer(this);
    connect(mouseTimer,SIGNAL(timeout()),this,SLOT(update()));
    mouseTimer->start(20);

}

vmouse::~vmouse()
{
    delete ui;
}

void vmouse::paintEvent(QPaintEvent *event){
    //New painter
    QPainter painter(this);

    //Clear
    painter.fillRect(this->rect(), QColor(0,0,0,0));

    //Set Pen and Brush, Brush color is R160:G255:B200 (BLUE)
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor(00,160,255,200)));

    //Draw Ellipse, size is 50*50, position is (screen_x - 25, screen_y - 25)
    painter.drawEllipse(screen_x-25 ,screen_y-25,50,50);

    //Move the RealMouse use screen position (screen_x,screen_y)
    XTestFakeMotionEvent(QX11Info::display(),-1,screen_x,screen_y,0);



}

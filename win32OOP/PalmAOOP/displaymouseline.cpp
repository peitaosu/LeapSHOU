#include "displaymouseline.h"
#include "ui_displaymouseline.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>
#include <QPainter>
#include <QPen>
#include <Windows.h>
#include <iostream>
int prevx,prevy,crtx,crty = 0;
DisplayMouseLine::DisplayMouseLine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayMouseLine)
{
    ui->setupUi(this);

    this->setGeometry(0,0,QApplication::desktop()->width(),QApplication::desktop()->height());
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    SetWindowLong((HWND)winId(), GWL_EXSTYLE, GetWindowLong((HWND)winId(), GWL_EXSTYLE) |
                  WS_EX_TRANSPARENT | WS_EX_LAYERED);

    QTimer *updateLine = new QTimer(this);
    connect(updateLine,SIGNAL(timeout()),this,SLOT(update()));
    updateLine->start(20);

}

DisplayMouseLine::~DisplayMouseLine()
{
    delete ui;
}

void DisplayMouseLine::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth (30);
    pen.setCapStyle(Qt::PenCapStyle(Qt::RoundCap));
    pen.setColor(QColor(00,160,255,200));
    painter.setPen(pen);
    painter.setBrush(QBrush(QColor(00,160,255,200)));
    //painter. drawLine( 100 , 100 , 500 , 500 );
    if(prevx!=0){
        painter. drawLine( prevx+160 , prevy+160 , crtx , crty );
    }
    std::cout<<prevx<<prevy<<crtx<<crty<<std::endl;
    //painter.drawEllipse(crtx-15 ,crty-15,30,30);
}

void DisplayMouseLine::setLine(int x1,int y1,float x2,float y2){
    prevx = x1;
    prevy = y1;
    crtx = x2 * QApplication::desktop()->width();
    crty = y2 * QApplication::desktop()->height();
}



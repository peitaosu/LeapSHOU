#include "display.h"
#include "ui_display.h"
#include <Windows.h>
#include <iostream>
#include <QApplication>
#include <QDesktopWidget>


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
    default:
        break;
    }
}


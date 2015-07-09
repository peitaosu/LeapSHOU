#include "drawgesture.h"
#include "ui_drawgesture.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QPen>
#include <Windows.h>
#include "header/Leap.h"
#include "header/fit.h"
DrawGesture::DrawGesture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawGesture)
{
    ui->setupUi(this);
    //Set Geometry (-60,-60) from Right-Buttom, size is 180*180
    this->setGeometry(QApplication::desktop()->width()/2-320,QApplication::desktop()->height()/2-240,640,480);
    //Set Window Background Color R0:G0:B0 (BLACK), Opacity is 0.8
    this->setPalette(QPalette( QColor(0, 0, 0)) );
    this->setWindowOpacity(0.8);

    //Set Window Flag : Tool | Frameless | Stay On Top
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    SetWindowLong((HWND)winId(), GWL_EXSTYLE, GetWindowLong((HWND)winId(), GWL_EXSTYLE) |
                  WS_EX_TRANSPARENT | WS_EX_LAYERED);

    QTimer *updatePoint = new QTimer(this);
    connect(updatePoint,SIGNAL(timeout()),this,SLOT(update()));
    updatePoint->start(20);

}

void DrawGesture::paintEvent(QPaintEvent *event){
    iBox = controller.frame().interactionBox();
    screen_x = iBox.normalizePoint(controller.frame().hands()[0].stabilizedPalmPosition()).x * 640;
    screen_y = (1-iBox.normalizePoint(controller.frame().hands()[0].stabilizedPalmPosition()).y) * 480;

    //New painter
    QPainter painter(this);

    //Clear
    if(!ON){
        painter.fillRect(this->rect(), QColor(0,0,0,0));
    }
    //Set Pen and Brush, Brush color is R160:G255:B200 (BLUE)
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor(00,160,255,200)));

    //Draw Ellipse, size is 50*50, position is (screen_x - 25, screen_y - 25)
    painter.drawEllipse(screen_x-15 ,screen_y-15,30,30);
}


DrawGesture::~DrawGesture()
{
    delete ui;
}

void DrawGesture::setON()
{
    this->ON = true;
}

void DrawGesture::setOFF()
{
    this->ON = false;
}

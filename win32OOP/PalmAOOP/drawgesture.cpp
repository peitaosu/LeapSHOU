#include "drawgesture.h"
#include "ui_drawgesture.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>
#include <QPainter>
#include <QPen>
#include <Windows.h>
#include "header/Leap.h"
#include "header/fit.h"
int DrawGestureStatus[3] = {0};
int dCount = 0;
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

    QTimer *drawGesture = new QTimer(this);
    connect(drawGesture,SIGNAL(timeout()),this,SLOT(getDrawGesture()));
    drawGesture->start(500);

    //QPixmap pix = QPixmap::grabWidget(this);
}

void DrawGesture::paintEvent(QPaintEvent *event){
    if(GR.getHandsCount() != 0){

        iBox = controller.frame().interactionBox();
        for(int i=59;i>-1;i--){
            int screen_x = iBox.normalizePoint(controller.frame(i).hands()[0].stabilizedPalmPosition()).x * 640;
            int screen_y = (1-iBox.normalizePoint(controller.frame(i).hands()[0].stabilizedPalmPosition()).y) * 480;

            //New painter
            QPainter painter(this);

            //Clear
    //        if(!START){
    //            //painter.fillRect(this->rect(), QColor(0,0,0,0));
    //        }
            painter.setPen(Qt::NoPen);
            painter.setBrush(QBrush(QColor (Qt:: yellow)));

            //Draw Ellipse, size is 50*50, position is (screen_x - 25, screen_y - 25)
            painter.drawEllipse(screen_x-15 ,screen_y-15,30,30);
        }
    }
}


DrawGesture::~DrawGesture()
{
    delete ui;
}

void DrawGesture::setSTART()
{
    this->START = true;
}

void DrawGesture::setSTOP()
{
    this->START = false;
}

void DrawGesture::getDrawGesture(){
    int gesSlope = GR.getSlope(30);
    if(GR.getHandsCount() != 0){
        if(gesSlope <= 0.2 && gesSlope >= -0.2){
            gesSlope = 1;
        }else if(gesSlope >= 0.2 && gesSlope <= 5){
            //
            gesSlope = 2;
        }else if(gesSlope >= 5 || gesSlope <= -5){
            //
            gesSlope = 3;
        }else if(gesSlope >= -5 && gesSlope <= -0.2){
            //
            gesSlope = 4;
        }
        if(dCount == 0){
            DrawGestureStatus[dCount] = gesSlope;
            dCount++;
        }else{
            if(dCount == 3){
                dCount == 0;
            }else{
                if(gesSlope != DrawGestureStatus[dCount-1]){
                    DrawGestureStatus[dCount] = gesSlope;
                    dCount++;
                }else{
                    //break;
                }
            }
        }
        int DrawResult = DrawGestureStatus[0]*100+DrawGestureStatus[1]*10+DrawGestureStatus[2];
        switch(DrawResult){
        case 323:
            emit drawGesture(323);
        default:
            break;
        }
        std::cout<<DrawResult<<std::endl;
    }else{
        dCount = 0;
        DrawGestureStatus[3] = {0};
    }
}


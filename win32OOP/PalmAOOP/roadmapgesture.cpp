#include "roadmapgesture.h"
#include "ui_roadmapgesture.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>
#include <Windows.h>
#include <QPainter>
#include <QPen>

#define WindowWidth 854
#define WindowHeight 480
RoadMapGesture::RoadMapGesture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoadMapGesture)
{
    ui->setupUi(this);

    this->setGeometry(QApplication::desktop()->width()/2-WindowWidth/2,QApplication::desktop()->height()/2-WindowHeight/2,WindowWidth,WindowHeight);

    this->setPalette(QPalette( QColor(0, 0, 0)) );
    this->setWindowOpacity(0.8);

    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    SetWindowLong((HWND)winId(), GWL_EXSTYLE, GetWindowLong((HWND)winId(), GWL_EXSTYLE) |
                  WS_EX_TRANSPARENT | WS_EX_LAYERED);

    QTimer *updateRoadMap = new QTimer(this);
    connect(updateRoadMap,SIGNAL(timeout()),this,SLOT(setRoadMap()));
    updateRoadMap->start(20);

    QTimer *updateRoadMapPaint = new QTimer(this);
    connect(updateRoadMapPaint,SIGNAL(timeout()),this,SLOT(update()));
    updateRoadMapPaint->start(20);

}

RoadMapGesture::~RoadMapGesture()
{
    delete ui;
}

void RoadMapGesture::setRoadMap(){

    if(GR.getHandsCount()!=0){
        int road_map_point_x = GR.getX()*WindowWidth;
        int road_map_point_y = GR.getY()*WindowHeight;

        if(road_map_point_x>227 && road_map_point_x<327 && road_map_point_y>40 && road_map_point_y<140){
            //1
            ui->RoadMapLabel1->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>327 && road_map_point_x<427 && road_map_point_y>40 && road_map_point_y<140){
            //2
            ui->RoadMapLabel2->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>427 && road_map_point_x<527 && road_map_point_y>40 && road_map_point_y<140){
            //3
            ui->RoadMapLabel3->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>527 && road_map_point_x<627 && road_map_point_y>40 && road_map_point_y<140){
            //4
            ui->RoadMapLabel4->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>227 && road_map_point_x<327 && road_map_point_y>140 && road_map_point_y<240){
            //5
            ui->RoadMapLabel5->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>327 && road_map_point_x<427 && road_map_point_y>140 && road_map_point_y<240){
            //6
            ui->RoadMapLabel6->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>427 && road_map_point_x<527 && road_map_point_y>140 && road_map_point_y<240){
            //7
            ui->RoadMapLabel7->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>527 && road_map_point_x<627 && road_map_point_y>140 && road_map_point_y<240){
            //8
            ui->RoadMapLabel8->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>227 && road_map_point_x<327 && road_map_point_y>240 && road_map_point_y<340){
            //9
            ui->RoadMapLabel9->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>327 && road_map_point_x<427 && road_map_point_y>240 && road_map_point_y<340){
            //10
            ui->RoadMapLabel10->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>427 && road_map_point_x<527 && road_map_point_y>240 && road_map_point_y<340){
            //11
            ui->RoadMapLabel11->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>527 && road_map_point_x<627 && road_map_point_y>240 && road_map_point_y<340){
            //12
            ui->RoadMapLabel12->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>227 && road_map_point_x<327 && road_map_point_y>340 && road_map_point_y<440){
            //13
            ui->RoadMapLabel13->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>327 && road_map_point_x<427 && road_map_point_y>340 && road_map_point_y<440){
            //14
            ui->RoadMapLabel14->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>427 && road_map_point_x<527 && road_map_point_y>340 && road_map_point_y<440){
            //15
            ui->RoadMapLabel15->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>527 && road_map_point_x<627 && road_map_point_y>340 && road_map_point_y<440){
            //16
            ui->RoadMapLabel16->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>754 && road_map_point_x<854 && road_map_point_y>380 && road_map_point_y<480){
            //16
            ui->RoadMapDoneLabel->setStyleSheet("background-color: rgb(255, 255, 0)");
        }
    }else{
        ui->RoadMapLabel1->setStyleSheet("");
        ui->RoadMapLabel2->setStyleSheet("");
        ui->RoadMapLabel3->setStyleSheet("");
        ui->RoadMapLabel4->setStyleSheet("");
        ui->RoadMapLabel5->setStyleSheet("");
        ui->RoadMapLabel6->setStyleSheet("");
        ui->RoadMapLabel7->setStyleSheet("");
        ui->RoadMapLabel8->setStyleSheet("");
        ui->RoadMapLabel9->setStyleSheet("");
        ui->RoadMapLabel10->setStyleSheet("");
        ui->RoadMapLabel11->setStyleSheet("");
        ui->RoadMapLabel12->setStyleSheet("");
        ui->RoadMapLabel13->setStyleSheet("");
        ui->RoadMapLabel14->setStyleSheet("");
        ui->RoadMapLabel15->setStyleSheet("");
        ui->RoadMapLabel16->setStyleSheet("");
    }

}

void RoadMapGesture::paintEvent(QPaintEvent *event){
    if(GR.getHandsCount() != 0){
            //New painter
            QPainter painter(this);

            //Clear
            painter.fillRect(this->rect(), QColor(0,0,0,0));

            painter.setPen(Qt::NoPen);
            painter.setBrush(QBrush(QColor (Qt:: yellow)));

            //Draw Ellipse, size is 50*50, position is (screen_x - 25, screen_y - 25)
            int road_map_point_x = GR.getX()*WindowWidth;
            int road_map_point_y = GR.getY()*WindowHeight;
            painter.drawEllipse(road_map_point_x-15 ,road_map_point_y-15,30,30);

    }
}

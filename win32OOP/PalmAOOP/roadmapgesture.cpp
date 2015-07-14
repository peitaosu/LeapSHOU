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

int RoadMapStatus[17]={0};
QTimer *updateRoadMap;
QTimer *updateRoadMapPaint;
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

    updateRoadMap = new QTimer(this);
    connect(updateRoadMap,SIGNAL(timeout()),this,SLOT(setRoadMap()));
    updateRoadMap->start(20);

    updateRoadMapPaint = new QTimer(this);
    connect(updateRoadMapPaint,SIGNAL(timeout()),this,SLOT(update()));
    updateRoadMapPaint->start(20);

    //connect(this,SIGNAL(Done(int*)),this,SLOT(DoneSlot(int*)));
}
void RoadMapGesture::DoneSlot(int *RoadMap){
    //
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
            RoadMapStatus[1]=1;
            ui->RoadMapLabel1->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>327 && road_map_point_x<427 && road_map_point_y>40 && road_map_point_y<140){
            //2
            RoadMapStatus[2]=1;
            ui->RoadMapLabel2->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>427 && road_map_point_x<527 && road_map_point_y>40 && road_map_point_y<140){
            //3
            RoadMapStatus[3]=1;
            ui->RoadMapLabel3->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>527 && road_map_point_x<627 && road_map_point_y>40 && road_map_point_y<140){
            //4
            RoadMapStatus[4]=1;
            ui->RoadMapLabel4->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>227 && road_map_point_x<327 && road_map_point_y>140 && road_map_point_y<240){
            //5
            RoadMapStatus[5]=1;
            ui->RoadMapLabel5->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>327 && road_map_point_x<427 && road_map_point_y>140 && road_map_point_y<240){
            //6
            RoadMapStatus[6]=1;
            ui->RoadMapLabel6->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>427 && road_map_point_x<527 && road_map_point_y>140 && road_map_point_y<240){
            //7
            RoadMapStatus[7]=1;
            ui->RoadMapLabel7->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>527 && road_map_point_x<627 && road_map_point_y>140 && road_map_point_y<240){
            //8
            RoadMapStatus[8]=1;
            ui->RoadMapLabel8->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>227 && road_map_point_x<327 && road_map_point_y>240 && road_map_point_y<340){
            //9
            RoadMapStatus[9]=1;
            ui->RoadMapLabel9->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>327 && road_map_point_x<427 && road_map_point_y>240 && road_map_point_y<340){
            //10
            RoadMapStatus[10]=1;
            ui->RoadMapLabel10->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>427 && road_map_point_x<527 && road_map_point_y>240 && road_map_point_y<340){
            //11
            RoadMapStatus[11]=1;
            ui->RoadMapLabel11->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>527 && road_map_point_x<627 && road_map_point_y>240 && road_map_point_y<340){
            //12
            RoadMapStatus[12]=1;
            ui->RoadMapLabel12->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>227 && road_map_point_x<327 && road_map_point_y>340 && road_map_point_y<440){
            //13
            RoadMapStatus[13]=1;
            ui->RoadMapLabel13->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>327 && road_map_point_x<427 && road_map_point_y>340 && road_map_point_y<440){
            //14
            RoadMapStatus[14]=1;
            ui->RoadMapLabel14->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>427 && road_map_point_x<527 && road_map_point_y>340 && road_map_point_y<440){
            //15
            RoadMapStatus[15]=1;
            ui->RoadMapLabel15->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>527 && road_map_point_x<627 && road_map_point_y>340 && road_map_point_y<440){
            //16
            RoadMapStatus[16]=1;
            ui->RoadMapLabel16->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>754 && road_map_point_x<854 && road_map_point_y>380 && road_map_point_y<480){
            //DONE
            RoadMapStatus[0]=1;
            ui->RoadMapDoneLabel->setStyleSheet("background-color: rgb(255, 255, 0)");
//            int ROADMAP = RoadMapStatus[1]+RoadMapStatus[2]+RoadMapStatus[3];
//            emit Done(ROADMAP);
            emit Done(&RoadMapStatus[0]);
            for(int i=0;i<17;i++){
                RoadMapStatus[i] = 0;
            }
            updateRoadMap->stop();
            updateRoadMapPaint->stop();
            this->~RoadMapGesture();
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
        ui->RoadMapDoneLabel->setStyleSheet("");
        for(int i=0;i<17;i++){
            RoadMapStatus[i] = 0;
        }
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

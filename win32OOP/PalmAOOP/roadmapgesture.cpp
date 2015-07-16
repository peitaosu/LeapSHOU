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

//全局变量int型数组，下标0为是否完成的状态值，1-16为对应区域的状态值
//new integer type global variable,
//subscript 0 is a flag done or not;
//subscript 1 to 16 are blocks flag.
int RoadMapStatus[17]={0};
//添加定时器updateRoadMap，用于更新状态
//new timer named updateRoadMap, used to update status
QTimer *updateRoadMap;
//添加定时器updateRoadMapPaint，用于更新显示
//new timer named updateRoadMapPaint, used to update display
QTimer *updateRoadMapPaint;

RoadMapGesture::RoadMapGesture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoadMapGesture)
{
    ui->setupUi(this);

    //设置显示大小为854*480，位置为屏幕居中
    //set window geometry size is 854*480, in the screen middle
    this->setGeometry(QApplication::desktop()->width()/2-WindowWidth/2,QApplication::desktop()->height()/2-WindowHeight/2,WindowWidth,WindowHeight);

    //背景为黑色RGB(0,0,0)，透明度为0.8
    //window background is black (R0,G0,B0), opacity is 0.8 (0-1)
    this->setPalette(QPalette( QColor(0, 0, 0)) );
    this->setWindowOpacity(0.8);
    //设置窗体为无标题栏无边框，总是在前
    //set window flag are frameless and stay-on-top
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    //设置窗体为点击穿透
    //TRANSPARENT and LAYERED
    SetWindowLong((HWND)winId(), GWL_EXSTYLE, GetWindowLong((HWND)winId(), GWL_EXSTYLE) |
                  WS_EX_TRANSPARENT | WS_EX_LAYERED);

    //定时器timeout()信号连接到槽setRoadMap()
    //connect the timer signal timeout() to slot setRoadMap()
    updateRoadMap = new QTimer(this);
    connect(updateRoadMap,SIGNAL(timeout()),this,SLOT(setRoadMap()));
    updateRoadMap->start(20);

    //定时器timeout()信号连接到槽paint()
    //connect the timer signal timeout() to slot paint()
    updateRoadMapPaint = new QTimer(this);
    connect(updateRoadMapPaint,SIGNAL(timeout()),this,SLOT(update()));
    updateRoadMapPaint->start(20);
}
RoadMapGesture::~RoadMapGesture()
{
    delete ui;
}

void RoadMapGesture::setRoadMap(){
    //当检测到手部时
    //when get one hand or one more
    if(GR.getHandsCount()!=0){

        //转换手部坐标到窗体中的坐标
        //convert the hand position to the form
        int road_map_point_x = GR.getX()*WindowWidth;
        int road_map_point_y = GR.getY()*WindowHeight;

        //根据手部坐标所在的窗体坐标所处区间，标记相应的区块
        //according to hand`s position intervals in the form, mark the corresponding blocks
        if(road_map_point_x>227 && road_map_point_x<327 && road_map_point_y>40 && road_map_point_y<140){
            //区块1
            //block1
            RoadMapStatus[1]=1;
            ui->RoadMapLabel1->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>327 && road_map_point_x<427 && road_map_point_y>40 && road_map_point_y<140){
            //区块2
            //block2
            RoadMapStatus[2]=1;
            ui->RoadMapLabel2->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>427 && road_map_point_x<527 && road_map_point_y>40 && road_map_point_y<140){
            //区块3
            //block3
            RoadMapStatus[3]=1;
            ui->RoadMapLabel3->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>527 && road_map_point_x<627 && road_map_point_y>40 && road_map_point_y<140){
            //区块4
            //block4
            RoadMapStatus[4]=1;
            ui->RoadMapLabel4->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>227 && road_map_point_x<327 && road_map_point_y>140 && road_map_point_y<240){
            //区块5
            //block5
            RoadMapStatus[5]=1;
            ui->RoadMapLabel5->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>327 && road_map_point_x<427 && road_map_point_y>140 && road_map_point_y<240){
            //区块6
            //block6
            RoadMapStatus[6]=1;
            ui->RoadMapLabel6->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>427 && road_map_point_x<527 && road_map_point_y>140 && road_map_point_y<240){
            //区块7
            //block7
            RoadMapStatus[7]=1;
            ui->RoadMapLabel7->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>527 && road_map_point_x<627 && road_map_point_y>140 && road_map_point_y<240){
            //区块8
            //block8
            RoadMapStatus[8]=1;
            ui->RoadMapLabel8->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>227 && road_map_point_x<327 && road_map_point_y>240 && road_map_point_y<340){
            //区块9
            //block9
            RoadMapStatus[9]=1;
            ui->RoadMapLabel9->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>327 && road_map_point_x<427 && road_map_point_y>240 && road_map_point_y<340){
            //区块10
            //block10
            RoadMapStatus[10]=1;
            ui->RoadMapLabel10->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>427 && road_map_point_x<527 && road_map_point_y>240 && road_map_point_y<340){
            //区块11
            //block11
            RoadMapStatus[11]=1;
            ui->RoadMapLabel11->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>527 && road_map_point_x<627 && road_map_point_y>240 && road_map_point_y<340){
            //区块12
            //block12
            RoadMapStatus[12]=1;
            ui->RoadMapLabel12->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>227 && road_map_point_x<327 && road_map_point_y>340 && road_map_point_y<440){
            //区块13
            //block13
            RoadMapStatus[13]=1;
            ui->RoadMapLabel13->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>327 && road_map_point_x<427 && road_map_point_y>340 && road_map_point_y<440){
            //区块14
            //block14
            RoadMapStatus[14]=1;
            ui->RoadMapLabel14->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>427 && road_map_point_x<527 && road_map_point_y>340 && road_map_point_y<440){
            //区块15
            //block15
            RoadMapStatus[15]=1;
            ui->RoadMapLabel15->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>527 && road_map_point_x<627 && road_map_point_y>340 && road_map_point_y<440){
            //区块16
            //block16
            RoadMapStatus[16]=1;
            ui->RoadMapLabel16->setStyleSheet("background-color: rgb(255, 255, 0)");
        }else if(road_map_point_x>754 && road_map_point_x<854 && road_map_point_y>380 && road_map_point_y<480){
            //完成
            //DONE
            RoadMapStatus[0]=1;
            ui->RoadMapDoneLabel->setStyleSheet("background-color: rgb(255, 255, 0)");

            //发送完成信号，参数为状态值
            //emit signal, send RoadMapStatus
            emit Done(&RoadMapStatus[0]);

            //清除状态
            //clear
            for(int i=0;i<17;i++){
                RoadMapStatus[i] = 0;
            }

            //暂停定时器
            //stop timer
            updateRoadMap->stop();
            updateRoadMapPaint->stop();

            //释放资源
            //release
            this->~RoadMapGesture();
        }
    }else{
        //当设备视野中未识别到任何手部时
        //when no hand the device can get
        //清除状态
        //clear
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
    //当检测到手部时才开始绘图
    //when the device get one hand or one more, start paint
    if(GR.getHandsCount() != 0){
            //新建绘图工具
            //new painter
            QPainter painter(this);

            //清空绘图区域
            //clear
            painter.fillRect(this->rect(), QColor(0,0,0,0));

            //设置画笔和笔刷，笔刷颜色为黄色
            //set paint pen and brush, the brush color is yellow
            painter.setPen(Qt::NoPen);
            painter.setBrush(QBrush(QColor (Qt:: yellow)));

            //画点，大小为30*30，位置为(road_map_point_x-15 ,road_map_point_y-15)
            //Draw Ellipse, size is 30*30, position is (road_map_point_x-15 ,road_map_point_y-15)
            int road_map_point_x = GR.getX()*WindowWidth;
            int road_map_point_y = GR.getY()*WindowHeight;
            painter.drawEllipse(road_map_point_x-15 ,road_map_point_y-15,30,30);

    }
}

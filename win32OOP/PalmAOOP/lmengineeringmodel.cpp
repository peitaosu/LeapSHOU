#include "lmengineeringmodel.h"
#include "ui_lmengineeringmodel.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>
#include "gesturerecognition.h"
LMEngineeringModel::LMEngineeringModel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LMEngineeringModel)
{
    ui->setupUi(this);

    this->setGeometry(QApplication::desktop()->width()/2-240,QApplication::desktop()->height()/2-180,480,360);

    this->setPalette(QPalette( QColor(0, 0, 0)) );
    this->setWindowOpacity(0.8);

    this->setWindowFlags(Qt::Tool
                         //| Qt::FramelessWindowHint
                         //| Qt::WindowStaysOnTopHint
                         );
    QTimer *getInfoTimer = new QTimer(this);
    connect(getInfoTimer,SIGNAL(timeout()),this,SLOT(getInfo()));
    getInfoTimer->start(20);
}

LMEngineeringModel::~LMEngineeringModel()
{
    delete ui;
}

void LMEngineeringModel::getInfo()
{
    ui->HANDSCOUNT->setText(QString::number(GR.getHandsCount()));
    ui->X->setText(QString::number(GR.getX()));
    ui->Y->setText(QString::number(GR.getY()));
    ui->Z->setText(QString::number(GR.getZ()));
    if(GR.gesGrabRight()){
        ui->GRAB->setText(QString("YES"));
    }else{
        ui->GRAB->setText(QString("NO"));
    }
    if(GR.gesPinchRight()){
        ui->PINCH->setText(QString("YES"));
    }else{
        ui->PINCH->setText(QString("NO"));
    }
    if(GR.gesHoldRight()){
        ui->HOLD->setText(QString("YES"));
    }else{
        ui->HOLD->setText(QString("NO"));
    }
    if(GR.gesCircle()){
        ui->CIRCLE->setText(QString("YES"));
    }else{
        ui->CIRCLE->setText(QString("NO"));
    }
    if(GR.gesCircleAnti()){
        ui->ANTICIRCLE->setText(QString("YES"));
    }else{
        ui->ANTICIRCLE->setText(QString("NO"));
    }
}



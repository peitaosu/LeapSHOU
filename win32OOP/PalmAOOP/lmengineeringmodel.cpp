#include "lmengineeringmodel.h"
#include "ui_lmengineeringmodel.h"
#include <QApplication>
#include <QDesktopWidget>


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

}

LMEngineeringModel::~LMEngineeringModel()
{
    delete ui;
}



#include "gestureshow.h"
#include "ui_gestureshow.h"

GestureShow::GestureShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GestureShow)
{
    ui->setupUi(this);
}

GestureShow::~GestureShow()
{
    delete ui;
}

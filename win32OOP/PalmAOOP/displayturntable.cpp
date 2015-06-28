#include "displayturntable.h"
#include "ui_displayturntable.h"
#include <QBitmap>
#include <QPalette>
#include <QPaintEvent>
#include <QApplication>
#include <QDesktopWidget>
DisplayTurntable::DisplayTurntable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayTurntable)
{
    ui->setupUi(this);

    //Set Geometry (-60,-60) from Right-Buttom, size is 180*180
    this->setGeometry(QApplication::desktop()->width()-480,QApplication::desktop()->height()-480,400,400);

    //Set Window Background Color R0:G0:B0 (BLACK), Opacity is 0.8
    this->setPalette(QPalette( QColor(0, 0, 0)) );
    this->setWindowOpacity(0.8);

    //Set Window Flag : Tool | Frameless | Stay On Top
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    m_Pixmap.load(":/png/turntable-320.png");
    resize(320, 320);
    m_Pixmap = m_Pixmap.scaled(size());
    setAutoFillBackground(true);
    setMask( m_Pixmap.mask() );

}

DisplayTurntable::~DisplayTurntable()
{
    delete ui;
}

void DisplayTurntable::paintEvent(QPaintEvent *event){
    QPalette bgPalette = this->palette();
    bgPalette.setBrush(QPalette::Background,m_Pixmap);
    this->setPalette(bgPalette);
}

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

    m_Pixmap_desktop.load(":/png/turntable_desktop-320.png");
    m_Pixmap_filemanager.load(":/png/turntable_filemanager-320.png");
    resize(320, 320);
    m_Pixmap_desktop = m_Pixmap_desktop.scaled(size());
    m_Pixmap_filemanager = m_Pixmap_filemanager.scaled(size());
    setAutoFillBackground(true);


}

DisplayTurntable::~DisplayTurntable()
{
    delete ui;
}

void DisplayTurntable::paintEvent(QPaintEvent *event){
    QPalette bgPalette = this->palette();
    switch (this->FGWin) {
    case 1:
        bgPalette.setBrush(QPalette::Background,m_Pixmap_desktop);
        break;
    case 2:
        break;
    case 3:
        bgPalette.setBrush(QPalette::Background,m_Pixmap_filemanager);
        break;
    default:
        break;
    }


    this->setPalette(bgPalette);
}

void DisplayTurntable::showDisplayTurntable(int x,int y){
    switch (this->FGWin) {
    case 1:
        this->setMask( m_Pixmap_desktop.mask());
        break;
    case 2:
        break;
    case 3:
         this->setMask( m_Pixmap_filemanager.mask());
        break;
    default:
        break;
    }
    this->setGeometry(x,y,400,400);
    this->show();
}

void DisplayTurntable::setFGWin(int x){
    this->FGWin = x;
}

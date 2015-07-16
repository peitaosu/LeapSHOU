#include "vmouse.h"
#include "ui_vmouse.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QPalette>
#include <QColor>
#include <QPainter>
#include <QPoint>
#include <QTimer>
#include <Windows.h>

VMouse::VMouse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VMouse)
{
    ui->setupUi(this);
    //获取用户设备屏幕大小
    //get the user device screen size
    UserDeviceScreenWidth = QApplication::desktop()->width();
    UserDeviceScreenHeight= QApplication::desktop()->height();

    //设置显示大小为屏幕大小
    //set window geometry size is full screen
    this->setGeometry(0,0,QApplication::desktop()->width(),QApplication::desktop()->height());

    //透明背景
    //Translucent Background
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    //设置窗体为无标题栏无边框，总是在前
    //set window flag are frameless and stay-on-top
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    //设置窗体为点击穿透
    //TRANSPARENT and LAYERED
    SetWindowLong((HWND)winId(), GWL_EXSTYLE, GetWindowLong((HWND)winId(), GWL_EXSTYLE) |
                  WS_EX_TRANSPARENT | WS_EX_LAYERED);

    //添加定时器vmousePaintTimer，用于更新显示
    //new timer named vmousePaintTimer, used to update display
    QTimer *vmousePaintTimer = new QTimer(this);
    connect(vmousePaintTimer,SIGNAL(timeout()),this,SLOT(update()));
    vmousePaintTimer->start(20);


}

VMouse::~VMouse()
{
    delete ui;
}

void VMouse::paintEvent(QPaintEvent *event){
    //转换手部坐标到屏幕坐标
    //convert the hand position to the screen
    iBox = controller.frame().interactionBox();
    screen_x = iBox.normalizePoint(controller.frame().hands()[0].stabilizedPalmPosition()).x * UserDeviceScreenWidth;
    screen_y = (1-iBox.normalizePoint(controller.frame().hands()[0].stabilizedPalmPosition()).y) * UserDeviceScreenHeight;

    //新建绘图工具
    //new painter
    QPainter painter(this);

    //清空绘图区域
    //Clear
    painter.fillRect(this->rect(), QColor(0,0,0,0));

    //设置画笔和笔刷,笔刷颜色为R160,G255,B200（蓝色）
    //Set Pen and Brush, Brush color is R160:G255:B200 (BLUE)
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor(00,160,255,200)));

    //画点，大小为30*30，位置为(screen_x - 15, screen_y - 15)
    //Draw Ellipse, size is 30*30, position is (screen_x - 15, screen_y - 15)
    painter.drawEllipse(screen_x-15 ,screen_y-15,30,30);
}


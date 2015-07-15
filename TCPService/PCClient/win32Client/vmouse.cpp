#include "vmouse.h"
#include "ui_vmouse.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QDesktopWidget>
#include <QTimer>
#include <QCursor>
#include <QPalette>
#include <QColor>
#include <QPainter>
#include <QPoint>

#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

#define  SERVER_PORT 20000  //  define the defualt connect port id
#define  CLIENT_PORT ((20002+rand())%65536)  //  define the defualt client port as a random port
#define  VBUFFER_SIZE 10

char vbuf[VBUFFER_SIZE];
int vservfd,vclifd,vlength = 0;
int screen_x,screen_y,mouse_x,mouse_y;
char scx[] = "HELLO";
int prevrrceive = 0;
int Status = 0;
SOCKET sclient;
vmouse::vmouse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vmouse)
{
    ui->setupUi(this);

    OP = new Operate();

    //Set Geometry Full Sreen, Flag : Tool | Frameless | Stay On Top
    this->setGeometry(0,0,QApplication::desktop()->width(),QApplication::desktop()->height());
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    //New a Timer to Update PaintEvent, time is 10ms
    QTimer *mouseTimer = new QTimer(this);
    connect(mouseTimer,SIGNAL(timeout()),this,SLOT(update()));
    mouseTimer->start(10);

    WORD sockVersion = MAKEWORD(2,2);
    WSADATA data;
    if(WSAStartup(sockVersion, &data) != 0)
    {
        std::cout<<"Socket Error"<<std::endl;
        //return 0;
    }

    sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sclient == INVALID_SOCKET)
    {
        std::cout<<"invalid socket !";
        //return 0;
    }

    sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(20000);
    serAddr.sin_addr.S_un.S_addr = inet_addr("192.168.1.101");
    if (::connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
    {
        std::cout<<"connect error !";
        closesocket(sclient);
        //return 0;
    }

}

vmouse::~vmouse()
{
    delete ui;
}

void vmouse::paintEvent(QPaintEvent *event){
    int ret = recv(sclient, vbuf, 255, 0);
    if(ret > 0)
    {
       vbuf[1] = 0x00;
       std::cout<<vbuf[0]<<","<<prevrrceive<<std::endl;
       if(vbuf[0] == 52 && prevrrceive == 53){
           //5->4
           Status = 524;
           OP->keyUp();
       }else if(vbuf[0] == 52 && prevrrceive == 51){
           //4->3
           Status = 423;
           OP->keyDown();
       }else{
           Status = 0;
       }
       prevrrceive = vbuf[0];
    }
}

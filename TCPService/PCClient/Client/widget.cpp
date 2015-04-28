#include "widget.h"
#include "ui_widget.h"
#include<iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include <stdlib.h>
#include <string.h>

#include <QCursor>
#include <QDesktopWidget>
#include <QPalette>
#include <QColor>
#include <QPainter>
#include <QPoint>
#include <QTimer>
#include <X11/extensions/shape.h>
#include <X11/extensions/XTest.h>
#include <QtX11Extras/QX11Info>

#define  SERVER_PORT 20000  //  define the defualt connect port id
#define  CLIENT_PORT ((20001+rand())%65536)  //  define the defualt client port as a random port
#define  BUFFER_SIZE 1

char buf[BUFFER_SIZE];
int servfd,clifd,length = 0;
//int screen_x,screen_y,mouse_x,mouse_y;
//char scx[] = "HELLO";

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


    //Set Geometry Full Sreen, Flag : Tool | Frameless | Stay On Top
    this->setGeometry(0,0,QApplication::desktop()->width(),QApplication::desktop()->height());
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    //Set Mouse Shape Input when the window stay on top, in X11/Linux
    XShapeCombineRectangles(QX11Info::display(), winId(), ShapeInput,0,0, NULL, 0, ShapeSet, YXBanded);

    /*
    //New a Timer to Update PaintEvent, time is 10ms
    QTimer *mouseTimer = new QTimer(this);
    connect(mouseTimer,SIGNAL(timeout()),this,SLOT(update()));
    mouseTimer->start(10);
    */
    QTimer *showGesTimer = new QTimer(this);
    connect(mouseTimer,SIGNAL(timeout()),this,SLOT(showGesture()));
    showGesTimer ->start(10);

    struct  sockaddr_in servaddr,cliaddr;
    socklen_t socklen  =   sizeof (servaddr);

    if ((clifd  =  socket(AF_INET,SOCK_STREAM, 0 ))  <   0 )
      {
          printf( " create socket error!\n " );
          exit( 1 );
    }

    srand(time(NULL)); // initialize random generator

    bzero( & cliaddr, sizeof (cliaddr));
    cliaddr.sin_family  =  AF_INET;
    cliaddr.sin_port  =  htons(CLIENT_PORT);
    cliaddr.sin_addr.s_addr  =  htons(INADDR_ANY);

    bzero( & servaddr, sizeof (servaddr));
    servaddr.sin_family  =  AF_INET;
    inet_aton("127.0.0.1", & servaddr.sin_addr);
    servaddr.sin_port  =  htons(SERVER_PORT);
   // servaddr.sin_addr.s_addr = htons(INADDR_ANY);

    if  (bind(clifd, (struct sockaddr* ) &cliaddr, sizeof (cliaddr)) < 0 )
    {
           printf( " bind to port %d failure!\n " ,CLIENT_PORT);
           exit( 1 );
    }

     if (::connect(clifd,( struct  sockaddr * ) & servaddr, socklen)  <   0 )
    {
           printf( " can't connect to %s!\n ", "127.0.0.1");
           exit( 1 );
    }

}

Widget::~Widget()
{
    delete ui;
}

void Widget::showGesture(){
    length  =  recv(clifd, buf, BUFFER_SIZE, 0);
    if(length < 0){
         printf( " error comes when recieve data from server %s! ", "127.0.0.1");
         exit( 1 );
    }else{
         switch(buf){
           case "L":break;
           case "R":break;
           case "U":break;
           case "D":break;
           case "F":break;
           case "B":break;
         }
    }
}

/*
void Widget::paintEvent(QPaintEvent *event){

    /*
     *Draw the position
     *
    //New painter
    QPainter painter(this);

    //Clear
    painter.fillRect(this->rect(), QColor(0,0,0,0));

    //Set Pen and Brush, Brush color is R160:G255:B200 (BLUE)
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor(00,160,255,200)));

    //Draw Ellipse, size is 50*50, position is (screen_x - 25, screen_y - 25)
    painter.drawEllipse(screen_x-25 ,screen_y-25,50,50);

     *
     *
     *
    //Move the RealMouse use screen position (screen_x,screen_y)
    //XTestFakeMotionEvent(QX11Info::display(),-1,screen_x,screen_y,0);

    /*
     *recv screen/mouse position
     *
    strncpy(scx,buf,5);
    screen_x = atoi(scx)%10000;
    strncpy(scx,buf+5,5);
    screen_y = atoi(scx)%10000;

    strncpy(scx,buf+10,5);
    mouse_x = atoi(scx);
    strncpy(scx,buf+15,5);
    mouse_y = atoi(scx);
    std::cout<<screen_x<<","<<screen_y<<","<<mouse_x<<","<<mouse_y<<std::endl;
     *
     *
     *

    //std::cout<<buf<<std::endl;
}
*/

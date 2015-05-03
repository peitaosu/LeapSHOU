#include "vmouse.h"
#include "ui_vmouse.h"
#include<iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include <stdlib.h>
#include <string.h>

#include <QDesktopWidget>
#include <QTimer>

#include <QCursor>
#include <QPalette>
#include <QColor>
#include <QPainter>
#include <QPoint>
#include <X11/extensions/shape.h>
#include <X11/extensions/XTest.h>
#include <QtX11Extras/QX11Info>

#define  SERVER_PORT 20000  //  define the defualt connect port id
#define  CLIENT_PORT ((20002+rand())%65536)  //  define the defualt client port as a random port
#define  VBUFFER_SIZE 10

char vbuf[VBUFFER_SIZE];
int vservfd,vclifd,vlength = 0;
int screen_x,screen_y,mouse_x,mouse_y;
char scx[] = "HELLO";

vmouse::vmouse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vmouse)
{
    ui->setupUi(this);

    //Set Geometry Full Sreen, Flag : Tool | Frameless | Stay On Top
    this->setGeometry(0,0,QApplication::desktop()->width(),QApplication::desktop()->height());
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    //Set Mouse Shape Input when the window stay on top, in X11/Linux
    XShapeCombineRectangles(QX11Info::display(), winId(), ShapeInput,0,0, NULL, 0, ShapeSet, YXBanded);

    //New a Timer to Update PaintEvent, time is 10ms
    QTimer *mouseTimer = new QTimer(this);
    connect(mouseTimer,SIGNAL(timeout()),this,SLOT(update()));
    mouseTimer->start(10);

    struct  sockaddr_in servaddr,cliaddr;
    socklen_t socklen  =   sizeof (servaddr);

    if ((vclifd  =  socket(AF_INET,SOCK_STREAM, 0 ))  <   0 )
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

    if  (bind(vclifd, (struct sockaddr* ) &cliaddr, sizeof (cliaddr)) < 0 )
    {
           printf( " bind to port %d failure!\n " ,CLIENT_PORT);
           exit( 1 );
    }

     if (::connect(vclifd,( struct  sockaddr * ) & servaddr, socklen)  <   0 )
    {
           printf( " can't connect to %s!\n ", "127.0.0.1");
           exit( 1 );
    }

}

vmouse::~vmouse()
{
    delete ui;
}

void vmouse::paintEvent(QPaintEvent *event){
    vlength  =  recv(vclifd, vbuf, VBUFFER_SIZE, 0);
    if(vlength < 0){
        printf( " error comes when recieve data from server %s! ", "127.0.0.1");
        exit( 1 );
    }
    //New painter
    QPainter painter(this);

    //Clear
    painter.fillRect(this->rect(), QColor(0,0,0,0));

    //Set Pen and Brush, Brush color is R160:G255:B200 (BLUE)
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor(00,160,255,200)));

    //Draw Ellipse, size is 50*50, position is (screen_x - 25, screen_y - 25)
    painter.drawEllipse(screen_x-25 ,screen_y-25,50,50);

    //Move the RealMouse use screen position (screen_x,screen_y)
    //XTestFakeMotionEvent(QX11Info::display(),-1,screen_x,screen_y,0);

    /*
      *recv screen/mouse position
      */
      strncpy(scx,vbuf,4);
      screen_x = atoi(scx)-1000;
      strncpy(scx,vbuf+4,4);
      screen_y = atoi(scx)-1000;

      std::cout<<screen_x<<","<<screen_y<<std::endl;

    /*
     *
     */
      std::cout<<vbuf<<std::endl;
}

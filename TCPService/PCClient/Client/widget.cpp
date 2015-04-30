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

#include <QDesktopWidget>
#include <QTimer>

#include <X11/extensions/shape.h>
#include <QtX11Extras/QX11Info>

#define  SERVER_PORT 20000  //  define the defualt connect port id
#define  CLIENT_PORT ((20001+rand())%65536)  //  define the defualt client port as a random port
#define  BUFFER_SIZE 10
#define  LOGINIP "192.168.1.101"
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

    QTimer *showGesTimer = new QTimer(this);
    connect(showGesTimer,SIGNAL(timeout()),this,SLOT(showGesture()));
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
    inet_aton(LOGINIP, & servaddr.sin_addr);
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
         char cr = buf[8];
         switch(cr){
           case 'L':std::cout<<"LEFT"<<std::endl;break;
           case 'R':std::cout<<"RIGHT"<<std::endl;break;
           case 'U':std::cout<<"UP"<<std::endl;break;
           case 'D':std::cout<<"DOWN"<<std::endl;break;
           case 'F':std::cout<<"FORWARD"<<std::endl;break;
           case 'B':std::cout<<"BACKWARD"<<std::endl;break;
         default:break;
         }
    }
}


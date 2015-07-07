#include "socketreceiver.h"

#include <QTimer>
#include <QPoint>
#include <winsock2.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")

#define  SERVER_PORT 20000  //  define the defualt connect port id
#define  CLIENT_PORT ((20002+rand())%65536)  //  define the defualt client port as a random port
#define  VBUFFER_SIZE 10

char vbuf[VBUFFER_SIZE];
SOCKET sclient;

SocketReceiver::SocketReceiver(QObject *parent) :
    QObject(parent)
{
    connect(this,SIGNAL(sendUpS()),&OP,SLOT(sendUp()));
    connect(this,SIGNAL(sendDownS()),&OP,SLOT(sendDown()));
    QTimer *receiveTimer = new QTimer(this);
    connect(receiveTimer,SIGNAL(timeout()),this,SLOT(receive()));
    receiveTimer->start(10);


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

void SocketReceiver::receive(){
    int ret = recv(sclient, vbuf, 255, 0);
    if(ret > 0)
    {
       vbuf[ret] = 0x00;
       std::cout<<vbuf<<std::endl;
    }
    if(strstr(vbuf,"0")){

    }
    if(strstr(vbuf,"1")){
        emit sendUpS();
    }
    if(strstr(vbuf,"2")){

    }
    if(strstr(vbuf,"3")){

    }
    if(strstr(vbuf,"4")){
        emit sendDownS();
    }
    if(strstr(vbuf,"5")){

    }
}

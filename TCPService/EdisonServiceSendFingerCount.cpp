/******************************************************************************\
* Copyright (C) 2012-2014 Leap Motion, Inc. All rights reserved.               *
* Leap Motion proprietary and confidential. Not for distribution.              *
* Use subject to the terms of the Leap Motion SDK Agreement available at       *
* https://developer.leapmotion.com/sdk_agreement, or another agreement         *
* between Leap Motion and you, your company or other organization.             *
\******************************************************************************/

#include <iostream>
#include <string.h>
#include "Leap.h"
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <time.h>
#include <cstring>
#include <stdlib.h>

#define  SERVER_PORT 20000
#define  LENGTH_OF_LISTEN_QUEUE 1
#define  BUFFER_SIZE 1
#define  SENSITIVITY 800

using namespace Leap;

int  servfd,clifd;
struct  sockaddr_in servaddr,cliaddr;
char buf[BUFFER_SIZE];
int ctrD = -1;
int prevD = -1;

int PrevHandCount = -1;
class SampleListener : public Listener {
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    virtual void onDeviceChange(const Controller&);
    virtual void onServiceConnect(const Controller&);
    virtual void onServiceDisconnect(const Controller&);
  private:
};

void SampleListener::onInit(const Controller& controller) {

  if  ((servfd  =  socket(AF_INET,SOCK_STREAM, 0 ))  <   0 )
  {
       std::cout<<"create socket error!"<<std::endl;
       exit( 1 );
  }
  bzero( & servaddr, sizeof (servaddr));

  servaddr.sin_family  =  AF_INET;
  servaddr.sin_port  =  htons(SERVER_PORT);
  servaddr.sin_addr.s_addr  =  htons(INADDR_ANY);

  if  (bind(servfd,( struct  sockaddr * ) & servaddr, sizeof (servaddr)) < 0 )
  {
    std::cout<<"bind to port failure!"<<std::endl;
       exit( 1 );
  }
 if  (listen(servfd,LENGTH_OF_LISTEN_QUEUE)  <   0 )
  {
    std::cout<<"call listen failure!"<<std::endl;
       exit( 1 );
  }
  std::cout << "Initialized" << std::endl;

}

void SampleListener::onConnect(const Controller& controller) {
  socklen_t length  =   sizeof (cliaddr);
  clifd  =  accept(servfd,( struct  sockaddr * ) & cliaddr, & length);

  if  (clifd  <   0 )
  {
        std::cout<<"error comes when call accept!"<<std::endl;
        //break ;
  }

  std::cout << "Connected" << std::endl;
}

void SampleListener::onDisconnect(const Controller& controller) {
  std::cout << "Disconnected" << std::endl;
}

void SampleListener::onExit(const Controller& controller) {
  std::cout << "Exited" << std::endl;
}

void SampleListener::onFrame(const Controller& controller) {

  const Frame frame = controller.frame();
  std::cout<<controller.frame().currentFramesPerSecond()<<std::endl;
/*
  InteractionBox iBox = controller.frame().interactionBox();
  const Vector handCenter = iBox.normalizePoint(controller.frame().hands()[0].stabilizedPalmPosition());
  std::cout<<handCenter.x<<handCenter.y<<handCenter.z<<std::endl;

  Vector handSpeed = controller.frame().hands()[0].palmVelocity();

  if(handSpeed.x > SENSITIVITY){
      //RIGHT
      ctrD = 0;
  }else if(handSpeed.x < -SENSITIVITY){
      //LEFT
      ctrD = 1;
  }

  if(handSpeed.y > SENSITIVITY){
      //UP
      ctrD = 2;
  }else if(handSpeed.y < -SENSITIVITY){
      //DOWN
      ctrD = 3;
  }

  if(handSpeed.z > SENSITIVITY){
      //FORWARD
      ctrD = 4;
  }else if(handSpeed.z < -SENSITIVITY){
      //BACKWARD
      ctrD = 5;
  }
  std::cout<<std::endl;
  std::cout<<ctrD<<std::endl;
  if(ctrD != prevD){
    switch(ctrD){
      case(0):
        strcpy(buf,"R");
        break;
      case(1):
        strcpy(buf,"L");
        break;
      case(2):
        strcpy(buf,"U");
        break;
      case(3):
        strcpy(buf,"D");
        break;
      case(4):
        strcpy(buf,"F");
        break;
      case(5):
        strcpy(buf,"B");
        break;
    }
    send(clifd,buf,BUFFER_SIZE, 0 );
    prevD = ctrD;    
  }
  */
    int HandCount = frame.hands()[0].fingers().count();
    if(HandCount != PrevHandCount){
	switch(HandCount){
        case 1:
	    strcpy(buf,"1");break; 
	case 2:
            strcpy(buf,"2");break;
 	case 3:
            strcpy(buf,"3");break;
 	case 4:
            strcpy(buf,"4");break;
 	case 5:
            strcpy(buf,"5");break;
 	case 0:
            strcpy(buf,"0");break;
 	default:
            break;
	}
	send(clifd,buf,BUFFER_SIZE, 0 );
	PrevHandCount = HandCount;
    }
}

void SampleListener::onFocusGained(const Controller& controller) {
  std::cout << "Focus Gained" << std::endl;
}

void SampleListener::onFocusLost(const Controller& controller) {
  std::cout << "Focus Lost" << std::endl;
  close(clifd);
}

void SampleListener::onDeviceChange(const Controller& controller) {
  std::cout << "Device Changed" << std::endl;
}

void SampleListener::onServiceConnect(const Controller& controller) {
  std::cout << "Service Connected" << std::endl;
}

void SampleListener::onServiceDisconnect(const Controller& controller) {
  std::cout << "Service Disconnected" << std::endl;
}

int main(int argc, char** argv) {
  // Create a sample listener and controller
  SampleListener listener;
  Controller controller;

  // Have the sample listener receive events from the controller
  controller.addListener(listener);

  // Keep this process running until Enter is pressed
  std::cout << "Press Enter to quit..." << std::endl;
  std::cin.get();

  // Remove the sample listener when done
  controller.removeListener(listener);

  return 0;
}


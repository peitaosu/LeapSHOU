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
#include <sstream>

#define  SERVER_PORT 20000
#define  LENGTH_OF_LISTEN_QUEUE 10
#define  BUFFER_SIZE 10
#define  SCREENX 1366
#define  SCREENY 768

enum DirecGes{UP,DOWN,LEFT,RIGHTM,FORWARD,BACKWARD};

using namespace Leap;

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

const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};
const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};

int  servfd,clifd;
struct  sockaddr_in servaddr,cliaddr;
char buf[20];

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
  socklen_t length  =   sizeof (cliaddr);
  clifd  =  accept(servfd,( struct  sockaddr * ) & cliaddr, & length);

  if  (clifd  <   0 )
  {
        std::cout<<"error comes when call accept!"<<std::endl;
        //break ;
  }
  std::cout << "Initialized" << std::endl;

}

void SampleListener::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
  controller.enableGesture(Gesture::TYPE_CIRCLE);
  controller.enableGesture(Gesture::TYPE_KEY_TAP);
  controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
  controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SampleListener::onDisconnect(const Controller& controller) {
  // Note: not dispatched when running in a debugger.
  std::cout << "Disconnected" << std::endl;
}

void SampleListener::onExit(const Controller& controller) {
  std::cout << "Exited" << std::endl;
}

void SampleListener::onFrame(const Controller& controller) {

  std::cout<<"Begin Frame"<<std::endl;
  const Frame frame = controller.frame();
  //Set a InteractionBox
  InteractionBox iBox = controller.frame().interactionBox();
  //Set a HandList
  HandList hands = frame.hands();


  for(HandList::const_iterator hl = hands.begin();hl != hands.end();++hl){
      std::cout<<"Begin Hands"<<std::endl;

      //Get the 1st Hand
      const Hand hand = *hl;
      //Get the hand`s normal Vector and Direction

      /*
       *Send hands position
       */
      const Vector handCenter = iBox.normalizePoint(controller.frame().hands()[0].stabilizedPalmPosition());

      int mouse_x,mouse_y,screen_x,screen_y;

      mouse_x = handCenter.x * 65535;
      mouse_y = 65535 - handCenter.y * 65535;

      screen_x = handCenter.x*SCREENX;
      screen_y = (1-handCenter.y)*SCREENY;

      std::cout<<mouse_x<<mouse_y<<screen_x<<screen_y<<std::endl;

      std::stringstream ss;
      ss<<screen_x+1000<<screen_y+1000;
      /*
       *
       *
       */

      Vector handSpeed = controller.frame().hands()[0].palmVelocity();

      if(handSpeed.x > 1500){
        //RIGHT
        ss<<"R";
      }else if(handSpeed.x < -1500){
        //LEFT
        ss<<"L";
      }

      if(handSpeed.y > 1500){
        //UP
        ss<<"U";
      }else if(handSpeed.y < -1500){
        //DOWN
        ss<<"D";
      }

      if(handSpeed.z > 1500){
        //FORWARD
        ss<<"F";
      }else if(handSpeed.z < -1500){
        //BACKWARD
        ss<<"B";
      }

      std::string si = ss.str();
      const char *c = si.c_str();
      c = si.c_str();
      strcpy(buf,c);
      send(clifd,buf,BUFFER_SIZE, 0 );

      std::cout<<buf<<std::endl;
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
  const DeviceList devices = controller.devices();

  for (int i = 0; i < devices.count(); ++i) {
    std::cout << "id: " << devices[i].toString() << std::endl;
    std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
  }

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

  if (argc > 1 && strcmp(argv[1], "--bg") == 0)
    controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

  // Keep this process running until Enter is pressed
  std::cout << "Press Enter to quit..." << std::endl;
  std::cin.get();

  // Remove the sample listener when done
  controller.removeListener(listener);

  return 0;
}

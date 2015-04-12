/***********************************************************************\
* Copyright (C) 2014-2015 Shanghai Ocean University. All rights reserved.                         *
* This is a Human-Computer Interaction System based on LEAP MOTION CONTROLLER. *
* The system can be applied on different platforms, such as Windows, Linux and Mac,    *
* programmed in C/C+, combined with Qt. It contains System API, TCP/IP, Digital Picture*
* Processing Technique and Embedded Developing and can be applied in AR/VR, Robots*
* and the Internet of things.                                                                           --TONY SU          *
\************************************************************************/

#include "data.h"
#include <QDebug>

int Status;
int gesStatus;

int mouse_x,mouse_y;
int screen_x,screen_y;
int UserDeviceScreenWidth,UserDeviceScreenHeight;

//New 2 arrays to save every 60 Frames Data
int fitPos_x[60],fitPos_y[60];
//New 2 variables to save Points Average
int PosXM,PosYM;
//New variable to save Points Slope
double PosSlope;

int Hold[3]={0};
int hCount;
int HoldPtr[2]={0};

extern char *program_invocation_name;
extern char *program_invocation_short_name;

void NewListener::onInit(const Controller & controller){
    std::cout << "Initialized" << std::endl;
}
void NewListener::onConnect(const Controller & controller){
    std::cout << "Connected" << std::endl;
}
void NewListener::onDisconnect(const Controller & controller){
    std::cout << "Disconnected" << std::endl;
}
void NewListener::onServiceConnect(const Controller & controller){
    std::cout << "Service Connected" << std::endl;
}
void NewListener::onServiceDisconnect(const Controller & controller){
    std::cout << "Service Disconnected" << std::endl;
}
void NewListener::onExit(const Controller & controller){
    std::cout << "Exited" << std::endl;
}
void NewListener::onFrame(const Controller & controller){
    //Get frames and processing data
    const Frame frame = controller.frame();
    //Set a InteractionBox
    InteractionBox iBox = controller.frame().interactionBox();
    //Set a HandList
    HandList hands = frame.hands();

    //std::cout<<program_invocation_short_name<<std::endl;

    for(HandList::const_iterator hl = hands.begin();hl != hands.end();++hl){

        //Get the 1st Hand
        const Hand hand = *hl;
        //Get the hand`s normal Vector and Direction
        const Vector handCenter = iBox.normalizePoint(controller.frame().hands()[0].stabilizedPalmPosition());

        //Set Virtual Mouse Position
        /*
         * Mouse Position is between 65535*65535
         * base from screen Left-Top.
         */
        mouse_x = handCenter.x * 65535;
        mouse_y = 65535 - handCenter.y * 65535;

        //Set Position in User`s Device Screen
        /*
         * Screen Width and Height will changed
         * while User change their Screen
         */
        screen_x = handCenter.x*UserDeviceScreenWidth;
        screen_y = (1-handCenter.y)*UserDeviceScreenHeight;

        //Get 30 Frames Position
        if(frame.id()%30 == 0){
            //Save 60 frames 2D position (x,y) to fitPos_x and fitPos_y
            for(int p=0;p<60;p++){
                fitPos_x[p] = iBox.normalizePoint(controller.frame(p).hands()[0].stabilizedPalmPosition()).x * UserDeviceScreenWidth;
                fitPos_y[p] = iBox.normalizePoint(controller.frame(p).hands()[0].stabilizedPalmPosition()).y * UserDeviceScreenHeight;
            }
            //PolyFit
            czy::Fit fit;
            //Get every 60 points Slope
            fit.polyfit(fitPos_x,fitPos_y,60,2,true);
            PosSlope = fit.getSlope();
            //Get average X,Y
            PosXM = fit.Mean(fitPos_x,60);
            PosYM = fit.Mean(fitPos_y,60);

            //HOLD GESTURE;
            if(fitPos_x[0] >= (PosXM-5) && fitPos_x[0] <= (PosXM+5) && fitPos_y[0] >= (PosYM-5) && fitPos_y[0] <= (PosYM+5)){
                //The Point is NEAR the average 60 points;
                Hold[hCount] = 1;
                hCount++;
            }else{
                if(hCount == 0){
                    continue;
                }else{
                    Hold[0] = 0;
                    Hold[1] = 0;
                    Hold[2] = 0;
                    hCount = 0;
                }
            }
            if(Hold[0] == 1 && Hold[1] == 1 && Hold[2] == 1){
                //HOLD in a Long Time.
                gesStatus = 123;
            }else if(Hold[0] == 1 && Hold[1] == 1 && Hold[2] == 0){
                gesStatus = 122;
                HoldPtr[0] = mouse_x;
                HoldPtr[1] = mouse_y;
            }else if(Hold[0] == 1 && Hold[1] == 0 && Hold[2] == 0){
                gesStatus = 121;
            }else{
                gesStatus = 120;
            }

            std::cout<<Hold[0]<<Hold[1]<<Hold[2]<<std::endl;


        }


    }
}
void NewListener::onDeviceChange(const Controller & controller){
    std::cout << "Device Changed" << std::endl;
}
void NewListener::onFocusGained(const Controller & controller){
    std::cout << "Focus Gained" << std::endl;
}
void NewListener::onFocusLost(const Controller & controller){
    std::cout << "Focus Lost" << std::endl;
}

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
#include <list>

bool BW_CLKWS = 0;
bool BW_ATCLKWS = 0;
bool BW_LINK = 0;
bool BW_TAB = 0;

bool V_MOUSE = 1;
bool V_CTRL = 0;

bool D_MINISIZE = 1;
bool D_MAXSIZE = 1;
bool D_SWITCH = 1;

bool DESKTOP;
bool BW;


int Status;
int gesStatus;

int mouse_x,mouse_y;
int screen_x,screen_y;
int UserDeviceScreenWidth,UserDeviceScreenHeight;


//New 2 arrays to save every 60 Frames Data
int fitPos_x[60],fitPos_y[60];
/******
//New variable to save Points Slope
double PosSlope;
******/
//New 2 variables to save Points Average
int PosXM,PosYM;

int Hold[3]={0};
int hCount;
int HoldPtr[2]={0};

//extern char *program_invocation_name;
//extern char *program_invocation_short_name;
/******/

int PinchCrt = 0;
int PinchPrv = 0;
int GrabCrt = 0;
int GrabPrv = 0;
int PinchCrtD = 0;
int PinchPrvD = 0;
int GrabCrtD = 0;
int GrabPrvD = 0;

void dataListener::onInit(const Controller & controller){
    controller.enableGesture(Gesture::TYPE_CIRCLE);
    std::cout << "Initialized" << std::endl;
}
void dataListener::onConnect(const Controller & controller){
    std::cout << "Connected" << std::endl;
}
void dataListener::onDisconnect(const Controller & controller){
    std::cout << "Disconnected" << std::endl;
}
void dataListener::onServiceConnect(const Controller & controller){
    std::cout << "Service Connected" << std::endl;
}
void dataListener::onServiceDisconnect(const Controller & controller){
    std::cout << "Service Disconnected" << std::endl;
}
void dataListener::onExit(const Controller & controller){
    std::cout << "Exited" << std::endl;
}
void dataListener::onFrame(const Controller & controller){
    //Get frames and processing data
    const Frame frame = controller.frame();
    //Set a InteractionBox
    InteractionBox iBox = controller.frame().interactionBox();
    //Set a HandList
    HandList hands = frame.hands();

    std::list<int> GesList;
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



        /******/
        //Get 30 Frames Position
        if(frame.id()%30 == 0){
            //Save 60 frames 2D position (x,y) to fitPos_x and fitPos_y
            for(int p=0;p<60;p++){
                fitPos_x[p] = iBox.normalizePoint(controller.frame(p).hands()[0].stabilizedPalmPosition()).x * UserDeviceScreenWidth;
                fitPos_y[p] = iBox.normalizePoint(controller.frame(p).hands()[0].stabilizedPalmPosition()).y * UserDeviceScreenHeight;
            }
            //PolyFit
            czy::Fit fit;
            /******
            //Get every 60 points Slope
            fit.polyfit(fitPos_x,fitPos_y,60,2,true);
            PosSlope = fit.getSlope();
            ******/
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
                GesList.push_back(123);
                //gesStatus = 123;
            }else if(Hold[0] == 1 && Hold[1] == 1 && Hold[2] == 0){
                //gesStatus = 122;
                GesList.push_back(122);
                HoldPtr[0] = mouse_x;
                HoldPtr[1] = mouse_y;
            }else if(Hold[0] == 1 && Hold[1] == 0 && Hold[2] == 0){
                GesList.push_back(121);
                //gesStatus = 121;
            }else{
                GesList.push_back(120);
                //gesStatus = 120;
            }
            //std::cout<<Hold[0]<<Hold[1]<<Hold[2]<<std::endl;
        }       
    }
    /******/
    if(hands.count()==1){
        //One Hand Pinch Gesture
        PinchPrv = PinchCrt;
        if(frame.hands()[0].pinchStrength()>=0.9){
            PinchCrt = 1;
        }else{
            PinchCrt = 0;
        }
        if(PinchCrt == 1 && PinchPrv == 0){
            GesList.push_back(111);
        }else if(PinchCrt == 0 && PinchPrv == 1){
            GesList.push_back(110);
        }else if(PinchCrt == 1 && PinchPrv == 1){
            GesList.push_back(112);
        }
        //One Hand Grab Gesture
        GrabPrv = GrabCrt;
        if(frame.hands()[0].grabStrength()>=0.9){
            GrabCrt = 1;
        }else{
            GrabCrt = 0;
        }
        if(GrabCrt == 1 && GrabPrv == 0){
            GesList.push_back(131);
        }else if(GrabCrt == 0 && GrabPrv == 1){
            GesList.push_back(130);
        }else if(GrabCrt == 1 && GrabPrv == 1){
            GesList.push_back(132);
        }
    }else if(hands.count()==2){
        //Two Hand Pinch Gesture
        PinchPrvD = PinchCrtD;
        if(frame.hands()[0].pinchStrength()>=0.9 && frame.hands()[1].pinchStrength()>=0.9){
            PinchCrtD = 1;
        }else{
            PinchCrtD = 0;
        }
        if(PinchCrtD == 1 && PinchPrvD == 0){
            GesList.push_back(1111);
        }else if(PinchCrtD == 0 && PinchPrvD == 1){
            GesList.push_back(1110);
        }
        //Two Hand Grab Gesture
        GrabPrvD = GrabCrtD;
        if(frame.hands()[0].grabStrength()>=0.9 && frame.hands()[1].grabStrength()>=0.9){
            GrabCrtD = 1;
        }else{
            GrabCrtD = 0;
        }
        if(GrabCrtD == 1 && GrabPrvD == 0){
            GesList.push_back(1311);
        }else if(GrabCrt == 0 && GrabPrv == 1){
            GesList.push_back(1310);
        }else{
            GesList.push_back(1312);
        }

    }
    /******/
    for(std::list<int>::const_iterator GL= GesList.begin();GL!=GesList.end();++GL){
        int Ges = *GL;
        if(!DESKTOP){
            switch (Ges) {
            //
            case 110:
                gesStatus = 110;
                //std::cout<<110<<std::endl;
                break;
            case 111:
                gesStatus = 111;
                std::cout<<111<<std::endl;
                break;
            case 112:
                gesStatus = 112;
                //std::cout<<111<<std::endl;
                break;
            case 1110:
                gesStatus = 1110;
                //std::cout<<1110<<std::endl;
                break;
            case 1111:
                gesStatus = 1111;
                //std::cout<<1111<<std::endl;
                break;
            //
            case 130:
                gesStatus = 130;
                //std::cout<<130<<std::endl;
                break;
            case 131:
                gesStatus = 131;
                //std::cout<<131<<std::endl;
                break;
            case 132:
                gesStatus = 132;
                //std::cout<<131<<std::endl;
                break;
            //
            case 1310:
                gesStatus = 1310;
                //std::cout<<1310<<std::endl;
                break;
            case 1311:
                gesStatus = 1311;
                //std::cout<<1311<<std::endl;
                break;
            case 1312:
                gesStatus = 1312;
                //std::cout<<1311<<std::endl;
                break;
            default:
                break;
            }
        }else{
            /******/
            switch(Ges){
            case 123:
                gesStatus = 123;
                //std::cout<<123<<std::endl;
                break;
            case 122:
                gesStatus = 122;
                //std::cout<<122<<std::endl;
                break;
            case 121:
                gesStatus = 121;
                //std::cout<<121<<std::endl;
                break;
            case 120:
                gesStatus = 120;
                //std::cout<<120<<std::endl;
                break;
            }
        }
    }
    /******/

    // Get gestures
    const GestureList gestures = frame.gestures();
    for (int g = 0; g < gestures.count(); ++g) {
        Gesture gesture = gestures[g];

        switch (gesture.type()) {
        case Gesture::TYPE_CIRCLE:
        {
            CircleGesture circle = gesture;
            std::string clockwiseness;

            if (circle.pointable().direction().angleTo(circle.normal()) <= PI/2) {
                clockwiseness = "clockwise";
                //std::cout<<"clockwise"<<std::endl;
                //gesStatus = 31;

            } else {
                clockwiseness = "counterclockwise";
                //gesStatus = 32;
                //std::cout<<"ATclockwise"<<std::endl;

            }

            // Calculate angle swept since last frame
            float sweptAngle = 0;
            if (circle.state() != Gesture::STATE_START) {
                CircleGesture previousUpdate = CircleGesture(controller.frame(1).gesture(circle.id()));
                sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * PI;
            }else{
                //gesStatus = 30;
            }
            //Status = 10;
            break;
        }
        default:
            //        std::cout << std::string(2, ' ')  << "Unknown gesture type." << std::endl;
            break;
        }
    }

}
void dataListener::onDeviceChange(const Controller & controller){
    std::cout << "Device Changed" << std::endl;
}
void dataListener::onFocusGained(const Controller & controller){
    std::cout << "Focus Gained" << std::endl;
}
void dataListener::onFocusLost(const Controller & controller){
    std::cout << "Focus Lost" << std::endl;
}


#include "lmlistener.h"
#include <iostream>
void LMListener::onInit(const Controller& controller){
    std::cout<<"INIT"<<std::endl;
}

void LMListener::onConnect(const Controller& controller){

}

void LMListener::onDisconnect(const Controller& controller){

}

void LMListener::onServiceConnect(const Controller& controller){

}

void LMListener::onServiceDisconnect(const Controller& controller){

}

void LMListener::onExit(const Controller& controller){

}

void LMListener::onFrame(const Controller& controller){
    const Frame frame = controller.frame();
    InteractionBox iBox = controller.frame().interactionBox();
    //HandList hands = frame.hands();
    Hand FirstHand = frame.hands()[0];
//    handCenter = iBox.normalizePoint(FirstHand.stabilizedPalmPosition());
//    handCenter_x = handCenter.x;
//    handCenter_y = handCenter.y;
//    handCenter_z = handCenter.z;
//    std::cout<<handCenter_x<<","<<handCenter_y<<","<<handCenter_z<<std::endl;

}

void LMListener::onFocusGained(const Controller& controller){

}

void LMListener::onFocusLost(const Controller& controller){

}

void LMListener::onDeviceChange(const Controller& controller){

}

float LMListener::getHandCenterX(const Controller& controller){
    handCenter = controller.frame().interactionBox().normalizePoint(controller.frame().hands()[0].stabilizedPalmPosition());
    return handCenter.x;
}

float LMListener::getHandCenterY(const Controller& controller){
    handCenter = controller.frame().interactionBox().normalizePoint(controller.frame().hands()[0].stabilizedPalmPosition());
    return handCenter.y;
}

float LMListener::getHandCenterZ(const Controller& controller){
    handCenter = controller.frame().interactionBox().normalizePoint(controller.frame().hands()[0].stabilizedPalmPosition());
    return handCenter.z;
}

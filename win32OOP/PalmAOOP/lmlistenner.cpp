#include "lmlistenner.h"
int Status[3];

void LMListenner::onInit(const Leap::Controller & controller){
    std::cout << "Initialized" << std::endl;
    Status[3] = {0};
}
void LMListenner::onConnect(const Leap::Controller & controller){
    std::cout << "Connected" << std::endl;
    Status[0] = 1;
}
void LMListenner::onDisconnect(const Leap::Controller & controller){
    std::cout << "Disconnected" << std::endl;
    Status[0] = 0;
}
void LMListenner::onServiceConnect(const Leap::Controller & controller){
    std::cout << "Service Connected" << std::endl;
    Status[1] = 1;
}
void LMListenner::onServiceDisconnect(const Leap::Controller & controller){
    std::cout << "Service Disconnected" << std::endl;
    Status[1] = 0;
}
void LMListenner::onExit(const Leap::Controller & controller){
    std::cout << "Exited" << std::endl;
    Status[2] = 0;
}
void LMListenner::onFrame(const Leap::Controller & controller){
    std::cout << "OnFrame"<< std::endl;
    Status[2] = 1;
}
void LMListenner::onDeviceChange(const Leap::Controller & controller){
    std::cout << "Device Changed" << std::endl;
}
void LMListenner::onFocusGained(const Leap::Controller & controller){
    std::cout << "Focus Gained" << std::endl;
}
void LMListenner::onFocusLost(const Leap::Controller & controller){
    std::cout << "Focus Lost" << std::endl;
}


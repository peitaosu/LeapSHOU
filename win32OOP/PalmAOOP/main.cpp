#include <QApplication>
#include"gesturerecognition.h"
#include"debug.h"
#include "eventcontrol.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //debug d;
    EventControl E;


    return a.exec();
}

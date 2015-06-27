#include "debug.h"
#include <QTimer>
debug::debug(QObject *parent) :
    QObject(parent)
{
    QTimer *debugTimer = new QTimer(this);
    connect(debugTimer,SIGNAL(timeout()),this,SLOT(debugcout()));
    debugTimer->start(20);
    VM.show();
}

void debug::debugcout(){
    //
    //std::cout<<VM.getX()<<std::endl;
}

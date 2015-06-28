#ifndef DEBUG_H
#define DEBUG_H

#include <QObject>
#include "gesturerecognition.h"
#include "vmouse.h"
#include "fgwin.h"
#include "operate.h"
#include "display.h"
#include "displaystatus.h"
#include "lmlistenner.h"
class debug : public QObject
{
    Q_OBJECT
public:
    explicit debug(QObject *parent = 0);

signals:

public slots:
    void debugcout();

private:
    GestureRecognition GR;
    VMouse VM;
    FGWin FGW;
    //Operate OP;
    Display DP;
    DisplayStatus DS;
    Leap::Controller controller;
    LMListenner listenner;
};

#endif // DEBUG_H

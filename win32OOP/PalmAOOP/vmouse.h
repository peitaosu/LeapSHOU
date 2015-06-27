#ifndef VMOUSE_H
#define VMOUSE_H

#include <QWidget>
#include "header/Leap.h"
namespace Ui {
class VMouse;
}

class VMouse : public QWidget
{
    Q_OBJECT

public:
    explicit VMouse(QWidget *parent = 0);
    ~VMouse();
    int getX();
public slots:
    void paintEvent(QPaintEvent *event);

private:
    Ui::VMouse *ui;
    Leap::Controller controller;
    Leap::InteractionBox iBox;
    int mouse_x;
    int mouse_y;
    int screen_x;
    int screen_y;
    int UserDeviceScreenWidth;
    int UserDeviceScreenHeight;
};

#endif // VMOUSE_H

#ifndef VMOUSE_H
#define VMOUSE_H
#include "data.h"
#include <QWidget>


namespace Ui {
class vmouse;
}

class vmouse : public QWidget
{
    Q_OBJECT

public:
    explicit vmouse(QWidget *parent = 0);
    ~vmouse();

private:
    Ui::vmouse *ui;
    Leap::Controller controller;
    Leap::Listener listener;
    Leap::Frame frame;
    Leap::InteractionBox iBox;
    Leap::PointableList pointables;
    Leap::Pointable pointable;

public slots:

private slots:
    void paintEvent(QPaintEvent *event);
};

#endif // VMOUSE_H

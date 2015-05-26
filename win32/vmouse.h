#ifndef VMOUSE_H
#define VMOUSE_H

#include <QWidget>
#include "data.h"
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
    //std::list<int> GesList;

public slots:

private slots:
    void paintEvent(QPaintEvent *event);
};

#endif // VMOUSE_H

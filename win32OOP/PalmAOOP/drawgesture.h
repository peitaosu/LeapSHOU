#ifndef DRAWGESTURE_H
#define DRAWGESTURE_H
#include "header/Leap.h"

#include <QWidget>
namespace Ui {
class DrawGesture;
}

class DrawGesture : public QWidget
{
    Q_OBJECT

public:
    explicit DrawGesture(QWidget *parent = 0);
    ~DrawGesture();
public slots:
    void setON();
    void setOFF();
private:
    Ui::DrawGesture *ui;
    Leap::Controller controller;
    Leap::InteractionBox iBox;
    int mouse_x;
    int mouse_y;
    bool ON;
};

#endif // DRAWGESTURE_H

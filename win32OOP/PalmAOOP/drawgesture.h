#ifndef DRAWGESTURE_H
#define DRAWGESTURE_H
#include "header/Leap.h"
#include "gesturerecognition.h"

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
    void paintEvent(QPaintEvent *event);

signals:
    void drawGesture(int);

public slots:
    void getDrawGesture();
    void setSTART();
    void setSTOP();

private:
    Ui::DrawGesture *ui;
    Leap::Controller controller;
    Leap::InteractionBox iBox;
    int mouse_x;
    int mouse_y;
    bool START;
    GestureRecognition GR;
};

#endif // DRAWGESTURE_H

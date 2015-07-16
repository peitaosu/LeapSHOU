#ifndef ROADMAPGESTURE_H
#define ROADMAPGESTURE_H

#include <QWidget>
#include "gesturerecognition.h"

namespace Ui {
class RoadMapGesture;
}

class RoadMapGesture : public QWidget
{
    Q_OBJECT

public:
    explicit RoadMapGesture(QWidget *parent = 0);
    ~RoadMapGesture();
    void paintEvent(QPaintEvent *event);
signals:
    void Done(int *);
private slots:
    void setRoadMap();

private:
    Ui::RoadMapGesture *ui;
    GestureRecognition GR;
};

#endif // ROADMAPGESTURE_H

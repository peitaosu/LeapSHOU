#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include "displayturntable.h"
#include <QTime>
#include "displaystatus.h"

namespace Ui {
class Display;
}

class Display : public QWidget
{
    Q_OBJECT

public:
    explicit Display(QWidget *parent = 0);
    ~Display();
signals:
    void delayShowS();
    void delayHideS();
public slots:
    void DTTurntableShow();
    void DTTurntableChange(int, int, int, int, float);
    void DTTurntableHide();
    void showGesture(int);

    void delayShow();
    void delayHide();


private:
    Ui::Display *ui;
    DisplayTurntable dt;
    QTime current_time;
    DisplayStatus DS;
};

#endif // DISPLAY_H

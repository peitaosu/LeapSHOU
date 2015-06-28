#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include "displayturntable.h"
namespace Ui {
class Display;
}

class Display : public QWidget
{
    Q_OBJECT

public:
    explicit Display(QWidget *parent = 0);
    ~Display();

public slots:
    void DTTurntableShow();
    void DTTurntableChange(int, int, int, int, float);
    void DTTurntableHide();

private:
    Ui::Display *ui;
    DisplayTurntable dt;
};

#endif // DISPLAY_H

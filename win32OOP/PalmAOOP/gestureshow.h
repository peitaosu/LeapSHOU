#ifndef GESTURESHOW_H
#define GESTURESHOW_H

#include <QWidget>

namespace Ui {
class GestureShow;
}

class GestureShow : public QWidget
{
    Q_OBJECT

public:
    explicit GestureShow(QWidget *parent = 0);
    ~GestureShow();

private:
    Ui::GestureShow *ui;
};

#endif // GESTURESHOW_H

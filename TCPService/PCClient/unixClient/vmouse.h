#ifndef VMOUSE_H
#define VMOUSE_H

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

private slots:
    void paintEvent(QPaintEvent *event);

};

#endif // VMOUSE_H

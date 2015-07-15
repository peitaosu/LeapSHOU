#ifndef VMOUSE_H
#define VMOUSE_H

#include <QWidget>
#include "operate.h"

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
    Operate *OP;
private slots:
    void paintEvent(QPaintEvent *event);


};

extern char vbuf[];
extern int Status;

#endif // VMOUSE_H

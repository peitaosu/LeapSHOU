#ifndef CTRL_H
#define CTRL_H

#include <QWidget>

namespace Ui {
class ctrl;
}

class ctrl : public QWidget
{
    Q_OBJECT

public:
    explicit ctrl(QWidget *parent = 0);
    ~ctrl();

private:
    Ui::ctrl *ui;

private slots:
    void showCTRL();
};

#endif // CTRL_H

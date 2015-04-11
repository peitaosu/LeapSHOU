#ifndef GESWIN_H
#define GESWIN_H

#include <QWidget>

namespace Ui {
class GesWin;
}

class GesWin : public QWidget
{
    Q_OBJECT

public:
    explicit GesWin(QWidget *parent = 0);
    ~GesWin();

private:
    Ui::GesWin *ui;
};

#endif // GESWIN_H

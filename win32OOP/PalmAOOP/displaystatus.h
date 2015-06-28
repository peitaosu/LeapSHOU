#ifndef DISPLAYSTATUS_H
#define DISPLAYSTATUS_H

#include <QWidget>

namespace Ui {
class DisplayStatus;
}

class DisplayStatus : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayStatus(QWidget *parent = 0);
    ~DisplayStatus();
public slots:
    void setStatusDisplay();

private:
    Ui::DisplayStatus *ui;
};

#endif // DISPLAYSTATUS_H

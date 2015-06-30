#ifndef DISPLAYMOUSELINE_H
#define DISPLAYMOUSELINE_H

#include <QWidget>

namespace Ui {
class DisplayMouseLine;
}

class DisplayMouseLine : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayMouseLine(QWidget *parent = 0);
    ~DisplayMouseLine();
    void paintEvent(QPaintEvent *event);
    void setLine(int, int, float, float);

private:
    Ui::DisplayMouseLine *ui;
};

#endif // DISPLAYMOUSELINE_H

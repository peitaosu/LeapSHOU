#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>

namespace Ui {
class display;
}

class display : public QWidget
{
    Q_OBJECT

public:
    explicit display(QWidget *parent = 0);
    ~display();

public slots:
    //    void delayShow();
    void Show();

private:
    Ui::display *ui;
//    double opacityInc;//透明度增长值
//    double maxOpacity;//最大透明度
//    bool isDisplay;//是否已经显示
//    int displayTime;//已经显示了多久
//    int displayInterval;//窗口显示时间
//    int timerInterval;
};

#endif // DISPLAY_H

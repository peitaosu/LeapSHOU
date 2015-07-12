#ifndef SETTINGPANEL_H
#define SETTINGPANEL_H

#include <QDialog>

namespace Ui {
class SettingPanel;
}

class SettingPanel : public QDialog
{
    Q_OBJECT

public:
    explicit SettingPanel(QWidget *parent = 0);
    ~SettingPanel();

signals:
    void AutoStartChanged();
    void reset();
private slots:
    void setAutoStart(bool);
    void setCheckButton();
    bool getAutoStartINI();
    void setAutoStartINI(bool);

    void on_exit_Setting_Panel_Button_clicked();
    void on_reset_Setting_Panel_Button_clicked();

private:
    Ui::SettingPanel *ui;
};

#endif // SETTINGPANEL_H

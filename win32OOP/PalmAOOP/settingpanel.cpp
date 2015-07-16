#include "settingpanel.h"
#include "ui_settingpanel.h"
#include <QApplication>
#include <QSettings>

//开机自启动项在注册表中的路径，cmd->regedit->HKEY_CURRENT_USER->Software->Microsoft->Windows->CurrentVersion->Run
//the path of startup in the register table
#define REG_RUN "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"

SettingPanel::SettingPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingPanel)
{
    ui->setupUi(this);
    /*
     * 事件：
     * 当checkbox被按下时，根据是否按下，把bool型的状态发给槽函数setAutoStart(bool);
     * 然后用setAutoStartINI(bool)把相应的设置写入ini文件;
     * 设置更改后，发送AutoStartChanged()信号，触发text的改变。
     * Event:
     * when checkbox clicked, send bool status to slot setAutoStart(bool);
     * use setAutoStartINI(bool) to write the options to *.ini file;
     * after the option changed, send signal AutoStartChanged(), and change the text.
     */
    connect(ui->auto_start_checkbox,SIGNAL(clicked(bool)),this,SLOT(setAutoStart(bool)));
    connect(ui->auto_start_checkbox,SIGNAL(clicked(bool)),this,SLOT(setAutoStartINI(bool)));
    connect(this,SIGNAL(AutoStartChanged()),this,SLOT(setCheckButton()));
}

SettingPanel::~SettingPanel()
{
    delete ui;
}

/*
 * 获取Option.ini文件中，组AutoStart的项auto_start的值，类型为bool，返回值为bool型
 * get the value of auto_start one of keys in the AutoStart from file Option.ini, return bool
 * #####Option.ini#####
 * [AutoStart]
 * auto_start = true or flase
 */
bool SettingPanel::getAutoStartINI()
{
    QSettings settings("Option.ini", QSettings::IniFormat);
    bool auto_start = settings.value("AutoStart/auto_start").toBool();
    return auto_start;
}
/*
 * 设置Option.ini文件中，组AutoStart的项auto_start的值，类型为bool，传入值为bool型，无返回值
 * set the value of auto_start one of keys in the AutoStart in file Option.ini;
 * the value type is bool and import type is bool, no return
 * #####Option.ini#####
 * [AutoStart]
 * auto_start = true or flase
 * 设置好后发送信号AutoStartChanged()，通知槽函数该值已经改变。
 * after set the option, send signal AutoStartChanged() to let the slot know the value had changed
 */
void SettingPanel::setAutoStartINI(bool auto_start)
{
    QSettings settings("Option.ini", QSettings::IniFormat);
    settings.beginGroup("AutoStart");
    if(auto_start){
        settings.setValue("auto_start", true);
    }else{
        settings.setValue("auto_start", false);
    }
    settings.endGroup();
    emit AutoStartChanged();
}
/*
 * 设置注册表中的REG_RUN项，传入值为bool型，无返回值
 * set the REG_RUN in the register table, import value type is bool, no return
 */
void SettingPanel::setAutoStart(bool is_auto_start)
{
    QString application_name = QApplication::applicationName();
    QSettings *settings = new QSettings(REG_RUN, QSettings::NativeFormat);
    if(is_auto_start)
    {
        QString application_path = QApplication::applicationFilePath();
        settings->setValue(application_name, application_path.replace("/", "\\"));
    }
    else
    {
        settings->remove(application_name);
    }
    delete settings;
}
/*
 * 更改控件checkbox的text属性
 * 根据getAutoStartINI()的返回值，更改为相应的文字。
 * change the checkbox text
 * change to what return from getAutoStartINI()
 */
void SettingPanel::setCheckButton()
{
    if(this->getAutoStartINI()){
        ui->auto_start_checkbox->setText(QString("取消开机自启动"));
    }else{
        ui->auto_start_checkbox->setText(QString("开机自启动"));
    }
}
/*
 * 退出按钮事件
 * Exit event
 */
void SettingPanel::on_exit_Setting_Panel_Button_clicked()
{
    this->hide();
}
/*
 * 重置按钮事件
 * Reset event
 */
void SettingPanel::on_reset_Setting_Panel_Button_clicked()
{
    ui->auto_start_checkbox->setChecked(false);
    emit ui->auto_start_checkbox->clicked(false);
}

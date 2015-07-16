#include "operate.h"
#include <QDesktopServices>
#include <QUrl>
#include <Windows.h>
#include <iostream>
#pragma comment (lib,"Advapi32.lib")
#pragma comment (lib,"User32.lib")
Operate::Operate(QObject *parent) :
    QObject(parent)
{
    //移动鼠标到绝对位置（65535,40000）
    //move mouse to absolute position (65535,40000)
    mouse_event(MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE,65535,40000,0,0);
}

/*
 * 事件：鼠标左键单击
 * 传入值：int x, int y
 * 位置：绝对位置（x,y）
 * 结束后移动鼠标到绝对位置（65535,40000）
 * Event: Mouse Left Click
 * Improt: int x, int y
 * Position: absolute position (x,y)
 * After that: move mouse to absolute position (65535,40000)
 */
void Operate::MouseLeftClick(int x,int y){
    mouse_event(MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE,x,y,0,0);
    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP,0,0, 0, 0 );
    mouse_event(MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE,65535,40000,0,0);
}

/*
 * 事件：鼠标左键双击
 * 传入值：int x, int y
 * 位置：绝对位置（x,y）
 * 结束后移动鼠标到绝对位置（65535,40000）
 * Event: Mouse Left Double Click
 * Improt: int x, int y
 * Position: absolute position (x,y)
 * After that: move mouse to absolute position (65535,40000)
 */
void Operate::MouseLeftDClick(int x,int y){
    mouse_event(MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE,x,y,0,0);
    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP,0,0, 0, 0 );
    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP,0,0, 0, 0 );
    mouse_event(MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE,65535,40000,0,0);
}

/*
 * 事件：鼠标右键单击
 * 传入值：int x, int y
 * 位置：绝对位置（x,y）
 * 结束后移动鼠标到绝对位置（65535,40000）
 * Event: Mouse Right Click
 * Improt: int x, int y
 * Position: absolute position (x,y)
 * After that: move mouse to absolute position (65535,40000)
 */
void Operate::MouseRightClick(int x,int y){
    mouse_event(MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE,x,y,0,0);
    mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP,0,0, 0, 0 );
    mouse_event(MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE,65535,40000,0,0);
}

/*
 * 事件：鼠标滚轮
 * 滚动距离：5
 * Event: Mouse Wheel
 * Distance: 5
 */
void Operate::MouseWheel(){
    mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 5, 0);
}

/*
 * 事件：鼠标反向滚轮
 * 滚动距离：-5
 * Event: Mouse Wheel N
 * Distance: -5
 */
void Operate::MouseWheelN(){
    mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -5, 0);
}

/*
 * 事件：鼠标滚轮
 * 传入值：int w
 * 滚动距离：w
 * Event: Mouse Wheel
 * Import: int w
 * Distance: w
 */
void Operate::MouseWheel(int w){
    mouse_event(MOUSEEVENTF_WHEEL, 0, 0, w, 0);
}

/*
 * 事件：鼠标滚轮停止
 * Event: Mouse Wheel Stop
 */
void Operate::MouseWheelStop(){
    mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 0, 0);
}

/*
 * 事件：显示桌面
 * Event: Show Desktop
 */
void Operate::showDesktop(){
    keybd_event(VK_LWIN,0,0,0);
    keybd_event(0x44,0,0,0);
    keybd_event(0x44,0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_LWIN,0,KEYEVENTF_KEYUP,0);
}

/*
 * 事件：打开文件管理器
 * Event: Open File Manager
 */
void Operate::openFileManager(){
    keybd_event(VK_LWIN,0,0,0);
    keybd_event(0x45,0,0,0);
    keybd_event(0x45,0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_LWIN,0,KEYEVENTF_KEYUP,0);
}

/*
 * 事件：切换窗口
 * Event: Swipe Window
 */
void Operate::swipeWindow(){
    keybd_event(VK_LWIN,0,0,0);
    keybd_event(VK_TAB,0,0,0);
    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_TAB,0,0,0);
    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_LWIN,0,KEYEVENTF_KEYUP,0);
}

/*
 * 事件：切换x个窗口
 * 传入值：int x
 * Event: Swipe x Windows
 * Import: int x
 */
void Operate::swipeWindow(int x){
    keybd_event(VK_LWIN,0,0,0);
    keybd_event(VK_TAB,0,0,0);
    for(int i=0;i<x;i++){
        keybd_event(VK_TAB,0,0,0);
        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
    }
    keybd_event(VK_LWIN,0,KEYEVENTF_KEYUP,0);
}

/*
 * 事件：切换浏览器选项卡
 * Event: Swipe Browser Tab
 */
void Operate::swipeBrowserTab(){
    keybd_event(VK_CONTROL,0,0,0);
    keybd_event(VK_TAB,0,0,0);
    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
}

/*
 * 事件：窗口移向左边
 * Event: Move Window to Left
 */
void Operate::moveWindowtoLeft(){
    keybd_event(VK_LWIN,0,0,0);
    keybd_event(VK_LEFT,0,0,0);
    keybd_event(VK_LEFT,0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_LWIN,0,KEYEVENTF_KEYUP,0);
}

/*
 * 事件：窗口移向右边
 * Event: Move Window to Right
 */
void Operate::moveWindowtoRight(){
    keybd_event(VK_LWIN,0,0,0);
    keybd_event(VK_RIGHT,0,0,0);
    keybd_event(VK_RIGHT,0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_LWIN,0,KEYEVENTF_KEYUP,0);
}

/*
 * 事件：最大化窗口
 * Event: Maxsize the Window
 */
void Operate::moveWindowtoUp(){
    keybd_event(VK_LWIN,0,0,0);
    keybd_event(VK_UP,0,0,0);
    keybd_event(VK_UP,0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_LWIN,0,KEYEVENTF_KEYUP,0);
}

/*
 * 事件：最小化窗口
 * Event: Minisize the Window
 */
void Operate::moveWindowtoDown(){
    keybd_event(VK_LWIN,0,0,0);
    keybd_event(VK_DOWN,0,0,0);
    keybd_event(VK_DOWN,0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_LWIN,0,KEYEVENTF_KEYUP,0);
}

/*
 * 事件：打开浏览器并访问http:://www.shou.edu.cn
 * Event: Open Browser and visit http:://www.shou.edu.cn
 */
void Operate::openBrowser(){
    QUrl url("http://www.shou.edu.cn");
    QDesktopServices::openUrl(url);
}

/*
 * 事件：进入
 * Event: Enter
 */
void Operate::goEnter(){
    keybd_event(VK_RETURN,0,0,0);
    keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0);
}

/*
 * 事件：返回
 * Event: Go Back
 */
void Operate::goBack(){
    keybd_event(VK_BACK,0,0,0);
    keybd_event(VK_BACK,0,KEYEVENTF_KEYUP,0);
}
/*
 * 事件：刷新
 * Event: Refresh
 */
void Operate::goRefresh(){
    keybd_event(VK_F5,0,0,0);
    keybd_event(VK_F5,0,KEYEVENTF_KEYUP,0);
}

/*
 * 事件：锁定工作区
 * Event: Lock WorkStation
 */
void Operate::lockscreen(){
    LockWorkStation();
}

/*
 * 事件：关机
 * Event: Shutdown
 */
bool Operate::shutdown(){
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;

    if (!OpenProcessToken(GetCurrentProcess(),
        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
      return( FALSE );

    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,
        &tkp.Privileges[0].Luid);

    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
        (PTOKEN_PRIVILEGES)NULL, 0);

    if (GetLastError() != ERROR_SUCCESS)
      return FALSE;

    if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_POWEROFF,
               SHTDN_REASON_MAJOR_OPERATINGSYSTEM |
               SHTDN_REASON_MINOR_UPGRADE |
               SHTDN_REASON_FLAG_PLANNED))
      return FALSE;

    return TRUE;

}

/*
 * 事件：强制关机
 * Event: Shutdown Force
 */
bool Operate::shutdownforce(){
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;

    if (!OpenProcessToken(GetCurrentProcess(),
        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
      return( FALSE );

    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,
        &tkp.Privileges[0].Luid);

    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
        (PTOKEN_PRIVILEGES)NULL, 0);

    if (GetLastError() != ERROR_SUCCESS)
      return FALSE;

    if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE,
               SHTDN_REASON_MAJOR_OPERATINGSYSTEM |
               SHTDN_REASON_MINOR_UPGRADE |
               SHTDN_REASON_FLAG_PLANNED))
      return FALSE;

    return TRUE;

}

/*
 * 事件：重启
 * Event: Reboot
 */
bool Operate::reboot(){
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;

    if (!OpenProcessToken(GetCurrentProcess(),
        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
      return( FALSE );

    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,
        &tkp.Privileges[0].Luid);

    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
        (PTOKEN_PRIVILEGES)NULL, 0);

    if (GetLastError() != ERROR_SUCCESS)
      return FALSE;

    if (!ExitWindowsEx(EWX_REBOOT,
               SHTDN_REASON_MAJOR_OPERATINGSYSTEM |
               SHTDN_REASON_MINOR_UPGRADE |
               SHTDN_REASON_FLAG_PLANNED))
      return FALSE;

    return TRUE;
}

/*
 * 事件：登出
 * Event: Logout
 */
bool Operate::logout(){
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;

    if (!OpenProcessToken(GetCurrentProcess(),
        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
      return( FALSE );

    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,
        &tkp.Privileges[0].Luid);

    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
        (PTOKEN_PRIVILEGES)NULL, 0);

    if (GetLastError() != ERROR_SUCCESS)
      return FALSE;

    if (!ExitWindowsEx(EWX_LOGOFF,
               SHTDN_REASON_MAJOR_OPERATINGSYSTEM |
               SHTDN_REASON_MINOR_UPGRADE |
               SHTDN_REASON_FLAG_PLANNED))
      return FALSE;

    return TRUE;
}

#include "fgwin.h"
#include <QTimer>
#include <iostream>
#include <string>
#include <locale>
#include <Windows.h>
#include "tlhelp32.h"

LPWSTR GetProcessNameById(DWORD ProcessID)
{
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    LPWSTR result = new WCHAR[32];

    //获取系统中全部进程的快照
    //Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hProcessSnap) return(FALSE);

    pe32.dwSize = sizeof(PROCESSENTRY32);

    //获取第一个进程的信息
    //若获取失败则退出
    //Retrieve information about the first process,
    //and exit if unsuccessful
    if (!Process32First(hProcessSnap, &pe32))
    {
        //清除快照
        //clean the snapshot object
        CloseHandle(hProcessSnap);
        printf("!!! Failed to gather information on system processes! \n");
        return(NULL);
    }

    //匹配进程ID
    //Matching Process ID
    do
    {
        if (ProcessID == pe32.th32ProcessID)
        {
            //拷贝进程名
            //Copy Process Name
            wcscpy(result, (LPWSTR)pe32.szExeFile);
            break;
        }
    } while (Process32Next(hProcessSnap, &pe32));

    //清除快照
    //clean the snapshot object
    CloseHandle(hProcessSnap);

    return result;
}

//设置缓冲区
//set buffer
WCHAR buf[MAX_PATH] = { 0 };

//设置应用程序字段
//set applications character

//浏览器窗口标题
//browser window text
WCHAR FF[] = L"- Mozilla Firefox";
WCHAR GC[] = L"- Google Chrome";
WCHAR IE[] = L"- Internet Explorer";
WCHAR OP[] = L"- Opera";

//浏览器进程名
//browser process name
WCHAR Firefox[] = L"firefox.exe";
WCHAR Chrome[] = L"chrome.exe";
WCHAR IExplore[] = L"iexplore.exe";
WCHAR Opera[] = L"opera.exe";

//桌面和文件管理器
//desktop and file manager
WCHAR PC[] = L"\u8ba1\u7b97\u673a";
WCHAR DT[] = L"Program Manager";
WCHAR Desktop[] = L"explorer.exe";
WCHAR FileManager[] = L"explorer.exe";


FGWin::FGWin(QObject *parent) :
    QObject(parent)
{
    //设置显示语言
    //set language
    setlocale(LC_ALL, "");

    //新建定时器，定时获取前台窗口
    //new timer, timeout to get foreground window name
    QTimer *CheckFGWinNameTimer = new QTimer(this);
    connect(CheckFGWinNameTimer,SIGNAL(timeout()),this,SLOT(getFGWinName()));
    CheckFGWinNameTimer->start(50);
}

int FGWin::getFGWinName(){

    //声明并初始化变量process_ID
    //new variable process_ID
    DWORD process_ID = 0;

    //获取前台窗口
    //get foreground window
    HWND hwnd_foreground_window = GetForegroundWindow();

    //获取前台窗口的进程ID
    //get foreground window process id
    GetWindowThreadProcessId(hwnd_foreground_window,&process_ID);

    //获取前台窗口的窗口标题
    //get foreground window window text
    GetWindowText(GetForegroundWindow(), buf, MAX_PATH);

    //声明并初始化变量szProcessName，保存进程名
    //new variable szProcessName，used to save process name
    LPWSTR szProcessName = new WCHAR[32];
    wcscpy(szProcessName, GetProcessNameById(process_ID));

    //匹配进程名
    //match process name
    if (wcsstr(buf, FF)||wcsstr(buf, GC)||wcsstr(buf, IE)||wcsstr(buf, OP)){
        return 2;
    }else if(wcsstr(szProcessName,Desktop)){
        if(wcsstr(buf, DT)){
            return 1;
        }else if(wcsstr(buf, PC)){
            return 3;
        }else{
            return 1;
        }
    }else{
        return 0;
    }
}

int FGWin::getFGWinNameByMatchTitle(){
    //获取前台窗口的窗口标题
    //get foreground window window text
    if(GetWindowText(GetForegroundWindow(), buf, MAX_PATH)){
    }

    //匹配窗口名
    //match window text
    if (wcsstr(buf, FF)||wcsstr(buf, GC)||wcsstr(buf, IE)){
        return 2;
    }else if(wcsstr(buf, DT)){
        return 1;
    }else if(wcsstr(buf, PC)){
        return 3;
    }else{
        return 0;
    }
}


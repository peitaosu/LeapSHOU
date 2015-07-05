#include "fgwin.h"
#include <QTimer>
#include <iostream>
#include <string>
#include <locale>
#include <Windows.h>
//#include <Psapi.h>
#include "tlhelp32.h"
//#pragma comment (lib,"Psapi.lib")

LPWSTR GetProcessNameById(DWORD ProcessID)
{
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    LPWSTR result = new WCHAR[32];

    //获取系统中全部进程的快照 Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hProcessSnap) return(FALSE);

    pe32.dwSize = sizeof(PROCESSENTRY32);

    // 获取第一个进程的信息 Retrieve information about the first process,
    // 若获取失败则退出 and exit if unsuccessful
    if (!Process32First(hProcessSnap, &pe32))
    {
        // 清除快照 clean the snapshot object
        CloseHandle(hProcessSnap);
        printf("!!! Failed to gather information on system processes! \n");
        return(NULL);
    }

    //匹配进程ID Matching Process ID
    do
    {
        if (ProcessID == pe32.th32ProcessID)
        {
            //拷贝进程名 Copy Process Name
            wcscpy(result, (LPWSTR)pe32.szExeFile);
            break;
        }
    } while (Process32Next(hProcessSnap, &pe32));

    // 清除快照 clean the snapshot object
    CloseHandle(hProcessSnap);

    return result;
}

WCHAR buf[MAX_PATH] = { 0 };

WCHAR FF[] = L"- Mozilla Firefox";
WCHAR GC[] = L"- Google Chrome";
WCHAR IE[] = L"- Internet Explorer";
WCHAR PC[] = L"\u8ba1\u7b97\u673a";
WCHAR DT[] = L"Program Manager";

WCHAR Firefox[] = L"firefox.exe";
WCHAR Chrome[] = L"chrome.exe";
WCHAR IExplore[] = L"iexplore.exe";
WCHAR Opera[] = L"opera.exe";

WCHAR Desktop[] = L"explorer.exe";
WCHAR FileManager[] = L"explorer.exe";


FGWin::FGWin(QObject *parent) :
    QObject(parent)
{
    setlocale(LC_ALL, "");

    QTimer *CheckFGWinNameTimer = new QTimer(this);
    connect(CheckFGWinNameTimer,SIGNAL(timeout()),this,SLOT(getFGWinName()));
    CheckFGWinNameTimer->start(50);
}

int FGWin::getFGWinName(){
    DWORD process_ID = 0;
    HWND hwnd_foreground_window = GetForegroundWindow();
    GetWindowThreadProcessId(hwnd_foreground_window,&process_ID);
    GetWindowText(GetForegroundWindow(), buf, MAX_PATH);
    LPWSTR szProcessName = new WCHAR[32];
    wcscpy(szProcessName, GetProcessNameById(process_ID));

    if (wcsstr(buf, FF)||wcsstr(buf, GC)||wcsstr(buf, IE)){
        return 2;
    }else if(wcsstr(szProcessName,Desktop)){
        if(wcsstr(buf, DT)){
            return 1;
        }else{
            return 3;
        }
    }else{
        return 0;
    }
}


int FGWin::getFGWinNameByMatchTitle(){
    if(GetWindowText(GetForegroundWindow(), buf, MAX_PATH)){
    }
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


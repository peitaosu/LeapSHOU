#include "getinfo.h"
#include <QTimer>
#include <iostream>
#include <string>
#include <locale>
#include <Windows.h>
#include "data.h"


WCHAR buf[MAX_PATH] = { 0 };

WCHAR FF[] = L"- Mozilla Firefox";
WCHAR GC[] = L"- Google Chrome";
WCHAR IE[] = L"- Internet Explorer";
WCHAR PC[] = L"\u8ba1\u7b97\u673a";
WCHAR DT[] = L"Program Manager";

GetInfo::GetInfo()
{

    setlocale(LC_ALL, "");

    QTimer *CheckFGWinNameTimer = new QTimer(this);
    connect(CheckFGWinNameTimer,SIGNAL(timeout()),this,SLOT(getFGWinName()));
    CheckFGWinNameTimer->start(1000);

}

GetInfo::~GetInfo()
{
    //
}

void GetInfo::getFGWinName(){
    if(GetWindowText(GetForegroundWindow(), buf, MAX_PATH)){
        std::wcout << buf << std::endl;
    }
    if (wcsstr(buf, FF)||wcsstr(buf, GC)||wcsstr(buf, IE)){
        std::wcout << "BW!" << std::endl;
        //
        BW_CLKWS = 1;
        BW_ATCLKWS = 1;
        BW_LINK = 1;
        BW_TAB = 1;

        V_CTRL = 0;
        V_MOUSE = 0;
    }else if(wcsstr(buf, DT)){
        std::wcout << "DT!" << std::endl;
        //
        V_CTRL = 1;
    }else if(wcsstr(buf, PC)){
        std::wcout << "PC!" << std::endl;
        //
    }else{
        V_MOUSE = 1;
        V_CTRL = 0;

        BW_CLKWS = 0;
        BW_ATCLKWS = 0;
        BW_LINK = 0;
        BW_TAB = 0;
    }
}

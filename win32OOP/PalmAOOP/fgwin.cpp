#include "fgwin.h"
#include <QTimer>
#include <iostream>
#include <string>
#include <locale>
#include <Windows.h>

WCHAR buf[MAX_PATH] = { 0 };

WCHAR FF[] = L"- Mozilla Firefox";
WCHAR GC[] = L"- Google Chrome";
WCHAR IE[] = L"- Internet Explorer";
WCHAR PC[] = L"\u8ba1\u7b97\u673a";
WCHAR DT[] = L"Program Manager";

FGWin::FGWin(QObject *parent) :
    QObject(parent)
{
    setlocale(LC_ALL, "");

    QTimer *CheckFGWinNameTimer = new QTimer(this);
    connect(CheckFGWinNameTimer,SIGNAL(timeout()),this,SLOT(getFGWinName()));
    CheckFGWinNameTimer->start(50);
}

int FGWin::getFGWinName(){
    if(GetWindowText(GetForegroundWindow(), buf, MAX_PATH)){
        //std::wcout << buf << std::endl;
    }
    if (wcsstr(buf, FF)||wcsstr(buf, GC)||wcsstr(buf, IE)){
        //std::wcout << "BW!" << std::endl;
        //
        return 2;
    }else if(wcsstr(buf, DT)){
        //std::wcout << "DT!" << std::endl;
        //
        return 1;
    }else if(wcsstr(buf, PC)){
        //std::wcout << "PC!" << std::endl;
        return 3;
    }else{
        return 0;
    }
}


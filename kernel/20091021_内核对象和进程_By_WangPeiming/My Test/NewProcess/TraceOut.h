// TraceOut.h: interface for the CTraceOut class.
// this file should be put into stdafx.h
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRACEOUT_H__1574F964_1439_4E5A_95A7_E7A817C1C716__INCLUDED_)
#define AFX_TRACEOUT_H__1574F964_1439_4E5A_95A7_E7A817C1C716__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <conio.h>

/*
    Usage:
    1 This file  should be put into stdafx.h
    2 After that ,you can use Trace function at any place in the project,
        a console window will display when your app starts,and disappear after
        your app exit.both unicode and ansi are supported
    3 eg.:
        TRACEOUT(_T("*******"));
    4 If you want to disable trace,just do
        //#define ENABLE_TRACE 1 //comment this to disable trace
*/

#define ENABLE_TRACE 1 //comment this to disable trace



#ifndef ENABLE_TRACE
#define TRACEOUT(x)
#else
class CTraceOut
{
public:
    CTraceOut(){
        if (!AllocConsole())
            AfxMessageBox(_T("Failed to create the trace console!"), MB_ICONEXCLAMATION);
    };
    virtual ~CTraceOut()
    {
        if (!FreeConsole())
            AfxMessageBox(_T("Could not free the trace console!"));
    };
};
static char* GetCurTime()
{
    static char system_time[255];
    CTime time = CTime::GetCurrentTime();
    int hour = time.GetHour();
    int minute = time.GetMinute();
    int second = time.GetSecond();
    sprintf(system_time,"%2d:%2d:%2d",hour,minute,second);
    return system_time;
}
static char *UnicodeToAnsi(LPCTSTR UniStr)
{
    static char str[1000];
//    int num=WideCharToMultiByte(932, 0, UniStr, -1, str, 1000, 0, 0);
    return str;
}
#ifdef _UNICODE
#define TRACEOUT(x) _cprintf("%s:%s\r\n", GetCurTime(),UnicodeToAnsi(x));
#else
#define TRACEOUT(x) _cprintf(_T("%s:%s\r\n"), GetCurTime(),x);
#endif
CTraceOut g_traceout;

#endif
#endif // !defined(AFX_TRACEOUT_H__1574F964_1439_4E5A_95A7_E7A817C1C716__INCLUDED_)

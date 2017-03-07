; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTimerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "timer.h"
LastPage=0

ClassCount=3
Class1=CTimerApp
Class2=CAboutDlg
Class3=CTimerDlg

ResourceCount=3
Resource1=IDD_TIMER_DIALOG
Resource2=IDD_ABOUTBOX
Resource3=IDR_MENU_TEST

[CLS:CTimerApp]
Type=0
BaseClass=CWinApp
HeaderFile=Timer.h
ImplementationFile=Timer.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=TimerDlg.cpp
ImplementationFile=TimerDlg.cpp
LastObject=CAboutDlg

[CLS:CTimerDlg]
Type=0
BaseClass=CDialog
HeaderFile=TimerDlg.h
ImplementationFile=TimerDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=ID_CLOSE

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TIMER_DIALOG]
Type=1
Class=CTimerDlg
ControlCount=10
Control1=IDCANCEL,button,1342242816
Control2=IDC_SHUTDOWN,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_SPIN,msctls_updown32,1342177334
Control6=IDC_CURTIME,static,1342308352
Control7=IDC_APPLY,button,1342242816
Control8=IDC_SHUT_TIME,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352

[MNU:IDR_MENU_TEST]
Type=1
Class=?
Command1=ID_CLOSE
Command2=ID_ABOUT
CommandCount=2


; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CThreadTestDlg
LastTemplate=CWinThread
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ThreadTest.h"

ClassCount=4
Class1=CThreadTestApp
Class2=CThreadTestDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_THREADTEST_DIALOG
Resource4=IDD_ABOUTBOX (English (U.S.))
Class4=NewThread
Resource5=IDD_THREADTEST_DIALOG (English (U.S.))

[CLS:CThreadTestApp]
Type=0
HeaderFile=ThreadTest.h
ImplementationFile=ThreadTest.cpp
Filter=N

[CLS:CThreadTestDlg]
Type=0
HeaderFile=ThreadTestDlg.h
ImplementationFile=ThreadTestDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=ThreadTestDlg.h
ImplementationFile=ThreadTestDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_THREADTEST_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CThreadTestDlg

[DLG:IDD_THREADTEST_DIALOG (English (U.S.))]
Type=1
Class=CThreadTestDlg
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_BUTTON2,button,1342242816
Control5=IDC_BUTTON3,button,1342242816
Control6=IDC_BUTTON4,button,1342242816
Control7=IDC_BUTTON5,button,1342242816
Control8=IDC_BUTTON6,button,1342242816
Control9=IDC_BUTTON7,button,1342242816

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:NewThread]
Type=0
HeaderFile=NewThread.h
ImplementationFile=NewThread.cpp
BaseClass=CWinThread
Filter=N
LastObject=NewThread


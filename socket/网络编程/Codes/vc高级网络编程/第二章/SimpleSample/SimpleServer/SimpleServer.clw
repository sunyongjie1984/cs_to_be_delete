; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSimpleServerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SimpleServer.h"

ClassCount=3
Class1=CSimpleServerApp
Class2=CSimpleServerDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SIMPLESERVER_DIALOG

[CLS:CSimpleServerApp]
Type=0
HeaderFile=SimpleServer.h
ImplementationFile=SimpleServer.cpp
Filter=N

[CLS:CSimpleServerDlg]
Type=0
HeaderFile=SimpleServerDlg.h
ImplementationFile=SimpleServerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDCANCEL

[CLS:CAboutDlg]
Type=0
HeaderFile=SimpleServerDlg.h
ImplementationFile=SimpleServerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SIMPLESERVER_DIALOG]
Type=1
Class=CSimpleServerDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_PORT,edit,1350631552


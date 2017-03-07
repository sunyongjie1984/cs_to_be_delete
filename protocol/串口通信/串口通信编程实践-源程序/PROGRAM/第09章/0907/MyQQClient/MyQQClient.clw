; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyMyQQClientDlg
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MyQQClient.h"

ClassCount=5
Class1=CMyMyQQClientApp
Class2=CMyMyQQClientDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_MY20043155MYQQCLIENT05_DIALOG
Class4=CLoginLoad
Class5=CMainSocket
Resource4=IDD_LOGINLOAD_DIALOG

[CLS:CMyMyQQClientApp]
Type=0
HeaderFile=MyQQClient.h
ImplementationFile=MyQQClient.cpp
Filter=N
LastObject=CMyMyQQClientApp

[CLS:CMyMyQQClientDlg]
Type=0
HeaderFile=MyQQClientDlg.h
ImplementationFile=MyQQClientDlg.cpp
Filter=D
LastObject=CMyMyQQClientDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=MyQQClientDlg.h
ImplementationFile=MyQQClientDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MY20043155MYQQCLIENT05_DIALOG]
Type=1
Class=CMyMyQQClientDlg
ControlCount=5
Control1=IDC_RECEIVE,edit,1352728644
Control2=IDC_STATIC,static,1342308352
Control3=IDC_COMBO1,combobox,1344340226
Control4=IDC_SEND,edit,1352728644
Control5=IDC_BUTTON1,button,1342242816

[DLG:IDD_LOGINLOAD_DIALOG]
Type=1
Class=CLoginLoad
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_SEVER,edit,1350631552
Control7=IDC_IP,edit,1350631552
Control8=IDC_NAME,edit,1350631552

[CLS:CLoginLoad]
Type=0
HeaderFile=LoginLoad.h
ImplementationFile=LoginLoad.cpp
BaseClass=CDialog
Filter=D
LastObject=CLoginLoad
VirtualFilter=dWC

[CLS:CMainSocket]
Type=0
HeaderFile=MainSocket.h
ImplementationFile=MainSocket.cpp
BaseClass=CSocket
Filter=N
LastObject=CMainSocket
VirtualFilter=uq


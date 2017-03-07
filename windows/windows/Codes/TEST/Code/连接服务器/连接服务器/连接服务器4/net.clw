; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CNetDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "net.h"

ClassCount=4
Class1=CNetApp
Class2=CNetDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_NET_DIALOG
Class4=CUserinfoDlg
Resource4=IDD_USER_INFO

[CLS:CNetApp]
Type=0
HeaderFile=net.h
ImplementationFile=net.cpp
Filter=N

[CLS:CNetDlg]
Type=0
HeaderFile=netDlg.h
ImplementationFile=netDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CNetDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=netDlg.h
ImplementationFile=netDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_NET_DIALOG]
Type=1
Class=CNetDlg
ControlCount=8
Control1=IDC_BUTTON1,button,1342242816
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT2,edit,1350631584
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT3,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_BUTTON_GET_USER_INFO,button,1342242816

[DLG:IDD_USER_INFO]
Type=1
Class=CUserinfoDlg
ControlCount=1
Control1=IDC_LIST1,SysListView32,1350631425

[CLS:CUserinfoDlg]
Type=0
HeaderFile=UserinfoDlg.h
ImplementationFile=UserinfoDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC


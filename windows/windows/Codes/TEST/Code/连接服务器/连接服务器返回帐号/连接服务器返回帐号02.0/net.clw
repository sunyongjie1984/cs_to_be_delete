; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CStationscriptDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "net.h"

ClassCount=5
Class1=CNetApp
Class2=CNetDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_NET_DIALOG
Class4=CUsernameDlg
Resource4=IDD_DIALOG1
Class5=CStationscriptDlg

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
LastObject=IDC_EDIT1

[CLS:CAboutDlg]
Type=0
HeaderFile=netDlg.h
ImplementationFile=netDlg.cpp
Filter=D

[DLG:IDD_NET_DIALOG]
Type=1
Class=CNetDlg
ControlCount=7
Control1=IDC_BUTTON1,button,1342242816
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT2,edit,1350631584
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT3,edit,1350631552
Control7=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG]
Type=1
Class=CUsernameDlg
ControlCount=3
Control1=IDC_LIST1,SysListView32,1350631425
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_BUTTON2,button,1342242816

[CLS:CUsernameDlg]
Type=0
HeaderFile=UsernameDlg.h
ImplementationFile=UsernameDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CUsernameDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG1]
Type=1
Class=CStationscriptDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_STATIC,static,1342308352

[CLS:CStationscriptDlg]
Type=0
HeaderFile=StationscriptDlg.h
ImplementationFile=StationscriptDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CStationscriptDlg
VirtualFilter=dWC


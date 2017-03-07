; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGetIP
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ClientTest.h"

ClassCount=4
Class1=CClientTestApp
Class2=CClientTestDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_CLIENTTEST_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=CGetIP
Resource4=IDD_DIALOG_GETIP

[CLS:CClientTestApp]
Type=0
HeaderFile=ClientTest.h
ImplementationFile=ClientTest.cpp
Filter=N

[CLS:CClientTestDlg]
Type=0
HeaderFile=ClientTestDlg.h
ImplementationFile=ClientTestDlg.cpp
Filter=D
LastObject=IDCANCEL
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=ClientTestDlg.h
ImplementationFile=ClientTestDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CLIENTTEST_DIALOG]
Type=1
Class=CClientTestDlg
ControlCount=5
Control1=IDOK,button,1342242816
Control2=IDC_EDIT_MESSAGE,edit,1350631552
Control3=IDC_SEND,button,1342242817
Control4=IDC_LIST,listbox,1352728835
Control5=IDCANCEL,button,1342242816

[DLG:IDD_DIALOG_GETIP]
Type=1
Class=CGetIP
ControlCount=4
Control1=IDC_IPADDRESS,SysIPAddress32,1342242816
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352

[CLS:CGetIP]
Type=0
HeaderFile=GetIP.h
ImplementationFile=GetIP.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CGetIP


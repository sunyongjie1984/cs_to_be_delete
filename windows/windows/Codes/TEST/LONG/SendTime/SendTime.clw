; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSendTimeDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SendTime.h"

ClassCount=3
Class1=CSendTimeApp
Class2=CSendTimeDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SENDTIME_DIALOG

[CLS:CSendTimeApp]
Type=0
HeaderFile=SendTime.h
ImplementationFile=SendTime.cpp
Filter=N

[CLS:CSendTimeDlg]
Type=0
HeaderFile=SendTimeDlg.h
ImplementationFile=SendTimeDlg.cpp
Filter=D
LastObject=IDC_EDIT_IP
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=SendTimeDlg.h
ImplementationFile=SendTimeDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SENDTIME_DIALOG]
Type=1
Class=CSendTimeDlg
ControlCount=5
Control1=IDC_EDIT_MSG,edit,1350631552
Control2=IDC_SEND,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_IP,edit,1350631552
Control5=IDC_STATIC,static,1342308352


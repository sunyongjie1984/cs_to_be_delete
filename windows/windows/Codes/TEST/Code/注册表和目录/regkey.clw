; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRegkeyDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "regkey.h"

ClassCount=3
Class1=CRegkeyApp
Class2=CRegkeyDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_REGKEY_DIALOG

[CLS:CRegkeyApp]
Type=0
HeaderFile=regkey.h
ImplementationFile=regkey.cpp
Filter=N

[CLS:CRegkeyDlg]
Type=0
HeaderFile=regkeyDlg.h
ImplementationFile=regkeyDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_REG_KEY2

[CLS:CAboutDlg]
Type=0
HeaderFile=regkeyDlg.h
ImplementationFile=regkeyDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_PROGRESS

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=1
Control1=IDC_PROGRESS,msctls_progress32,1350565888

[DLG:IDD_REGKEY_DIALOG]
Type=1
Class=CRegkeyDlg
ControlCount=7
Control1=IDC_START,button,1342242816
Control2=IDC_REG_KEY,edit,1350631552
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_BUTTON2,button,1342242816
Control5=IDC_BUTTON3,button,1342242816
Control6=IDC_REG_KEY2,edit,1350631552
Control7=IDC_REG_KEY3,edit,1350631584


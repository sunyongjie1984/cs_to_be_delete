; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPublicNetSoftDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PublicNetSoft.h"

ClassCount=3
Class1=CPublicNetSoftApp
Class2=CPublicNetSoftDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_PUBLICNETSOFT_DIALOG

[CLS:CPublicNetSoftApp]
Type=0
HeaderFile=PublicNetSoft.h
ImplementationFile=PublicNetSoft.cpp
Filter=N

[CLS:CPublicNetSoftDlg]
Type=0
HeaderFile=PublicNetSoftDlg.h
ImplementationFile=PublicNetSoftDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT

[CLS:CAboutDlg]
Type=0
HeaderFile=PublicNetSoftDlg.h
ImplementationFile=PublicNetSoftDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PUBLICNETSOFT_DIALOG]
Type=1
Class=CPublicNetSoftDlg
ControlCount=5
Control1=IDC_EDIT,edit,1350631552
Control2=IDOK,button,1342242816
Control3=IDCANCEL,button,1342242816
Control4=IDC_LIST,listbox,1352728835
Control5=IDC_SEND,button,1342242817


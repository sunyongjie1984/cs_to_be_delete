; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CApiCommDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ApiComm.h"

ClassCount=4
Class1=CApiCommApp
Class2=CApiCommDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_APICOMM_DIALOG

[CLS:CApiCommApp]
Type=0
HeaderFile=ApiComm.h
ImplementationFile=ApiComm.cpp
Filter=N

[CLS:CApiCommDlg]
Type=0
HeaderFile=ApiCommDlg.h
ImplementationFile=ApiCommDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=ApiCommDlg.h
ImplementationFile=ApiCommDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_APICOMM_DIALOG]
Type=1
Class=CApiCommDlg
ControlCount=1
Control1=IDC_BUTTON2,button,1342242816


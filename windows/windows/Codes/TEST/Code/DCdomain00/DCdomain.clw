; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDCdomainDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DCdomain.h"

ClassCount=4
Class1=CDCdomainApp
Class2=CDCdomainDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DCDOMAIN_DIALOG

[CLS:CDCdomainApp]
Type=0
HeaderFile=DCdomain.h
ImplementationFile=DCdomain.cpp
Filter=N

[CLS:CDCdomainDlg]
Type=0
HeaderFile=DCdomainDlg.h
ImplementationFile=DCdomainDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=DCdomainDlg.h
ImplementationFile=DCdomainDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DCDOMAIN_DIALOG]
Type=1
Class=CDCdomainDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_BUTTON1,button,1342242816


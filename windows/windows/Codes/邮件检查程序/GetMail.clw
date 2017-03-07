; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGetMailDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "GetMail.h"

ClassCount=3
Class1=CGetMailApp
Class2=CGetMailDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDR_MENU_TRAY
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDD_GETMAIL_DIALOG

[CLS:CGetMailApp]
Type=0
HeaderFile=GetMail.h
ImplementationFile=GetMail.cpp
Filter=N

[CLS:CGetMailDlg]
Type=0
HeaderFile=GetMailDlg.h
ImplementationFile=GetMailDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CGetMailDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=GetMailDlg.h
ImplementationFile=GetMailDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_GETMAIL_DIALOG]
Type=1
Class=CGetMailDlg
ControlCount=12
Control1=IDOK,button,1342275584
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT_POP3,edit,1342242944
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_USER,edit,1342242944
Control7=IDC_EDIT_PASS,edit,1342242976
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_TIME,edit,1342242944
Control10=IDC_STATIC,static,1342308352
Control11=IDCANCEL,button,1342275584
Control12=IDC_STATIC_INFO,edit,1342244992

[MNU:IDR_MENU_TRAY]
Type=1
Command1=IDM_HIDE
Command2=IDM_SHOW
Command3=IDM_ABOUT
Command4=IDM_EXIT
CommandCount=4


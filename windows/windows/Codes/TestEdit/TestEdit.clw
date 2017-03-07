; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTestEditDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TestEdit.h"

ClassCount=3
Class1=CTestEditApp
Class2=CTestEditDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_TESTEDIT_DIALOG

[CLS:CTestEditApp]
Type=0
HeaderFile=TestEdit.h
ImplementationFile=TestEdit.cpp
Filter=N

[CLS:CTestEditDlg]
Type=0
HeaderFile=TestEditDlg.h
ImplementationFile=TestEditDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT1

[CLS:CAboutDlg]
Type=0
HeaderFile=TestEditDlg.h
ImplementationFile=TestEditDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TESTEDIT_DIALOG]
Type=1
Class=CTestEditDlg
ControlCount=1
Control1=IDC_EDIT1,edit,1350631552


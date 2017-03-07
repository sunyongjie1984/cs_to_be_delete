; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFileOperateDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "FileOperate.h"

ClassCount=3
Class1=CFileOperateApp
Class2=CFileOperateDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_FILEOPERATE_DIALOG

[CLS:CFileOperateApp]
Type=0
HeaderFile=FileOperate.h
ImplementationFile=FileOperate.cpp
Filter=N

[CLS:CFileOperateDlg]
Type=0
HeaderFile=FileOperateDlg.h
ImplementationFile=FileOperateDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_LIST_FILE

[CLS:CAboutDlg]
Type=0
HeaderFile=FileOperateDlg.h
ImplementationFile=FileOperateDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_FILEOPERATE_DIALOG]
Type=1
Class=CFileOperateDlg
ControlCount=7
Control1=IDC_STATIC,button,1342177287
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_LIST_FILE,SysListView32,1350631425
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,static,1342308352
Control7=IDC_E_FOLDER_PATH,edit,1350631552


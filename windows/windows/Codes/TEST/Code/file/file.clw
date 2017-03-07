; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFileDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "file.h"

ClassCount=4
Class1=CFileApp
Class2=CFileDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_FILE_DIALOG

[CLS:CFileApp]
Type=0
HeaderFile=file.h
ImplementationFile=file.cpp
Filter=N

[CLS:CFileDlg]
Type=0
HeaderFile=fileDlg.h
ImplementationFile=fileDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=fileDlg.h
ImplementationFile=fileDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_FILE_DIALOG]
Type=1
Class=CFileDlg
ControlCount=1
Control1=IDC_READ,button,1342242816


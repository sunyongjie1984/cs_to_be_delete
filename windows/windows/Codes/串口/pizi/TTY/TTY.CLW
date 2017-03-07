; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTTYDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TTY.h"
LastPage=0

ClassCount=6
Class1=CTTYApp
Class2=CTTYDoc
Class3=CTTYView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CCommSetDlg
Resource3=IDD_COMMDLG

[CLS:CTTYApp]
Type=0
HeaderFile=TTY.h
ImplementationFile=TTY.cpp
Filter=N
LastObject=CTTYApp

[CLS:CTTYView]
Type=0
HeaderFile=TTYView.h
ImplementationFile=TTYView.cpp
Filter=C
BaseClass=CEditView
VirtualFilter=VWC
LastObject=CTTYView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=TTY.cpp
ImplementationFile=TTY.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_API_SETTINGS
Command11=ID_API_CONNECT
Command12=ID_API_DISCONNECT
Command13=ID_APP_ABOUT
CommandCount=13

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_COMMDLG]
Type=1
Class=CCommSetDlg
ControlCount=16
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_PORT,combobox,1344339970
Control6=IDC_STATIC,static,1342308352
Control7=IDC_BAUD,combobox,1344339970
Control8=IDC_STATIC,static,1342308352
Control9=IDC_DATABITS,combobox,1344339970
Control10=IDC_STATIC,static,1342308352
Control11=IDC_PARITY,combobox,1344339970
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STOPBITS,combobox,1344339970
Control14=IDC_STATIC,static,1342308352
Control15=IDC_NEWLINE,button,1342242819
Control16=IDC_ECHO,button,1342242819

[CLS:CCommSetDlg]
Type=0
HeaderFile=CommSetDlg.h
ImplementationFile=CommSetDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CCommSetDlg
VirtualFilter=dWC

[CLS:CTTYDoc]
Type=0
HeaderFile=ttydoc.h
ImplementationFile=ttydoc.cpp
BaseClass=CDocument
LastObject=CTTYDoc


; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CConnectDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "atldraw.h"
LastPage=0

ClassCount=6
Class1=CATLDrawDoc
Class2=CATLDrawApp
Class3=CAboutDlg
Class4=CATLDrawView
Class5=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX (English (U.S.))
Resource2=IDD_REMOTEIP
Class6=CConnectDlg
Resource3=IDR_MAINFRAME (English (U.S.))

[CLS:CATLDrawDoc]
Type=0
BaseClass=CDocument
HeaderFile=ATLDDOC.H
ImplementationFile=ATLDDOC.CPP

[CLS:CATLDrawApp]
Type=0
BaseClass=CWinApp
HeaderFile=ATLDRAW.H
ImplementationFile=ATLDRAW.CPP

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ATLDRAW.CPP
ImplementationFile=ATLDRAW.CPP
LastObject=CAboutDlg

[CLS:CATLDrawView]
Type=0
BaseClass=CView
HeaderFile=ATLDVIEW.H
ImplementationFile=ATLDVIEW.CPP

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MAINFRM.H
ImplementationFile=MAINFRM.CPP

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_REMOTEIP]
Type=1
Class=CConnectDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_NAME,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[TB:IDR_MAINFRAME (English (U.S.))]
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

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_SERVER_CONNECT
Command15=ID_SERVER_DISCONNENT
Command16=ID_VIEW_COLOR
Command17=ID_VIEW_TOOLBAR
Command18=ID_VIEW_STATUS_BAR
Command19=ID_APP_ABOUT
CommandCount=19

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
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

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CConnectDlg]
Type=0
HeaderFile=ConnectDlg.h
ImplementationFile=ConnectDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_NAME


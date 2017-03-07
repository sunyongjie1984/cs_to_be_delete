; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChatView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "chat.h"
LastPage=0

ClassCount=8
Class1=CChatApp
Class2=CChatDoc
Class3=CChatView
Class4=CMainFrame

ResourceCount=4
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CMesg
Class7=CCLientSocket
Resource3=IDD_CHAT_FORM
Class8=CLoginDlg
Resource4=IDD_DIALOG1

[CLS:CChatApp]
Type=0
HeaderFile=chat.h
ImplementationFile=chat.cpp
Filter=N

[CLS:CChatDoc]
Type=0
HeaderFile=chatDoc.h
ImplementationFile=chatDoc.cpp
Filter=N

[CLS:CChatView]
Type=0
HeaderFile=chatView.h
ImplementationFile=chatView.cpp
Filter=D
BaseClass=CFormView
VirtualFilter=VWC
LastObject=IDC_COMBO1


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_BLACKSTART
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=chat.cpp
ImplementationFile=chat.cpp
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
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
Command17=ID_BLACKSTART
Command18=IDC_SEND
Command19=IDC_LOGIN
Command20=IDC_LOGOUT
CommandCount=20

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

[DLG:IDD_CHAT_FORM]
Type=1
Class=CChatView
ControlCount=7
Control1=IDC_NAMELIST,SysListView32,1350631425
Control2=IDC_EDIT_MSG,edit,1350631552
Control3=IDC_COMBO1,combobox,1344340227
Control4=IDC_MSGLIST,listbox,1352728835
Control5=IDC_STATIC1,static,1342308352
Control6=IDC_STATIC2,static,1342308352
Control7=IDC_STATIC_INFO,static,1342312704

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

[CLS:CMesg]
Type=0
HeaderFile=Mesg.h
ImplementationFile=Mesg.cpp
BaseClass=CCmdTarget
Filter=N

[CLS:CCLientSocket]
Type=0
HeaderFile=CLientSocket.h
ImplementationFile=CLientSocket.cpp
BaseClass=CSocket
Filter=N

[DLG:IDD_DIALOG1]
Type=1
Class=CLoginDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC3,static,1342308352
Control4=IDC_STATIC4,static,1342308352
Control5=IDC_STATIC5,static,1342308352
Control6=IDC_EDIT1,edit,1350631552
Control7=IDC_EDIT2,edit,1350631552
Control8=IDC_EDIT3,edit,1350631552

[CLS:CLoginDlg]
Type=0
HeaderFile=LoginDlg.h
ImplementationFile=LoginDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=dWC


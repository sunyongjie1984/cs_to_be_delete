; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPort
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "chatserver.h"
LastPage=0

ClassCount=9
Class1=CChatserverApp
Class2=CChatserverDoc
Class3=CChatserverView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_CHATSERVER_FORM
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CMesg
Class7=CLisnSocket
Class8=CchatSocket
Resource3=IDR_MAINFRAME
Class9=CPort
Resource4=IDD_DIALOG1

[CLS:CChatserverApp]
Type=0
HeaderFile=chatserver.h
ImplementationFile=chatserver.cpp
Filter=N

[CLS:CChatserverDoc]
Type=0
HeaderFile=chatserverDoc.h
ImplementationFile=chatserverDoc.cpp
Filter=N

[CLS:CChatserverView]
Type=0
HeaderFile=chatserverView.h
ImplementationFile=chatserverView.cpp
Filter=D
BaseClass=CFormView
VirtualFilter=VWC
LastObject=CChatserverView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=chatserver.cpp
ImplementationFile=chatserver.cpp
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
CommandCount=16

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

[DLG:IDD_CHATSERVER_FORM]
Type=1
Class=CChatserverView
ControlCount=4
Control1=IDC_LIST1,listbox,1352728835
Control2=IDC_START,button,1342242816
Control3=IDC_END,button,1342242816
Control4=IDC_STATIC_INFO,static,1342308352

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

[CLS:CLisnSocket]
Type=0
HeaderFile=LisnSocket.h
ImplementationFile=LisnSocket.cpp
BaseClass=CSocket
Filter=N

[CLS:CchatSocket]
Type=0
HeaderFile=chatSocket.h
ImplementationFile=chatSocket.cpp
BaseClass=CSocket
Filter=N

[DLG:IDD_DIALOG1]
Type=1
Class=CPort
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[CLS:CPort]
Type=0
HeaderFile=Port.h
ImplementationFile=Port.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=dWC


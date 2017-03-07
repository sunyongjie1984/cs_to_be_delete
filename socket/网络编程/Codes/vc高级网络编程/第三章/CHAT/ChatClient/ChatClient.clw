; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChatClientView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "chatclient.h"
LastPage=0

ClassCount=9
Class1=CChatClientApp
Class2=CAboutDlg
Class3=CChatClientDoc
Class4=CChatClientView
Class5=CLogin
Class6=CMainFrame
Class7=COnlineBar
Class8=COnlineList
Class9=CToolTipWnd

ResourceCount=6
Resource1=IDD_ONLINEDLG
Resource2=IDD_SENDDLG
Resource3=IDR_MAINFRAME
Resource4=IDD_ABOUTBOX
Resource5=IDR_CNTR_INPLACE
Resource6=IDD_SETUP

[CLS:CChatClientApp]
Type=0
BaseClass=CWinApp
HeaderFile=ChatClient.h
ImplementationFile=ChatClient.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ChatClient.cpp
ImplementationFile=ChatClient.cpp
LastObject=CAboutDlg

[CLS:CChatClientDoc]
Type=0
BaseClass=CRichEditDoc
HeaderFile=ChatClientDoc.h
ImplementationFile=ChatClientDoc.cpp

[CLS:CChatClientView]
Type=0
BaseClass=CRichEditView
HeaderFile=ChatClientView.h
ImplementationFile=ChatClientView.cpp
Filter=C
VirtualFilter=VWC
LastObject=IDC_SEND

[CLS:CLogin]
Type=0
BaseClass=CDialog
HeaderFile=Login.h
ImplementationFile=Login.cpp
LastObject=CLogin

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC

[CLS:COnlineBar]
Type=0
BaseClass=CDialogBar
HeaderFile=OnlineBar.h
ImplementationFile=OnlineBar.cpp
LastObject=COnlineBar

[CLS:COnlineList]
Type=0
BaseClass=CListCtrl
HeaderFile=OnlineList.h
ImplementationFile=OnlineList.cpp
LastObject=COnlineList

[CLS:CToolTipWnd]
Type=0
BaseClass=CWnd
HeaderFile=ToolTipWnd.h
ImplementationFile=ToolTipWnd.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SETUP]
Type=1
Class=CLogin
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_NAME,combobox,1344340226
Control5=IDC_STATIC,static,1342308352
Control6=IDC_SERVER,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_IMAGE,combobox,1344340226

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=IDC_CONNECT
Command2=IDC_DISCONNECT
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_FILE_PRINT
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_MAINFRAME]
Type=1
Class=CChatClientView
Command1=IDC_CONNECT
Command2=IDC_DISCONNECT
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
Command14=ID_EDIT_PASTE_SPECIAL
Command15=ID_EDIT_SELECT_ALL
Command16=ID_EDIT_FIND
Command17=ID_EDIT_REPEAT
Command18=ID_EDIT_REPLACE
Command19=ID_OLE_INSERT_NEW
Command20=ID_OLE_EDIT_LINKS
Command21=ID_OLE_EDIT_PROPERTIES
Command22=ID_OLE_VERB_FIRST
Command23=ID_VIEW_TOOLBAR
Command24=ID_VIEW_STATUS_BAR
Command25=ID_APP_ABOUT
CommandCount=25

[MNU:IDR_CNTR_INPLACE]
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
CommandCount=9

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_SELECT_ALL
Command2=ID_EDIT_COPY
Command3=ID_EDIT_FIND
Command4=ID_EDIT_REPLACE
Command5=ID_FILE_NEW
Command6=ID_FILE_OPEN
Command7=ID_FILE_PRINT
Command8=ID_FILE_SAVE
Command9=ID_EDIT_PASTE
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_CANCEL_EDIT_CNTR
Command13=ID_EDIT_REPEAT
Command14=ID_NEXT_PANE
Command15=ID_PREV_PANE
Command16=ID_EDIT_COPY
Command17=ID_EDIT_PASTE
Command18=IDC_SEND
Command19=ID_OLE_EDIT_PROPERTIES
Command20=ID_EDIT_CUT
Command21=ID_EDIT_UNDO
CommandCount=21

[ACL:IDR_CNTR_INPLACE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_CANCEL_EDIT_CNTR
CommandCount=7

[DLG:IDD_SENDDLG]
Type=1
Class=CChatClientView
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDC_TO,combobox,1344340226
Control3=IDC_SEND,button,1342242816
Control4=IDC_TYPE,combobox,1344339970
Control5=IDC_SECRET,button,1342242819
Control6=IDC_FILTER,button,1342242819
Control7=IDC_STATIC,static,1342308352
Control8=IDC_TEXT,edit,1350631552
Control9=IDC_COLOR,button,1342242816

[DLG:IDD_ONLINEDLG]
Type=1
Class=?
ControlCount=0


; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChildFrame
LastTemplate=CView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ReadCompass.h"
LastPage=0

ClassCount=8
Class1=CReadCompassApp
Class2=CReadCompassDoc
Class3=CReadCompassView
Class4=CMainFrame
Class6=CChildFrame
Class7=CAboutDlg

ResourceCount=4
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Resource3=IDR_READCOTYPE
Class5=CReadCompassSet
Class8=CDraw
Resource4=IDD_READCOMPASS_FORM

[CLS:CReadCompassApp]
Type=0
HeaderFile=ReadCompass.h
ImplementationFile=ReadCompass.cpp
Filter=N
LastObject=CReadCompassApp

[CLS:CReadCompassDoc]
Type=0
HeaderFile=ReadCompassDoc.h
ImplementationFile=ReadCompassDoc.cpp
Filter=N

[CLS:CReadCompassView]
Type=0
HeaderFile=ReadCompassView.h
ImplementationFile=ReadCompassView.cpp
Filter=D
LastObject=CReadCompassView
BaseClass=CRecordView
VirtualFilter=RVWC


[CLS:CReadCompassSet]
Type=0
HeaderFile=ReadCompassSet.h
ImplementationFile=ReadCompassSet.cpp
Filter=N

[DB:CReadCompassSet]
DB=1
DBType=ODBC
ColumnCount=8
Column1=[ID], 4, 4
Column2=[number], 4, 4
Column3=[temperature], 12, 100
Column4=[DATE], 12, 100
Column5=[CLASS], 12, 100
Column6=[NAME], 12, 100
Column7=[¸ÐÏë], 12, 100
Column8=[pressure], 12, 100


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
BaseClass=CMDIChildWnd
VirtualFilter=mfWC
LastObject=CChildFrame


[CLS:CAboutDlg]
Type=0
HeaderFile=ReadCompass.cpp
ImplementationFile=ReadCompass.cpp
Filter=D
LastObject=IDOK

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
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_RECORD_FIRST
Command9=ID_RECORD_PREV
Command10=ID_RECORD_NEXT
Command11=ID_RECORD_LAST
Command12=ID_APP_ABOUT
CommandCount=12

[MNU:IDR_READCOTYPE]
Type=1
Class=CReadCompassView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_RECORD_FIRST
Command16=ID_RECORD_PREV
Command17=ID_RECORD_NEXT
Command18=ID_RECORD_LAST
Command19=ID_VIEW_TOOLBAR
Command20=ID_VIEW_STATUS_BAR
Command21=ID_WINDOW_NEW
Command22=ID_WINDOW_CASCADE
Command23=ID_WINDOW_TILE_HORZ
Command24=ID_WINDOW_ARRANGE
Command25=ID_WINDOW_SPLIT
Command26=ID_APP_ABOUT
CommandCount=26

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

[DLG:IDD_READCOMPASS_FORM]
Type=1
Class=CReadCompassView
ControlCount=6
Control1=IDC_BUTTON1,button,1342242816
Control2=IDC_EDIT2,edit,1350631552
Control3=IDC_STATIC,button,1342177287
Control4=IDC_EDIT3,edit,1352728581
Control5=IDC_MSCOMM1,{648A5600-2C6E-101B-82B6-000000000014},1342242816
Control6=IDC_STATIC,static,1342308352

[CLS:CDraw]
Type=0
HeaderFile=Draw.h
ImplementationFile=Draw.cpp
BaseClass=CView
Filter=C
LastObject=CDraw


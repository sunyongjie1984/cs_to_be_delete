; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CShowBitmapChildWindowView
LastTemplate=CView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ProgrammeTechnicAccumulate.h"
LastPage=0

ClassCount=8
Class1=CProgrammeTechnicAccumulateApp
Class2=CProgrammeTechnicAccumulateDoc
Class3=CProgrammeTechnicAccumulateView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CGraphicsProgrammeDlg
Class7=CShowBitmapChildWindowFrame
Class8=CShowBitmapChildWindowView
Resource3=IDD_DLG_GRAPHICS_PROGRAMME

[CLS:CProgrammeTechnicAccumulateApp]
Type=0
HeaderFile=ProgrammeTechnicAccumulate.h
ImplementationFile=ProgrammeTechnicAccumulate.cpp
Filter=N

[CLS:CProgrammeTechnicAccumulateDoc]
Type=0
HeaderFile=ProgrammeTechnicAccumulateDoc.h
ImplementationFile=ProgrammeTechnicAccumulateDoc.cpp
Filter=N

[CLS:CProgrammeTechnicAccumulateView]
Type=0
HeaderFile=ProgrammeTechnicAccumulateView.h
ImplementationFile=ProgrammeTechnicAccumulateView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CProgrammeTechnicAccumulateView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_MENU_GRAPHICS_PROGRAMME




[CLS:CAboutDlg]
Type=0
HeaderFile=ProgrammeTechnicAccumulate.cpp
ImplementationFile=ProgrammeTechnicAccumulate.cpp
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
Command16=ID_MENU_GRAPHICS_PROGRAMME
Command17=ID_APP_ABOUT
CommandCount=17

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

[DLG:IDD_DLG_GRAPHICS_PROGRAMME]
Type=1
Class=CGraphicsProgrammeDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON_SHOW_BITMAP_FILE,button,1342242816

[CLS:CGraphicsProgrammeDlg]
Type=0
HeaderFile=GraphicsProgrammeDlg.h
ImplementationFile=GraphicsProgrammeDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CGraphicsProgrammeDlg
VirtualFilter=dWC

[CLS:CShowBitmapChildWindowFrame]
Type=0
HeaderFile=ShowBitmapChildWindowFrame.h
ImplementationFile=ShowBitmapChildWindowFrame.cpp
BaseClass=CFrameWnd
Filter=T
VirtualFilter=fWC

[CLS:CShowBitmapChildWindowView]
Type=0
HeaderFile=ShowBitmapChildWindowView.h
ImplementationFile=ShowBitmapChildWindowView.cpp
BaseClass=CView
Filter=C


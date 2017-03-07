; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFileOperateDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ProgrammeTechnicFund.h"
LastPage=0

ClassCount=8
Class1=CProgrammeTechnicFundApp
Class2=CProgrammeTechnicFundDoc
Class3=CProgrammeTechnicFundView
Class4=CMainFrame

ResourceCount=4
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX
Class6=CFileOperateDlg
Resource3=IDD_FILE
Class7=CVariableUsingMethodDlg
Class8=CUsingMethodDlg
Resource4=IDD_USING_METHOD_DLG

[CLS:CProgrammeTechnicFundApp]
Type=0
HeaderFile=ProgrammeTechnicFund.h
ImplementationFile=ProgrammeTechnicFund.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CProgrammeTechnicFundDoc]
Type=0
HeaderFile=ProgrammeTechnicFundDoc.h
ImplementationFile=ProgrammeTechnicFundDoc.cpp
Filter=N

[CLS:CProgrammeTechnicFundView]
Type=0
HeaderFile=ProgrammeTechnicFundView.h
ImplementationFile=ProgrammeTechnicFundView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CProgrammeTechnicFundView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_USING_METHOD
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=ProgrammeTechnicFund.cpp
ImplementationFile=ProgrammeTechnicFund.cpp
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
Command16=ID_READ_CONNECT_DB_CONFIGURATION_FILE
Command17=ID_USING_METHOD
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

[DLG:IDD_FILE]
Type=1
Class=CFileOperateDlg
ControlCount=23
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_FILE_NAME,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_MESSAGE,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_IPADDRESS,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_LONG_DISTANCE_COMPUTER_PORT,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_INSERT_RECORD_COUNT,edit,1350631552
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDIT_INSERT_RECORD_TIME_ALTERNATION,edit,1350631552
Control16=IDC_STATIC,button,1342177287
Control17=IDC_BUTTON_UDP_SEND,button,1342242816
Control18=IDC_STATIC,button,1342177287
Control19=IDC_BUTTON_UDP_RECEIVE,button,1342242816
Control20=IDC_BUTTON_TCP_SEND,button,1342242816
Control21=IDC_BUTTON_UDP_SEND_FILE,button,1342242816
Control22=IDC_TEST_EVENT,button,1342242816
Control23=IDC_STATIC,button,1342177287

[CLS:CFileOperateDlg]
Type=0
HeaderFile=FileOperateDlg.h
ImplementationFile=FileOperateDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_BUTTON_UDP_SEND_FILE

[CLS:CVariableUsingMethodDlg]
Type=0
HeaderFile=VariableUsingMethodDlg.h
ImplementationFile=VariableUsingMethodDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CVariableUsingMethodDlg
VirtualFilter=dWC

[DLG:IDD_USING_METHOD_DLG]
Type=1
Class=CUsingMethodDlg
ControlCount=28
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,button,1342177287
Control4=IDC_USING_CSTRINGARRAY,button,1342242816
Control5=IDC_STATIC,button,1342177287
Control6=IDC_WRITE_FILE,button,1342242816
Control7=ID_STATIC_INSTANCE_CLASS,button,1342242816
Control8=ID_WRITE_RECORD_INTO_DB,button,1342242816
Control9=ID_READ_CONNECT_DB_CONFIGURATION_FILE,button,1342251008
Control10=IDC_NUMBER_AND_CHARACTER_STRING_CONVERSION,button,1342185472
Control11=IDC_CONNECT_PROCESS_COMMUNICATION,button,1342251008
Control12=ID_READ_RECORD_IN_DB,button,1342242816
Control13=ID_DELETE_RECORD_FROM_DB,button,1342242816
Control14=ID_TEST_ARRAY_SLOP_OVER,button,1342242816
Control15=IDC_STATIC,button,1342177287
Control16=IDC_CREATE_SPECIFY_REGEDIT_KEY,button,1342242816
Control17=IDC_READ_SPECIFY_REGEDIT_KEY,button,1342242816
Control18=IDC_STATIC,button,1342177287
Control19=IDC_LONG_DISTANCE_CLOSE_COMPETER,button,1342251008
Control20=IDC_UDP_CONNECT_COMMUNICATION,button,1342251008
Control21=ID_TEST_LOAD_RESOURCE,button,1342242816
Control22=IDC_GET_HOST_COMPUTER_INFO,button,1342251008
Control23=IDC_TEST_ACE_COMMUNICATION,button,1342251008
Control24=ID_TEST_USING_POINT,button,1342242816
Control25=IDC_GET_COMPUTER_NAME,button,1342251008
Control26=IDC_TEST_ACE_SEND,button,1342251008
Control27=ID_TEST_GLOBAL_VARIABLE,button,1342242816
Control28=ID_EMS_MEMORY_LEAK,button,1342242816

[CLS:CUsingMethodDlg]
Type=0
HeaderFile=UsingMethodDlg.h
ImplementationFile=UsingMethodDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_READ_RECORD_IN_DB
VirtualFilter=dWC


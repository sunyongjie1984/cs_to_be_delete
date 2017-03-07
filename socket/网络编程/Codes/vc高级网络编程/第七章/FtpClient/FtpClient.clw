; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "FtpClient.h"
LastPage=0

ClassCount=5
Class1=CFtpClientApp
Class2=CFtpClientDoc
Class3=CFtpClientView
Class4=CMainFrame

ResourceCount=11
Resource1=IDD_SERV_FORMVIEW
Resource2=IDD_LOC_FORMVIEW
Resource8=IDR_LOC_SERV_MENU
Resource9=IDR_MAINFRAME
Resource10=IDD_ABOUTBOX
Class5=CAboutDlg
Resource11=CG_IDD_MYDIALOGBAR

[CLS:CFtpClientApp]
Type=0
HeaderFile=FtpClient.h
ImplementationFile=FtpClient.cpp
Filter=N

[CLS:CFtpClientDoc]
Type=0
HeaderFile=FtpClientDoc.h
ImplementationFile=FtpClientDoc.cpp
Filter=N

[CLS:CFtpClientView]
Type=0
HeaderFile=FtpClientView.h
ImplementationFile=FtpClientView.cpp
Filter=C


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=FtpClient.cpp
ImplementationFile=FtpClient.cpp
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

[DLG:IDD_SERV_FORMVIEW]
Type=1
Class=?
ControlCount=3
Control1=IDC_SERV_DIR,ComboBoxEx32,1344274690
Control2=IDC_SERV_FILE,SysListView32,1350632009
Control3=IDC_BACK,button,1342242944

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=IDC_QUICKCONNECT
Command2=ID_FILE_DISCONNECT
Command3=IDC_FILE_RECONNECT
Command4=ID_FILE_STOP
Command5=ID_FILE_REFUSE
Command6=ID_FILE_DELETE
Command7=ID_FILE_RENAME
Command8=ID_FILE_FTP_DOWNLOAD
Command9=ID_FILE_SEND
CommandCount=9

[MNU:IDR_LOC_SERV_MENU]
Type=1
Class=?
Command1=ID_FILE_SEND
Command2=ID_FILE_DELETE
Command3=ID_FILE_RENAME
Command4=ID_FILE_EXECUTE
CommandCount=4

[DLG:IDD_LOC_FORMVIEW]
Type=1
Class=?
ControlCount=2
Control1=IDC_LOC_DIR,ComboBoxEx32,1344274690
Control2=IDC_LOC_FILE,SysListView32,1350632009

[DLG:CG_IDD_MYDIALOGBAR]
Type=1
Class=?
ControlCount=9
Control1=IDC_STATIC,static,1342308865
Control2=IDC_FTPNAME,edit,1350631552
Control3=IDC_STATIC,static,1342308864
Control4=IDC_FTPUSER,edit,1350631552
Control5=IDC_STATIC,static,1342308864
Control6=IDC_FTPPASSWORD,edit,1350631584
Control7=IDC_QUICKCONNECT,button,1342242816
Control8=IDC_STATIC,static,1342308864
Control9=IDC_FTPPORT,edit,1350566017


; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSFTPDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SFTP.h"
LastPage=0

ClassCount=8
Class1=CSFTPApp
Class2=CSFTPDoc
Class3=CSFTPView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CFTPSocket
Class7=CSetupDlg
Resource3=IDD_SETUPADDR
Class8=CMessageDlg
Resource4=IDD_MESSAGE

[CLS:CSFTPApp]
Type=0
HeaderFile=SFTP.h
ImplementationFile=SFTP.cpp
Filter=N

[CLS:CSFTPDoc]
Type=0
HeaderFile=SFTPDoc.h
ImplementationFile=SFTPDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=IDC_FILE_DISCONNECT

[CLS:CSFTPView]
Type=0
HeaderFile=SFTPView.h
ImplementationFile=SFTPView.cpp
Filter=C
BaseClass=CListView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=IDC_LOGIN
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=SFTP.cpp
ImplementationFile=SFTP.cpp
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
Command1=IDC_FILE_CONNECT
Command2=IDC_FILE_DISCONNECT
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=IDC_LOGIN
Command8=ID_APP_ABOUT
CommandCount=8

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=IDC_FILE_CONNECT
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_EDIT_CUT
Command14=ID_EDIT_UNDO
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=IDC_FILE_CONNECT
Command2=IDC_FILE_DISCONNECT
Command3=ID_APP_ABOUT
CommandCount=3

[CLS:CFTPSocket]
Type=0
HeaderFile=FTPSocket.h
ImplementationFile=FTPSocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq
LastObject=CFTPSocket

[DLG:IDD_SETUPADDR]
Type=1
Class=CSetupDlg
ControlCount=20
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_SVRADDRESS,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_PORT,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_USER,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_PASS,edit,1350631584
Control11=IDC_STATIC,static,1342308352
Control12=IDC_PROXY,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_USERNAME,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_USERPASS,edit,1350631584
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,static,1342308352
Control19=IDC_PROXYTYPE,combobox,1344340226
Control20=IDC_PROXYPORT,edit,1350631552

[CLS:CSetupDlg]
Type=0
HeaderFile=SetupDlg.h
ImplementationFile=SetupDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSetupDlg

[DLG:IDD_MESSAGE]
Type=1
Class=CMessageDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_TEXTOUT,edit,1353779204

[CLS:CMessageDlg]
Type=0
HeaderFile=MessageDlg.h
ImplementationFile=MessageDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_TEXTOUT
VirtualFilter=dWC


; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyMyQQServerDlg
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MyQQServer.h"

ClassCount=7
Class1=CMyMyQQServerApp
Class2=CMyMyQQServerDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=cServerSocket
Class5=ServerSocket
Class6=ClientSocket
Class7=CClientSocket
Resource3=IDD_MY20043155MYQQSERVER05_DIALOG

[CLS:CMyMyQQServerApp]
Type=0
HeaderFile=MyQQServer.h
ImplementationFile=MyQQServer.cpp
Filter=N

[CLS:CMyMyQQServerDlg]
Type=0
HeaderFile=MyQQServerDlg.h
ImplementationFile=MyQQServerDlg.cpp
Filter=D
LastObject=CMyMyQQServerDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=MyQQServerDlg.h
ImplementationFile=MyQQServerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MY20043155MYQQSERVER05_DIALOG]
Type=1
Class=CMyMyQQServerDlg
ControlCount=12
Control1=IDC_USERLIST,listbox,1352728835
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_ACTION,button,1342242816
Control6=IDC_CLOSE,button,1476460544
Control7=IDC_STATIC,static,1342308352
Control8=IDC_UserName,combobox,1344340226
Control9=IDC_Message,edit,1350631552
Control10=IDC_BUTTON3,button,1342242816
Control11=IDC_BUTTON4,button,1342242816
Control12=IDC_STATIC,static,1342308352

[CLS:cServerSocket]
Type=0
HeaderFile=cServerSocket.h
ImplementationFile=cServerSocket.cpp
BaseClass=CSocket
Filter=N

[CLS:ServerSocket]
Type=0
HeaderFile=ServerSocket.h
ImplementationFile=ServerSocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq
LastObject=ServerSocket

[CLS:ClientSocket]
Type=0
HeaderFile=lientSocket.h
ImplementationFile=lientSocket.cpp
BaseClass=CSocket
Filter=N

[CLS:CClientSocket]
Type=0
HeaderFile=ClientSocket.h
ImplementationFile=ClientSocket.cpp
BaseClass=CSocket
Filter=N
LastObject=CClientSocket
VirtualFilter=uq


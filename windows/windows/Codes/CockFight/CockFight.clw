; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCockFightDlg
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CockFight.h"

ClassCount=6
Class1=CCockFightApp
Class2=CCockFightDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_COCKFIGHT_DIALOG
Class4=CSelCSDlg
Class5=CListenSocket
Class6=CClientSocket
Resource4=IDD_DLG_CS

[CLS:CCockFightApp]
Type=0
HeaderFile=CockFight.h
ImplementationFile=CockFight.cpp
Filter=N

[CLS:CCockFightDlg]
Type=0
HeaderFile=CockFightDlg.h
ImplementationFile=CockFightDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_LIST_HISTORY

[CLS:CAboutDlg]
Type=0
HeaderFile=CockFightDlg.h
ImplementationFile=CockFightDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_COCKFIGHT_DIALOG]
Type=1
Class=CCockFightDlg
ControlCount=12
Control1=IDC_STATIC,button,1342210055
Control2=IDOK,button,1342242816
Control3=IDC_BTN_FOREGIFT,button,1342242816
Control4=IDC_BTN_OPENONE,button,1342242816
Control5=IDC_BTN_DISCLAIM,button,1342242816
Control6=IDC_EDIT_MSG,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_BTN_SEND,button,1342242816
Control9=IDC_LIST_TOYINFO,SysListView32,1350631433
Control10=IDC_LIST_HISTORY,listbox,1352732929
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352

[DLG:IDD_DLG_CS]
Type=1
Class=CSelCSDlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDC_CMB_CS,combobox,1344340226
Control3=IDC_EDIT_SEVERNAME,edit,1350631552
Control4=IDC_EDIT_PORT,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_NAME,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_CMB_PIC,combobox,1344340226

[CLS:CSelCSDlg]
Type=0
HeaderFile=SelCSDlg.h
ImplementationFile=SelCSDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSelCSDlg
VirtualFilter=dWC

[CLS:CListenSocket]
Type=0
HeaderFile=ListenSocket.h
ImplementationFile=ListenSocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq
LastObject=CListenSocket

[CLS:CClientSocket]
Type=0
HeaderFile=ClientSocket.h
ImplementationFile=ClientSocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq
LastObject=CClientSocket


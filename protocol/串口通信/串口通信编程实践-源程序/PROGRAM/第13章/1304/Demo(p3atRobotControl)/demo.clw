; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDemoDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "demo.h"

ClassCount=3
Class1=CDemoApp
Class2=CDemoDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_DEMO_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDR_ACCELERATOR1

[CLS:CDemoApp]
Type=0
HeaderFile=demo.h
ImplementationFile=demo.cpp
Filter=N

[CLS:CDemoDlg]
Type=0
HeaderFile=demoDlg.h
ImplementationFile=demoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CDemoDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=demoDlg.h
ImplementationFile=demoDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177294
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DEMO_DIALOG]
Type=1
Class=CDemoDlg
ControlCount=48
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC2,button,1342177287
Control3=IDC_BUTTON_TURNLEFT,button,1342242816
Control4=IDC_BUTTONC_REVERSE,button,1342242816
Control5=IDC_BUTTON_TURNRIGHT,button,1342242816
Control6=IDC_BUTTON_ONWARD,button,1342242816
Control7=IDC_BUTTON_STOP,button,1342242816
Control8=IDC_STATIC,static,1342181383
Control9=IDC_STATIC,static,1342308352
Control10=IDC_COMBO_COMSELECT,combobox,1344342018
Control11=IDC_STATIC,static,1342308352
Control12=IDC_COMBO_BAUD,combobox,1344339970
Control13=IDC_STATIC,static,1342308352
Control14=IDC_COMBO_PARITY,combobox,1344339970
Control15=IDC_STATIC,static,1342308352
Control16=IDC_COMBO_DATABITS,combobox,1344339970
Control17=IDC_STATIC,static,1342308352
Control18=IDC_COMBO_STOPBITS,combobox,1344339970
Control19=IDC_BUTTON_OPENPORT,button,1342242816
Control20=IDC_STATIC_OPENOFF,static,1342177283
Control21=IDC_STATIC1,button,1342177287
Control22=IDC_BUTTON_SYN0,button,1342242816
Control23=IDC_BUTTON_STARTMOTOR,button,1342242816
Control24=IDC_BUTTON_CLOSEMOTOR,button,1342242816
Control25=IDC_BUTTON_URGENCYSTOP,button,1342242816
Control26=IDC_EDIT_RECIVE,edit,1352728644
Control27=IDC_BUTTON_STOPDISP,button,1342242816
Control28=IDC_BUTTON_CLEAR_RECI_AREA,button,1342242816
Control29=IDC_STATIC,button,1342177287
Control30=IDC_CHECK_HEXRECIEVE,button,1342242819
Control31=IDC_EDIT_SEND,edit,1352728644
Control32=IDC_STATIC,button,1342177287
Control33=IDC_CHECK_HEXSEND,button,1342242819
Control34=IDC_BUTTON_MANUALSEND,button,1342242816
Control35=IDC_CHECK_AUTOSEND,button,1342242819
Control36=IDC_EDIT_CYCLETIME,edit,1350631552
Control37=IDC_STATIC,static,1342308353
Control38=IDC_BUTTON_CLEARRECASENDA,button,1342242816
Control39=IDC_STATIC,static,1342308352
Control40=IDC_BUTTON_SYN1,button,1342242816
Control41=IDC_BUTTON_SYN2,button,1342242816
Control42=IDC_STATIC_STATUS,static,1342308352
Control43=IDC_STATIC_RXCOUNT,static,1342308352
Control44=IDC_STATIC_TXCOUNT,static,1342308352
Control45=IDC_BUTTON_COUNTRESET,button,1342242816
Control46=IDC_STATIC_ControlStatus,static,1342308352
Control47=IDC_STATIC,button,1342177287
Control48=IDC_BUTTON_RESET,button,1342242816

[ACL:IDR_ACCELERATOR1]
Type=1
Class=?
Command1=IDC_BUTTONC_REVERSE
Command2=IDC_BUTTON_TURNLEFT
Command3=IDC_BUTTON_STOP
Command4=IDC_BUTTON_TURNRIGHT
Command5=IDC_BUTTON_ONWARD
CommandCount=5


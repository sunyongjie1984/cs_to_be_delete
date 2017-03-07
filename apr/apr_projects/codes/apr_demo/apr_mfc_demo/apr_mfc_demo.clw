; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CConfigConnectorTestDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "apr_mfc_demo.h"

ClassCount=4
Class1=CApr_mfc_demoApp
Class2=CApr_mfc_demoDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_APR_MFC_DEMO_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_DLG_CONFIG_CONNECTOR_TEST
Resource4=IDD_ABOUTBOX
Class4=CConfigConnectorTestDlg
Resource5=IDR_MY_MENU

[CLS:CApr_mfc_demoApp]
Type=0
HeaderFile=apr_mfc_demo.h
ImplementationFile=apr_mfc_demo.cpp
Filter=N

[CLS:CApr_mfc_demoDlg]
Type=0
HeaderFile=apr_mfc_demoDlg.h
ImplementationFile=apr_mfc_demoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CApr_mfc_demoDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=apr_mfc_demoDlg.h
ImplementationFile=apr_mfc_demoDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_APR_MFC_DEMO_DIALOG]
Type=1
Class=CApr_mfc_demoDlg
ControlCount=1
Control1=IDC_LIST1,listbox,1352728835

[MNU:IDR_MY_MENU]
Type=1
Class=CApr_mfc_demoDlg
Command1=ID_THREAD_POOL_START
Command2=ID_THREAD_POOL_STOP
Command3=ID_THREAD_POOL_TEST
Command4=ID_SESSION_START
Command5=ID_SESSION_STOP
Command6=ID_SESSION_CONNECTOR
Command7=ID_CLEAR_LIST
CommandCount=7

[DLG:IDD_DLG_CONFIG_CONNECTOR_TEST]
Type=1
Class=CConfigConnectorTestDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_IP_ADDR,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[CLS:CConfigConnectorTestDlg]
Type=0
HeaderFile=ConfigConnectorTestDlg.h
ImplementationFile=ConfigConnectorTestDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_IP_ADDR
VirtualFilter=dWC


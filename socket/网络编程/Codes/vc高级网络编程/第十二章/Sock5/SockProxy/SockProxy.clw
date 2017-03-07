; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAsyncProxySocket
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "sockproxy.h"
LastPage=0

ClassCount=5
Class1=CAsyncProxySocket
Class2=CProxySocket
Class3=CSockProxyApp
Class4=CAboutDlg
Class5=CSockProxyDlg

ResourceCount=2
Resource1=IDD_ABOUTBOX
Resource2=IDD_SOCKPROXY_DIALOG

[CLS:CAsyncProxySocket]
Type=0
BaseClass=CAsyncSocket
HeaderFile=AsyncProxySocket.h
ImplementationFile=AsyncProxySocket.cpp
LastObject=CAsyncProxySocket
Filter=N
VirtualFilter=q

[CLS:CProxySocket]
Type=0
BaseClass=CSocket
HeaderFile=ProxySocket.h
ImplementationFile=ProxySocket.cpp

[CLS:CSockProxyApp]
Type=0
BaseClass=CWinApp
HeaderFile=SockProxy.h
ImplementationFile=SockProxy.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=SockProxyDlg.cpp
ImplementationFile=SockProxyDlg.cpp
LastObject=CAboutDlg

[CLS:CSockProxyDlg]
Type=0
BaseClass=CDialog
HeaderFile=SockProxyDlg.h
ImplementationFile=SockProxyDlg.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SOCKPROXY_DIALOG]
Type=1
Class=CSockProxyDlg
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SERVER,edit,1350631552
Control4=IDC_PORT,edit,1350631552
Control5=IDC_USER,edit,1350631552
Control6=IDC_PASS,edit,1350631584
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_TEST,button,1342242816
Control12=IDC_DEST,edit,1350631552
Control13=IDC_PORT2,edit,1350631552


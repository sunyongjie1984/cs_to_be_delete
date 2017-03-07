; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPrinterDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "printer.h"

ClassCount=3
Class1=CPrinterApp
Class2=CPrinterDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_PRINTER_DIALOG

[CLS:CPrinterApp]
Type=0
HeaderFile=printer.h
ImplementationFile=printer.cpp
Filter=N

[CLS:CPrinterDlg]
Type=0
HeaderFile=printerDlg.h
ImplementationFile=printerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CPrinterDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=printerDlg.h
ImplementationFile=printerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PRINTER_DIALOG]
Type=1
Class=CPrinterDlg
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_BUTTON2,button,1342242816
Control5=IDC_GET_PT_INFO,button,1342242816
Control6=IDC_USER,edit,1350631552
Control7=IDC_PATH,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_PASS,edit,1350631552
Control12=IDC_ADD,button,1342242816
Control13=IDC_ADD_PRINTER,button,1342242816


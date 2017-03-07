; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutTab
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "NewTab.h"

ClassCount=6
Class1=CNewTabApp
Class2=CNewTabDlg
Class3=CAboutDlg

ResourceCount=7
Resource1=IDD_OLE_PROPPAGE_SMALL (English (U.S.))
Resource2=IDR_MAINFRAME
Resource3=IDD_FORMVIEW_RELATION (English (U.S.))
Resource4=IDD_FORMVIEW_ENTROPY (English (U.S.))
Class4=CDialogEntropy
Class5=CDialogRelation
Resource5=IDD_ABOUTBOX
Resource6=IDD_NEWTAB_DIALOG
Class6=CAboutTab
Resource7=IDD_FORMVIEW (English (U.S.))

[CLS:CNewTabApp]
Type=0
HeaderFile=NewTab.h
ImplementationFile=NewTab.cpp
Filter=N

[CLS:CNewTabDlg]
Type=0
HeaderFile=NewTabDlg.h
ImplementationFile=NewTabDlg.cpp
Filter=D
LastObject=IDC_TAB_INFO
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=NewTabDlg.h
ImplementationFile=NewTabDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_NEWTAB_DIALOG]
Type=1
Class=CNewTabDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_TAB_INFO,SysTabControl32,1342177280

[DLG:IDD_FORMVIEW_RELATION (English (U.S.))]
Type=1
Class=CDialogRelation
ControlCount=1
Control1=IDC_STATIC_HISTGRAM,static,1342308352

[DLG:IDD_FORMVIEW_ENTROPY (English (U.S.))]
Type=1
Class=CDialogEntropy
ControlCount=24
Control1=IDC_BUTTON_Open,button,1342242816
Control2=IDC_BUTTON_Decode,button,1342242816
Control3=IDC_EDIT_INFILE,edit,1350631552
Control4=IDC_EDIT_OUTFILE,edit,1350631552
Control5=IDC_STATIC,static,1342308876
Control6=IDC_STATIC,static,1342308876
Control7=IDC_RADIO_ENCODE,button,1342308361
Control8=IDC_RADIO_DECODE,button,1342177289
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC_SOURCELENGTH,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC_ENTROPY,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC_CODELENGTH,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC_HEAD_LENGTH,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC_ACTUAL_LENGTH,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC_RATE,static,1342308352
Control23=IDC_STATIC,button,1342177287
Control24=IDC_BUTTON_DESTFILE,button,1342242816

[CLS:CDialogEntropy]
Type=0
HeaderFile=DialogEntropy.h
ImplementationFile=DialogEntropy.cpp
BaseClass=CTabPageSSL
Filter=D
LastObject=CDialogEntropy

[CLS:CDialogRelation]
Type=0
HeaderFile=DialogRelation.h
ImplementationFile=DialogRelation.cpp
BaseClass=CTabPageSSL
Filter=D
LastObject=CDialogRelation

[DLG:IDD_OLE_PROPPAGE_SMALL (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_FORMVIEW (English (U.S.))]
Type=1
Class=CAboutTab
ControlCount=2
Control1=IDC_STATIC,static,1342308352
Control2=IDC_BUTTON_EMAIL,button,1342242816

[CLS:CAboutTab]
Type=0
HeaderFile=AboutTab.h
ImplementationFile=AboutTab.cpp
BaseClass=CTabPageSSL
Filter=D
VirtualFilter=dWC


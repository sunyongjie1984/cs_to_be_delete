// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SCC.h"

#include "MainFrm.h"
#include "Transmit.h"
#include "DlgAutoSave.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define _countof(array) (sizeof(array)/sizeof(array[0]))
static UINT Toolbars[] = {IDR_MAINFRAME,IDR_SCC_TOOL,IDR_TOOLBAR_SHELL};
#define WM_ALWAYSONTOP	WM_USER + 5
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CGuiFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CGuiFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_XSAVE, OnFileXsave)
	ON_UPDATE_COMMAND_UI(ID_FILE_XSAVE, OnUpdateFileXsave)
	ON_WM_MENUSELECT()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
	ON_CBN_SELENDOK(ID_SCC_SET_COM, OnSCCComboComSelok)
	ON_COMMAND_EX(IDR_SCC_TOOL, OnBarCheck)
	ON_UPDATE_COMMAND_UI(IDR_SCC_TOOL, OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_VIEW_SFWND, OnBarCheck)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SFWND, OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_VIEW_TOOLBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR, OnUpdateControlBarMenu)
	ON_COMMAND_RANGE(ID_SCC_SET_OPTION,ID_SCC_ADDECHO,OnSCCCommon)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SCC_SET_OPTION,ID_SCC_ADDECHO,OnUpdateSCCCommon)
	ON_COMMAND_RANGE(ID_CS_ADDSUM,ID_CS_7,OnSCCCS)
	ON_UPDATE_COMMAND_UI_RANGE(ID_CS_ADDSUM,ID_CS_7,OnUpdateSCCCS)
	ON_COMMAND_RANGE(ID_FILE_MRU_FILE1,ID_FILE_MRU_FILE16,OnSCCMRU)
	ON_COMMAND_RANGE(ID_VIEW_CENTER,ID_FILE_SAVESEND,OnSCCView)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_CENTER,ID_FILE_SAVESEND,OnUpdateSCCView)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	SCC_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction
SCC_MSG_MAP_X(CMainFrame,RecvSCCMsg)

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_nCurCOM=0;
	m_bSPort=1,m_bSSend=0,m_bSTime=0;
	m_bAscRecv=0,m_bAscSend=0;
	m_bAddEnter=0,m_bAddStx=0,m_bAddEtx=0;
	m_bAddEcho=0;
	m_bPauseDis=0;
	m_nToolBtns=0;
	m_bToNext=0;
	m_unCycTimer=0;
	m_dwMs=::GetTickCount();
	m_unMulti=0;
	m_bTrigger=0;
	m_btTrigger=0;
	m_btTriggerCOM=0;
	Trasmt.bCOM=0;
	m_bFilter=0;
	AutoSave.bSave=0;
	AutoSave.bClear=0;
	AutoSave.nTime=1;
	AutoSave.strPath="";
	m_bAutoMenuEnable  = FALSE;
}

CMainFrame::~CMainFrame()
{
	
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGuiFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	InitMenu(IDR_MAINFRAME);
	InitToolBar(ID_VIEW_TOOLBAR,IDR_MAINFRAME);
	InitStatusBar(indicators,sizeof(indicators)/sizeof(UINT));
//============================
	if (!m_wndSCCTool.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_SCC_TOOL) ||
		!m_wndSCCTool.LoadToolBar(IDR_SCC_TOOL))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	CreateSCCTool();
	UINT uHis=AfxGetApp()->GetProfileInt("Settings","COMHis",0);
	m_comboCOM.SetCurSel(uHis);
	CSerialPort *psp=new CSerialPort;
	psp->m_nCOMNo=uHis;
	if(CSCCTools::RWReg(psp))	SetCOMParam(psp,1);
	delete psp;
	psp=NULL;	

	CreateImagelist();
//============================
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable	
//	CMenu*pSysMenu=GetSystemMenu(FALSE);
//	pSysMenu->InsertMenu(5,MF_BYPOSITION,MF_SEPARATOR);
//	pSysMenu->InsertMenu(6,MF_BYPOSITION, ID_ALWAYSONTOP,"总在最上面(&A)");
//	pSysMenu->AppendMenu(MF_SEPARATOR);
//	pSysMenu->AppendMenu(MF_STRING, WM_ALWAYSONTOP,"总在最上面(&A)");
//======================================
	if(!m_wndSF.CreateX(_T("发报窗"),this,ID_VIEW_SFWND))		return -1;

	EnableDocking(CBRS_ALIGN_ANY);
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndSCCTool.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndSF.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndMenuBar);
	DockControlBar(&m_wndSCCTool);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndSF,AFX_IDW_DOCKBAR_LEFT);
	
	sProfile = _T("MFW");
	LoadBars();
	m_dlgSend.Create(IDD_DIALOG_SEND,this);
	m_dlgFilter.Create(IDD_DIALOG_FILTER,this);
//========================
	DWORD dwConfig=AfxGetApp()->GetProfileInt("Settings","Common",1);
	m_bSPort=dwConfig&0x01;m_bSSend=(dwConfig&0x02)>>1;m_bSTime=(dwConfig&0x04)>>2;
	m_bAscRecv=(dwConfig&0x08)>>3;m_bAscSend=(dwConfig&0x10)>>4;
	m_bAddEnter=(dwConfig&0x20)>>5;m_bAddStx=(dwConfig&0x40)>>6;
	m_bAddEtx=(dwConfig&0x80)>>7;
	if(dwConfig&0x100)	SetWindowPos(&wndTopMost,0, 0, 0, 0,SWP_NOSIZE|SWP_NOMOVE);
	AutoSave.strPath=AfxGetApp()->GetProfileString("Settings","AutoSave");
	if(AutoSave.strPath.IsEmpty())	
	{
		AutoSave.strPath=AfxGetApp()->m_pszAppName;
		int position=AutoSave.strPath.ReverseFind('\\'); 
		if(position!=-1)	AutoSave.strPath=AutoSave.strPath.Left(position+1);
		else	AutoSave.strPath="c:\\";
	}
	dwConfig=AfxGetApp()->GetProfileInt("Settings","ASTime",0x00010001);
	AutoSave.nTime=dwConfig;
//	AutoSave.nTime=HIWORD(dwConfig);
//	AutoSave.bClear=(BOOL)(LOWORD(dwConfig));

//======================
	m_wndCool.LoadToolbars(Toolbars, _countof(Toolbars));
	EnableToolTips();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CGuiFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style &=~FWS_ADDTOTITLE ;
	cs.lpszName=_T("SCC－串口监视工具");
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CGuiFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CGuiFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::CreateSCCTool()
{
	CString str;
	m_wndSCCTool.CreateCombo(&m_comboCOM,ID_SCC_SET_COM,60,WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST |WS_VSCROLL | WS_TABSTOP);
	for(int i=0;i<256;i++)
	{
		str.Format("COM%d",i+1);
		m_comboCOM.AddString(str);
	}
	m_comboCOM.SetCurSel(0);

	m_wndSCCTool.CreateCombo(&m_comboBaud,ID_SCC_SET_BAUD,60,WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST |WS_VSCROLL | WS_TABSTOP);
	for(i=0;i<23;i++)
		m_comboBaud.AddString(CSCCTools::GetParStr(i,0,1));
	m_comboBaud.SetCurSel(4);

	m_wndSCCTool.CreateCombo(&m_comboParity,ID_SCC_SET_PARITY,60,WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST |WS_VSCROLL | WS_TABSTOP);
	m_comboParity.AddString("无校验");
	m_comboParity.AddString("奇校验");
	m_comboParity.AddString("偶校验");
	m_comboParity.AddString("Mark");
	m_comboParity.AddString("Space");
	m_comboParity.SetCurSel(0);

	m_wndSCCTool.CreateCombo(&m_comboData,ID_SCC_SET_DATA,30,WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST |WS_VSCROLL | WS_TABSTOP);
	m_comboData.AddString("8");
	m_comboData.AddString("7");
	m_comboData.AddString("6");
	m_comboData.AddString("5");
	m_comboData.AddString("4");
	m_comboData.SetCurSel(0);


	m_wndSCCTool.CreateCombo(&m_comboStop,ID_SCC_SET_STOP,30,WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST |WS_VSCROLL | WS_TABSTOP);
	m_comboStop.AddString("1");
	m_comboStop.AddString("1.5");
	m_comboStop.AddString("2");
	m_comboStop.SetCurSel(0);

	m_wndSCCTool.CreateCombo(&m_comboRTO,ID_SCC_SET_RTO,40,WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST |WS_VSCROLL | WS_TABSTOP);
	for(i=0;i<15;i++)
	{
		str.Format("%d",(i+1)*20);
		m_comboRTO.AddString(str);
	}
	m_comboRTO.SetCurSel(0);
	m_wndSCCTool.CreateCombo(&m_comboFC,ID_SCC_SET_FLOW,40,WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST |WS_VSCROLL | WS_TABSTOP);
	m_comboFC.AddString("无");
	m_comboFC.AddString("RTS/CTS");
	m_comboFC.AddString("XON/XOFF");
	m_comboFC.AddString("DTR/CTS");
	m_comboFC.AddString("RTS/DSR");
	m_comboFC.AddString("DTR/DSR");
	m_comboFC.SetCurSel(0);
	m_comboFC.EnableWindow(0);

	str.Empty();
}

void CMainFrame::OnSCCComboComSelok()
{
	m_nCurCOM=m_comboCOM.GetCurSel();
	int nCurSelIndex=m_ascc.GetCOMIndex(m_nCurCOM) ;

	if(nCurSelIndex!=-1)
	{
		SetCOMParam(m_ascc.GetCOM(nCurSelIndex),1);
		EnableSCCBtn(!m_ascc.IsCOMOpen(m_nCurCOM));
	//	m_wndSendFrame.EnableButton(0,(m_scc.IsCOMOpen(m_nCurCOM)==1));
	}
	else
	{
		EnableSCCBtn();
	//	m_wndSendFrame.EnableButton(0,0);
		CSerialPort *psp=new CSerialPort;
		psp->m_nCOMNo=m_nCurCOM;
		if(CSCCTools::RWReg(psp))		SetCOMParam(psp,1);
		else SetCOMParam(NULL,2);
		delete psp;
		psp=NULL;
	}
	ReplaceBtnIcon(ID_SCC_OPEN,IsCOMOpen()?m_nToolBtns+1:2);
}

void CMainFrame::EnableSCCBtn(BOOL bEnable)
{
	m_comboBaud.EnableWindow(bEnable);
	m_comboParity.EnableWindow(bEnable);
	m_comboData.EnableWindow(bEnable);
	m_comboStop.EnableWindow(bEnable);
	m_comboRTO.EnableWindow(bEnable);
}

void CMainFrame::SetCOMParam(CSerialPort *psp, int nSet)
{
	if(nSet==0)	//以当前组合框值设置当前所选串口
	{
		psp->m_nBaudRate=CSCCTools::GetParams(m_comboBaud.GetCurSel(),0);
		psp->m_nParityBit=CSCCTools::GetParams(m_comboParity.GetCurSel(),1);
		psp->m_nDataBit=CSCCTools::GetParams(m_comboData.GetCurSel(),2);
		psp->m_nStopBit=CSCCTools::GetParams(m_comboStop.GetCurSel(),3);
		psp->m_nRTO=(m_comboRTO.GetCurSel()+1)*20;
	}
	else if(nSet==1)//设置当前所选串口
	{
		m_comboBaud.SetCurSel(CSCCTools::GetParIndex(psp->m_nBaudRate,0));
		m_comboParity.SetCurSel(CSCCTools::GetParIndex(psp->m_nParityBit,1));
		m_comboData.SetCurSel(CSCCTools::GetParIndex(psp->m_nDataBit,2));
		m_comboStop.SetCurSel(CSCCTools::GetParIndex(psp->m_nStopBit,3));
		m_comboRTO.SetCurSel((psp->m_nRTO>=20)?(psp->m_nRTO/20-1):0);
	}
	else if(nSet==2)//设置组合框
	{
		m_comboBaud.SetCurSel(CSCCTools::GetParIndex(9600,0));
		m_comboParity.SetCurSel(CSCCTools::GetParIndex(NOPARITY,1));
		m_comboData.SetCurSel(CSCCTools::GetParIndex(8,2));
		m_comboStop.SetCurSel(CSCCTools::GetParIndex(ONESTOPBIT,3));
		m_comboRTO.SetCurSel(0);
	}
	else//设置当前所选串口
	{
		psp->m_nBaudRate=9600;
		psp->m_nParityBit=NOPARITY;
		psp->m_nDataBit=8;
		psp->m_nStopBit=ONESTOPBIT;
		psp->m_nRTO=20;
	}
}

BOOL CMainFrame::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_ascc.SaveConfig();
	AfxGetApp()->WriteProfileInt("Settings","COMHis",m_nCurCOM);
	DWORD dwConfig=m_bSPort|(m_bSSend<<1)|(m_bSTime<<2)|
				(m_bAscRecv<<3)|(m_bAscSend<<4)|
				(m_bAddEnter<<5)|(m_bAddStx<<6)|(m_bAddEtx<<7);
	DWORD dwTmp=AfxGetApp()->GetProfileInt("Settings","Common",1);
	dwConfig|=dwTmp&0x100;
	AfxGetApp()->WriteProfileInt("Settings","Common",dwConfig);
	AfxGetApp()->WriteProfileString("Settings","AutoSave",AutoSave.strPath);
//	AfxGetApp()->WriteProfileInt("Settings","ASTime",MAKELPARAM(AutoSave.bClear,AutoSave.nTime));
	AfxGetApp()->WriteProfileInt("Settings","ASTime",AutoSave.nTime);

	m_wndSF.SaveConfig();
	if(m_dlgSend.m_hWnd)	m_dlgSend.DestroyWindow();
	if(m_dlgFilter.m_hWnd)	m_dlgFilter.DestroyWindow();
	if(m_unCycTimer!=0)	KillTimer(m_unCycTimer);
	return CGuiFrameWnd::DestroyWindow();
}

void CMainFrame::OnSCCCommon(UINT nID)
{
	if(nID==ID_VIEW_WRAP)	GetView()->SetWrap(!GetView()->GetWrapMode());
	else if(nID==ID_VIEW_SCC_PORT)	m_bSPort=!m_bSPort;
	else if(nID==ID_VIEW_SCC_SEND)	m_bSSend=!m_bSSend;
	else if(nID==ID_VIEW_SCC_TIME)	m_bSTime=!m_bSTime;
	else if(nID==ID_SCC_ASCRECV)	m_bAscRecv=!m_bAscRecv;
	else if(nID==ID_SCC_ASCSEND)	m_bAscSend=!m_bAscSend;
	else if(nID==ID_SCC_ADDENTER)	m_bAddEnter=!m_bAddEnter;
	else if(nID==ID_SCC_ADDSTX)		m_bAddStx=!m_bAddStx;
	else if(nID==ID_SCC_ADDETX)		m_bAddEtx=!m_bAddEtx;
	else if(nID==ID_SCC_ADDECHO)	m_bAddEcho=!m_bAddEcho;
	else if(nID==ID_SCC_PAUSE)		m_bPauseDis=!m_bPauseDis;
	else if(nID==ID_SCC_GONEXT)		m_bToNext=!m_bToNext;
	else if(nID==ID_SCC_READONLY)	GetView()->SetReadOnly(!GetView()->GetReadOnly());
	else if(nID==ID_SCC_SENDLINE)	
	{
		if(!SendLine(m_nCurCOM))	AfxMessageBox("报文格式不对！组合键Ctrl+Alt+P分析错误！");
	}
	else if(nID==ID_SCC_SET_OPTION)
	{
		if(IsCOMOpen())	return;
		SetCOMParam(NULL,2);
	}
	else if(nID==ID_SCC_CLEARDATA)
	{
		GetView()->ClearDatas();
		GetView()->SetMF();
	}
	else if(nID==ID_SCC_OPEN)
	{
		int nCOMNo=m_comboCOM.GetCurSel();
		if(m_ascc.IsCOMOpen(nCOMNo))
		{
			if(m_ascc.CloseCOM(nCOMNo))	EnableSCCBtn(1);
		}
		else
		{
			int nIndex=m_ascc.GetCOMIndex(nCOMNo);
			CSerialPort *psp;
			if(nIndex==-1)	psp=new CSerialPort;
			else			psp=m_ascc.GetCOM(nIndex);
			SetCOMParam(psp,0);
			if(m_ascc.OpenCOM(psp,this,nCOMNo))
			{
				EnableSCCBtn(0);
				m_nCurCOM=nCOMNo;
			}
			else
			{
				if(psp!=NULL)	delete psp;
				psp=NULL;
			}
			if(nIndex!=-1)	psp=NULL;
		}
		ReplaceBtnIcon(ID_SCC_OPEN,IsCOMOpen(nCOMNo)?m_nToolBtns+1:2);
	}
}

void CMainFrame::OnUpdateSCCCommon(CCmdUI* pCmdUI)
{
	if(pCmdUI->m_nID ==ID_VIEW_WRAP)	pCmdUI->SetCheck(GetView()->GetWrapMode());
	else if(pCmdUI->m_nID ==ID_VIEW_SCC_PORT)	pCmdUI->SetCheck(m_bSPort);
	else if(pCmdUI->m_nID ==ID_VIEW_SCC_SEND)	pCmdUI->SetCheck(m_bSSend);
	else if(pCmdUI->m_nID ==ID_VIEW_SCC_TIME)	pCmdUI->SetCheck(m_bSTime);
	else if(pCmdUI->m_nID ==ID_SCC_ASCRECV)		pCmdUI->SetCheck(m_bAscRecv);
	else if(pCmdUI->m_nID ==ID_SCC_ASCSEND)		pCmdUI->SetCheck(m_bAscSend);
	else if(pCmdUI->m_nID ==ID_SCC_GONEXT)		pCmdUI->SetCheck(m_bToNext);
	else if(pCmdUI->m_nID ==ID_SCC_READONLY)	pCmdUI->SetCheck(GetView()->GetReadOnly());
	else if(pCmdUI->m_nID ==ID_SCC_SENDLINE)	pCmdUI->Enable(IsCOMOpen());
	else if(pCmdUI->m_nID ==ID_SCC_SET_OPTION)	pCmdUI->Enable(!IsCOMOpen());
	else if(pCmdUI->m_nID ==ID_SCC_ADDENTER)
	{
		pCmdUI->Enable(m_bAscSend);
		pCmdUI->SetCheck(m_bAddEnter);
	}
	else if(pCmdUI->m_nID ==ID_SCC_ADDECHO)
	{
		pCmdUI->Enable(m_bAscSend);
		pCmdUI->SetCheck(m_bAddEcho);
	}
	else if(pCmdUI->m_nID ==ID_SCC_ADDSTX)		
	{
		pCmdUI->Enable(m_bAscSend);
		pCmdUI->SetCheck(m_bAddStx);
	}
	else if(pCmdUI->m_nID ==ID_SCC_ADDETX)		
	{
		pCmdUI->Enable(m_bAscSend);
		pCmdUI->SetCheck(m_bAddEtx);
	}
	else if(pCmdUI->m_nID ==ID_SCC_PAUSE)		
	{
		pCmdUI->SetCheck(m_bPauseDis);
		pCmdUI->SetText(m_bPauseDis?"继续报文监视(&P)":"暂停报文监视(&P)");
	}
	else if(pCmdUI->m_nID ==ID_SCC_OPEN)		
	{
		CString str;
		str.Format("COM%d",m_nCurCOM+1);
		if(IsCOMOpen())	str="关闭"+str+"(&O)";
		else	str="打开"+str+"(&O)";
		pCmdUI->SetText(str);
		str.Empty();
	}
}

void CMainFrame::DisplayStr(CString str, int nCOMIndex,BOOL bRecv,BOOL bEnter)
{
	if(m_bPauseDis)	return;
	if(!bRecv&&!m_bSSend)	return;
	if(m_dlgFilter.m_nFilter==1)
	{
		if(nCOMIndex!=m_nCurCOM)	return;
	}
	CString strtmp,str1;
	CSCCView* pView=GetView();
	if(m_bSTime)
	{
		_strtime( strtmp.GetBuffer(9) );
		strtmp.ReleaseBuffer();
	//	strtmp="["+strtmp+"] ";
		str1.Format(" %03.0d",(::GetTickCount()-m_dwMs)%1000);
		m_dwMs=::GetTickCount();
		strtmp="["+strtmp+str1+"] ";
		pView->AddString(strtmp,5);
	}
	if(m_bSPort)//↑↓
	{
		pView->AddString("COM",5);
		if(bRecv)	strtmp.Format("%d",nCOMIndex+1);
		else		strtmp.Format("%d",nCOMIndex+1);
		pView->AddString(strtmp,1);
		if(bRecv)	pView->AddString("↑",5);
		else		pView->AddString("↓",5);
	}
	strtmp.Empty();
	str1.Empty();
	str+='\n';
	pView->AddString(str,bRecv?3:4);
	pView=NULL;
}

void CMainFrame::CreateImagelist()
{
	CImageList* m_imgList1;
	m_imgList1=(m_wndToolBar.GetToolBarCtrl()).GetImageList();
	m_nToolBtns=m_imgList1->GetImageCount();
	CBitmap cbmp;
	BITMAP bmp;
//	m_imgList1.Create(IDB_BITMAP1,16,27,RGB (255, 0, 0));
	cbmp.LoadBitmap(IDR_TOOLBAR_SHELL);
	cbmp.GetBitmap(&bmp);
	m_imgList1->Add(&cbmp,RGB (192, 192, 192));
	(m_wndToolBar.GetToolBarCtrl()).SetImageList(m_imgList1);
	m_imgList1->Detach();
	m_imgList1=NULL;
	cbmp.DeleteObject();
}

void CMainFrame::ReplaceBtnIcon(UINT unID, int nNew)
{
	int nIndex=m_wndToolBar.CommandToIndex(unID);
//	m_imgList1=(m_wndToolBar.GetToolBarCtrl()).GetImageList();
//	m_imgList1->Replace(0,m_imgList1->ExtractIcon(2));
//	m_imgList1->Detach();
//	m_wndToolBar.Invalidate();
	m_wndToolBar.SetButtonInfo(nIndex,unID,TBBS_BUTTON,nNew);
/*
m_wndToolBar.LoadToolBar(IDR_MAINFRAME);
//调入新的工具栏后，调用Invalidate函数以确保使用新的位图图象重画工具栏；
m_wndToolBar.Invalidate();
CMenu cMenu;
//调用新的以IDR_NEWMENU表示的菜单资源；
cMenu.LoadMenu(IDR_MAINFRAME);
//将cMenu设置为当前菜单；
SetMenu(&cMenu);
//释放菜单句柄 cMenu.Detach();
//重画菜单条；
DrawMenuBar();
//重新绘制窗口区域；
RecalcLayout(TRUE);
	*/
}

BOOL CMainFrame::IsCOMOpen(int nCOMIndex)
{
	if(nCOMIndex==-1)	nCOMIndex=m_nCurCOM;
	int nIndex=m_ascc.GetCOMIndex(nCOMIndex);
	if(nIndex==-1)	return 0;
	return m_ascc.GetCOM(nIndex)->IsOpen();
}

CSerialPort* CMainFrame::GetCOM(int nCOMIndex)
{
	if(nCOMIndex==-1)	nCOMIndex=m_nCurCOM;
	int nIndex=m_ascc.GetCOMIndex(nCOMIndex);
	if(nIndex==-1)	return NULL;
	return m_ascc.GetCOM(nIndex);
}

void CMainFrame::RecvSCCMsg(WPARAM wParam, LPARAM lParam)
{
	LPBYTE lpbtBuffer = (LPBYTE)::GlobalLock((HGLOBAL)wParam);
	WORD lPortNo=LOWORD(lParam);
	WORD lLength=HIWORD(lParam);
	//======
	CString str;
	m_bFilter=0;
	if(m_bAscRecv)	
	{
		str=((CString)lpbtBuffer).Left (lLength);
		m_bFilter=1;
	}
	else	
	{
		if(IsFilterFrame(lpbtBuffer,lLength))
		{
			str=CSCCTools::HexToStr(lpbtBuffer,lLength);
			m_bFilter=1;
		}	
	}
	if(m_bFilter)	DisplayStr(str,lPortNo);

	Transmits(lPortNo,lpbtBuffer,lLength);
	if(m_bTrigger)
	{
		int nl=IsTriggerLine(str);
		if(nl!=-1)
		{
			if(m_dlgSend.m_unTrigger==0)	
				SendLine(lPortNo,m_dlgSend.Trigger[nl].unTrigger-1);
			else	
			{
				m_btTrigger=nl;
				m_btTriggerCOM=(BYTE)lPortNo;
				SetTimer(102,m_dlgSend.m_unTrigger,NULL);
			}
		}
	}
	str.Empty();
	::GlobalUnlock((HGLOBAL)wParam);
}

int CMainFrame::AscSendAdd(CString &str)
{
	if(m_bAscSend)	
	{
		if(m_bAddStx)	str=(TCHAR)0x02+str;
		if(m_bAddEtx)	str+=(TCHAR)0x03;
		if(m_bAddEnter)	str+='\r';//str+=(TCHAR)0x0D;
		if(m_bAddEcho)	str+='\n';
	}
	return str.GetLength();
}

BOOL CMainFrame::SendLine(int nCOMIndex, int nLineIndex)
{
	if(!IsCOMOpen(nCOMIndex))	return 1;
	CString str;
	int nlength=m_wndSF.m_xrec.GetLineStr(str,nLineIndex);
	if(str.IsEmpty())	
	{
//		AfxMessageBox("空行！");
		m_wndSF.m_xrec.SetFocus();
		return 0;
	}
	if(m_bAscSend)
	{
		AscSendAdd(str);
		DisplayStr(str,nCOMIndex,0);
		GetCOM(nCOMIndex)->WriteData(str);
		if(m_bToNext)	m_wndSF.m_xrec.GotoLine(1,nLineIndex);
		return 1;
	}
	if(!m_wndSF.m_xrec.IsHexFormat(str) )
	{
//		AfxMessageBox("格式不对！组合键Ctrl+Alt+P分析错误！");
		m_wndSF.m_xrec.SetFocus();
		return 0;
	}
		BYTE btData[MAX_SCC_SEND_LEN];
		int nBytes=m_wndSF.m_xrec.StrToHex(str,btData);
		DisplayStr(str,nCOMIndex,0);
		GetCOM(nCOMIndex)->WriteData(btData,nBytes);	
		if(m_bToNext)	m_wndSF.m_xrec.GotoLine(1,nLineIndex);
		return 1;
}

void CMainFrame::OnSCCCS(UINT nID)
{
	if(nID==ID_CS_ADDSUM)		m_wndSF.m_xrec.CheckSum(4);
	if(nID==ID_CS_ADDSUMWORD)	m_wndSF.m_xrec.CheckSum(5);
	if(nID==ID_CS_MODBUS)		m_wndSF.m_xrec.CheckSum(0);
	if(nID==ID_CS_CRC_CCITT16)	m_wndSF.m_xrec.CheckSum(1);
	if(nID==ID_CS_CRC_CCITT8)	m_wndSF.m_xrec.CheckSum(2);
	if(nID==ID_CS_CRC_ANSI16)	m_wndSF.m_xrec.CheckSum(3);

}

void CMainFrame::OnUpdateSCCCS(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_wndSF.IsVisible());
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
		if(IsCASDown(4))//ctrl+alt
		{
			switch (pMsg->wParam)
			{  
			case 'C':
				m_comboCOM.SetFocus();
				return TRUE;
			case 'S':
				m_wndSF.m_xrec.SetFocus();
				return TRUE;
			}
		}
		break;
	}
	
	return CGuiFrameWnd::PreTranslateMessage(pMsg);
}

BOOL CMainFrame::IsCASDown(int nFlag)
{
	if(nFlag==0)		return (::GetKeyState(VK_CONTROL) < 0);
	else if(nFlag==1)	return (::GetKeyState(VK_MENU) < 0);
	else if(nFlag==2)	return (::GetKeyState(VK_SHIFT) < 0);
	else if(nFlag==3)	
	{
		return	(::GetKeyState(VK_CONTROL) < 0)&&(::GetKeyState(VK_MENU) >= 0)
			&&(::GetKeyState(VK_SHIFT) >= 0);
	}
	else if(nFlag==4)	
	{
		return	(::GetKeyState(VK_CONTROL)<0)&&(::GetKeyState(VK_MENU)  <  0)
			&&(::GetKeyState(VK_SHIFT) >= 0);
	}
	return 0;
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case 101:
		{
			int nLine=-1;
			if(m_dlgSend.m_nCycMode==0)
			{
				if(m_dlgSend.m_nCycSel==1)	nLine=m_dlgSend.m_unLine-1;
			}
			else
			{
				nLine=m_unMulti-1;
				m_unMulti++;		
				if(m_unMulti>m_dlgSend.m_unEnd)	m_unMulti=m_dlgSend.m_unStart;
			}
			if(!SendLine(m_nCurCOM,nLine))
			{
				KillTimer(m_unCycTimer);
				m_unCycTimer=0;
				AfxMessageBox("报文格式不对！组合键Ctrl+Alt+P分析错误！");
			}
		}
		break;
	case 102:
		{
			SendLine(m_btTriggerCOM,m_dlgSend.Trigger[m_btTrigger].unTrigger-1);			
			KillTimer(102);
		}
		break;
	case 103:
		{
			if(!AutoSave.bSave&&!AutoSave.bClear)	KillTimer(103);
			if(AutoSave.bSave)
			{
				CTime ttmp=CTime::GetCurrentTime();
				CString strs;
				strs.Format ("%04d%02d%02d %02d%02d",ttmp.GetYear (),ttmp.GetMonth (),ttmp.GetDay (),
					ttmp.GetHour(),ttmp.GetMinute());
				strs=AutoSave.strPath+strs+".pcf";
				GetView()->SaveFile(strs);
				strs.Empty();
			}
			if(AutoSave.bClear)	SendMessage(WM_COMMAND,ID_SCC_CLEARDATA);
		}
		break;
	}
	CGuiFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnFileOpen() 
{
	// TODO: Add your command handler code here
	CString strs=GetRWPath(1,"打开串口监视报文");
	if(!strs.IsEmpty())
	{
		if(GetView()->LoadFile(strs))	AfxGetApp()->AddToRecentFileList(strs);
		strs.Empty();
	}
}

void CMainFrame::OnFileXsave() 
{
	// TODO: Add your command handler code here
	CTime ttmp=CTime::GetCurrentTime();
	CString strs;
	strs.Format ("%04d%02d%02d %02d%02d",ttmp.GetYear (),ttmp.GetMonth (),ttmp.GetDay (),
		ttmp.GetHour(),ttmp.GetMinute());
	strs=GetRWPath(0,"保存串口监视报文",strs);
	if(!strs.IsEmpty())
	{
		if(GetView()->SaveFile(strs))	AfxGetApp()->AddToRecentFileList(strs);
		strs.Empty();
	}
}

void CMainFrame::OnUpdateFileXsave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(GetView()->IsModifyed());
}

void CMainFrame::OnSCCMRU(UINT nID)
{
	int nIndex = nID - ID_FILE_MRU_FILE1;
	ASSERT((*(theApp.GetFileList()))[nIndex].GetLength() != 0);
	if (!GetView()->LoadFile((*(theApp.GetFileList()))[nIndex]))
		theApp.RemoveFile(nIndex);
}
void CMainFrame::OnSCCView(UINT nID)
{
	int ny=GetSystemMetrics(SM_CYSCREEN);
	int nx=GetSystemMetrics(SM_CXSCREEN);
	if(nID==ID_VIEW_CENTER)	MoveWindow(CRect(nx/4,ny/4,nx*3/4,ny*3/4));
	else if(nID==ID_VIEW_TOPHARF)		MoveWindow(CRect(0,0,nx,ny/2));
	else if(nID==ID_VIEW_BOTTOMHARF)	MoveWindow(CRect(0,ny/2,nx,ny));
	else if(nID==ID_VIEW_LEFTHARF)		MoveWindow(CRect(0,0,nx/2,ny));
	else if(nID==ID_VIEW_RIGHTHARF)		MoveWindow(CRect(nx/2,0,nx,ny));
	else if(nID==ID_ALWAYSONTOP)	
	{
		DWORD dwConfig=AfxGetApp()->GetProfileInt("Settings","Common",1);
		if(GetExStyle()&WS_EX_TOPMOST)
		{
			SetWindowPos(&wndNoTopMost,0, 0, 0, 0,SWP_NOSIZE|SWP_NOMOVE);
			dwConfig&=0xFEFF;
		}
		else
		{
			SetWindowPos(&wndTopMost,0, 0, 0, 0,SWP_NOSIZE|SWP_NOMOVE);
			dwConfig|=0x100;
		}
		AfxGetApp()->WriteProfileInt("Settings","Common",dwConfig);
	}
	else if(nID==ID_ADVANCE_SEND)	
	{
		m_dlgSend.ShowWindow(1);
		m_dlgSend.SetFocus();
	}
	else if(nID==ID_SCC_CYCSEND)
	{
		if(m_unCycTimer==0)	
		{
			m_unCycTimer=SetTimer(101,m_dlgSend.m_unTime,NULL);
			m_unMulti=m_dlgSend.m_unStart;
		}
		else
		{
			KillTimer(m_unCycTimer);
			m_unCycTimer=0;
		}
	}
	else if(nID==ID_SCC_TRIGGER)
	{
		m_bTrigger=!m_bTrigger;
	}
	else if(nID==ID_SCC_TRANSMIT)
	{
		CTransmit dlgTrans;
		if(dlgTrans.DoModal()==IDCANCEL)
		{
			Trasmt.bCOM=dlgTrans.m_bCOM;
			Trasmt.btCOM1=dlgTrans.m_btCOM1;
			Trasmt.btCOM2=dlgTrans.m_btCOM2;
		}
	}
	else if(nID==ID_FILE_AUTOSAVE)
	{
		CDlgAutoSave dlgAS;
		dlgAS.m_bAS=AutoSave.bSave;
		dlgAS.m_bClear=AutoSave.bClear;
		dlgAS.m_nASTime=AutoSave.nTime;
		dlgAS.m_strPath=AutoSave.strPath;
		if(dlgAS.DoModal()==IDOK)
		{
			KillTimer(103);
			AutoSave.strPath=dlgAS.m_strPath;
			AutoSave.bClear=dlgAS.m_bClear;
			AutoSave.bSave=dlgAS.m_bAS;
			AutoSave.nTime=dlgAS.m_nASTime;
			if(AutoSave.bSave||AutoSave.bClear)	
				SetTimer(103,AutoSave.nTime*60*1000,NULL);
		}
	}
	else if(nID==ID_SHOW_FILTER)
	{
		m_dlgFilter.ShowWindow(1);
		m_dlgFilter.SetFocus();
	}
	else if(nID==ID_FILE_OPENS)
	{
		CString strs=GetRWPath(1,"打开发送窗报文");
		if(!strs.IsEmpty())
		{
			m_wndSF.m_xrec.LoadFile(strs);
			strs.Empty();
		}
	}
	else if(nID==ID_FILE_SAVESEND)
	{
		CString strs=GetRWPath(0,"保存发送窗报文","SCC");
		if(!strs.IsEmpty())
		{
			m_wndSF.m_xrec.SaveFile(strs);
			strs.Empty();
		}
	}
}
void CMainFrame::OnUpdateSCCView(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(pCmdUI->m_nID ==ID_ALWAYSONTOP)	pCmdUI->SetCheck(GetExStyle()&WS_EX_TOPMOST);
	else if(pCmdUI->m_nID ==ID_ADVANCE_SEND)	
	{
	//	pCmdUI->SetCheck(m_dlgSend.IsWindowVisible());
	//	pCmdUI->SetText(m_dlgSend.IsWindowVisible()?"隐藏高级发送窗(&A)":"显示高级发送窗(&A)");
	}
	else if(pCmdUI->m_nID ==ID_SCC_CYCSEND)	
	{
		pCmdUI->SetCheck(m_unCycTimer!=0);
	}
	else if(pCmdUI->m_nID ==ID_SCC_TRIGGER)	
	{
		pCmdUI->SetCheck(m_bTrigger);
	}
	else if((pCmdUI->m_nID ==ID_FILE_OPENS)	||(pCmdUI->m_nID ==ID_FILE_SAVESEND))
	{
		pCmdUI->Enable(m_wndSF.IsVisible());
	}
}

void CMainFrame::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu) 
{
//	CGuiFrameWnd::OnMenuSelect(nItemID, nFlags, hSysMenu);
	
	// TODO: Add your message handler code here
	if ((ID_FILE_MRU_FILE1<=nItemID && nItemID<=ID_FILE_MRU_FILE16) 
		||(nItemID==ID_SCC_OPEN)||(nItemID==ID_SCC_PAUSE))
	{
		CString sFileName;
		if(nItemID==ID_SCC_OPEN)
		{
			sFileName.Format("COM%d",m_nCurCOM+1);
			if(IsCOMOpen())	sFileName="关闭"+sFileName;
			else	sFileName="打开"+sFileName;
		}
		else if(nItemID==ID_SCC_PAUSE)
		{
			sFileName=(m_bPauseDis?"继续报文监视":"暂停报文监视");
		}
	//	else if(nItemID==ID_ADVANCE_SEND)
	//	{
		//	sFileName=(m_dlgSend.IsWindowVisible()?"隐藏高级发送窗":"显示高级发送窗");
	//	}
		else
		{
			sFileName=(*(theApp.GetFileList()))[nItemID-ID_FILE_MRU_FILE1];
			if(!sFileName.IsEmpty())	sFileName=_T("打开文件 ")+sFileName;
		}
		if(!sFileName.IsEmpty())
			SendMessage(WM_SETMESSAGESTRING, 0, (LPARAM)(LPCTSTR)sFileName);
		sFileName.Empty();
	}
	else 	CGuiFrameWnd::OnMenuSelect(nItemID, nFlags, hSysMenu);
}

BOOL CMainFrame::OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult)
{
	ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);

	// need to handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	TCHAR szFullText[256];
	CString strTipText;
	UINT nID = pNMHDR->idFrom;
	if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
		pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
	{
		// idFrom is actually the HWND of the tool
		nID = ::GetDlgCtrlID((HWND)nID);
	}
	if(nID==ID_SCC_OPEN)
	{
		strTipText.Format("COM%d",m_nCurCOM+1);
		if(IsCOMOpen())	strTipText="关闭"+strTipText;
		else	strTipText="打开"+strTipText;	
		SendMessage(WM_SETMESSAGESTRING, 0, (LPARAM)(LPCTSTR)strTipText);
	}
	else if(nID==ID_SCC_PAUSE)
	{
		strTipText=(m_bPauseDis?"继续报文监视":"暂停报文监视");
		SendMessage(WM_SETMESSAGESTRING, 0, (LPARAM)(LPCTSTR)strTipText);
	}
//	else if(nID==ID_ADVANCE_SEND)
//	{
	//	strTipText=(m_dlgSend.IsWindowVisible()?"隐藏高级发送窗":"显示高级发送窗");
//	}
	else if (nID != 0) // will be zero on a separator
	{
		// don't handle the message if no string resource found
		if (AfxLoadString(nID, szFullText) == 0)
			return FALSE;

		// this is the command id, not the button index
		AfxExtractSubString(strTipText, szFullText, 1, '\n');
	}
#ifndef _UNICODE
	if (pNMHDR->code == TTN_NEEDTEXTA)
		lstrcpyn(pTTTA->szText, strTipText, _countof(pTTTA->szText));
	else
		_mbstowcsz(pTTTW->szText, strTipText, _countof(pTTTW->szText));
#else
	if (pNMHDR->code == TTN_NEEDTEXTA)
		_wcstombsz(pTTTA->szText, strTipText, _countof(pTTTA->szText));
	else
		lstrcpyn(pTTTW->szText, strTipText, _countof(pTTTW->szText));
#endif
	*pResult = 0;

	// bring the tooltip window above other popup windows
	::SetWindowPos(pNMHDR->hwndFrom, HWND_TOP, 0, 0, 0, 0,
		SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOMOVE|SWP_NOOWNERZORDER);
	strTipText.Empty();
	return TRUE;    // message was handled
}


void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CGuiFrameWnd::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
//	m_dlgSend.SetTransper(23);
}

int CMainFrame::IsTriggerLine(CString str)
{
	for(int i=0;i<TRIGGER_MAX;i++)
	{
		if(m_dlgSend.Trigger[i].bValiu)
		{
			if(str==m_wndSF.m_xrec.GetLineStr(m_dlgSend.Trigger[i].unLine-1))
				return i;
			//	return m_dlgSend.Trigger[i].unTrigger;
		}
	}
	return -1;
}

void CMainFrame::Transmits(int nCOM,LPBYTE lpbt, int nLength)
{
	if(!Trasmt.bCOM)	return;
	CString str;
	if(Trasmt.btCOM1==nCOM+1)	nCOM=Trasmt.btCOM2-1;
	else if(Trasmt.btCOM2==nCOM+1)	nCOM=Trasmt.btCOM1-1;
	if(!IsCOMOpen(nCOM))	return;
	if(m_bAscRecv)	str=((CString)lpbt).Left (nLength);
	else	str=CSCCTools::HexToStr(lpbt,nLength);
	DisplayStr(str,nCOM,0);
	GetCOM(nCOM)->WriteData(lpbt,nLength);
	str.Empty();
}

BOOL CMainFrame::IsFilterFrame(LPBYTE lpb, int nLength)
{
	if(!m_dlgFilter.m_bFilter)	return 1;
	BOOL bFilter=1;
	for(int i=0;i<FILTER_MAX;i++)
	{
		if(m_dlgFilter.Filter[i].bFilter)
		{
			bFilter=0;
			if(m_dlgFilter.Filter[i].btNo>nLength)	return 0;
			if(lpb[m_dlgFilter.Filter[i].btNo-1]==m_dlgFilter.Filter[i].btValiu)
				return 1;
		}
	}
	return bFilter;
}

CString CMainFrame::GetRWPath(BOOL bOpen, LPCSTR lpstr,LPCSTR lpstrName)
{
	CString strs;
	CFileDialog* dlgFileOpen=new CFileDialog(bOpen,".pcf",lpstrName); 
	dlgFileOpen->m_ofn.lStructSize=(GetVersion() < 0x80000000)?88:76; 
	dlgFileOpen->m_ofn .lpstrFilter ="PCStudio Frame Files(*.pcf)\0*.pcf\0";
	dlgFileOpen->m_ofn.lpstrTitle =lpstr;
	strs.Empty ();	
	if(dlgFileOpen->DoModal()==IDOK)	strs=dlgFileOpen->GetPathName();
	delete dlgFileOpen;
	dlgFileOpen=NULL;
	return strs;
}

void CMainFrame::SaveIni()
{
//	CFile fIni("conf.ini")
}


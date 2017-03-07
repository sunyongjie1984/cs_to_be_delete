// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "FtpClient.h"
#include "FtpClientView.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame
BOOL IsFree;
CFtpInfoView* pFtpInfoView;
CLocFileView* pLocView;
CServFileView* pServView;
char szAppName[256];
char szFtpName[256];
char szFtpUser[20];
char szFtpPassword[20];
char szFtpDirectory[MAX_PATH];
char szLocDirectory[MAX_PATH];
int  nPort;
int  nCount;

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_COMMAND_EX(CG_ID_VIEW_MYDIALOGBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_MYDIALOGBAR, OnUpdateControlBarMenu)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_QUICKCONNECT, OnQuickconnect)
	ON_COMMAND(ID_FILE_DISCONNECT, OnFileDisconnect)
	ON_COMMAND(ID_FILE_STOP, OnFileStop)
	ON_UPDATE_COMMAND_UI(ID_FILE_DISCONNECT, OnUpdateFileDisconnect)
	ON_COMMAND(IDC_FILE_RECONNECT, OnFileReconnect)
	//}}AFX_MSG_MAP
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

CMainFrame::CMainFrame()
{
	m_bConnected=FALSE;
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CImageList imageList;
	CBitmap bitmap;
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// TODO: Add a menu item that will toggle the visibility of the
	// dialog bar named "My Dialog Bar":
	//   1. In ResourceView, open the menu resource that is used by
	//      the CMainFrame class
	//   2. Select the View submenu
	//   3. Double-click on the blank item at the bottom of the submenu
	//   4. Assign the new item an ID: CG_ID_VIEW_MYDIALOGBAR
	//   5. Assign the item a Caption: My Dialog Bar

	// TODO: Change the value of CG_ID_VIEW_MYDIALOGBAR to an appropriate value:
	//   1. Open the file resource.h
	// CG: The following block was inserted by the 'Dialog Bar' component
	{
		// Initialize dialog bar m_wndMyDialogBar
		if (!m_wndMyDialogBar.Create(this, CG_IDD_MYDIALOGBAR,
			CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE,
			CG_ID_VIEW_MYDIALOGBAR))
		{
			TRACE0("Failed to create dialog bar m_wndMyDialogBar\n");
			return -1;		// fail to create
		}

		m_wndMyDialogBar.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
		EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_wndMyDialogBar);
		m_wndMyDialogBar.SetDlgItemText(IDC_FTPPORT,"21");
		m_wndMyDialogBar.SetDlgItemText(IDC_FTPNAME,"10.13.21.66");
		m_wndMyDialogBar.SetDlgItemText(IDC_FTPUSER,"Anonymous");
		m_wndMyDialogBar.SetDlgItemText(IDC_FTPPASSWORD,"Anonymous");

	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

CString CMainFrame::GetFtpName()
{
	CString str;
	m_wndMyDialogBar.GetDlgItemText(IDC_FTPNAME,str);
	return str;

}
int CMainFrame::GetFtpPort()
{
	CString str;
	m_wndMyDialogBar.GetDlgItemText(IDC_FTPPORT,str);
	int i=atoi(str);
	return i;
}
CString CMainFrame::GetFtpUser()
{
	CString str;
	m_wndMyDialogBar.GetDlgItemText(IDC_FTPUSER,str);
	return str;
}
CString CMainFrame::GetFtpPassword()
{
	CString str;
	m_wndMyDialogBar.GetDlgItemText(IDC_FTPPASSWORD,str);
	return str;
}

void CMainFrame::OnQuickconnect() 
{
	GetFtpPara(&(pServView->m_ctServDir));
	if(!pServView->BeginFindServFile())
		AfxMessageBox("建立网络线程失败");
	m_bConnected=TRUE;
}

void CMainFrame::GetFtpPara(CComboBoxEx* pCombo)
{
	CString str;
	strcpy(szAppName,AfxGetAppName());
	strcpy(szFtpPassword,GetFtpPassword());
	strcpy(szFtpName,GetFtpName());
	nPort=GetFtpPort();
    pCombo->GetWindowText(str);
	strcpy(szFtpDirectory,str);
	strcpy(szFtpUser,GetFtpUser());
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


//////////////////////////////////////////////////////////////////////
// CFtpParaClass Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFtpParaClass::CFtpParaClass()
{
	HIMAGELIST hImageList;
	SHFILEINFO shFi;
	hImageList=(HIMAGELIST)SHGetFileInfo("C:\\",0,&shFi,sizeof(shFi),
		SHGFI_SYSICONINDEX|SHGFI_SMALLICON);
	if(!hImageList)
		return ;
	m_ctImageList.m_hImageList=hImageList;
	m_hDragCursor=AfxGetApp()->LoadIcon(IDI_CURSOR);
	m_bDragging=FALSE;
}

CFtpParaClass::~CFtpParaClass()
{
	if(m_ctImageList.m_hImageList)
		m_ctImageList.Detach();

}

void CFtpParaClass::SetFileColumns(CListCtrl* pListCtrl)
{
	static struct
	{
		LPSTR pszText;
		int uiFormat;
	}columns[]={
		_T("文件名"),LVCFMT_LEFT,
		_T("日期"),LVCFMT_CENTER,
		_T("字节数"),LVCFMT_CENTER
	};
	for(int i=0,j=120;i<sizeof(columns)/sizeof(columns[0]);i++,j-=10)
		pListCtrl->InsertColumn(i,columns[i].pszText,columns[i].uiFormat,j);
}

void CFtpParaClass::SetPopMenu(int nIndex)
{
	CMenu dMenu;
	if(!dMenu.LoadMenu(IDR_LOC_SERV_MENU))
		AfxThrowResourceException();
	CMenu* pPopMenu=dMenu.GetSubMenu(nIndex);
	ASSERT(pPopMenu!=NULL);
	POINT pt;
	::GetCursorPos(&pt);
	pPopMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,pt.x,pt.y,AfxGetMainWnd());
}

BOOL CFtpParaClass::SetImageList(CListCtrl* pListCtrl,CComboBoxEx* pCombo)
{
	pListCtrl->SetImageList(&m_ctImageList,LVSIL_SMALL);
	if(!pCombo)
		return TRUE;
	pCombo->SetImageList(&m_ctImageList);
	return TRUE;
}

void CFtpParaClass::GetFileIcon(CString& fileName,int* iIcon,int* iIconSel)
{
	CString str=fileName;
	if(str.Right(1)!="\\")
		str+="\\";
	SHFILEINFO shFi;
	if(!SHGetFileInfo(str,0,&shFi,sizeof(shFi),SHGFI_ICON|SHGFI_SMALLICON|SHGFI_DISPLAYNAME))
	{
		AfxMessageBox("111");
		return;
	}
	*iIcon=shFi.iIcon;
	DestroyIcon(shFi.hIcon);
	if(iIconSel)
	{
		if(!SHGetFileInfo(str,0,&shFi,sizeof(shFi),SHGFI_ICON|SHGFI_SMALLICON|SHGFI_OPENICON|SHGFI_DISPLAYNAME))
		{
			AfxMessageBox("222");
			return;
		}
		*iIconSel=shFi.iIcon;
		DestroyIcon(shFi.hIcon);
	}
//	fileName=shFi.szDisplayName;
	return ;
}

void CFtpParaClass::OnInsertFile(CListCtrl* pListCtrl,LPVOID pIn,LPARAM lParam)
{
	FILE_FTP_INFO*pInfo=(FILE_FTP_INFO*)pIn;
	LVITEM	lvIt;
	int iIcon,nItem;
	if(pInfo->nType==DIRECTORYICON)
		nItem=0;
	else
		nItem=pListCtrl->GetItemCount();
	CString fileName=pInfo->szFileName;;
	if((int)lParam==LOCFILE)
		GetFileIcon(fileName,&iIcon);
	else
		iIcon=pInfo->nType;
	lvIt.mask=LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM;
	lvIt.iImage=iIcon;
	lvIt.lParam=pInfo->nType;
	lvIt.pszText=pInfo->szFileName;
	lvIt.iSubItem=0;
	lvIt.iItem=nItem;
	int iPos=pListCtrl->InsertItem(&lvIt);
	lvIt.mask=LVIF_TEXT;
	lvIt.iItem=iPos;
	lvIt.pszText=pInfo->szFileDate;
	lvIt.iSubItem=1;
	pListCtrl->SetItem(&lvIt);
	lvIt.pszText=pInfo->szFileSize;
	lvIt.iSubItem=2;
	pListCtrl->SetItem(&lvIt);
	IsFree=TRUE;
}

void CFtpParaClass::OnFileName(CListCtrl* pListCtrl)
{
	POSITION iPos=pListCtrl->GetFirstSelectedItemPosition();
	CString str;
	int nItem=pListCtrl->GetNextSelectedItem(iPos);
	str=pListCtrl->GetItemText(nItem,0);
	CInputEdit* pEdit=new CInputEdit(nItem,0,str,pListCtrl);
	CRect rect;
	pListCtrl->GetItemRect(nItem,&rect,LVIR_LABEL);
	rect.left+=1;
	rect.right-=10;
	rect.top+=26;
	rect.bottom+=26;
	pEdit->Create(WS_CHILD|WS_VISIBLE|ES_LEFT|WS_BORDER|ES_MULTILINE|ES_AUTOVSCROLL,rect,pListCtrl->GetParent(),IDD_INPUT_EDIT);
}


/////////////////////////////////////////////////////////////////////////////
// CLocFileView


IMPLEMENT_DYNCREATE(CLocFileView, CFormView)

CLocFileView::CLocFileView()
	: CFormView(CLocFileView::IDD)
{
	m_bHaveDotFlag=FALSE;
	m_pSendFileThread=NULL;
	//{{AFX_DATA_INIT(CLocFileView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CLocFileView::~CLocFileView()
{
	if(m_pFindLocFileThread)
	{
		m_pFindLocFileThread->ResumeThread();
		::WaitForSingleObject(m_pFindLocFileThread->m_hThread,100);
		delete m_pFindLocFileThread;
		m_pFindLocFileThread=NULL;
	}
	if(m_pSendFileThread)
	{   m_pSendFileThread->ResumeThread();
		::WaitForSingleObject(m_pSendFileThread->m_hThread,100);
		delete m_pSendFileThread;
		m_pSendFileThread=NULL;
	}
}

void CLocFileView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLocFileView)
	DDX_Control(pDX, IDC_LOC_FILE, m_ctLocFile);
	DDX_Control(pDX, IDC_LOC_DIR, m_ctLocDir);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLocFileView, CFormView)
	//{{AFX_MSG_MAP(CLocFileView)
	ON_NOTIFY(NM_DBLCLK, IDC_LOC_FILE, OnDblclkLocFile)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_LOC_DIR, OnSelchangeLocDir)
	ON_CBN_DROPDOWN(IDC_LOC_DIR, OnDropdownLocDir)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_LOC_FILE, OnBegindragLocFile)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_NOTIFY(NM_RCLICK, IDC_LOC_FILE, OnRclickLocFile)
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_LOC_FILE, OnBeginlabeleditLocFile)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LOC_FILE, OnEndlabeleditLocFile)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SETFILE,CLocFileView::OnInsertLocFile)
	ON_MESSAGE(WM_SETREDRAWFLAG,CLocFileView::OnSetLocRedrawFlag)
	ON_MESSAGE(WM_SETDIRECTORYDISPLAY,CLocFileView::OnSetLocDirectoryDisplay)
	ON_MESSAGE(WM_REDISPLAYFILE,CLocFileView::OnReDisplayLocFile)
	ON_MESSAGE(WM_SETDIR,CLocFileView::OnSetLocDir)
	ON_COMMAND(ID_FILE_DELETE,CLocFileView::OnLocFileDelete)
	ON_COMMAND(ID_FILE_SEND,CLocFileView::OnLocFileSend)
	ON_COMMAND(ID_FILE_RENAME,CLocFileView::OnLocFileReName)
	ON_COMMAND(ID_FILE_EXECUTE,CLocFileView::OnLocFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocFileView diagnostics

#ifdef _DEBUG
void CLocFileView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLocFileView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLocFileView message handlers
/////////////////////////////////////////////////////////////////////////////
// CServFileView

IMPLEMENT_DYNCREATE(CServFileView, CFormView)

CServFileView::CServFileView()
	: CFormView(CServFileView::IDD)
{
	m_bHaveDotFlag=FALSE;
	m_pRenameFileThread=NULL;
	m_pReceiveFileThread=NULL;
	m_pFindServFileThread=NULL;
	m_pDeleteFileThread=NULL;
	//{{AFX_DATA_INIT(CServFileView)
	//}}AFX_DATA_INIT
}

CServFileView::~CServFileView()
{
	if(m_ctServImageList.m_hImageList)
		m_ctServImageList.Detach();
	if(m_pFindServFileThread)
	{
		::WaitForSingleObject(m_pFindServFileThread->m_hThread,100);
		delete m_pFindServFileThread;
	}
	if(m_pReceiveFileThread)
	{
		::WaitForSingleObject(m_pReceiveFileThread->m_hThread,100);
		delete m_pReceiveFileThread;
	}
	if(m_pDeleteFileThread)
	{
		::WaitForSingleObject(m_pDeleteFileThread->m_hThread,100);
		delete m_pDeleteFileThread;
	}
	if(m_pRenameFileThread)
	{
		::WaitForSingleObject(m_pRenameFileThread->m_hThread,100);
		delete m_pRenameFileThread;
	}
	DeleteObject(hBitmap);

}

void CServFileView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServFileView)
	DDX_Control(pDX, IDC_BACK, m_ctBack);
	DDX_Control(pDX, IDC_SERV_FILE, m_ctServFile);
	DDX_Control(pDX, IDC_SERV_DIR, m_ctServDir);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CServFileView, CFormView)
	//{{AFX_MSG_MAP(CServFileView)
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_SERV_FILE, OnDblclkServFile)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_SERV_FILE, OnBegindragServFile)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_NOTIFY(NM_RCLICK, IDC_SERV_FILE, OnRclickServFile)
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_SERV_FILE, OnBeginlabeleditServFile)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_SERV_FILE, OnEndlabeleditServFile)
	ON_BN_CLICKED(IDC_BACK, OnBack)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SETFILE,CServFileView::OnInsertServFile)
	ON_MESSAGE(WM_SETREDRAWFLAG,CServFileView::OnSetServRedrawFlag)
	ON_MESSAGE(WM_SETDIRECTORYDISPLAY,CServFileView::OnSetServDirectoryDisplay)
	ON_MESSAGE(WM_REDISPLAYFILE,CServFileView::OnReDisplayServFile)
	ON_MESSAGE(WM_SETDIR,CServFileView::OnSetServDir)
	ON_COMMAND(ID_FILE_DELETE,CServFileView::OnServFileDelete)
	ON_COMMAND(ID_FILE_FTP_DOWNLOAD,CServFileView::OnServFileDownload)
	ON_COMMAND(ID_FILE_RENAME,CServFileView::OnServFileReName)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServFileView diagnostics

#ifdef _DEBUG
void CServFileView::AssertValid() const
{
	CFormView::AssertValid();
}

void CServFileView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CServFileView message handlers
/////////////////////////////////////////////////////////////////////////////
// CFtpInfoView

IMPLEMENT_DYNCREATE(CFtpInfoView, CEditView)

CFtpInfoView::CFtpInfoView()
{
	
}

CFtpInfoView::~CFtpInfoView()
{
	m_NewFont.DeleteObject();
}


BEGIN_MESSAGE_MAP(CFtpInfoView, CEditView)
	//{{AFX_MSG_MAP(CFtpInfoView)
	ON_WM_CREATE()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_RECORDFTPINFO,CFtpInfoView::OnRecordFtpInfo)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFtpInfoView drawing

void CFtpInfoView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
}

/////////////////////////////////////////////////////////////////////////////
// CFtpInfoView diagnostics

#ifdef _DEBUG
void CFtpInfoView::AssertValid() const
{
	CEditView::AssertValid();
}

void CFtpInfoView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFtpInfoView message handlers

LRESULT CFtpInfoView::OnRecordFtpInfo(WPARAM wParam,LPARAM lParam)
{

	CEdit& edit=GetEditCtrl();
	
	CString str=(LPCTSTR)lParam;
	int nLine=edit.GetLineCount();
	int nStart=edit.LineIndex(nLine);
	edit.SetSel(nStart,str.GetLength()+nStart);
	edit.ReplaceSel("\r\n"+str);
	return 0L;

}
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// CG: The following block was added by the Splitter Bar component.
	{
		if(!m_wndSplitter1.CreateStatic(this,2,1))
			return FALSE;
        if(!m_wndSplitter1.CreateView(0,0,RUNTIME_CLASS(CFtpInfoView),CSize(375,100),pContext))
			return FALSE;
		m_wndSplitter1.SetRowInfo(1,180,0);
		if(m_wndSplitter2.CreateStatic(&m_wndSplitter1,1,2,WS_CHILD|WS_VISIBLE,m_wndSplitter1.IdFromRowCol(1,0))==NULL)
			return FALSE;
		if(!m_wndSplitter2.CreateView(0,0,RUNTIME_CLASS(CLocFileView),CSize(375,180),pContext)||
			!m_wndSplitter2.CreateView(0,1,RUNTIME_CLASS(CServFileView),CSize(375,180),pContext))
			return FALSE;
		return TRUE;
	}
}

void CLocFileView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	m_pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	pLocView=this;
	m_pFindLocFileThread=NULL;
    SetFileColumns(&m_ctLocFile);
	SetImageList(&m_ctLocFile,&m_ctLocDir);
	m_ctLocFile.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	GetLocDir();
	int i=m_ctLocDir.FindStringExact(-1,"C:\\");
	m_ctLocDir.SetCurSel(i);
	::SetCurrentDirectory("C:\\");
	GetLocCurrentDirectory();
	BeginFindLocFile();	
	
}

int CLocFileView::InsertLocDir(CString& str,int iIcon,int iIconSel)
{
	int nItem=m_ctLocDir.GetCount();
	COMBOBOXEXITEM Combo;
	Combo.mask=CBEIF_IMAGE|CBEIF_TEXT|CBEIF_SELECTEDIMAGE;
	Combo.iImage=iIcon;
	Combo.iSelectedImage=iIconSel;
	Combo.pszText=(LPTSTR)(LPCTSTR)str;
	Combo.iItem=nItem;
	m_ctLocDir.InsertItem(&Combo);
	return nItem;
}

void CServFileView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	m_ctServFile.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	pServView=this;
	hBitmap=::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BACKBITMAP));
	m_ctBack.SetBitmap(hBitmap);
	SetFileColumns(&m_ctServFile);	
	SetServImageList(IDB_FILE_BITMAP);
}

LRESULT CServFileView::OnInsertServFile(WPARAM wParam,LPARAM lParam)
{
	FILE_FTP_INFO* pInfo=(FILE_FTP_INFO*)wParam;
	CString str=pInfo->szFileName;
	if(str=="."||str=="..")
	{
		m_bHaveDotFlag=TRUE;
		return 0L;
	}
	OnInsertFile(&m_ctServFile,(LPVOID)pInfo,lParam);

	return 0L;

}

LRESULT CServFileView::OnSetServRedrawFlag(WPARAM wParam,LPARAM lParam)
{
	if(m_bHaveDotFlag)
	{
		CString str="..";
		int iIcon=DIRECTORYICON;
		m_ctServFile.InsertItem(0,str,iIcon);
		m_ctServFile.SetItemData(0,DIRECTORYICON);
		m_bHaveDotFlag=FALSE;
	}
	m_ctServFile.Invalidate();
	m_ctServFile.SetRedraw();	
	return 0L;	
}

LRESULT CServFileView::OnSetServDirectoryDisplay(WPARAM wParam,LPARAM lParam)
{
	FILE_FTP_INFO* pInfo=(FILE_FTP_INFO*)lParam;
	CString str;
	str=szFtpDirectory;
	m_ctServDir.SetWindowText(str);
	m_ctServDir.Invalidate();
	return 0L;
}

LRESULT CServFileView::OnReDisplayServFile(WPARAM wParam,LPARAM lParam)
{
	CString str=(LPCTSTR)wParam;
	m_ctServDir.SetWindowText(str);
	m_ctServDir.Invalidate();
	m_pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	m_pMainFrame->GetFtpPara(&m_ctServDir);
	if(!BeginFindServFile())
		AfxMessageBox("建立网络线程失败");
	return 0L;
}

LRESULT CServFileView::OnSetServDir(WPARAM wParam,LPARAM lParam)
{
    CString str=(LPCTSTR)lParam;
	m_ctServDir.SetWindowText(str);
	m_ctServFile.SetRedraw(FALSE);
	m_ctServFile.DeleteAllItems();
	m_ctServFile.SetRedraw();
	return 0L;

}

void CServFileView::OnServFileDelete()
{
	FILE_COUNT_INFO* pFileCount;
	CString str;
	int i=0;
	POSITION iPos;
	i=m_ctServFile.GetSelectedCount();
	pFileCount=new FILE_COUNT_INFO[i];
	strcpy(szAppName,AfxGetAppName());
	strcpy(szFtpName,m_pMainFrame->GetFtpName());
	strcpy(szFtpUser,m_pMainFrame->GetFtpUser());
	nPort=m_pMainFrame->GetFtpPort();
	strcpy(szFtpPassword,m_pMainFrame->GetFtpPassword());
	m_ctServDir.GetWindowText(str);
	strcpy(szFtpDirectory,str);
	nCount=i;
	iPos=m_ctServFile.GetFirstSelectedItemPosition();
	for(int j=0;j<i;j++)
	{
		int nItem=m_ctServFile.GetNextSelectedItem(iPos);
		m_ctServFile.GetItemText(nItem,0,pFileCount[j].fileName,256);
		pFileCount[j].ufileFlag=m_ctServFile.GetItemData(nItem);
		
	}
	if(!BeginDeleteFile((LPVOID)pFileCount))
		AfxMessageBox("建立文件删除线程出错");
}


void CServFileView::OnServFileDownload()
{
	FILE_COUNT_INFO* pFileCount;
	CString str;
	int i=0;
	POSITION iPos;
	i=m_ctServFile.GetSelectedCount();
	pFileCount=new FILE_COUNT_INFO[i];
	strcpy(szAppName,AfxGetAppName());
	strcpy(szFtpName,m_pMainFrame->GetFtpName());
	strcpy(szFtpUser,m_pMainFrame->GetFtpUser());
	nPort=m_pMainFrame->GetFtpPort();
	strcpy(szFtpPassword,m_pMainFrame->GetFtpPassword());
	pLocView->m_ctLocDir.GetWindowText(str);
	strcpy(szLocDirectory,str);
	m_ctServDir.GetWindowText(str);
	strcpy(szFtpDirectory,str);
	nCount=i;
	iPos=m_ctServFile.GetFirstSelectedItemPosition();
	for(int j=0;j<i;j++)
	{
		int nItem=m_ctServFile.GetNextSelectedItem(iPos);
		m_ctServFile.GetItemText(nItem,0,pFileCount[j].fileName,255);
		pFileCount[j].ufileFlag=m_ctServFile.GetItemData(nItem);
		
	}
	if(!BeginReceiveFile((LPVOID)pFileCount))
		AfxMessageBox("建立文件发送线程出错");
}

void CServFileView::OnServFileReName()
{
	OnFileName(&m_ctServFile);
}

BOOL CServFileView::BeginDeleteFile(LPVOID pInfo)
{
	if(m_pDeleteFileThread)
	{
		::WaitForSingleObject(m_pDeleteFileThread->m_hThread,100);
		delete m_pDeleteFileThread;
		m_pDeleteFileThread=NULL;
	}
	if(m_pDeleteFileThread=AfxBeginThread(CMyAppThread::DeleteFileThread,pInfo,THREAD_PRIORITY_ABOVE_NORMAL,
		0,CREATE_SUSPENDED,NULL))
	{
		m_pDeleteFileThread->m_bAutoDelete=FALSE;
		m_pDeleteFileThread->ResumeThread();
		return TRUE;
	}
	return FALSE;
}

BOOL CServFileView::BeginRenameFile(LPVOID pInfo)
{
	if(m_pRenameFileThread)
	{
		::WaitForSingleObject(m_pRenameFileThread->m_hThread,100);
		delete m_pRenameFileThread;
		m_pRenameFileThread=NULL;
	}
	if(m_pRenameFileThread=AfxBeginThread(CMyAppThread::RenameFileThread,pInfo,THREAD_PRIORITY_ABOVE_NORMAL,
		0,CREATE_SUSPENDED,NULL))
	{
		m_pRenameFileThread->m_bAutoDelete=FALSE;
		m_pRenameFileThread->ResumeThread();
		return TRUE;
	}
	return FALSE;
}
BOOL CServFileView::BeginFindServFile()
{
	if(m_pFindServFileThread)
	{
		::WaitForSingleObject(m_pFindServFileThread->m_hThread,100);
		delete m_pFindServFileThread;
		m_pFindServFileThread=NULL;
	}
	if(m_pFindServFileThread=AfxBeginThread(CMyAppThread::FindServFileThread,NULL,THREAD_PRIORITY_ABOVE_NORMAL,
		0,CREATE_SUSPENDED,NULL))
	{
		m_pFindServFileThread->m_bAutoDelete=FALSE;
		m_ctServFile.SetRedraw(FALSE);
		m_ctServFile.DeleteAllItems();		
		m_pFindServFileThread->ResumeThread();
		return TRUE;
	}
	return FALSE;
}


void CLocFileView::GetLocDir()
{
	int iIcon,iIconSel;
	char lpBuffer[MAX_PATH];
	char* ptr;
	CString str;
	m_iDirCount=0;
	::GetLogicalDriveStrings(MAX_PATH,lpBuffer);
	ptr=lpBuffer;
	while(*ptr)
	{
		m_iDirCount++;
		str=ptr;
		GetFileIcon(str,&iIcon,&iIconSel);
		InsertLocDir(str,iIcon,iIconSel);
		ptr+=strlen(ptr)+1;
	}
}

BOOL CLocFileView::BeginFindLocFile()
{
	if(m_pFindLocFileThread)
	{
		::WaitForSingleObject(m_pFindLocFileThread->m_hThread,INFINITE);
		delete m_pFindLocFileThread;
		m_pFindLocFileThread=NULL;
	}
	if(m_pFindLocFileThread=AfxBeginThread(CMyAppThread::FindLocFileThread,NULL,THREAD_PRIORITY_ABOVE_NORMAL,
		0,CREATE_SUSPENDED,NULL))
	{
		m_pFindLocFileThread->m_bAutoDelete=FALSE;
		m_ctLocFile.SetRedraw(FALSE);
		m_ctLocFile.DeleteAllItems();
		m_pFindLocFileThread->ResumeThread();
		return TRUE;
	}
	m_ctLocFile.SetRedraw(FALSE);
	return FALSE;
}

BOOL CLocFileView::BeginSendFile(LPVOID pInfo)
{
	if(m_pSendFileThread)
	{
		::WaitForSingleObject(m_pSendFileThread->m_hThread,10);
		delete m_pSendFileThread;
		m_pSendFileThread=NULL;
	}
	if(m_pSendFileThread=AfxBeginThread(CMyAppThread::SendFileThread,(LPVOID)pInfo,THREAD_PRIORITY_ABOVE_NORMAL,
		0,CREATE_SUSPENDED,NULL))
	{
		m_pSendFileThread->m_bAutoDelete=FALSE;
		m_pSendFileThread->ResumeThread();
		return TRUE;
	}
	else
		return FALSE;
}

void CLocFileView::GetLocCurrentDirectory()
{
	CString str;
	m_ctLocDir.GetWindowText(str);
	strcpy(szLocDirectory,str);
}

LRESULT CLocFileView::OnSetLocDirectoryDisplay(WPARAM wParam,LPARAM lParam)
{
	CString str;
	str=szLocDirectory;
	m_ctLocDir.SetWindowText(str);
	m_ctLocDir.Invalidate();
	return 0L;
}

LRESULT CLocFileView::OnSetLocRedrawFlag(WPARAM wParam,LPARAM lParam)
{
	if(m_bHaveDotFlag)
	{
		CString str="..";
		int iIcon=DIRECTORYICON;
		m_ctLocFile.InsertItem(0,str,iIcon);
		m_ctLocFile.SetItemData(0,DIRECTORYICON);
		m_bHaveDotFlag=FALSE;
	}
	m_ctLocFile.Invalidate();
	m_ctLocFile.SetRedraw();
	return 0L;	
}

LRESULT CLocFileView::OnReDisplayLocFile(WPARAM wParam,LPARAM lParam)
{
	CString str=(LPCTSTR)wParam;
	m_ctLocDir.SetWindowText(str);
	m_ctLocDir.Invalidate();
	GetLocCurrentDirectory();
	if(!BeginFindLocFile())
		AfxMessageBox("建立网络线程失败");
	return 0L;
}

LRESULT CLocFileView::OnInsertLocFile(WPARAM wParam,LPARAM lParam)
{
	FILE_FTP_INFO* pInfo=(FILE_FTP_INFO*)wParam;
	CString str=pInfo->szFileName;
	if(str=="."||str=="..")
	{
		m_bHaveDotFlag=TRUE;
		return 0L;
	}
	OnInsertFile(&m_ctLocFile,pInfo,lParam);
	return 0L;
}
/////////////////////////////////////////////////////////////////////////////
// CMyAppThread

IMPLEMENT_DYNCREATE(CMyAppThread, CWinThread)

CMyAppThread::CMyAppThread()
{
}

CMyAppThread::~CMyAppThread()
{
}

BOOL CMyAppThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CMyAppThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CMyAppThread, CWinThread)
	//{{AFX_MSG_MAP(CMyAppThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyAppThread message handlers

UINT CMyAppThread::FindLocFileThread(LPVOID lParam)
{
	CFtpParaClass:: FILE_FTP_INFO* pInfo=new (CFtpParaClass::FILE_FTP_INFO);
	CFileFind fileFind;
	UINT i=0;
	CTime time;
	BOOL bContinue;
	::SetCurrentDirectory(szLocDirectory);
	::PostMessage(pLocView->m_hWnd,WM_SETDIRECTORYDISPLAY,0,0);
	bContinue=fileFind.FindFile("*.*");
	if(!bContinue)
		return 0L;
	CString str;
	while(bContinue)
	{
		bContinue=fileFind.FindNextFile();
		if(fileFind.IsHidden())continue;
		str=fileFind.GetFileName();
		strcpy(pInfo->szFileName,str);
		fileFind.GetLastWriteTime(time);
		str=time.Format("%x");
		strcpy(pInfo->szFileDate,str);
		if(fileFind.IsDirectory())
		{
			strcpy(pInfo->szFileSize,"");
			pInfo->nType=DIRECTORYICON;
			::SendMessage(pLocView->m_hWnd,WM_SETFILE,(WPARAM)pInfo,
				(LPARAM)LOCFILE);
		}
		else
		{
			int i=fileFind.GetLength();
			if(i>1024)
			{
				str.Format("%d",i/1024);
				str+="KB";
			}
			else
				str.Format("%d",i);
			strcpy(pInfo->szFileSize,str);
			pInfo->nType=FILEICON;
			::SendMessage(pLocView->m_hWnd,WM_SETFILE,(WPARAM)pInfo,
				(LPARAM)LOCFILE);
		}
	}
	::SendMessage(pLocView->m_hWnd,WM_SETREDRAWFLAG,0,0);
	delete pInfo;
	fileFind.Close();
	return 0L;
}

UINT CMyAppThread::FindServFileThread(LPVOID lParam)
{
	CFtpParaClass::FILE_FTP_INFO* pInfo=new(CFtpParaClass::FILE_FTP_INFO);
	FILETIME fileTime;
	CString str,szFile,szFtpInfo;
	WIN32_FIND_DATA findData;
	HINTERNET hFind;
	HINTERNET hInetSession=InternetOpen(szAppName,INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,0);
	szFtpInfo="正在连接";
	szFtpInfo+=szFtpName;
	szFtpInfo+="服务器";
	pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
	HINTERNET hFtpConn=InternetConnect(hInetSession,szFtpName,nPort,
		szFtpUser,szFtpPassword,INTERNET_SERVICE_FTP,INTERNET_FLAG_PASSIVE,0);
	if(!hFtpConn)
	{
		szFtpInfo=szFtpName;
		szFtpInfo+="服务器未接上";
		pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
		InternetCloseHandle(hInetSession);
		::Sleep(10);
		return 0L;
	}
	szFtpInfo=szFtpName;
	szFtpInfo+="服务器已连上，用户";
	szFtpInfo+=szFtpUser;
	szFtpInfo+="登录成功";
	pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
	DWORD dwLength=MAX_PATH;
	if(szFtpDirectory!=0)
		FtpSetCurrentDirectory(hFtpConn,szFtpDirectory);
	FtpGetCurrentDirectory(hFtpConn,szFtpDirectory,&dwLength);
	::PostMessage(pServView->m_hWnd,WM_SETDIRECTORYDISPLAY,0,0);
	szFtpInfo="正在查找文件";
	pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
	if(!(hFind=FtpFindFirstFile(hFtpConn,_T("*"),&findData,0,0)))
	{
		if (GetLastError()  == ERROR_NO_MORE_FILES) 
		{
			AfxMessageBox("目录为空，没有多余的内容");
			goto end;
		}
		else
		{
			szFtpInfo="文件查找出错，退回，请查明原因";
			pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
			goto end;
		}
	}
	do{
		szFile=findData.cFileName;
		strcpy(pInfo->szFileName,szFile);
		fileTime=findData.ftLastWriteTime;
		CTime time=CTime(fileTime);
		CString str=time.Format("%x");
		strcpy(pInfo->szFileDate,str);
		if(findData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY)
		{
			strcpy(pInfo->szFileSize,"");
			pInfo->nType=DIRECTORYICON;
		}
		else
		{
			DWORD i=findData.nFileSizeLow;
			if(i>1024)
			{
				str.Format("%ld",i/1024);
				str+="KB";
			}
			else
				str.Format("%ld",i);
			strcpy(pInfo->szFileSize,str);
			pInfo->nType=FILEICON;
		}
		::SendMessage(pServView->m_hWnd,WM_SETFILE,(WPARAM)pInfo,(LPARAM)SERVFILE);
		
	}while(InternetFindNextFile(hFind,&findData));
	
	::SendMessage(pServView->m_hWnd,WM_SETREDRAWFLAG,0,0);
	InternetCloseHandle(hFind);
end:
	szFtpInfo="查找文件结束";
	pFtpInfoView->SendMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
	::Sleep(10);
	delete pInfo;
	InternetCloseHandle(hFtpConn);
	InternetCloseHandle(hInetSession);
	return 0L;	
}

UINT CMyAppThread::SendFileThread(LPVOID lParam)
{
	IsFree=TRUE;
	CFtpParaClass:: FILE_FTP_INFO* pInf=new (CFtpParaClass::FILE_FTP_INFO);
	CFtpParaClass::FILE_COUNT_INFO* pInfo=(CFtpParaClass::FILE_COUNT_INFO*)lParam;
    BOOL Result;
	CInternetSession* lpInetSession;
	CFtpConnection* lpFtpConnection;
	CString str,strFtp,OldLoc,OldFtp,szFtpInfo;
	lpInetSession=new CInternetSession(szAppName,1,PRE_CONFIG_INTERNET_ACCESS);
	if(!lpInetSession)
		return 0;
	try
	{
		lpFtpConnection=lpInetSession->GetFtpConnection(szFtpName,szFtpUser,szFtpPassword,nPort);
	}
	catch(CInternetException* lpEx)
	{
		lpEx->ReportError();
		lpEx->Delete();
		delete lpInetSession;
		return 0;
	}
	lpFtpConnection->SetCurrentDirectory(szFtpDirectory);
	::SetCurrentDirectory(szLocDirectory);
	OldLoc=szLocDirectory;
	OldFtp=szFtpDirectory;
	for(int i=0;i<nCount;i++)
	{
		str=OldLoc;
		strFtp=OldFtp;
		CString DirName=pInfo[i].fileName;
		if(pInfo[i].ufileFlag==FILEICON)
		{
			szFtpInfo="发送";
			szFtpInfo+=DirName;
			pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
			if(lpFtpConnection->PutFile(DirName,DirName))
			{
				if(IsFree)
				{
					IsFree=FALSE;
					strcpy(pInf->szFileName,DirName);
					strcpy(pInf->szFileDate,"");
					strcpy(pInf->szFileSize,"");
					pInf->nType=FILEICON;
					::PostMessage(pServView->m_hWnd,WM_SETFILE,(WPARAM)pInf,SERVFILE);
				}
				continue;
			}
			else
			{
				szFtpInfo="发送";
				szFtpInfo+=DirName;
				szFtpInfo+="出错";
				pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
				break;
			}
		}
		else
		{
			if(str.Right(1)=="\\")
				str+=DirName;
			else
				str+="\\"+DirName;
			if(strFtp.Right(1)=='/')
				strFtp+=DirName;
			else
				strFtp+="/"+DirName;
			if(Result=PreSendFile(lpFtpConnection,str,strFtp,(LPVOID)pInfo))
				continue;
			else
			{
				AfxMessageBox("发送有错,请查明原因");
				break;
			}
		}
	}
	
	szFtpInfo="文件发送结束,退回";
	szFtpInfo+=OldFtp;
    pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
	::Sleep(10);
	if(IsFree)
		::SendMessage(pServView->m_hWnd,WM_REDISPLAYFILE,(WPARAM)(LPCTSTR)OldFtp,0);
	delete[] pInfo;
	delete pInf;
	delete lpFtpConnection;
	delete lpInetSession;
	return 0L;

}


BOOL CMyAppThread::PreSendFile(CFtpConnection* lpFtp,CString& str,CString& strFtp,LPVOID pInf)
{
	CFtpParaClass:: FILE_FTP_INFO* pInfo=(CFtpParaClass::FILE_FTP_INFO*)pInf;
	BOOL result;
	UINT uSize;
	CFileFind fileFind;
	HANDLE hHeap;
	LPSTR lpBuffer;
	CString lpBufferFtp,szFtpInfo;
	CFtpConnection* lpFtpConnection=lpFtp;
	uSize=(GetCurrentDirectory(0,NULL)*sizeof(TCHAR));
	hHeap=GetProcessHeap();
	lpBuffer=(LPSTR)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,uSize);
	lpFtpConnection->GetCurrentDirectory(lpBufferFtp);
	GetCurrentDirectory(uSize,(LPTSTR)(LPCTSTR)lpBuffer);
	if(str!=lpBuffer)
	{
		SetCurrentDirectory(str);
		szFtpInfo="创建";
		szFtpInfo+=strFtp;
		szFtpInfo+="目录";
		pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
		lpFtpConnection->CreateDirectory(strFtp);
		lpFtpConnection->SetCurrentDirectory(strFtp);
		szFtpInfo="进入";
		szFtpInfo+=strFtp;
		szFtpInfo+="目录成功";
		pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
		::SendMessage(pServView->m_hWnd,WM_SETDIR,0,(LPARAM)(LPCTSTR)strFtp);;
	}
	UINT bContinue=fileFind.FindFile("*");
	CString tFile;
	if(bContinue)
	{
		do
		{
			bContinue=fileFind.FindNextFile();
			tFile=fileFind.GetFileName();
			if(tFile=="."||tFile==".."||fileFind.IsHidden())continue;
			if(fileFind.IsDirectory())
			{
				if(str.Right(1)=='\\')
				{
					if(strFtp.Right(1)=='/')
						PreSendFile(lpFtpConnection,str+tFile,strFtp+tFile,(LPVOID)pInfo);
					else
						PreSendFile(lpFtpConnection,str+tFile,strFtp+"/"+tFile,(LPVOID)pInfo);
				}
				else
				{
					if(strFtp.Right(1)=='/')
						result=PreSendFile(lpFtpConnection,str+"\\"+tFile,strFtp+tFile,(LPVOID)pInfo);
					else
						result=PreSendFile(lpFtpConnection,str+"\\"+tFile,strFtp+"/"+tFile,(LPVOID)pInfo);
				}
			}
			else
			{
				szFtpInfo="发送";
				szFtpInfo+=tFile;
				pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
				result=(lpFtpConnection->PutFile(tFile,tFile))?TRUE:FALSE;
				if(IsFree)
				{
					IsFree=FALSE;
					strcpy(pInfo->szFileName,tFile);
					strcpy(pInfo->szFileDate,"");
					strcpy(pInfo->szFileSize,"");
					pInfo->nType=FILEICON;
					::PostMessage(pServView->m_hWnd,WM_SETFILE,(WPARAM)pInf,SERVFILE);
				}
				continue;
			}
		}while(bContinue);
		fileFind.Close();
		SetCurrentDirectory(lpBuffer);
		szFtpInfo="退回";
		szFtpInfo+=lpBufferFtp;
		pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
		lpFtpConnection->SetCurrentDirectory(lpBufferFtp);
		::SendMessage(pServView->m_hWnd,WM_SETDIR,0,(LPARAM)(LPCTSTR)lpBufferFtp);
		HeapFree(hHeap,HEAP_NO_SERIALIZE,lpBuffer);
		return result;
	}
	fileFind.Close();
	SetCurrentDirectory(lpBuffer);
	lpFtpConnection->SetCurrentDirectory(lpBufferFtp);
	::SendMessage(pServView->m_hWnd,WM_SETDIR,0,(LPARAM)(LPCTSTR)lpBufferFtp);
	HeapFree(hHeap,HEAP_NO_SERIALIZE,lpBuffer);
	return FALSE;
}

UINT CMyAppThread::ReceiveFileThread(LPVOID lParam)
{
	IsFree=TRUE;
	CString szFtpInfo;
	CFtpParaClass:: FILE_FTP_INFO* pInf=new (CFtpParaClass::FILE_FTP_INFO);
	CFtpParaClass::FILE_COUNT_INFO* pInfo=(CFtpParaClass::FILE_COUNT_INFO*)lParam;
	BOOL Result;
	CString str,strFtp,OldLoc,OldFtp;
	HINTERNET hInetSession=InternetOpen(szAppName,INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,0);
	HINTERNET hFtpConn=InternetConnect(hInetSession,szFtpName,nPort,
		szFtpUser,szFtpPassword,INTERNET_SERVICE_FTP,INTERNET_FLAG_PASSIVE,0);
	if(!hFtpConn)
	{
		AfxMessageBox("建立联接出错，返回");
		InternetCloseHandle(hInetSession);
		return 0L;
	}
	szFtpInfo="正在进入";
	szFtpInfo+=szFtpDirectory;
	pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
	FtpSetCurrentDirectory(hFtpConn,szFtpDirectory);
    ::SetCurrentDirectory(szLocDirectory);
	OldLoc=szLocDirectory;
	OldFtp=szFtpDirectory;
	for(int i=0;i<nCount;i++)
	{
		str=OldLoc;
		strFtp=OldFtp;
		CString DirName=pInfo[i].fileName;
		if(pInfo[i].ufileFlag==FILEICON)
		{
			szFtpInfo="正在接收";
			szFtpInfo+=DirName;
			pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
			if(FtpGetFile(hFtpConn,DirName,DirName,FALSE,FILE_ATTRIBUTE_NORMAL,FTP_TRANSFER_TYPE_BINARY |
				INTERNET_FLAG_NO_CACHE_WRITE,0))
			{
				if(IsFree)
				{
					IsFree=FALSE;
					strcpy(pInf->szFileName,DirName);
					strcpy(pInf->szFileDate,"");
					strcpy(pInf->szFileSize,"");
					pInf->nType=FILEICON;
					::PostMessage(pLocView->m_hWnd,WM_SETFILE,(WPARAM)pInf,(LPARAM)SERVFILE);
				}
				szFtpInfo="接收";
				szFtpInfo+=DirName;
				szFtpInfo+="完毕，下一个";
				pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
				continue;
			}
			else
			{
				szFtpInfo="接收";
				szFtpInfo+=DirName;
				szFtpInfo+="出错，退出查找原因";
				pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
				break;
			}
		}
		else
		{
			if(str.Right(1)=="\\")
				str+=DirName;
			else
				str+="\\"+DirName;
			if(strFtp.Right(1)=='/')
				strFtp+=DirName;
			else
				strFtp+="/"+DirName;
			if(Result=PreReceiveFile(hInetSession,str,strFtp,(LPVOID)pInf))
				continue;
			else
			{
				AfxMessageBox("发送有错,请查明原因");
				break;
			}
		}
	}
	szFtpInfo="文件接收结束，退回";
	szFtpInfo+=OldLoc;
	pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
	::Sleep(20);
	if(IsFree)
	{
		::SendMessage(pLocView->m_hWnd,WM_REDISPLAYFILE,(WPARAM)(LPCTSTR)OldLoc,0);
	}

	delete[] pInfo;
	delete pInf;
	InternetCloseHandle(hFtpConn);
	InternetCloseHandle(hInetSession);
	return 0L;

}

UINT CMyAppThread::DeleteFileThread(LPVOID lParam)
{
	IsFree=TRUE;
	CString szFtpInfo;
	CFtpParaClass::FILE_COUNT_INFO* pInfo=(CFtpParaClass::FILE_COUNT_INFO*)lParam;
	BOOL Result;
	CString strFtp,OldFtp;
	HINTERNET hInetSession=InternetOpen(szAppName,INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,0);
	szFtpInfo="正在连接";
	szFtpInfo+=szFtpName;
	pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
	HINTERNET hFtpConn=InternetConnect(hInetSession,szFtpName,nPort,
		szFtpUser,szFtpPassword,INTERNET_SERVICE_FTP,INTERNET_FLAG_PASSIVE,0);
	if(!hFtpConn)
	{
		szFtpInfo="未连接上";
		szFtpInfo+=szFtpName;
		szFtpInfo+="服务器";
		pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
		::Sleep(10);
		InternetCloseHandle(hInetSession);
		return 0L;
	}
	szFtpInfo="成功连上";
	szFtpInfo+=szFtpName;
	szFtpInfo+="服务器，现在进入";
	szFtpInfo+=szFtpDirectory;
	pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
	FtpSetCurrentDirectory(hFtpConn,szFtpDirectory);
    OldFtp=szFtpDirectory;
	for(int i=0;i<nCount;i++)
	{
		strFtp=OldFtp;
		CString DirName=pInfo[i].fileName;
		if(pInfo[i].ufileFlag==FILEICON)
		{
			szFtpInfo="正在删除";
			szFtpInfo+=DirName;
			pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
			if(FtpDeleteFile(hFtpConn,DirName))
			{
				continue;
			}
			else
			{
				szFtpInfo="删除";
				szFtpInfo+=DirName;
				szFtpInfo+="出错，返回";
				pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
				break;
			}
		}
		else
		{
			if(strFtp.Right(1)=='/')
				strFtp+=DirName;
			else
				strFtp+="/"+DirName;
			if(Result=PreDeleteFile(hInetSession,strFtp,OldFtp))
				continue;
			else
			{
				AfxMessageBox("删除出错,请查明原因");
				break;
			}
		}
	}
	szFtpInfo="文件删除结束";
	pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
	::Sleep(10);
		if(IsFree)
			::SendMessage(pServView->m_hWnd,WM_REDISPLAYFILE,(WPARAM)(LPCTSTR)OldFtp,0);
	delete[] pInfo;
	InternetCloseHandle(hFtpConn);
	InternetCloseHandle(hInetSession);
	return 0L;

}

UINT CMyAppThread::RenameFileThread(LPVOID lParam)
{
	CString szFtpInfo;
	CFtpParaClass::FILE_CHANGE_INFO* pInfo=(CFtpParaClass::FILE_CHANGE_INFO*)lParam;
	HINTERNET hInetSession=InternetOpen(szAppName,INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,0);
	szFtpInfo="正在连接";
	szFtpInfo+=szFtpName;
	szFtpInfo+="服务器";
    pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
	HINTERNET hFtpConn=InternetConnect(hInetSession,szFtpName,nPort,
		szFtpUser,szFtpPassword,INTERNET_SERVICE_FTP,INTERNET_FLAG_PASSIVE,0);
	if(!hFtpConn)
	{
		szFtpInfo="未连上";
		szFtpInfo+=szFtpName;
		szFtpInfo+="服务器，请查明原因,目前只能返回";
		pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
		InternetCloseHandle(hInetSession);
		::Sleep(10);
		return 0L;
	}
	szFtpInfo=szFtpName;
	szFtpInfo+="服务器连接成功,现进行改名操作";
	pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
	FtpSetCurrentDirectory(hFtpConn,szFtpDirectory);
	szFtpInfo="正在把";
	szFtpInfo+=pInfo->OldName;
	szFtpInfo+="改为";
	szFtpInfo+=pInfo->NewName;
	pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
    FtpRenameFile(hFtpConn,pInfo->OldName,pInfo->NewName);
	szFtpInfo="改名成功";
	pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
	::Sleep(10);
	delete pInfo;
	InternetCloseHandle(hFtpConn);
	InternetCloseHandle(hInetSession);
	return 0L;

}

BOOL CMyAppThread::PreDeleteFile(HINTERNET hInetSession, CString& strFtp,CString& OldDir)
{
	CString szFtpInfo;
	BOOL result;
	DWORD dwSize=MAX_PATH;
	CString tFile;
	WIN32_FIND_DATA findData;
	HINTERNET hFind;
	HINTERNET hFtpConn=InternetConnect(hInetSession,szFtpName,nPort,szFtpUser,szFtpPassword,INTERNET_SERVICE_FTP,INTERNET_FLAG_PASSIVE,0);
	if(!hFtpConn)
	{
		AfxMessageBox("建立联接出错，返回");
		InternetCloseHandle(hInetSession);
		return FALSE;
	}
	szFtpInfo="正在进入";
	szFtpInfo+=strFtp;
	szFtpInfo+="目录";
    pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
	FtpSetCurrentDirectory(hFtpConn,strFtp);
	szFtpInfo="进入";
	szFtpInfo+=strFtp;
	szFtpInfo+="目录成功";
	pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
	if(!(hFind=FtpFindFirstFile(hFtpConn,_T("*"),&findData,0,0)))
	{
		if (GetLastError()!= ERROR_NO_MORE_FILES)
			result=FALSE;
		else
			result=TRUE;
		goto end;
	}
	do
	{
		tFile=findData.cFileName;
		if(tFile=="."||tFile=="..")continue;
		if(findData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY)
		{
			if(!(result=PreDeleteFile(hInetSession,strFtp+"/"+tFile,strFtp)))
			{
				AfxMessageBox("删除出错，返回");
				break;
			}
		}
		else
		{
			szFtpInfo="正在删除";
			szFtpInfo+=tFile;
			pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
			result=(FtpDeleteFile(hFtpConn,tFile))?TRUE:FALSE;
			if(!result)
			{
				szFtpInfo="删除"+tFile+"出错";
				pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
				break;
			}
		}
	}while(InternetFindNextFile(hFind,&findData));
	FtpSetCurrentDirectory(hFtpConn,OldDir);
	szFtpInfo="正在删除"+strFtp+"目录";
	pFtpInfoView->PostMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
	FtpRemoveDirectory(hFtpConn,strFtp);
	InternetCloseHandle(hFind);
	InternetCloseHandle(hFtpConn);
	return result;
	
end:
    InternetCloseHandle(hFtpConn);
	return result;

}
BOOL CMyAppThread::PreReceiveFile(HINTERNET hInetSession, CString& str,CString& strFtp,LPVOID pInf)
{
	CFtpParaClass:: FILE_FTP_INFO* pInfo=(CFtpParaClass:: FILE_FTP_INFO*)pInf;
	BOOL result;
	UINT uSize;
	DWORD dwSize=MAX_PATH;
	HANDLE hHeap;
	LPSTR lpBuffer;
	CString lpBufferFtp,tFile;
	WIN32_FIND_DATA findData;
	HINTERNET hFind;
	HINTERNET hFtpConn=InternetConnect(hInetSession,szFtpName,nPort,szFtpUser,szFtpPassword,INTERNET_SERVICE_FTP,INTERNET_FLAG_PASSIVE,0);
	if(!hFtpConn)
	{
		AfxMessageBox("建立联接出错，返回");
		InternetCloseHandle(hInetSession);
		return FALSE;
	}
	uSize=(GetCurrentDirectory(0,NULL)*sizeof(TCHAR));
	hHeap=GetProcessHeap();
	lpBuffer=(LPSTR)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,uSize);
	GetCurrentDirectory(uSize,lpBuffer);
	
	FtpSetCurrentDirectory(hFtpConn,strFtp);
	::CreateDirectory(str,NULL);
	::SetCurrentDirectory(str);		
	::SendMessage(pLocView->m_hWnd,WM_SETDIR,0,(LPARAM)(LPCTSTR)str);
	if(!(hFind=FtpFindFirstFile(hFtpConn,_T("*"),&findData,0,0)))
	{
		if (GetLastError()!= ERROR_NO_MORE_FILES)
			result=FALSE;
		else
			result=TRUE;
		goto end;
	}
	do
	{
		tFile=findData.cFileName;
		if(tFile=="."||tFile==".."||findData.dwFileAttributes==FILE_ATTRIBUTE_HIDDEN)continue;
		if(findData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY)
		{
			if(!(result=PreReceiveFile(hInetSession,str+"\\"+tFile,strFtp+"/"+tFile,pInf)))
			{
				AfxMessageBox("文件发送出错，返回");
				break;
			}
		}
		else
		{
			result=(FtpGetFile(hFtpConn,tFile,tFile,FALSE,FILE_ATTRIBUTE_NORMAL,FTP_TRANSFER_TYPE_BINARY|
				INTERNET_FLAG_NO_CACHE_WRITE,0))?TRUE:FALSE;
			if(!result)
			{
				AfxMessageBox("文件发送出错，返回");
				break;
			}
			if(IsFree)
			{
				IsFree=FALSE;
				strcpy(pInfo->szFileName,tFile);
				strcpy(pInfo->szFileDate,"");
				strcpy(pInfo->szFileSize,"");
				pInfo->nType=FILEICON;
				::PostMessage(pLocView->m_hWnd,WM_SETFILE,(WPARAM)pInfo,SERVFILE);
			}
		}
	}while(InternetFindNextFile(hFind,&findData));
	SetCurrentDirectory(lpBuffer);
	::SendMessage(pLocView->m_hWnd,WM_SETDIR,0,(LPARAM)lpBuffer);
	InternetCloseHandle(hFind);
	HeapFree(hHeap,HEAP_NO_SERIALIZE,lpBuffer);
	InternetCloseHandle(hFtpConn);
	return result;
	
end:
	::SetCurrentDirectory(lpBuffer);
	::SendMessage(pLocView->m_hWnd,WM_SETDIR,0,(LPARAM)lpBuffer);
	HeapFree(hHeap,HEAP_NO_SERIALIZE,lpBuffer);
	InternetCloseHandle(hFtpConn);
	return result;
}



void CLocFileView::OnDblclkLocFile(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NMLVDISPINFO* pLocInfo=(NMLVDISPINFO*)pNMHDR;
	CString str,buf;
	int iIcon,iIconSel;
	str.Format("%d",pLocInfo->item);
	if(str=="-1")
		return;
	int nItem=atoi(str);
	DWORD dwFlag=m_ctLocFile.GetItemData(nItem);
	if(dwFlag==FILEICON)
	{
		OnLocFileOpen();
		return;
	}
	::GetCurrentDirectory(MAX_PATH,szLocDirectory);
	str=szLocDirectory;
	m_ctLocFile.GetItemText(nItem,0,szLocDirectory,MAX_PATH);
	buf=szLocDirectory;
	if(str.Right(1)!="\\")
		str+="\\";
	str+=szLocDirectory;
	GetFileIcon(buf,&iIcon,&iIconSel);
	int i=InsertLocDir(str,iIcon,iIconSel);
	m_ctLocDir.SetCurSel(i);
	::SetCurrentDirectory(str);
	::GetCurrentDirectory(MAX_PATH,szLocDirectory);
	BeginFindLocFile();	
	*pResult = 0;
}

void CLocFileView::OnSize(UINT nType, int cx, int cy) 
{
//	CFormView::OnSize(nType, cx, cy);
	if(m_ctLocDir.m_hWnd)
		m_ctLocDir.SetWindowPos(this,0,0,cx,0,SWP_NOZORDER|SWP_NOMOVE);
	if(m_ctLocFile.m_hWnd)
	{
		m_ctLocFile.ShowWindow(SW_HIDE);
		m_ctLocFile.SetWindowPos(this,0,0,cx,cy-25,SWP_NOZORDER|SWP_NOMOVE);
		m_ctLocFile.ShowWindow(SW_SHOW);
	}
	
}

void CServFileView::OnSize(UINT nType, int cx, int cy) 
{
//	CFormView::OnSize(nType, cx, cy);
    if(m_ctServDir.m_hWnd&&m_ctBack.m_hWnd)
	{
		m_ctServDir.SetWindowPos(this,0,0,cx-30,0,SWP_NOZORDER|SWP_NOMOVE);
		m_ctBack.SetWindowPos(this,cx-28,0,0,0,SWP_NOZORDER|SWP_NOSIZE);
	}
	if(m_ctServFile.m_hWnd)
	{
		m_ctServFile.ShowWindow(SW_HIDE);
		m_ctServFile.SetWindowPos(this,0,0,cx,cy-25,SWP_NOZORDER|SWP_NOMOVE);
		m_ctServFile.ShowWindow(SW_SHOW);
	}	
}

BOOL CServFileView::SetServImageList(UINT nBitmapID)
{
	if(m_ctServImageList.Create(nBitmapID,16,1,RGB(0,255,0)))
		m_ctServFile.SetImageList(&m_ctServImageList,LVSIL_SMALL);
	else
		return FALSE;
	
	return TRUE;
}

void CLocFileView::OnSelchangeLocDir() 
{
	CString str;
    char lpBuffer[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH,lpBuffer);
	int i=m_ctLocDir.GetCurSel();
	m_ctLocDir.GetLBText(i,(LPTSTR)(LPCTSTR)str);
	i=0;
	while(1)
	{
		if(!SetCurrentDirectory(str))
		{
			i++;
			if(i<2)
			{
				AfxMessageBox("请插入磁盘再试");
				continue;
			}
			str=lpBuffer;
			if((i=m_ctLocDir.FindStringExact(-1,str))!=-1)
				m_ctLocDir.SetCurSel(i);
			else
				m_ctLocDir.SetWindowText(str);
		}
		else
		{
			::SetCurrentDirectory(str);
			GetLocCurrentDirectory();
			BeginFindLocFile();
		}
		break;
		
	}	
}

void CLocFileView::OnDropdownLocDir() 
{
	int i=m_ctLocDir.GetCount();
	for(;i>m_iDirCount-1;--i)
		m_ctLocDir.DeleteItem(i);	
}

void CServFileView::OnDblclkServFile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMLVDISPINFO* pLocInfo=(NMLVDISPINFO*)pNMHDR;
	CString str,buf;
	str.Format("%d",pLocInfo->item);
	if(str=="-1")
		return;
	int nItem=atoi(str);
	DWORD dwFlag=m_ctServFile.GetItemData(nItem);
	if(dwFlag==FILEICON)
		return;
	m_ctServDir.GetWindowText(str);
	if(str!="/")
		str+="/";
	str+=m_ctServFile.GetItemText(nItem,0);
	m_ctServDir.SetWindowText(str);
	m_ctServDir.Invalidate();
	::PostMessage(AfxGetApp()->m_pMainWnd->m_hWnd,WM_COMMAND,IDC_QUICKCONNECT,0);
	*pResult = 0;
}

void CLocFileView::OnBegindragLocFile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_bDragging)return;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;    	
	*pResult = 0;
	int nItem=pNMListView->iItem;
	POINT pt=pNMListView->ptAction;
	m_pDragImageList=m_ctLocFile.CreateDragImage(nItem,&pt);
	m_bDragging=TRUE;
	m_pDragImageList->BeginDrag(0,CPoint(0,0));
	m_pDragImageList->DragEnter(NULL,pt);
	SetCapture();
	SetCursor(m_hDragCursor);
	
	
	*pResult = 0;
}

void CLocFileView::OnMouseMove(UINT nFlags, CPoint point) 
{
    if(m_bDragging)
	{
		CRect rect;
		pServView->m_ctServFile.GetWindowRect(&rect);
		ClientToScreen(&point);
		if(rect.PtInRect(point))
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		else
			SetCursor(m_hDragCursor);
		m_pDragImageList->DragMove(point);
	}	
	CFormView::OnMouseMove(nFlags, point);
}

void CLocFileView::OnLButtonUp(UINT nFlags, CPoint point) 
{
    if(m_bDragging)
	{
		extern CServFileView* pServView;
		m_bDragging=FALSE;
		CImageList::DragLeave(NULL);
		CImageList::EndDrag();
		ReleaseCapture();
		delete m_pDragImageList;
		m_pDragImageList=NULL;
		CRect rect;
		pServView->m_ctServFile.GetWindowRect(&rect);
		ClientToScreen(&point);
		if(rect.PtInRect(point))
			OnLocFileSend();
	}	
	CFormView::OnLButtonUp(nFlags, point);
}

void CLocFileView::OnLocFileSend()
{
	CString str;
	pServView->m_ctServDir.GetWindowText(str);
	int i=0;
	POSITION iPos;
	i=m_ctLocFile.GetSelectedCount();
	FILE_COUNT_INFO* pFileCount=new FILE_COUNT_INFO[i];
	strcpy(szAppName,AfxGetAppName());
	strcpy(szFtpName,m_pMainFrame->GetFtpName());
	strcpy(szFtpUser,m_pMainFrame->GetFtpUser());
	nPort=m_pMainFrame->GetFtpPort();
	strcpy(szFtpPassword,m_pMainFrame->GetFtpPassword());
	strcpy(szFtpDirectory,str);
	m_ctLocDir.GetWindowText(str);
	strcpy(szLocDirectory,str);
	nCount=i;
	iPos=m_ctLocFile.GetFirstSelectedItemPosition();
	for(int j=0;j<i;j++)
	{
		int nItem=m_ctLocFile.GetNextSelectedItem(iPos);
		m_ctLocFile.GetItemText(nItem,0,pFileCount[j].fileName,256);
		pFileCount[j].ufileFlag=m_ctLocFile.GetItemData(nItem);
		
	}
	if(!BeginSendFile((LPVOID)pFileCount))
		AfxMessageBox("建立文件发送线程出错");
}

void CLocFileView::OnLocFileOpen()
{
	GetLocCurrentDirectory();
	CString str=szLocDirectory;
	POSITION iPos=m_ctLocFile.GetFirstSelectedItemPosition();
	int nItem=m_ctLocFile.GetNextSelectedItem(iPos);
	int i=m_ctLocFile.GetItemData(nItem);
	if(str.Right(1)=="\\")
		str+=m_ctLocFile.GetItemText(nItem,0);
	else
		str+="\\"+m_ctLocFile.GetItemText(nItem,0);
	if(i==FILEICON)
		::ShellExecute(m_hWnd,NULL,str,"explore",szLocDirectory,SW_SHOWDEFAULT);
	else
	{
		strcpy(szLocDirectory,str);		
		BeginFindLocFile();
	}

}
void CLocFileView::OnLocFileDelete()
{
	POSITION iPos=m_ctLocFile.GetFirstSelectedItemPosition();
	if(!iPos)return;
	SHFILEOPSTRUCT lpsh;
	CString str;
	int i=m_ctLocFile.GetSelectedCount();
	ZeroMemory(&lpsh,sizeof(lpsh));
	lpsh.hwnd= HWND_DESKTOP;
	lpsh.fFlags=FOF_NOCONFIRMATION;
	lpsh.wFunc=FO_DELETE;
	for(int j=0;j<i;j++)
	{
		int nItem=m_ctLocFile.GetNextSelectedItem(iPos);
		str=m_ctLocFile.GetItemText(nItem,0);
		char buf[256];
		strcpy(buf,str);
		buf[str.GetLength()+1]='\0';
		lpsh.pFrom=buf;
		if( 0 != SHFileOperation(&lpsh))
			AfxMessageBox("删除文件出错,请检查");
	}
	::GetCurrentDirectory(MAX_PATH,szLocDirectory);
	BeginFindLocFile();
}

void CLocFileView::OnLocFileReName()
{
	OnFileName(&m_ctLocFile);
}


void CLocFileView::OnRclickLocFile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;
	int nItem=pNMListView->iItem;
	if(nItem==-1)return;
	SetPopMenu(0);
/*	CMenu dMenu;
	if(!dMenu.LoadMenu(IDR_LOC_SERV_MENU))
		AfxThrowResourceException();
	CMenu* pPopMenu=dMenu.GetSubMenu(0);
	ASSERT(pPopMenu!=NULL);
	POINT pt;
	::GetCursorPos(&pt);
	pPopMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,pt.x,pt.y,AfxGetMainWnd());	*/
	*pResult = 0;
}

void CLocFileView::OnBeginlabeleditLocFile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CLocFileView::OnEndlabeleditLocFile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM * pItem=&pDispInfo->item;
	int nItem=pItem->iItem;
	CString str;
	str=m_ctLocFile.GetItemText(nItem,0);
	if(pItem->pszText)
	{
		m_ctLocFile.SetItemText(pItem->iItem,pItem->iSubItem,pItem->pszText);
		::rename(str,pItem->pszText);
	}
	*pResult = 0;
}

LRESULT CLocFileView::OnSetLocDir(WPARAM wParam,LPARAM lParam)
{
	CString str=(LPCTSTR)lParam;
	m_ctLocDir.SetWindowText(str);
	m_ctLocFile.SetRedraw(FALSE);
	m_ctLocFile.DeleteAllItems();
	m_ctLocFile.SetRedraw();
	return 0L;

}
/////////////////////////////////////////////////////////////////////////////
// CInputEdit

CInputEdit::CInputEdit(int iItem,int iSubItem,CString& szInitText,CListCtrl* pListCtrl)
{
	m_pListCtrl=pListCtrl;
	m_iItem=iItem;
	m_iSubItem=iSubItem;
	m_szInitText=szInitText;
	m_bEsc=FALSE;
}

CInputEdit::~CInputEdit()
{
}


BEGIN_MESSAGE_MAP(CInputEdit, CEdit)
	//{{AFX_MSG_MAP(CInputEdit)
	ON_WM_CHAR()
	ON_WM_KILLFOCUS()
	ON_WM_CREATE()
	ON_WM_NCDESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputEdit message handlers

void CInputEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(nChar==VK_ESCAPE||nChar==VK_RETURN)
	{
		if(nChar==VK_ESCAPE)
			m_bEsc=TRUE;
		GetParent()->SetFocus();
		return;
	}
	CEdit::OnChar(nChar, nRepCnt, nFlags);
	CString str;
	GetWindowText(str);
	CWindowDC dc(this);
	CFont* pFont=GetParent()->GetFont();
	CFont* pFontDC=dc.SelectObject(pFont);
	CSize size=dc.GetTextExtent(str);
	dc.SelectObject(pFontDC);
	size.cx+=5;
	CRect rect,parentrect;
	GetClientRect(&rect);
	GetParent()->GetClientRect(&parentrect);
	ClientToScreen(&rect);
	GetParent()->ScreenToClient(&rect);
	if(size.cx>rect.Width())
	{
		if(size.cx+rect.left<parentrect.right)
			rect.right=rect.left+size.cx;
		else
			rect.right=parentrect.right;
		MoveWindow(&rect);
	}
}

void CInputEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);
	CString str;
	GetWindowText(str);
	LV_DISPINFO dispinfo;
	dispinfo.hdr.hwndFrom=m_pListCtrl->m_hWnd;
	dispinfo.hdr.idFrom=GetDlgCtrlID();
	dispinfo.hdr.code=LVN_ENDLABELEDIT;
	dispinfo.item.mask=LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM;
	dispinfo.item.iItem=m_iItem;
	dispinfo.item.iSubItem=m_iSubItem;
	dispinfo.item.pszText=m_bEsc?NULL:(LPTSTR)(LPCTSTR)str;
	dispinfo.item.cchTextMax=str.GetLength();
	GetParent()->SendMessage(WM_NOTIFY,GetParent()->GetDlgCtrlID(),(LPARAM)&dispinfo);	
	DestroyWindow();	
}

BOOL CInputEdit::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->wParam==VK_RETURN||pMsg->wParam==VK_DELETE||pMsg->wParam==VK_ESCAPE||
		GetKeyState(VK_CONTROL))
	{
		::TranslateMessage(pMsg);
		::DispatchMessage(pMsg);
		return TRUE;
	}
	
	return CEdit::PreTranslateMessage(pMsg);
}

int CInputEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	CFont* font=GetParent()->GetFont();
	SetFont(font);
	SetWindowText(m_szInitText);
	SetFocus();
	SetSel(0,-1);
	return 0;
}

void CInputEdit::OnNcDestroy() 
{
	CEdit::OnNcDestroy();
	delete this;	
}

BOOL CLocFileView::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE&&m_bDragging)
	{
		m_bDragging=FALSE;
		CImageList::DragLeave(NULL);
		CImageList::EndDrag();
		ReleaseCapture();
		delete m_pDragImageList;
		return TRUE;
	}	
	return CFormView::PreTranslateMessage(pMsg);
}

void CServFileView::OnBegindragServFile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_bDragging)return;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;    	
	*pResult = 0;
	int nItem=pNMListView->iItem;
	POINT pt=pNMListView->ptAction;
	m_pDragImageList=m_ctServFile.CreateDragImage(nItem,&pt);
	m_bDragging=TRUE;
	m_pDragImageList->BeginDrag(0,CPoint(0,0));
	m_pDragImageList->DragEnter(NULL,pt);
	SetCapture();
}

void CServFileView::OnMouseMove(UINT nFlags, CPoint point) 
{
    if(m_bDragging)
	{
		CRect rect;
		pLocView->m_ctLocFile.GetWindowRect(&rect);
		ClientToScreen(&point);
		if(rect.PtInRect(point))
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		else
			SetCursor(m_hDragCursor);
		m_pDragImageList->DragMove(point);
	}	
	CFormView::OnMouseMove(nFlags, point);
}

BOOL CServFileView::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE&&m_bDragging)
	{
		m_bDragging=FALSE;
		CImageList::DragLeave(NULL);
		CImageList::EndDrag();
		ReleaseCapture();
		delete m_pDragImageList;
		return TRUE;
	}	
	return CFormView::PreTranslateMessage(pMsg);
}

void CServFileView::OnLButtonUp(UINT nFlags, CPoint point) 
{
    if(m_bDragging)
	{
		m_bDragging=FALSE;
		CImageList::DragLeave(NULL);
		CImageList::EndDrag();
		ReleaseCapture();
		delete m_pDragImageList;
		m_pDragImageList=NULL;
		CRect rect;
		pLocView->m_ctLocFile.GetWindowRect(&rect);
		ClientToScreen(&point);
		if(rect.PtInRect(point))
			OnServFileDownload();
	}
	CFormView::OnLButtonUp(nFlags, point);
}

BOOL CServFileView::BeginReceiveFile(LPVOID pIn)
{
	FILE_COUNT_INFO* pInfo=(FILE_COUNT_INFO*)pIn;
	if(m_pReceiveFileThread)
	{
		::WaitForSingleObject(m_pReceiveFileThread->m_hThread,100);
		delete m_pReceiveFileThread;
		m_pReceiveFileThread=NULL;
	}
	if(m_pReceiveFileThread=AfxBeginThread(CMyAppThread::ReceiveFileThread,(LPVOID)pInfo,THREAD_PRIORITY_ABOVE_NORMAL,
		0,CREATE_SUSPENDED,NULL))
	{
		m_pReceiveFileThread->m_bAutoDelete=FALSE;
		m_pReceiveFileThread->ResumeThread();
		return TRUE;
	}
	else
		return FALSE;
}

void CServFileView::OnRclickServFile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;
	int nItem=pNMListView->iItem;
	if(nItem==-1)return;
	SetPopMenu(1);
	
}

void CServFileView::OnBeginlabeleditServFile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	*pResult = 0;
}

void CServFileView::OnEndlabeleditServFile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM * pItem=&pDispInfo->item;
	int nItem=pItem->iItem;
	CString str;
	FILE_CHANGE_INFO* pInfo=new FILE_CHANGE_INFO;
	str=m_ctServFile.GetItemText(nItem,0);
	if(pItem->pszText)
	{
		strcpy(pInfo->OldName,str);
		strcpy(pInfo->NewName,pItem->pszText);
		if(!BeginRenameFile((LPVOID)pInfo))
			AfxMessageBox("建立文件重命名线程出错，返回");
		m_ctServFile.SetItemText(pItem->iItem,pItem->iSubItem,pItem->pszText);

	}
	*pResult = 0;
}

void CServFileView::OnBack() 
{
	CString str;
	m_ctServDir.GetWindowText(str);   	
	if(str.Right(1)=="/")return;
	str+="/..";
	m_ctServDir.SetWindowText(str);
	m_ctServDir.Invalidate();
	::PostMessage(AfxGetApp()->m_pMainWnd->m_hWnd,WM_COMMAND,IDC_QUICKCONNECT,0);
}


int CFtpInfoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
    pFtpInfoView = this;
	m_NewFont.CreatePointFont(70,"Arial",NULL);
	GetEditCtrl().SetFont(&m_NewFont,true);
	return 0;
}




void CFtpInfoView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
 	
//	CEditView::OnChar(nChar, nRepCnt, nFlags);
}

void CMainFrame::OnFileDisconnect() 
{
	CString szFtpInfo;
	szFtpInfo="已中断与";
	szFtpInfo+=szFtpName;
	szFtpInfo+="的连接";
    pFtpInfoView->SendMessage(WM_RECORDFTPINFO,0,(LPARAM)(LPCTSTR)szFtpInfo);
	m_bConnected=FALSE;
}

void CMainFrame::OnFileStop() 
{
	// TODO: Add your command handler code here
	
}

void CFtpInfoView::OnFileReconnect() 
{
	AfxGetApp()->m_pMainWnd->SendMessage(WM_COMMAND,IDC_QUICKCONNECT);	
}

void CMainFrame::OnUpdateFileDisconnect(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(m_bConnected);
   
}
void CMainFrame::OnFileReconnect() 
{
	OnQuickconnect();	
}


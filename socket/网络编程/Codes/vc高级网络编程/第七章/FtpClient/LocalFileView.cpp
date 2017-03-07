// LocalFileView.cpp : implementation file
//

#include "stdafx.h"
#include "FtpClient.h"
#include "LocalFileView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLocalFileView

IMPLEMENT_DYNCREATE(CLocalFileView, CFormView)

CLocalFileView::CLocalFileView()
	: CFormView(CLocalFileView::IDD)
{
	//{{AFX_DATA_INIT(CLocalFileView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CLocalFileView::~CLocalFileView()
{
}

void CLocalFileView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLocalFileView)
	DDX_Control(pDX, IDC_FILEPATH, m_cbFilePath);
	DDX_Control(pDX, IDC_FILELIST, m_ctFileLocal);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLocalFileView, CFormView)
	//{{AFX_MSG_MAP(CLocalFileView)
	ON_NOTIFY(LVN_BEGINRDRAG, IDC_FILELIST, OnBeginrdragFilelist)
	ON_WM_MOUSEMOVE()
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_FILELIST, OnBeginlabeleditFilelist)
	ON_NOTIFY(NM_DBLCLK, IDC_FILELIST, OnDblclkFilelist)
	ON_CBN_DROPDOWN(IDC_FILEPATH, OnDropdownFilepath)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_FILEPATH, OnSelchangeFilepath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocalFileView diagnostics

#ifdef _DEBUG
void CLocalFileView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLocalFileView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLocalFileView message handlers

BOOL CLocalFileView::FindLocalFile()
{
    if(m_pFindLocalFileThread)
	{
		::WaitForSingleObject(m_pFindLocalFileThread->m_hThread,INFINITE);
		delete m_pFindLocFileThread;
		m_pFindLocFileThread = NULL;
	}
	if(m_pFindLocalFileThread = AfxBeginThread(CMyAppThread::FindLocalFileThread,
		          NULL,THREAD_PRIORITY_ABOVE_NORMAL,0,CREATE_SUSPENDED,NULL))
	{
		m_pFindLocalFileThread->m_bAutoDelete = FALSE;
		m_ctFileLocal.SetRedraw(FALSE);
		m_ctFileLocal.DeleteAllItems();
		m_pFindLocalFileThread->ResumeThread();
		return TRUE;
	}
	m_ctFileLocal.SetRedraw(FALSE);
	return FALSE;
}

BOOL CLocalFileView::SendFile(LPVOID pInfo)
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

void CLocalFileView::GetLocCurrentDirectory()
{
    CString str;
	m_ctLocDir.GetWindowText(str);
	strcpy(szLocDirectory,str);
}

void CLocalFileView::GetLocDir()
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

int CLocalFileView::InsertLocDir(CString &str, int iIcon, int iIconSel)
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


void CLocalFileView::OnBeginrdragFilelist(NMHDR* pNMHDR, LRESULT* pResult) 
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

void CLocalFileView::OnMouseMove(UINT nFlags, CPoint point) 
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

void CLocalFileView::OnBeginlabeleditFilelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
    	
	*pResult = 0;
}

void CLocalFileView::OnDblclkFilelist(NMHDR* pNMHDR, LRESULT* pResult) 
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

void CLocalFileView::OnDropdownFilepath() 
{
    int i=m_ctLocDir.GetCount();
	for(;i>m_iDirCount-1;--i)
		m_ctLocDir.DeleteItem(i);	
}

void CLocalFileView::OnInitialUpdate() 
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

void CLocalFileView::OnSize(UINT nType, int cx, int cy) 
{
	//CFormView::OnSize(nType, cx, cy);
	
   if(m_ctLocDir.m_hWnd)
		m_ctLocDir.SetWindowPos(this,0,0,cx,0,SWP_NOZORDER|SWP_NOMOVE);
	if(m_ctLocFile.m_hWnd)
	{
		m_ctLocFile.ShowWindow(SW_HIDE);
		m_ctLocFile.SetWindowPos(this,0,0,cx,cy-25,SWP_NOZORDER|SWP_NOMOVE);
		m_ctLocFile.ShowWindow(SW_SHOW);
	}	
}

BOOL CLocalFileView::PreTranslateMessage(MSG* pMsg) 
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

void CLocalFileView::OnSelchangeFilepath() 
{
	// TODO: Add your control notification handler code here
	
}

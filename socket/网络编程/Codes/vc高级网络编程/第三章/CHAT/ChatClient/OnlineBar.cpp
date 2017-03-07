// OnlineBar.cpp : implementation file
//

#include "stdafx.h"
#include "chatclient.h"
#include "OnlineBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COnlineBar dialog

COnlineBar::COnlineBar()
{
}

COnlineBar::~COnlineBar()
{
	delete m_ListCtrl;
}

BEGIN_MESSAGE_MAP(COnlineBar, CDialogBar)
	//{{AFX_MSG_MAP(COnlineBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COnlineBar message handlers
int COnlineBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	GetClientRect(&rect);
	rect.left += 8;
	rect.top += 15;
	rect.right -= 8;
	rect.bottom -= 8;
	
	m_ListCtrl = new COnlineList;
	if (!m_ListCtrl->Create(WS_CHILD | WS_VISIBLE | LVS_REPORT,
		rect, this, IDC_LISTBOX))
	{
		TRACE0("Failed to create view for CMyBarLeft\n");
		return -1;
	}

	m_ListCtrl->ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	AddExStyle(LVS_EX_FULLROWSELECT | LVS_OWNERDRAWFIXED);
	
	int i;
	LV_COLUMN lvc;

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	CString	strTemp[2] = {"Ãû³Æ", "IP"};
	int size[2] = {140,40};
	for(i = 0; i < 2; i++)
	{
		lvc.iSubItem = i;
		lvc.pszText = (char*)(LPCTSTR)strTemp[i];
		lvc.cx = size[i];
		lvc.fmt = LVCFMT_LEFT;
		m_ListCtrl->InsertColumn(i, &lvc);
	}

	return 0;
}

void COnlineBar::AddExStyle(DWORD dwNewStyle)
{
	DWORD dwStyle = ::SendMessage (m_ListCtrl->m_hWnd, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0);
	dwStyle |= dwNewStyle;

	::SendMessage (m_ListCtrl->m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
}

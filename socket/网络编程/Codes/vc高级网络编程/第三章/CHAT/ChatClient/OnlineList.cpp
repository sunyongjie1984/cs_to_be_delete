// OnlineList.cpp : implementation file
//

#include "stdafx.h"
#include "chatclient.h"
#include "OnlineList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COnlineList

COnlineList::COnlineList()
{

}

COnlineList::~COnlineList()
{
}

BEGIN_MESSAGE_MAP(COnlineList, CListCtrl)
	//{{AFX_MSG_MAP(COnlineList)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COnlineList message handlers
int COnlineList::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_imgList.Create(IDB_IMAGE, 16, 1, RGB(0, 255, 0));
	HIMAGELIST him = m_imgList.m_hImageList;
	::SendMessage(this->m_hWnd,LVM_SETIMAGELIST,(WPARAM)LVSIL_SMALL,(LPARAM)him);
//	::SendMessage(this->m_hWnd,LVM_SETIMAGELIST,(WPARAM)LVSIL_NORMAL,(LPARAM)him);
	ImageList_SetBkColor(him,CLR_NONE);

	return 0;
}

void COnlineList::AddItem(short i, char* name, char* text)
{
	LVITEM			lvi;

	lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
	lvi.iItem = GetItemCount();
    lvi.iImage = i;
	lvi.iSubItem = 0;
	lvi.pszText = name;
	lvi.cchTextMax = 64;
	lvi.lParam = 0;
	InsertItem(&lvi);

	lvi.mask = LVIF_TEXT;
	lvi.pszText = text;
	lvi.cchTextMax = 32;
	lvi.iSubItem = 1;
	SetItem(&lvi);
}

void COnlineList::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	CString str;
	int iSel = pNMListView->iItem;
	if (iSel >= 0 ){
		str = GetItemText(iSel,0);
		CWnd* pParentWnd = GetParent();
		while (pParentWnd != NULL){ 
			if (pParentWnd->IsFrameWnd()){
				break;
			}
			pParentWnd = pParentWnd->GetParent();
		}
		if (pParentWnd != NULL)
	       pParentWnd->SendMessage(WM_DBCLICKITEM, 0, (LPARAM)&str);
	}
	*pResult = 0;
}

void COnlineList::Remove(char *name)
{
	CString str;
	for(int i = 0; i < GetItemCount(); i++){
		str = GetItemText(i,0);
		if(strcmp(str, name) == 0){
			DeleteItem(i);
			break;
		}
	}
}

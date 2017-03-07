

#include "stdafx.h"
#include "CListCtrlEx.h"

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx

BOOL CListCtrlEx::AddColumn(LPCTSTR strItem,int nItem,int nSubItem,int nMask,int nFmt)
{
	LV_COLUMN lvc;
	lvc.mask = nMask;
	lvc.fmt = nFmt;
	lvc.pszText = (LPTSTR) strItem;
	lvc.cx = GetStringWidth(lvc.pszText) + 15;
	if(nMask & LVCF_SUBITEM){
		if(nSubItem != -1)
			lvc.iSubItem = nSubItem;
		else
			lvc.iSubItem = nItem;
	}
	return InsertColumn(nItem,&lvc);
}

int CListCtrlEx::AddItem(int nItem,int nSubItem,LPCTSTR strItem,int nImageIndex)
{
	LV_ITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = nItem;
	lvItem.iSubItem = nSubItem;
	lvItem.pszText = (LPTSTR) strItem;
	if(nImageIndex != -1){
		lvItem.mask |= LVIF_IMAGE;
		lvItem.iImage |= LVIF_IMAGE;
	}
    if(nSubItem == 0) {
		return InsertItem(&lvItem);
    }
    if (SetItem(&lvItem)) {
        return(nItem);
    }
    return(-1);
}

CListCtrlEx::CListCtrlEx() : CListCtrl()
{
}

CListCtrlEx::~CListCtrlEx()
{
}

CImageList* CListCtrlEx::SetImageList(CImageList* pImageList, int nImageListType)
{
	return CListCtrl::SetImageList(pImageList,nImageListType); 
}

/////////////////////////////////////////////////////////////////////////////


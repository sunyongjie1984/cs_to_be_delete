#ifndef CLIST_CTRL_EX_H
#define CLIST_CTRL_EX_H

#ifndef __AFXWIN_H__
	#include <afxwin.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx

class CListCtrlEx : public CListCtrl
{
	// Attributes
protected:

	// Operation
public:
	CListCtrlEx();
	~CListCtrlEx();
	CImageList* SetImageList(CImageList* pImageList, int nImageListType = TVSIL_NORMAL);
	BOOL AddColumn(
		LPCTSTR strItem,int nItem,int nSubItem = -1,
		int nMask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM,
		int nFmt = LVCFMT_LEFT);
	int AddItem(int nItem,int nSubItem,LPCTSTR strItem,int nImageIndex = -1);
};


/////////////////////////////////////////////////////////////////////////////

#endif // CLIST_CTRL_EX_H

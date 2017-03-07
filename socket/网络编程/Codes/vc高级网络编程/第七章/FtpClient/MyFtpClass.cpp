// MyFtpClass.cpp: implementation of the CMyFtpClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FtpClient.h"
#include "MyFtpClass.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyFtpClass::CMyFtpClass()
{
    HIMAGELIST hImageList;
	SHFILEINFO shFi;
	hImageList = (HIMAGELIST)SHGetFileInfo("C:\\",0,&shFi,sizeof(shFi),
		SHGFI_SYSICONINDEX|SHGFI_SMALLICON);
	if(!hImageList)
		return ;
	m_ctImageList.m_hImageList = hImageList;
	m_hDragCursor = AfxGetApp()->LoadIcon(IDI_CURSOR);
	m_bDragging=FALSE;
}

CMyFtpClass::~CMyFtpClass()
{
    if(m_ctImageList.m_hImageList)
		m_ctImageList.Detach();
}

void CMyFtpClass::GetFileIcon(CString &fileName, int *iIcon, int *iIconSel)
{
   CString str = fileName;
	if (str.Right(1) != "\\")
		str += "\\";
	SHFILEINFO shFi;
	if (!SHGetFileInfo(str,0,&shFi,sizeof(shFi),SHGFI_ICON|SHGFI_SMALLICON|SHGFI_DISPLAYNAME))
	{
		AfxMessageBox("111");
		return;
	}
	*iIcon = shFi.iIcon;
	DestroyIcon(shFi.hIcon);
	if(iIconSel)
	{
		if(!SHGetFileInfo(str,0,&shFi,sizeof(shFi),SHGFI_ICON|SHGFI_SMALLICON|SHGFI_OPENICON|SHGFI_DISPLAYNAME))
		{
			AfxMessageBox("222");
			return;
		}
		*iIconSel = shFi.iIcon;
		DestroyIcon(shFi.hIcon);
	}

	return ;
}

void CMyFtpClass::OnFileName(CListCtrl *pListCtrl)
{
    POSITION iPos = pListCtrl->GetFirstSelectedItemPosition();
	CString str;
	int nItem = pListCtrl->GetNextSelectedItem(iPos);
	str = pListCtrl->GetItemText(nItem,0);
	CInputEdit* pEdit = new CInputEdit(nItem,0,str,pListCtrl);
	CRect rect;
	pListCtrl->GetItemRect(nItem,&rect,LVIR_LABEL);
	rect.left += 1;
	rect.right -= 10;
	rect.top += 26;
	rect.bottom += 26;
	pEdit->Create(WS_CHILD|WS_VISIBLE|ES_LEFT|WS_BORDER|ES_MULTILINE|ES_AUTOVSCROLL,rect,pListCtrl->GetParent(),IDD_INPUT_EDIT);
}

void CMyFtpClass::OnInsertFile(CListCtrl *pListCtrl, LPVOID pIn, LPARAM lParam)
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

void CMyFtpClass::SetFileColumns(CListCtrl *pListCtrl)
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

BOOL CMyFtpClass::SetImageList(CListCtrl *pListCtrl, CComboBoxEx *pCombo)
{
    pListCtrl->SetImageList(&m_ctImageList,LVSIL_SMALL);
	if(!pCombo)
		return TRUE;
	pCombo->SetImageList(&m_ctImageList);
	return TRUE;
}

void CMyFtpClass::SetPopMenu(int nIndex)
{

}

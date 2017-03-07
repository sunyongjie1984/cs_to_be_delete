// MyFtpClass.h: interface for the CMyFtpClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYFTPCLASS_H__A1D026E2_4CF9_45CE_BCAA_093CFA63F6C0__INCLUDED_)
#define AFX_MYFTPCLASS_H__A1D026E2_4CF9_45CE_BCAA_093CFA63F6C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyFtpClass  
{
public:
	CMyFtpClass();
	virtual ~CMyFtpClass();
protected:
	HCURSOR m_hDragCursor;
	BOOL m_bDragging;
	CImageList* m_pDragImageList;
	CImageList m_ctImageList;
public:
	void SetPopMenu(int nIndex);
	BOOL SetImageList(CListCtrl* pListCtrl,CComboBoxEx* pCombo);
	void SetFileColumns(CListCtrl* pListCtrl);
	void OnInsertFile(CListCtrl* pListCtrl,LPVOID pIn,LPARAM lParam);
	void OnFileName(CListCtrl* pListCtrl);
	void GetFileIcon(CString& fileName,int* iIcon,int* iIconSel);
		typedef struct
	{
		char szFileName[256];
		char szFileDate[20];
		char szFileSize[20];
		int nType;
	}FILE_FTP_INFO;
	typedef struct
	{
		char fileName[256];
		UINT ufileFlag;
	}FILE_COUNT_INFO;
	typedef struct
	{
		char OldName[256];
		char NewName[256];
	}FILE_CHANGE_INFO

};

#endif // !defined(AFX_MYFTPCLASS_H__A1D026E2_4CF9_45CE_BCAA_093CFA63F6C0__INCLUDED_)

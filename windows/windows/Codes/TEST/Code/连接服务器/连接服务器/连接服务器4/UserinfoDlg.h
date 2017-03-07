#if !defined(AFX_USERINFODLG_H__9CA228EE_C011_48DF_8296_7C4ED74BF677__INCLUDED_)
#define AFX_USERINFODLG_H__9CA228EE_C011_48DF_8296_7C4ED74BF677__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserinfoDlg.h : header file
//
#include <stdio.h>
#include <assert.h>
#include <windows.h> 
#include <lm.h>
#include "Lmaccess.h"

#pragma comment(lib,"ActiveDS.lib")

/////////////////////////////////////////////////////////////////////////////
// CUserinfoDlg dialog

class CUserinfoDlg : public CDialog
{
// Construction
public:
	CUserinfoDlg(CWnd* pParent = NULL);   // standard constructor

////////////////////////////////
	LPUSER_INFO_0 pBuf;
	LPUSER_INFO_0 pTmpBuf;
	DWORD dwLevel;
	DWORD dwPrefMaxLen;
	DWORD dwEntriesRead;
	DWORD dwTotalEntries;
	DWORD dwResumeHandle;
	DWORD i;
	DWORD dwTotalCount;
	NET_API_STATUS nStatus;
	LPTSTR pszServerName;
// Dialog Data
	//{{AFX_DATA(CUserinfoDlg)
	enum { IDD = IDD_USER_INFO };
	CListCtrl	m_listuserinfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserinfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserinfoDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERINFODLG_H__9CA228EE_C011_48DF_8296_7C4ED74BF677__INCLUDED_)

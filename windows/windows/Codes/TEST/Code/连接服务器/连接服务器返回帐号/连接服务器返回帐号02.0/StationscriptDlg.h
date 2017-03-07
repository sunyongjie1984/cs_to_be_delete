#if !defined(AFX_STATIONSCRIPTDLG_H__4A4C3559_F1EE_47EE_9A60_20B034DA75EB__INCLUDED_)
#define AFX_STATIONSCRIPTDLG_H__4A4C3559_F1EE_47EE_9A60_20B034DA75EB__INCLUDED_

#include "stdafx.h"
#include <stdio.h>
#include <windows.h> 
#include <lm.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StationscriptDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStationscriptDlg dialog

class CStationscriptDlg : public CDialog
{
// Construction
public:
	CString m_serverName;
	CStationscriptDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStationscriptDlg)
	enum { IDD = IDD_DIALOG1 };
	CString	m_userName;
	CString	m_scriptpath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStationscriptDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStationscriptDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATIONSCRIPTDLG_H__4A4C3559_F1EE_47EE_9A60_20B034DA75EB__INCLUDED_)

 #if !defined(AFX_DIALOGRELATION_H__A615A403_1D89_41B6_9399_EC1EB5D84558__INCLUDED_)
#define AFX_DIALOGRELATION_H__A615A403_1D89_41B6_9399_EC1EB5D84558__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogRelation.h : header file
//

#include "TabPageSSL.h"
#include "En_Decode.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogRelation dialog

class CDialogRelation : public CTabPageSSL
{
// Construction
public:
	CDialogRelation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogRelation)
	enum { IDD = IDD_FORMVIEW_RELATION };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogRelation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogRelation)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void DrawHistgram();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGRELATION_H__A615A403_1D89_41B6_9399_EC1EB5D84558__INCLUDED_)

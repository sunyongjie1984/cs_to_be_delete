#if !defined(AFX_NEWTHREAD_H__7A3B3CD9_5FD9_41CB_B435_62F04EFBCE36__INCLUDED_)
#define AFX_NEWTHREAD_H__7A3B3CD9_5FD9_41CB_B435_62F04EFBCE36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewThread.h : header file
//


#define THREAD_MESSAGE1     WM_USER + 1000
#define THREAD_MESSAGE2     WM_USER + 1001
#define THREAD_MESSAGE3     WM_USER + 1002
/////////////////////////////////////////////////////////////////////////////
// NewThread thread

class NewThread : public CWinThread
{
	DECLARE_DYNCREATE(NewThread)
protected:
	NewThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NewThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~NewThread();

	// Generated message map functions
	//{{AFX_MSG(NewThread)
		// NOTE - the ClassWizard will add and remove member functions here.
    afx_msg void OnMessage1( WPARAM wParam, LPARAM lParam );
    afx_msg void OnMessage2( WPARAM wParam, LPARAM lParam );
    afx_msg void OnMessage3( WPARAM wParam, LPARAM lParam );
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWTHREAD_H__7A3B3CD9_5FD9_41CB_B435_62F04EFBCE36__INCLUDED_)

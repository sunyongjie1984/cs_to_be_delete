#if !defined(AFX_LISNSOCKET_H__60736CB2_B8B0_4256_A84A_12BF1E970136__INCLUDED_)
#define AFX_LISNSOCKET_H__60736CB2_B8B0_4256_A84A_12BF1E970136__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LisnSocket.h : header file
//


class CChatserverView;

/////////////////////////////////////////////////////////////////////////////
// CLisnSocket command target

class CLisnSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CLisnSocket(CChatserverView *pvew);
	virtual ~CLisnSocket();

// Overrides
public:
	virtual void OnAccept(int nErrorCode);
	CChatserverView *p_view;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLisnSocket)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CLisnSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISNSOCKET_H__60736CB2_B8B0_4256_A84A_12BF1E970136__INCLUDED_)

#if !defined(AFX_CLIENTSOCKET_H__92B5ED75_F22F_11D7_8D52_0030F149A9D4__INCLUDED_)
#define AFX_CLIENTSOCKET_H__92B5ED75_F22F_11D7_8D52_0030F149A9D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CLientSocket.h : header file
//

class CChatView;
class CChatDoc;
/////////////////////////////////////////////////////////////////////////////
// CCLientSocket command target


class CCLientSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CCLientSocket(CChatView  *view);
	virtual ~CCLientSocket();

// Overrides
public:
	virtual void OnReceive(int nErrorCode);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCLientSocket)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CCLientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
private:
	CChatView * p_view;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCKET_H__92B5ED75_F22F_11D7_8D52_0030F149A9D4__INCLUDED_)

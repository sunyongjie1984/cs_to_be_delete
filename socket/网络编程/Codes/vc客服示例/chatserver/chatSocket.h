#if !defined(AFX_CHATSOCKET_H__AF2A6F61_FF84_4627_AD62_56527582AF13__INCLUDED_)
#define AFX_CHATSOCKET_H__AF2A6F61_FF84_4627_AD62_56527582AF13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// chatSocket.h : header file
//

class CChatserverView;
class CMesg;

/////////////////////////////////////////////////////////////////////////////
// CchatSocket command target

class CchatSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CchatSocket(CChatserverView *pview);
	virtual ~CchatSocket();

// Overrides
public:
	virtual void OnReceive(int nErrorCode);
	void sendmessage(CMesg *msg);
	void receivemessage(CMesg *msg);
	void init();
	void Abort();



	CChatserverView *m_pview;
	CString name;
	CArchive *m_out;
	CArchive *m_in;
	CSocketFile *m_pfile;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CchatSocket)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CchatSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATSOCKET_H__AF2A6F61_FF84_4627_AD62_56527582AF13__INCLUDED_)

#if !defined(AFX_MESG_H__92B5ED74_F22F_11D7_8D52_0030F149A9D4__INCLUDED_)
#define AFX_MESG_H__92B5ED74_F22F_11D7_8D52_0030F149A9D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Mesg.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CMesg command target

class CMesg : public CObject
{
//	DECLARE_DYNCREATE(CMesg)
public:
	CMesg();           // protected constructor used by dynamic creation
    virtual ~CMesg();
// Attributes
public:

// Operations
public:
	void init();
	void Serialize(CArchive &ar);
	int type;
	CString to;
	CString from;
	CString m_str;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMesg)
	//}}AFX_VIRTUAL

// Implementation
protected:
//	virtual ~CMesg();

	// Generated message map functions
	//{{AFX_MSG(CMesg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

//	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESG_H__92B5ED74_F22F_11D7_8D52_0030F149A9D4__INCLUDED_)

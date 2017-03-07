#if !defined(AFX_DATAEX_H__53C8C66F_3837_11D3_BB17_00104BC71186__INCLUDED_)
#define AFX_DATAEX_H__53C8C66F_3837_11D3_BB17_00104BC71186__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataEx.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CExchange command target

class CExchange : public CAsyncSocket
{
// Attributes
private:
	int DataBlock;
	int MaxDataBlock;
	int CurrentBlock;

public:
	void DelDataBlock()
	{DataBlock--;}

// Operations
public:
	CExchange();
	virtual ~CExchange();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExchange)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CExchange)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAEX_H__53C8C66F_3837_11D3_BB17_00104BC71186__INCLUDED_)

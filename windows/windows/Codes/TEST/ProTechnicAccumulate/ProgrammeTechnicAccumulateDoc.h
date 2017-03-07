// ProgrammeTechnicAccumulateDoc.h : interface of the CProgrammeTechnicAccumulateDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROGRAMMETECHNICACCUMULATEDOC_H__86796DE7_AB87_4340_88FA_07E4EB035658__INCLUDED_)
#define AFX_PROGRAMMETECHNICACCUMULATEDOC_H__86796DE7_AB87_4340_88FA_07E4EB035658__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CProgrammeTechnicAccumulateDoc : public CDocument
{
protected: // create from serialization only
	CProgrammeTechnicAccumulateDoc();
	DECLARE_DYNCREATE(CProgrammeTechnicAccumulateDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgrammeTechnicAccumulateDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProgrammeTechnicAccumulateDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CProgrammeTechnicAccumulateDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRAMMETECHNICACCUMULATEDOC_H__86796DE7_AB87_4340_88FA_07E4EB035658__INCLUDED_)

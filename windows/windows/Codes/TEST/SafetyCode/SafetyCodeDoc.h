// SafetyCodeDoc.h : interface of the CSafetyCodeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAFETYCODEDOC_H__9D337EF4_EA0A_4A65_A36F_8BA1F65BA876__INCLUDED_)
#define AFX_SAFETYCODEDOC_H__9D337EF4_EA0A_4A65_A36F_8BA1F65BA876__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSafetyCodeDoc : public CDocument
{
protected: // create from serialization only
	CSafetyCodeDoc();
	DECLARE_DYNCREATE(CSafetyCodeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSafetyCodeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSafetyCodeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSafetyCodeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAFETYCODEDOC_H__9D337EF4_EA0A_4A65_A36F_8BA1F65BA876__INCLUDED_)


// eeeDoc.h : interface of the CeeeDoc class
//


#pragma once


class CeeeDoc : public CDocument
{
protected: // create from serialization only
	CeeeDoc();
	DECLARE_DYNCREATE(CeeeDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CeeeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};



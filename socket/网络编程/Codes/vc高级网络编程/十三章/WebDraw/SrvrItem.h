// SrvrItem.h : interface of the CWebDrawSrvrItem class
//

#if !defined(AFX_SRVRITEM_H__2562EC14_DA00_4F2A_A80F_EDDF852E0E08__INCLUDED_)
#define AFX_SRVRITEM_H__2562EC14_DA00_4F2A_A80F_EDDF852E0E08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWebDrawSrvrItem : public CDocObjectServerItem
{
	DECLARE_DYNAMIC(CWebDrawSrvrItem)

// Constructors
public:
	CWebDrawSrvrItem(CWebDrawDoc* pContainerDoc);

// Attributes
	CWebDrawDoc* GetDocument() const
		{ return (CWebDrawDoc*)CDocObjectServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWebDrawSrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CWebDrawSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRVRITEM_H__2562EC14_DA00_4F2A_A80F_EDDF852E0E08__INCLUDED_)

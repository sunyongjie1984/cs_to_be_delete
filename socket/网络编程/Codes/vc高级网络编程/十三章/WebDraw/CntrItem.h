// CntrItem.h : interface of the CWebDrawCntrItem class
//

#if !defined(AFX_CNTRITEM_H__14B89CCD_785D_4E03_B7E0_918F96820D0B__INCLUDED_)
#define AFX_CNTRITEM_H__14B89CCD_785D_4E03_B7E0_918F96820D0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWebDrawDoc;
class CWebDrawView;

class CWebDrawCntrItem : public COleDocObjectItem
{
	DECLARE_SERIAL(CWebDrawCntrItem)

// Constructors
public:
	CWebDrawCntrItem(CWebDrawDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CWebDrawDoc* GetDocument()
		{ return (CWebDrawDoc*)COleDocObjectItem::GetDocument(); }
	CWebDrawView* GetActiveView()
		{ return (CWebDrawView*)COleDocObjectItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWebDrawCntrItem)
	public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();
	protected:
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	virtual BOOL CanActivate();
	//}}AFX_VIRTUAL

// Implementation
public:
	~CWebDrawCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__14B89CCD_785D_4E03_B7E0_918F96820D0B__INCLUDED_)

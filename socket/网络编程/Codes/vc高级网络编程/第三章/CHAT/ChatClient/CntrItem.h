// CntrItem.h : interface of the CChatClientCntrItem class
//

#if !defined(AFX_CNTRITEM_H__414C0D9F_C7A0_41C9_96F5_7A3270536EFF__INCLUDED_)
#define AFX_CNTRITEM_H__414C0D9F_C7A0_41C9_96F5_7A3270536EFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CChatClientDoc;
class CChatClientView;

class CChatClientCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CChatClientCntrItem)

// Constructors
public:
	CChatClientCntrItem(REOBJECT* preo = NULL, CChatClientDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CChatClientDoc* GetDocument()
		{ return (CChatClientDoc*)CRichEditCntrItem::GetDocument(); }
	CChatClientView* GetActiveView()
		{ return (CChatClientView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatClientCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	~CChatClientCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__414C0D9F_C7A0_41C9_96F5_7A3270536EFF__INCLUDED_)

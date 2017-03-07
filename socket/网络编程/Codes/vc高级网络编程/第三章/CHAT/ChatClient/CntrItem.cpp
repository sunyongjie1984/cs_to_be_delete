// CntrItem.cpp : implementation of the CChatClientCntrItem class
//

#include "stdafx.h"
#include "ChatClient.h"

#include "ChatClientDoc.h"
#include "ChatClientView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatClientCntrItem implementation

IMPLEMENT_SERIAL(CChatClientCntrItem, CRichEditCntrItem, 0)

CChatClientCntrItem::CChatClientCntrItem(REOBJECT* preo, CChatClientDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
	
}

CChatClientCntrItem::~CChatClientCntrItem()
{
	// TODO: add cleanup code here
	
}

/////////////////////////////////////////////////////////////////////////////
// CChatClientCntrItem diagnostics

#ifdef _DEBUG
void CChatClientCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CChatClientCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////

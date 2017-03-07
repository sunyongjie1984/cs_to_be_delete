// MFCLeakTestDoc.cpp : implementation of the CMFCLeakTestDoc class
//

#include "stdafx.h"
#include "MFCLeakTest.h"

#include "MFCLeakTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCLeakTestDoc

IMPLEMENT_DYNCREATE(CMFCLeakTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCLeakTestDoc, CDocument)
END_MESSAGE_MAP()


// CMFCLeakTestDoc construction/destruction

CMFCLeakTestDoc::CMFCLeakTestDoc()
{
	// TODO: add one-time construction code here

}

CMFCLeakTestDoc::~CMFCLeakTestDoc()
{
}

BOOL CMFCLeakTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMFCLeakTestDoc serialization

void CMFCLeakTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CMFCLeakTestDoc diagnostics

#ifdef _DEBUG
void CMFCLeakTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCLeakTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCLeakTestDoc commands

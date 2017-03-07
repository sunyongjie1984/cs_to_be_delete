
// eeeDoc.cpp : implementation of the CeeeDoc class
//

#include "stdafx.h"
#include "eee.h"

#include "eeeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CeeeDoc

IMPLEMENT_DYNCREATE(CeeeDoc, CDocument)

BEGIN_MESSAGE_MAP(CeeeDoc, CDocument)
END_MESSAGE_MAP()


// CeeeDoc construction/destruction

CeeeDoc::CeeeDoc()
{
	// TODO: add one-time construction code here

}

CeeeDoc::~CeeeDoc()
{
}

BOOL CeeeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CeeeDoc serialization

void CeeeDoc::Serialize(CArchive& ar)
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


// CeeeDoc diagnostics

#ifdef _DEBUG
void CeeeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CeeeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CeeeDoc commands

// ReceiverDoc.cpp : implementation of the CReceiverDoc class
//

#include "stdafx.h"
#include "Receiver.h"

#include "ReceiverDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReceiverDoc

IMPLEMENT_DYNCREATE(CReceiverDoc, CDocument)

BEGIN_MESSAGE_MAP(CReceiverDoc, CDocument)
	//{{AFX_MSG_MAP(CReceiverDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReceiverDoc construction/destruction

CReceiverDoc::CReceiverDoc()
{
	// TODO: add one-time construction code here

}

CReceiverDoc::~CReceiverDoc()
{
}

BOOL CReceiverDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CReceiverDoc serialization

void CReceiverDoc::Serialize(CArchive& ar)
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

/////////////////////////////////////////////////////////////////////////////
// CReceiverDoc diagnostics

#ifdef _DEBUG
void CReceiverDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CReceiverDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReceiverDoc commands

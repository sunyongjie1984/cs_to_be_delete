// MyBrowserExDoc.cpp : implementation of the CMyBrowserExDoc class
//

#include "stdafx.h"
#include "MyBrowserEx.h"

#include "MyBrowserExDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyBrowserExDoc

IMPLEMENT_DYNCREATE(CMyBrowserExDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyBrowserExDoc, CDocument)
	//{{AFX_MSG_MAP(CMyBrowserExDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyBrowserExDoc construction/destruction

CMyBrowserExDoc::CMyBrowserExDoc()
{
	// TODO: add one-time construction code here

}

CMyBrowserExDoc::~CMyBrowserExDoc()
{
}

BOOL CMyBrowserExDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyBrowserExDoc serialization

void CMyBrowserExDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CMyBrowserExDoc diagnostics

#ifdef _DEBUG
void CMyBrowserExDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyBrowserExDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyBrowserExDoc commands

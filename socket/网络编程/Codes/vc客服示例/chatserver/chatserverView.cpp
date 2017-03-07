// chatserverView.cpp : implementation of the CChatserverView class
//

#include "stdafx.h"
#include "chatserver.h"

#include "chatserverDoc.h"
#include "chatserverView.h"
#include "Mesg.h"
#include "Port.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatserverView

IMPLEMENT_DYNCREATE(CChatserverView, CFormView)

BEGIN_MESSAGE_MAP(CChatserverView, CFormView)
	//{{AFX_MSG_MAP(CChatserverView)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_END, OnEnd)
	ON_BN_CLICKED(IDC_START, OnStart)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatserverView construction/destruction

CChatserverView::CChatserverView()
	: CFormView(CChatserverView::IDD)
{
	//{{AFX_DATA_INIT(CChatserverView)
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	initflag=0;

}

CChatserverView::~CChatserverView()
{
}

void CChatserverView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatserverView)
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_END, m_end);
	DDX_Control(pDX, IDC_START, m_start);
	DDX_Control(pDX, IDC_STATIC_INFO, m_info);
	//}}AFX_DATA_MAP
}

BOOL CChatserverView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CChatserverView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CChatserverView printing

BOOL CChatserverView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CChatserverView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CChatserverView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CChatserverView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CChatserverView diagnostics

#ifdef _DEBUG
void CChatserverView::AssertValid() const
{
	CFormView::AssertValid();
}

void CChatserverView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CChatserverDoc* CChatserverView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChatserverDoc)));
	return (CChatserverDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChatserverView message handlers

void CChatserverView::deletefromlist(CString name)
{
      int max;
	  CString item;
	  max=m_list.GetCount();
	  for(int i=0;i<max;i++)
	  {
		  m_list.GetText(i,item);
		  if(name==item)
			  m_list.DeleteString(i);
	  }
}

void CChatserverView::addtolist(CString name)
{
       m_list.AddString(name);
}

void CChatserverView::sendmsg(CchatSocket *sock, CMesg *msg)
{
      TRY
	  {
		  sock->sendmessage(msg);
	  }
	  CATCH(CFileException,e)
	  {
		  sock->Abort();
	  }
	  END_CATCH
}

void CChatserverView::UpdateClient(CMesg *msg, CchatSocket *clientsock)
{
	if(msg->type==1)//新用户上线
	{
		for(POSITION pos=m_clientlist.GetHeadPosition();pos!=NULL;)
		{
			CchatSocket*csock=(CchatSocket *)m_clientlist.GetNext(pos);
			if(csock->name==msg->from)//判断重名
			{
				CMesg msgback;
				msgback.type=3;
				msgback.from=msgback.to=msgback.m_str="";
				sendmsg(clientsock,&msgback);

				return;
			}
		}
	}
	for(POSITION pos=m_clientlist.GetHeadPosition();pos!=NULL;)
	{
		POSITION tmp=pos;
		CchatSocket*csock=(CchatSocket*)m_clientlist.GetNext(pos);
		if(clientsock!=csock)
			sendmsg(csock,msg);
		if(msg->type==1)
			if(csock->name=="")
			{
				csock->name=msg->from;
				addtolist(msg->from);
			}
	}
	if(msg->type==5)
	{
		for(POSITION pos=m_clientlist.GetHeadPosition();pos!=NULL;)
		{
			POSITION tmp=pos;
			CchatSocket*csock=(CchatSocket*)m_clientlist.GetNext(pos);
			if(csock==clientsock)
			{
				m_clientlist.RemoveAt(tmp);
				delete clientsock;
				deletefromlist(msg->from);
			}
		}
	}

}

void CChatserverView::Receive(CchatSocket *clientsock)
{
      CMesg msg;
      do
	  {
		  TRY
		  {
			  clientsock->receivemessage(&msg);
		  }
		  CATCH(CFileException,e)
		  {
			  clientsock->Abort();
		  }
		  END_CATCH
	  }
	  while(!clientsock->m_in->IsBufferEmpty());
	  UpdateClient(&msg,clientsock);
}

void CChatserverView::Accept()
{
     CchatSocket*clientsock=new CchatSocket(this);
	 if(m_listensock->Accept(*clientsock))
	 {
		 clientsock->init();
		 m_clientlist.AddTail(clientsock);
	 }
	 else
	 {
         delete clientsock;
	 }
}

void CChatserverView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CFormView::OnPaint() for painting messages
}

void CChatserverView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

void CChatserverView::OnEnd() 
{
	// TODO: Add your control notification handler code here
	m_start.EnableWindow(true);
	m_end.EnableWindow(false);
}

void CChatserverView::OnStart() 
{
	// TODO: Add your control notification handler code here
	CPort portdlg;
	if(portdlg.DoModal()==IDOK)
	{
          m_listensock=new CLisnSocket(this);
		  if(m_listensock->Create(8800/*portdlg.m_port*/))
		  {
			  if(!m_listensock->Listen())
			  { 
				  AfxMessageBox("监听失败");
                  return;
			  }
		  }
	}
	m_start.EnableWindow(false);
	m_end.EnableWindow(true);
}

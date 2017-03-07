// chatView.cpp : implementation of the CChatView class
//

#include "stdafx.h"
#include "chat.h"

#include "chatDoc.h"
#include "chatView.h"

////////////////////////////////
#include "CLientSocket.h"

#include "LoginDlg.h"
////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define BOARD 469
#define CHESS 26
#define SIZE 13
#define pattern 30
#define distance 19
//////////////////////////////
//#include CLientSocket.h
//#include Mesg.h
/////////////////////////////////////////////////////////////////////////////
// CChatView

IMPLEMENT_DYNCREATE(CChatView, CFormView)

BEGIN_MESSAGE_MAP(CChatView, CFormView)
	//{{AFX_MSG_MAP(CChatView)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_BN_CLICKED(IDC_LOGIN, OnLogin)
	ON_BN_CLICKED(IDC_LOGOUT, OnLogout)
	ON_NOTIFY(NM_CLICK, IDC_NAMELIST, OnClickNamelist)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_BLACKSTART, OnBlackstart)
	ON_UPDATE_COMMAND_UI(ID_BLACKSTART,OnUpdateBlackstart)
	ON_UPDATE_COMMAND_UI(IDC_SEND,OnUpdatesend)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()
// CChatView construction/destruction
CChatView::CChatView()
	: CFormView(CChatView::IDD)
{
	//{{AFX_DATA_INIT(CChatView)
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	bmp[0].LoadBitmap(IDB_BOARD);
	bmp[1].LoadBitmap(IDB_BLACK);
	bmp[2].LoadBitmap(IDB_WHITE);
	////////////////////////////////////////////

	
	pt.x=0;
	pt.y=0;
	start=0;
	first=0;
	ii = 0;
	zz=0;
	jj=0;
	turn=false;

	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			state[i][j]=0;
	
		
}
void CChatView::OnBlackstart() 
{
	start=1;
	first=1;
	turn=true;
	GetDlgItem(IDC_STATIC_INFO)->SetWindowText("我方下棋--------(您执黑棋)");
	CString to;	
	m_combo.GetWindowText(to);
	msg.to=to;
	msg.type=7;
	ii=1;
	

	sendmsg();
	
	
}
void CChatView::OnLButtonDown(UINT nFlags, CPoint point) 
{
    if(start&&turn)
	{
		if(!canvertpos(point))//
		{
			return;
		}
        Invalidate();
   	    if(check(px,py,1))
		{
		     start=0;
		}		
		CString to;
	    CString m_str;
		m_str=formatsend(px,py);
	    CString out;
	    m_combo.GetWindowText(to);
	    msg.to=to;
	    msg.m_str=m_str;
	    msg.type=6;
	    sendmsg();
		if(first)
			GetDlgItem(IDC_STATIC_INFO)->SetWindowText("对方下棋--------(您执黑棋)");
		turn=!turn;
	}		
	CFormView::OnLButtonDown(nFlags, point);
}
CString CChatView::formatsend(int x, int y)
{
        CString outbuf,temp;
		char s;
		s='a'+x;
		temp.Format("%c",s);
		outbuf=temp;
		s='a'+y;
		temp.Format("%c",s);
		outbuf+=temp;
		return outbuf;
}
int CChatView::getformat(CString buf, int *x, int *y)
{	   
	 char s;
	 s=buf.GetAt(0);
	 *x=int(s-'a');
	 s=buf.GetAt(1);
	 *y=int(s-'a');
	 return 0;
}
void CChatView::OnDraw(CDC *pDC)
{
          putchess(px,py);//判断落子颜色和位置
}	

void CChatView::putchess(int px, int py)
{
       CPaintDC dc(this);
	   CSize psize(CHESS,CHESS);
	   CPoint ppos;
	   ppos.x=pt.x+distance+px*pattern-SIZE;
       ppos.y=pt.y+distance+py*pattern-SIZE;
	   if((first==1 && turn)||(first==0 && !turn))      
		   dc.DrawState(ppos,psize,&bmp[1],DST_BITMAP);
	   else
		   dc.DrawState(ppos,psize,&bmp[2],DST_BITMAP);
}
void CChatView::OnPaint() 
{
	CPaintDC dc(this); 	
	m_pImageList=new CImageList();
	m_pImageList->Create(IDB_BITMAP1,32,1,RGB(255,255,255));
	m_namelist.SetImageList(m_pImageList,LVSIL_SMALL);
	m_namelist.InsertColumn(0,"在线用户",LVCFMT_LEFT,100);
	m_combo.AddString("所有人");
	m_combo.SetCurSel(0);	
//	m_login.EnableWindow(true);
	if (jj==0)
	{
//		m_logout.EnableWindow(false);
//		m_send.EnableWindow(false);
	}
	

	CSize size;
    size.cx=BOARD;
	size.cy=BOARD;
	dc.DrawState(pt,size,&bmp[0],DST_BITMAP);
	for(int i=0;i<N;i++)
	{	for(int j=0;j<N;j++)
		{
			if(state[i][j]!=0)
			{
				CSize psize(CHESS,CHESS);
				CPoint ppos;
				ppos.x=pt.x+distance+i*pattern-SIZE;
                ppos.y=pt.y+distance+j*pattern-SIZE;
				if((first==1&& state[i][j]==1)||(first==0 && state[i][j]==-1))
				    dc.DrawState(ppos,psize,&bmp[1],DST_BITMAP); 
				else
				    dc.DrawState(ppos,psize,&bmp[2],DST_BITMAP); 
			}
		}
	}
	OnDraw(&dc);
}

bool CChatView::canvertpos(CPoint ps)
{
       CRect rc;
	   rc.top=pt.y;
	   rc.left=pt.x;
	   rc.bottom=pt.y+BOARD;
	   rc.right=pt.x+BOARD;
	   if(!PtInRect(rc,ps))
		   return false;
	   int x,y,i;
	   x=ps.x-pt.x-distance;
	   y=ps.y-pt.y-distance;
	   for(i=0;i<N;i++)
		   if(x>i*pattern-SIZE&&x<i*pattern+SIZE)
		   {
			   px=i;
			   break;
		   }
	   for(i=0;i<N;i++)
		   if(y>i*pattern-SIZE&&y<i*pattern+SIZE)
		   {
			   py=i;
			   break;
		   }
	   if(px<0||px>14||py<0||py>14)
	   {
		   MessageBox("该处无法放子，请正确点击");
		   return false;
	   }
	   if(state[px][py])
	   {
		   MessageBox("此处已有子，请重新选择放子位置");
		   return false;
	   }
	   state[px][py]=1;
	   return true;
}
bool CChatView::check(int x, int y, int me)
{
	int dx[]={1,1,1,0,-1,-1,-1,0};
	int dy[]={-1,0,1,1,1,0,-1,-1};
	int i,num,num1;
	int chess;
	chess=me;
	for(i=0;i<8;i++)
	{
		if(dx[i]+x>=0 && dx[i]+x<N && dy[i]+y>=0 && dy[i]+y<N)
		{
			num=0;
			while((num+1)*dx[i]+x>=0 && (num+1)*dx[i]+x<N && (num+1)*dy[i]+y>=0 && (num+1)*dy[i]+y<N && state[(num+1)*dx[i]+x][(num+1)*dy[i]+y]==chess)
			{
				num++;
			}
			num1=num;
			num=0;
			while(-(num+1)*dx[i]+x>=0 && -(num+1)*dx[i]+x<N && -(num+1)*dy[i]+y>=0 && -(num+1)*dy[i]+y<N && state[-(num+1)*dx[i]+x][-(num+1)*dy[i]+y]==chess)
			{
				num++;
			}
			if(num+num1>=4)
			{
				if(chess==-1)
				{
					MessageBox("很遗憾，您失败了!");
					return true;
				}
				else
				{
					MessageBox("恭喜您，您胜利了!");
					return true;
				}
			}
		}
	}
	return false;
}
CChatView::~CChatView()
{
}

void CChatView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatView)
	DDX_Control(pDX, IDC_STATIC2, m_info);
	DDX_Control(pDX, IDC_STATIC1, m_object);
	DDX_Control(pDX, IDC_NAMELIST, m_namelist);
//	DDX_Control(pDX, IDC_LOGOUT, m_logout);
//	DDX_Control(pDX, IDC_LOGIN, m_login);
//	DDX_Control(pDX, IDC_SEND, m_send);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Control(pDX, IDC_EDIT_MSG, m_msg);
	DDX_Control(pDX, IDC_MSGLIST, m_msglist);
	//}}AFX_DATA_MAP
}

BOOL CChatView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CChatView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
}

/////////////////////////////////////////////////////////////////////////////
// CChatView printing

BOOL CChatView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CChatView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CChatView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CChatView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CChatView diagnostics

#ifdef _DEBUG
void CChatView::AssertValid() const
{
	CFormView::AssertValid();
}

void CChatView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CChatDoc* CChatView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChatDoc)));
	return (CChatDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChatView message handlers

bool CChatView::connectserver(CString name, CString servname, int servport)
{
     m_socket=new CCLientSocket(this);
	 if(!m_socket->Create())
	 {
		 TRACE("Create Socket Failed!");
		 delete m_socket;
		 m_socket=NULL;
		 return false;
	 }
//	 CString servnamea="\\\\192.168.0.206";
//	 servport=8800;
//	 TCHAR SERVERNAME[100]={0};
//	 strcpy(SERVERNAME,servnamea.GetBuffer(0));
	 while(!m_socket->Connect(servname,servport))
	 {
		 if(AfxMessageBox("无法连接服务器，是否重试?",MB_YESNO)==IDNO)
		 {
			 delete m_socket;
			 m_socket=NULL;
			 return false;
		 }
	 }

	 m_sockfile=new CSocketFile(m_socket);
	 m_in=new CArchive(m_sockfile,CArchive::load);
     m_out=new CArchive(m_sockfile,CArchive::store);

//	 m_login.EnableWindow(false);
//	 m_logout.EnableWindow(true);
//	 m_send.EnableWindow(true);
	 msg.type=1;
	 msg.m_str="";
	 sendmsg();
	 return true;
}

void CChatView::sendmsg()
{
    msg.from=name;
	if(m_out!=NULL)
	{
         TRY
		 {
		      msg.Serialize(*m_out);
		      m_out->Flush();
		 }
	     CATCH(CFileException,e)
		 {
		      m_out->Abort();
			  delete m_out;
			  m_out=NULL;
		 }
	     END_CATCH
	}
}

void CChatView::RecvMsg()
{
     TRY
	 {
		 msg.Serialize(*m_in);
		 process_msg();
	 }
	 CATCH(CFileException,e)
	 {
		 m_in->Abort();
	 }
	 END_CATCH
}

void CChatView::process_msg()
{
      int i,max;
	  if(msg.type==1)
	  {
		  max=m_namelist.GetItemCount();
		  for(i=0;i<max;i++)
		  {
			  if( m_namelist.GetItemText(i,0)==msg.from)
				  return;
		  }
		  m_namelist.InsertItem(max,msg.from,0);
		  m_combo.AddString(msg.from);
		  CString to;
		  to=msg.from;
		  msg.type=2;
		  msg.to=to;
		  sendmsg();
	  }
	  if(msg.type==2)
	  {
		  if(msg.to!=name)
			  return;

		  max=m_namelist.GetItemCount();
		  for(i=0;i<max;i++)
		  {
			  if( m_namelist.GetItemText(i,0)==msg.from)
				  return;
		  }
		  m_namelist.InsertItem(max,msg.from,0);
		  m_combo.AddString(msg.from);
	  }
      if(msg.type==3)
	  {
		  MessageBox("该用户名已经存在，请换其他用户名重新登录");
		  delete m_in;
		  m_in=NULL;
		  delete m_out;
		  m_out=NULL;
		  delete m_sockfile;
		  m_sockfile=NULL;
		  delete m_socket;
		  m_socket=NULL;
	  }
      if(msg.type==4)
	  {
          CString out;
		  out=msg.from+"对";
		  out+=msg.to==name?"你":msg.to;
		  out+="说";
		  out+=msg.m_str;
		  m_msglist.AddString(out);
	  }
	  if(msg.type==5)
	  {
		  int index=-1;
		  max=m_namelist.GetItemCount();

		  for(i=0;i<max;i++)
		  {
			  if( m_namelist.GetItemText(i,0)==msg.from)
				  index=i;
		  }
		  if(index!=-1)
		  {
			  m_namelist.DeleteItem(index);
              m_msglist.AddString(msg.from+"离开聊天室！");
              int number=m_combo.GetCount();
			  CString nametemp;
			  for(i=0;i<number;i++)
			  {
				  m_combo.GetLBText(i,nametemp);
				  if(nametemp==msg.from)
					  m_combo.DeleteString(i);
   			  }
		  }
	  }
	  if(msg.type==6)
	  {
    	 CString out;
//	     int cc,x,y;
	     int result;
	     //cc=m_connectsocket.Receive(buf,1024);

//	     if(cc!=SOCKET_ERROR)
//		 {
//		     buf[cc]=NULL;
	         out=msg.m_str;
		     result=getformat(out,&px,&py);
		     if(!turn && !result)
			 {
			       state[px][py]=-1;

			       Invalidate();
			       check(px,py,-1);
			       if(first)
				        GetDlgItem(IDC_STATIC_INFO)->SetWindowText("我方下棋-------------（您持黑棋）");
			       else
                        GetDlgItem(IDC_STATIC_INFO)->SetWindowText("对方下棋-------------（您持白棋）");
		           turn=!turn;
			 }
//		 }
	  }
	  if(msg.type==7)
	  {
		  first=0;
		  start=1;
		  //turn=true;
		  



	  }
}

void CChatView::OnSend() 
{
	CString to;
	CString m_str;
	CString out;
	m_combo.GetWindowText(to);
	msg.to=to;
	m_msg.GetWindowText(m_str);
	msg.m_str=m_str;
	msg.type=4;
	sendmsg();
	out=" 你对"+to+"说："+m_str;
	m_msglist.AddString(out);
}

void CChatView::OnLogin() 
{
	CLoginDlg dlg;
	while(1)
	{
		if(dlg.DoModal()!=IDOK)
			return;
		name=dlg.name;
		if(connectserver(dlg.name,dlg.sername,dlg.serport))// dlg.name,dlg.sername,dlg.serport))
		{
			
			return;
		}
		if(AfxMessageBox("登录不上服务器，是否重新试？",MB_YESNO)==IDNO)
		{
			return;
		}
	}
}

void CChatView::OnLogout() 
{
	// TODO: Add your control notification handler code here
	msg.type=5;
	sendmsg();
	delete m_in;
	m_in=NULL;
	delete m_out;
	m_out=NULL;
	delete m_sockfile;
	m_sockfile=NULL;
	delete m_socket;
	m_socket=NULL;
//	m_login.EnableWindow(true);
////	m_logout.EnableWindow(false);

}

void CChatView::OnClickNamelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int selitem=m_namelist.GetSelectionMark();
	int i;
	CString name=m_namelist.GetItemText(selitem,0);
	int number=m_combo.GetCount();
	CString nametemp;

	   for(i=0;i<number;i++)
	   {
		   m_combo.GetLBText(i,nametemp);
		   if(nametemp==name)
			   m_combo.SetCurSel(i);
	   }
	*pResult = 0;
	ii=1;
	zz=1;
}
void CChatView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
}

void CChatView::OnUpdateBlackstart(CCmdUI* pCmdUI)
{
	 
	if (ii==0)
	{
		pCmdUI->Enable(FALSE);
	}
}
void CChatView::OnUpdatesend(CCmdUI* pCmdUI)
{
	if (zz==0)
	{
		pCmdUI->Enable(FALSE);
	}
}





















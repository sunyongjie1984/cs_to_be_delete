// Draw.cpp : implementation file
//

#include "stdafx.h"
#include "ReadCompass.h"
#include "Draw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDraw
extern double m_heading[2000];
extern  m_num;

IMPLEMENT_DYNCREATE(CDraw, CView)

CDraw::CDraw()
{
}

CDraw::~CDraw()
{
}


BEGIN_MESSAGE_MAP(CDraw, CView)
	//{{AFX_MSG_MAP(CDraw)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDraw drawing

void CDraw::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	int           cxGraph,cyGraph ;
        RECT         rc;

        CPen   pen (PS_SOLID, 1, RGB(255, 0, 0)); // red pen
        CBrush brush(RGB(255, 0, 0));             // red brush
        CBrush* pOldBrush = pDC->SelectObject(&brush);
        CPen*   pOldPen = pDC->SelectObject(&pen);

        cxGraph = 280;
        cyGraph = 550;  // defined in resource.h

        this->GetClientRect(&rc);
        pDC->SetMapMode(MM_ANISOTROPIC);
        pDC->SetWindowOrg(0, 0);
        pDC->SetViewportOrg(10, rc.bottom-10);
        pDC->SetWindowExt(cxGraph, cyGraph);
        pDC->SetViewportExt(rc.right-20, -(rc.bottom-20));
      
        pDC->MoveTo(30, 30);
        pDC->LineTo(30, cyGraph);
        pDC->MoveTo(30, 30);
        pDC->LineTo(cxGraph, 30);

//		pDC->SetBkMode(TRANSPARENT);
  //  int ntxtcolor=pDC->SetTextColor(RGB(0,0,0));
 	pDC->TextOut(240-5,10+5,"210");
	pDC->TextOut(210-5,10+5,"180");	
	pDC->TextOut(60-5,10+5,"30");
    pDC->TextOut(90-5,10+5,"60");
    pDC->TextOut(120-5,10+5,"90");
	pDC->TextOut(150-5,10+5,"120");
	pDC->TextOut(180-5,10+5,"150");


	CPen   pen3 (PS_SOLID, 1, RGB(0, 0, 0)); // red pen
    CBrush brush3(RGB(0, 0, 0));             // red brush
    CBrush* pOldBrush3 = pDC->SelectObject(&brush3);
    CPen*   pOldPen3 = pDC->SelectObject(&pen3);
	pDC -> MoveTo( 30, 430);
	pDC -> LineTo( 280, 430 );

    pDC -> MoveTo( 30, 330);
	pDC -> LineTo( 280, 330);
	pDC->SelectObject(pOldBrush3);
    pDC->SelectObject(pOldPen3);

  //  pDC->TextOut(0,450+25,"420");
	pDC->TextOut(0,430+5,"400");
	pDC->TextOut(0,330+5,"300"); 
    pDC->TextOut(0,230+5,"200");
	pDC->TextOut(0,130+5,"100");
	pDC->TextOut(0,80+5, "50");
	pDC->TextOut(0,30+5,"0");

  //  pDC->SetTextColor(ntxtcolor);

		for( int nCount = 1; nCount < 9; nCount++ )
	{
		pDC -> MoveTo( nCount * 30+30, 10 +30);
		pDC -> LineTo( nCount * 30+30, 0 +30 );
		pDC -> MoveTo( nCount * 30 - 15+30, 5 +30);
		pDC -> LineTo( nCount * 30 - 15+30, 0 +30 );
	}
        for(  nCount = 1; nCount < 10; nCount++ )
		 {

		pDC -> MoveTo( 0 +30, nCount * 50+30 );
		pDC -> LineTo( 10+30, nCount * 50 +30);
		pDC -> MoveTo( 0 +30, nCount * 50- 25 +30);
		pDC -> LineTo( 5+30, nCount * 50 - 25+30 );
	}

        
        pDC->SelectObject(::GetStockObject (NULL_PEN));
       
       pDC->SelectObject(pOldBrush);
       pDC->SelectObject(pOldPen);
////////////////////////////////////////////////////////
	   CPen   pen2 (PS_SOLID, 1, RGB(0, 255, 0)); // red pen
        CBrush brush2(RGB(255, 0, 0));             // red brush
        CBrush* pOldBrush2 = pDC->SelectObject(&brush2);
        CPen*   pOldPen2 = pDC->SelectObject(&pen2);

   
	    CString str;
		str.Format("航向变化曲线图");
		pDC->TextOut(100,535,str);

		pDC->MoveTo(0+30,m_heading[0]+30);
//        pDC->LineTo(200,100);
		 for(int j=1;j<m_num;j++)		
	  { 
		pDC->LineTo(j+30,m_heading[j]+30);
	  }


    pDC->SelectObject(pOldBrush2);
    pDC->SelectObject(pOldPen2);
}

/////////////////////////////////////////////////////////////////////////////
// CDraw diagnostics

#ifdef _DEBUG
void CDraw::AssertValid() const
{
	CView::AssertValid();
}

void CDraw::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDraw message handlers

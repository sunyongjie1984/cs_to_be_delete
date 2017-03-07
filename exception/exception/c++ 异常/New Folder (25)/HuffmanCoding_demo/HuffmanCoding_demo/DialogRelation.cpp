         // DialogRelation.cpp : implementation file
//

#include "stdafx.h"
#include "NewTab.h"
#include "DialogRelation.h"

extern En_Decode Coder;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogRelation dialog


CDialogRelation::CDialogRelation(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CDialogRelation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogRelation)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogRelation::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogRelation)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogRelation, CTabPageSSL)
	//{{AFX_MSG_MAP(CDialogRelation)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogRelation message handlers

void CDialogRelation::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
	// 字符串
	CString str;
	// 循环变量
	LONG i;

	// 最大计数
	LONG lMaxCount = Coder.GetMaxFreq();
	// 设备上下文
//	CPaintDC dc(this);

	// 获取绘制坐标的文本框
	CWnd* pWnd = GetDlgItem(IDC_STATIC_HISTGRAM);
	// 指针
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	pDC->Rectangle(0,0,350,300);
	// 创建画笔对象
	CPen* pPenRed = new CPen;
	// 红色画笔
	pPenRed->CreatePen(PS_SOLID,1,RGB(255,0,0));
	// 创建画笔对象
	CPen* pPenBlue = new CPen;
	// 蓝色画笔
	pPenBlue->CreatePen(PS_SOLID,1,RGB(0,0, 255));
	// 创建画笔对象
	CPen* pPenGreen = new CPen;
	// 绿色画笔
	pPenGreen->CreatePen(PS_DOT,1,RGB(0,255,0));

	// 选中当前红色画笔，并保存以前的画笔
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);

	// 绘制坐标轴
	pDC->MoveTo(10,10);

	// 垂直轴
	pDC->LineTo(10,280);

	// 水平轴
	pDC->LineTo(320,280);

	// 写X轴刻度值
	str.Format("0");
	pDC->TextOut(10, 283, str);
	str.Format("50");
	pDC->TextOut(60, 283, str);
	str.Format("100");
	pDC->TextOut(110, 283, str);
	str.Format("150");
	pDC->TextOut(160, 283, str);
	str.Format("200");
	pDC->TextOut(210, 283, str);
	str.Format("255");
	pDC->TextOut(265, 283, str);

	// 绘制X轴刻度
	for (i = 0; i < 256; i += 5)
	{
		if ((i & 1) == 0)
		{
			// 10的倍数
			pDC->MoveTo(i + 10, 280);
			pDC->LineTo(i + 10, 284);
		}
		else
		{
			// 10的倍数
			pDC->MoveTo(i + 10, 280);
			pDC->LineTo(i + 10, 282);
		}
	}

	// 绘制X轴箭头
	pDC->MoveTo(315,275);
	pDC->LineTo(320,280);
	pDC->LineTo(315,285);

	// 绘制X轴箭头
	pDC->MoveTo(10,10);
	pDC->LineTo(5,15);
	pDC->MoveTo(10,10);
	pDC->LineTo(15,15);

	// 输出最大计数值
	pDC->MoveTo(10, 25);
	pDC->LineTo(14, 25);
	str.Format("%d", lMaxCount);
	pDC->TextOut(11, 26, str);

	// 更改成绿色画笔
	pDC->SelectObject(pPenGreen);	
/*
	// 绘制窗口上下限
	pDC->MoveTo(m_iLowGray + 10, 25);
	pDC->LineTo(m_iLowGray + 10, 280);
	pDC->MoveTo(m_iUpGray + 10, 25);
	pDC->LineTo(m_iUpGray + 10, 280);//*/

	// 更改成蓝色画笔
	pDC->SelectObject(pPenBlue);	

	// 判断是否有计数
	if (lMaxCount > 0)
	{
		// 绘制直方图
		for (i = 0; i <= 256; i ++)
		{
			pDC->MoveTo(i + 10, 280);
			pDC->LineTo(i + 10, 281 - (int) (Coder.GetFreq(i) * 256 / lMaxCount));
		}
	}//*/

	// 恢复以前的画笔
	pDC->SelectObject(pOldPen);	

	// 删除新的画笔
	delete pPenRed;
	delete pPenBlue;
	delete pPenGreen;

	// Do not call CTabPageSSL::OnPaint() for painting messages
}

void CDialogRelation::DrawHistgram()
{
/*	// 字符串
	CString str;
	// 循环变量
	LONG i;

	// 最大计数
	LONG lMaxCount = 0;
	// 设备上下文
	CPaintDC dc(this);

	// 获取绘制坐标的文本框
	CWnd* pWnd = GetDlgItem(IDC_STATIC_HISTGRAM);
	// 指针
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	pDC->Rectangle(0,0,350,300);
	// 创建画笔对象
	CPen* pPenRed = new CPen;
	// 红色画笔
	pPenRed->CreatePen(PS_SOLID,1,RGB(255,0,0));
	// 创建画笔对象
	CPen* pPenBlue = new CPen;
	// 蓝色画笔
	pPenBlue->CreatePen(PS_SOLID,1,RGB(0,0, 255));
	// 创建画笔对象
	CPen* pPenGreen = new CPen;
	// 绿色画笔
	pPenGreen->CreatePen(PS_DOT,1,RGB(0,255,0));

	// 选中当前红色画笔，并保存以前的画笔
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);

	// 绘制坐标轴
	pDC->MoveTo(10,10);

	// 垂直轴
	pDC->LineTo(10,280);
	
	// 水平轴
	pDC->LineTo(320,280);

	// 写X轴刻度值
	str.Format("0");
	pDC->TextOut(10, 283, str);
	str.Format("50");
	pDC->TextOut(60, 283, str);
	str.Format("100");
	pDC->TextOut(110, 283, str);
	str.Format("150");
	pDC->TextOut(160, 283, str);
	str.Format("200");
	pDC->TextOut(210, 283, str);
	str.Format("255");
	pDC->TextOut(265, 283, str);

	// 绘制X轴刻度
	for (i = 0; i < 256; i += 5)
	{
		if ((i & 1) == 0)
		{
			// 10的倍数
			pDC->MoveTo(i + 10, 280);
			pDC->LineTo(i + 10, 284);
		}
		else
		{
			// 10的倍数
			pDC->MoveTo(i + 10, 280);
			pDC->LineTo(i + 10, 282);
		}
	}

	// 绘制X轴箭头
	pDC->MoveTo(315,275);
	pDC->LineTo(320,280);
	pDC->LineTo(315,285);

	// 绘制X轴箭头
	pDC->MoveTo(10,10);
	pDC->LineTo(5,15);
	pDC->MoveTo(10,10);
	pDC->LineTo(15,15);

	// 计算最大计数值
	for (i = m_iLowGray; i <= m_iUpGray; i ++)
	{
		// 判断是否大于当前最大值
		if (m_lCount[i] > lMaxCount)
		{
			// 更新最大值
			lMaxCount = m_lCount[i];
		}
	}

	// 输出最大计数值
	pDC->MoveTo(10, 25);
	pDC->LineTo(14, 25);
	str.Format("%d", lMaxCount);
	pDC->TextOut(11, 26, str);

	// 更改成绿色画笔
	pDC->SelectObject(pPenGreen);	

	// 绘制窗口上下限
	pDC->MoveTo(m_iLowGray + 10, 25);
	pDC->LineTo(m_iLowGray + 10, 280);
	pDC->MoveTo(m_iUpGray + 10, 25);
	pDC->LineTo(m_iUpGray + 10, 280);

	// 更改成蓝色画笔
	pDC->SelectObject(pPenBlue);	

	// 判断是否有计数
	if (lMaxCount > 0)
	{
		// 绘制直方图
		for (i = m_iLowGray; i <= m_iUpGray; i ++)
		{
			pDC->MoveTo(i + 10, 280);
			pDC->LineTo(i + 10, 281 - (int) (m_lCount[i] * 256 / lMaxCount));
		}
	}

	// 恢复以前的画笔
	pDC->SelectObject(pOldPen);	

	// 删除新的画笔
	delete pPenRed;
	delete pPenBlue;
	delete pPenGreen;*/

}

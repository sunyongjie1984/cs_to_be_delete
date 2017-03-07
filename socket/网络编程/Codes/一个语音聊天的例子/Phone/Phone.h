// Phone.h : main header file for the PHONE DLL
//

#if !defined(AFX_PHONE_H__53C8C668_3837_11D3_BB17_00104BC71186__INCLUDED_)
#define AFX_PHONE_H__53C8C668_3837_11D3_BB17_00104BC71186__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

class CExchange;

#define MAXWAVEBLOCK  10//输入内存块数
#define MAXWAVEBUFFER 800//每块内存大小

extern CString RemoteHost;//远程主机名
extern CString RemoteIp;//远程主机IP地址
extern long RemotePort;//远端电话IP端口
extern HWAVEOUT hWaveOut;
extern WAVEHDR WaveHdrOut[MAXWAVEBLOCK];
extern bool m_Opened;//电话状态

/////////////////////////////////////////////////////////////////////////////
// CPhoneApp
// See Phone.cpp for the implementation of this class
//

class CPhoneApp : public CWinApp
{
public:
	CPhoneApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPhoneApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CPhoneApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PHONE_H__53C8C668_3837_11D3_BB17_00104BC71186__INCLUDED_)

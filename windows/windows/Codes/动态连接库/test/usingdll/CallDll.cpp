// CallDll.cpp: implementation of the CCallDll class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "usingdll.h"
#include "CallDll.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCallDll::CCallDll()
{
	MyMsgBox = NULL;
	aMsgBoxA  = NULL;

	m_hmyDll = LoadLibrary( "mydll.dll" );

	if( NULL == m_hmyDll )
	{
		return;
	}

	MyMsgBox  = ( _MyMsgBox )GetProcAddress( m_hmyDll, "MyMsgBox" );
	aMsgBoxA  = ( _aMsgBoxA )GetProcAddress( m_hmyDll, "aMsgBoxA" );
	
	if ( ( NULL == MyMsgBox ) &&
		 ( NULL == aMsgBoxA ) )
	{
		FreeLibrary( m_hmyDll );
		return;
	}
}

CCallDll::~CCallDll()
{
	if( NULL != m_hmyDll )
	{
		FreeLibrary( m_hmyDll );
	}
}

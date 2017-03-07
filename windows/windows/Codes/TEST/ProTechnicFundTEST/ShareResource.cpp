// ShareResource.cpp: implementation of the CShareResource class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProgrammeTechnicFund.h"
#include "ShareResource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShareResource::CShareResource()
{

}

CShareResource::~CShareResource()
{

}

int CShareResource::HintMessageBox( HWND hWnd, UINT errorID, UINT infoHint, UINT type )
{
	CHAR szHintInfo[MAX_PATH] = {0};
	CHAR szHint[MAX_PATH]     = {0};
	
	::LoadString( NULL,	errorID, szHintInfo, sizeof(CHAR) * MAX_PATH );
	
	::LoadString( NULL,	infoHint, szHint, sizeof(CHAR) * MAX_PATH );
	
	int nResult = ::MessageBox( hWnd, szHintInfo, szHint, type );
	
	return nResult;
}
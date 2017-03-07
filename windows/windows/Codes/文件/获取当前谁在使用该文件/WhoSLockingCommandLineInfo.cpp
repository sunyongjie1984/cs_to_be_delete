// WhoSLockingCommandLineInfo.cpp: implementation of the CWhoSLockingCommandLineInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WhoSLocking.h"
#include "WhoSLockingCommandLineInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWhoSLockingCommandLineInfo::CWhoSLockingCommandLineInfo()
{

}

CWhoSLockingCommandLineInfo::~CWhoSLockingCommandLineInfo()
{

}

void CWhoSLockingCommandLineInfo::ParseParam(LPCTSTR lpszParam, BOOL bFlag, BOOL bLast)
{
    if (!bFlag && lpszParam && *lpszParam!='\0') {
        // A file name has been passed as a parameter: store it
        m_szDefaultFilePath = lpszParam;
    }
}

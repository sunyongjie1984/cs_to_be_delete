// IsClientEnterDomain1.h: interface for the IsClientEnterDomain class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISCLIENTENTERDOMAIN1_H__6A1F59DD_1CD1_4031_8678_7420D83F0105__INCLUDED_)
#define AFX_ISCLIENTENTERDOMAIN1_H__6A1F59DD_1CD1_4031_8678_7420D83F0105__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Winbase.h"
#include "Windows.h"
#include "Winnt.h"
#pragma comment(lib,"Kernel32.lib")
#pragma comment(lib,"Netapi32.lib")
#pragma comment(lib,"Mpr.lib")
   
#define JOIN_GROUP 1
#define JOIN_DOMAIN 2
#define NOT_JOIN 0
class IsClientEnterDomain  
{
public:
	IsClientEnterDomain();
	virtual ~IsClientEnterDomain();
public:

	BOOL GetEnterType();
	BOOL IsEnterDomain();
	BOOL Is_Win2000_DomainController ();
	int GetGroupInfo(LPSTR strServerName, UINT *uType);
};

#endif // !defined(AFX_ISCLIENTENTERDOMAIN1_H__6A1F59DD_1CD1_4031_8678_7420D83F0105__INCLUDED_)

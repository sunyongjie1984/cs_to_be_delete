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
#include "StdString.h"   
#define JOIN_GROUP 1
#define JOIN_DOMAIN 2
#define NOT_JOIN 0



class CIsClientEnterDomain  
{

public:
	CIsClientEnterDomain();
	virtual ~CIsClientEnterDomain();
public:

	BOOL GetEnterType();
	BOOL IsEnterDomain();
	int Is_Win2000_DomainController (); // 0: 本地。1: 域服务器。-1: 错误
	int GetGroupInfo(LPSTR strServerName, UINT *uType);
};

#endif // !defined(AFX_ISCLIENTENTERDOMAIN1_H__6A1F59DD_1CD1_4031_8678_7420D83F0105__INCLUDED_)

// InitSock.h: interface for the CInitSock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INITSOCK_H__5D81BC3D_F78C_4A06_AC09_887999C11F38__INCLUDED_)
#define AFX_INITSOCK_H__5D81BC3D_F78C_4A06_AC09_887999C11F38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdlib.h>
#include <WinSock2.h>
#pragma comment(lib, "WS2_32")

class CInitSock  
{
public:
	CInitSock();
	virtual ~CInitSock();
};

#endif // !defined(AFX_INITSOCK_H__5D81BC3D_F78C_4A06_AC09_887999C11F38__INCLUDED_)

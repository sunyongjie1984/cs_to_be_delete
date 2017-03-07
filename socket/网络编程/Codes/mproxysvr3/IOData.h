// IOData.h: interface for the IOData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IODATA_H__85562453_FA38_4CE0_BF03_9467360D910D__INCLUDED_)
#define AFX_IODATA_H__85562453_FA38_4CE0_BF03_9467360D910D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const int DATA_BUFSIZE	= 8192; 

typedef struct TagLPWSAOVERLAPPEDEX
{
	WSAOVERLAPPED Overlapped; //重叠结构
	WSABUF     WSABuf;//socket数据缓冲
	char       Buffer[DATA_BUFSIZE];//wsaBuf指向的真实数据位置
	SOCKET	   hSocket;//socket 句柄
	SOCKET	   hSocketPair;//相关的socket句柄
	LPVOID     pProxy3;//指向代理对象
	TagLPWSAOVERLAPPEDEX *pPair;//指向相关socket的重叠扩展结构
}WSAOVERLAPPEDEX, *LPWSAOVERLAPPEDEX;//重叠扩展结构




#endif // !defined(AFX_IODATA_H__85562453_FA38_4CE0_BF03_9467360D910D__INCLUDED_)

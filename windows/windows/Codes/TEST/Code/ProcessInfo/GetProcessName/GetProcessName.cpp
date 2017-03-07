#define WIN32_LEAN_AND_MEAN
#define WINVER 0x0500
#include <windows.h>

//==========================日啊，好麻烦的结构啊，晕死他的BOOLEAN了，搞得不能对齐。==========
#pragma pack(push,8)

typedef struct _PEB_LDR_DATA
{

	ULONG               Length;
	BOOLEAN             Initialized;
	PVOID               SsHandle;
	LIST_ENTRY          InLoadOrderModuleList;
	LIST_ENTRY          InMemoryOrderModuleList;
	LIST_ENTRY          InInitializationOrderModuleList;

} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _UNICODE_STRING
{

	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;

} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _LDR_MODULE
{

	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
	PVOID BaseAddress;
	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG Flags;
	SHORT LoadCount;
	SHORT TlsIndex;
	LIST_ENTRY HashTableEntry;
	ULONG TimeDateStamp;

} LDR_MODULE, *PLDR_MODULE;


typedef struct RTL_DRIVE_LETTER_CURDIR
{

	USHORT              Flags;
	USHORT              Length;
	ULONG               TimeStamp;
	UNICODE_STRING      DosPath;

} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

typedef struct _RTL_USER_PROCESS_PARAMETERS
{

	ULONG               AllocationSize;
	ULONG               Size;
	ULONG               Flags;
	ULONG               DebugFlags;
	HANDLE              hConsole;
	ULONG               ProcessGroup;
	HANDLE              hStdInput;
	HANDLE              hStdOutput;
	HANDLE              hStdError;
	UNICODE_STRING      CurrentDirectoryName;
	HANDLE              CurrentDirectoryHandle;
	UNICODE_STRING      DllPath;
	UNICODE_STRING      ImagePathName;
	UNICODE_STRING      CommandLine;
	PWSTR               Environment;
	ULONG               dwX;
	ULONG               dwY;
	ULONG               dwXSize;
	ULONG               dwYSize;
	ULONG               dwXCountChars;
	ULONG               dwYCountChars;
	ULONG               dwFillAttribute;
	ULONG               dwFlags;
	ULONG               wShowWindow;
	UNICODE_STRING      WindowTitle;
	UNICODE_STRING      Desktop;
	UNICODE_STRING      ShellInfo;
	UNICODE_STRING      RuntimeInfo;
	RTL_DRIVE_LETTER_CURDIR DLCurrentDirectory[0x20];

} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

typedef VOID (_stdcall *PPEBLOCKROUTINE)(PVOID);

typedef struct _PEB_FREE_BLOCK
{

	struct _PEB_FREE_BLOCK* Next;
	ULONG Size;

} PEB_FREE_BLOCK, *PPEB_FREE_BLOCK;

struct PEB 
{
	
	BOOLEAN InheritedAddressSpace;
	BOOLEAN ReadImageFileExecOptions;
	BOOLEAN BeingDebugged;
	BOOLEAN Spare;
	HANDLE Mutant;
	PVOID ImageBaseAddress;
	PPEB_LDR_DATA LoaderData;
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
	PVOID SubSystemData;
	PVOID ProcessHeap;
	PVOID FastPebLock;
	PPEBLOCKROUTINE FastPebLockRoutine;
	PPEBLOCKROUTINE FastPebUnlockRoutine;
	ULONG EnvironmentUpdateCount;
	PVOID *KernelCallbackTable;
	PVOID EventLogSection;
	PVOID EventLog;
	PPEB_FREE_BLOCK FreeList;
	ULONG TlsExpansionCounter;
	PVOID TlsBitmap;
	ULONG TlsBitmapBits[0x2];
	PVOID ReadOnlySharedMemoryBase;
	PVOID ReadOnlySharedMemoryHeap;
	PVOID *ReadOnlyStaticServerData;
	PVOID AnsiCodePageData;
	PVOID OemCodePageData;
	PVOID UnicodeCaseTableData;
	ULONG NumberOfProcessors;
	ULONG NtGlobalFlag;
	BYTE Spare2[0x4];
	LARGE_INTEGER CriticalSectionTimeout;
	ULONG HeapSegmentReserve;
	ULONG HeapSegmentCommit;
	ULONG HeapDeCommitTotalFreeThreshold;
	ULONG HeapDeCommitFreeBlockThreshold;
	ULONG NumberOfHeaps;
	ULONG MaximumNumberOfHeaps;
	PVOID **ProcessHeaps;
	PVOID GdiSharedHandleTable;
	PVOID ProcessStarterHelper;
	PVOID GdiDCAttributeList;
	PVOID LoaderLock;
	ULONG OSMajorVersion;
	ULONG OSMinorVersion;
	ULONG OSBuildNumber;
	ULONG OSPlatformId;
	ULONG ImageSubSystem;
	ULONG ImageSubSystemMajorVersion;
	ULONG ImageSubSystemMinorVersion;
	ULONG GdiHandleBuffer[0x22];
	ULONG PostProcessInitRoutine;
	ULONG TlsExpansionBitmap;
	BYTE TlsExpansionBitmapBits[0x80];
	ULONG SessionId;
	
};

typedef struct _CLIENT_ID
{

	HANDLE UniqueProcess;
	HANDLE UniqueThread;

} CLIENT_ID, *PCLIENT_ID;

typedef struct _GDI_TEB_BATCH
{

	ULONG Offset;
	ULONG HDC;
	ULONG Buffer[0x136];

} GDI_TEB_BATCH, *PGDI_TEB_BATCH;

struct TEB
{

	NT_TIB Tib;                         /* 00h */
	PVOID EnvironmentPointer;           /* 1Ch */
	CLIENT_ID Cid;                      /* 20h */
	PVOID ActiveRpcInfo;                /* 28h */
	PVOID ThreadLocalStoragePointer;    /* 2Ch */
	PEB *Peb;                           /* 30h */
	ULONG LastErrorValue;               /* 34h */
	ULONG CountOfOwnedCriticalSections; /* 38h */
	PVOID CsrClientThread;              /* 3Ch */
	void* Win32ThreadInfo; /* 40h */
	ULONG Win32ClientInfo[0x1F];        /* 44h */
	PVOID WOW32Reserved;                /* C0h */
	LCID CurrentLocale;                 /* C4h */
	ULONG FpSoftwareStatusRegister;     /* C8h */
	PVOID SystemReserved1[0x36];        /* CCh */
	PVOID Spare1;                       /* 1A4h */
	LONG ExceptionCode;                 /* 1A8h */
	UCHAR SpareBytes1[0x28];            /* 1ACh */
	PVOID SystemReserved2[0xA];         /* 1D4h */
	GDI_TEB_BATCH GdiTebBatch;          /* 1FCh */
	ULONG gdiRgn;                       /* 6DCh */
	ULONG gdiPen;                       /* 6E0h */
	ULONG gdiBrush;                     /* 6E4h */
	CLIENT_ID RealClientId;             /* 6E8h */
	PVOID GdiCachedProcessHandle;       /* 6F0h */
	ULONG GdiClientPID;                 /* 6F4h */
	ULONG GdiClientTID;                 /* 6F8h */
	PVOID GdiThreadLocaleInfo;          /* 6FCh */
	PVOID UserReserved[5];              /* 700h */
	PVOID glDispatchTable[0x118];       /* 714h */
	ULONG glReserved1[0x1A];            /* B74h */
	PVOID glReserved2;                  /* BDCh */
	PVOID glSectionInfo;                /* BE0h */
	PVOID glSection;                    /* BE4h */
	PVOID glTable;                      /* BE8h */
	PVOID glCurrentRC;                  /* BECh */
	PVOID glContext;                    /* BF0h */
	LONG LastStatusValue;           /* BF4h */
	UNICODE_STRING StaticUnicodeString; /* BF8h */
	WCHAR StaticUnicodeBuffer[0x105];   /* C00h */
	PVOID DeallocationStack;            /* E0Ch */
	PVOID TlsSlots[0x40];               /* E10h */
	LIST_ENTRY TlsLinks;                /* F10h */
	PVOID Vdm;                          /* F18h */
	PVOID ReservedForNtRpc;             /* F1Ch */
	PVOID DbgSsReserved[0x2];           /* F20h */
	ULONG HardErrorDisabled;            /* F28h */
	PVOID Instrumentation[0x10];        /* F2Ch */
	PVOID WinSockData;                  /* F6Ch */
	ULONG GdiBatchCount;                /* F70h */
	USHORT Spare2;                      /* F74h */
	BOOLEAN IsFiber;                    /* F76h */
	UCHAR Spare3;                       /* F77h */
	ULONG Spare4;                       /* F78h */
	ULONG Spare5;                       /* F7Ch */
	PVOID ReservedForOle;               /* F80h */
	ULONG WaitingOnLoaderLock;          /* F84h */
	ULONG Unknown[11];                  /* F88h */
	PVOID FlsSlots;                     /* FB4h */
	PVOID WineDebugInfo;                /* Needed for WINE DLL's  */
	
};

#pragma pack(pop)

#pragma comment(linker,"/merge:.rdata=.data")
#pragma comment(linker,"/merge:.text=.data")



inline bool mystrcmp ( const char * src, const char * dst )
{
	int ret = 0;
	
	while( !( ret = *(unsigned char*)src - *(unsigned char*)dst ) && *dst )
	{
		++src, ++dst;
	}

	return ret == 0;
}

unsigned int GetFunctionByName(unsigned int ImageBase,const char*FuncName)
{
	IMAGE_DOS_HEADER	*pdoshdr = (IMAGE_DOS_HEADER *)ImageBase;

	PIMAGE_NT_HEADERS32 pnthdr	 = (PIMAGE_NT_HEADERS32)(ImageBase+pdoshdr->e_lfanew);

	if( pnthdr->Signature != IMAGE_NT_SIGNATURE )
	{
		return 0;
	}
	
	PIMAGE_DATA_DIRECTORY	pidd = &pnthdr->OptionalHeader.DataDirectory[0];

	IMAGE_EXPORT_DIRECTORY *pied = (IMAGE_EXPORT_DIRECTORY*)(ImageBase+pidd->VirtualAddress);

	LONG *pfuncnames = (LONG *)(ImageBase+pied->AddressOfNames);

	for( unsigned int i = 0; i < pied->NumberOfNames; i++ )
	{
		PSTR pfunc = (PSTR)(ImageBase+pfuncnames[i]);

		if( mystrcmp( pfunc, FuncName ) )
		{
			WORD *EOT = (WORD *)(pied->AddressOfNameOrdinals+ImageBase);

			LONG *EAT = (LONG *)(pied->AddressOfFunctions+ImageBase);

			int index = EOT[i];
			
			return (ImageBase+EAT[index]);   
		}
	}
	return 0;
}

typedef HMODULE (WINAPI *TLoadLibraryA)( LPCSTR		lpFileName );
typedef BOOL	(WINAPI *TFreeLibrary) ( HMODULE	hModule );
typedef void	(WINAPI *TExitProcess) ( UINT		uExitCode );
typedef int		(WINAPI *TMessageBox)  ( HWND		hWnd,
										 LPCSTR		lpText,
										 LPCSTR		lpCaption,
										 UINT		uType );


extern "C" int APIENTRY  WinMain( HINSTANCE		hInstance,
								  HINSTANCE		hPrevInstance,
								  LPSTR			lpCmdLine,
								  int			nCmdShow )
{
	unsigned int kernel32imagebase,user32imagebase;

	char title[] = "ddd&&*U( sunwang need beauty %^%&*";

	char caption[] = "hack";

	char user32[] = "user32";

	TEB *pteb = NULL;

	__asm mov eax,fs:[18h]
		
	__asm mov pteb,eax

	PEB *ppeb = pteb->Peb;

	PPEB_LDR_DATA pldr = ppeb->LoaderData;

	PLDR_MODULE	  pmodule		  = (PLDR_MODULE)pldr->InLoadOrderModuleList.Flink;

	PLDR_MODULE	  pntdllmodule	  = (PLDR_MODULE)pmodule->InLoadOrderModuleList.Flink;

	PLDR_MODULE   pkernel32module = (PLDR_MODULE)pntdllmodule->InLoadOrderModuleList.Flink;

	kernel32imagebase			  = (unsigned int)pkernel32module->BaseAddress;

	TLoadLibraryA pLoadLibraryA   = (TLoadLibraryA)GetFunctionByName(kernel32imagebase,"LoadLibraryA");

	TFreeLibrary  pFreeLibrary    = (TFreeLibrary)GetFunctionByName(kernel32imagebase,"FreeLibrary");

	TExitProcess  pExitProcess    = (TExitProcess)GetFunctionByName(kernel32imagebase,"ExitProcess");

	user32imagebase = (unsigned int)pLoadLibraryA(user32);
	
	TMessageBox pMessageBox = (TMessageBox)GetFunctionByName(user32imagebase,"MessageBoxA");
	
	pMessageBox( NULL, title, caption, MB_OK );

	pFreeLibrary( (HMODULE)user32imagebase );

	pExitProcess(0);

	return 0;
}
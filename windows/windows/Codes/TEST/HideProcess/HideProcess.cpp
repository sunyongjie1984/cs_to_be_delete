#include "windows.h"
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		DWORD dwVersion = GetVersion();
		if (dwVersion >= 0x80000000)
		{
			int (CALLBACK *rsp)(DWORD,DWORD);

			HINSTANCE dll=LoadLibrary("KERNEL32.DLL");

			rsp=(int(CALLBACK*)(DWORD,DWORD))GetProcAddress(dll,"RegisterServiceProcess");

			rsp(NULL,1);
			FreeLibrary(dll);
		}
	}
	catch (/*Exception &exception*/...)
	{
	}
	return 0;
}
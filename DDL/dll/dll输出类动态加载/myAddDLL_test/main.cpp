#include "myAddDLL.h"
#include "windows.h"
#include "stdio.h"

typedef void (__stdcall * PCTOR) (); // 这里是定义类型
typedef void (__stdcall * pPrint) ();


//void  (__stdcall *PCTOR) ();           // 这里是定义指针
//void  (__stdcall *pPrint) ();


//typedef int iiiii ;
//iiiii a = 0;

int main()
{
	HMODULE hmodule = LoadLibrary("myAddDLL.dll");
	if (NULL == hmodule)
	{
		printf ("LoadLibrary failed\n");
		return 1;
	}
	// 1. 

	// 2. Obtain a block of memory equal to the class layout
	CBook *pCBook = (CBook *) malloc (sizeof (CBook));	
	if (NULL == pCBook)
	{
		printf ("memory allocation failed\n");
		return 1;
	}
	// 2. 

	// 3. Get the address of the ctor
	PCTOR pCtor = (PCTOR) GetProcAddress (hmodule, "CBook");
	if (NULL == pCtor)
	{
		printf ("GetProcAddress Ctor failed\n");
		return 1;
	}

	pPrint a = (pPrint) GetProcAddress (hmodule, "print");
	if (NULL == pCtor)
	{
		printf ("GetProcAddress Ctor failed\n");
		return 1;
	}
	//pCBook->print();
	//pCtor();
	a();
	FreeLibrary(hmodule);
	return 0;
}
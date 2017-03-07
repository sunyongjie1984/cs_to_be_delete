// UserOfCalc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "Calc.h"

typedef int    (WINAPI * PADD)  (int, int);
typedef int    (WINAPI * PSUB)  (int, int);
typedef void   (WINAPI * PCTOR) ();
typedef TCHAR* (WINAPI * PGETLASTUSEDFUNC) ();

int main ()
{
	// 1. Load the library
	HMODULE hMod = LoadLibrary ("Calc.dll");
	if (NULL == hMod)
	{
		printf ("LoadLibrary failed\n");
		return 1;
	}
	// 1. 

	// 2. Obtain a block of memory equal to the class layout
	CCalc *pCCalc = (CCalc *) malloc (sizeof (CCalc));	
	if (NULL == pCCalc)
	{
		printf ("memory allocation failed\n");
		return 1;
	}
	// 2. 

	// 3. Get the address of the ctor
	PCTOR pCtor = (PCTOR) GetProcAddress (hMod, "CCalc");
	if (NULL == pCtor)
	{
		printf ("GetProcAddress Ctor failed\n");
		return 1;
	}
	// 3. 

	// 4. Move the ptr to the block of memory to ECX 
	//    and call the constructor. 
	__asm { MOV ECX, pCCalc }	
	pCtor ();
	// 4. 

	// 5. Similarly do this for all the other member functions
	PGETLASTUSEDFUNC pGetLastUsedFunc = 
		(PGETLASTUSEDFUNC) GetProcAddress (hMod, "GetLastUsedFunc");
	if (NULL == pGetLastUsedFunc)
	{
		printf ("GetProcAddress GetLastUsedFunc failed\n");
		return 1;
	}

	__asm { MOV ECX, pCCalc }
	printf ("Last used func in Calc.DLL is: %s\n", pGetLastUsedFunc ());


	PADD pAdd = (PADD) GetProcAddress (hMod, "Add");
	if (NULL == pAdd)
	{
		printf ("GetProcAddress Add failed\n");
		return 1;
	}

	__asm { MOV ECX, pCCalc }	
	int i = pAdd (15, 10);
	
	printf ("i = %d\n", i);

	__asm { MOV ECX, pCCalc }
	printf ("Last used func in Calc.DLL is: %s\n", pGetLastUsedFunc ());

	PSUB pSub = (PSUB) GetProcAddress (hMod, "Sub");
	if (NULL == pSub)
	{
		printf ("GetProcAddress Sub failed\n");
		return 1;
	}
	
	__asm { MOV ECX, pCCalc }	
	i = pSub (15, 10);
	
	printf ("i = %d\n", i);

	__asm { MOV ECX, pCCalc }
	printf ("Last used func in Calc.DLL is: %s\n", pGetLastUsedFunc ());
	// 5. 
	
	FreeLibrary (hMod);

	return 0;
}


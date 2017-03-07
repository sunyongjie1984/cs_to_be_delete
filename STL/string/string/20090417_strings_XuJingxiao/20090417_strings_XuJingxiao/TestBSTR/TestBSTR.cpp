// TestBSTR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <wtypes.h> // BSTR
#include <oleauto.h> // BSTR APIs

#include <tchar.h> // _T

#include <conio.h>

//////////////////////////////////////////////////////////////////////////
void OutputByBytes( BSTR bstrString );

void TestBSTR();

void TestBSTRAllocFree();

void TestBSTRReallocFree();

//////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    //
    ::printf("\nTest BSTR!\n");
    TestBSTR();

    // 
    ::printf("\nPress any key to continue!\n");
    _getch();
    ::printf("\nTestBSTR Alloc and Free!\n");
    TestBSTRAllocFree();

    //
    ::printf("\nPress any key to continue!\n");
    _getch();
    ::printf("\nTestBSTR Realloc and Free");
    TestBSTRReallocFree();

    ::printf("\nPress any key to exit!\n");
    _getch();
	return 0;
}

//////////////////////////////////////////////////////////////////////////
void OutputByBytes( BSTR bstrString )
{
    ::wprintf(L"\n********** Enter OutputByBytes **********");
    UINT unBSTRStrLen = ::SysStringLen(bstrString);
    ::wprintf(L"\nSysStringLen() = %u", unBSTRStrLen);

    UINT unBSTRByteCount = ::SysStringByteLen(bstrString);
    ::wprintf(L"\nSysStringByteLen() = %u", unBSTRByteCount);

    BYTE* pByte = reinterpret_cast<BYTE*>(bstrString);
    for (UINT unByteIndex = 0u; unByteIndex < unBSTRByteCount; unByteIndex++)
    {
        ::wprintf(L"\nASCII-->Char: 0X%02X-->[%c]", pByte[unByteIndex], pByte[unByteIndex]);
    }
    ::wprintf(L"\n********** Exit OutputByBytes **********");
}

//////////////////////////////////////////////////////////////////////////
void TestBSTR()
{
    BSTR bstrString = NULL;
    bstrString = L"OK, I am a \0 BSTR!\n";
    
    OutputByBytes(bstrString); // 1, Result of this API, why?:
}

//////////////////////////////////////////////////////////////////////////
void TestBSTRAllocFree()
{
    BSTR bstrString = NULL;
    bstrString = ::SysAllocString(_T("0123456789\0ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
    OutputByBytes(bstrString); // 2, Result of this API, why?:
    ::SysFreeString(bstrString);
    bstrString = NULL;

    bstrString = ::SysAllocStringLen(_T("0123456789\0abcdefghijklmnopqrstuvwxyz"), 10 + 1 + 26 + 1);
    OutputByBytes(bstrString); // 3, Result of this API, why?:
    ::SysFreeString(bstrString);
    bstrString = NULL;

    bstrString = ::SysAllocStringByteLen("0123456789\0ABCDEFGHIJKLMNOPQRSTUVWXYZ", 10 + 1+ 26 + 1);
    OutputByBytes(bstrString); // 4, Result of this API, why?: Very strange here.
    ::SysFreeString(bstrString);
    bstrString = NULL;
}

//////////////////////////////////////////////////////////////////////////
void TestBSTRReallocFree()
{
    BSTR bstrString = NULL;

    bstrString = ::SysAllocString(_T("0123456789\0ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
    OutputByBytes(bstrString);

    ::SysReAllocString(&bstrString, _T("0123456789\0abcdefghijklmnopqrstuvwxyz"));
    OutputByBytes(bstrString); // 5, Result of this API, why?:

    ::SysReAllocStringLen(&bstrString, _T("0123456789\0ABCDEFGHIJKLMNOPQRSTUVWXYZ"), 10 + 1 + 26 + 1);
    OutputByBytes(bstrString); // 6, Result of this API, why?:

    ::SysFreeString(bstrString); // 7, Why this line only occurs once?
    bstrString = NULL;
}
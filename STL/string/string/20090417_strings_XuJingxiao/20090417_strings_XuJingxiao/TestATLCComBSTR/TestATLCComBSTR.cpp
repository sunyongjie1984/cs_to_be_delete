// TestATLCComBSTR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <tchar.h>
#include <conio.h>
#include <atlbase.h>

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

void FromBSTRToCComBSTR();
void TestCComBSTRConstructor();
void TestBSTR_CComBSTR();

//////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    ::printf("\nPress any key to continue!\n");
    _getch();
    FromBSTRToCComBSTR();

    ::printf("\nPress any key to continue!\n");
    _getch();
    TestCComBSTRConstructor();

    ::printf("\nPress any key to continue!\n");
    _getch();

    printf("\nHello World!\n");
	return 0;
}

//////////////////////////////////////////////////////////////////////////
void FromBSTRToCComBSTR()
{
    BSTR bstr = ::SysAllocString(L"Hello BSTR!\n");
    
    CComBSTR bstrCom;
    bstrCom.Attach(bstr);

    unsigned int unLenCom = bstrCom.Length();
    UINT unLen = ::SysStringLen(bstr);

    printf("\nCComBSTR's length is %u", unLenCom);
    printf("\nBSTR's length is %u", unLen);
    ::_tprintf(_T("\nm_str = 0x%08x"), bstrCom.m_str); // 1, Result:
    
    // 1, Do we need free the BSTR here? Why?
}

void TestCComBSTRConstructor()
{
    ::_tprintf(_T("\nI am bstrCom"));
    CComBSTR bstrCom;
    ::_tprintf(_T("\nm_str = 0x%08x"), bstrCom.m_str); // 1, Result:
    OutputByBytes(bstrCom.operator BSTR());

    ::_tprintf(_T("\nI am bstrComNull\n"));
    CComBSTR bstrComNull(NULL);
    ::_tprintf(_T("\nm_str = 0x%08x\n"), bstrComNull.m_str); //2, Result:
    OutputByBytes(bstrComNull.operator BSTR());
    
    ::_tprintf(_T("\nI am bstrCom1\n"));
    CComBSTR bstrCom1(10);
    ::_tprintf(_T("\nm_str = 0x%08x"), bstrCom1.m_str); // 3, Result:
    OutputByBytes(bstrCom1.operator BSTR());

    ::_tprintf(_T("\nI am bstrCom2Unicode\n"));
    CComBSTR bstrCom2Unicode(12, L"0123456789\0ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    ::_tprintf(_T("\nm_str = 0x%08x"), bstrCom2Unicode.m_str); // 4, Result:
    OutputByBytes(bstrCom2Unicode.operator BSTR());
    
    ::_tprintf(_T("\nI am bstrCom2ANSI\n"));
    CComBSTR bstrCom2ANSI(12, "0123456789\0ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    ::_tprintf(_T("\nm_str = 0x%08x"), bstrCom2ANSI.m_str); // 5, Result:
    OutputByBytes(bstrCom2ANSI.operator BSTR());
    
    ::_tprintf(_T("\nI am bstrCom3\n"));
    CComBSTR bstrCom3("0123456789\0ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    ::_tprintf(_T("\nm_str = 0x%08x"), bstrCom3.m_str); // 6, Result:
    OutputByBytes(bstrCom3.operator BSTR());
    
    ::_tprintf(_T("\nI am bstrCom4\n"));
    CComBSTR bstrCom4(bstrCom2Unicode);
    ::_tprintf(_T("\nm_str = 0x%08x"), bstrCom4.m_str); // 7, Result:
    OutputByBytes(bstrCom4.operator BSTR());
    

    ::_tprintf(_T("\nI am bstrCom5\n"));
    // Microsoft Development Environemnt
    // {B2104A32-2AE8-11D1-8EC0-00A0C90F26EA}
    GUID guid;
    guid.Data1 = 0xB2104A32;
    guid.Data2 = 0x2AE8;
    guid.Data3 = 0x11D1;
    guid.Data4[0] = 0x8E;
    guid.Data4[1] = 0xC0;
    guid.Data4[2] = 0x00;
    guid.Data4[3] = 0xA0;
    guid.Data4[5] = 0xC9;
    guid.Data4[6] = 0x0F;
    guid.Data4[7] = 0x26;
    guid.Data4[8] = 0xEA;
    CComBSTR bstrCom5(guid);
    ::_tprintf(_T("\nm_str = 0x%08x"), bstrCom5.m_str); // 8, Result:
    OutputByBytes(bstrCom5.operator BSTR());
    
}

void TestBSTR_CComBSTR()
{
    // Operator
    CComBSTR bstrCom;

    bstrCom.operator BSTR();
    bstrCom.operator&();
    bstrCom.Detach();
    bstrCom.m_str;
    bstrCom.Copy();

}
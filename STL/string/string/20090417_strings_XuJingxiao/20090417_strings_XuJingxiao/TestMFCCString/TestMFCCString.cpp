// TestMFCCString.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include "TestMFCCString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

// Declaration
void OutputByBytes( BSTR bstrString );
void OutputByBytes( const CString& csString );

void TestOperator();
void TestBSTRConversion();
void TestConstruction();
void TestCStringArray();

// Entry-point
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
        // operator LPCTSTR()
        TestOperator();

        // CString-->BSTR
        ::_tprintf(_T("\nPress any key to continue!\n"));
        ::_getch();
        TestBSTRConversion();

        // CString Construction
        ::_tprintf(_T("\nPress any key to continue!\n"));
        ::_getch();
        TestConstruction();

        // CStringArray
        ::_tprintf(_T("\nPress any key to continue!\n"));
        ::_getch();
        TestCStringArray();
	}

    cout << endl;

    ::_tprintf(_T("\nPress any key to exit!\n"));
    ::_getch();
	return nRetCode;
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

void OutputByBytes( const CString& csString )
{
    ::wprintf(L"\n********** Enter OutputByBytes **********");
    const BYTE* pByte = reinterpret_cast<const BYTE*>(csString.operator LPCTSTR());
    int nBufLen = (csString.GetLength() + 1)*sizeof(TCHAR);
    for (int i = 0; i < nBufLen; i++)
    {
        ::wprintf(L"\nASCII-->Char: 0X%02X-->[%c]", pByte[i], pByte[i]);
    }
    
    ::wprintf(L"\n********** Exit OutputByBytes **********");
}

void OutputArray(const CStringArray& csaArray)
{
    ::wprintf(L"\n********** Enter OutputArray **********");
    int nArraySize = csaArray.GetSize();
    ::wprintf(L"\nThe array have [%d] elements.", nArraySize);
    for (int i = 0; i < nArraySize; i++)
    {
        ::_tprintf(_T("\nElement[%02d] = [%s]"), i, csaArray[i].operator LPCTSTR());
    }

    ::wprintf(L"\n********** Exit OutputArray **********");
}
//////////////////////////////////////////////////////////////////////////
void TestOperator()
{
    CString csHello;
    csHello.LoadString(IDS_HELLO);
    ::_tprintf( csHello.operator LPCTSTR()) ; // 1, Why these two lines have same result?
    cout << endl;
    ::_tprintf( csHello );     // 1, 
    cout << endl;
}

void TestBSTRConversion()
{
    CString csBSTR(_T("I will become a BSTR!"));
    BSTR bstrString = csBSTR.AllocSysString();
    OutputByBytes( bstrString ); // 2, Write the result(Unicode/non-Unicode):
    
    CString csBSTR2(_T("I am another BSTR!"));
    csBSTR2.SetSysString(&bstrString);
    OutputByBytes( bstrString ); // 3, Write the result(Unicode/non-Unicode):
    
    ::SysFreeString(bstrString);  // Free one time!
    bstrString = NULL;
}

void TestConstruction()
{
    CString csConstructorNull;

    CString csConstructorANSI("I am ANSI string!");
    OutputByBytes(csConstructorANSI); // 4, Write the result(Unicode/non-Unicode):

    CString csConstructorUnicode(L"I am Unicode string!");
    OutputByBytes(csConstructorUnicode); // 5, Write the result(Unicode/non-Unicode):

    unsigned char pString[] = "I am unsigned char array";
    CString csConstructorUnsignedChar(pString);
    OutputByBytes(csConstructorUnsignedChar); // 6, Write the result(Unicode/non-Unicode):
}

void TestCStringArray()
{
    CStringArray csaArrayA;
    CStringArray csaArrayU;

    for (int i = 0; i < 10; i++)
    {
        CString csElementA('A', i);
        CString csElementU(L'U', i);
        
        csaArrayA.Add(csElementA);
        csaArrayU.Add(csElementU);
    }

    OutputArray(csaArrayA); // 7, Write the result
    OutputArray(csaArrayU); // 8, Write the result

    csaArrayA.SetSize(5);
    OutputArray(csaArrayA); // 9, Write the result

    csaArrayA.Copy(csaArrayU);
    OutputArray(csaArrayA); // 10, Write the result

    csaArrayA.SetSize(15);
    OutputArray(csaArrayA); // 11, Write the result

    csaArrayA.RemoveAt(3, 2);
    OutputArray(csaArrayA); // 12, Write the result

    csaArrayA.FreeExtra();
    OutputArray(csaArrayA); // 13, Write the result

    csaArrayA.Append(csaArrayU);
    OutputArray(csaArrayA); // 14, Write the result
}
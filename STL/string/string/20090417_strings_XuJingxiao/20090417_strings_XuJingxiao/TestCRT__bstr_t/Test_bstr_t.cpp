// Test_bstr_t.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <comutil.h>

int main(int argc, char* argv[])
{
    //////////////////////////////////////////////////////////////////////////
    // 1, Why both normal and wide print function could work?
    _bstr_t bstr("It should be stop here!");
    unsigned int unStopPos1 = bstr.length();
    unsigned int unCurLen = 0;
    printf(bstr);
    printf("\n");
    wprintf(bstr);
    wprintf(L"\n");
    unCurLen = bstr.length();
    printf("\nCurrent _bstr_t string's length is : %u \n", unCurLen);

    // Append a normal string
    bstr += "I am norm string!";
    unsigned int unStopPos2 = bstr.length();
    printf(bstr);
    printf("\n");
    wprintf(bstr);
    wprintf(L"\n");
    unCurLen = bstr.length();
    printf("\nCurrent _bstr_t string's length is : %u \n", unCurLen);


    // Append a wide string
    bstr += L"I am wide string!";
    printf(bstr);
    printf("\n");
    wprintf(bstr);
    wprintf(L"\n");
    unCurLen = bstr.length();
    printf("\nCurrent _bstr_t string's length is : %u \n", unCurLen);

    //////////////////////////////////////////////////////////////////////////
    printf("\nAfter Modification!\n");

    char* pData = bstr.operator char*();
    pData[unStopPos2] = '\0'; // Modify and insert a NULL terminator for normal string!
    printf(bstr); // 2, Write result:
    printf("\n");
    wprintf(bstr); // 3, Write result:
    wprintf(L"\n");

    wchar_t* pWData = bstr.operator wchar_t*();
    pWData[unStopPos1] = L'\0'; // Modify and insert a NULL terminator for normal string!
    printf(bstr); // 4, Write result:
    printf("\n");
    wprintf(bstr); // 5, Write result:
    wprintf(L"\n");

    // 6, What is the length of bstr string?
    unCurLen = bstr.length();
    printf("\nCurrent _bstr_t string's length is : %u \n", unCurLen);

    {
        // Print the characters one by one by wchar_t*
        wprintf(L"\nPrint the characters one by one by wchar_t* is:\n");
        for (unsigned int i = 0; i < unCurLen; i++)
        {
            ::wprintf(L"%c", bstr.operator const wchar_t*()[i]);
        } // 7, Write result:
        wprintf(L"\n");
        
        wprintf(bstr);
        wprintf(L"\n");
    }

    {
        // Print the characters one by one by char*
        printf("\nPrint the characters one by one by char* is:\n");
        for (unsigned int j = 0; j < unCurLen; j++)
        {
            ::printf("%c", bstr.operator const char*()[j]);
        } // 8, Write result:
        printf("\n");
        
        printf(bstr);
        printf("\n");
    }

	return 0;
}


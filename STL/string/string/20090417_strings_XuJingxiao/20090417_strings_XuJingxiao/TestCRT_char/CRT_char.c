
#include <string.h>
#include <stdio.h>

void main()
{
    char c = 97;
    wchar_t wc = 65;

    char szC[] = "This is Norm string!";
    wchar_t szWC[] = L"This is Wide string!";

    unsigned int i = 0;
    char* pFlag = 0;
    //////////////////////////////////////////////////////////////////////////
    // 1, Result:
    printf("\nsizeof(char) = %d bytes", sizeof(char));
    printf("\nsizeof(wchar_t) = %d bytes", sizeof(wchar_t));

    printf("\nc = %c", c);
    wprintf(L"\nwc = %c", wc);

    //////////////////////////////////////////////////////////////////////////
    // 
    printf("\nszC = %s, length is %u, size is %u bytes", szC, strlen(szC), sizeof(szC)); // 2, Result:
    wprintf(L"\nszC = %s, length is %u, size is %u bytes", szC, wcslen(szC), sizeof(szC));  // 3, Does it compile OK?
    printf("\n");
    pFlag = szC;
    for (i = 0; i < sizeof(szC); i++) // 4, Output every byte of the string.
    {
        printf("%u: 0x%2x\n", i, pFlag[i]);
    }

    //////////////////////////////////////////////////////////////////////////
    printf("\nszWC = %s, length is %u, size is %u bytes", szWC, strlen(szWC), sizeof(szWC));  // 5, Does it compile OK?
    wprintf(L"\nszWC = %s, length is %u, size is %u bytes", szWC, wcslen(szWC), sizeof(szWC)); // 6, Result:
    printf("\n");
    pFlag = (char*)(szWC); // Cast here
    for (i = 0; i < sizeof(szWC); i++) // 7, Output every byte of the string.
    {
        wprintf(L"%u:0x%x\n", i, pFlag[i]);
    }

    //////////////////////////////////////////////////////////////////////////
    printf("\n");

    return;
}
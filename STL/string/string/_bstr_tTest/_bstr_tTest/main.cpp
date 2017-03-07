#include <comutil.h>
#include <iostream>
int main()
{
    BSTR a = L"hello BSTR"; // wrong
    _bstr_t b = a;
    BSTR c = SysAllocString(L"hello BSTR");
    std::cout << a << '\n' << b 
        << '\n' << c << std::endl;
    return 0;
}
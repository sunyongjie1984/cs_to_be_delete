#include <atlstr.h>
#include <comutil.h>
int main()
{
    CString csTemp = "I Love China";
    _bstr_t a = _bstr_t(csTemp);
    return 0;
}
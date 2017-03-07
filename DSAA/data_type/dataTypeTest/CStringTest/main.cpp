#include <atlstr.h>
#include <iostream>
#include <string>
int main()
{   
    CString cs = L"I Love China";
    // CString是不以这么输出的，调试可以看到赋值是成功的。如果想测试应该
    // 在MFC的对话框中调试。
    std::cout << cs << std::endl;
    std::string s = "I Love China";
    std::cout << s << std::endl;
    return 0;
}
#include "CArray.h"
int main()
{
    CArray<std::string> strArray; // 12个空字符串
    CArray<int> intArray;         // 12个0

    std::cout << strArray << std::endl;
    std::cout << intArray << std::endl;

    int intArr[3] = { 2, 8, 4 };
    CArray<int> intArray2(intArr, 3);
    std::cout << intArray2 << std::endl;

    std::string str[3] = { "I love China", "I love American", "I love japan"};
    CArray<std::string> strArray2(str, 3);
    std::cout << strArray2 << std::endl;

    CArray<char> ca;
    std::cout << ca << std::endl; // 12个空字符 // 不知道为什么，如果把屏暮的字调大成150%，
                                  // 那么控制台就会将空字符打印成小写字母a
								  // 这件事害我重装了一次系统也没有找出来

    return 0;
}
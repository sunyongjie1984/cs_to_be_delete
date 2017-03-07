#include <iostream>
int main()
{
    int i = 20;
    // 不初始化
    int* p = new int[i]; // 动态分配的数组不需要数组名与确定的数组长度。
    // 初始化为0
//    int* p = new int[i](); // 动态分配的数组不需要数组名与确定的数组长度。
    //　错误
//    int* p = new int[i](); // 动态分配的数组不需要数组名与确定的数组长度。
    for (int j = 0; j != 10; j++)
    {
        std::cout << *(p + j) << std::endl;
    }
    return 0;
}
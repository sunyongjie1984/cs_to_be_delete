#include <iostream>
using namespace std;
int main()
{
    int i;
    std::cout << 20;
    std::cin >> i; // 自动刷新缓冲区
    std::cout << i << std::endl;

    std::cout << '\?' << std::endl; // 问号
    std::cout << '\b' << std::endl; // 退格符，不可显示字符
    return 0;
}
#include <iostream>
// const对象默认为文件局部对象
extern unsigned int const AA;
int main()
{
    std::cout << AA << std::endl;
    return 0;
}
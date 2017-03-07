#include <iostream>
#include <string>
// 编译器真是相当友好啊warning C4172: returning address of local
// variable or temporary 一定不要返回局部变量啊

char* GetMemory(void)
{
    char p[] = "hello world";
    return p; // 这里是返回local的address
}

int get_int(void)
{
    int i = 3;
    return i; // 这是返回local的值，与上面是两回事，上面是说返回之后，用到这个地址返回值
}             // 要用GetMemory这个函数里面的已经析构了的数据  
              // 而下面就涉及到get_int这个函数里面的local变量，因为别人只用这个int值
int main()
{
    char *str = NULL;
    //	std::cout << *str; //不可以这样输出0么？
    str = GetMemory();
    printf(str);
    std::cout << std::endl;

    std::cout << get_int() << std::endl;
    return 0;
}

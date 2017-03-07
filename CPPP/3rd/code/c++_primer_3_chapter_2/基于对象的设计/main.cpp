#include "CIntArray.h"
#include <iostream>
int main()
{
    CIntArray arr(10);     // 初始化 默认构造函数
    CIntArray arr1;        // 初始化 默认构造函数
    //CIntArray array2();
    CIntArray arr3(arr);   // 初始化 拷贝构造函数

    for (int i = 0; i !=10; i++)
    {
        // std::cout << arr[20] << std::endl; // assert 失败
        std::cout << arr[i] << std::endl;
    }

    std::cout << arr << std::endl;
    std::cout << arr1 << std::endl;
    //std::cout << arr2 << std::endl;
    std::cout << arr3 << std::endl;

    int a[3] = { 2, 7, 4};
    CIntArray a1(a, 3);     // 初始化 构造函数2
    CIntArray a2 = a1;      // 初始化 拷贝构造函数
    CIntArray a3;
    //a3 = a1;              // 赋值操作 不是初始化 调用重载的赋值操作符，在没有定义重载的赋值操作符时，编译器会为我们合成一个，
                            // 但是这个类具有指针成员，编译器为我们合成的操作符只是将对应指针指向同一位置，并没有new新的空间给我
                            // 这种作法是非常错误的。之后我在类的定义体中声明了赋值操作符，后这里就编译通不过了，这是一种方法，
                            // 类的设计者，通过这种方法可以限制用户使用赋值操作，拷贝构造函数也可以这样做。
    std::cout << a1 << std::endl;
    std::cout << a2 << std::endl;
    std::cout << a3 << std::endl;

	a1[2] = 200;
	std::cout << a1 << std::endl;
    return 0;
}
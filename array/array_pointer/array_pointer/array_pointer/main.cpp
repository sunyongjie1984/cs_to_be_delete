#ifdef SUNYJ_UNIXLIKE
#include <stdio.h>
#endif

#include <iostream>
int main()
{
    // 简练定义       必要解释
    int a = 0;              // 定义一个整型变量a。

    int* b = NULL;             // 定义一个指针b，b指向一个整形变量。
    // 下面的可以写成 int* *a;这种形式么，我试一下子^_^
    int** c = NULL;            // 定义一个指针c，c指向的一个指针，指向整形变量的指针。

    int d[10] = {0};          // 定义一个数组d，d中含有10个整形变量。

    int* e[10] = {0};         // 定义一个指针数组e，e有10个指针元素，每个元素指向一个整形数。

    // 类型 小括号 中括号 指向数组的指针
    int (*f)[5] = NULL;        // 定义一个指针f，f指向一个数组，此数组含有5个整形变量。

    // 类型 小括号 小括号 指向函数的指针
    int (*g)(int) = NULL;      // 定义一个指针g，g指向一个函数，此函数接受一个整型实参，返回一个整形值。

    // 设x等于第一个小括号中的内容，x与int* e[10]相同，x为一个指针数组，则
    // int (*h[10])(int) = int (x)(int) 与 int(*g)(int)相同
    int (*h[10])(int) = {0};  // 定义一个指针数组h，h有10个指针元素，每个元素指向一个函数，每个函数接受一个整形实参，返回一个整型值。
    
    // 10 pointers 10 x 8 = 80
    std::cout << " sizeof(e): = " << " " << sizeof(e) << std::endl;
    // 1 pointers 10 x 8 = 80
    std::cout << " sizeof(f): = " << " " << sizeof(f) << std::endl;

    int arr[5] = { 0, 1, 2, 3, 4 };
    int (*pp)[5] = &arr; // pp指向一个含有5个整数的整形数

    std::cout << (long)pp << std::endl;
    pp++; // pp += sizeof(pp)也就是5 x 4 = 20
    std::cout << (long)pp << std::endl;

    // 引入了一个关于输出流的问题，不明白了，就是下面的这个语句
    int k = 1;

    // the right "k++" first calculate, but the out put operation of "k++" if after "k"
    std::cout << k << " " << k++  << std::endl;

    std::cout << k << " " << ++k << std::endl;

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;
    std::cout << f << std::endl;
    std::cout << g << std::endl;
    std::cout << h << std::endl;

    getchar();
    return 0;
}

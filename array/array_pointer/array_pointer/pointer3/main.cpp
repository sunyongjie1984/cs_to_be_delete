#include <iostream>
int main()
{
    int test[2][3] = { {1, 2, 3}, { 4, 5, 6 } };
    //	int (*p)[4]; // 这里必须是3，任何其它的数都不行，
    // 这里是不是说，p是一个指针，它指向一个数组，这个数
    int (*p)[3]; // 组有3个整形元素，必须是严格按照类型匹配的。@.@	             
    p = &test[1];
    // 无论怎么，数组都不能够直接输出来。
    // 可以清楚看出，每个人四个字节。
    std::cout << test[0]     << ' ' << *test[0] << std::endl;
    std::cout << test[0] + 1 << ' ' << *(test[0] + 1) << std::endl;
    std::cout << test[0] + 2 << ' ' << *(test[0] + 2) << "\n\n";

    std::cout << test[0] + 3 << ' ' << *(test[0] + 3) << std::endl;
    std::cout << test[1]     << ' ' << *test[1]       << std::endl;
    std::cout << *p          << ' ' << **p            << "\n\n";

    std::cout << *p + 1      << ' ' << *(*p + 1)      << std::endl;
    std::cout << *(p - 1)    << ' ' << **(p - 1)      << std::endl;

    return 0;
}                
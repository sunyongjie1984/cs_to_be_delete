#include <iostream>
#include "windows.h"
using namespace std;
void test()
{
    int i; // 定义一个整形对象。
    // 输入一个整形字面值，且不等于97，则while语句测试条件表达式为真，比如3。
    // 输入字符字面值a或b都会使流对象cin在执行完函数operator>>后，处于出错状态。
    // while语句在测试作用在对象上的函数operator>>的返回值（cin对象的引用）
    // 时，会将该返回值隐式转换为false，导致测试失败。
    while ((cin >> i) && (97 != i)) 
    {                               
        cout << "I love China" << endl; 
    }
}

void test1()
{
    char i; // 定义一个字符型对象
    // 输入一个字符型字面值，且不等于'a'，
    // 则满足while语句测试条件表达式为真，比如’b'。
    // 输入字面值3，并输出回车键时，不会使流对象处于出错状态，
    //（windows操作系统）我不知道该怎么说，会认为你输入了一个字符3加上一个
    // \r字符再加上一个\n字符，操作系统应该是认为本次用户的输入操作结束，
    // 此时输入缓冲区中有3个字符，为别为'3','\r','\n'，
    while ((cin >> i) && ('a' != i)) // 输入一个字符，并且不等于97，
    {	
        cout << "I Love China" << endl;
    }
}

void test2()
{
    char i;
    while ((cin >> i) && (51 != i))
    {	
        cout << "I Love China" << endl;
    }
}

void test3()
{
    char i; // 定义一个字符型对象
    while ((cin >> i) && (51 != i)) // 输入一个字符，并且不等于'a'，
    {	
        cout << "I Love China" << endl;
    }
}

int main()
{
    // test();
    // test1();
    test2();
    return 0;
}

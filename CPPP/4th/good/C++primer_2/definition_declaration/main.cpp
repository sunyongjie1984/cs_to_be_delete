#include <iostream>
#include <string>
using namespace std;

extern int test;  //声明
int p;            //定义  首先它是全局变量（所有定义在函数外面的变量都是全局变量），分配了存储空间。

                      // in linux extern in this way will generate a warning
extern int kkk = 30;  //这里是定义，虽然用了extern，但是分配了存储空间，所以不能说是声明，这种用法可以。

int main()
{
    // 局部变量所对应的自动对象在函数控制在经过变量定义语句是创建。
    // 如果在定义时提供了初始化式，那么每次创建对象时，对象都会被赋予指定的处置。
    // 对于未初始化的内置数据类型局部变量其初值不确定。
    int a = 10;  // 定义
    int b;       // 定义未初始化
    cout << a << endl;
    cout << b << endl;
    cout << p << endl;


    return 0;
}

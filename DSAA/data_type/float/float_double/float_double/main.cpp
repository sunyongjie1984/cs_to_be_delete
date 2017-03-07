#include <iostream>
#include <float.h>
using std::cout;
using std::endl;

// 浮点数最大，最小值
int main()
{
    cout << "int 类型能存储的最大值和最小值" << endl;
    cout << "INT_MAX = " << INT_MAX << endl;
    cout << "INT_MIN = " << INT_MIN << endl;
    cout << "long 类型能存储的最大值和最小值" << endl;
    cout << "LONG_MAX = " << LONG_MAX << endl;
    cout << "LONG_MIN = " << LONG_MIN << endl;

    cout << "float 类型能存储的最大值和最小值" << endl;
    cout << "FLT_MAX = " << FLT_MAX << endl;
    cout << "FLT_MIN = " << FLT_MIN << endl;
    cout << "double 类型能存储的最大值和最小值" << endl;
    cout << "DBL_MAX = " << DBL_MAX << endl;
    cout << "DBL_MIN = " << DBL_MIN << endl;

    float a  = FLT_MAX;
    double b = DBL_MAX;

    std::cout << a << std::endl;
    std::cout << b << std::endl;

    return 0;
}
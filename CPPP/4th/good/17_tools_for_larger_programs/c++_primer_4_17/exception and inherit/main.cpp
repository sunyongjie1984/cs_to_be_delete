#include <iostream>     // standard library
#include "bookexcept.h" // user difine header
#include "Sales_item.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

int main()
{
    // use hypothetical bookstore exceptions
    Sales_item item1;
    Sales_item item2;
    Sales_item sum;

    // read two transactions
    while (cin >> item1 >> item2)
    {
        try
        {
            sum = item1 + item2;
            cout << sum << endl;
        }
        //catch (const isbn_mismatch& e)
        //{
        //    cerr << e.what() << ": left isbn(" << e.left
        //        << ") right isbn(" << e.right << ")" << endl;
        //}

        // c++ primer 4 page 584，查找匹配的处理代码：
        // 允许从非const到const的转换
        // 允许从派生类到基类的转换（是不是因为派生类中一定存在基类成员）
        // 将数组转换为指向数组类型的指针，将函数转换为指向函数类型的指针
        catch (std::logic_error const & e)
        {
            cerr << e.what() << endl;
        }
    }
    return 0;
}

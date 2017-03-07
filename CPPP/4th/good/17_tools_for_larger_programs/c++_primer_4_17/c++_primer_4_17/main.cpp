#include <iostream>     // standard library
#include "bookexcept.h" // user difine header
#include "Sales_item.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

void process(double) { } // 这个函数是干什么的？

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
            sum = item1 + item2; // calculate their sum
            cout << sum << endl; // use sum
        }
        catch (isbn_mismatch const &e) // runtime_error和logical_error都有what这个成员
        {
            cerr << e.what() << ": left isbn(" << e.left
                << ") right isbn(" << e.right << ")" << endl;
        }
        catch (...)
        {
            cerr << "exception unknown" << endl;
        }
    }
    return 0;
}
#include <iostream>
#include <assert.h>
#include "mate.hpp"
#include "lambda.hpp"
#include "Sales_item.h"
#include "bookexcept.h"
#include "t_RAII.h"

#include <functional>
#include <algorithm>
#include <cassert>
#include <vector>
#include <map>

#include "mate.hpp"
#define AM_BIND_ENABLE_STDCALL
#include "lambda.hpp"

namespace lambda = am::lambda;

void test01()
{
    Resource<Sales_item> a(1);
    Resource<Sales_item> b(1);
    std::cin >> *(a.get_object());
    std::cin >> *(b.get_object());

    //std::cout << *(a.r) + *(b.r) << std::endl;

    try
    {
        std::cout << *(a.get_object()) + *(b.get_object()) << std::endl;
    }
    catch (std::exception const & e) // 截断
    {
        std::cout << e.what() << std::endl;
    }
}

void test02()
{
    am::mate<char const *> lpszFilePath( "d:\\test.dat", &::DeleteFile );
    am::mate<HANDLE> hFile( ::CreateFile( lpszFilePath, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL ),
        &::CloseHandle,
        (HANDLE)INVALID_HANDLE_VALUE  != lambda::_1 || ( (HANDLE)123 <= lambda::_1 && ! true ) );
    if( INVALID_HANDLE_VALUE != hFile )
    {
        DWORD dwFileSize = 0;
        ::GetFileSize( hFile, &dwFileSize );
    }
}

void print_sales_item(Sales_item const & item)
{
    std::cout << item << std::endl;
}

void test03()
{
    Sales_item a("sun yongjie");
    Sales_item b("sun yongjie");
    {
        am::mate<Sales_item> item(a, &print_sales_item);
        am::mate<Sales_item> item2(b, &print_sales_item);
        //std::cin >> item; // error，可能是因为am::mate<class Type>的对象都是const对象
        std::cout << item << std::endl; // ok 为什么这里可以上面的不可以
        print_sales_item(item);

        std::cout << item + item2 << std::endl;
    }
    std::cout << "hehe" << std::endl;
    {
        MATE(a, print_sales_item);
    }
}

int main()
{
    //test01();
    //test02();
    test03();
    return 0;
}

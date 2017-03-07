#include "t_RAII.h"

void fcn() throw() // 程序员认为不抛出任何异常
{
    Sleep(1000);
    //Resource<int> const res(1024);
    Resource<std::string> const res(1024);
}

void fcn2() throw(std::exception) // 程序员认为这个函数可能抛出std::exception类型或者其派生类类型的异常
{
    Sleep(1000);
    //Resource<std::string> const res(1);
    Resource<int> const res(1000);
    //Resource<char> const res(1000);
    throw std::exception("a! yi chang le!!!");
}

int func_pointer(int const & i)
{
    int j = i + 1;
    return j;
}

int main()
{
    //while(true) // 用来验证我的RAII是不是好用，一是注释析构中的release，然后取消注释，通过任务管理器能看的很清楚
    //{
    //    fcn();
    //}
    // 把上面注释起来，下面用来看出异常时，能否有效
    //while(true)
    //{
    //    try
    //    {
    //        fcn2();
    //    }
    //    catch(std::exception const & e)
    //    {
    //        std::cout << e.what() << std::endl;
    //    }
    //}
    
    int i = 10;
    i = func_pointer(i);
    std::cout << i << std::endl;

    int (*p_func)(int const &) = func_pointer;
    i = p_func(i);
    std::cout << i << std::endl;

    return 0;
}
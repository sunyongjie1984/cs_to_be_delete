#include <iostream>
#include <string>

class my_exception : public std::exception {
public:
    my_exception() { }

private:
    std::string m_priority;
};

class c_book {
public:
    c_book(): i(10), j(20) { }
    ~c_book()
    {
        std::cout << "c_book::~c_book()" << std::endl;
    }
private:
    int i;
    int j;
};

void func()
{   // 这块内存是一定不会被析构了，这说明我的类c_book不是异常安全的，可是要怎么做才能呢，书上的例子有
    c_book const * const p = new c_book;
    try
    {
        throw my_exception();
    }
    catch(std::runtime_error const & e)
    {
        std::cout << e.what() << std::endl;
    }

    delete p;
}

void func2()
{
    c_book const * const p = new c_book;
    try
    {
        throw my_exception();
    }
    catch(std::runtime_error const & e)
    {
        std::cout << e.what() << std::endl;
    }
    catch(...)
    {
        delete p; // 这里是析构掉了，不过还是不清楚，这是不是一个非常好的万全的办法
        std::cout << "exception unknown" << std::endl;
        throw;
    }
    delete p;
}
int main()
{
    try
    {
        //func();
        func2();
    }
    catch (std::exception const & e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

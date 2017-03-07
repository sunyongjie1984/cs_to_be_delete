#include <iostream>
#include <string>
#include <memory>

class c_book {
public:
    c_book():i(20) { }
    ~c_book()
    {
        std::cout << "c_book::~c_book()" << std::endl;
    }
private:
    int i;
};

void func()
{
    c_book const * const p = new c_book;
    try
    {
        throw std::exception();
    }
    catch(std::runtime_error const & e)
    {
        std::cout << "exception std::runtime_error" << e.what() << std::endl;
    }
    delete p;
}

void func2()
{
    std::auto_ptr<c_book> p(new c_book()); // p指向的对象的内存会保证释放
    try
    {
        throw std::exception();
    }
    catch(std::exception const & e)
    {
        std::cout << "exception : std::exception : " << e.what() << std::endl;
    }
    catch(...)
    {
        std::cout << "exception unknow catch in (...) " << std::endl;
    }
}

int main()
{
    try
    {
        func2();
        //func();
    }
    catch (std::exception const & e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

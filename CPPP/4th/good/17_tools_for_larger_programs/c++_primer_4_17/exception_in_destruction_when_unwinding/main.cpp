#include <iostream>
#include <exception>

class c_book {
public:
    c_book() { }
    ~c_book()
    {
        try
        {
            throw std::exception("exception in deconstructor");
        }

        catch (std::runtime_error const & e) // 析构函数内部不能捕获，导致标准库调用terminate函数
        {                                    // terminate调用abort函数，强制整个程序非正常退出
            std::cout << e.what() << std::endl;
        }
        //catch (std::exception const & e)   // 在栈展开过程中，析构函数又抛出异常，且又自己捕获不了
        //{
        //    std::cout << e.what() << std::endl;
        //}
    }
private:
    int i;
};

void func()
{
    c_book const a;                        // 栈展开会调用a的析构函数
    try
    {
        throw std::exception("exception"); // 抛出异常
    }
    catch (std::runtime_error const & e)   // 没有捕获，致使栈展开
    {
        std::cout << e.what() << std::endl;
    }
}                                          // 会调用对象a的析构函数

int main()
{
    try
    {
        func(); // 本例结合c++ primer 4th page 583，析构函数应该从不抛出异常
    }
    catch (std::exception const & e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}

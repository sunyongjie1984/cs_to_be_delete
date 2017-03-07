//class Resource {
//public:
//    Resource(parms p): r(allocate(p)) { }
//    ~Resource() { release(r); }
//    // also need to define copy and assignment
//private:
//    resource_type *r;           // resource managed by this type
//    resource_type *allocate(parms p);     // allocate this resource
//    void release(resource_type*);         // free this resource
//};

//void fcn()
//{
//    Resource res(args);   // allocates resource_type
//    // code that might throw an exception
//    // if exception occurs, destructor for res is run automatically
//    // ...
//}  // res goes out of scope and is destroyed automatically

#include <exception>
#include <iostream>
#include "Windows.h"

class Resource {
public:
    // 不用allocate这个函数时，可以使用这个构造函数也是一样的
    //Resource(int const & number) : r(new int [number]())
    //{ 
    //    std::cout << "allocate 4k bytes" << std::endl;
    //}
    Resource(int const & number) : r(allocate(number)) { }
    ~Resource() { release(r); }
private:
    int * allocate(const int & number) const // 程序员我认为这个函数可能抛出任何异常
    {
        std::cout << "allocate 4k bytes " << std::endl;
        return new int[number]();           // 小括号表示初始化为0，在linux下这句话也是编不过的，必须把小括号拿掉
    }

    void release(int * pRes) const throw()   // 程序员我认为这个函数不抛出任何异常
    {
        std::cout << "free 4k bytes " << std::endl;
        delete pRes;
    }
    int * r;
};

void fcn() throw() // 程序员认为不抛出任何异常
{
    Sleep(1000);
    Resource const res(1024);

}

void fcn2() throw(std::exception) // 程序员认为这个函数可能抛出std::exception类型或者其派生类类型的异常
{
    Sleep(1000);
    Resource const res(1000);
    throw std::exception("a! yi chang le!!!");
}

int main()
{
    //while(true) // 用来验证我的RAII是不是好用，一是注释析构中的release，然后取消注释，通过任务管理器能看的很清楚
    //{
    //    fcn();
    //}

    // 把上面注释起来，下面用来看出异常时，能否有效

    while(true)
    {
        try
        {
            fcn2();
        }
        catch(std::exception const & e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
}

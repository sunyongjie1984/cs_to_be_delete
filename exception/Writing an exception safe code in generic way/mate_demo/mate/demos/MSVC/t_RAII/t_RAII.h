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

template <class Type> class Resource {
public:
    Resource(int const & number) : r(allocate(number)) { }
    //Resource(int const & number)
    //{
    //    r = allocate(number);
    //}
    ~Resource() { release(r); }
private:
    Type * allocate(int const & number) const // 程序员我认为这个函数可能抛出任何异常
    {
        std::cout << "allocate 4k bytes " << std::endl;
        return new Type[number](); // 小括号表示初始化为0，在linux下这句话也是编不过的，必须把小括号拿掉
    }

    void release(Type * pRes) const throw()   // 程序员我认为这个函数不抛出任何异常
    {
        std::cout << "free 4k bytes " << std::endl;
        delete [] pRes; // []重要，没有会导致异常发生，new的是数组，delete不是数组，会有异常发生
    }                   // 在这里，windows下，整型不发生异常，new了std::string类型的数组会发生异常
                        // int * p = new int[1]; 使用delete [] p是安全的
                        // int * p = new int;    使用delete [] p是抛出异常的
    Type * r;
};
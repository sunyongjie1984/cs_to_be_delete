#include <exception>
#include <string>
#include <iostream>

class my_base_exception : public std::exception {
public:
    my_base_exception(std::string const & str = "sunyongjie" ) : m_name(str), m_age(28) { }
    virtual void print() const { std::cout << m_name << " " << m_age; }
    virtual ~my_base_exception() throw() { }
private:
    std::string m_name;
    int m_age;
};



class my_derive_exception : public my_base_exception {
public:
    //my_derive_exception(std::string const & str) : m_b_funny(true) { }
    //my_derive_exception(std::string const & str) : my_base_exception(), m_b_funny(true) { }
    // 按照上面的两个函数my_derive_exception的对象m_name为空字符串，
    my_derive_exception(std::string const & str) : my_base_exception(str), m_b_funny(true) { }
    void print() const { my_base_exception::print(); std::cout << " " << m_b_funny; }
private:
    bool m_b_funny;
};



int main()
{
    my_base_exception const a;
    my_derive_exception const b("yongjisu");
    a.print();
    std::cout << std::endl;
    b.print();
    std::cout << std::endl;
    try
    {
        throw b;
    }
    //catch(my_derive_exception const & e) // 这个catch是正常捕捉
    //{
    //    e.print();
    //    std::cout << std::endl;
    //}
    catch(my_base_exception const & e)   // 这个catch是动态绑定
    {
        e.print();
        std::cout << std::endl;
    }
//     catch(my_base_exception const e)       // 截断发生，其实这和CBase base = child;一样的
//     {
//         e.print();
//         std::cout << std::endl;
//     }  
    const my_base_exception* const pBase = &b;
    pBase->print();
    std::cout << std::endl;
    try
    {   // c++ primer 4 page 582，在抛出中对指针进行解引用，解引用产生的对象与指针类型相匹配，
        throw *pBase; // 动态绑定不发生，throw动作一，抛出表达式，动作二复制这个表达式产生异常对象
    }             
    //catch(my_derive_exception const & e) // 这个将不能捕获因为子类不能捕获基类异常对象
    //{
    //    e.print();
    //    std::cout << std::endl;
    //}
    //catch(my_base_exception const & e)   // 与类型为基类的异常对象匹配
    //{
    //    e.print();
    //    std::cout << std::endl;
    //}
    catch(...)
    {
        std::cout << "exception unknown" << std::endl;
    }

    std::cin.get();
    return 0;
}

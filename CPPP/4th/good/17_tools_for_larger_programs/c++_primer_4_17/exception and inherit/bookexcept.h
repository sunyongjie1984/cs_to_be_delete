#ifndef BOOK_EXCEPT
#define BOOK_EXCEPT

#include <stdexcept>

// std::runtime_error and std::logical_error are defined in file stdexcept
// hypothetical exception classes for a bookstore application
// hypothetical 假设的，假定的，爱猜想的
class out_of_stock: public std::runtime_error {
public:
    // I think, this constructor is like this,
    // runtime_error is a base class of out_of_stock, in the constructor
    // initialize list std::runtime_error(s) means, invoke the base
    // class constructor to initialize the base part of the out_of_stock object
    // explicit 意思是调用这个构造函数的时候，不能发生隐式转换，只能传进一个std::string
    // 类型的对象，不可以是能转换为std::string类型的对象，比如char*之类
    explicit out_of_stock(std::string const & s): std::runtime_error(s) { }
};

class isbn_mismatch: public std::logic_error {
public:
    explicit isbn_mismatch(std::string const & s): std::logic_error(s) { }

    isbn_mismatch(std::string const & s, std::string const & lhs, std::string const & rhs):
        std::logic_error(s), left(lhs), right(rhs) { }

    // myref(section)(exceptSpec) explains the destructor and why we need one
    virtual ~isbn_mismatch() throw() { }

    // 必须在构造函数初始化列表中赋值，c++ primer 4 page 388
    // 没有默认构造函数的类类型成员，以及const或引用类型成员，不管是什么类型
    // 都必须在构造函数初始化列表中进行初始化
    const std::string left;
    const std::string right;
};

#endif

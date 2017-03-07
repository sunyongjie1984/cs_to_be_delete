#ifndef SUNYONGJIE_EXCEPTION
#define SUNYONGJIE_EXCEPTION

#include <stdexcept>
#include <string>

class my_exception : public std::logic_error {
public:
    explicit my_exception(std::string const & s) :
        std::logic_error(s) { }

    my_exception(std::string const & s, std::string const & lhs, std::string const & rhs):
        std::logic_error(s), left(lhs), right(rhs) { }

    // 可以被初始化，但是不可以赋值
    // this member data can be initialized not assigned
    // it is a necessary for a constructor initialize list
    std::string const left;

    std::string right;

    // myref(section)(exceptSpec) explains the destructor and why we need one
    virtual ~my_exception() throw() { }
};

#endif

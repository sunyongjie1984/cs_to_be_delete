#include <exception> // 这个文件与stdexcept的区别与联系是什么
#include <iostream>  // what如何被覆盖
#include <string>

class my_exception : public std::exception {
public:
    explicit my_exception(std::string const & str = "I have fucking no idea what happened")
        : m_string(str) { }
    std::string zadele() const
    {
        return m_string;
    }
    virtual char const * what() const throw()
    {
        return m_string.c_str();
    }
private:
    std::string m_string;
};

int main()
{
    try
    {
        my_exception const a;
        throw a;
    }
    catch (my_exception const & e)
    {
        std::cout << e.what() << std::endl;
        std::cout << e.zadele() << std::endl;
    }
    return 0;
}

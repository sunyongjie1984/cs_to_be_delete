#include <string>
#include <iostream>

class myBook {
public:
    // 这个explicit的意思是，在一个函数调用发生时，像myBook::same_book_name(const myBook&)
    // 这个期待一个myBook类型的实参传入时，如果传入的实参类型是可以隐式转换为myBook类型
    // 的实参时，也不可以通过编译的意思，它并不是说myBook b("hehe")这样的语句执行不了
    // 构造函数explicit myBook(std::string)的形参是值传递的是实参的复本，如果定义成
    // explicit myBook(const std::string&)也是可以的，是引用传递的
    // 只有定义成explicit myBook(std::string&)不行，因为非const引用只能绑定到类型为
    // myBook的对象，相互转换的是不行的，右值是不行的，以前有很多地方讨论过这个问题
    // explicit的用途在myBook::same_book_name(const myBook&)期待一个myBook的对象时，不
    // 能传入std::string形式的对象，第一件事和函数调用参数传递无关，只要是定义一个变量
    // 或引用时就会发生，后者是讨论的调用构造函数进行隐匿转换的事情。
    explicit myBook(std::string str)
    {
        name = str;
    }

    myBook(char* p)
    {
        name = p;
    }

    bool same_book_name(const myBook& book)
    {
        return name == book.name;
    }
private:
    std::string name;
};

int main()
{
    std::string s = "haha";

    myBook a(s);
    myBook b("hehe"); // 相当于std::string str = "hehe"，这是可以的
                      // 而且const std::string& str = "hehe"，也是可以的
                      // 只有std::string& str = "hehe"不行

    // 这条语句不论myBook的构造函数有没有explicit都是不行的，不能发生两次类型转换的
    // 只有当myBook有个以char*类型的构造函数而且那个构造函数前面还没有explicit的时候才可以
    std::cout << a.same_book_name("haha") << std::endl; // 成功因为myBook::myBook(char*)
    std::cout << a.same_book_name(b) << std::endl;      // 成功因为完全匹配
    //a.same_book_name(s);                              // 失败因为explicit

    return 0;
}

#include <iostream>
class CBookBase {
public:
    std::string GetISBN() // 期望子类继承的函数不可以定义为虚函数。
    {
        return isbn;
    }

    virtual void GetTitle() // 期望子类覆盖的函数一定要定义为虚函数。
    {
        std::cout << "CBookBase::GetTitle" << std::endl;
    }

    virtual void GetColor() = 0; // 子类必须覆盖的函数定义为纯虚函数。

private:
    std::string isbn;
    int title;
    int color;
};

class CBookChild1 : public CBookBase {
public:
    /*
    std::string GetISBN() // 这里没有定义这个函数是对的，因为设计父类的时候就是要你子类
    {
        ////
    }
    */
    void GetTitle()
    {
        std::cout << "CBookChild1::GetTitle" << std::endl;
    }

    void GetColor()
    {
        std::cout << "CBookChild1::GetColor" << std::endl;
    }
};

class CBookChild2 : public CBookBase {
public:
    void GetTitle()
    {
        std::cout << "CBookChild2::GetTitle" << std::endl;
    }

    void GetColor()
    {
        std::cout << "CBookChild2::GetColor" << std::endl;
    }
};

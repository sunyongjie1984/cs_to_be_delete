#include <iostream>

class c_base {
public:
    void apple()          { std::cout << "apple in base" << std::endl; }
    virtual void orange() { std::cout << "orange in base" << std::endl; }
    void virtual pear()   { std::cout << "pear in base" << std::endl; }
};

class c_derive : public c_base {
public:
    void apple()          { std::cout << "apple in derive" << std::endl; }
    virtual void orange() { std::cout << "orange in derive" << std::endl; }
    virtual void pear()   { std::cout << "pear in derive" << std::endl; apple(); orange();}
};

class c_derive_twice : public c_derive {
public:
    void pear() { std::cout << "pear in derive_twice" << std::endl; }
};

int main()
{
    c_base a;
    a.apple();
    a.orange();
    std::cout << std::endl;

    c_derive b;
    b.apple();
    b.orange();
    std::cout << std::endl;

    c_derive c;
    c_base* p = &c;
    p->apple();
    p->orange();
    p->pear();
    std::cout << std::endl;

    c_derive_twice d;
    c_derive* q = &d;
    q->pear();

    return 0;
}
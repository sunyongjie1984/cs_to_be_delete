#include <iostream>
class fruit {
public:
    virtual void print() { std::cout << "I am fruit" << std::endl; }
    void print2() { std::cout << "I am fruit 2" << std::endl; }
};

class apple : public fruit {
public:
    void print() { std::cout << "I am apple" << std::endl; }
    void print2() { std::cout << "I am apple 2" << std::endl; }
};

int main()
{
    fruit* p = new fruit();
    p->print();
    p->print2();

    ((apple*)p)->print();
    ((apple*)p)->print2();
    return 0;
}

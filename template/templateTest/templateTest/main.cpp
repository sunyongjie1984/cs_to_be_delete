#include <string>
#include <iostream>
template <class T>
class CStack { // 这什么都看不出来。
public:
    CStack()
    {
        ISBN = 100;
    }
    int getISBN()
    {
        return ISBN;
    }
private:
    int ISBN;
    std::string name;
};
int main()
{
    CStack<int> a;
    std::cout << a.getISBN() << std::endl;

    CStack<std::string> b;
    std::cout << b.getISBN() << std::endl;

    return 0;
}
        
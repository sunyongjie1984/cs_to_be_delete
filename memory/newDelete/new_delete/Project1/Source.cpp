#include <iostream>
class CBook {
public:
    CBook(): m_price(20.01) { }
    double get_price() { return m_price; }
private:
    double m_price;
};

int main()
{
    CBook a;
    std::cout << a.get_price() << std::endl;
    std::cin.get();
}

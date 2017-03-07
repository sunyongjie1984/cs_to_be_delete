#include <iostream>
_declspec(dllexport) int add(const int& a, const int& b)
{
    return a + b;
}

class _declspec(dllexport) CBook {
public:
    void print()
    {
        std::cout << "I Love China" << std::endl;
    }
};
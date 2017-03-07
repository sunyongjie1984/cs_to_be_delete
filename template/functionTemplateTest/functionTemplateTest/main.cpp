#include <iostream>

class CBook {
public:
    CBook()
    {
        i = 20;
        j = 30;
    }
    friend bool operator<(CBook& l, CBook& r)
    {
        if (l.i < r.i)
        {
            return 1;
        }
        return 0;
    }
// private:
    int i;
    int j;
};

template <typename T>
int compare(const T& v1, const T& v2)
{
    if (v1 < v2)
    {
        return -1;
    }
    if (v2 < v1)
    {
        return 1;
    }
    return 0;
}

int main()
{
    int i = 10;
    int j = 20;
    CBook a;
    CBook b;
    a.i = 3;
    bool k = a < b;
    std::cout << k << std::endl;
    // std::cout << compare(a, b) << std::endl; // I still do not understand.
    std::cout << compare(i, j) << std::endl;
    return 0;
}

#include <iostream>
#include <string>
#include <vector>

using namespace std;

std::vector<int>&& haha(const unsigned int& count )
{
    std::vector<int> a;
    for (unsigned int i = 0; i < count; i++)
    {
        a.push_back(i);
        printf("%d\n", a[i]);
    }
    // still wrong, a will be destroyed, it is not the typical use of move
    return std::move(a);
}

int main()
{
    auto ret = haha(4);
    return 0;
}

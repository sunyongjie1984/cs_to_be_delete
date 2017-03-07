#include <iostream>
namespace SUNYONGJIE {
    class CBook {
    public:
        CBook()
        {
            i = 10;
            j = 9;
        }
        int GetNumber()
        {
            return i;
        }
    private:
        int i;
        int j;
    };
}
int main()
{
    SUNYONGJIE::CBook a;
    std::cout << a.GetNumber() << std::endl;
    return 0;
}

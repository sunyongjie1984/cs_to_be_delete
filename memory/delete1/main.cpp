#include <iostream>
class CBook {
public:
    CBook():m_i(10){}
    ~CBook()
    {
        int kkk = 0;
        std::cout << kkk << std::endl;
    }
private:
    unsigned m_i;
};

typedef struct tagTestType{
    CBook* pBook;
    int   b;
}STOCK_TYPE;

int main()
{
    CBook a;

    STOCK_TYPE* p = new STOCK_TYPE;
    p->pBook = &a;
    delete p;
    return 0;
}

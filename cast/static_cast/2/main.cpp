#include <iostream>

typedef struct tagPAGE {
    int  o;
    int  p;
}PAGE;

typedef struct tagBook {
    PAGE i;
    int  m;
}BOOK;

int main()
{
    PAGE aa;
    aa.o = 100;
    aa.p = 200;

    PAGE* p = &aa;

    BOOK* q = (PAGE*)p;
    //BOOK* q = static_cast<PAGE*>(p);
    std::cout << q->i.p << std::endl;
    return 0;
}

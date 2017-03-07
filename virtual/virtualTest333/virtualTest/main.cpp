#include "book.h"

int main()
{
    CBookBase* p1 = new CBookChild1();
    CBookBase* p2 = new CBookChild2();

    p1->GetTitle();
    p2->GetTitle();

    p1->GetColor();
    p2->GetColor();

    return 0;
}
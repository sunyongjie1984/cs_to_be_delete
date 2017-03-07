#ifndef INT_SINGLY_LINKED_LIST_NODE
#define INT_SINGLY_LINKED_LIST_NODE
#include <iostream>
using std::ostream;
using std::istream;
class islln
{   // using friend, I keep info and next private
    // and the class isll can access them
    // and the global function overloaded operators can access them.
    friend class isll;
    friend ostream& operator<<(ostream&, const isll&);
    friend istream& operator>>(istream&, isll&);
public:
    islln(): info(0), next(0) { }
    islln(int i, islln* in = 0): info(i), next(in) { }
private:
    int info;
    islln* next;
};
#endif

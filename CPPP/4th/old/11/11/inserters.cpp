#include "algs_preamble.h"
int main() 
{
    list<int> ilst, ilst2, ilst3;     // empty lists

    // after this loop ilst contains: 1 2 3 4
    for (list<int>::size_type i = 0; i != 4; ++i)
         ilst.push_front(i);

    // print list to see the ordering
    cout << "ilst" << endl;
    for (list<int>::iterator iter = ilst.begin(); iter != ilst.end(); ++iter)
	    cout << *iter << " ";
    cout << endl;

    // after copy ilst2 contains: 4 3 2 1
    copy(ilst.begin(), ilst.end(), front_inserter(ilst2));

    // after copy, ilst3 contains: 1 2 3 4
    copy(ilst.begin(), ilst.end(), 
                inserter(ilst3, ilst3.begin()));

    // print ilst2 and ilst3 
    cout << "ilst2" << endl;
    for (list<int>::iterator iter = ilst2.begin(); iter != ilst2.end(); ++iter)
	    cout << *iter << " ";
    cout << endl;
    cout << "ilst3" << endl;
    for (list<int>::iterator iter = ilst3.begin(); iter != ilst3.end(); ++iter)
	    cout << *iter << " ";
    cout << endl;

    return 0;
}

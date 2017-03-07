#include <iostream>
using namespace std;
char* fun()
{
    char *p = "I Love China!";
    return p;
}
int main()
{
    char* q = fun();
    cout << q << endl;
    cout << *q << endl;

    int i = 10;
    int* a = &i;
    cout << *a << ' ' << a << endl;

    char* b = q;
    cout << b << endl;

    return 0;
}

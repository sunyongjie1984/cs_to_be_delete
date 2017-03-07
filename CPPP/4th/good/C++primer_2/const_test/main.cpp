// this source code is useless, this file could be ignored
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int i = 10;
    int const j =10;
    int * p = &i;
    int & r = i;

    //int const * pp = &i;
    int const * pp = &j;
    //int * q = &j;
    //*pp = 2;
    i++;
    cout << *pp << endl;
    int const & rr = i;

    const int* ii = &i;
    int* const ii2 = &i;
    int const * ii3 = &i;   //不建议这么定义
    *ii2 = 4;
    cout << *ii2 << endl;

    return 0;
}

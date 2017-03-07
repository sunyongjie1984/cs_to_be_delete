#include <iostream>   
using namespace std;   

void f1(int*& a)   
{   
    int* b;   
    b = a;   
}   

void f2(int *c)   
{   
    int* d;   
    d = c;   
}   

void main()   
{   
    int m  = 10;   
    int *n = &m;   

    f1(n);   
    f2(n);   
}        
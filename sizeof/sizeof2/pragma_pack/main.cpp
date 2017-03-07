// pragma_directives_pack.cpp
#include <stddef.h>
#include <stdio.h>

struct S {
    int    i;   // size 4
    short  j;   // size 2
    double k;   // size 8
};

#pragma pack(2)
struct T {
    int    i;
    short  j;
    double k;
};

int main() 
{
    S a;
    T b;
    printf("%d ", sizeof(a));
    printf("%d ", sizeof(b));
}

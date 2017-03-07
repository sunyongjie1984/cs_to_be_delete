#include <iostream>
#include <stdint.h>
#include <stdio.h>
int main()
{
    int i = 20;
    unsigned int j = 300;
    uint64_t k = 4294967295; // (2 32) - 1
    uint64_t l = 5294967295;
    printf("%d,  %d,  %d,  %d  \n",  i, j, k, l);
    printf("%ld, %ld, %ld, %ld \n", i, j, k, l);

    uint32_t m = 4294967295;
    printf("%ld \n", 2 * m);

    uint32_t o = 4294967295;
    uint32_t o1 = 10;
    printf("hehe %ld \n", (uint64_t)(o1 * o));
    printf("hehe %ld \n", (uint64_t)o1 * o);
    printf("%lu \n", (uint64_t)2 * o);

    uint32_t p = 4294967295;
    printf("%ld \n", -(uint64_t)2 * p);
    printf("haha %ld \n", (uint64_t)(2 * o));
    printf("%lu \n", (uint64_t)2 * o);

    // uint32_t p = 4294967295;
    // printf("%ld \n", -(uint64_t)2 * p);

    uint64_t n = 4294967295;
    printf("%ld \n", 2 * n);


    uint64_t q = (uint64_t)-2;
    printf("%ld \n", q);
    printf("%lu \n", q);


    return 0;
}

#include <iostream>
#include "static_hash.h"

int main(int argc, char **argv)
{
    CHash test(10, 100 * 1000);
    char* p = "sunyj00001";
    // char* q = NULL;
    void* q;
    test.add(p, (void*)"hello world");
    std::cout << test.get(p, q) << std::endl;
    std::cout << q << std::endl;
    std::cout << (char*)q << std::endl;
    
    char* p1 = "sunyj00002";
    int a = 100;
    void* q1;
    test.add(p1, (void*)&a);
    test.get(p1, q1);
    std::cout << q1 << std::endl;
    std::cout << *(int*)q1 << std::endl;
    return 0;
}

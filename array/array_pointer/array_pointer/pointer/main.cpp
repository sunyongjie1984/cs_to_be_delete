#ifdef SUNYJ_UNIXLIKE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#endif

#include <iostream>
#include <string>

char* GetMemory(char** p, int num) 
{
    *p = (char*)malloc(num);
    return *p;
}

int main()
{
    char* p_dele = NULL;           // 首先str是一个定义了的变量，是变量就要分配内存空间
    char* str = NULL;              // 首先str是一个定义了的变量，是变量就要分配内存空间
    p_dele = GetMemory(&str, 100); // &str假设是1000，传到GetMeory，p就是&str,
    // 也就是说，p就是str的地址，那么*p，就是指针str,*p指向分配好了的
    // 内存，也就是说str指向了分配好了的内存。疯了，一定有别的理解方法
    strcpy(str, "I Love China!"); 
    // strcpy(str, "I Love \0China!"); // 真的能够截断啊！
    printf(str); // 如何解决这个内存泄露问题呢，可以str == NULL?
    std::cout << std::endl;
    free(p_dele);
    p_dele = NULL; // after deleting the pointer, set the pointer to NULL
    delete p_dele; // safe, because p_dele has been set to NULL
    return 0;
}

#include <iostream>
#include <string>

int main()
{
    char *str = (char *) malloc(10);
    strcpy(str, "hello");
    free(str);
    if(str != NULL)
    {
        strcpy(str, "world"); // 有人说这个指针现在非常危险呵呵，
        printf(str);          // 可是就是能够输出内容，呵呵
    }  
    std::cout << std::endl;
    return 0;
}
#include <iostream>
#include <string>
// very friendly compiler
// warning C4172: returning address of local
// variable or temporary
char* GetMemory(void)
{
    char p[] = "hello world"; // define a array of char
    return p;
}

int main()
{
    char * str = NULL; // difine a pointer to a char
    // std::cout << str;  // runtime error
    str = GetMemory();
    printf(str);
    std::cout << std::endl;
    return 0;
}

#include <iostream>
#include <string> // & 左边是char* 表示定义谁的引用，右边是p引用变量名
char*& GetMemory(char*& p) // 绑定到指针的引用，或者说是指针的引用。


//char* GetMemory(char* p) // 没有能够改变主调函数中的str，只有引用才能
{                        // 完成这个任务，呵呵。
    p = (char *)malloc(100);
    return p;
}

int main()
{
    char *str = NULL;
    GetMemory(str);	
    strcpy(str, "hello world");
    printf(str); // 这可够乱的了，呵呵，要试一下好不好用。
    std::cout << std::endl;
    return 0;
}                               
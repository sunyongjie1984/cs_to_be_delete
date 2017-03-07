#include <list>
#include <string>
#include <iostream>
using namespace std;
int main()
{
    // 这个语句定义了一个指针数组：


    // 1，定义了一个数组
    // 2，数组名字是words
    // 3, 数组中元素类型为指针
    // 4, 指针类型为指向字符的指针
    char* words[] = { "stately", "plump", "buck", "mulligan" };
    size_t words_size = sizeof(words) / sizeof(char*);
    list<string> words2(words, words + words_size);

    char* p = "hehe"; // 字义了一个指向字符的指针，这个指针被初始化为一个字符串常量的地址。
    char a = 'a';
    char* p2 = &a;

    // 1，定义了一个数组
    // 2，数组名字是a
    // 3, 数组中元素类型为字符
    char a[] = { 's', 'b', 'c'};
    return 0;
}

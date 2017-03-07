#include <iostream> //这道题大家一起努力了很久的，呵呵。乐天兄讲的
using namespace std;
struct tagAAA
{
    unsigned char a : 1;
    unsigned char b : 2;
    unsigned char c : 6;
    unsigned char d : 4; // 三个字节
    unsigned char e;     // 第四个
    unsigned char f : 4; // 自己四个
    unsigned long g;     // 又四个
}AAA_S;
int main()
{
    cout << sizeof(AAA_S) << endl;
    return 0;
}

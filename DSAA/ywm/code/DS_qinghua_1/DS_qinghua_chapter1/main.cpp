#include <iostream>

#ifdef __linux
#include <stdio.h>
#endif

typedef struct  
{
    int i;
    float j;
}LNode, *pNode;
// 我觉得这个定义的意思是
// LNode这个类型和*pNode是一个类型，那么pNode的类型就是指向LNode类型的指针

int main()
{
    LNode a;
    a.i = 200;
    a.j = 200.00;

    // pNode作为一个类型，定义了变量p被初始化为a的地址
    // PNode一定与LNode*是一样的
    // 因为正常来说是应该这样定义的 LNode* p = &a，不知道王总能理解不

    pNode p = &a;

    std::cout << p->j << std::endl;

    getchar();
    return 0;
}
#include "example.h"
CExample::CExample()
{
    pBuffer = NULL;
    nSize = 0;
}

CExample::CExample(const CExample& rSide)
{
    nSize = rSide.nSize;
    pBuffer = new char[nSize];
    memcpy(pBuffer, rSide.pBuffer, nSize * sizeof(char));
}

CExample::~CExample()
{
    // delete pBuffer[]; 有时也可以，多了没有想。
    delete pBuffer;
}

void CExample::Init(int n)
{
    pBuffer = new char[n];
    nSize = n;
}

void CExample::SetBuffer(char* p)
{
    if (strlen(p) > nSize) // 必须的，不然，赋值可能可以成功，但是析构的时候可能会有问题。
    {
        return;
    }
    else
    {
        // memcpy(pBuffer, p, sizeof(p) * sizeof(char)); // sizeof(p) == 4
        memcpy(pBuffer, p, strlen(p) * sizeof(char)); // 操作自己的字符串，pBuffer又是char*类型的好像只能这么操作
                                                      // 它了吧。
    }
}

void CExample::PrintBuffer()
{
    std::cout << pBuffer << std::endl;
}

/*
CExample& CExample::operator=(CExample& rSide) // 这是一个错误的重载赋值操作符，没有去delete原来指针对象指向的内存。
{
    nSize = rSide.nSize;
    pBuffer = new char[nSize];
    memcpy(pBuffer, rSide.pBuffer, nSize * sizeof(char));
    return *this;
}
*/

CExample& CExample::operator=(const CExample& rSide)
{
    nSize = rSide.nSize; // 复制常规成员。

    char* p = new char[nSize];
    memcpy(p, rSide.pBuffer, nSize * sizeof(char)); // 复制指针指向的内容。

    delete []pBuffer; // delete自己原来new出来的内存。// 这里可不可以delete pBuffer不用[]呢?

    pBuffer = p;      // 建立新的指向。

    return *this;
}
/*
CExample::CExample(const CExample& rSide)
{
    pBuffer = NULL; // 这个语句非常有用，从调试中可以看到，因为赋值运算符很可能没有考虑到拷贝构造函数
                    // 要使用你来定义，所以还是要先delete掉你原来指向的内存
                    // 可是由于咱们是一个构造函数，指针成员还没有new出东西来，所有delete时就造成了错误。
    *this = rSide;  // 调用重载后的赋值操作符。
}
*/
void CExample::SetTooLongBuffer(char* p)
{
    memcpy(pBuffer, p, strlen(p) * sizeof(char));
}

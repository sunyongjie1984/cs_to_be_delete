#include <iostream>
class CExample {
public:
    CExample();                   // 默认构造函数
    // CExample(const CExample&); // 拷贝构造函数
    ~CExample();                  // 析构函数

    void Init(int);               // 初始化
    void SetBuffer(char*);        // 赋值
    void SetTooLongBuffer(char*); // wrong func
    void PrintBuffer();           // 输出

    CExample& operator=(const CExample&); // 重载赋值操作符
    CExample(const CExample&);    // 拷贝构造函数可以使用重载赋值操作符来定义自己
private:
    char* pBuffer;
    int nSize;
};

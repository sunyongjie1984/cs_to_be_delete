#include <iostream>
#define NULL 0
class CExample {
public:
	CExample();                     // 默认构造函数
    ~CExample()
    {
        delete pBuffer;
    }
    void CExample::Init(int );
private:
	char* pBuffer;              
	int nSize;
};
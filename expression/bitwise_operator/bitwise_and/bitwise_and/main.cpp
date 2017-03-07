#include <iostream>
#include "test_macro.h"
int main()
{   // 按位与，按位或
    
    // 按位或就是功能相加的意思
    int m_nUserFlags = 1;
    m_nUserFlags |= USER_FLAG_EXTERNSUBSCIBE;

    m_nUserFlags = 1;
    m_nUserFlags |= (USER_FLAG_WTQR|USER_FLAG_LOCALTLDM);

    // 宏都定义成只有一位为1，这样flag与它们按位或等于就是说，加上某个标识
    // flag与它们按位与，就是要判断目前的flag中有没有这个功能，是否设置了这个标识，如果flag中设置了这个宏标识，则按位与的结果不为0
    if ((m_nUserFlags&USER_FLAG_EXIT) == 0)
    {

    }
    m_nUserFlags = USER_FLAG_INITSUBSCIBE;
    if ((m_nUserFlags&USER_FLAG_INITSUBSCIBE) == 0)
    { // 1289 ..> 1293
        m_nUserFlags |= (USER_FLAG_INITSUBSCIBE|USER_FLAG_EXTERNSUBSCIBE);
    }

    m_nUserFlags &= ~USER_FLAG_UDPQUOTE;
    
    // 1293变269
    m_nUserFlags &= ~USER_FLAG_LOCALTLDM;
    
    // 269变285
    m_nUserFlags |= USER_FLAG_QHHQCX;
    getchar();
    return 0;
}
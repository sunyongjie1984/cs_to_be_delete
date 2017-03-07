#include "CIntArray.h"
CIntArray::CIntArray(int sz)
{
    //m_iSize = sz; // sz有可能是0，或者负数。
    //ia = new int[m_iSize]; // 可能会失败，内存不是总有空间
    //for (int ix = 0; ix != m_iSize; ix++)
    //{
    //    ia[ix] = 0;
    //}
    Init(0, sz);
}

CIntArray::CIntArray(int* arr, int array_size)
{
    //m_iSize = array_size;
    //ia = new int[m_iSize];
    //for (int ix = 0; ix != m_iSize; ix++)
    //{
    //    ia[ix] = arr[ix];
    //}
    Init(arr, array_size);
}

CIntArray::CIntArray(const CIntArray& rhs)
{
    //m_iSize = rhs.m_iSize;
    //ia = new int[m_iSize];
    //for (int ix = 0; ix != m_iSize; ix++)
    //{
    //    ia[ix] = rhs.ia[ix];
    //}
    Init(rhs.ia, rhs.m_iSize);
}

void CIntArray::Init(int* arr, int sz)
{
    m_iSize = sz;
    ia = new int[m_iSize];
    for (int ix = 0; ix != m_iSize; ix++)
    {
        if (!arr)
        {
            ia[ix] = 0;
        }
        else
        {
            ia[ix] = arr[ix];
        }
    }
}


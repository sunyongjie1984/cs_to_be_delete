//TempSample1.h
#include "stdafx.h"

// 如何声明和定义自己的模版类
template<  class T >
class Test1
{
public:
    Test1( void ){};
    ~Test1( void ){};
   
    //如何定义统一的处理方法
    void OutputMsg( LPCSTR lpszMsg );

    void Textincpp( void );
};

//如何定义统一的处理方法
template< class T >
 void Test1<T>::OutputMsg( LPCSTR lpszMsg )
{
    // 如何定义统一的处理方法
    T Outer;
    Outer.OutMsg1( "template< class T > Test1<T>::OutputMsg1 ->", lpszMsg );
    return;
}
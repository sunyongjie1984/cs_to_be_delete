//TempSample11.h
#include "stdafx.h"

// 如何声明和定义自己的模版类
template<  class T >
class Test2
{
public:
    Test2( void ){};
    ~Test2( void ){};

    //如何定义统一的处理方法
    void OutMsg( LPCSTR lpszMsg );

    //如何定义统一的处理方法
    void OutMsg1( LPCSTR lpszParent, LPCSTR lpszMsg );

};

//如何定义统一的处理方法
template< class T >
 void Test2<T>::OutMsg( LPCSTR lpszMsg )
{
    T Outer;

    Outer.OutMsg1( "template< class T > Test2<T>::OutputMsg1 ->", lpszMsg );

    return;
}

template< class T >
 void Test2<T>::OutMsg1( LPCSTR lpszParent, LPCSTR lpszMsg )
{
    T Outer;

    Outer.OutMsg2( lpszParent, "template< class T > Test2<T>::OutputMsg2 ->", lpszMsg );

    return;
}
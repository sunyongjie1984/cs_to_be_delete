// TestVectorPush1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
// 包含头文件 #include<vector>
#include <vector>

// 使用命名空间 using namespace std;
using namespace std;


class Out1
{
public:
    Out1( void ){};
    ~Out1( void ){};

    //如何定义统一的处理方法
    void OutMsg( LPCSTR lpszMsg )
    {
        cout << " Class Out1::OutMsg( " << lpszMsg << " )" << endl;
    }
    
    void OutMsg1( LPCSTR lpszParent, LPCSTR lpszMsg )
    {
        cout <<  lpszParent <<" Class Out1::OutMsg1( " << lpszMsg << " )" << endl;
    }

    void OutMsg2( LPCSTR lpszRoot , LPCSTR lpszParent, LPCSTR lpszMsg )
    {
        cout << lpszRoot <<  lpszParent <<" Class Out1::OutMsg2( " << lpszMsg << " )" << endl;
    }

};

typedef vector<Out1*> OuterArray_type;

int main(int argc, char* argv[])
{
    OuterArray_type oAry;
    OuterArray_type::const_iterator c_oIt = oAry.begin();
    OuterArray_type::iterator oIt = oAry.begin();
    OuterArray_type::reverse_iterator rIt = oAry.rbegin();
    OuterArray_type::size_type stCnt = 5;
    OuterArray_type::size_type i = 0;

    OuterArray_type::value_type pVal = NULL;
    
    for(  i = 0; i < stCnt; i++  )
    {
        pVal = new Out1;
        if ( NULL == pVal )
        {
        }
        else
        {
            oAry.push_back( pVal );
            cout << pVal << " ";
            cout << "the capacity is " << oAry.capacity() << endl;
        }
    }

    // 注意元素的安全 
    //  因为 end() 返回的是指向最后一个元素后面的迭代器
    // 所以可以使用rbegin()得到向量的最后一个元素
    rIt = oAry.rbegin();
    delete (*rIt);
    *rIt = NULL;

    //  因为 end() 返回的是指向最后一个元素后面的迭代器
    // 所以如果要得到最后一个元素，应该是oIt = oAry.end() - 1;
//    oIt = oAry.end();
//    oIt--; 
//    delete (*oIt);
//    *oIt = NULL;

    // 移除向量的最后一个元素
    oAry.pop_back();

    OuterArray_type::size_type nCnt = oAry.size();
    for( c_oIt = oAry.begin(); c_oIt != oAry.end(); c_oIt++ )
    {
        cout << *c_oIt << " ";
        (*c_oIt)->OutMsg( "out test!" );
    }

    for( c_oIt = oAry.begin(); c_oIt != oAry.end(); c_oIt++ )
    {
        cout << *c_oIt << " ";
    }
    cout << endl;

    // 注意元素的安全
    for( oIt = oAry.begin(); oIt != oAry.end(); oIt++ )
    {
        delete (*oIt);
        *oIt = NULL;
    }

    cout << "the capacity is " << oAry.capacity() << endl ;
    
    for( c_oIt = oAry.begin(); c_oIt != oAry.end(); c_oIt++ )
    {
       cout << *c_oIt << " ";
    }
    cout << endl;

    //// 注意元素的安全
    oAry.clear();

	return 0;
}


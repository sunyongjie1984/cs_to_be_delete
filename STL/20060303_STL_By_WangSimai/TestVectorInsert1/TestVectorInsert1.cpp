 // TestVectorInsert1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
// 包含头文件 #include<vector>
#include <vector>

// 使用命名空间 using namespace std;
using namespace std;

// 定义自定义类型并用其创建实例 
typedef vector<int> IntArray_type;

int main(int argc, char* argv[])
{
	// 实例化向量
    IntArray_type Vecint_1;

	// 尽量使用std::vector中定义的类型定义变量并使用
	// 定义迭代器
    IntArray_type::const_iterator constIt = Vecint_1.begin();
    IntArray_type::iterator It = Vecint_1.begin();
    IntArray_type::iterator It1 = Vecint_1.begin();
	// 定义反向迭代器
    IntArray_type::reverse_iterator rIt = Vecint_1.rbegin(); 
	// 定义计数
    IntArray_type::size_type Vecint_1_sz = 10;
    IntArray_type::size_type Vecint_1_cnt = 0;
	// 定义元素类型变量
    IntArray_type::value_type Vecint_1_Val = 6;

	// 为vector<int>开辟的存储能力空间
    cout << "the capacity of Vecint_1 is " << Vecint_1.capacity() << endl;

	// 对向量赋值
    Vecint_1.assign( Vecint_1_sz, Vecint_1_Val );

	// 观察存储能力空间
    cout << "the capacity of Vecint_1 is " << Vecint_1.capacity() << endl;

	// 输出向量元素
	// 多使用迭代器进行数组元素的访问
    for ( constIt = Vecint_1.begin(); constIt != Vecint_1.end(); constIt++ )
    {
        cout << *constIt << " ";
    }
    cout << endl;

    Vecint_1_Val = 12345;

	// begin函数返回指向向量第一个元素的迭代器
    It = Vecint_1.begin();

	// 改变第一个元素的值。iterator可以改变元素的值
    *It = 1;
	// 移动指向的元素
    It = It+4;

    constIt = Vecint_1.begin();
	// const_iterator不能改变元素的值
	// *constIt = 5678;
    constIt++;
    
    // 插入值
    It1 = Vecint_1.insert( It+4, Vecint_1_Val );

    // back() 函数返回最后一个元素的引用 
    int& nback = Vecint_1.back();
    nback++;

	// back() 函数返回最后一个元素的const reference
    const int& ncback = Vecint_1.back();
//    ncback++;

	// front() 函数返回最后一个元素的引用
    int& nFront = Vecint_1.front();

	// size() 函数返回现有元素个数
    Vecint_1_cnt = Vecint_1.size();
	
	// 观察元素个数
    cout << "the count of elements int Vecint_1 is " << Vecint_1_cnt << endl;

	// 观察存储能力空间
    cout << "the capacity of Vecint_1 is " << Vecint_1.capacity() << endl;

	// 重新设定向量大小
    Vecint_1.resize( 6 );

	// 观察存储能力空间
    cout << "the capacity of Vecint_1 is " << Vecint_1.capacity() << endl;

	// 输出向量元素
	// 多使用迭代器进行数组元素的访问
    for ( constIt = Vecint_1.begin(); constIt != Vecint_1.end(); constIt++ )
    {
        cout << *constIt << " ";
    }
    cout << endl;
    cout << endl;

	// 反向输出向量元素
	// 多使用迭代器进行数组元素的访问
    for ( rIt = Vecint_1.rbegin(); rIt != Vecint_1.rend(); rIt++ )
    {
        cout << *rIt << " ";
    }
    cout << endl;
    cout << endl;

	// 清空向量
    Vecint_1.clear();

	// 观察元素个数
    Vecint_1_cnt = Vecint_1.size();
    cout << "After clear Vecint_1.size() = " << Vecint_1_cnt << endl;

	// 输出向量元素
	// 多使用迭代器进行数组元素的访问
    for ( constIt = Vecint_1.begin(); constIt != Vecint_1.end(); constIt++ )
    {
        cout << *constIt << " ";
    }
    cout << endl;

	// 观察存储能力空间
    cout << "the capacity of Vecint_1 is " << Vecint_1.capacity() << endl;

	// 设置保留空间
    Vecint_1.reserve( 21 );

	// 观察存储能力空间
    cout << "the capacity of Vecint_1 is " << Vecint_1.capacity() << endl;

	return 0;
}


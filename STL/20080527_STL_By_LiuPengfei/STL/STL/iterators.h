#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>

#include <functional>// greater需要
#include <fstream>
using namespace std;

inline void TestIterators()
{
    int ia[] = { 0, 1, 1, 2, 3, 5, 5, 8 };
    vector<int> ivec( ia, ia+8 );
    vector<int> vres;

    // reverse iterator
    vector<int>::reverse_iterator rIt = ivec.rbegin();//声明
    // 如果执行 rIt++, 实际效果等于ivec.back()--
    // 以升序排列 vector
    sort( ivec.begin(), ivec.end() );
    // 以降序排列vector
    sort( ivec.rbegin(), ivec.rend() );


    // insert iterator
    vector<int> vecInsert;
    back_insert_iterator<vector<int> > it( vecInsert );//初始化
    it = 3;// 将3插入vecInsert.

    // unique_copy() 现在用 vres.push_back() 插入
    // 将ivec中相邻重复元素剔除插入vres中
    unique_copy( ivec.begin(), ivec.end(), back_inserter( vres ));

    // Error, vector不提供push_front操作。
    // unique_copy( ivec.begin(), ivec.end(), front_inserter( vres ));
    
    // 将ivec中相邻重复元素剔除反向插入vres中
    unique_copy( ivec.begin(), ivec.end(), inserter( vres, vres.begin() ));

    // iostream iterator
    istream_iterator< int > input( cin );//初始化
    istream_iterator< int > end_of_stream;
    vector<int> vec;
    copy ( input, end_of_stream, inserter( vec, vec.begin() ));// 输入
    sort( vec.begin(), vec.end(), greater<int>() );// 从大到小排序
    ostream_iterator< int > output( cout, " " );
    unique_copy( vec.begin(), vec.end(), output );// 剔除相同元素并回显


    // 读入标准输入并回显
    copy( istream_iterator< int >( cin ),
            istream_iterator< int >(),
            ostream_iterator< int >( cout ));
}
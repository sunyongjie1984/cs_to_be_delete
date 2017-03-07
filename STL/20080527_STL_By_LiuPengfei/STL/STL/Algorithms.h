#include <algorithm>
#include <vector>
#include <list>
#include <functional>
#include <iostream>
#include <numeric>
using namespace std;
template< class Type >
void printElem( Type t){ cout << t << " ";};

//查找算法
void TestSearch( vector<int> &ivec )
{
    // 查找算法find and find_if
    // 查找第一个等于2的元素
    vector<int>::iterator it = find( ivec.begin(), ivec.end(), 2 );
    // 查找最后一个等于2的元素
    vector<int>::reverse_iterator rit = find( ivec.rbegin(), ivec.rend(), 2 );
    // 查找第一个大于3的元素
    it = find_if( ivec.begin(), ivec.end(),
        bind2nd( greater<int>(), 3));
    // 查找第一个大于3，小于8，且能被5整除的元素
    //     it = find_if( ivec.begin(), ivec.end(), 
    //         compose2( logical_and<bool>(),
    //                   compose2( logical_and<bool>(),
    //                             bind2nd( greater<int>(),3),
    //                             bind2nd( less<int>(), 8) ),
    //                   not2(bind2nd( modulus<int>(), 5 )))));
    
    // 查找第一个能被5整除的元素
    it = find_if( ivec.begin(), ivec.end(), not1( bind2nd( modulus<int>(), 5 )));
    if ( it != ivec.end())
    {
        int nPos = it - ivec.begin() + 1;
        cout << "The found value moduled by 5 is " << *it
            << " Position " << nPos << endl;
    }
}
// 排序算法
void TestSort( vector<int> &ivec )
{
    sort( ivec.begin(), ivec.end());// 从小到大排列
    cout << "After sort by less: ";
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    sort( ivec.begin(), ivec.end(), greater<int>());// 从大到小排列
    cout << "After sort by greater: ";
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    sort( ivec.rbegin(), ivec.rend());// 从大到小排列，注意于上一算法的区别
    partial_sort( ivec.begin(), ivec.begin()+5, ivec.end());// 排出最小的5个，其余不管
    cout << "After sort by partial_sort: ";
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    // 以第5个元素为分界，小于的排左边，大于等于的排右边，可以和find联合使用
    nth_element( ivec.begin(), ivec.begin()+4, ivec.end());
    cout << "After nth_element: ";
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

// 删除于替换算法
void TestDeleteAndReplace( vector<int> &ivec )
{
    vector<int>::iterator it = remove( ivec.begin(), ivec.end(), 5 );// 删除所有等于5的元素
    // 注意，不是真的删除，而是将要删除的元素放在it之后，
    // 并且会改变原有的值,所以一般需要再调用earse函数
    // 将大于5的元素删除
    cout << "after remove :";
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    it = remove_if( ivec.begin(), ivec.end(), bind2nd(greater<int>(), 5));
    cout << "after remove_if:";
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    it = unique( ivec.begin(), ivec.end() );// 剔除相邻重复的元素
    // 注意事项同remove, 不是真的删除, 并且会改变原有的值，也需要和earse联合使用
    cout << "after unique :";
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

// 排列组合算法
void TestPermutation( vector<int> &ivec )
{
    while ( next_permutation( ivec.begin(), ivec.begin()+3 ))
    {
        copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
}
// 数值算法
void TestNumeric( vector<int> &ivec )
{
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    int nSum = accumulate( ivec.begin(), ivec.end(), 0 );
    cout << " The sum is " << nSum << endl;
}
// 生成与异变算法
void TestGenerateAndTransform( vector<int> &ivec, int* ia )
{
    void( *pif)(int) = printElem;
    cout << "after for_each:";
    for_each( ivec.begin(), ivec.end(), pif );// 打印所有元素
    cout << endl;
    // 将所有元素+1
    cout << "after transform for increase element by 1:";
    transform( ivec.begin(), ivec.end(), ivec.begin(), bind2nd(plus<int>(), 1));
    for_each( ivec.begin(), ivec.end(), pif );
    cout << endl;
    // 将两个数组相加后存到第一个数组中
    cout << "after transform for plus the elements of two vectors:";
    transform( ivec.begin(), ivec.end(), ia, ivec.begin(), plus<int>());
    for_each( ivec.begin(), ivec.end(), pif );
    cout << endl;
}
// 关系算法
void TestRelation( vector<int> &ivec )
{
    vector<int>::iterator it = max_element( ivec.begin(), ivec.end());
    cout << "max is " << *it << " position " << it-ivec.begin()+1 << endl;
    sort( ivec.begin(), ivec.end());
    cout << "after sort: ";
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    //查找能够插入5而不会破坏排序的位置
    int nInsertNum = 4;
    it = lower_bound( ivec.begin(), ivec.end(), nInsertNum );
    cout << "Lower_bound ";
    cout << "found the insert position of " << nInsertNum<<" is " << it - ivec.begin();
    cout << endl;
}
// 堆算法
void TestSet( vector<int> &ivec, int* ia )
{
    vector<int> vecUninRes;
    for ( int i =0; i < ivec.size(); i++)
    {
        *(ia+i) = i;
    }
    cout << "another array is: ";
    copy( ia, ia+ivec.size(), ostream_iterator<int>(cout, " "));
    cout << endl;
    set_union( ivec.begin(), ivec.end(), ia, ia + 8, back_inserter( vecUninRes ));
    cout << "after set_union: ";
    copy( vecUninRes.begin(), vecUninRes.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    vector<int> vecDifRes;
    set_difference( ivec.begin(), ivec.end(), ia, ia+8, back_inserter( vecDifRes ));
    cout << "after set_difference: ";
    copy( vecDifRes.begin(), vecDifRes.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

void TestHeap( vector<int> &ivec )
{
    make_heap( ivec.begin(), ivec.end());// 创建堆
    cout << "after make_heap: ";
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    ivec.push_back( 4 );
    push_heap( ivec.begin(), ivec.end());
    cout << "after push_heap: ";
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

inline void TestAlgorithms()
{
    int ia[] = { 1, 0, 5, 2, 3, 1, 5, 8 };
    vector<int> ivec( ia, ia+8 );
    cout << "The initial vector is ";
    copy( ivec.begin(), ivec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    
//     TestSearch(ivec);//查找算法    
//     TestSort(ivec);// 排序算法    
//     TestDeleteAndReplace(ivec);// 删除和替换算法    
//     TestPermutation(ivec);// 排列组合算法    
//     TestNumeric(ivec);// 算术算法    
//     TestGenerateAndTransform( ivec, ia );// 生成和异变算法    
//     TestRelation(ivec);// 关系算法    
//     TestSet(ivec, ia);// 集合算法   
//     TestHeap(ivec); // 堆算法   
}
#include <iostream>
using namespace std;
void SelectSort(int* const a, int n)
{
    int i, j, k;
    for (i=0; i<n-1; i++) // 选择第 i 小的记录，并交换到位
    {
        j = i;
        for (k=i+1; k<=n-1; k++) // 在a[i..n-1]中选择关键字最小的记录
        {
            if (a[k]<a[j])
            {
                j=k; // "<"变">"变为 反向排序
            }
        }
        if (i!=j)
        {
            swap(a[i], a[j]); //与第 i 个记录互换
        }
    }
}
int main()
{
    int a[] = { 20, 50, 40, 30, 80, 70 };
    int n=sizeof(a)/sizeof(int);
    SelectSort(a ,n);
    for ( int i=0; i<n; i++)
    {
        cout<<a[i]<<endl;
    }
    return 0;
}

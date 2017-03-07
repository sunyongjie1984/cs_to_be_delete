#include <iostream>
// 数组为a[0],a[1].....a[p],a[p+1],a[p+2]....a[q]..a[r],a[r+1]......;
// 一共进来七次
// first a[0],a[1] then a[2],a[3],
// then  a[0]~a[3]
// then  a[4],a[5], then a[6],a[7]
// then  a[4]~a[7]
// then  a[0]~a[7].
void merge(int* const a, int const p, int const q, int const r)
{   // 第一次到这个函数时，p==0，q==0，r==1，把这个由二个元素组成的数组看作是由两个已经排序的大小为1的数组组成	
    // a[0]==5,a[1]==2
    for (int i = p; i < p + (r - p + 1); ++i)
    {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
    int n1 =q - p + 1; // 因为把下标为q的元素分到了第一个数组中，所以n1为q-p+1
    int n2 =r - q;
    int* L =new int[n1 + 1]; // 多一个元素用来放哨兵
    int* R =new int[n2 + 1];
    for (int i = 0; i < n1; ++i)
        L[i] = a[p + i];
    for (int j = 0; j < n2; ++j)
        R[j] = a[q + j + 1];
    // L[n1]=1024*1024*1024*2-1; // 2^31-1次方，在这里编译器有警告是不是说，这个整型字面值1024*1024*1024*2
    // R[n2]=1024*1024*1024*2-1; // 编译器是由一个字表示的，所以这里就已经越界了，我不晓得了。那我这样表示应该就可以了。
    L[n1] = 1024 * 1024 * 1024 - 1 + 1024 * 1024 * 1024; // 这样果然不警告了。
    R[n2] = 1024 * 1024 * 1024 - 1 + 1024 * 1024 * 1024;
    int i = 0;
    int j = 0;
    for (int k = p; k <= r; ++k)
    {
        if (L[i] <= R[j])
        {
            a[k] = L[i];
            ++i;
        }
        else
        {
            a[k] = R[j];
            ++j;
        }
    }
    for (int i = p; i < p + (r - p + 1); ++i)
    {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

void merge_sort(int* a, int const p, int const r)
{
    if (p < r)
    {
        int q = (p + r) / 2;
        merge_sort(a, p, q);   // 第一次，从这里开始了对a[0],a[1],a[2],a[3]的devide
        // 第二次，从这里开始了对a[0],a[1]的devide。
        // 第三次，从这里开始了对a[0],a[0]devede,进入merge_sort后直接退出，
        // 然后第一次进入了merge_sort(a, q+1, r)这个语句。
        merge_sort(a, q + 1, r); // first time，从这里开始了对a[1],a[1]的devide,进入merge_sort后直接退出，
        // 相当于对a[0],a[1]这个数组的devide过程已经结束，也可以说merge_sort相邻的两个元素时可以开始merge的过程了。

        merge(a, p, q, r);	   // 这个过程是merge(a, 0, 0, 1);将这个由两个元素的大数组当成两个数组开始merge。
        // 之后应该是对a[2],a[3]的devide过程，进入merge_sort(a, q+1, r)实施。
        // 这个过程首先由merge_sort(a, p, q)devide,a[2],a[2]直接退出后，由
        // merge_sort(a, q+1, r)来完成devide,a[3],a[3]直接退出后，进入a[2],a[3]
        // 的过程。
        // 再然后就是merge,a[0],a[1],a[2],a[3]的过程。过个函数结束，也就是栈
        // 返回到第一次进入merge_sort(a, p, q)的地方。然后开始devide,
        // a[4],a[5],a[6],a[7]然后开始devide,a[4],a[5],devide,a[4],a[4],
        // devide,a[5],a[5].merge,a[4],a[5],devide,a[6],a[7],devide,a[6],a[6]
        // devide,a[7],a[7],merge,a[6],a[7],merge,a[4],a[5],a[6],a[7],
        // merge,a[0~7]结束。
    }
}
int main()
{
    int a[10] = { 2, 5, 3, 8, 1, 4, 23, 2, 123, 4 };
    std::cout << "before sort" << std::endl;
    for (int i = 0; i < 10; ++i)
    {
        std::cout << a[i] << " ";
    }
    std::cout << "\n" << std::endl;
    merge_sort(a, 0, 9);
    std::cout << "\nafter sort" << std::endl;
    for (int i = 0; i < 10; ++i)
    {
        std::cout << a[i] << " ";
    }
    std::cout << "\n" << std::endl;

    int b[8] = { 5, 2, 4, 7, 1, 3, 2, 6 };
    std::cout << "before sort" << std::endl;
    for (int i = 0; i < 8; ++i)
    {
        std::cout << b[i] << " ";
    }
    std::cout << "\n" << std::endl;
    merge_sort(b, 0, 7);
    std::cout << "\nafter sort" << std::endl;
    for (int i = 0; i < 8; ++i)
    {
        std::cout << b[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}

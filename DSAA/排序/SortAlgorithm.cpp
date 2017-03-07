#include <iostream>
using namespace std;
void print(int*, int);
void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}
// Bubble
void Bubble(int* const a, int n)
{
    int i, j;
    for (i = 0; i < n-1; i++) // i < n-1 (即:10个数只循环9趟)
        for (j = 0; j < n-1-i; j++) // j< n-1-i (即:10个数只作9-i次交换)
        {
            if (a[j] > a[j+1]) // 调整> 变成 由大到小
            {
                swap(a[j], a[j+1]);
            }
        }
}
// Quick Sort
int Partition(int* const a, int low, int high)
{
    int rc = a[low];
    int pivot = a[low];
    while (low < high)
    {
        while (low < high && a[high] <= pivot) --high; // 调整>= 变成 反向排序
        a[low] = a[high];

        while (low < high && a[low] >= pivot) ++low; // 调整<= 变成 反向排序
        a[high] = a[low];
    }
    a[low] = rc;
    return low;
}

void QSort(int* const a, int low, int high)
{
    if (low < high)
    {
        int pivot = Partition(a, low, high); // cout << "Pivot:" << pivot << '\t';
        QSort(a, low, pivot-1);
        QSort(a, pivot+1, high);
    }
}

void QuickSort(int* const a, int n)
{
    QSort(a, 0, n-1);
}

void SelectSort(int* const a, int n)
{
    int i, j, k; // 下面到底应该是<还是<=呢？
    for (i = 0; i < n-1; i++) // 选择第 i 小的记录，并交换到位
    {
        j = i;
        for (k = i+1; k <= n-1; k++) // 在a[i..n-1]中选择关键字最小的记录
        {
            if (a[k] < a[j]) j = k; // "<"变">"变为 反向排序
        }
        if (i != j) 
        {
            swap(a[i], a[j]); //与第 i 个记录互换
        }
    }
}

// Heap Sort
void HeapAdjust(int* const a, int s, int m)
{
    // 已知a[s..m]中，除了a[s]之外，均满足堆定义
    // 本函数调整a[s]，使其成为一个大顶堆
    int i = 0;
    int rc = a[s];
    for (i = 2 * s; i <= m; i *= 2) // 沿key值较大的孩子节点向下筛选
    {
        // 小顶堆, 将下面两个语句的>好更改后，变为大顶堆
        if (i < m && (a[i] > a[i+1])) i++; // j为关键字较小的记录的下标
        if (rc <= a[i]) break; 
        a[i / 2] = a[i]; //节点j 上提,放在其的父节点上
    }
    a[i / 2] = rc; // 插入
}

void BuildHeap(int* const a, int n)
{
    // a[0..n-1]建成堆
    // 从数组最后一个元素开始向前建立堆
    int i = 0;

    for (i = n-2; i >= 0; i--)
    {
        HeapAdjust(a, i, n-1);
    }
}

void HeapSort(int* const a, int n)
{
    // a[0..n-1]
    int i = 0;
    BuildHeap(a, n);

    swap(a[0], a[n-1]); // 互换"堆顶"和"堆底"的记录
    for (i = n-2; i >= 0; i--)
    {
        HeapAdjust(a, 0, i); // 从根开始调整，将 a[1..i] 重新调整为大顶堆
        swap(a[0], a[i]); // 互换"堆顶"和当前的"堆底"，使已有序的记录沉积在底部
    }
}

int main()
{
    int a[] = {56, 49, 65, 97, 100, 76, 60, 300, 13, 9};
    int n = sizeof(a) / sizeof(int);
    cout << n << "numbers:" << endl;
    print(a, n);
    cout << "--------------------------------------" << endl;
    // Bubble Sort:
    cout << "Bubble:" << endl ; 
    Bubble(a, n);
    print(a, n);
    // Quick Sort:
    cout << "Quick Sort:" << endl; 
    QuickSort(a, n);
    print(a, n);
    // Select Sort:
    cout << "Select Sort:" << endl; 
    SelectSort(a, n);
    print(a, n);
    // Heap Sort:
    cout << "Heap Sort:" << endl; 
    HeapSort(a, n);
    print(a, n);
    cout << endl <<"---------------------------------------" << endl;
    cout << "GCD:" << endl;
    cout << GCD(a[0], a[1]) << endl;
    cout << GCD1(a[0], a[1]) << endl;

    return 0;
}

void print(int* const a, int n)
{
    int i = 0;
    while (i < n)
    {
        cout << a[i] << '\t';
        i++;
    }
    cout << endl;
}

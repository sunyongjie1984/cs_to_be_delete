#include <stdio.h>
#include <stdlib.h>

void HeapSort(int num[], int size);
void BuildHeap(int num[], int size);
void PercolateDown(int num[] , int index, int size);
void PrintHeap(const char* strMsg, int array[], int nLength);
void Swap(int num[] , int v, int u);

int main(int argc, char *argv[])
{
    /* 将数组看成完全二叉树的中序遍历结果的线性存储 */
    int data[13]={8, 5, 4, 6, 13, 7, 2, 9, 12, 11, 3, 10, 1};
    HeapSort(data, 13);

    system("PAUSE");
    return 0;
}


void HeapSort(int num[] ,int size)
{
    int i;
    int iLength = size;

    PrintHeap("Befor Sort:", num, iLength);

    BuildHeap(num, size);           // 建立小顶堆

    for (i = iLength - 1; i >= 1; i--)
    {
        Swap(num, 0, i);            // 交换
        size--;                     // 每交换一次让规模减少一次
        PercolateDown(num, 0, size); // 将新的首元素下滤操作
        PrintHeap("Sort Heap:", num, iLength);
    }
}

/* 建堆方法，只需线性时间建好；
   建堆的结果：数组的第一个元素（即树根）是所有元素中的最小值，索引小于等于size/2-1的其它元素（即其它非叶子节点）的值都是其所在子树的最小值 */   
void BuildHeap(int num[] ,int size)
{
    int i;
    // 从最后一个非叶子节点开始，对每个非叶子节点进型最小根调整，保证每个根节点都是其子树中的最小值
    for (i = size / 2 - 1; i >= 0; i--)
    {
        PercolateDown(num, i, size); // 进行下滤操作
        PrintHeap("Build heap:", num, size);
    }
}

/* 对该数进行下滤操作，直到该数比左右节点都小就停止下滤。
   即对某个根节点的值进行位置下降调整，使该值比其左右子节点都小；
   若该节点是叶子节点，则无法while循环 */
void PercolateDown(int num[] , int index, int size)
{
    int min;// 设置最小指向下标
    while (index * 2 + 1 < size)
    {   // 如果该数有左节点，则假设左节点最小
        min = index * 2 + 1;// 获取左节点的下标
        if (index * 2 + 2 < size)
        {   // 如果该数还有右节点
            if (num[min] > num[index * 2 + 2])
            {   // 就和左节点分出最小者
                min = index * 2 + 2;// 此时右节点更小，则更新min的指向下标   
            }
        }
        // 此时进行该数和最小者进行比较，
        if (num[index] < num[min])
        {   // 如果index最小，
            break; // 停止下滤操作
        }
        else
        {
            Swap(num, index, min); // 交换两个数，让大数往下沉
            index = min; // 更新index的指向
        }
    }// while
}

// 给定数组交换两个数的位置
void Swap(int num[] , int v, int u)
{
    int temp = num[v];
    num[v] = num[u];
    num[u] = temp;
}

void PrintHeap(const char* strMsg, int array[], int nLength)
{
    int i;
    printf("%s", strMsg);
    for(i = 0;i < nLength; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

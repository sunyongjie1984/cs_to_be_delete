#include <iostream>
using namespace std;
class MergeSort {
public:
    //构造函数
    MergeSort(int length)
    {
        this->length=length;
        arr=new int[length+1];
        temp=new int[length+1];
        num=0;
    }
    //归并排序递归定义算法
    void mergeSort(int start,int end)
    {
        int middle;
        if(start<end)
        {
            middle=(start+end)/2;
            mergeSort(start,middle);
            mergeSort(middle+1,end);
            merge(start,middle,end);
        }
    }
    //合并算法
    void merge(int start,int middle,int end)
    {
        int i=start;
        int j=middle+1;
        int k=start;
        copy(start,end); //拷贝arr[start:end]给temp[start:end]
        while(i<=middle&&j<=end)
        {
            if(temp[i]<=temp[j])
            {
                arr[k++]=temp[i++];
            }
            else
            {
                arr[k++]=temp[j++];
                num+=middle-i+1; //逆序对记录 ，因为如果arr[i]>arr[j],因为arr[start:middle]已好序呈递增状态，所以arr[i:middle]均大于arr[j],所以有middle-i+1个逆序对
            }
        }
        while(i<=middle)
        {
            arr[k++]=temp[i++];
        }

        while(j<=end)
        {
            arr[k++]=temp[j++];
        }
    }
    //拷贝数组
    void copy(int start,int end)
    {
        while(start<=end)
        {
            temp[start]=arr[start];
            start++;
        }
    }
    //输入数据函数
    void input()
    {
        int i=1;
        while(i<=length)
        {
            cin>>arr[i++];
        }
    }
    //输出数组排序结果
    void display()
    {
        int i=1;
        while(i<=length)
        {
            cout<<arr[i++]<<" ";
        }
    }
private:
    int *arr;    //待排序数组
    int *temp;   //临时记录数组
    int length;  //数组长度
    int num;     //逆序对数量
};

void main()
{
    MergeSort test(10);   //实例化对象
    test.input();         //输入数据
    test.mergeSort(1,10); //将1-10，共10个数据进行排序
    test.display();      //打印排序后结果
}


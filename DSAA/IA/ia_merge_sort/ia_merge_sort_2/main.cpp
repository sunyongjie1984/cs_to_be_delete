#include<iostream>
using namespace std;
template<class T>void MergeSort(T a[], int left, int right);
template<class T>void Merge(T c[], T d[], int l, int m, int r);
template<class T>void Copy(T a[], T b[], int l, int r);

int main()
{
    int const n(5);
    int a[n];
    cout<<"Input "<<n<<" numbers please:";
    for(int i=0; i<n; i++)
        cin>>a[i];
    MergeSort(a, 0, n-1);
    cout<<"The sorted array is"<<endl;
    for(int i=0; i<n; i++)
        cout<<a[i]<<" ";
    cout<<endl;

    return 0;
}

template<class T>
void MergeSort(T a[], int left, int right)
{
    if(left<right)
    {
        int i=(right+left)/2;
        T *b=new T();    // I have doubt about this program
        // T *b=new T[]; // I have no idea why in the 
        MergeSort(a, left, i);
        MergeSort(a, i+1, right);
        Merge(a, b, left, i, right);
        Copy(a, b, left, right);
    }
}

template<class T>
void Merge(T c[], T d[], int l, int m, int r)
{
    int i=l, j= m+1, k=l;
    while (i<=m&&j<=r)
    {
        if(c[i]<=c[j])d[k++]=c[i++];
        else d[k++]=c[j++];
    }
    if (i>m)
    {
        for (int q=j; q<=r; q++)
            d[k++]=c[q];
    }
    else
        for (int q=i; q<=m; q++)
            d[k++]=c[q];
}

template<class T>
void Copy(T a[], T b[], int l, int r)
{
    for (int i=l; i<=r; i++)
        a[i]=b[i];
}

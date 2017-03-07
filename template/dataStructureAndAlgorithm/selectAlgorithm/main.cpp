#include <iostream>
using namespace std;
template<class Type> void SelectSort(Type* const a, int n)
{
    int i, j, k;
    for (i = 0; i < n - 1; i++)
    {
        j = i;
        for (k = i + 1; k <= n - 1; k++)
        {
            if (a[k] < a[j]) j = k;
        }
        if (i != j)
        {
            swap(a[i], a[j]);
        }
    }
}
int main()
{
    int a[] = { 20, 50, 40, 30, 80, 70 };
    int n = sizeof(a) / sizeof(int);
    SelectSort(a , n);
    for ( int i = 0; i < n; i++)
    {
        cout << a[i] << ' ';
    }
	cout << endl;
    return 0;
}

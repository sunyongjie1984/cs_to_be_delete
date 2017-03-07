#include <iostream>
using namespace std;
void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}
void print(int* const a, int n)
{
    for (int i = 0; i <= n - 1; i++)
        cout << a[i] << '\t';
}
void maopao(int* const a, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - 1 - i; j++)
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
}
int main()
{
    int a[] = { 13, 26, 8, 49, 300, 36 };
    cout << "The numbers before sorted:" << endl;
    int n = sizeof(a) / sizeof(int);
    for (int i = 0; i <= n - 1; i++)
        cout << a[i] << '\t';
    cout << endl;
    maopao(a, n);
    cout << endl << "The numbers after sorted:" << endl;
    print(a, n);
    cout << "\n\n";
    return 0;
}

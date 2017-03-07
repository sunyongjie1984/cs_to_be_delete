#include <iostream>
#include <string>
using namespace std;
template<class Type> void mySwap(Type& a, Type& b)
{
    Type temp = a;
    a = b;
    b = temp;
}
template<class Type> void print(Type* const a, int n)
{
    for (int i = 0; i <= n-1; i++)
	{
        cout << a[i] << ' ';
	}
}
template<class Type> void maopao(Type* const a, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
	{
        for (j = 0; j < n - 1 - i; j++)
		{
            if (a[j] > a[j+1])
			{
                mySwap(a[j], a[j + 1]);
			}
		}
	}
}
int main()
{
    int a[] = { 13, 26, 8, 49, 300, 36 };
    cout << "The numbers before sorted:" << endl;
    int n = sizeof(a) / sizeof(int);
    for (int i = 0; i <= n - 1; i++)
        cout << a[i] << ' ';
    cout << endl;
    maopao(a, n);
    cout << endl << "The numbers after sorted:" << endl;
    print(a, n);
    cout << "\n\n";
	
    string b[] = { "book", "about", "door", "children" };
    cout << "The strings before sorted:" << endl;
    n = sizeof(b) / sizeof(int);
    for (int i = 0; i <= n - 1; i++)
        cout << b[i] << ' ';
    cout << endl;
    maopao(b, n);
    cout << endl << "The strings after sorted:" << endl;
    print(b, n);
    cout << endl;

    return 0;
}

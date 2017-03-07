#include <iostream>
#include <string.h>
using namespace std;
class CIntMergeSort {
public:
    CIntMergeSort(const int& iLength) : length(iLength)
    {
        // length = iLength;
        pI = new(std::nothrow) int[iLength];
        // pI = new int[iLength];
        if (NULL == pI)
        {
            // error bad alloc
        }
        memset(pI, 0, iLength * 4);
    }
    ~CIntMergeSort()
    {
        delete[] pI;
    }
    friend istream& operator>>(istream& is, CIntMergeSort& object)
    {
        int i = 0;
        int j = 0;
        int* q = object.pI;
        //while (i++ != object.length)
        //{
        //    is >> j;
        //    *q++ = j;
        //}
        while ((i++ != object.length) && (is >> j))
        {
            *q++ = j;
        }
        if (i != object.length + 1)
        {
            cout << "error bad int istream, reinput" << endl;
            memset(object.pI, 0, object.length * 4);
            is.clear();
            is.sync();
            is >> object;
            return is;
        }
        object.merge_sort(0, object.length - 1);
        return is;
    }
    friend ostream& operator<<(ostream& os, const CIntMergeSort& object)
    {
        const int* q = object.pI;
        for (int i = 0; i != object.length; i++)
        {
            os << *q++ << " ";
        }
        os << endl;
        return os;
    }
private:
    void merge(int p, int q, int r)
    {
        int n1 = q - p + 1;
        int n2 = r - q;
        int* L = new int[n1 + 1];
        int* R = new int[n2 + 1];
        for (int i = 0; i < n1; ++i)
            L[i] = pI[p + i];
        for (int j = 0; j < n2; ++j)
            R[j] = pI[q + j + 1];
        int i = 0;
        int j = 0;
        for (int k = p; k <= r; k++)
        {
            if (i == n1)
            {
                while (j < n2)
                {
                    pI[k++] = R[j++];
                }
                return;
            }
            if (j == n2)
            {
                while (i < n1)
                {
                    pI[k++] = L[i++];
                }
                return;
            }
            if (L[i] <= R[j])
            {
                pI[k] = L[i++];
            }
            else
            {
                pI[k] = R[j++];
            }
        }
        delete[] L;
        delete[] R;
    }
    void merge_sort(int p, int r)
    {
        if (p<r)
        {
            int q=(p + r) / 2;
            merge_sort(p, q);
            merge_sort(q + 1, r);
            merge(p, q, r);
        }
    }
private:
    int* pI;
    int const length;
};
int main()
{
    unsigned int num_to_be_sort;
    cout << "input how many numbers to be sort?" << endl;
    std::cin >> num_to_be_sort;
    unsigned int const n = num_to_be_sort;
    CIntMergeSort a(n); // how many numbers to be sorted?
    cout << "input these numbers" << endl;
    cin >> a;           // input the numbers
    cout << "these numbers after sorted" << endl;
    cout << a;          // output the sorted numbers
    return 0;
}


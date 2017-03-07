//************************  sorts.h  ***************************
//                 Generic sorting algorithms
//               overloading of < and = required

//conflict with <algorithms>, <queue>
//template<class T>
//inline void swap (T& e1, T& e2) {
//    T tmp = e1; e1 = e2; e2 = tmp;
//}

template<class T>
void insertionsort(T data[], int n) {
    for (int i = 1, j; i < n; i++) {
        T tmp = data[i];
        for (j = i; j > 0 && tmp < data[j-1]; j--)
            data[j] = data[j-1];
        data[j] = tmp;
    }
}

template<class T>
void selectionsort(T data[], int n) {
    for (int i = 0, least, j; i < n-1; i++) {
        for (j = i+1, least = i; j < n; j++)
            if (data[j] < data[least])
                least = j;
        swap(data[least],data[i]);
    }
}

template<class T>
void bubblesort(T data[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = n-1; j > i; --j)
            if (data[j] < data[j-1])
                swap(data[j],data[j-1]);
}

template<class T>
void ShellSort(T data[], int arrSize) {
    register int i, j, hCnt, h;
    int increments[20], k;
//  create an appropriate number of increments h
    for (h = 1, i = 0; h < arrSize; i++) {
        increments[i] = h;
        h = 3*h + 1;
    }
 // loop on the number of different increments h
    for (i--; i >= 0; i--) {
        h = increments[i];
     // loop on the number of subarrays h-sorted in ith pass
        for (hCnt = h; hCnt<2*h; hCnt++) {
         // insertion sort for subarray containing every hth element of array data
            for (j = hCnt; j < arrSize; ) {
                T tmp = data[j];
                k = j;
                while (k-h >= 0 && tmp < data[k-h]) {
                    data[k] = data[k-h];
                    k -= h;
                }
                data[k] = tmp;
                j += h;
            }
        }
    }
}

template<class T>
void moveDown (T data[], int first, int last) {
    int largest = 2*first + 1;
    while (largest <= last) {
        if (largest < last && // first has two children (at 2*first+1 and
            data[largest] < data[largest+1]) // 2*first+2) and the second
             largest++;                      // is larger than the first;

        if (data[first] < data[largest]) {   // if necessary,
             swap(data[first],data[largest]);// swap child and parent,
             first = largest;                // and move down;
             largest = 2*first+1;
        }
        else largest = last+1;  // to exit the loop: the heap property
    }                           // isn't violated by data[first];
}

template<class T>
void heapsort(T data[], int size) {
    int i;
    for (i = size/2 - 1; i >= 0; --i)   // create the heap;
        moveDown (data,i,size-1);
    for (i = size-1; i >= 1; --i) {
        swap(data[0],data[i]); // move the largest item to data[i];
        moveDown(data,0,i-1);  // restore the heap property;
    }
}

template<class T>
void quicksort(T data[], int first, int last) {
    int lower = first+1, upper = last;
    swap(data[first],data[(first+last)/2]);
    T bound = data[first];
    while (lower <= upper) {
        while (data[lower] < bound)
             lower++;
        while (bound < data[upper])
             upper--;
        if (lower < upper)
             swap(data[lower++],data[upper--]);
        else lower++;
    }
    swap(data[upper],data[first]);
    if (first < upper-1)
        quicksort (data,first,upper-1);
    if (upper+1 < last)
        quicksort (data,upper+1,last);
}

template<class T>
void quicksort(T data[], int n) {
    int i, max;
    if (n < 2)
        return;
    for (i = 1, max = 0; i < n; i++)// find the largest
        if (data[max] < data[i])    // element and put it
            max = i;                // at the end of data[];
    swap(data[n-1],data[max]); // largest el is now in its
    quicksort(data,0,n-2);     // final position;
}

template<class T>
void merge(T array1[], int first, int last) {
    int mid = (first + last) / 2;
    int i1 = 0, i2 = first, i3 = mid + 1;
    while (i2 <= mid && i3 <= last)
        if (array1[i2] < array1[i3])
             temp[i1++] = array1[i2++];
        else temp[i1++] = array1[i3++];
    while (i2 <= mid)
        temp[i1++] = array1[i2++];
    while (i3 <= last)
        temp[i1++] = array1[i3++];
    for (i1 = 0, i2 = first; i2 <= last; array1[i2++] = temp[i1++]);
}

template<class T>
void mergesort(T data[], int first, int last) {
    if (first < last) {
        int mid = (first + last) / 2;
        mergesort (data, first, mid);
        mergesort (data, mid+1, last);
        merge (data, first, last);
    }
}

#include <queue>
#include <stack>

using namespace std;

template<class T>
class Queue : public queue<T> {
public:
    T dequeue() {
        T tmp = front();
        queue<T>::pop();
        return tmp;
    }
    void enqueue(const T& el) {
        push(el);
    }
};

template<class T>
void radixsort(T data[], int n) {
    register int i, j, k, factor;
    const int radix = 10;
    const int digits = 5;
    Queue<T> queues[radix];
    for (i = 0, factor = 1; i < digits; factor *= radix, i++) {
        for (j = 0; j < n; j++)
            queues[(data[j] / factor) % radix].enqueue(data[j]);
        for (j = k = 0; j < radix; j++)
            while (!queues[j].empty())
                 data[k++] = queues[j].dequeue();
    }
}

template<class T>
void bitRadixsort(T data[], int n) {
    register int i, j, k, mask = 1;
    const int bits = sizeof(T)*8;
    Queue<T> queues[2];
    for (i = 0; i < bits; i++) {
        for (j = 0; j < n; j++)
            queues[data[j] & mask ? 1 : 0].enqueue(data[j]);
        mask <<= 1;
        k = 0;
        while (!queues[0].empty())
            data[k++] = queues[0].dequeue();
        while (!queues[1].empty())
            data[k++] = queues[1].dequeue();
   }
}

void inline clear(int& q) {
    q = -1;
}
int inline isEmpty(int q) {
    return q == -1;
}

template<class T>
class RadixSortNode {
public:
    T *arr;
    RadixSortNode *next;
};

template<class T>
void radixsort2(T data[], int n) {
    register int d, j, k, factor, where;
    const int radix = 10;
    const int digits = 5;
    RadixSortNode<T> n1, n2, *p1, *p2;
    n1.arr = data;
    n2.arr = new T[n];
    for (j = 0; j < n; j++)
        n2.arr[j] = data[j];
    int *queue = new int[n], queueHeads[radix], queueTails[radix];
    p1 = n2.next = &n1;
    p2 = n1.next = &n2;
    for (d = 0, factor = 1; d < digits; factor *= radix, d++) {
        for (j = 0; j < radix; j++)
            clear(queueHeads[j]);
        for (j = 0; j < n; j++) {
            where = (p1->arr[j] / factor) % radix;
            if (isEmpty(queueHeads[where]))
                 queueTails[where] = queueHeads[where] = j;
            else {
                 queue[queueTails[where]] = j;
                 queueTails[where] = j;
            }
        }
        for (j = 0; j < radix; j++)
            if (!(isEmpty(queueHeads[j])))
                 clear(queue[queueTails[j]]);
        for (j = k = 0; j < radix; j++)
            while (!(isEmpty(queueHeads[j]))) {
                 p2->arr[k++] = p1->arr[queueHeads[j]];
                 queueHeads[j] = queue[queueHeads[j]];
            }
        p2 = p2->next;
        p1 = p1->next;
    }
    if (digits % 2 != 0) // if digits is an odd number;
        for (d = 0; d < n; d++)
            data[d] = p1->arr[d];
}

template<class T>
void bitRadixsort2(T data[], int n) {
    register int d, j, k, where, mask = 1;
    const int radix = 10;
    const int digits = 5;
    const int bits = sizeof(T)*8;
    RadixSortNode<T> n1, n2, *p1, *p2;
    n1.arr = data;
    n2.arr = new T[n];
    for (j = 0; j < n; j++)
        n2.arr[j] = data[j];
    int *queue = new int[n], queueHeads[radix], queueTails[radix];
    p1 = n2.next = &n1;
    p2 = n1.next = &n2;
    for (d = 0; d < bits; d++, mask <<= 1) {
        clear(queueHeads[0]);
        clear(queueHeads[1]);
        for (j = 0; j < n; j++) {
            where = p1->arr[j] & mask ? 1 : 0;
            if (isEmpty(queueHeads[where]))
                 queueTails[where] = queueHeads[where] = j;
            else {
                 queue[queueTails[where]] = j;
                 queueTails[where] = j;
            }
        }
        for (j = 0; j < 2; j++)
            if (!(isEmpty(queueHeads[j])))
                 clear(queue[queueTails[j]]);
        for (j = k = 0; j < 2; j++)
            while (!(isEmpty(queueHeads[j]))) {
                 p2->arr[k++] = p1->arr[queueHeads[j]];
                 queueHeads[j] = queue[queueHeads[j]];
            }
        p2 = p2->next;
        p1 = p1->next;
    }
    if (digits % 2 != 0) // if digits is an odd number;
        for (d = 0; d < n; d++)
            data[d] = p1->arr[d];
}

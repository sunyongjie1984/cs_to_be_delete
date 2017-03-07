#include <stdio.h>

class Heap {
public:
    Heap(): sz(0) { }
    void push(int x)
    {
        int i = sz++;
        while (i > 0)
        {
            int p = (i - 1) / 2;
            if (heap[p] <= x)
                break;
            heap[i] = heap[p];
            i = p;
        }
        heap[i] = x;
    }
    int pop()
    {
        int ret = heap[0];
        int x = heap[--sz];
        int i = 0;
        while (i * 2 + 1 < sz)
        {
            int a = i * 2 + 1;
            int b = i * 2 + 2;
            if (b < sz && heap[b] < heap[a])
                a = b; // a always the minimum
            if (heap[a] >= x)
                break;
            heap[i] = heap[a];
            i = a;
        }
        heap[i] = x;
        return ret;
    }
private:
    static const int MAX_N = 1000;
    int heap[MAX_N];
    int sz;
};



int main(void)
{
    Heap h;
    h.push(3);
    h.push(5);
    h.push(4);
    h.push(1);
    for (int i = 0; i < 4; ++i)
    {
        printf("%d ", h.pop());
    }
    printf("\n");
    getchar();
    return 0;
}



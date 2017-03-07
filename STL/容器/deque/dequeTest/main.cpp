#include <deque> 

int main() 
{ 
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; //这里有一个数组 
    std::deque<int> y(a, a + 10); //用这个数组的前10个（其实也就是全部）元素来初始化一个deque 
    return 0; 
} 
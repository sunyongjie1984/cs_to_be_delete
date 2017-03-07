#include "CArray.h"
template <class elemType>
void swap(CArray<elemType>& array, int i, int j)
{
	elemType tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
}
int main()
{
	int arr[3] = { 3, 7, 111};
	CArray<int> a(arr, 3);
	swap(a, 0, 2);
	//swap(a, 1, 3); // out of range
	std::cout << a << std::endl;
	return 0;
}
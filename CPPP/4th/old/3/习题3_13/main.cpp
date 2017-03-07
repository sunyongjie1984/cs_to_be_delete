#include <iostream>
#include <vector>
using namespace std;
//using std::vector<int>::size_type;
int main()
{
	vector<int> ivec;
	int ival;

	cout << "Enter numbers(Ctrl+z to end):" << endl;
	while (cin >> ival)
	{
		ivec.push_back(ival);
	}
	
	if (ivec.size() == 0)
	{
		cout << "No element?!" << endl;
		return -1;
	}
	// 这块这个东西很重要，我试了，如果没有这个语句，那么当我输入的是奇数的元素个数时，输出出
	// 问题，现在就好了。方法都是输入Control + z 然后输入Enter键。
//	cout << endl;
	// 又出现问题了，我加了cout << endl;这个语句之后，输入奇数的时候固然是Control + z然后输入
	// Enter键，可是，输入偶数的时候就不用输入Enter直接电脑就把结果输出了。这些流的问题，
	// 很让人烦啊，可是一定是有原因的。
	cout << "Sum of each pair of adjaent elements in the vector:"
		 << endl;

	for (vector<int>::size_type ix = 0; ix < ivec.size() - 1; ix = ix + 2)
	{
		cout << ivec[ix] + ivec[ix + 1] << "\t"; // 我知道一点了，一定是当是奇数的时候这个流
		if ((ix + 1) % 6 == 0)                   // 出现了某种错误，然后乱七八糟又发生什么事。
		{
			cout << endl;
		}
	}

	if (ivec.size() % 2 != 0)
	{
		cout << endl
			 << "The last element is not been summed "
			 << "and its value is "
			 << ivec[ivec.size() - 1 ]
			 << endl;
	}
	return 0;
}

#include <iostream>
#include <string>
#include <vector>
using namespace std;


string sa[10];
int ia[10];

int main(){
	unsigned const buf_size = 1024;  //维数必须用值大于等于1的常量表达式（整型字面值常量，枚举常量或常量表达式初始化的整型const对象）
	int const b = 1024;
	int ib[b];
	int ia[buf_size];
	//int iaa[get_size()];
	int iaaa[4*7 - 14];
	//char st[11] = "fundamental";  //error  字符串字面值长度为11，但是数组必须有12个元素，有一个用于存放空字符null

	
	string sa2[10];
	int ia2[10];
	cout << sa[0] << endl;
	cout << sa2[0] << endl;
	/*cout << ia[0] << endl;              //error  being used without initialized
	cout << ia2[0] << endl;*/

	//vector<int> ivec = {0,1,2};         //error
	
	const size_t array_size = 10;
	int arr[array_size];
	for (size_t ix = 0; ix != array_size; ++ ix)
	{
		arr[ix] = ix;
		cout << arr[ix] << endl;
	}
	int* p = arr;
	cout << *p << endl;
	return 0;

}
#include <iostream>
using namespace std;
void fun();
int counter = 100; // 非const全局变量可以在工程中其他文件中用extern直接访问并使用
extern const int counter2 = 200; // 如果想要在其他文件中使用const变量，
int main()                       // 则必须显式声明，且那个文件也要那做。
{                  // 因为const对象默认为文件的局部变量。_CP_page50
	int counter = 10;
	fun();
	cout << counter << endl;
	return 0;
}
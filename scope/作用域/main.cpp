#include <iostream> // i虽然是全局作用域，但是要定义在上面，不这样就要在上面声明。
extern int i; // 把int i = 10放在函数的下面，在前面就要声明一下才行。
int main()
{
	int sum = 0; // sum局部作用域
	for (int val = 1; val <= 10; ++val)
	{
		sum += val;
	}
	std::cout << "Sum of 1 to 10 inclusive is "
		      << sum << std::endl;
	std::cout << i << std::endl;
	std::cout << val << std::endl; // 按理来说这里是不应该能够输出的
	return 0;                      // 因为val是语句作用域
}
int i = 10;

#include <iostream>
#include "cin_to_cout.h" // 我把类cin_to_cout的对象输出操作，用重载的
int main() // 方法变成了'>>'
{
	cin_to_cout a(5);
	// 有意思吧，前面输出完之后，返回的仍然是标准输出流对象，所以可以
	// 接着输出

	std::cout >> a << ' ' << 1 << std::endl;
	
	return 0;
}
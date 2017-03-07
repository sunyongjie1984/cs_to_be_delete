#include <iostream>
#include "Queue.h"
int main()
{
	Queue<int> a;
	a.push(3);
	a.push(5);
	a.push(4);
	std::cout << a.front() << std::endl;
	a.pop();
	std::cout << a.front() << std::endl;
	return 0;
}

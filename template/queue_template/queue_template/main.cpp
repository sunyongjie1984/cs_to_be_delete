#include "MS_Queue.h"
int main()
{
	Queue<int> queueInt;

	queueInt.push(3);
	queueInt.push(324);
	queueInt.push(4);

	std::cout << queueInt << std::endl;

	return 0;
}
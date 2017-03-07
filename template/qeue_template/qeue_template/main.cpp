#include "queue_template.h"
int main()
{
	Queue<int>* p_qi = new Queue<int>;
	int ival;
	for (ival = 0; ival < 10; ival++)
		p_qi->add(ival);
	return 0;
}
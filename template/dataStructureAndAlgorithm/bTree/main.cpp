#include "bTree.h"
int main()
{
	char* c = "abcdeg###f##h";
	BTree a(c, 13);
	a.PrintPreOrder();
	a.PrintInOrder();
	a.PrintPostOrder();
	BTree b;
	b.PrintPreOrder();
	b.PrintInOrder();
	b.PrintPostOrder();
	return 0;
}

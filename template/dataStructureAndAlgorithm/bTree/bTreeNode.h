#include <iostream>
class BTreeNode {
public:
	BTreeNode(): data(0), lchild(NULL), rchild(NULL) { }
	char data;
	BTreeNode* lchild;
	BTreeNode* rchild;
};

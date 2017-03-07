#include <string>
#include <iostream>
class Node {
public:
	Node(char *n = " ", int a = 0)
	{
		name = strdup(n);
		strncpy(name, n, 17);
		age = a;
	}/*
	Node(const Node &n)
	{
		name = strdup(n.name);
		age = n.age;
	}*/
	char *name;
	int age;
};
int main()
{
	Node node1("Roger", 20);
	Node node2(node1);

	strcpy(node2.name, "wendy");
	node2.age = 30;

	std::cout << node1.name << ' ' << node1.age;
	std::cout << "\n";
	std::cout << node2.name << ' ' << node2.age;
	return 0;
}
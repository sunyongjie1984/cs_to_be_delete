#include <string>
#include <iostream>
class Node 
{
public:
	Node(char *n = " ", int a = 0)
	{   // 这条语句应该可以用别的换，我看看。
//		name = strdup(n);
		
		name = n; // 改成这个语句，并且加上拷贝构造函数就能用了。
		age = a;  // 没有能够彻底明白啊
	}/*//                                        有你没有你，果然不一样啊
	Node(const Node &n)
	{
		name = strdup(n.name);
		age = n.age;
	} */
	char *name;
	int age;
};

int main()
{
	Node node1("Roger", 20);
//	Node node2(node1);

//	strcpy(node2.name, "wendy");
//	node2.age = 30;

	std::cout << node1.name << ' ' << node1.age;
	std::cout << "\n";
//	std::cout << node2.name << ' ' << node2.age;
	return 0;
}bbbbbbbg
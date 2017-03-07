#include <iostream>
class C
{
public:
	int& getRef()
	{
		return n; 返回n的引用，而n在定义的时候却是整形。
	}
	int getN()
	{
		return n;
	}
private:
	int n;
};
int main()
{
	C c;
//	int k = c.getN(); // 看好这两句话的不同。呵呵。
	int& k = c.getRef();
	k = 7;
	std::cout << c.getN() << '\t';
	return 0;
}

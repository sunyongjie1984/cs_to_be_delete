#include <list>

int main(int argc, char* argv[])
{
	std::list<int> l;
	std::list<int>::iterator* it1 = new std::list<int>::iterator(l.begin());
	memset(it1, 1, sizeof(std::list<int>::iterator));
	l.push_back(1);
	l.begin();
	return 0;
}
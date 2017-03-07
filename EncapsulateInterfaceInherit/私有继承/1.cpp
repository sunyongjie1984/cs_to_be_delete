#include "Animal.h" // 这一个部分内容不少，在宝典中p132，仔细读读
                    // 这三种继承方式。
void Func(Animal& an)
{
	an.eat();
}
int main()
{
	Cat dao;
	Giraffe gir;
	Func(dao);
//	Func(gir);
	return 0;
}

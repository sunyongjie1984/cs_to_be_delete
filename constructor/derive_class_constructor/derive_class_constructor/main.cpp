#include "CBook.h"
int main()
{
    // 这个时候，编译器应该生成了一个临时的std::string类型对象，然后再把这个临时对象传进构造函数中去
	// 这个时候会进入构造函数二，我只定义构造函数三时，编译不能通过
    CBook book("I love China"); 
								
	std::cout << book << std::endl;
	std::cout << "I love China\n" << std::endl;

	//std::string s = "I love American";
	//CBook book2(s); // 又定义构造函数二，又定义三导致这个语句执行不了了，因为编译器认为重载模糊了
	//std::cout << book2 << std::endl;

	std::string s2 = "I love spring"; // 1.派生类在构造对象时，一定会调用基类构造函数，本例是调用了基类中对应的重载构造函数
	CBookOnSale bookOnSale(s2, 3);    // 2.派生类在构造对象时，如果没有找到参数对应的基类重载构造函数，则调用基类默认构造函数
	std::cout << bookOnSale << std::endl; // 3.派生类必须在定义构造函数时指定，使用基类的哪一个构造函数。

	CBookOnSale bookOnSale2("I love China");
	std::cout << bookOnSale2 << std::endl;

	CBookOnSale bookOnSale3(5, 2.0);
	std::cout << bookOnSale3 << std::endl;

	std::cout << "\nprint function\n" << std::endl;

	book.print(std::cout);
	bookOnSale.print(std::cout);

	CBook* pBook = new CBookOnSale(5, 2.3);
	CBook* pBook2 = new CBook();

	pBook2->print(std::cout);
	pBook2->print2(std::cout);

	pBook->print(std::cout);
	pBook->print2(std::cout);

	CBookOnSale a(5, 2.3);
	CBook& book4 = a;
	book4.print(std::cout);
	book4.print2(std::cout);
	return 0;
}
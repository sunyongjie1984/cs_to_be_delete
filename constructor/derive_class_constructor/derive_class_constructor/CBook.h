#include <string>
#include <iostream>
class CBook {
public:
	CBook(): isbn("sunyongjie"), count(0)
	{
		std::cout << "CBook default constructor" << std::endl;	
	}
	CBook(std::string s): isbn(s), count(0)
	{
		std::cout << "CBook constructor 2" << std::endl;	
	}
	CBook(std::string& s): isbn(s), count(0)
	{
		std::cout << "CBook constructor 3" << std::endl;	
	}
	CBook(std::string& s, int c): isbn(s), count(c)
	{
		std::cout << "CBook constructor 4" << std::endl;	
	}
	friend std::ostream& operator<<(std::ostream& os, const CBook& book)
	{
		os << "isbn: " <<  book.isbn << "\t\tcount: " << book.count/*<< std::endl*/; // 操作符重载时最好只提供必须操作，这里不要添这个多余的东西。
		return os;
	}
	virtual void print(std::ostream& os)
	{   // 操作符重载时最好只提供必须操作，这里不要添这个多余的东西。
		os << "isbn: " <<  isbn << "\t\tcount: " << count<< std::endl; 
	}
	void print2(std::ostream& os) // print2定义为非虚函数，良好的类的设计者应该是充分考虑到了
	{	// 没有子类会重写这个方法，举个例子，也就是说CBookOnSale最好不要去重写这个函数。						  
		os << "isbn: " <<  isbn << "\t\tcount: " << count<< std::endl; 
	}
//private: // 不然派生类不能访问了
protected:
	std::string isbn;
	int count;
};

class CBookOnSale: public CBook {
public:
	//CBookOnSale()
	//{
	//	std::cout << "CBookOnSale default constructor" << std::endl;
	//}

    // 构造函数这样用比较好，用基类初始化基类成员，自己初始化自己的成员。												  
	CBookOnSale(std::string& s, int c, double d = 23.23): CBook(s, c), price(d)
	{
		std::cout << "CBookOnSale constructor" << std::endl;
	}
	friend std::ostream& operator<<(std::ostream& os, const CBookOnSale& book)
	{
		os << "isbn: " <<  book.isbn << "\t\tcount: " << book.count << "\t\tprice: " << book.price/*<< std::endl*/; 
		return os;
	}
	CBookOnSale(char* p)
	{
		isbn = p;
	}
	CBookOnSale(int c, double d)
	{
		count = c;
		price = d;
	}
	void print(std::ostream& os)
	{
		os << "isbn: " << isbn << "\t\tcount: " << count << "\t\tprice: " << price << std::endl; 
	}
	void print2(std::ostream& os)
	{
		os << "isbn: " << isbn << "\t\tcount: " << count << "\t\tprice: " << price << std::endl; 
	}
private:
	double price;
};
#include <string>
#include <iostream>
#include "windows.h"
using namespace std;

class Sales_item
{
public:
	Sales_item(string& s):isbn(s),units_sold(0),revenue(0.0){};
	Sales_item():units_sold(0),revenue(0.0){};
	Sales_item& operator =(const Sales_item& rhs);
protected:
private:
	string isbn;
	int units_sold;
	double revenue;
};

Sales_item& Sales_item::operator =(const Sales_item& rhs)
{
	isbn = rhs.isbn;
	units_sold = rhs.units_sold;
	revenue = rhs.revenue + 1000;
	return *this;
}

struct NoName 
{
	NoName():pstring(new string),i(0),d(0){count ++;}
	NoName(const NoName& other);
	NoName& operator=(const NoName& rhs);
	~NoName();
	static int count;
private:
	string* pstring;
	int i;
	double d;
};

int NoName::count = 0;

NoName::NoName(const NoName& other)
{
	pstring = new string;
	*pstring = *(other.pstring);
	i = other.i;
	d = other.d;

}

NoName& NoName::operator=(const NoName& rhs)
{

	//delete pstring;
	pstring = new string;
	*pstring = *(rhs.pstring);
	i = rhs.i;
	d = rhs.d;
	return *this;
}

NoName::~NoName()
{
	delete pstring;
}

void bar(const string& s)
{
	
}

string foo( )
{
	string s = "null";
	return s;
}

void test()
{

	NoName n1;
	NoName n3;
	n3 = n1;
}
int main()
 {
	cout << "initialized test";
	string book1 = "technology";
	Sales_item sale(book1);
	Sales_item sale2 = sale;
	Sales_item* item = new Sales_item;
	
	for (int i = 0; i < 10; i ++)
	{
		cout << i << endl;
	}

	/*while (1)
	{
		Sleep(10);
		test();
	}*/
	NoName n1;
	NoName n2 = n1;
	NoName n3;
	n3 = n1;
	cout << NoName.count << endl;

	int a = 3;
	const int& ra = a;
	//int& const ra2  = a;   //const are ignored
	//ra = 5;
	//ra2 = 5;
	a = 8;

	string s = "en";
	bar(s);
	//bar("hello world");
	return 0;
}



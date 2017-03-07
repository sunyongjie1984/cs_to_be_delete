#include <iostream>
#include <string>
using namespace std;

class Sales_item
{
public:
	explicit Sales_item(const std::string &book = ""):isbn(book),units_sold(0),revenue(0.0){}
	//Sales_item(std::istream& is){is >> *this;}
	//operations on Sales_item objects
	double ave_price() const;
	bool same_isbn(const Sales_item &rhs) const
	{
		//const成员函数不可以修改该对象的数据成员
		return isbn == rhs.isbn; 
	}

	//default constructor needed to initalize members of built-in type
	//Sales_item():units_sold(0),revenue(0.0){}
	double salary;
private:
	std::string isbn;
	unsigned units_sold;
	double revenue;
} gg;  //定义类的时候还需要分号？就是为了支持定义对象。
	//有一句话不理解，为什么说类是用struct关键字定义的，则在第一个访问标号之前的成员是公有的，
	//如果是类是用class关键字定义的，则这些成员是私有的。

double Sales_item::ave_price() const
{
	if(units_sold)
	{
		return revenue/units_sold;
	}else
	{
		return 0;
	} 
}


class Screen
{
public:

	typedef std::string::size_type index;
	//interface member functioins
	Screen& setContents(string ix);   //const在这里是什么意思？
	
private:
	string contents;
	index cursor;
	index height;
	index width;
};


Screen& Screen::setContents(string ix)
{
		contents = ix;
		return *this;
}

int main(){
	int i = 3;
	int j = 5;
   	cout << i << "+" << j
		<< "=" << i+j << endl;
	Sales_item si;
	cout << si.salary << endl;
	cout << " May be !" << endl;
	string null_book = "xxxx";
	si.same_isbn(Sales_item(null_book));

	Screen screen;
	string id = "this book is sold well.";
	screen.setContents(id);

    std::cin.get();
	return 0;
}

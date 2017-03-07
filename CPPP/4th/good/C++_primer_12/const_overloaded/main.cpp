#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Screen
{
public:
	typedef std::string::size_type index;
	//return character at the cursor or at a given position
	char get() const
	{
		return contents[cursor];
	}
	//char get(index ht,index wd) const;
	inline Screen const & get(index ht,index wd) const;   //类内部定义的成员函数默认为inline
	//Screen&表明返回的是成员函数对自身类型对象的引用
	Screen& set(char);
	Screen& set(index,index,char);
	Screen& setCursor(index c);
	index getCursor() const;
	Screen& setContents(string ix);
	Screen& move(index r,index c);

	Screen& display(std::ostream &os)
	{
		do_display(os);
		return *this;
	}

	const Screen& display(std::ostream &os) const
	{
		do_display(os);
		return *this;
	}

	//构造函数
	Screen():cursor(0),height(0),width(0){}
	Screen(index cursor,index height){}


private:
	string contents;
	index cursor;
	index height;
	index width;

	void do_display(ostream &os) const
	{
		os << contents;
	}
};


//char Screen::get(index r,index c) const 
//{
//	index row = r * width;
//	return contents[row+c];
//}

Screen const & Screen::get(index r,index c) const 
{
	index row = r * width;
	return (*this);
}

Screen& Screen::setContents(string ix)
{
	this->contents = ix;
	return *this;
}

Screen& Screen::set(char c)
{
	this->contents[cursor] = c;
	return *this;
}

Screen& Screen::setCursor(index c)
{
	this->cursor = c;
	return *this;
}

inline Screen::index Screen::getCursor() const
{
	return cursor;
}

Screen& Screen::move(index r,index c)
{
	index row = r * width;
	cursor = row + c;
	return *this;
}

int func(float f)
{
	return f;
}

int main()
{
	int i = 3;
	/*Screen myScreen(5,3);
	const Screen blank(5,3);
	myScreen.set('#').display(cout);
	blank.display(cout);
	Screen myScreen2(4,5);*/
	Screen myScreen(4,3);
	string t = "ttttttttttttttt";
	Screen myScreen1 = myScreen.display(cout); 
	myScreen1.setCursor(3);
	Screen myScreen2 = myScreen.setContents(t);
	myScreen.display(cout);
	vector<int> ivec(5);

	Screen a;
	a.display(cout).setContents(t);

	Screen const r = a.display(cout);
	//r.setContents(t);
	
	int p = func(3.5);
	cout << endl;
	cout << p << endl;
	
    std::cin.get();
	return 0;
}

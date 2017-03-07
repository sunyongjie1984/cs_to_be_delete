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
	inline char get(index ht,index wd) const;
	//Screen&表明返回的是成员函数对自身类型对象的引用
	Screen& set(char);
	Screen& set(index,index,char);
	Screen& Screen::setCursor(index c);
	Screen& setContents(string ix);
	Screen& move(index r,index c);

	//构造函数
	Screen():cursor(0),height(0),width(0){}
	
private:
	string contents;
	index cursor;
	index height;
	index width;
};


char Screen::get(index r,index c) const 
{
	index row = r * width;
	return contents[row+c];
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

Screen& Screen::move(index r,index c)
{
		index row = r * width;
		cursor = row + c;
		return *this;
}

int main()
{

	//std::string a("hhhhhhhhh");
	//a[0] = 'd';
	//std::cout << a[1] << std::endl;
	//Screen screen;
	//screen.setContents("hhhhhhhhhh");
	//cout << screen.get() << endl;
	//screen.set('d');   //?
	//cout << screen.get() << endl;
	//screen.move(1,1);
	//cout << screen.get() << endl;
    Screen* s = new Screen[10];
	vector<Screen> vec(s,s+10);
	Screen* s2 = new Screen;
	
	//delete[] s;
	return 0;
}
#include <iostream>
#include <string>
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
	Screen& setContents(string ix); 

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

int main()
{
	Screen screen;
	char ch = screen.get();
	cout << ch << endl;
	screen.setContents("hh");
	ch = screen.get(0,0);
	cout << ch << endl;
	return 0;
}
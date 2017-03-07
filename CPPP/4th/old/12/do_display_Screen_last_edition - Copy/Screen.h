#include <iostream>
#include <string>
using namespace std;
class Screen {
public:
	typedef string::size_type index;

	Screen(index hght, index wdth, const string &cntnts);

	Screen& move(index r, index c);
	Screen& set(char);

	Screen& display(ostream &os);
	const Screen& display(ostream &os) const;

	inline char get(index ht, index wd) const;
	index get_cursor() const;
	char get() const 
    { 
        return contents[cursor];
    }
private:
	void do_display(ostream &os) const;
  
	string contents;
	index cursor;
	index height, width;
};

// inline函数头文件与源文件不能分离。
inline Screen::index Screen::get_cursor() const // 这个返回值很是奇怪。
{
	return cursor;
}
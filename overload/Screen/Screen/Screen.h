#include <iostream>
#include <string>
using namespace std;

class Screen
{
public:
	typedef string::size_type index;
	//constructor
	Screen(index h, index w, string c);
	//destructor
	//~Screen()
	Screen & display(ostream & os);
	Screen const & display(ostream & os) const;
	index max();
	/*{
		return height;
	}*/

private:
	string contents;
	index height;
	index width;
	index cursor;
	void do_display(ostream & os) const; // 当对象调用const成员函数时不会修改该对象的数据成员
};

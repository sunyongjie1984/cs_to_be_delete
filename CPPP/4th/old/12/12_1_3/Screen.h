#include <string>
#include <iostream>
class Screen 
{
public:
	typedef std::string::size_type index;
	Screen(index hght, index wdth, const std::string &cntnts);
	char get() const 
	{
		return contents[cursor]; 
	}
	char get(index ht, index wd) const;
	friend std::ostream& operator<<(std::ostream&, const Screen&);
private:
	std::string contents;
	index cursor;
	index height, width;
};
Screen::Screen(index hght, index wdth, const std::string &cntnts):
    contents(cntnts), cursor(0), height(hght), width(wdth)
	{
	}
std::ostream& operator<<(std::ostream& os, const Screen& object)
{
	os << object.contents;
	return os;
}
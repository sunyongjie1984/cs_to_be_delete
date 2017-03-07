#include <string>
class Person 
{
public:
	Person(const string &nm, const string &addr): 
	  name(nm), address(addr) {}
	string getName() const 
	{
		return name;
	}
	string getAddress() const 
	{
		return address;
	}
private:
	string name;
	string address;
};

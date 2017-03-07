#include <iostream>
using namespace std;
void foo()
{
	cout<<a<<endl;
}
class A
{
public:
	friend void foo();
private:
	int a;
};


main()
{

}
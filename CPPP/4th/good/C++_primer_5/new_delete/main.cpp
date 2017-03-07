#include <iostream>
#include <string>
#include <vector>
using namespace std;


int main()
{   

	//动态分配   new,malloc都属于动态分配

	int * p = new int;
	*p = 30;
	cout << *p << endl;
	delete p;
	p = 0;
	cout << p << endl;

	//const对象的动态分配与回收
	int const * pci = new int const (1024); 
	std::cout << *pci << std::endl;
	delete pci;
	pci = 0;

	vector<string> svec(10);
	vector<string> *pvec1 = new vector<string>(10);
	vector<string> *pvec2 = new vector<string>[10];
	vector<string> *pv1 = &svec;
	vector<string> *pv2 = pvec1;

	cout << svec[1] << endl;
	cout << &svec << endl;

	//delete svec;
	delete pvec1;
	delete [] pvec2;
	//delete pv1;   //不用delete
	delete pv2;     //重复delete导致崩溃

}


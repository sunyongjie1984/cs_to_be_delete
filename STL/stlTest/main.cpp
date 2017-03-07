// SetFind.cpp
// compile with: /EHsc
//
//      Illustrates how to use the find function to get an iterator
//      that points to the first element in the controlled sequence
//      that has a particular sort key.
//
// Functions:
//
//    find         Returns an iterator that points to the first element
//                 in the controlled sequence that has the same sort key
//                 as the value passed to the find function. If no such
//                 element exists, the iterator equals end().
//////////////////////////////////////////////////////////////////////

#pragma warning(disable:4786)
#include <set>
#include <iostream>

using namespace std ;

typedef set<int> SET_INT;

void truefalse(int x)
{
	cout << (x?"True":"False") << endl;
}

int main() 
{
	SET_INT s1;
	cout << "s1.insert(5)" << endl;
	s1.insert(5);
	cout << "s1.insert(8)" << endl;
	s1.insert(8);
	cout << "s1.insert(12)" << endl;
	s1.insert(12);	
	
	SET_INT::iterator it;
	cout << "it=find(8)" << endl;
	it = s1.find(8);
	cout << "it!=s1.end() returned ";
	truefalse(it!=s1.end());  //  True
	
	cout << "it=find(6)" << endl;
	it=s1.find(6);
	cout << "it!=s1.end() returned ";
	truefalse(it!=s1.end());  // False
}
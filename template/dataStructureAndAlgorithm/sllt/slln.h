#ifndef SINGLY_LINKED_LIST_NODE
#define SINGLY_LINKED_LIST_NODE

#include <iostream>
using namespace std; // not recommanded, it is better to use using std::cout, std::cin, etc.

// before implementing template
// class slln
// {
// 	friend class sll;
// 	friend ostream& operator<<(ostream&, const sll&);
// 	friend istream& operator>>(istream&, sll&);
// private:
// 	slln(): info(0), next(0) { }
// 	slln(int i, slln* in = 0): info(i), next(in) { }
// 	int info;
// 	slln* next;
// };

// fist of all, be aware of one thing:
// identify template class/function definination/declaration and
// class/function defination/declaration

// this is a template class defination:
// template <class Type> class slln { ... };

// these are template function definations:
// template <class Type> ostream& globalPrint(ostream& os, const sll<Type>& list) { ... }
// template <class Type> ostream& operator<<(ostream& os, const sll<Type>& list) { ... }

// this is a template class declaration:
// template <class Type> class slln;

// these are template function declarations:
// template <class Type> ostream& globalPrint(ostream&, const sll<Type>&);
// template <class Type> ostream& operator<<(ostream&, const sll<Type>&);

// these are class definations:
// class CBook { ... };
// in a template class defination, it is not common used for me
// class sll<Type> { ... };

// these are function definations:
// int func(int a ) { ... }
// in a template class defination, it is not common used for me
// ostream& operator<< <Type>(ostream& os, const sll<Type>& list) { ... }

// these are class declarations:
// class CBook;
// in a template defination
// class sll<Type>;

// these are function declarations:
// int func(int);
// in a template defination
// friend ostream& operator<< <Type>(ostream&, const sll<Type>&);

// template class declaration
// it is used for a friend class declaration sll<Type> below
template <class Type> class sll;

// template function declaration
// it is used for a friend function declaration operator<< <Type> below
template <class Type> ostream& operator<<(ostream&, const sll<Type>&);

// template function declaration
// it is used for friend function declaration globalPrint<Type> below
template <class Type> ostream& globalPrint(ostream&, const sll<Type>&);

// template function declaration
// it is used for a friend function declaration operator>> <Type> below
template <class Type> istream& operator>>(istream&, sll<Type>&);

// template class slln defination
template <class Type> class slln {

	// friend class declaration, the class named sll<Type>,
	// is a instance of template class named sll
	friend class sll<Type>;

	// friend function declaration, the function named operator<< <Type>,
	// is a instance of template function named operator<<
	//    // ret value, function name, arguments list, which mean it's normal function
	friend ostream& operator<< <Type>(ostream&, const sll<Type>&);

	// friend function declaration, the function named globalPrint<Type>,
	// is a instance of template function named golbalPrint
	friend ostream& globalPrint<Type>(ostream&, const sll<Type>&);

	// friend function declaration, the function named operator>> <Type>,
	// is a instance of template function named operator>>
	friend istream& operator>> <Type>(istream&, sll<Type>&);

	// all are private, this template class is only used for template class sll
	// not a common used template class
private:
	// slln() : info(0), next(NULL) { }
	slln() : info(Type()), next(NULL) { } // the change is typical
                                          // for a template class defination
	slln(Type i, slln* in = NULL) : info(i), next(in) { }
	Type info;
	slln* next;
	// slln<Type>* next; // also ok
};

#endif

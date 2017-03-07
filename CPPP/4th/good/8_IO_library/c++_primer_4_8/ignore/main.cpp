// basic_istream_ignore.cpp
// compile with: /EHsc
#include <iostream>
int main( ) 
{
	using namespace std;
	char chararray[10];
	cout << "Type 'abcdef': ";
	//cin.ignore( 5, 'c' );
	cin >> chararray;
	cout << chararray;
}

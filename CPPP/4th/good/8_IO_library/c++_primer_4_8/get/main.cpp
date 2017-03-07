// basic_istream_get.cpp
// compile with: /EHsc
#include <iostream>
using namespace std;

int main( ) 
{
	char c[10];

	c[0] = cin.get( );
	cin.get( c[1] );
	cin.get( &c[2],3 );
	cin.get( &c[4], 4, '7' );

	cout << c << endl;
}

// string_getline_sample.cpp
// compile with: /EHsc
// Illustrates how to use the getline function to read a
// line of text from the keyboard.
//
// Functions:
//
//    getline       Returns a string from the input stream.
//////////////////////////////////////////////////////////////////////

#pragma warning(disable:4786)
#include <string>
#include <iostream>

using namespace std ;

int main()
{
   string s1;
   cout << "Enter a sentence (use <space> as the delimiter): ";
   getline(cin,s1, ' ');
   cout << "You entered: " << s1 << endl;;
}

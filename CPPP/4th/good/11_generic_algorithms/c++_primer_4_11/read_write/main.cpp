#include <iostream>
#include <iterator>
#include <fstream>
using namespace std;

void read_write() {
	ofstream outfile;
	outfile.open("dictionary");

	// write a sequence of strings to the ofstream named outfile
	// placing each string on a separate line
	ostream_iterator<string> os_string(outfile, "\n");

	istream_iterator<int> input(cin), eof;
	ostream_iterator<int> output(cout);  
	while (input != eof)
		*output++ = *input++;
}

int main()
{
	read_write();
	return 0;
}
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;
int main() {
	istream_iterator<int> in_iter(cin);  // read ints from cin
	istream_iterator<int> eof;      // istream ``end'' iterator
	vector<int> vec(in_iter, eof);  // construct vec from an iterator range

	// print vec to see what we read
	for (vector<int>::const_iterator it = vec.begin();
		it != vec.end(); ++it)
		cout << *it << " ";
	cout << endl;
}
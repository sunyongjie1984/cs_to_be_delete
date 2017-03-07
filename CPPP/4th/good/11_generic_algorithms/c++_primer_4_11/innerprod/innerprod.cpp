//#include "algs_preamble.h"
#include <iostream>
#include <string>
#include <vector>
//#include <algorithm>
#include <numeric>
using namespace std;
// combine elements into a parenthesized, comma-separated pair
string combine(string x, string y)
{
	return "(" + x + ", " + y + ")";
}
// add two strings, each separated by a comma
string concatenate(string x, string y)
{
	if (x.empty())
		return y;
	return x + ", " + y;
}

int main()
{
	vector<string> names, values;
	names.push_back("if");
	values.push_back("keyword");
	names.push_back("string");
	values.push_back("library type");
	names.push_back("sort");
	values.push_back("algorithm");

	cout << inner_product(names.begin(), names.end(),
	                      values.begin(), string(),
	                      concatenate, combine);
}

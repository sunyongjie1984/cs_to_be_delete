#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
int ia[10] = { 51, 23, 7, 88, 41, 98, 12, 103, 37, 6};
int main()
{
	vector<int> vec(ia, ia + 10);
	sort(vec.begin(), vec.end());
	int searchValue;
	cin >> searchValue;

	vector<int>::iterator found;
	found = find(vec.begin(), vec.end(), searchValue);
	if (found != vec.end())
	{
		cout << "searchValue found!" << endl;
	}
	else
		cout << "searchValue not found!" << endl;
}
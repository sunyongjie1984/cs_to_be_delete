#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

bool is_shorter(const string& s1, const string& s2)
{
	return s1.size() < s2.size();
}

bool GT6(const string& s)
{
	return s.size() >=6;
}

int main()
{
	vector<string> words;
	string next_word;
	while (cin >> next_word)
	{
		words.push_back(next_word);
	}
	sort(words.begin(), words.end());
	vector<string>::iterator end_unique = unique(words.begin(), words.end());
	words.erase(end_unique, words.end());
	stable_sort(words.begin(), words.end(), is_shorter);
	vector<string>::size_type wc = count_if(words.begin(), words.end(), GT6);
	//cout << wc << " " << make_plural(wc, "words", "s") << " 6 charactors or longer" << endl;
	return 0;
}
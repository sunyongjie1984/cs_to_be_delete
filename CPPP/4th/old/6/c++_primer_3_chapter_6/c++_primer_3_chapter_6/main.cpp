#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <map>
#include <set>
using namespace std;

vector<string>* retrieve_text()
{
	string file_name;
	cout << "please enter file name: ";
	cin >> file_name;

	ifstream infile(file_name.c_str(), ios::in);
	if (!infile)
	{
		cerr << "oops!   retrieve_text" << file_name;
		exit(-1);
	}
	else 
	{
		cout << '\n';
	}
	vector<string>* lines_of_text = new vector<string>; // 这里是一个new出来的容器，所以我们可以在这个函数当中返回这个容器的指针
	string textline; // 而不用担心主函数当中获得这个容器的指针时这个容器的内容会被析构掉。

	typedef pair<string::size_type, int> stats;
	stats maxline;
	int linenum = 0;
	while (getline(infile, textline, '\n'))
	{
		cout << "line read: " << textline << '\n';
		if (maxline.first < textline.size())
		{
			maxline.first = textline.size();
			maxline.second = linenum;
		}
		lines_of_text->push_back(textline);
		linenum++;
	}
	return lines_of_text;
}

typedef pair<short, short> location;
typedef vector<location> loc;
typedef vector<string> text;
typedef pair<text*, loc*> text_loc;
typedef map<string, loc*>::value_type value_type;
text_loc* separate_words(const vector<string>* text_file)
{
	vector<string>* words = new vector<string>;
	vector<location>* locations = new vector<location>;
	short line_pos = 0;
	for(; line_pos < text_file->size(); ++line_pos)
	{
		short word_pos = 0;
		string textline = (*text_file)[line_pos];
		string::size_type pos = 0;
		string::size_type prev_pos = 0;
		while ((pos = textline.find_first_of(' ', pos)) != string::npos)
		{
			words->push_back(textline.substr(prev_pos, pos - prev_pos));
			locations->push_back(make_pair(line_pos, word_pos));
			++word_pos;
			prev_pos = ++pos;
		}
		words->push_back(textline.substr(prev_pos, pos - prev_pos));
		locations->push_back(make_pair(line_pos, word_pos));
	}
	return new text_loc(words, locations);
}

void filter_text(vector<string>* words, string filter)
{
	vector<string>::iterator iter = words->begin();
	vector<string>::iterator iter_end = words->end();
	if (!filter.size())
		filter.insert(0, "\".,");
	while (iter != iter_end)
	{
		string::size_type pos = 0;
		while ((pos = (*iter).find_first_of(filter, pos)) != string::npos)
			(*iter).erase(pos, 1);
		iter++;
	}
}
extern map<string, loc*>* build_word_map(const text_loc* text_locations)
{
	set<string> exclusion_set;
	ifstream infile("exclusion_set");

	//ifstream infile(file_name.c_str(), ios::in);
	if (!infile)
	{
		cerr << "oops!";
		exit(-1);
	}
	else 
	{
		cout << '\n';
	}
	vector<string>* lines_of_text = new vector<string>; // 这里是一个new出来的容器，所以我们可以在这个函数当中返回这个容器的指针
	string textline; // 而不用担心主函数当中获得这个容器的指针时这个容器的内容会被析构掉。

	typedef pair<string::size_type, int> stats;
	stats maxline;
	int linenum = 0;
	while (getline(infile, textline, '\n'))
	{
		cout << "line read: " << textline << '\n';
		if (maxline.first < textline.size())
		{
			maxline.first = textline.size();
			maxline.second = linenum;
		}
		lines_of_text->push_back(textline);
		linenum++;
	}
	vector<string>* words = new vector<string>;
	short line_pos = 0;
	for(; line_pos < lines_of_text->size(); ++line_pos)
	{
		string textline = (*lines_of_text)[line_pos];
		string::size_type pos = 0;
		string::size_type prev_pos = 0;
		while ((pos = textline.find_first_of(' ', pos)) != string::npos)
		{
			words->push_back(textline.substr(prev_pos, pos - prev_pos));
			exclusion_set.insert(textline.substr(prev_pos, pos - prev_pos));
			prev_pos = ++pos;
		}
		words->push_back(textline.substr(prev_pos, pos - prev_pos));
		exclusion_set.insert(textline.substr(prev_pos, pos - prev_pos));
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	//exclusion_set.insert(
	map<string, loc*>* word_map = new map<string, loc*>;
	vector<string>* text_words = text_locations->first;
	vector<location>* text_locs = text_locations->second;
	register int elem_cnt = text_words->size();
	for (int ix = 0; ix < elem_cnt; ix++)
	{
		string textword = (*text_words)[ix];
		// 单词小于3个字符，或者这个单词这个exclusion_set中，那么就
		if (textword.size() < 3 || exclusion_set.count(textword))
			continue;
		if (!word_map->count((*text_words)[ix]))
		{
			loc* ploc = new vector<location>;
			ploc->push_back((*text_locs)[ix]);
			word_map->insert(value_type((*text_words)[ix], ploc));
		}
		else
		{
			(*word_map)[(*text_words)[ix]]->push_back((*text_locs)[ix]);
		}
	}
	return word_map;
}

void display_map_text(map<string, loc*>* text_map)
{
	typedef map<string, loc*> tmap;
	tmap::iterator iter = text_map->begin();
	tmap::iterator iter_end = text_map->end();
	while (iter != iter_end)
	{
		cout << "word: " << (*iter).first << " (";
		int loc_cnt = 0;
		loc* text_locs = (*iter).second;
		loc::iterator liter = text_locs->begin();
		loc::iterator liter_end = text_locs->end();
		while (liter != liter_end)
		{
			if (loc_cnt)
				cout << ',';
			else
				++loc_cnt;
			cout << '(' << (*liter).first << ',' << (*liter).second << ')';
			++liter;
		}
		cout << ")\n";
		++iter;
	}
}


int main()
{
	vector<string, allocator<string>>* text_file = retrieve_text();
	text_loc* text_locations = separate_words(text_file);
	string filt_elems("\",.;:!?)(\\/");
	filter_text(text_locations->first, filt_elems);
	map<string, loc*>* text_map = build_word_map(text_locations);
	display_map_text(text_map);
	return 0;
}
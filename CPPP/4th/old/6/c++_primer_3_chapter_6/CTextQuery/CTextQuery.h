// 标准库头文件
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <set>

#include <iostream>
#include <fstream>

// 标准c头文件
#include <stddef.h>
#include <ctype.h>

using namespace std;
// typedefs 使声明更简单
typedef pair<short, short> location;
typedef vector<location> loc;
typedef vector<string> text;
typedef pair<text*, loc*> text_loc;

class CTextQuery {
public:
	CTextQuery()
	{
		memset(this, 0, sizeof(CTextQuery));
	}
	static void filter_elements(string felems)
	{
		m_filt_elems = felems;
	}
	void query_text();
	void display_map_text();
	void display_text_locations();
	void doit()
	{
		retrieve_text();
		separate_words();
		filter_text();
		suffix_text();
		strip_caps();
		build_word_map();
	}
private:
	void retrieve_text();
	void separate_words();
	void filter_text();
	void suffix_text();
	void strip_caps();
	void build_word_map();
	void suffix_s(string&);
private:
	vector<string>* m_lines_of_text;
	text_loc* m_text_locations;
	map<string, loc*>* m_word_map;
	static string m_filt_elems;
};
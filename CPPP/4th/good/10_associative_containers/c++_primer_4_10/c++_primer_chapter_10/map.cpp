#include <map>
#include <iostream>
#include <string>
int main()
{
    std::map<std::string, int> word_count;
    std::string s="hello";
    std::map<std::string, int>::value_type a(s, 33);
    word_count.insert(a);
    std::map<std::string, int>::iterator map_it=word_count.begin();
    std::cout << map_it->first << std::endl;
    std::cout << map_it->second << std::endl;
    std::cout << (*map_it).first << std::endl;

    std::string s1="hello";
    std::map<std::string, int>::value_type b(s1,222);
    word_count.insert(b);
    //std::cout
	return 0;
}
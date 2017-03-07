#include <boost/spirit.hpp> 
#include <string> 
#include <fstream> 
#include <sstream> 
#include <iostream> 

struct json_grammar 
  : public boost::spirit::grammar<json_grammar> 
{ 
  struct print 
  { 
    void operator()(const char *begin, const char *end) const 
    { 
      std::cout << std::string(begin, end) << std::endl; 
    } 

    void operator()(const double d) const 
    { 
      std::cout << d << std::endl; 
    } 
  }; 

  template <typename Scanner> 
  struct definition 
  { 
    boost::spirit::rule<Scanner> object, member, string, value, number, array; 

    definition(const json_grammar &self) 
    { 
      using namespace boost::spirit; 
      object = "{" >> member >> *("," >> member) >> "}"; 
      member = string[print()] >> ":" >> value; 
      string = "\"" >> *~ch_p("\"") >> "\""; 
      value = string | number | object | array | str_p("true")[print()] | "false" | "null"; 
      number = real_p[print()]; 
      array = "[" >> value >> *("," >> value) >> "]"; 
    } 

    const boost::spirit::rule<Scanner> &start() 
    { 
      return object; 
    } 
  }; 
}; 

int main(int argc, char *argv[]) 
{ 
  std::ifstream fs(argv[1]); 
  std::ostringstream ss; 
  ss << fs.rdbuf(); 
  std::string data = ss.str(); 

  json_grammar g; 
  boost::spirit::parse_info<> pi = boost::spirit::parse(data.c_str(), g, boost::spirit::space_p); 
  if (pi.hit) 
  { 
    if (pi.full) 
      std::cout << "parsing all data successfully" << std::endl; 
    else 
      std::cout << "parsing data partially" << std::endl; 
    std::cout << pi.length << " characters parsed" << std::endl; 
  } 
  else 
    std::cout << "parsing failed; stopped at '" << pi.stop << "'" << std::endl; 
} 
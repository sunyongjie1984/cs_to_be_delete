#include <boost/spirit.hpp> 

struct json_grammar 
  : public boost::spirit::grammar<json_grammar> 
{ 
  template <typename Scanner> 
  struct definition 
  { 
    boost::spirit::rule<Scanner> object, member, string, value, number, array; 

    definition(const json_grammar &self) 
    { 
      using namespace boost::spirit; 
      object = "{" >> member >> *("," >> member) >> "}"; 
      member = string >> ":" >> value; 
      string = "\"" >> *~ch_p("\"") >> "\""; 
      value = string | number | object | array | "true" | "false" | "null"; 
      number = real_p; 
      array = "[" >> value >> *("," >> value) >> "]"; 
    } 

    const boost::spirit::rule<Scanner> &start() 
    { 
      return object; 
    } 
  }; 
}; 

int main() 
{ 
} 
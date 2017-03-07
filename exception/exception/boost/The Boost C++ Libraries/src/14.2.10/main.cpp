#include <boost/tuple/tuple.hpp> 
#include <string> 
#include <iostream> 

boost::tuple<std::string, int> func() 
{ 
  return boost::make_tuple("Error message", 2009); 
}

int main() 
{ 
  std::string errmsg; 
  int errcode; 

  boost::tie(errmsg, errcode) = func(); 
  std::cout << errmsg << ": " << errcode << std::endl; 
} 
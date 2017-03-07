#include <boost/signal.hpp> 
#include <iostream> 

int func1() 
{ 
  return 1; 
} 

int func2() 
{ 
  return 2; 
} 

int main() 
{ 
  boost::signal<int ()> s; 
  s.connect(func1); 
  s.connect(func2); 
  std::cout << s() << std::endl; 
} 
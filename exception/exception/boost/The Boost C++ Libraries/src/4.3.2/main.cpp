#include <boost/signal.hpp> 
#include <iostream> 

void func() 
{ 
  std::cout << "Hello, world!" << std::endl; 
} 

int main() 
{ 
  boost::signal<void ()> s; 
  boost::signals::connection c = s.connect(func); 
  c.block(); 
  s(); 
  c.unblock(); 
  s(); 
} 
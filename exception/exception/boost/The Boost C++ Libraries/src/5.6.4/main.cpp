#include <boost/format.hpp> 
#include <iostream> 

int main() 
{ 
  std::cout << boost::format("%|1$+| %2% %1%") % 99 % 100 << std::endl; 
} 
#include <boost/filesystem.hpp> 
#include <iostream> 

int main() 
{ 
  boost::filesystem::path p("C:\\Windows\\System"); 
  std::cout << p.string() << std::endl; 
  std::cout << p.file_string() << std::endl; 
  std::cout << p.directory_string() << std::endl; 
} 
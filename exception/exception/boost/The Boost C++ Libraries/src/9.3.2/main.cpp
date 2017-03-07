#include <boost/filesystem.hpp> 
#include <iostream> 

int main() 
{ 
  boost::filesystem::path p("C:\\Windows\\win.ini"); 
  try 
  { 
    std::cout << boost::filesystem::file_size(p) << std::endl; 
  } 
  catch (boost::filesystem::filesystem_error &e) 
  { 
    std::cerr << e.what() << std::endl; 
  } 
} 
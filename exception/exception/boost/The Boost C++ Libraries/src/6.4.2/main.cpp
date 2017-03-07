#include <boost/thread.hpp> 
#include <iostream> 
#include <cstdlib> 
#include <ctime> 

void init_number_generator() 
{ 
  static boost::thread_specific_ptr<bool> tls; 
  if (!tls.get()) 
    tls.reset(new bool(false)); 
  if (!*tls) 
  { 
    *tls = true; 
    std::srand(static_cast<unsigned int>(std::time(0))); 
  } 
} 

boost::mutex mutex; 

void random_number_generator() 
{ 
  init_number_generator(); 
  int i = std::rand(); 
  boost::lock_guard<boost::mutex> lock(mutex); 
  std::cout << i << std::endl; 
} 

int main() 
{ 
  boost::thread t[3]; 

  for (int i = 0; i < 3; ++i) 
    t[i] = boost::thread(random_number_generator); 

  for (int i = 0; i < 3; ++i) 
    t[i].join(); 
} 
#include <boost/signal.hpp> 
#include <boost/bind.hpp> 
#include <iostream> 
#include <memory> 

class world : 
  public boost::signals::trackable 
{ 
  public: 
    void hello() const 
    { 
      std::cout << "Hello, world!" << std::endl; 
    } 
}; 

int main() 
{ 
  boost::signal<void ()> s; 
  { 
    std::auto_ptr<world> w(new world()); 
    s.connect(boost::bind(&world::hello, w.get())); 
  } 
  std::cout << s.num_slots() << std::endl; 
  s(); 
} 
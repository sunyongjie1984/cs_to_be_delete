#include "thread.h"
class my_thread : public CThread {
public:
    my_thread() {}
    long Run()
    {
        std::cout << " " << __FILE__ << " " << __LINE__ << std::endl;
        return 0;
    }
};

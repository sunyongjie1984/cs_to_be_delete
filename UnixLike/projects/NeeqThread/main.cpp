#include <iostream>
#include "my_thread.h"

int main(int argc, char **argv)
{
    my_thread t1;
    t1.Start();
    sleep(5);
    t1.Stop();
    return 0;
}

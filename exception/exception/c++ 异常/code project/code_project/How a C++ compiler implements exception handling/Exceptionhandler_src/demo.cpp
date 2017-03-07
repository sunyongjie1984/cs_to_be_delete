#include "install_my_handler.h"
#include <iostream>

using std::cout;
using std::endl;

namespace
{
    void install_my_exc_handler()
    {
       if(my_handler::install_my_handler())
            cout<<"using my exception handler..."<<endl;
        else
            cout<<"failure in installing my handler"<<endl;
    }

    int g_i = 0;

    class E
    {
    };

    void foo()
    {
        try
        {
            cout<<"in foo()"<<endl;
            if(0 == g_i)
                throw E();
            cout<<"exiting foo()"<<endl;
        }
        catch(E&)
        {
            cout<<"caught E exception"<<endl;
        }
    }
}

int main()
{
    foo();  //use vc++ default exception handler.
    install_my_exc_handler();
    foo();
    return 0;
}
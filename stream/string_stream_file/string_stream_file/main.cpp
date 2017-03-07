#include <string>
#include <sstream>
#include <time.h>
#include <fstream>

int main()
{
    time_t t;
    char tmp[64];
    char b[10] = "hello";

    t = time(0); 
    strftime(tmp, sizeof(tmp), "%Y%m%d\_%H%M%S\_",localtime(&t));

    std::string file_name;
    std::string prefix = "..\\log\\";
    prefix += tmp;

    int test = 20;
    std::stringstream ss;
    ss << test;
    ss >> file_name;


    file_name = prefix + file_name;

    std::ofstream ofs;
    ofs.open(file_name.c_str(), std::ios_base::app);
    if (!ofs.bad())
    {
        //ofs << Ret << '\_' << b << std::endl;
        ofs << b;
        ofs.close();
    }
}
#include <iostream>
#include	"unp.h"

int main(int argc, char **argv)
{
    union {
        short  s;
        char   c[sizeof(short)];
    } un;

    un.s = 0x0103;
    std::cout << "un.s =: " << un.s << std::endl;
    printf("%s: ", CPU_VENDOR_OS);
    if (sizeof(short) == 2)
    {
        if (un.c[0] == 1 && un.c[1] == 3)
            printf("big-endian\n");
        else if (un.c[0] == 3 && un.c[1] == 1)
            printf("little-endian\n");
        else
            printf("unknown\n");
    }
    else
        printf("sizeof(short) = %d\n", static_cast<int>(sizeof(short)));

    exit(0);
}

#include <iostream>
using namespace std;
int main()
{
    char *p1;
    char *p2;
    p1=(char*)malloc(25);
    p2=(char*)malloc(25);
    strcpy(p1, "Cisco");
    strcpy(p2, "systems");
    strcat(p1, p2);
    printf("%s", p1);
    return 0;
}

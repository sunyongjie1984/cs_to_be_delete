#include <stdio.h>
//#include <list>
#include <list.h>
#include <string.h>
main()
{
    list<int> str;
    str.push_back(10);
    str.push_back(20);
    str.push_front(30);
    str.push_front(40);
    
    list<int>::iterator iter;
    for(iter = str.begin();iter!=str.end();iter++)
	printf("%d\n",*iter);

    printf("num is %d\n",str.size());
}

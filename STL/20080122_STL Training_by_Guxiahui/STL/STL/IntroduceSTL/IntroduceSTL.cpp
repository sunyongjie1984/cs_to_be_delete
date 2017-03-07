// IntroduceSTL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>

int main(int argc, char* argv[])
{
    std::vector<int> v(3); 
    v[0] = 7;
    v[1] = v[0] + 3;
    v[2] = v[0] + v[1]; 
    printf("Test OutPut:%d,%d,%d!\n", v[0],v[1],v[2]);
    std::vector<int>::reverse_iterator ri = v.rbegin();
     printf("%d\n", *ri);
     printf("%d\n", *((ri).base()));
     ri++;
     ri++;
    printf("%d\n", *((ri).base()));    
	
//     std::reverse(v.begin(), v.end()); 
//     printf("Test OutPut:%d,%d,%d!\n", v[0],v[1],v[2]);
//     std::vector<int> v1(3); 
//     v1 = v;
//     printf("Test OutPut:%d,%d,%d!\n", v1[0],v1[1],v1[2]);
	return 0;
}


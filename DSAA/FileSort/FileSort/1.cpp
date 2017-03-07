//copyright@ yansha  
//July、2010.05.30。  
//位图方案解决10^7个数据量的文件的排序问题  
//如果有重复的数据，那么只能显示其中一个 其他的将被忽略  
#include <iostream>  
#include <bitset>  
#include <assert.h>  
#include <time.h>  
using namespace std;  

const int max_each_scan = 5000000;  

int main()  
{  
    clock_t begin = clock();  
    bitset<max_each_scan> bit_map;  
    bit_map.reset();  

    // open the file with the unsorted data  
    FILE *fp_unsort_file = fopen("data.txt", "r");  
    assert(fp_unsort_file);  
    int num;  

    // the first time scan to sort the data between 0 - 4999999  
    while (fscanf(fp_unsort_file, "%d ", &num) != EOF)  
    {  
        if (num < max_each_scan)  
            bit_map.set(num, 1);  
    }  

    FILE *fp_sort_file = fopen("sort.txt", "w");  
    assert(fp_sort_file);  
    int i;  

    // write the sorted data into file  
    for (i = 0; i < max_each_scan; i++)  
    {  
        if (bit_map[i] == 1)  
            fprintf(fp_sort_file, "%d ", i);  
    }  

    // the second time scan to sort the data between 5000000 - 9999999  
    int result = fseek(fp_unsort_file, 0, SEEK_SET);  
    if (result)  
        cout << "fseek failed!" << endl;  
    else  
    {  
        bit_map.reset();  
        while (fscanf(fp_unsort_file, "%d ", &num) != EOF)  
        {  
            if (num >= max_each_scan && num < 10000000)  
            {  
                num -= max_each_scan;  
                bit_map.set(num, 1);  
            }  
        }  
        for (i = 0; i < max_each_scan; i++)  
        {  
            if (bit_map[i] == 1)  
                fprintf(fp_sort_file, "%d ", i + max_each_scan);  
        }  
    }  

    clock_t end = clock();  
    cout<<"用位图的方法，耗时："<<endl;  
    cout << (end - begin) / CLK_TCK << "s" << endl;  
    fclose(fp_sort_file);  
    fclose(fp_unsort_file);  
    return 0;  
}  
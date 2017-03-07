//给char*一个名分
//char* 不停的问自己：我是字符串还是指针？谁能给我一个名份？
#include <iostream>
#include <string>
// add for FR ddd test

using namespace std;

char* GetName(int nID)
{
    if(nID > 0)
    {
        return "Name";
    }
    else
    {
        return NULL;
    }
    // return "";
}
// add started get const name 2011_11_30_syj
const char* GetConstName(int nID)
{
    if(nID > 0)
    {
        return "Name";
    }
    else
    {
        return NULL;  
    }
}
// add end get const name 2011_11_30_syj

int main()
{
    string strName = GetName(1);
    cout << strName << endl;
    // strName = GetName(0);       // run error
    // cout << strName << endl;    // 我认为原因是，GetName应该返回一个空字符串就好了"" 
    // 试了一下，果然可以。

    const string strConstName = GetConstName(1);
    cout << strConstName << endl;

    // const string strConstName2 = GetConstName(0); //run error
    // cout << strConstName2 << endl;
    return 0;
}

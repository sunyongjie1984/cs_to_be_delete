#include <iostream>
using namespace std;
int main()
{
    const int up=1001;
    int a[up];
    for (int i=1; i<up; i++)
    {
        a[i]=i;
    }
    for (i=2; i<up; i++)
    {
        if (a[i]!=0)
            for (int j=i+1; j < up; )
            {
                if (j%i==0)
                    a[j]=0;
                j=j+1;
            }
    }
    int j=0;
    for (i=2; i<up; i++)
    {
        // static int j = 0;
        if (a[i]!=0)
        {
            cout<<i<<' ';

            // 我自己加的想要实现每10个一换行。设置j还开始错了，怎么都不知道怎么弄实在是
            j++;                                                        // 太笨了，呵呵。
            if((j%10)==0)
                cout<<"\n";
        }
    }
    cout<<"\n"<<"一共有 "<<j<<" 个素数"<<endl;
    return 0;
}

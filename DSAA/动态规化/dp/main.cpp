#include <iostream>
using namespace std;

//动态规划：0-1背包问题
//bestValue[i][j]=max ( bestValue[i+1][j-w[i]]+v[i] ,bestValue[i+1][j] )  w[i]<=j
//bestValue[i][j]=bestValue[i+1][j]        w[i]>j

class Knapsack
{
private:
    int *weight;        //物品重量数组
    int *value;         //物品价值数组
    int numOfItems;     //物品数量
    int bagSpace;       //背包容量
    int **bestValue;    //动态规划表格，记录bestValue[i][j]的价值，为最优价值，i表示物品i...n装入容量为j的背包能达到的最大价值
    int **path;         //为了求出取得最优值时的解，记录动态规划表不同表项的选择与否
public:
    //构造函数
    Knapsack(int numOfItems,int bagSpace)
    {
        weight=new int[numOfItems+1];
        value=new int[numOfItems+1];
        this->bagSpace=bagSpace;
        this->numOfItems=numOfItems;

        bestValue=new int* [numOfItems+1];
        for(int i=0;i<numOfItems+1;i++)
        {
            bestValue[i]=new int[bagSpace+1];
        }

        path=new int* [numOfItems+1];
        for(int i=0;i<numOfItems+1;i++)
        {
            path[i]=new int[bagSpace+1];
        }
    }
    //输入物品的重量与价值
    void input()
    {
        int i=1;
        while(i<=numOfItems)
        {
            cout<<"输入第"<<i<<"个物品的重量"<<endl;
            cin>>weight[i];
            cout<<"输入第"<<i<<"个物品的价值"<<endl;
            cin>>value[i];
            ++i;
        }
    }
    //动态规划核心算法
    void knapsack()
    {
        //初始化递归最底层,即将bestValue[n][0:c]进行初始化
        for(int i=0;i<=bagSpace;i++)
        {
            if(weight[numOfItems]<=i)
            {
                bestValue[numOfItems][i]=value[numOfItems];
                path[numOfItems][i]=1;
            }
            else
            {
                bestValue[numOfItems][i]=0;
                path[numOfItems][i]=0;
            }
        }
        //递推的进行动态规划，自底向上，最终bestValue[1][bageSpace]为1-n物品放入容量bagSpace内的最大价值
        for(int k=numOfItems-1;k>=1;k--)
        {
            for(int j=0;j<=bagSpace;j++)
            {
                bestValue[k][j]=bestValue[k+1][j];
                path[k][j]=0;//不放入的情况
                if(weight[k]<=j)//如果容量足够放入当前物品
                {
                    if(bestValue[k+1][j-weight[k]]+value[k]>bestValue[k][j])//如果放入的价值大于不放的价值
                    {
                        bestValue[k][j]=bestValue[k+1][j-weight[k]]+value[k];
                        path[k][j]=1;//那么就选择放入
                    }
                }
            }
        }
    }
    //输出最大价值，并且输出选择方式
    void display()
    {
        //打印出bestValue[1][bagSpace],表示1...numOfItems的物品装入容量为bagSpace的最大价值
        int i=1;
        int j=bagSpace;
        cout<<"最大价值为"<<bestValue[1][j]<<endl;
        //根据path[1][bagSpace]的记录开始，递归到path[n][某容量],从而打印出每个物品是否被选择进入背包
        while(i<=numOfItems)
        {
            if(path[i][j]==0)//如果i物品没被放入，看i+1个物品装入容量j背包
            {
                ++i;
            }
            else
            {
                cout<<"<重量:"<<weight[i]<<"，价值:"<<value[i]<<">" << endl;
                j-=weight[i];
                ++i;
            }
        }
    }
};

void main()
{
    // 0/1背包问题:设有4个物体,其重量分别为(4,7,5,3),价值为(40,42,25,12),背包容量W = 10
    Knapsack test(4,10); // 4个物品，背包容量10
    test.input();        // 输入4个物品的价值与重量
    test.knapsack();     // 动态规划
    test.display();      // 打印选择与最大价值
}

#include"GreedyAlgorithm.h"

//================================
//函数名称：GreedyAlgorithm
//函数功能：初始化对象
//函数参数说明:_weight[] 物品重量,_value[] 物品价值,_capacity 背包容量
//函数返回值：void
//创建时间：2009-04-28
//更新：
//================================
GreedyAlgorithm::GreedyAlgorithm(int _weight[],int _value[],int _capacity){

    this->weight=_weight;
    this->value=_value;
    this->capacity=_capacity;
    this->profit=0;
    return;
}

//================================
//函数名称：ComputeRatio
//函数功能：计算出物品的单位价值
//函数参数说明:
//函数返回值：double *
//创建时间：2009-04-28
//更新：
//================================
double *GreedyAlgorithm::ComputeRatio(){
    double *Ratio=new double[5];
    for(int i=0;i<5;i++)
        Ratio[i]=(double)value[i]/weight[i];
    return Ratio;
}

//================================
//函数名称：SortRatio
//函数功能：根据单位价值比大小，对物品的价值和重量进行排序
//函数参数说明:
//函数返回值：void
//创建时间：2009-04-28
//更新：
//================================
void GreedyAlgorithm::SortRatio(double _Ratio[]){
    for(int i=0;i<5;i++)
        for(int j=i+1;j<5;j++)
        {
            if(_Ratio[j]>_Ratio[i]){
                int temp=weight[i];
                weight[i]=weight[j];
                weight[j]=temp;
                temp=value[i];
                value[i]=value[j];
                value[j]=temp;
            }
        }
        return;
}
//================================
//函数名称：ComputeProfit
//函数功能：计算背包的内所放物品的最大价值
//函数参数说明:
//函数返回值：double
//创建时间：2009-04-28
//更新：
//================================
double GreedyAlgorithm::ComputeProfit()
{
    int temp=0;
    int i=0;
    while(temp<=capacity){
        if(i==5)	break;
        else{
            if((weight[i]+temp)<=capacity){
                profit+=value[i];
                temp+=weight[i];
            }
            else if((weight[i]+temp)>capacity){
                int _weight=capacity-temp;
                double _Ratio=(double)value[i]/weight[i];
                profit+=_Ratio*_weight;
                temp+=_weight;
            }

        }
        i++;
    }
    return profit;
}
#include <stdio.h>
#define W 1000
#define N 1000

typedef struct data
{
    int vaule;
    int weight;
}goods;

int returnmax(int a, int b)
{
    return (a > b ? a : b);
}

int KNAPSACK(goods *P, int a, int s)
{
    int V[N][W];
    int i,j,mv;
    for(i = 0; i < a; i++)
        V[i][0] = 0;
    for(j = 0; j < s; j++)
        V[0][j] = 0;
    for(i = 1; i <= a; i++)
        for(j = 1; j <= s; j++)
        {
            V[i][j] = V[i - 1][j];
            if(P[i].weight <= j)
                V[i][j] = returnmax(V[i][j],V[i - 1][j - P[i].weight] + P[i].vaule);
        }
        mv = V[a][s];
        return mv;
}

int main()
{
    int mostvalue,amount,size,i;
    goods A[N];
    printf("Input how much the goods have: ");
    scanf("%d",&amount);
    printf("Input the size of the bag: ");
    scanf("%d",&size);
    printf("Input the data of the goods: ");
    for(i = 0; i < amount; i++)
        scanf("%d %d",&A[i].vaule,&A[i].weight);
    mostvalue = KNAPSACK(A,amount,size);
    printf("%d",mostvalue);
    return 0;
}
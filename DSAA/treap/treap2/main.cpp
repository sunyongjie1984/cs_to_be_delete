#include <iostream>
#include <ctime>
#define MAX 100

using namespace std;

typedef struct
{
    int l,r,key,fix;
}node;

class treap
{
public:
    node p[MAX];
    int size,root;
    treap()
    {
        srand(time(0));
        size=-1;
        root=-1;
    }

    void rot_l(int &x)  //看上面的图解
    {
        int y=p[x].r;
        p[x].r=p[y].l;
        p[y].l=x;
        x=y;
    }

    void rot_r(int &x) //看上面的图解
    {
        int y=p[x].l;
        p[x].l=p[y].r;
        p[y].r=x;
        x=y;
    }

    void insert(int &k,int tkey)
    {
        if (k==-1) //根节点为空，空树
        {
            k=++size;
            p[k].l=p[k].r=-1;//左右子树置为空
            p[k].key=tkey;//保存关键字
            p[k].fix=rand();//生产一个随机的优先级
        }
        else
            if (tkey<p[k].key)  //按照二叉查找树的规律去插入
            {
                insert(p[k].l,tkey);
                if (p[ p[k].l ].fix>p[k].fix) //但是插完不满足条件要进行旋转
                    rot_r(k);
            }
            else
            {
                insert(p[k].r,tkey);
                if (p[ p[k].r ].fix>p[k].fix)
                    rot_l(k);
            }

    }

    void remove(int &k,int tkey)  //删除节点
    {
        if (k==-1) return;
        if (tkey<p[k].key)  //按照而叉查找树的规律去查找
            remove(p[k].l,tkey);
        else if (tkey>p[k].key)
            remove(p[k].r,tkey);
        else
        {
            if (p[k].l==-1 && p[k].r==-1) //被删除的是叶子节点，直接删除
                k=-1;
            else if (p[k].l==-1)  //被删除的左孩子节点为空
                k=p[k].r;
            else if (p[k].r==-1) //被删除的有孩子节点为空
                k=p[k].l;
            else
                if (p[ p[k].l ].fix < p[ p[k].r ].fix)  //选择孩子节点小的方向旋转
                {
                    rot_l(k);
                    remove(p[k].l,tkey);
                }
                else
                {
                    rot_r(k);
                    remove(p[k].r,tkey);
                }
        }
    }

    void print(int k)  //中序遍历
    {
        if (p[k].l!=-1)
            print(p[k].l);
        cout << p[k].key << " : " << p[k].fix << endl;
        if (p[k].r!=-1)
            print(p[k].r);
    }
};

treap T;

int main()
{

    int i;
    for (i=8;i>=1;i--)
        T.insert(T.root,i);
    cout<<"插入节点之后："<<endl;
    T.print(T.root);
    for (i=3;i>=1;i--)
    {
        cout << "删除key为"<<i<<"的节点："<<endl;
        T.remove(T.root,i);
        T.print(T.root);
    }
    system("pause");
    return 0;
}
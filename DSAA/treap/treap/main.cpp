/* 
LANG: C++ 
Author By : YangZX
一个以Treap实现的BST模板，支持的操作比较齐全：
1.void insert(T x) 将x插入平衡树
2.void erase(T) 将一个x从平衡树中移除
3.T select(int kth) 返回第k小的元素
4.void sort(T* arr) 按照从小到大顺序将所有元素输出到arr
5.int count(T) 返回T在树中的个数
*/ 
#include <iostream>
#include <time.h>
using namespace std;
template<typename T>
class BST
{
public:
    void insert(const T& x);
    void erase(const T& x);
    int count(const T& x);
    const T& select(int kth);
    void sort(T* arr);
    int size();
    BST(int n);
    ~BST();
private:
    typedef int Treap;
    int newnode();
    void SRL(Treap&);
    void SRR(Treap&);
    void foreach(Treap &rt, T* arr);
    const T& slt(int kth, Treap &rt);
    int bstcnt(const T& x, Treap &rt);
    void ers(const T&, Treap& rt);
    void ins(const T&, Treap& rt);
    Treap rt;
    struct node{
        Treap L, R;
        T v;
        int num, size, prio;
    }*Tree;
    int cnt, sortcnt;
    static const int MAXPRIO = 1 <<28;
};
template<typename T>
BST<T>::BST(int x)
{
    srand(time(NULL));
    Tree = new node[x];
    cnt = rt = 0;
    Tree[0].prio = MAXPRIO;
}
template<typename T>
BST<T>::~BST()
{
    delete[] Tree;
}
template<typename T>
int BST<T>::size()
{
    if(!rt)
        return 0;
    return Tree[rt].size;
}
template<typename T>
int BST<T>::count(const T& x)
{
    bstcnt(x, rt);
}
template<typename T>
void BST<T>::foreach(Treap &rt, T* arr)
{
    if(!rt)
        return;
    foreach(Tree[rt].L, arr);
    for(int i=1; i<=Tree[rt].num; i++)
        arr[sortcnt++] = Tree[rt].v;
    foreach(Tree[rt].R, arr);
}
template<typename T>
int BST<T>::bstcnt(const T& x, Treap &rt)
{
    if(!rt)
        return 0;
    if(Tree[rt].v == x)
        return Tree[rt].num;
    if(x < Tree[rt].v)
        return bstcnt(x, Tree[rt].L);
    else
        return bstcnt(x, Tree[rt].R);
}
template<typename T>
void BST<T>::sort(T* a)
{
    sortcnt = 0;
    foreach(rt, a);
}
template<typename T>
int BST<T>::newnode()
{
    Tree[++cnt].prio = rand();
    Tree[cnt].L = Tree[cnt].R = 0;
    return cnt;
}
template<typename T>
const T& BST<T>::select(int k)
{
    return slt(k, rt);
}
template<typename T>
const T& BST<T>::slt(int k, Treap &rt)
{
    if(k >= Tree[Tree[rt].L].size + 1 && k <= Tree[Tree[rt].L].size + Tree[rt].num)
        return Tree[rt].v;
    else if(k <= Tree[Tree[rt].L].size)
        return slt(k, Tree[rt].L);
    else
        return slt(k - Tree[Tree[rt].L].size - Tree[rt].num, Tree[rt].R);
}
template<typename T>
void BST<T>::insert(const T& x)
{
    ins(x, rt);
}
template<typename T>
void BST<T>::ins(const T& x, Treap& rt)
{
    if(!rt){
        rt = newnode();
        Tree[rt].v = x;
        Tree[rt].num = Tree[rt].size = 1;
        return;
    }
    if(Tree[rt].v == x){
        Tree[rt].num++;
        Tree[rt].size++;
        return;
    }else if(x < Tree[rt].v){
        ins(x, Tree[rt].L);
        if(Tree[Tree[rt].L].prio < Tree[rt].prio)
            SRL(rt);
    }else{
        ins(x, Tree[rt].R);
        if(Tree[Tree[rt].R].prio < Tree[rt].prio)
            SRR(rt);
    }
    Tree[rt].size = Tree[Tree[rt].L].size + Tree[Tree[rt].R].size + Tree[rt].num;
}
template<typename T>
void BST<T>::erase(const T& x)
{
    ers(x, rt);	
}
template<typename T>
void BST<T>::ers(const T& x, Treap &rt)
{
    if(!rt)
        return;
    if(Tree[rt].v == x && Tree[rt].num > 0){
        Tree[rt].num--;
        Tree[rt].size--;
        return;
    }else if(Tree[rt].v == x)
        return;
    if(x < Tree[rt].v)
        ers(x, Tree[rt].L);
    else
        ers(x, Tree[rt].R);
    Tree[rt].size = Tree[Tree[rt].L].size + Tree[Tree[rt].R].size + Tree[rt].num;
}
template<typename T>
void BST<T>::SRL(Treap &rt)
{
    Treap L;
    L = Tree[rt].L;
    Tree[rt].L = Tree[L].R;
    Tree[L].R = rt;
    Tree[rt].size = Tree[Tree[rt].L].size + Tree[Tree[rt].R].size + Tree[rt].num;
    Tree[L].size = Tree[rt].size + Tree[Tree[L].L].size + Tree[L].num;
    rt = L;
}
template<typename T>
void BST<T>::SRR(Treap &rt)
{
    Treap R;
    R = Tree[rt].R;
    Tree[rt].R = Tree[R].L;
    Tree[R].L = rt;
    Tree[rt].size = Tree[Tree[rt].L].size + Tree[Tree[rt].R].size + Tree[rt].num;
    Tree[R].size = Tree[rt].size + Tree[Tree[R].R].size + Tree[R].num;
    rt = R;
}

/*Demo*/
int main()
{
    int n;
    int k;
    cin>>n>>k;
    int i, x;
    BST<int> st(n);
    for(i=1; i<=n; i++){
        cin>>x;
        st.insert(x);
    }
    cout<<st.select(k)<<endl;
    getchar();
    return 0;
}
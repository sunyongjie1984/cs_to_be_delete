#include <iostream>

#ifdef __linux
#include <stdio.h>
#endif

using namespace std;

template <class T>
class BSTNode
{
public:
    BSTNode(T k=0,BSTNode<T> *l=NULL, BSTNode<T> *r=NULL, BSTNode<T> *p=NULL):
        left(l),right(r),parent(p),data(k){};
    ~BSTNode(){};
    BSTNode<T> *left;
    BSTNode<T> *right;
    BSTNode<T> *parent;
    T data;
};

template <class T>
class BST
{
public:
    BST(BSTNode<T> *r=NULL):root(r){};
    ~BST();
    void Inorder(BSTNode<T> *x);
    BSTNode<T>* search(T k,BSTNode<T> *x);
    BSTNode<T>* min(BSTNode<T> *x);
    BSTNode<T>* max(BSTNode<T> *x);
    BSTNode<T>* successor(BSTNode<T> *x);
    void Insert(BSTNode<T> *z);
    void Delete(BSTNode<T> *z);
    BSTNode<T>* root;
};

template <class T>
void BST<T>::Inorder(BSTNode<T> *x)
{
    if(x == NULL)
        return;
    Inorder(x->left);
    cout << x->data << " ";
    Inorder(x->right);
}

template <class T>
BSTNode<T>* BST<T>::search(T k,BSTNode<T> *x)
{
    if(x==NULL || x->data==k)
        return x;
    BSTNode<T> *p=x;
    while(p!=NULL && p->data!=k)
    {
        if(k<(p->data))
            p=p->left;
        else
            p=p->right;
    }
    return p;
}

template <class T>
BSTNode<T>* BST<T>::min(BSTNode<T> *x)
{
    if(x==NULL)
        return NULL;
    BSTNode<T> *p=x;
    while(p->left!=NULL)
        p=p->left;
    return p;
}

template <class T>
BSTNode<T>* BST<T>::max(BSTNode<T> *x)
{
    if(x==NULL)
        return NULL;
    BSTNode<T> *p=x;
    while(p->right!=NULL)
        p=p->right;
    return p;
}

template <class T>
BSTNode<T>* BST<T>::successor(BSTNode<T> *x)
{
    if(x->right!=NULL)
        return min(x->right);
    BSTNode<T> *p=x->parent;
    BSTNode<T> *y=x;
    while(p!=NULL && p->right==y)
    {
        y=p;
        p=p->parent;
    }
    return p;
}

template <class T>
void BST<T>::Insert(BSTNode<T> *z)
{
    BSTNode<T> *x=root;
    BSTNode<T> *y=NULL;
    while(x!=NULL)
    {
        y=x;
        if(z->data < x->data)
            x=x->left;
        else
            x=x->right;
    }
    z->parent=y;
    if(y==NULL)
        root=z;
    else
    {
        if(z->data < y->data)
            y->left=z;
        else
            y->right=z;
    }
}

template <class T>
void BST<T>::Delete(BSTNode<T> *z)
{
    BSTNode<T> *y;
    BSTNode<T> *x=NULL;
    if(z->right==NULL || z->left==NULL)
        y=z;
    else
        y=successor(z);
    if(y->left!=NULL)
        x=y->left;
    else
        x=y->right;
    if(x!=NULL)
        x->parent=y->parent;
    if(y->parent==NULL)
        root=x;
    else
    {
        if(y->parent->left==y)
            y->parent->left=x;
        else
            y->parent->right=x;
    }
    if(y!=z)
        z->data=y->data;
}

int main()
{
    BSTNode<int> *root=new BSTNode<int>(5);
    BSTNode<int> *a1=new BSTNode<int>(3);
    BSTNode<int> *a2=new BSTNode<int>(8);
    BSTNode<int> *a3=new BSTNode<int>(4);
    BSTNode<int> *a4=new BSTNode<int>(2);
    BSTNode<int> *a5=new BSTNode<int>(9);
    BSTNode<int> *a6=new BSTNode<int>(7);
    BSTNode<int> *a7=new BSTNode<int>(10);
    BSTNode<int> *a8=new BSTNode<int>(1);
    BSTNode<int> *a9=new BSTNode<int>(6);

    BST<int> *T=new BST<int> (root);
    T->Insert(a1);
    T->Insert(a2);
    T->Insert(a3);
    T->Insert(a4);
    T->Insert(a5);
    T->Insert(a6);
    T->Insert(a7);
    T->Insert(a8);
    T->Insert(a9);

    T->Inorder(T->root);

    cout << endl;
    cout << (T->max(T->root))->data << endl;
    cout << (T->min(T->root))->data << endl;
    cout << T->successor(a8)->data << endl;
    T->Delete(T->search(3,T->root));

    T->Inorder(T->root);

    getchar();

}

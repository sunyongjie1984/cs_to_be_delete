#ifndef _TS_BBST
#define _TS_BBST

// ¶¯Ì¬ Æ½ºâ¶þ²æÅÅÐòÊ÷
#include <iostream>
#include <vector>
#include <string>

// const int maxint = ((signed int)(((unsigned int)~((unsigned int)0)) >> 1));
const int maxint = 0x7FFFFFFF;

const int LH = 1;
const int EH = 0;
const int RH = -1;

class BSTNode {
public:
    BSTNode() : key(0), bf(0), ltag(false), rtag(false), left(nullptr), right(nullptr), father(nullptr), val(nullptr) { }
    BSTNode(BSTNode& a);
    friend class myBST;
private:
    int key;
    int bf;
    bool ltag;
    bool rtag;
    BSTNode* left;
    BSTNode* right;
    BSTNode* father;
    void* val;
};

class myBST {
public:
    myBST(bool flag_next = true) : m_root(nullptr), m_curr(nullptr), m_b_first(true)
        , m_current(nullptr), m_b_next(flag_next), m_low(0), m_high(maxint) {}
    
    
    int first_valid(void*& val);
    int next_valid(void*& val);
    void set_valid_range(int const low, int const high) { m_low = low; m_high = 0 == high ? maxint : high; }
    void print_info();      // print inorder

    
    
    
    
    
    int search(int e, void*& val);

    void print_inorder();      // print inorder
    void print_preorder();      // print inorder
    void print_levelorder();      // print inorder
    void print_inorder_no_bf();      // print inorder
    void print_inorder_valid_range();      // print inorder
    void print_by_next();      // print by next
    void print_by_pre();      // print by next

    int delete_node(int e, void* val);
    int insert_node(int e, void* val);

    int search_in_validrange(int const e, int const compare, void*& val);
    int first(void*& val);
    int end(void*& val);
    int pre(void*& val);
    int next(void*& val);
    int pre_valid(void*& val, int const compare);
    int next_valid(void*& val, int const compare);

    int first_buy_valid(int const price,  int const compare_price, void*& val);
    int first_sale_valid(int const price, int const compare_price, void*& val);

private:
    int first(BSTNode*& val);
    int end(BSTNode*& val);
    int pre_node (const BSTNode* p, BSTNode*& q);
    int next_node(const BSTNode* p, BSTNode*& q);

    bool delete_node(BSTNode* p);
    BSTNode* insert(int e, BSTNode*& in);
//     int delete_avl_not_recusive(int e, bool& shorter);
    BSTNode* search_add(int e, BSTNode*& in);
//     bool delete_node(int e);
    void left_balance(BSTNode*& p);
    void left_balance_for_del(BSTNode*& p, bool& shorter);
    void right_balance(BSTNode*& p);
    void right_balance_for_del(BSTNode*& p, bool& shorter);
    int insert_avl(int e, void* val, bool& taller);
    int delete_avl(int e, void* val, bool& shorter);
    void inorder(BSTNode* p); // in order print
    void preorder(BSTNode* p); // in order print
    void levelorder(BSTNode* p); // in order print
    void inorder_no_bf(BSTNode* p); // in order print
    void inorder_valid_range(BSTNode* p); // in order print
    void left_rotate(BSTNode*& p);
    void right_rotate(BSTNode*& p);
    BSTNode* m_root;
    BSTNode* m_curr;
    bool m_b_first;
    BSTNode* m_current;
    bool m_b_next; // default next method call for bigger key, like saletray

    int m_low;
    int m_high;
    std::string m_log_str;
};

#endif
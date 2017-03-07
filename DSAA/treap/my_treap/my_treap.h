#ifndef MY_TREAP
#define MY_TREAP

#include <iostream>
#include <stdint.h>
#include <time.h>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::endl;

template <class TYPE> class my_treap;

template <class TYPE>
class treap_node {
public:
    friend class my_treap<TYPE>;
    treap_node() : key(0), ltag(false), rtag(false), left(nullptr), right(nullptr), val(nullptr), priority(0) { }
private:
    TYPE key;
    bool ltag;
    bool rtag;
    treap_node* left;
    treap_node* right;
    void* val;
    uint64_t priority;
};

template <class TYPE>
class my_treap
{
public:
    my_treap(bool saletray = true) : m_root(nullptr), m_curr(nullptr), m_low(0), m_high(UINT64_MAX), m_b_saletray(saletray), m_p_for_search_or_insert(nullptr)
    {
        srand(static_cast<unsigned int>(time(0)));
        // srand(7);
    }
    ~my_treap() { }
    uint64_t first(void*& val);
    uint64_t insert(TYPE const key, void* const val);
    uint64_t del(TYPE key);
    uint64_t successor(treap_node<TYPE>* p, treap_node<TYPE>*& q);
    uint64_t predecessor(treap_node<TYPE>* p, treap_node<TYPE>*& q);
    void set_valid_range(TYPE const low, TYPE const high) { m_low = low; m_high = high; }
    uint64_t search_in_valid_range(TYPE const key, TYPE const compare_key, void*& val);
    void print_inorder();
    void print_levelorder();
    void print_levelorder_no_priority();
private:
    uint64_t insert_implement(bool is_tag, treap_node<TYPE>*& p, TYPE const key, void* const val);
    uint64_t del_implement(bool p_is_left, treap_node<TYPE>*& p, TYPE const key);
    uint64_t search_in_valid_range_implement(treap_node<TYPE>*& p,TYPE const key, TYPE const compare_key, void*& val);
    uint64_t search_in_valid_range_implement_successor(treap_node<TYPE>*& p,TYPE const key, TYPE const compare_key, void*& val);
    void right_roate(treap_node<TYPE>*& p);
    void left_roate(treap_node<TYPE>*& p);
    void inorder(treap_node<TYPE>* p);
    void levelorder(treap_node<TYPE>* p);
    void levelorder_no_priority(treap_node<TYPE>* p);
    uint64_t gen_priority(TYPE const key);
    treap_node<TYPE>* m_root;
    treap_node<TYPE>* m_curr;
    TYPE m_low;
    TYPE m_high;
    bool m_b_saletray;
    treap_node<TYPE>* m_p_for_search_or_insert;

};

template <class TYPE> uint64_t my_treap<TYPE>::first(void*& val)
{
    return m_b_saletray ? search_in_valid_range(m_low, m_high, val) : search_in_valid_range(m_high, m_low, val);
}

template <class TYPE> uint64_t my_treap<TYPE>::insert(TYPE const key, void* const val)
{
    if (nullptr == m_root)
    {
        m_root = new treap_node<TYPE>;
        m_root->key = key;
        m_root->val = val;
        m_root->priority = gen_priority(key);
        return 0;
    }
    m_p_for_search_or_insert = nullptr;
    return insert_implement(false, m_root, key, val);
}

template <class TYPE> uint64_t my_treap<TYPE>::del(TYPE key)
{
    if (nullptr == m_root)
    {
        return 1;
    }
    return del_implement(0, m_root, key);
}

template <class TYPE> uint64_t my_treap<TYPE>::successor(treap_node<TYPE>* p, treap_node<TYPE>*& q)
{
    q = nullptr;
    if (p->rtag) // 右孩子是线索
    {
        q = p->right;
    }
    else
    {
        if (nullptr == p->right) // 按照线索树的性质，右孩子不是线索，右孩子又是空的，那么这个节点没有后继
        {
            q = nullptr;
        }
        else // 存在右子树
        {
            q = p->right;
            while (nullptr != q->left && !q->ltag) // found the s node ahead of p, use the data of s
            {
                q = q->ltag ? nullptr : q->left;
            }
        }
    }

    return q == nullptr ? 1 : 0 ;
}

template <class TYPE> uint64_t my_treap<TYPE>::predecessor(treap_node<TYPE>* p, treap_node<TYPE>*& q)
{
    q = nullptr;
    if (p->ltag) 
    {
        q = p->left;
    }
    else
    {
        if (nullptr == p->left) // 没有左子树，没有前驱
        {
            q = nullptr;
        }
        else
        {
            q = p->left;
            while (nullptr != q->right && !q->rtag) // found the s node ahead of p, use the data of s
            {
                q = q->rtag ? nullptr : q->right;
            }
            // 将节点s的值赋值给p，s结点没有右孩子，如果有左孩子，将左孩子接到q节点的右孩子上，因为此左孩子的data大于q的data，
            // 因为此左孩子是s结点的左孩子子，s结点的data大于q结点的data
        }
    }
    return nullptr == q ? 1 : 0;
}

template <class TYPE> uint64_t my_treap<TYPE>::search_in_valid_range(TYPE const key, TYPE const compare_key, void*& val)
{
    if (nullptr == m_root)
    {
        return 1;
    }
    m_p_for_search_or_insert = nullptr;
//     return search_in_valid_range_implement(m_root, key, compare_key, val);
    return search_in_valid_range_implement_successor(m_root, key, compare_key, val);
}

template <class TYPE> void my_treap<TYPE>::print_inorder()
{
    std::cout << "in order print start, valid range[" << m_low << ", " << m_high << "]" << std::endl;
    inorder(m_root);
    std::cout << "\nin order print end: " << std::endl;
}

template <class TYPE> void my_treap<TYPE>::print_levelorder()
{
    std::cout << "level order print start, valid range[" << m_low << ", " << m_high << "]" << std::endl;
    levelorder(m_root);
    std::cout << "level order print end: " << std::endl;
}

template <class TYPE> void my_treap<TYPE>::print_levelorder_no_priority()
{
    std::cout << "level order no priority print start, valid range[" << m_low << ", " << m_high << "]" << std::endl;
    levelorder_no_priority(m_root);
    std::cout << "level order no priority  print end: " << std::endl;
}

template <class TYPE> uint64_t my_treap<TYPE>::insert_implement(bool new_node, treap_node<TYPE>*& p, TYPE const key, void* const val)
{
    uint64_t ret = 0;
    bool b_is_new_node = false;
    treap_node<TYPE>* p_tmp;
    if (new_node || nullptr == p)
    {
        p = new treap_node<TYPE>;
        p->key = key;
        p->val = val;
        p->priority = gen_priority(key);
        return 0;
    }
    if (key == p->key)
    {
        return 1;
    }
    else if (key < p->key)
    {
        p_tmp = p->left;
        b_is_new_node = (p->ltag || !p->ltag && nullptr == p->left);
        // p->ltag is true, p_tmp is the predecessor of p
        ret = insert_implement(b_is_new_node, p->left, key, val);
        if (1 == ret) { return 1; }

        // p->key is bigger than key, p is successor of node key
        // the predecessor of p is the predecessor of node key
        if (b_is_new_node)
        {
            p->left->right = p;                                   // successor
            p->left->rtag = true;                                 
            p->left->ltag = (nullptr != (p->left->left = p_tmp)); // predecessor
            p->ltag = false;                                      // p->left is not a tag any more 
        }

        if (p->priority > p->left->priority)
        {
            right_roate(p);
        }
    }
    else
    {
        p_tmp = p->right;
        b_is_new_node = (p->rtag || !p->rtag && nullptr == p->right);
        ret = insert_implement(b_is_new_node, p->right, key, val);
        if (1 == ret) { return 1; }
        // p->key is smaller than key, p is predecessor of node key
        // the successor of p is the successor of node key
        if (b_is_new_node)
        {
            p->right->rtag = (nullptr != (p->right->right = p_tmp)); // successor
            p->right->ltag = true;                                   // predecessor
            p->right->left = p;
            p->rtag = false; // p->left is not a tag any more 
        }
        if (p->priority > p->right->priority)
        {
            left_roate(p);
        }
    }
    return 0;

}

template <class TYPE> uint64_t my_treap<TYPE>::del_implement(bool p_is_left, treap_node<TYPE>*& p, TYPE const key)
{
    uint64_t ret = 0;

    if (nullptr == p)
    {
        return 1;
    }
    if (key == p->key)
    {
        treap_node<TYPE>* q = p;
        if (nullptr != p->left && !p->ltag && nullptr != p->right && !p->rtag) // two leaves
        {
            if (p->left->priority < p->right->priority)
            {
                right_roate(p);
                del_implement(0, p->right, key);
            }
            else
            {
                left_roate(p);
                del_implement(1, p->left, key);
            }
        }
        else
        {
            treap_node<TYPE>* tmp;
            if ((p->rtag || (nullptr == p->right && !p->rtag )) && (p->ltag || (nullptr == p->left && !p->ltag ))) // leaf
            {
                // p is a left child
                if (p_is_left)
                {
                    tmp = p->right;
                    tmp->ltag = true;
                    p = p->left;

                }
                else
                {
                    // p is a right
                    tmp = p->left;
                    tmp->rtag = true;
                    p = p->right;
                }
            }
            else if ((p->ltag || (nullptr == p->left && !p->ltag ))) // there is right child
            {
                if (0 == successor(p, tmp)) // found the succ 
                {
                    if (tmp->ltag) // pre has rtag
                    {
                        tmp->left = p->left;
                        if (nullptr == p->left) // p is not the last node
                        {
                            tmp->ltag = false;
                        }
                    }
                }
                p = p->right;
            }
            else if ((p->rtag || (nullptr == p->right && !p->rtag))) // there is left child
            {
                if (0 == predecessor(p, tmp)) // found the pre 
                {
                    if (tmp->rtag) // pre has rtag
                    {
                        tmp->right = p->right;
                        if (nullptr == p->right) // p is not the last node
                        {
                            tmp->rtag = false;
                        }
                    }
                }
                p = p->left;
            }
            else // not happen
            {

            }
            delete q;
            q = nullptr;
        }
        return 0;
    }
    else if (key < p->key)
    {
        if (p->ltag)
        {
            return 1;
        }
        ret = del_implement(1, p->left, key);
        if (1 == ret) { return 1; }
    }
    else
    {
        if (p->rtag)
        {
            return 1;
        }
        ret = del_implement(0, p->right, key);
        if (1 == ret) { return 1; }
    }
    return 0;

}

template <class TYPE> 
uint64_t my_treap<TYPE>::search_in_valid_range_implement(treap_node<TYPE>*& p,TYPE const key, TYPE const compare_key, void*& val)
{
    uint64_t ret = 0;
    if (nullptr == p)
    {
        return 1; // not found
    }
    else if (key == p->key)
    {
        return 0; // found 
    }
    else if (key < p->key)
    {
        if (!m_b_saletray && p->key <= compare_key) return 2; // buy tray search for m_high, but p->key is already smaller than m_low

        if (m_b_saletray && p->key <= compare_key) m_p_for_search_or_insert = p; // sale tray search, record every node bigger than key

        if (p->ltag || (!p->ltag && nullptr == p->left))
        {
            ret = 1;
        }
        else
        {
            ret = search_in_valid_range_implement(p->left, key, compare_key, val);
        }
        if (0 == ret) return 0;
        if (1 == ret) // p is leaf
        {
            if (m_b_saletray) // for sale tray
            {
                if (p->key <= compare_key) // p->key > key
                {
                    val = p->val;
                    return 0;
                }
                return 2;
            } // for sale tray
            else // for buy tray
            {
                if (nullptr != m_p_for_search_or_insert)
                {
                    val = m_p_for_search_or_insert->val;
                    return 0;
                }
                return 2;
            } // for buy tray
        }
    }
    else
    {
        if (m_b_saletray && p->key >= compare_key) return 2; // sale tray search for m_low, but p->key is already bigger than m_hihg

        if (!m_b_saletray && p->key >= compare_key) m_p_for_search_or_insert = p; // buy tray search, record every node smaller than key

        if (p->rtag || (!p->rtag && nullptr == p->right))
        {
            ret = 1;
        }
        else
        {
            ret = search_in_valid_range_implement(p->right, key, compare_key, val);
        }
        if (0 == ret) return 0;
        if (1 == ret) // p is leaf
        {
            if (m_b_saletray) // for sale tray p->key < key
            {
                if (nullptr != m_p_for_search_or_insert)
                {
                    val = m_p_for_search_or_insert->val;
                    return 0;
                }
                return 2;
            } // for sale tray
            else // for buy tray
            {
                if (p->key >= compare_key)
                {
                    val = p->val;
                    return 0;
                }
                return 2;
            } // for buy tray
        }
    }
    return 0;
}

template <class TYPE> 
uint64_t my_treap<TYPE>::search_in_valid_range_implement_successor(treap_node<TYPE>*& p,TYPE const key, TYPE const compare_key, void*& val)
{
    uint64_t ret = 0;
    treap_node<TYPE>* q;
    if (nullptr == p)
    {
        return 1; // not found
    }
    else if (key == p->key)
    {
        return 0; // found 
    }
    else if (key < p->key)
    {
        if (!m_b_saletray && p->key <= compare_key) return 2; // buy tray search for m_high, but p->key is already smaller than m_low

        if (p->ltag || (!p->ltag && nullptr == p->left))
        {
            ret = 1;
        }
        else
        {
            ret = search_in_valid_range_implement_successor(p->left, key, compare_key, val);
        }
        if (0 == ret) return 0;
        if (1 == ret) // p is leaf
        {
            if (m_b_saletray) // for sale tray
            {
                if (p->key <= compare_key) // p->key > key
                {
                    val = p->val;
                    return 0;
                }
                return 2;
            } // for sale tray
            else // for buy tray
            {
                if (0 == predecessor(p, q))
                {
                    val = q->val;
                }
                return 2;
            } // for buy tray
        }
    }
    else
    {
        if (m_b_saletray && p->key >= compare_key) return 2; // sale tray search for m_low, but p->key is already bigger than m_hihg

        if (p->rtag || (!p->rtag && nullptr == p->right))
        {
            ret = 1;
        }
        else
        {
            ret = search_in_valid_range_implement_successor(p->right, key, compare_key, val);
        }
        if (0 == ret) return 0;
        if (1 == ret) // p is leaf
        {
            if (m_b_saletray) // for sale tray p->key < key
            {
                if (0 == successor(p, q))
                {
                    val = q->val;
                    return 0;
                }
                return 2;
            } // for sale tray
            else // for buy tray
            {
                if (p->key >= compare_key)
                {
                    val = p->val;
                    return 0;
                }
                return 2;
            } // for buy tray
        }
    }
    return 0;
}

// no parent no ltag rtag found first valid implement
// template <class TYPE> 
// uint64_t my_treap<TYPE>::search_in_valid_range_implement(treap_node<TYPE>*& p,TYPE const key, TYPE const compare_key, void*& val)
// {
//     uint64_t ret = 0;
//     if (nullptr == p)
//     {
//         return 1; // not found
//     }
//     else if (key == p->key)
//     {
//         return 0; // found 
//     }
//     else if (key < p->key)
//     {
//         if (!m_b_saletray && p->key <= compare_key) return 2; // buy tray search for m_high, but p->key is already smaller than m_low
// 
//         if (m_b_saletray && p->key <= compare_key) m_p_for_search = p; // sale tray search, record every node bigger than key
// 
//         ret = search_in_valid_range_implement(p->left, key, compare_key, val);
//         if (0 == ret) return 0;
//         if (1 == ret) // p is leaf
//         {
//             if (m_b_saletray) // for sale tray
//             {
//                 if (p->key <= compare_key) // p->key > key
//                 {
//                     val = p->val;
//                     return 0;
//                 }
//                 return 2;
//             } // for sale tray
//             else // for buy tray
//             {
//                 if (nullptr != m_p_for_search)
//                 {
//                     val = m_p_for_search->val;
//                     return 0;
//                 }
//                 return 2;
//             } // for buy tray
//         }
//     }
//     else
//     {
//         if (m_b_saletray && p->key >= compare_key) return 2; // sale tray search for m_low, but p->key is already bigger than m_hihg
// 
//         if (!m_b_saletray && p->key >= compare_key) m_p_for_search = p; // buy tray search, record every node smaller than key
// 
//         ret = search_in_valid_range_implement(p->right, key, compare_key, val);
//         if (0 == ret) return 0;
//         if (1 == ret) // p is leaf
//         {
//             if (m_b_saletray) // for sale tray p->key < key
//             {
//                 if (nullptr != m_p_for_search)
//                 {
//                     val = m_p_for_search->val;
//                     return 0;
//                 }
//                 return 2;
//             } // for sale tray
//             else // for buy tray
//             {
//                 if (p->key >= compare_key)
//                 {
//                     val = p->val;
//                     return 0;
//                 }
//                 return 2;
//             } // for buy tray
//         }
//     }
//     return 0;
// }

template <class TYPE> void my_treap<TYPE>::right_roate(treap_node<TYPE>*& p)
{
//     treap_node<TYPE>* q = p->left;
//     p->left = q->right;
//     q->right = p;
//     p = q;
    treap_node<TYPE>* q = p->left;
    int is_p_need_assign = 0;
    if (q->rtag)
    {
//          p->left = nullptr;
        is_p_need_assign = 1;
    }
    else
    {
        if (nullptr != q->right)
        {
            p->left = q->right;
            p->ltag = false;
        }
        else
        {
            p->left = nullptr;
            is_p_need_assign = 1;
        }
    }
    q->right = p;
    q->rtag = false;
    if (is_p_need_assign)
    {
        p->ltag = true;
        p->left = q;
    }
    p = q;
}

template <class TYPE> void my_treap<TYPE>::left_roate(treap_node<TYPE>*& p)
{
//     treap_node<TYPE>* q = p->right;
//     p->right = q->left;
//     q->left = p;
//     p = q;
    treap_node<TYPE>* q = p->right;
    int is_p_need_assign = 0; // 0表示p的右孩子非线索 1表示p的右孩子为线索
    if (q->ltag)  // q的左孩子为线索，p右孩子应该为指向p的后继，后继为q
    {
//          p->right = nullptr;
        is_p_need_assign = 1;
    }
    else// q的左孩子非线索
    {                           
        if (nullptr != q->left) // q的左孩子非空，p有右子树
        {
            p->right = q->left;
            p->rtag = false;
        }
        else // p右孩子，p右孩子应该为指向p的后继，后继为q
        {
            p->right = nullptr;
            is_p_need_assign = 1;
        } 
    }
    q->left = p;
    q->ltag = false;
    if (is_p_need_assign)
    {
        p->rtag = true;
        p->right = q;
    }
    p = q;
}

template <class TYPE> void my_treap<TYPE>::inorder(treap_node<TYPE>* p)
{
    if (nullptr != p)
    {
        if (nullptr != p->left && !p->ltag)
        {
            inorder(p->left);
        }
        if (p->key >= m_low && p->key <= m_high)
        {
            std::cout << p->key << "[" << p->priority << "]" << " ";
        }
        else
        {
            std::cout << p->key << "(" << p->priority << ")" << " ";
        }
        if (nullptr != p->right && !p->rtag)
        {
            inorder(p->right);
        }
    }
}

template <class TYPE> void my_treap<TYPE>::levelorder(treap_node<TYPE>* p)
{
    std::vector<treap_node<TYPE>* > vec;
    if (nullptr == p)
    {
        return;
    }
    vec.push_back(p);
    int cur = 0;
    int last = 1;
    char tmp[256];
    memset(tmp, 0, 256 * sizeof(char));
    std::string tmp_str_sum;
    int level = 0;
    while(static_cast<typename std::vector<treap_node<TYPE>* >::size_type>(cur) < vec.size())
    {
        last = static_cast<int>(vec.size());
        while(cur < last)
        {
            if (vec[cur]->key >= m_low && vec[cur]->key <= m_high)
            {
                 sprintf_s(tmp, "%d[%d] ", vec[cur]->key, vec[cur]->priority);
            }
            else
            {
                 sprintf_s(tmp, "%d(%d) ", vec[cur]->key, vec[cur]->priority);
            }
            tmp_str_sum += tmp;
            if (nullptr != vec[cur]->left && !vec[cur]->ltag)
            {
                vec.push_back(vec[cur]->left);
            }
            if (nullptr != vec[cur]->right && !vec[cur]->rtag)
            { 
                vec.push_back(vec[cur] ->right);
            }
            cur++;
        }
        std::cout << "level " << level++ << ":  " << tmp_str_sum << std::endl;
        tmp_str_sum.clear();
    }
}

template <class TYPE> void my_treap<TYPE>::levelorder_no_priority(treap_node<TYPE>* p)
{
    std::vector<treap_node<TYPE>* > vec;
    if (nullptr == p)
    {
        return;
    }
    vec.push_back(p);
    int cur = 0;
    int last = 1;
    char tmp[256];
    memset(tmp, 0, 256 * sizeof(char));
    std::string tmp_str_sum;
    int level = 0;
    while(static_cast<typename std::vector<treap_node<TYPE>* >::size_type>(cur) < vec.size())
    {
        last = static_cast<int>(vec.size());
        while(cur < last)
        {
            //             sprintf(tmp, "%c(%d) ", vec[cur]->key, vec[cur]->priority);
            if (vec[cur]->key >= m_low && vec[cur]->key <= m_high)
            {
                //                 sprintf_s(tmp, "%d[%d] ", vec[cur]->key, vec[cur]->priority);
                sprintf_s(tmp, "[%d] ", vec[cur]->key);
            }
            else
            {
                //                 sprintf_s(tmp, "%d(%d) ", vec[cur]->key, vec[cur]->priority);
                sprintf_s(tmp, "%d ", vec[cur]->key);
            }
            tmp_str_sum += tmp;
            if (nullptr != vec[cur]->left && !vec[cur]->ltag)
            {
                vec.push_back(vec[cur]->left);
            }
            if (nullptr != vec[cur]->right && !vec[cur]->rtag)
            { 
                vec.push_back(vec[cur] ->right);
            }
            cur++;
        }
        std::cout << "level " << level++ << ":  " << tmp_str_sum << std::endl;
        tmp_str_sum.clear();
    }
}

template <class TYPE> uint64_t my_treap<TYPE>::gen_priority(TYPE const key)
{
    uint64_t priority = rand() % 10000 + 10000; // bigger than 10000 less than 20000
    if (key >= m_low && key <= m_high) // in valid range smaller than 10000
    {
        priority = rand() % 10000;
    }
    return priority;
//     static int i = 0;
//     return i++;
}
#endif
#include "my_treap.h"

int main()
{
    void* val = nullptr;
    /*
    my_treap<uint64_t> c;
    uint64_t val_600 = 600;
    uint64_t val_610 = 610;
    uint64_t val_670 = 670;
    uint64_t val_680 = 680;
    uint64_t val_790 = 790;
    uint64_t val_800 = 800;
    c.insert(1000, val);
    c.insert(500, val);
    c.insert(2000, val);
    c.insert(200, val);
    c.insert(800, static_cast<void*>(&val_800));
    c.insert(1700, val);
    c.insert(300, val);
    c.insert(600, static_cast<void*>(&val_600));
    c.insert(900, val);
    c.insert(550, val);
    c.insert(650, val);
     c.insert(850, val);
    c.insert(910, val);
    c.insert(610, val);
    c.insert(680, static_cast<void*>(&val_680));
    c.insert(670, static_cast<void*>(&val_670));
    c.insert(790, static_cast<void*>(&val_790));
    c.print_levelorder();

    // for sale tray ut test
    // p is 790, p->key is bigger than key 700, p is a right child, p is first valid
    c.set_valid_range(700, 1000);
    c.print_levelorder();
    c.print_inorder();
    c.first(val);
    std::cout << "first valid sale tray (700, 1000) " << *static_cast<uint64_t*>(val) << std::endl;
    std::cout << std::endl;

    // p is 670, p->key is bigger than key 660, p is a left child, p is first valid
    c.set_valid_range(660, 1000);
    c.print_levelorder();
    c.print_inorder();
    c.first(val);
    std::cout << "first valid sale tray (660, 1000) " << *static_cast<uint64_t*>(val) << std::endl;
    std::cout << std::endl;
    
    // p is 790, p->key is smaller than key 791, p is a right child, successor of p is first valid
    c.set_valid_range(791, 1000);
    c.print_levelorder();
    c.print_inorder();
    c.first(val);
    std::cout << "first valid sale tray (791, 1000) " << *static_cast<uint64_t*>(val) << std::endl;
    std::cout << std::endl;
    
    // p is 670, p->key is smaller than key 671, p is a left child, successor of p is first valid
    c.set_valid_range(671, 1000);
    c.print_levelorder();
    c.print_inorder();
    c.first(val);
    std::cout << "first valid sale tray (671, 1000) " << *static_cast<uint64_t*>(val) << std::endl;
    std::cout << std::endl;
*/
//     c.del(900);
//     c.print_levelorder();
//     c.print_inorder();
//     std::cout << std::endl;

    /*
    my_treap<uint64_t> d(false);
    d.insert(1000, val);
    d.insert(500, val);
    d.insert(2000, val);
    d.insert(200, val);
    d.insert(800, static_cast<void*>(&val_800));
    d.insert(1700, val);
    d.insert(300, val);
    d.insert(600, static_cast<void*>(&val_600));
    d.insert(900, val);
    d.insert(550, val);
    d.insert(650, val);
    d.insert(850, val);
    d.insert(910, val);
    d.insert(610, static_cast<void*>(&val_610));
    d.insert(680, static_cast<void*>(&val_680));
    d.insert(670, static_cast<void*>(&val_670));
    d.insert(790, static_cast<void*>(&val_790));
    d.print_levelorder();

    // for buy tray ut test
    // p is 610, p->key is bigger than key 605, p is a right child, predecessor of p is first valid
    d.set_valid_range(100, 605);
    d.print_levelorder();
    d.print_inorder();
    d.first(val);
    std::cout << "first valid buy tray (100, 605) " << *static_cast<uint64_t*>(val) << std::endl;
    std::cout << std::endl;

    // p is 790, p->key is bigger than key 780, p is a right child, predecessor of p is first valid
    d.set_valid_range(100, 780);
    d.print_levelorder();
    d.print_inorder();
    d.first(val);
    std::cout << "first valid buy tray (100, 780) " << *static_cast<uint64_t*>(val) << std::endl;
    std::cout << std::endl;

    // p is 610, p->key is smaller than key 611, p is a left child, p is first valid
    d.set_valid_range(100, 611);
    d.print_levelorder();
    d.print_inorder();
    d.first(val);
    std::cout << "first valid buy tray (100, 611) " << *static_cast<uint64_t*>(val) << std::endl;
    std::cout << std::endl;

    // p is 790, p->key is smaller than key 791, p is a right child, p is first valid
    d.set_valid_range(100, 791);
    d.print_levelorder();
    d.print_inorder();
    d.first(val);
    std::cout << "first valid buy tray (100, 791) " << *static_cast<uint64_t*>(val) << std::endl;
    std::cout << std::endl;

    getchar();
    /*
    my_treap<char> a;
    a.insert('G', val);
    a.insert('B', val);
    a.insert('H', val);
    a.insert('A', val);
    a.insert('E', val);
    a.insert('K', val);
    a.insert('H', val);
    a.insert('I', val);
    a.insert('C', val);
    a.insert('D', val);
    a.insert('F', val);
    a.print_inorder();
    a.print_levelorder();
    a.del('H');
    a.print_inorder();
    a.print_levelorder();
    getchar();

    
    my_treap<char> b;
    b.set_valid_range('H', 'P');
    int i = 0;
    char rand_key;
    while (i++ < 26 * 10)
    {
        rand_key = rand() % 26 + 'A';
        b.insert(rand_key, val);
    }
    b.print_inorder();
    b.print_levelorder();
    getchar();
    return 0;
    */
    
    int iii = 0;
    int jjj = 0;
    int rand_low;
    int randb_high;
    my_treap<uint64_t>* rand_bst;
    int for_swap;
    int tmp_node;
    int rand_index = 5000;

    while (jjj++ < 1000) // 多少棵树
    {
        std::cout << "jjj = " << jjj << std::endl;
        rand_low   = abs(rand() % rand_index);
        randb_high = abs(rand() % rand_index);

        if (rand_low > randb_high)
        {
            for_swap = rand_low;
            rand_low = randb_high;
            randb_high = for_swap;
        }
        iii = 0;
        rand_bst = new my_treap<uint64_t>;
        rand_bst->set_valid_range(rand_low, rand_low * 140 / 100);
        std::cout << "inserting ";
        while (iii++ < rand_index * 2) // 每棵树有多少结点
        {
            while (0 == (tmp_node = abs(rand() % rand_index)));
            std::cout << tmp_node << " ";
            // std::cout << "inserting " << tmp_node << std::endl;
            rand_bst->insert(tmp_node, val); // 每个结点的取值范围(0～n)
        }
        std::cout << std::endl;
        rand_bst->print_inorder();
//         rand_bst->print_levelorder();
        rand_bst->print_levelorder_no_priority();

        iii = 0;
        std::cout << "deleting ";
        while(iii++ < rand_index * 2)
        {
            while (0 == (tmp_node = abs(rand() % rand_index)));
            std::cout << tmp_node << " ";
             rand_bst->del(tmp_node); 
        }
        std::cout << std::endl;
        rand_bst->print_levelorder_no_priority();
        std::cout << "jjj = " << jjj << " end!" << std::endl;
    }
    getchar();
    
    return 0;
}

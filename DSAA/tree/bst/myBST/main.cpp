#include <iostream>
#include <stdlib.h>
#include "myBST.h"

// 需要考虑，如果被删除节点存在后继，且后续存在前驱，则应修改后继的前驱；如果存在前驱，则找到前驱节点，如果有需要，修改它的后继
// http://blog.csdn.net/goodluckwhh/article/details/11786079

int main()
{
    bool flag = true;
    void* val = nullptr;
    
    void* first;
    void* end;
    void* next;
    void* pre;

    int low;
    int high;

    int iii = 0;
    int jjj = 0;
    int rand_low;
    int randb_high;
    myBST* rand_bst;
    flag = true;
    int for_swap;
    int tmp_node;
    int rand_index = 30;
   
    while (jjj++ < 40000) // 多少棵树
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
        flag = (0 == rand_low % 2) ? true : false; 
        rand_bst = new myBST(flag);
//         rand_bst->set_valid_range(rand_low, randb_high);
        rand_bst->set_valid_range(rand_low, rand_low * 140 / 100);
        rand_bst->print_info();
        while (iii++ < rand_index) // 每棵树有多少结点
        {
            while (0 == (tmp_node = abs(rand() % rand_index)));
             std::cout << "inserting " << tmp_node << " ";
//            std::cout << "inserting " << tmp_node << std::endl;
            rand_bst->insert_node(tmp_node, val); // 每个结点的取值范围(0～n)
        }
        std::cout << std::endl;
//          rand_bst->set_valid_range(rand_low, randb_high);
        rand_bst->print_info();
//         iii = 0;
//         while (iii++ < rand_index)
//         {
//             while (0 == (tmp_node = abs(rand() % rand_index)));
//             std::cout << "deleting " << tmp_node << " ";
//              rand_bst->delete_node(tmp_node, val);
//         }  
//         std::cout << std::endl;
//         std::cout << "after delete: " << std::endl;
//         rand_bst->print_info();
// 
//         iii = 0;
//         while (iii++ < rand_index) // 每棵树有多少结点
//         {
//             while (0 == (tmp_node = abs(rand() % rand_index)));
//             std::cout << "inserting " << tmp_node << " ";
//             rand_bst->insert_node(tmp_node, val); // 每个结点的取值范围(0～n)
//         }
//         std::cout << std::endl;
//          rand_bst->print_info();
//         iii = 0;
//         while (iii++ < rand_index)
//         {
//             while (0 == (tmp_node = abs(rand() % rand_index)));
//             std::cout << "deleting " << tmp_node << " " ;
//              rand_bst->delete_node(tmp_node, val);
//         }  
//         std::cout << std::endl;
//         std::cout << "after delete: " << std::endl;
//          rand_bst->print_info();
         std::cout << "jjj = " << jjj << " end!" << std::endl;
    }
    getchar();
     return 0;
   

    myBST bug5;
    bug5.set_valid_range(18, 25);
    bug5.insert_node(25, val);
    bug5.insert_node(5, val);
    bug5.insert_node(3, val);
    bug5.insert_node(12, val);
    bug5.insert_node(9, val);
    bug5.insert_node(26, val);
    bug5.insert_node(20, val);
    bug5.insert_node(19, val);
    bug5.insert_node(17, val);
    bug5.insert_node(13, val);
    bug5.insert_node(10, val);
    bug5.insert_node(14, val);
    bug5.insert_node(6, val);
    bug5.insert_node(27, val);
    bug5.insert_node(28, val);
    bug5.insert_node(22, val);
    bug5.insert_node(15, val);
    bug5.insert_node(21, val);
    bug5.insert_node(11, val);
    bug5.print_info();

//     myBST bug5;
//     bug5.set_valid_range(9, 11);
//     bug5.insert_node(8, val);
//     bug5.insert_node(2, val);
//     bug5.insert_node(4, val);
//     bug5.insert_node(11, val);
//     bug5.insert_node(12, val);
//     bug5.insert_node(9, val);
//     bug5.insert_node(10, val);
//     bug5.insert_node(6, val);
//     bug5.insert_node(5, val);
//     bug5.print_info();
//     bug5.insert_node(22, val);
//     bug5.print_info();

//     bug5.delete_node(15, val);
//     bug5.print_info();
    getchar();
    return 0;
//     myBST bug5;
//     bug5.insert_node(20, val);
//     bug5.insert_node(10, val);
//     bug5.insert_node(30, val);
//     bug5.insert_node(15, val);
//     bug5.insert_node(25, val);
//     bug5.insert_node(40, val);
//     bug5.insert_node(23, val);
//     bug5.insert_node(46, val);
// 
//     bug5.delete_node(15, val);
//     bug5.print_inorder();
//     bug5.print_inorder_no_bf();

    myBST bug4;
    bug4.insert_node(14, val);
    bug4.insert_node(9, val);
    bug4.insert_node(15, val);
    bug4.insert_node(12, val);
    bug4.insert_node(11, val);
    bug4.insert_node(8, val);
    bug4.insert_node(4, val);
    bug4.insert_node(19, val);
    bug4.insert_node(3, val);
    bug4.insert_node(1, val);
    bug4.insert_node(7, val);
    bug4.insert_node(10, val);
    bug4.insert_node(6, val);


    bug4.delete_node(1, val);
    bug4.delete_node(2, val);
    bug4.delete_node(15, val);
    bug4.delete_node(10, val);
    bug4.delete_node(12, val);
    bug4.delete_node(9, val);
    bug4.delete_node(8, val);
    bug4.delete_node(14, val);
    bug4.delete_node(7, val);
    bug4.delete_node(3, val);
    bug4.delete_node(4, val);
    bug4.delete_node(6, val);
    bug4.delete_node(11, val);

    myBST bug3;
    bug3.insert_node(8, val);
    bug3.insert_node(1, val);
    bug3.insert_node(9, val);

    bug3.delete_node(8, val);
    bug3.delete_node(1, val);
    bug3.delete_node(9, val);


    myBST bug2;
    bug2.insert_node(8, val);
    bug2.insert_node(1, val);
    bug2.insert_node(14, val);
    bug2.insert_node(5, val);
    bug2.insert_node(9, val);
    bug2.insert_node(2, val);
    bug2.insert_node(13, val);
    bug2.insert_node(12, val);

    bug2.delete_node(14, val);
    bug2.delete_node(5, val);
    bug2.delete_node(10, val);
    bug2.delete_node(10, val);
    bug2.delete_node(9, val);
    bug2.delete_node(3, val);
    bug2.delete_node(2, val);
    bug2.delete_node(13, val);
    bug2.delete_node(12, val);
    bug2.delete_node(11, val);
    bug2.delete_node(8, val);
    bug2.delete_node(6, val);
    bug2.delete_node(2, val);
    bug2.delete_node(1, val);
    bug2.delete_node(14, val);

    //     bug2.print_levelorder();
    bug2.print_inorder();
    bug2.print_inorder_no_bf();


    //     getchar();

    myBST bug1;
    bug1.insert_node(12, val);
    bug1.insert_node(1, val);
    bug1.insert_node(16, val);
    bug1.insert_node(10, val);
    bug1.insert_node(2, val);
    bug1.insert_node(19, val);
    bug1.insert_node(17, val);
    bug1.insert_node(14, val);
    bug1.insert_node(13, val);
    bug1.insert_node(15, val);
    bug1.insert_node(6, val);
    bug1.insert_node(11, val);
    bug1.insert_node(4, val);
    bug1.insert_node(3, val);

    bug1.delete_node(17, val);
    bug1.delete_node(19, val);
    bug1.delete_node(8, val);
    bug1.delete_node(11, val);
    bug1.delete_node(7, val);
    bug1.delete_node(16, val);
    bug1.delete_node(10, val);
    bug1.delete_node(1, val);
    bug1.delete_node(10, val);
    bug1.delete_node(12, val);
    bug1.delete_node(5, val);
    bug1.delete_node(11, val);
    bug1.delete_node(9, val);
    bug1.delete_node(17, val);
    bug1.delete_node(11, val);
    bug1.delete_node(1, val);
    bug1.delete_node(3, val);
    bug1.delete_node(11, val);
    bug1.delete_node(12, val);
    bug1.delete_node(6, val);
    bug1.delete_node(18, val);

    //     bug1.print_levelorder();
    bug1.print_inorder();
    bug1.print_inorder_no_bf();

    //     getchar();
    //     myBST pre_bst;
    //     pre_bst.insert_node(5, val);
    //     pre_bst.insert_node(3, val);
    //     pre_bst.insert_node(8, val);
    //     pre_bst.insert_node(1, val);
    //     pre_bst.insert_node(4, val);
    //     pre_bst.insert_node(6, val);
    //     pre_bst.insert_node(9, val);
    // 
    //     pre_bst.print_levelorder();
    //     getchar();


    myBST sale_tray_withvalid;
    myBST buy_tray_withvalid(false);
    int price100 = 100;
    int price90  = 90;
    int price110 = 110;
    int price70  = 70;
    int price95  = 95;
    int price105 = 105;
    int price115 = 115;
    int price60  = 60;
    int price75  = 75;
    int price93  = 93;
    int price97  = 97;
    int price104 = 104;
    int price112 = 112;
    int price130 = 130;
    int price78  = 78;
    int price121 = 121;
    int price135 = 135;

    sale_tray_withvalid.insert_node(100, static_cast<void*>(&price100));
    sale_tray_withvalid.insert_node(90, static_cast<void*>(&price90));
    sale_tray_withvalid.insert_node(110, static_cast<void*>(&price110));
    sale_tray_withvalid.insert_node(70, static_cast<void*>(&price70));
    sale_tray_withvalid.insert_node(95, static_cast<void*>(&price95));
    sale_tray_withvalid.insert_node(105, static_cast<void*>(&price105));
    sale_tray_withvalid.insert_node(115, static_cast<void*>(&price115));
    sale_tray_withvalid.insert_node(60, static_cast<void*>(&price60));
    sale_tray_withvalid.insert_node(75, static_cast<void*>(&price75));
    sale_tray_withvalid.insert_node(93, static_cast<void*>(&price93));
    sale_tray_withvalid.insert_node(97, static_cast<void*>(&price97));
    sale_tray_withvalid.insert_node(104, static_cast<void*>(&price104));
    sale_tray_withvalid.insert_node(112, static_cast<void*>(&price112));
    sale_tray_withvalid.insert_node(130, static_cast<void*>(&price130));
    sale_tray_withvalid.insert_node(78, static_cast<void*>(&price78));
    sale_tray_withvalid.insert_node(121, static_cast<void*>(&price121));
    sale_tray_withvalid.insert_node(135, static_cast<void*>(&price135));

    buy_tray_withvalid.insert_node(100, static_cast<void*>(&price100));
    buy_tray_withvalid.insert_node(90, static_cast<void*>(&price90));
    buy_tray_withvalid.insert_node(110, static_cast<void*>(&price110));
    buy_tray_withvalid.insert_node(70, static_cast<void*>(&price70));
    buy_tray_withvalid.insert_node(95, static_cast<void*>(&price95));
    buy_tray_withvalid.insert_node(105, static_cast<void*>(&price105));
    buy_tray_withvalid.insert_node(115, static_cast<void*>(&price115));
    buy_tray_withvalid.insert_node(60, static_cast<void*>(&price60));
    buy_tray_withvalid.insert_node(75, static_cast<void*>(&price75));
    buy_tray_withvalid.insert_node(93, static_cast<void*>(&price93));
    buy_tray_withvalid.insert_node(97, static_cast<void*>(&price97));
    buy_tray_withvalid.insert_node(104, static_cast<void*>(&price104));
    buy_tray_withvalid.insert_node(112, static_cast<void*>(&price112));
    buy_tray_withvalid.insert_node(130, static_cast<void*>(&price130));
    buy_tray_withvalid.insert_node(78, static_cast<void*>(&price78));
    buy_tray_withvalid.insert_node(121, static_cast<void*>(&price121));
    buy_tray_withvalid.insert_node(135, static_cast<void*>(&price135));
    
    low  = 80;
    high = 120;
//     sale_tray_withvalid.set_valid_range(low, high);
//     sale_tray_withvalid.set_valid_range(0, maxint);
    sale_tray_withvalid.print_info();
    getchar();



    sale_tray_withvalid.set_valid_range(low, high);
    sale_tray_withvalid.print_inorder_no_bf();
    sale_tray_withvalid.print_inorder_valid_range();
    sale_tray_withvalid.first_valid(val);
    std::cout << "best sale: " << *static_cast<int*>(val) << std::endl;

    buy_tray_withvalid.set_valid_range(low, high);
    buy_tray_withvalid.first_valid(val);
    std::cout << "best buy:  " << *static_cast<int*>(val) << std::endl;

    std::cout << "sale tray next valid: " ;
    while (!sale_tray_withvalid.next_valid(val))
    {
        std::cout << *static_cast<int*>(val) << " ";
    }
    std::cout << std::endl ;

    std::cout << "buy tray next valid : " ;
    while (!buy_tray_withvalid.next_valid(val))
    {
        std::cout << *static_cast<int*>(val) << " ";
    }
    std::cout << std::endl ;
    std::cout << std::endl ;


    getchar();

    std::cout << "valid range [" << low << ", " << high << "]" << std::endl;
    sale_tray_withvalid.print_inorder_no_bf();
    sale_tray_withvalid.search_in_validrange(low, high, val);
    std::cout << "best sale: " << *static_cast<int*>(val) << std::endl;
    buy_tray_withvalid.search_in_validrange(high, low, val);
    std::cout << "best buy:  " << *static_cast<int*>(val) << std::endl;

    std::cout << "sale tray next      : " ;
    while (!sale_tray_withvalid.next(val))
    {
        std::cout << *static_cast<int*>(val) << " ";
    }
    std::cout << std::endl ;

    sale_tray_withvalid.search_in_validrange(low, high, val);
    std::cout << "sale tray next valid: " ;
    while (!sale_tray_withvalid.next_valid(val, high))
    {
        std::cout << *static_cast<int*>(val) << " ";
    }
    std::cout << std::endl ;

    std::cout << "buy tray next       : " ;
    while (!buy_tray_withvalid.next(val))
    {
        std::cout << *static_cast<int*>(val) << " ";
    }
    std::cout << std::endl ;

    buy_tray_withvalid.search_in_validrange(high, low, val);
    std::cout << "buy tray next valid : " ;
    while (!buy_tray_withvalid.next_valid(val, low))
    {
        std::cout << *static_cast<int*>(val) << " ";
    }
    std::cout << std::endl ;
    std::cout << std::endl ;




    low  = 40;
    high = 140;
    std::cout << "valid range [" << low << ", " << high << "]" << std::endl;
    sale_tray_withvalid.print_inorder_no_bf();
    sale_tray_withvalid.search_in_validrange(low, high, val);
    std::cout << "best sale: " << *static_cast<int*>(val) << std::endl;
    buy_tray_withvalid.search_in_validrange(high, low, val);
    std::cout << "best buy:  " << *static_cast<int*>(val) << std::endl;
    std::cout << std::endl;

    low  = 61;
    high = 101;
    std::cout << "valid range [" << low << ", " << high << "]" << std::endl;
    sale_tray_withvalid.print_inorder_no_bf();
    sale_tray_withvalid.search_in_validrange(low, high, val);
    std::cout << "best sale: " << *static_cast<int*>(val) << std::endl;
    buy_tray_withvalid.search_in_validrange(high, low, val);
    std::cout << "best buy:  " << *static_cast<int*>(val) << std::endl;
    std::cout << std::endl;
    getchar();

    
    std::cout << "valid range [" << low << ", " << high << "]" << std::endl;
    sale_tray_withvalid.print_inorder_no_bf();
    sale_tray_withvalid.first(first);
    std::cout << "sale tray first=: " << *static_cast<int*>(first) << std::endl;
    std::cout << "next=: ";
    while (!sale_tray_withvalid.next(next))
    {
        std::cout << *static_cast<int*>(next) << " ";
    }
    std::cout << std::endl;

    sale_tray_withvalid.end(end);
    std::cout << "sale tray end=: " << *static_cast<int*>(end) << std::endl;

    std::cout << "pre=: ";
    while (!sale_tray_withvalid.pre(pre))
    {
        std::cout << *static_cast<int*>(pre) << " ";
    }
    std::cout << std::endl;

    buy_tray_withvalid.first(first);
    std::cout << "buy tray first=: " << *static_cast<int*>(first) << std::endl;
    std::cout << "next=: ";
    while (!buy_tray_withvalid.next(next))
    {
        std::cout << *static_cast<int*>(next) << " ";
    }
    std::cout << std::endl;

    buy_tray_withvalid.end(end);
    std::cout << "buy tray end=: " << *static_cast<int*>(end) << std::endl;

    std::cout << "pre=: ";
    while (!buy_tray_withvalid.pre(pre))
    {
        std::cout << *static_cast<int*>(pre) << " ";
    }
    std::cout << std::endl;
    getchar();

    myBST a;
    a.insert_node(100, val);

    a.insert_node(50, val);
    a.insert_node(150, val);

    a.insert_node(25, val);
    a.insert_node(75, val);
    a.insert_node(125, val);
    a.insert_node(175, val);

    a.insert_node(12, val);
    a.insert_node(37, val);
    a.insert_node(63, val);
    a.insert_node(87, val);
    a.insert_node(112, val);
    a.insert_node(137, val);
    a.insert_node(163, val);
    a.insert_node(187, val);

    a.insert_node(6, val);
    a.insert_node(18, val);
    a.insert_node(31, val);
    a.insert_node(43, val);
    a.insert_node(57, val);
    a.insert_node(69, val);
    a.insert_node(81, val);
    a.insert_node(93, val);
    a.insert_node(106, val);
    a.insert_node(118, val);
    a.insert_node(131, val);
    a.insert_node(143, val);
    a.insert_node(157, val);
    a.insert_node(169, val);
    a.insert_node(181, val);
    a.insert_node(193, val);

    a.insert_node(3, val);
    a.insert_node(9, val);
    a.insert_node(15, val);
    a.insert_node(21, val);
    a.insert_node(28, val);
    a.insert_node(34, val);
    a.insert_node(40, val);
    a.insert_node(46, val);
    a.insert_node(54, val);
    a.insert_node(60, val);
    a.insert_node(66, val);
    a.insert_node(72, val);
    a.insert_node(78, val);
    a.insert_node(84, val);
    a.insert_node(90, val);
    a.insert_node(96, val);
    a.insert_node(103, val);
    a.insert_node(109, val);
    a.insert_node(115, val);
    a.insert_node(121, val);
    a.insert_node(128, val);
    a.insert_node(134, val);
    a.insert_node(140, val);
    a.insert_node(146, val);
    a.insert_node(154, val);
    a.insert_node(160, val);
    a.insert_node(166, val);
    a.insert_node(172, val);
    a.insert_node(178, val);
    a.insert_node(184, val);
    a.insert_node(190, val);
    a.insert_node(196, val);

    a.insert_node(44, val);
    a.insert_node(48, val);

    a.print_inorder();
    a.print_by_next();
    a.print_by_pre();

    a.delete_node(50, val);
    std::cout << "after delete 50" << std::endl;
    a.print_inorder();
    std::cout << std::endl;

    a.delete_node(44, val);
    std::cout << "after delete 44" << std::endl;
    a.print_inorder();
    std::cout << std::endl;

    a.delete_node(3, val);
    std::cout << "after delete 3" << std::endl;
    a.print_inorder();
    std::cout << std::endl;
   
    a.delete_node(9, val);
    std::cout << "after delete 9" << std::endl;
    a.print_inorder();
    std::cout << std::endl;

    a.delete_node(6, val);
    std::cout << "after delete 6" << std::endl;
    a.print_inorder();
    std::cout << std::endl;

    myBST kk; // 删除叶子，叶子为右孩子
    kk.insert_node(10, val);
    kk.insert_node(5, val);
    kk.insert_node(15, val);
    kk.insert_node(3, val);
    kk.insert_node(6, val);
    kk.insert_node(12, val);
    kk.insert_node(18, val);
    kk.insert_node(13, val);

    kk.delete_node(13, val);
    kk.print_inorder();

    myBST ll; // 删除叶子，叶子为左孩子
    ll.insert_node(10, val);
    ll.insert_node(5, val);
    ll.insert_node(15, val);
    ll.insert_node(3, val);
    ll.insert_node(8, val);
    ll.insert_node(14, val);
    ll.insert_node(16, val);
    ll.insert_node(7, val);

    ll.delete_node(7, val);
    ll.print_inorder();

    myBST mm; // 删除单孩子节点，该节点叶子为右孩子
    mm.insert_node(10, val);
    mm.insert_node(5, val);
    mm.insert_node(15, val);
    mm.insert_node(3, val);
    mm.insert_node(6, val);
    mm.insert_node(12, val);
    mm.insert_node(18, val);
    mm.insert_node(13, val);

    mm.delete_node(12, val);
    mm.print_inorder();

    myBST nn; // 删除单孩子节点，该节点叶子为左孩子
    nn.insert_node(10, val);
    nn.insert_node(5, val);
    nn.insert_node(15, val);
    nn.insert_node(3, val);
    nn.insert_node(6, val);
    nn.insert_node(12, val);
    nn.insert_node(18, val);
    nn.insert_node(11, val);

    nn.delete_node(12, val);
    nn.print_inorder();

    myBST oo;
    oo.insert_node(10, val);
    oo.insert_node(5, val);
    oo.insert_node(15, val);
    oo.insert_node(3, val);
    oo.insert_node(8, val);
    oo.insert_node(14, val);
    oo.insert_node(16, val);
    oo.insert_node(7, val);

    oo.delete_node(8, val);
    oo.print_inorder();

    myBST pp;
    pp.insert_node(10, val);
    pp.insert_node(5, val);
    pp.insert_node(15, val);
    pp.insert_node(3, val);
    pp.insert_node(8, val);
    pp.insert_node(14, val);
    pp.insert_node(16, val);
    pp.insert_node(9, val);

    pp.delete_node(8, val);
    pp.print_inorder();

     // A的右子树的平衡因子为-1
    myBST b;
    b.insert_node(20, val);
    b.insert_node(10, val);
    b.insert_node(30, val);
    b.insert_node(15, val);
    b.insert_node(25, val);
    b.insert_node(40, val);
    b.insert_node(35, val);
    b.insert_node(46, val);

    b.print_inorder();
    b.delete_node(15, val);
    std::cout << "after delete 15" << std::endl;
    b.print_inorder();
    std::cout << std::endl;

    // A的右子树的平衡因子为0
    myBST c;
    c.insert_node(20, val);
    c.insert_node(10, val);
    c.insert_node(30, val);
    c.insert_node(15, val);
    c.insert_node(25, val);
    c.insert_node(40, val);
    c.insert_node(23, val);
    c.insert_node(46, val);

    c.print_inorder();
    c.delete_node(15, val);
    std::cout << "after delete 15" << std::endl;
    c.print_inorder();
    std::cout << std::endl;

    // A的右子树的平衡因子为1
    myBST d;
    d.insert_node(20, val);
    d.insert_node(10, val);
    d.insert_node(30, val);
    d.insert_node(8, val);
    d.insert_node(25, val);
    d.insert_node(40, val);
    d.insert_node(23, val);
    d.insert_node(28, val);

    d.print_inorder();
    d.delete_node(8, val);
    std::cout << "after delete 8" << std::endl;
    d.print_inorder();
    std::cout << std::endl;
 
    // A的右子树的平衡因子为-1，A不是根节点
    myBST e;
    e.insert_node(50, val);
    e.insert_node(20, val);
    e.insert_node(90, val);
    e.insert_node(10, val);
    e.insert_node(30, val);
    e.insert_node(80, val);
    e.insert_node(100, val);
    e.insert_node(15, val);
    e.insert_node(25, val);
    e.insert_node(40, val);
    e.insert_node(85, val);
    e.insert_node(95, val);
    e.insert_node(150, val);
    e.insert_node(35, val);
    e.insert_node(46, val);
    e.insert_node(140, val);

    e.print_inorder();
    e.delete_node(15, val);
    std::cout << "after delete 15" << std::endl;
    e.print_inorder();
    std::cout << std::endl;
    
    // A的左子树的平衡因子为-1
    myBST f;
    f.insert_node(20, val);
    f.insert_node(10, val);
    f.insert_node(30, val);
    f.insert_node(5, val);
    f.insert_node(15, val);
    f.insert_node(25, val);
    f.insert_node(11, val);
    f.insert_node(17, val);

    f.print_inorder();
    f.delete_node(25, val); // 左平衡，先左旋A的左子树，后右旋A
    std::cout << "after delete 25" << std::endl;
    f.print_inorder();
    std::cout << std::endl;

    // A的左子树的平衡因子为0
    myBST g;
    g.insert_node(20, val);
    g.insert_node(10, val);
    g.insert_node(30, val);
    g.insert_node(5, val);
    g.insert_node(15, val);
    g.insert_node(25, val);
    g.insert_node(4, val);
    g.insert_node(17, val);

    g.print_inorder();
    g.delete_node(25, val); // 左平衡，右旋A一次
    std::cout << "after delete 25" << std::endl;
    g.print_inorder();
    std::cout << std::endl;

    // A的左子树的平衡因子为1
    myBST h;
    h.insert_node(20, val);
    h.insert_node(10, val);
    h.insert_node(30, val);
    h.insert_node(5, val);
    h.insert_node(15, val);
    h.insert_node(25, val);
    h.insert_node(4, val);

    h.print_inorder();
    h.delete_node(25, val); // 左平衡，右旋A一次
    std::cout << "after delete 25" << std::endl;
    h.print_inorder();
    std::cout << std::endl;
    

    myBST i; // 增加导致左平衡，右旋一次
    i.insert_node(10, val);
    i.insert_node(6, val);
    i.insert_node(12, val);
    i.insert_node(4, val);
    i.insert_node(7, val);
    i.insert_node(3, val);

    i.print_inorder();
    std::cout << std::endl;

    myBST j; // 增加导致右平衡，左旋一次
    j.insert_node(6, val);
    j.insert_node(4, val);
    j.insert_node(10, val);
    j.insert_node(7, val);
    j.insert_node(12, val);
    j.insert_node(15, val);

    j.print_inorder();
    std::cout << std::endl;

    myBST k; // 先左后右，两旋
    k.insert_node(10, val);
    k.insert_node(6, val);
    k.insert_node(12, val);
    k.insert_node(4, val);
    k.insert_node(7, val);
    k.insert_node(8, val);

    k.print_inorder();
    std::cout << std::endl;

    myBST l; 
    l.insert_node(10, val);
    l.insert_node(6, val);
    l.insert_node(12, val);
    l.insert_node(4, val);
    l.insert_node(8, val);
    l.insert_node(7, val);

    l.print_inorder();
    std::cout << std::endl;

    myBST m; // 先右后左，两旋
    m.insert_node(7, val);
    m.insert_node(6, val);
    m.insert_node(10, val);
    m.insert_node(8, val);
    m.insert_node(12, val);
    m.insert_node(9, val);

    m.print_inorder();
    std::cout << std::endl;

    myBST n; // 先右后左，两旋
    n.insert_node(7, val);
    n.insert_node(6, val);
    n.insert_node(10, val);
    n.insert_node(8, val);
    n.insert_node(12, val);
    n.insert_node(9, val);

    n.print_inorder();
    std::cout << std::endl;
    getchar();

    myBST test2(false);
    test2.insert_node(6100, val);
    test2.set_valid_range(4000, 6000);
    test2.first_valid(val);

    myBST test3(true);
    test3.insert_node(6100, val);
    test3.set_valid_range(7000, 8000);
    test3.first_valid(val); 

    getchar();



    return 0;
}

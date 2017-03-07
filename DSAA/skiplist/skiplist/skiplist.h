///跳表数据结构类定义
/***********************************************************************
系统名称: xxxx
模块名称:
文 件 名: skiplist.h
功能说明:
作    者: helf
开发日期: 2013-7-10   10:45:52
修改记录:
***********************************************************************/
#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <stdint.h>
#include <new>
#include <iostream>

#ifdef __linux
#include <config_env.h>
#include <config_posix.h>
#endif

#define FBASE_NEW new(std::nothrow)

// #define MAX_LEVEL       32        /* Should be enough for 2^32 elements */
#define MAX_LEVEL       32

#define SKIPLIST_P      0.25

const uint32_t uint_max = 0xffffffffui32; 

class skiplistnode
{
public:
    int32_t key;
    void* val;
    skiplistnode** forward;
    int32_t level;
};

class skiplist
{
public:
    ///构造函数
    /**
     *@param bool type = true  排序方式，true为升序，false为降序，默认为升序
     */
    skiplist(bool type = true);

    ///析构函数
    /**
     */
    ~skiplist();

    ///1.添加数据
    /**
     *@param const int32_t key  关键字key
     *@param const void* val    如果不使用，val设为NULL
     *@return int32_t           添加成功返回0，失败返回-1
     */
    virtual int32_t add(const int32_t key, const void* val);

    ///2.删除数据
    /**
     *@param const int32_t key  删除关键字
     *@param void*& val = NULL  返回外部维护的内存块
     *@return int32_t           删除成功返回0，失败返回-1
     */
    virtual int32_t del(const int32_t key, void*& val);

    ///3.查找数据
    /**
     *@param const int32_t key  查找关键字
     *@param void*& val         val用于向外部返回，用完不能释放val，如果不使用VAL，val设为NULL
     *@return int32_t           存在返回0，不存在返回-1
     */
    int32_t get(const int32_t key, void*& val);

    ///4.返回跳表数据量
    /**
     *@param 
     *@return int32_t           返回跳表中的数据量，空返回0
     */
    int32_t size() const;

    ///5.遍历跳表操作，线程不安全
    ///5.1开始遍历：返回跳表首节点数据
    /**
     *@param int32_t& key       key用于向外部返回
     *@param void*& val         val用于向外部返回
     *@return int32_t           成功返回0，跳表空或者出错返回-1
     */
    int32_t first(int32_t& key, void*& val);

    ///5.2循环遍历：返回跳表下个节点数据
    /**
     *@param int32_t& key       key用于向外部返回
     *@param void*& val         val用于向外部返回
     *@return int32_t           成功返回0，结束或者出错返回-1
     */
    int32_t next(int32_t& key, void*& val);

    ///5.3重置遍历位置：根据key值重置当前遍历指针
    /**
     *@param const int32_t key  key用于向外部返回
     *@return int32_t           成功返回0，出错返回-1
     */
    int32_t locate(const int32_t key);

    ///5.4遍历是否结束
    /**
     *@return bool              结束返回true，未结束返回false
     */
    bool isEof();
    void print_by_level()
    {
        skiplistnode* p;
        skiplistnode* q;
        for (int i = 0; i < m_level; i++)
        {
            p = m_header;
            std::cout << "level: " << m_level - i - 1 << std::endl;
            while ((p->level >= m_level - i - 1) && (q = p->forward[m_level - i - 1]))
            {
                std::cout << q->key << " ";
                p = q;
            }
            std::cout << std::endl;
        }
    }
protected:
    skiplistnode* createNode(const int32_t key, const void* val, int32_t level);
    int32_t randomLevel();

protected:
    bool m_type;
    int32_t m_size;
    int32_t m_level;
    skiplistnode* m_header;
    skiplistnode* m_curr;
};

class skiplist_bid : public skiplist {
public:
    skiplist_bid(bool type = true): skiplist(type), m_low(0), m_high(uint_max), m_first_valid(NULL) { }
     ///1.添加数据
    /**
     *@param const int32_t key  关键字key
     *@param const void* val    如果不使用，val设为NULL
     *@return int32_t           添加成功返回0，失败返回-1
     */
    int32_t add(const int32_t key, const void* val);

    ///2.删除数据
    /**
     *@param const int32_t key  删除关键字
     *@param void*& val = NULL  返回外部维护的内存块
     *@return int32_t           删除成功返回0，失败返回-1
     */
    int32_t del(const int32_t key, void*& val);
	/**
    *@param const int32_t key  查找最优
    *@param const int32_t compare_key  最优价需在价格区间中
     *@param void*& val         val用于向外部返回，用完不能释放val，如果不使用VAL，val设为NULL
     *@return int32_t           存在返回0，不存在返回-1
     */
    int32_t first_valid(void*& val);    
    /**
     *@param int32_t& key       key用于向外部返回
     *@param const int32_t compare_key是有效价格区间使用的比较值
     *@param void*& val         val用于向外部返回
     *@return int32_t           成功返回0，结束或者出错返回-1
     */
    int32_t next_valid(void*& val);
    
    //
    //int32_t get_add(const int32_t key, const void* val) { return 0; }
    // 有成交导致有效价格区间变化
    void set_valid_range(int32_t low, int32_t high);

    void print_valid_range()
    {
        std::cout << "valid range: [" << m_low << ", " << m_high << "]" << std::endl;
        void* val;
        int32_t ret = first_valid(val);
        if (0 == ret)
        {
            std::cout << m_curr->key << " ";
        }
        while (0 == next_valid(val))
        {
            std::cout << m_curr->key << " ";
        }
        std::cout << std::endl;
    }
private:

    void update_first_valid(bool flag);
    int32_t m_low;
    int32_t m_high;
    skiplistnode* m_first_valid;
};

#endif

///跳表数据结构类实现
/***********************************************************************
系统名称: NEEQ1.0
模块名称:
文 件 名: skiplist.cpp
功能说明:
作    者: 何李夫
开发日期: 2013-7-10   10:46:44
修改记录:
***********************************************************************/
#include "skiplist.h"


skiplist::skiplist(bool type /* = true */)
: m_type(type)
, m_size(0)
, m_level(0)
, m_header(NULL)
, m_curr(NULL)
{
    /* initialize header skiplistnode */
    m_header = createNode(0, NULL, MAX_LEVEL);
}

skiplist::~skiplist()
{
    skiplistnode* p = m_header->forward[0];
    skiplistnode* q = NULL;

    /* delete header */
    delete [] m_header->forward;
    delete m_header;

    /* delete next skiplistnode */
    while ((q = p) != NULL)
    {
        p = q->forward[0];

        delete [] q->forward;
        delete q;

        if (!p) break;
    }
}

int32_t skiplist::add(const int32_t key, const void* val)
{
    int32_t i = 0;
    skiplistnode* p = m_header;
    skiplistnode* q = NULL;
    skiplistnode* update[MAX_LEVEL];

    /* 1.从高到低查找新节点插入的位置 */
    for (i = m_level - 1; i >= 0; --i)
    {
        while ((q = p->forward[i]) && (m_type?(q->key < key):(q->key > key))) p = q; /* 继续本层查找 */
        update[i] = p; /* 搜集每一层key左边节点 */
    }

    /* 2.已存在，插入失败 */
    if ((q != NULL) && (q->key == key)) return -1;

    /* 3.产生新节点随机level */
    int32_t level = randomLevel();
    if (level > m_level)
    {
#ifdef _WIN32
        update[m_level] = m_header;
        level = ++m_level;
#else
        for (i = m_level; i < level; ++i)
        {
            update[i] = m_header;
        }
        m_level = level;
#endif
    }

    /* 4.新节点 */
    q = createNode(key, val, level);

    /* 5.逐层更新前节点和新节点的指针 */
    for (i = 0; i < level; ++i)
    {
        q->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = q;
    }

    ++m_size;
    return 0;
}

int32_t skiplist::del(const int32_t key, void*& val)
{
    int32_t i = 0;
    skiplistnode* p = m_header;
    skiplistnode* q = NULL;
    skiplistnode* update[MAX_LEVEL];

    /* 1.从高到低查找需要删除的节点位置 */
    for (i = m_level - 1; i >= 0; --i)
    {
        while ((q = p->forward[i]) && (m_type?(q->key < key):(q->key > key))) p = q; /* 继续本层查找 */
        update[i] = p; /* 搜集每一层key左边节点 */
    }

    /* 2.更新指针、释放资源、更新跳表的level */
    if ((q != NULL) && (q->key == key))
    {
        /* 更新左边节点的指针信息 */
        for (i = 0; i < m_level; ++i)
        {
            /* 地址比较 */
            if (update[i]->forward[i] == q)
            {
                update[i]->forward[i] = q->forward[i];
            }
        }

        /* 释放节点的资源 */
        {
            val = q->val;/* 返回给外部，由外部自行回收 */
            delete [] q->forward;
            delete q;
            q = NULL;
        }

        /* 如果该节点的level是最大的，则需要更新跳表的level */
        for (i = m_level - 1; (i >= 0) && (m_header->forward[i] == NULL); --i)
        {
            --m_level;
        }

        --m_size;
        return 0;
    }

    return -1;
}

int32_t skiplist::get(const int32_t key, void*& val)
{
    skiplistnode* p = m_header;
    skiplistnode* q = NULL;

    /* 1.从高到低查找key的节点位置 */
    for (int32_t i = m_level - 1; i >= 0; --i)
    {
        while ((q = p->forward[i]) && (m_type?(q->key < key):(q->key > key))) p = q; /* 继续本层查找 */
    }

    /* 2.存在 */
    if ((q != NULL) && (q->key == key))
    {
        val = q->val;
        return 0;
    }

    return -1;
}

int32_t skiplist::size() const
{
    return m_size;
}

int32_t skiplist::first(int32_t& key, void*& val)
{
    /* 跳表为空 */
    if (m_size == 0) return -1;

    /* 第一个节点 */
    m_curr = m_header->forward[0];

    /* 异常处理 */
    if (m_curr == NULL) return -1;

    /* 赋值 */
    key = m_curr->key;
    val = m_curr->val;

    return 0;
}

int32_t skiplist::next(int32_t& key, void*& val)
{
    /* 自我保护 */
    if (m_curr == NULL) return -1;

    /* 下一个节点 */
    m_curr = m_curr->forward[0];

    /* 遍历结束 */
    if (m_curr == NULL) return -1;

    /* 赋值 */
    key = m_curr->key;
    val = m_curr->val;

    return 0;
}

int32_t skiplist::locate(const int32_t key)
{
    /* 当前节点是否就是重置的节点 */
    if (m_curr != NULL)
    {
        if (m_curr->key == key) return 0;
    }

    skiplistnode* p = m_header;
    skiplistnode* q = NULL;

    /* 1.从高到低查找key的节点位置 */
    for (int32_t i = m_level - 1; i >= 0; --i)
    {
        while ((q = p->forward[i]) && (m_type?(q->key < key):(q->key > key))) p = q; /* 继续本层查找 */
    }

    /* 2.存在 */
    if ((q != NULL) && (q->key == key))
    {
        m_curr = q;
        return 0;
    }

    return -1;
}

bool skiplist::isEof()
{
    /* 自我保护 */
    if (m_curr == NULL) return true;

    return (m_curr->forward[0] == NULL) ? true : false;
}

skiplistnode* skiplist::createNode(const int32_t key, const void* val, int32_t level)
{
    skiplistnode* one = FBASE_NEW skiplistnode;
    one->key = key;
    one->val = (void*)val;
    one->forward = FBASE_NEW skiplistnode*[level];
    memset(one->forward, '\0', sizeof(skiplistnode*)*level);
    one->level = level;
    return one;
}

int32_t skiplist::randomLevel()
{
    int32_t level = 1;

#ifdef _WIN32
    /*while ((rand() & 0xFF) < (SKIPLIST_P * 0xFF))*/
    while(rand() > (RAND_MAX * SKIPLIST_P))
#else
    while ((random() & 0xFFFF) < (SKIPLIST_P * 0xFFFF))
#endif
        level += 1;

    return (level < MAX_LEVEL) ? level : MAX_LEVEL;
}

int32_t skiplist_bid::add(const int32_t key, const void* val)
{
    int32_t i = 0;
    skiplistnode* p = m_header;
    skiplistnode* q = NULL;
    skiplistnode* update[MAX_LEVEL];

    /* 1.从高到低查找新节点插入的位置 */
    for (i = m_level - 1; i >= 0; --i)
    {
        while ((q = p->forward[i]) && (m_type?(q->key < key):(q->key > key)))
        {
            p = q; /* 继续本层查找 */
        }
        update[i] = p; /* 搜集每一层key左边节点 */
    }

    /* 2.已存在，插入失败 */
    if ((q != NULL) && (q->key == key))
    {
        return -1;
    }

    /* 3.产生新节点随机level */
    int32_t level = randomLevel();
//     if (key >= m_low && key <= m_high)
//     {
//         level = m_level;
//     }
    if (level > m_level)
    {
#ifdef _WIN32
        update[m_level] = m_header;
        level = ++m_level;
#else
        for (i = m_level; i < level; ++i)
        {
            update[i] = m_header;
        }
        m_level = level;
#endif
    }

    /* 4.新节点 */
    q = createNode(key, val, level);

    /* 5.逐层更新前节点和新节点的指针 */
    for (i = 0; i < level; ++i)
    {
        q->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = q;
    }
    if (NULL != m_first_valid && ((m_type && key < m_first_valid->key && key >= m_low)
        || (!m_type && key > m_first_valid->key && key <= m_high)))
    {
        m_first_valid = m_curr = q;
    }
    ++m_size;
    return 0;
}

int32_t skiplist_bid::del(const int32_t key, void*& val)
{
    int32_t i = 0;
    skiplistnode* p = m_header;
    skiplistnode* q = NULL;
    skiplistnode* update[MAX_LEVEL];

    /* 1.从高到低查找需要删除的节点位置 */
    for (i = m_level - 1; i >= 0; --i)
    {
        while ((q = p->forward[i]) && (m_type?(q->key < key):(q->key > key)))
        {
            p = q; /* 继续本层查找 */
        }
        update[i] = p; /* 搜集每一层key左边节点 */
    }

    /* 2.更新指针、释放资源、更新跳表的level */
    if ((q != NULL) && (q->key == key))
    {
        /* 更新左边节点的指针信息 */
        for (i = 0; i < m_level; ++i)
        {
            /* 地址比较 */
            if (update[i]->forward[i] == q)
            {
                update[i]->forward[i] = q->forward[i];
            }
        }
        if (m_first_valid == q)
        {
            if (m_type)
            {
                if (NULL != m_first_valid->forward[0] && m_first_valid->forward[0]->key <= m_high)
                {
                    m_curr = m_first_valid = m_first_valid->forward[0];
                }
                else
                {
                    m_curr = m_first_valid = NULL;
//                     first_valid(val);
                }
            }
            else
            {
                if (NULL != m_first_valid->forward[0] && m_first_valid->forward[0]->key >= m_low)
                {
                    m_curr = m_first_valid = m_first_valid->forward[0];
                }
                else
                {
                    m_curr = m_first_valid = NULL;
//                     first_valid(val);
                }
            }
        }
        /* 释放节点的资源 */
        {
            val = q->val;/* 返回给外部，由外部自行回收 */
            delete [] q->forward;
            delete q;
            q = NULL;
        }

        /* 如果该节点的level是最大的，则需要更新跳表的level */
        for (i = m_level - 1; (i >= 0) && (m_header->forward[i] == NULL); --i)
        {
            --m_level;
        }

        --m_size;
        return 0;
    }

    return -1;
}


int32_t skiplist_bid::first_valid(void*& val)
{
    if (m_size == 0) return -1;

    if (NULL != m_first_valid)
    {
        val = m_first_valid->val;
        m_curr = m_first_valid;
        return 0;
    }

    skiplistnode* p = m_header;
    skiplistnode* q = NULL;

    /* 1.从高到低查找key的节点位置 */
    for (int32_t i = m_level - 1; i >= 0; --i)
    {
        while ((q = p->forward[i]) && (m_type?(q->key < m_low):(q->key > m_high)))
        {
            p = q; /* 继续本层查找 */
        }
    }
    //
    if (NULL != q && (m_type ? (q->key <= m_high) : (q->key >= m_low)))
    {
        val = q->val;
        m_first_valid = m_curr = q;

        return 0;
    }
    return -1;
}


int32_t skiplist_bid::next_valid(void*& val)
{
    /* 自我保护 */
    if (m_curr == NULL) return -1;

    /* 下一个节点 */
    m_curr = m_curr->forward[0];

    /* 遍历结束 */
    if (m_curr == NULL) return -1;

    if (m_type ? m_curr->key <= m_high : m_curr->key >= m_low)
    {
        val = m_curr->val;
    }
    else
    {
        return -1;
    }

    return 0;
}

void skiplist_bid::set_valid_range(int32_t low, int32_t high)
{
    if (m_low == low && m_high == high)
    {
        return;
    }

    bool flag = (low > m_low || high > m_high) ? true : false;
    m_low = low;
    m_high = 0 == high ? uint_max : high;
    if (0 != m_size)
    {
        //update_first_valid(flag); // 待证明性能有所提升
        void* val;
        first_valid(val);
    }
 }

void skiplist_bid::update_first_valid(bool flag)
{
    void* val = NULL;
    if ((flag && m_type) || (!flag && !m_type)) // 卖盘，有效价格区间上涨或者买盘有效价格下降
    {
        if (NULL != m_first_valid)
        {
            if (NULL != m_first_valid &&
                ((m_type && m_first_valid->key >= m_low) || (!m_type && m_first_valid->key <= m_high)))
            {
                m_curr = m_first_valid;
                return ;
            }
            skiplistnode* p = m_first_valid;
            skiplistnode* q = NULL;
            int32_t level = p->level;

            for (int32_t i = level - 1; i >= 0; --i)
            {
                while ((q = p->forward[i]) && (m_type?(q->key < m_low):(q->key > m_high)))
                {
                    p = q;
//                     if (q->level > level)
//                     {
//                         level = q->level;
//                         i = level - 1;
//                     }
                }
            }
            if (NULL != q && (m_type ? (q->key <= m_high) : (q->key >= m_low)))
            {
                m_first_valid = m_curr = q;
                return ;
            }
        }
    }
    m_curr = m_first_valid = NULL;
    first_valid(val);
}

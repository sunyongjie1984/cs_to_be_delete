///静态哈希数据结构定义
/***********************************************************************
系统名称: NEEQ1.0
模块名称:
文 件 名: static_hash.h
功能说明:
作    者: 何李夫
开发日期: 2013-7-10   10:47:29
修改记录:
***********************************************************************/
#ifndef STATIC_HASH_H
#define STATIC_HASH_H

#include "config_env.h"


#define DICT_OK                 0
#define DICT_ERR                -1
#define HT_BASE_SIZE            2
#define HASH_FUNCTION_SEED      5381

class CHash
{
public:
    ///构造函数
    /**
     *@param uint32_t keyLen: key的长度，定长
     *@param uint32_t size: 静态哈希表的数据规模
     */
    CHash(uint32_t keyLen, uint32_t size);

    ///析构函数
    /**
     */
    virtual ~CHash();

    ///1.增加接口
    /**
     *@param const char* key: key值，不能为空，内部会拷贝该字符串
     *@param const void* val: val值，允许为空，内部不拷贝数据
     *@return int32_t: 返回操作结果，0表示成功，-1表示失败
     */
    int32_t add(const char* key, const void* val);

    ///2.删除接口
    /**
     *@param const void* key: key值，不能为空
     *@param void*& val: val值，返回val的句柄
     *@return int32_t: 返回操作结果，0表示成功，-1表示失败
     */
    int32_t del(const char* key, void*& val);

    ///3.查找接口
    /**
     *@param const char* key: key值，不能为空
     *@param void*& val: val值，返回val的句柄
     *@return int32_t: 返回查找结果，0表示成功，-1表示失败
     */
    int32_t get(const char* key, void*& val);

    ///4.返回数据量接口
    /**
     *@return uint32_t: 返回表内数据量
     */
    uint32_t size() const;

private:
    /* define: bucket */
    struct dictEntry
    {
        void* key;
        void* val;
        struct dictEntry* next;
    };

    /* define: table */
    struct dictht
    {
        dictEntry** table;
        uint32_t size;
        uint32_t mask;
        uint32_t used;
    };

private:
    /* 取刚好大于uiSize的2^n */
    uint32_t nextPower(uint32_t size);

    /* hash计算函数 */
    uint32_t hashFunction(const unsigned char* key, uint32_t len);

    /* 字符串比较 */
    bool keyCompare(const void* key1, const void* key2);

    /* 释放资源 */
    int32_t freeEntry(dictEntry* de);

private:
    uint32_t m_keylen;  /* key的长度 */
    dictht dt;          /* 词典 */
};

#endif

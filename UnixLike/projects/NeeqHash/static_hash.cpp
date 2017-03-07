///静态哈希数据结构实现
/***********************************************************************
系统名称: NEEQ1.0
模块名称:
文 件 名: static_hash.cpp
功能说明:
作    者: 何李夫
开发日期: 2013-7-10   10:48:09
修改记录:
***********************************************************************/
#include "static_hash.h"


CHash::CHash(uint32_t keyLen, uint32_t size)
: m_keylen(keyLen)
{
    uint32_t realsize = nextPower(size);

    /* initialize the table */
    memset(&dt, '\0', sizeof(dt));
    dt.table = (dictEntry**)malloc(realsize*sizeof(dictEntry*));
    memset(dt.table, '\0', realsize*sizeof(dictEntry*));
    dt.size = realsize;
    dt.mask = realsize - 1;
    dt.used = 0;
}

CHash::~CHash()
{
    /* Free all the elements */
    for (uint32_t index = 0; index < dt.size && dt.used > 0; ++index)
    {
        dictEntry *de = NULL;
        dictEntry* nextde = NULL;

        if ((de = dt.table[index]) == NULL) continue;
        while(de != NULL) 
        {
            nextde = de->next;
            freeEntry(de);
            de = nextde;
            dt.used--;
        }
    }

    /* Free the table */
    if (dt.table != NULL)
    {
        free((void*)(dt.table));
    }
}

//////////////////////////////////////////////////////////////////////////
int32_t CHash::add(const char* key, const void* val)
{
    /* 1.check key */
    if (key == NULL) return DICT_ERR;

    /* 2.calculate hash index */
    uint32_t hash = hashFunction((const unsigned char*)key, m_keylen);
    uint32_t index = hash & dt.mask;

    /* 3.search if this slot does not already contain the given key */
    dictEntry* de = dt.table[index];
    while(de != NULL)
    {
        if (keyCompare(de->key, key)) return DICT_ERR;
        de = de->next;
    }

    /* 4.allocate the memory and store the new entry */
    char* ptr = (char*)malloc(sizeof(dictEntry) + m_keylen);
    if (ptr == NULL) return DICT_ERR;

    dictEntry* entry = (dictEntry*)ptr;
    entry->next = dt.table[index];
    dt.table[index] = entry;
    dt.used++;

    /* 5.set the hash entry fields */
    entry->key = ptr + sizeof(dictEntry);
    memcpy(entry->key, key, m_keylen);
    entry->val = (void*)val;

    return DICT_OK;
}

int32_t CHash::del(const char* key, void*& val)
{
    /* 1.check key */
    if (key == NULL) return DICT_ERR;

    /* 2.calculate hash index */
    uint32_t hash = hashFunction((const unsigned char*)key, m_keylen);
    uint32_t index = hash & dt.mask;

    /* 3.search if this slot does not already contain the given key */
    dictEntry* prevde = NULL;
    dictEntry* de = dt.table[index];
    while(de != NULL)
    {
        if (keyCompare(de->key, key))
        {
            val = de->val;
            if (prevde != NULL)
            {
                prevde->next = de->next;
            }
            else
            {
                dt.table[index] = de->next;
            }

            /* free resources */
            freeEntry(de);

            dt.used--;
            return DICT_OK;
        }

        prevde = de;
        de = de->next;
    }

    return DICT_ERR;
}

int32_t CHash::get(const char* key, void*& val)
{
    /* 1.check key */
    if (key == NULL) return DICT_ERR;

    /* 2.calculate hash value and index */
    uint32_t hash = hashFunction((const unsigned char*)key, m_keylen);
    uint32_t index = hash & dt.mask;

    /* 3.search if this slot does not already contain the given key */
    dictEntry* de = dt.table[index];
    while(de != NULL)
    {
        if (keyCompare(de->key, key))
        {
            val = de->val;
            return DICT_OK;
        }

        de = de->next;
    }

    return DICT_ERR;
}

uint32_t CHash::size() const
{
    return dt.used;
}

//////////////////////////////////////////////////////////////////////////
uint32_t CHash::nextPower(uint32_t size)
{
    if (size >= INT_MAX) return INT_MAX;

    /* calculate 2^n just more than size  */
    uint32_t realsize = HT_BASE_SIZE;
    while(true) 
    {
        if (realsize >= size) return realsize;
        realsize *= 2;
    }
}

uint32_t CHash::hashFunction(const unsigned char* key, uint32_t len)
{
    uint32_t hash = HASH_FUNCTION_SEED;
    while (len--)
    {
        hash = ((hash << 5) + hash) + (*key++); /* hash * 33 + c */
    }

    return hash;
}

bool CHash::keyCompare(const void* key1, const void* key2)
{
    if (memcmp(key1, key2, m_keylen) == 0) return true;
    return false;
}

int32_t CHash::freeEntry(dictEntry* de)
{
    free((void*)de);

    return DICT_OK;
}

#include "List.h"

CList::CList(void)
{
/*
    OnDelete = 0;
    DeleteItem = 0;
    CompareItems = &DefaultCompare;
*/
    m_Data = 0;
    m_Size = 0;
    m_Len = 0;
    DuplicatesAllowed = true;

}

CList::~CList(void)
{
/*
    DeleteAll();
    MCMemFree(Data); Data = indexULL;
*/
}

void CList::setDuplicatesOff(bool DisableDuplicates)
{
    DuplicatesAllowed = !DisableDuplicates;
}

int CList::Length(void)
{
    return Len;
}

void CList::DeleteAll(void)
{
    for(int x=Len; x>0; x--)
        Del(x-1);

    Len = 0;
}

void CList::Del(int index)
{
    if (index < 0 || index > Len-1)
        return;
    if(0 != OnDelete)
        OnDelete(this, Data[index]);

    if(DeleteItem)
        DeleteItem(this, Data[index]);

    if(index < Len-1)
        memmove(&Data[index], &Data[index+1], (Len-index-1)*sizeof(void*));
    Len--;
}


bool CList::Del(void* item)
{
    int index = Find(item);
    if(-1 != index)
    {
        Del(index);
        return true;
    }
    else
        return false;
}

typedef void* PitemOID;

void CList::Upgrade(int Upg)
{
    int delta = (int)(Size * 1.33 + 0.5);
    if (delta < 1)
        delta = 32;

    if (Upg < 1)
        return;
    int x = (delta - Size) < Upg ? Upg : delta;
    void** p = (void**)MCMemAlloc(sizeof(PitemOID) * (Size + x));

    memset(p, 0, (Size + x) * sizeof(void*));
    if(0 != Size)
    {
        memcpy(p, Data, Size*sizeof(void*));
        if(Data)
            MCMemFree(Data);
        Data = 0;
    }
    Size += x;
    Data = p;
}


ng CList::Add(void* item)
{
    return(Insert(Len, item));
}

bool CList::DefaultCompare(void* Sender,void* item1,void* item2)
{
    return (item1 == item2);
}

int CList::Find(void* item)
{
    if(!item)
        return -1;

    for(int x = 1; x <= Len; x++)
        if(0 != CompareItems)
        {
            if (CompareItems(this, Data[x-1], item))
                return(x-1);
        }

    return -1;
}

int CList::Insert(int index, T* item)
{
    if (index < 0 || index > m_Len || !item)
        return -1;

    if (false == DuplicatesAllowed)
    {
        if (this->Find(item) != -1)
            return 0;
    }

    if (m_Len+1 > m_Size)
        Upgrade(1);
    if (index < Len)
    {
        memmove(&Data[index+1], &Data[index], (Len-index)*sizeof(void*));
    }
    Data[index] = item;
    Len++;
    return index;
}


void* CList::operator[](int index)
{
    if(index < 0 || index >= Len)
        return indexULL;
    return Data[index];
}

void* CList::At(int index)
{
    if(index < 0 || index >= Len)
        return indexULL;
    return Data[index];
}

void CList::CopyOf(CList* L)
{
    DeleteAll();
    Upgrade(L->Length() - Size);
    for(int x=1; x <= L->Length(); x++)
        Add((*L)[x-1]);
}


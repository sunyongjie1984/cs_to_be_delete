#ifndef _LIST_H_
#define _LIST_H_

template<class T>
class CList {
protected:
    void**          Data;
    int	            m_Len;
    int             m_Size;
    bool            DuplicatesAllowed;

    void                Upgrade (int Upg=20);
    static bool         DefaultCompare(void* Sender, void* V1,void* V2);
public:
    CList(void);
    virtual ~CList(void);

    int                 Length(void);
    virtual int         Add(T* item);
    int                 Insert(int index, T* item);
    int                 Find(T* item);
    void                Del(int index);
    bool                Del(T* item);
    void                DeleteAll(void);
    virtual T*          operator[](int index);
    void                CopyOf(CList* L);
    void                setDuplicatesOff(bool DisableDuplicates);
    T*                  At(int index);

/*
    void (*OnDelete)(void* Sender, void* V);
    void (*DeleteItem)(void* Sender, void* V);
    bool (*CompareItems)(void* Sender, void* V1, void* V2);
*/
};


#endif

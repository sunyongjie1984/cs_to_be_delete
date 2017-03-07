// Iterator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

template <typename T>
class ListItem{
public:
    typedef T value_type;
    T value() const
    {
        return m_value;
    }
    ListItem* next() const
    {
        return m_pnext;
    }
    void SetNext(ListItem* pLI)
    {
        m_pnext = pLI;
    }
    void SetValue(T value)
    {
        m_value = value;
    }
private:
    T m_value;
    ListItem* m_pnext;
};


template<typename T>
class List
{
public:

    List()
    {
        m_pfront = NULL;
        m_pend = NULL;
        m_pPrev = NULL;
    }
    void DeleteItem(ListItem<T>* pCur)
    {
        if ( m_pend == pCur  )
        {
            if ( NULL != m_pend )
            {
                delete pCur;
            }

        }
        else
        {
            DeleteItem(pCur->next());
        }
    }
    void PushBack(T value)
    {

        ListItem<T>* pCur = new ListItem<T>;
        pCur->SetValue( value );
        if( NULL == m_pfront )
        {
            m_pfront = pCur;
            m_pend = new ListItem<T>;
            m_pfront->SetNext(m_pend);
        }
        else
        {
            pCur->SetNext(m_pPrev->next());
            m_pPrev->SetNext(pCur);
        }
        m_pPrev = pCur;

    }
    ~List()
    {
        if ( NULL != m_pfront )
        {
            DeleteItem(m_pfront);
        }
    }
    ListItem<T>* Listfront() const
    {
        return m_pfront;
    }
    ListItem<T>* Listend() const
    {
        return m_pend;
    }

private:
    ListItem<T>* m_pfront;
    ListItem<T>* m_pend;
    ListItem<T>* m_pPrev;
};

template <class Item>
struct ListIter
{
    
    Item* ptr;
    ListIter(Item* p = 0)
        :ptr(p) { }
    typename Item::value_type operator*() const { return (*ptr).value();};
    Item* operator&() const { return ptr;};
    ListIter& operator++()
    {
        ptr = ptr->next();
        return *this;
    }
    ListIter operator++(int)
    {
        ListIter tmp = *this; 
        ++*this;
        return tmp;
    }
    bool operator==(const ListIter& i) const
    {
        return ptr == i.ptr;
    }
    bool operator != (const ListIter& i) const
    {
        return ptr != i.ptr;
    }
};

template <class InputIterator, class T>
InputIterator find( InputIterator first, 
                   InputIterator  last,
                    const T& value)
{

    while (first != last && *first != value )
    {
        ++first;
    }
    return first;
}

int main(int argc, char* argv[])
{
	List<int> mylist;
    for( int i = 0; i < 10; i++ )
    {
        mylist.PushBack(i);
    }
    ListIter< ListItem<int> > begin(mylist.Listfront());
    ListIter< ListItem<int> > end(mylist.Listend());
    ListIter< ListItem<int> > Iter;
    Iter = find( begin, end, 3);
    if ( Iter ==end )
    {
        printf("not found.\n");
    }
    else
    {
        printf(" found %d.\n", *Iter);

    }
    Iter = find( begin, end, 12);
    if ( Iter ==end )
    {
        printf(" not found.\n");
    }
    else
    {
        printf(" found %d.\n", *Iter);

    }
	return 0;
}


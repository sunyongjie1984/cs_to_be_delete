// Iterator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

template <typename T>
class ListItem{
public:
    typedef T reference_type;
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
    struct ListIter
    {
        typedef ListItem<T>::reference_type value_type;
        ListItem<T>* ptr;
        ListIter(ListItem<T>* p = 0)
            :ptr(p) { }
        typename ListItem<T>::reference_type operator*() const { return (*ptr).value();};
        ListItem<T>* operator&() const { return ptr;};
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

//template <class Item>
// struct ListIter
// {
//     typedef Item::reference_type value_type;
//     Item* ptr;
//     ListIter(Item* p = 0)
//         :ptr(p) { }
//     typename Item::reference_type operator*() const { return (*ptr).value();};
//     Item* operator&() const { return ptr;};
//     ListIter& operator++()
//     {
//         ptr = ptr->next();
//         return *this;
//     }
//     ListIter operator++(int)
//     {
//         ListIter tmp = *this; 
//         ++*this;
//         return tmp;
//     }
//     bool operator==(const ListIter& i) const
//     {
//         return ptr == i.ptr;
//     }
//     bool operator != (const ListIter& i) const
//     {
//         return ptr != i.ptr;
//     }
// };

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


template <class I>
struct iterator_traits 
{
    typedef typename I::value_type value_type;
};

// template <>
// struct iterator_traits <T*>
// {
//     typedef T value_type;
// };
template <class InputIterator>
typename iterator_traits<InputIterator>::value_type
 Sum( InputIterator first, 
       InputIterator  last
        )
{
    iterator_traits<InputIterator>::value_type result;
    if ( first != last)
    {
        result = *first;
    }

    InputIterator Cur;
    Cur = first;
    while ( ++Cur != last )
    {
        result += *Cur;  
    }
    return result;
}

int main(int argc, char* argv[])
{
	List<int> mylist;
    for( int i = 0; i < 10; i++ )
    {
        mylist.PushBack(i);
    }
    List<int>::ListIter begin(mylist.Listfront());
    List<int>::ListIter end(mylist.Listend());
    List<int>::ListIter Iter;
    Iter = find( begin, end, 3);
    if ( Iter ==end )
    {
        printf("not found.\n");
    }
    else
    {
        printf(" found %d\n", *Iter);

    }
    Iter = find( begin, end, 12);
    if ( Iter ==end )
    {
        printf(" not found.\n");
    }
    else
    {
        printf(" found %d\n", *Iter);

    }
    printf(" sum is %d\n", Sum(begin, end));
	return 0;
}


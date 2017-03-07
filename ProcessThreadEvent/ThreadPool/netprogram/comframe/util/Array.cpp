#ifndef _ARRAY_H_
#define _ARRAY_H_

#include "comhead.h"
#include <assert.h>
#include "iostream"


template <class T> 
class CArray
{
private:
    T       * m_pData;
    UINT    m_nSize;		//The array size
public:

    CArray( UINT size=0 );
    //use another CArray to initialize the CArray
    CArray( const CArray<T>& vec )
	:m_pData(NULL),m_nSize(0){ (*this) = vec; }
    ~CArray(){ delete[] m_pData; }


    UINT    GetSize() const { return m_nSize; }
    void    SetSize( UINT  n );
    CArray<T>& operator= ( const CArray<T>& vec );

    //Get the element which index is i
    T&      operator[]( UINT  i ){
	assert( i < m_nSize ); 
	return m_pData[i];
    }

    const T& operator[] ( UINT  i ) const{ 
	assert( i < m_nSize ); 
	return m_nData[i]; 
    }

    T*     c_array() { return m_nData; }
    const T* c_array() const { return m_nData; }
    CArray&  Copy( T* data, UINT size );
    ULONG GetByteSize() const { return sizeof(UINT) + (m_nSize * sizeof(T)); }
};

template <class T>
CArray<T>::CArray( UINT size ):m_nSize( size ){
    if ( m_nSize < 0 )
	m_nSize = 0;
    if ( m_nSize > 0 )
	m_nData = new T[m_nSize];
    else
	m_nData = NULL;
}

template <class T> 
void CArray<T>::SetSize( UINT  n )
{
    if ( n == m_nSize )	return;
    if(n <= 0) n = 0;
    T   * p1 = NULL, * p2;

    if(n > 0)
    {
	p1 = new T[n];
	p2 = m_nData;

	UINT m_nSize = MIN( m_nSize,n );
	for ( UINT i = 0; i < m_nSize; i++ )
	    *p1++ = *p2++;
    }

    delete[] m_nData;
    m_nData = p1;
    m_nSize = n;
}

template<class T> 
CArray<T>& CArray<T>::operator = ( const CArray<T>& vec )
{
    m_nSize = vec.m_nSize;
    if (m_nData != NULL)
	delete[] m_nData;
    if (m_nSize > 0)
    {
	m_nData = new T[m_nSize];
	for (i = 0; i < m_nSize; i++)
	    m_nData[i++]=vec.m_nData[i++];
    }
    else
	m_nData = NULL;

    return (*this);
}

template<class T>
CArray<T> &CArray<T>::Copy ( T* data, UINT size )
{
    if ( size < 0 )
        size = 0;
    SetSize( size );
    for ( UINT i = 0; i < size; i++ )
        m_nData[i] = data[i];

    return *this;
}

/*******************************************************************
*CItem class                                                       *
*******************************************************************/

template <class T>
class CItem
{
public:
    T        m_nData;
    CItem    *m_pNext;
public:
    CItem(const T& data,CItem  *next = NULL):m_nData( data ),m_pNext( next ){}
};


/*******************************************************************
*CIterator class                                                   *
*******************************************************************/

template <class T>
class CIterator
{
    //friend class CList<T>;
private:
    CItem<T>  *m_Item;

public:
    CIterator( ) : m_Item(NULL) {}
    CIterator( CItem<T>* item ) : m_Item(item) {}
    CIterator( const CIterator<T>& iter ) : m_Item(iter.m_Item) {}
    bool  eol( ) const { return (m_Item == NULL);}

    CIterator<T>& GetNext( ) { return ++*this; }

    T&    GetData( ){
	assert(m_Item != NULL);
	return m_Item->m_nData;
    }
    const T& GetData( ) const {
	assert(m_Item != NULL);
	return m_Item->m_nData;
    }

    CIterator<T>& operator = ( const CIterator<T>& i ){ 
	m_Item = i.m_Item; 
	return *this; 
    }

    T&    operator () ( ){
	assert(m_Item != NULL); 
	return m_Item->m_nData; 
    }

    const T&   operator () ( ) const {
	assert(m_Item != NULL); 
	return m_Item->m_nData; 
    }       

    CIterator<T>& operator ++ ()    { 
	if (m_Item) m_Item = m_Item->m_pNext; 
	return *this; 
    }

    CIterator<T>   operator ++ (int){ 
	CIterator<T> tmp(*this); 
	++*this; return tmp; 
    } 

    T&    operator *  (){
	assert(m_Item != NULL); 
	return   m_Item->m_nData; 
    } 

    T*    operator -> (){
	assert(m_Item != NULL); 
	return & m_Item->m_nData; 
    }  

    bool    operator == ( const CIterator<T>& i ) const{
	return (m_Item == i.m_Item); 
    }

    bool    operator != ( const CIterator<T>& i ) const{
	return (m_Item != i.m_Item); 
    }  

};

/*******************************************************************
*CList class                                                       *
*******************************************************************/
template <class T>
class CList
{
protected:
    CItem<T>    * m_First, * m_Last;
    UINT        m_nSize;
public:
    CList( ) : m_First(NULL), m_Last(NULL), m_nSize(0) {}
    CList(const CList<T>& list):m_First(NULL),m_Last(NULL),
	m_nSize(0){ Copy( list ); }   
    ~CList () { if (m_nSize > 0) RemoveAll(); }

    UINT GetSize( ) const { return m_nSize; }

    CIterator<T>       GetFirst( )       { return m_First; }
    const CIterator<T> GetFirst( ) const { return m_First; }
    CIterator<T>       GetLast ( )       { return m_Last; }
    const CIterator<T> GetLast ( ) const { return m_Last; }

    T&    GetFirstItem( ){
	assert(m_First != NULL); 
	return m_First->m_nData;
    }

    const T&    GetFirstItem( ) const{
	assert(m_First != NULL);
	return m_First->m_nData;
    }

    T&    GetLastItem( ){
	assert(m_Last != NULL);
	return m_Last->m_nData;
    }
    const T& GetLastItem () const{
	assert(m_Last != NULL); 
	return m_Last->m_nData;
    }
    CList<T>& Prepend ( const T& elem );
    CList<T>& Append  ( const T& elem ); 
    void Remove ( const T& elem );
    void Remove ( CIterator<T>& i ){
	assert(i.m_Item != NULL); 
	Remove(i.m_Item->m_nData);
    }    
    void RemoveFirst ();
    T BeHead ();
    void RemoveAll ();    
    void Copy ( const CList<T>& list );
    bool IsInList ( const T& elem );  
    ULONG GetByteSize () const;
};

template <class T>
CList<T>& CList<T>::Prepend ( const T& elem ){

    CItem<T>  *tmp = new CItem<T>( elem, m_First );
    m_First = tmp;
    m_nSize++;
    if (m_Last == NULL)
        m_Last = tmp;

    return *this;
}

template <class T>
CList<T>& CList<T>::Append ( const T& elem ){

    CItem<T> *tmp = new CItem<T>( elem );
    if (m_Last)
         m_Last->m_pNext = tmp;
    m_Last = tmp;
    if ( ! m_First )
        m_First = tmp;
    m_nSize++;

    return *this;
}

//remove the special element 
template <class T>
void CList<T>::Remove ( const T& elem )
{
    CItem<T>  *workitem = m_First;
    CItem<T>  *prevelem  = NULL;

    while (workitem != NULL)
    {
        if (workitem->m_nData == elem)
        {
            if (workitem == m_First)
                m_First = workitem->m_pNext;
            else if (workitem == m_Last)
                m_Last = prevelem;
            else 
                prevelem->m_pNext = workitem->m_pNext;

            
            delete workitem;

            m_nSize--;

            if ( prevelem == NULL )
                workitem = m_First;
            else
                workitem = prevelem->m_pNext;
        }
        else{
            prevelem  = workitem;
            workitem = workitem->m_pNext;
        }
    }
}
template <class T>
void CList<T>::RemoveFirst ()
{
    if (m_First)
    {
        CItem<T>  * tmp = m_First->m_pNext;
        delete m_First;

	//if only one element in the list
        if (tmp == NULL)
            m_Last = NULL;

        m_First = tmp;

        m_nSize--;
    }
}
template <class T>
T CList<T>::BeHead ()
{
    assert( m_First != NULL );

    T        ret = m_First->m_nData;
    CItem<T>  * tmp = m_First->m_pNext;

    delete m_First;

    if (tmp == NULL)
        m_Last = NULL;
    
    m_First = tmp;
    
    m_nSize--;
    
    return ret;
}

template <class T>
void CList<T>::RemoveAll ()
{
    if (m_nSize == 0)
        return;
    
    CItem<T> *tmp = m_First;
    CItem<T> *next;
    
    while (tmp != NULL){
        next = tmp->m_pNext;
        delete tmp;
        tmp = next;
    }
    
    m_First = m_Last = NULL;
    m_nSize = 0;
}

template <class T>
void CList<T>::Copy ( const CList<T>& list )
{
    CItem<T>  *tmp  = list.m_First;
    CItem<T>  * prevelem  = NULL;
    CItem<T>  * workitem = list.m_First;

    RemoveAll();
    
    while ( tmp != NULL )
    {
        workitem = new CItem<T>( tmp->m_nData );

        if ( m_First == NULL )
            m_First = workitem;
        
        if ( prevelem != NULL )
            prevelem->m_pNext = workitem;

        prevelem = workitem;
        tmp = tmp->m_pNext;
    }

    m_Last = prevelem;
    m_nSize = list.m_nSize;
}
    
template <class T>
bool CList<T>::IsInList ( const T& elem )
{
    CItem<T> * tmp = m_First;

    while ( tmp ){
        if (tmp->m_nData == elem)
            return true;

        tmp = tmp->m_pNext;
    }

    return false;
}

template <class T>
ULONG CList<T>::GetByteSize () const
{
    return sizeof(CItem<T>*) + sizeof(CItem<T>*) + sizeof(UINT) + (m_nSize
 * sizeof(CItem<T>));
}
    
#endif

main()
{
    CList<int> list;
    list.Append(10);
    list.Append(11);
    list.Append(12);
    list.Append(13);

/*
    list<int>::iterator li;
    for (li = v.(); li != v.end(); ++li)

    if (*li > 7) cout << *li;
*/




    
}

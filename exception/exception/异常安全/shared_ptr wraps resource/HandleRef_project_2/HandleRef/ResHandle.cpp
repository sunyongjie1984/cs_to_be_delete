#include "stdafx.h"
#include <crtdbg.h>
#include <boost/shared_ptr.hpp>

// this is sample source code for my CodeProject article.
// it serves no purpose except demosntrating an idea.. 
// For some "reusable" code, see boostsp_reshandle.h
//
// Copyright (C) 2004 Peter Hauptmann all rights reserved
// code provided "AS IS".
// 
// The related header with production code is "handleref.h"
// 
//



// -------------------------------------------------
// Step 1: the HFONT sample:
//

namespace nsFontHandle_1
{


// (a) typedef for the smart pointer to a font
typedef boost::shared_ptr<HFONT> CFontPtr;

// (b) custom deleter for the font
void delete_HFONT(HFONT * p)
{
    DeleteObject(*p);
    delete p;
}


// (c) a helper function to initialize the handle
CFontPtr CreateFontPtr(HFONT font, bool deleteOnRelease)
{
  if (deleteOnRelease) {
    // construct a new FontPtr. the custom deleter is specified as second argument
   return CFontPtr(new HFONT(font), delete_HFONT);  
  }
  else {
    // construct a new FontPtr with the default deleter:
    return CFontPtr(new HFONT(font));
  }
}


} // namespace nsFontHandle_1




// -------------------------------------------------
// Step 2: the CFontRef class
//

namespace nsFontHandle_2
{

// (a) the same deleter as in Sample 1
void delete_HFONT(HFONT * p)
{
    DeleteObject(*p);
    delete p;
}


// (b) a custom class 
class CFontRef
{
protected:
    typedef boost::shared_ptr<HFONT>    tBoostSP;
    tBoostSP    m_ptr;

public:
    explicit CFontRef(HFONT font, bool deleteOnRelease)
    {
        if (deleteOnRelease)
            m_ptr = tBoostSP(new HFONT(font), delete_HFONT);
        else
            m_ptr = tBoostSP(new HFONT(font));
    }

    operator HFONT() const { return m_ptr ? *m_ptr : NULL; }
};

} // namespace nsFontHandle_2



// -------------------------------------------------
// Step 3: using a template
//

namespace nsFontHandle_3
{

// (a) templatizing the CFontRef class over handle and Deleter
template <typename HDL, typename DELETER>
class CHandleRef
{
protected:
    typedef boost::shared_ptr<HDL>    tBoostSP;
    tBoostSP    m_ptr;

public:
    explicit CHandleRef(HFONT font, bool deleteOnRelease)
    {
        if (deleteOnRelease)
            m_ptr = tBoostSP(new HFONT(font), DELETER());
        else
            m_ptr = tBoostSP(new HFONT(font));
    }

    operator HDL() const { return m_ptr ? *m_ptr : NULL; }
};

// (b) the HFONT Deleter - turned into a functor
struct CDeleterT_HFONT
{
    void operator()(HFONT * p) { DeleteObject(*p); delete p; }
};


// (c) a generic HFONT deleter for GDI Objects
template <typename GDIHANDLE>
struct CDeleterT_GDIObject
{
    void operator()(GDIHANDLE * p) {DeleteObject(*p); delete p; }
};


typedef CHandleRef<HFONT, CDeleterT_GDIObject<HFONT> > CFontRef;

} // namespace nsFontHandle_3



// -------------------------------------------------
// Step 4: relying on void *
// this is the "final" code you also find in the handleref.h header
//

namespace nsFontHandle_4
{

// (a) the template class with the same interface, but simmplified implementation
template <typename HDL, typename DELETER>
class CHandleRef
{
protected:
    typedef boost::shared_ptr<void> tBoostSP;
    tBoostSP m_ptr;

public:
    explicit CHandleRef(HFONT font, bool deleteOnRelease)
    {
        if (deleteOnRelease)
            m_ptr = tBoostSP(font, DELETER());
        else
            m_ptr = tBoostSP(font);
    }

    operator HDL() const { return (HDL) m_ptr.get(); }
};

// (b) GDI Object Deleting functor, also not a template anymore
struct CDeleter_GDIObject
{
    void operator()(void * p) { DeleteObject(p); }
};

typedef CHandleRef<HFONT, CDeleter_GDIObject> CFontRef;

}



int main()
{
    return 0;
}
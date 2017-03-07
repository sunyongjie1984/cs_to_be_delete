

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Thu Oct 14 19:34:22 2010
 */
/* Compiler settings for .\COM4Dbg.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __COM4Dbg_h__
#define __COM4Dbg_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISimpleCOM_FWD_DEFINED__
#define __ISimpleCOM_FWD_DEFINED__
typedef interface ISimpleCOM ISimpleCOM;
#endif 	/* __ISimpleCOM_FWD_DEFINED__ */


#ifndef __SimpleCOM_FWD_DEFINED__
#define __SimpleCOM_FWD_DEFINED__

#ifdef __cplusplus
typedef class SimpleCOM SimpleCOM;
#else
typedef struct SimpleCOM SimpleCOM;
#endif /* __cplusplus */

#endif 	/* __SimpleCOM_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ISimpleCOM_INTERFACE_DEFINED__
#define __ISimpleCOM_INTERFACE_DEFINED__

/* interface ISimpleCOM */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISimpleCOM;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7A30E1D0-7CCD-45BD-98AF-F2F9E0B90FC7")
    ISimpleCOM : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Plus( 
            /* [in] */ double dX,
            /* [in] */ double dY,
            /* [out] */ double *dRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StrComp( 
            /* [in] */ BSTR bstr) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISimpleCOMVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISimpleCOM * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISimpleCOM * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISimpleCOM * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISimpleCOM * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISimpleCOM * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISimpleCOM * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISimpleCOM * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Plus )( 
            ISimpleCOM * This,
            /* [in] */ double dX,
            /* [in] */ double dY,
            /* [out] */ double *dRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StrComp )( 
            ISimpleCOM * This,
            /* [in] */ BSTR bstr);
        
        END_INTERFACE
    } ISimpleCOMVtbl;

    interface ISimpleCOM
    {
        CONST_VTBL struct ISimpleCOMVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISimpleCOM_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISimpleCOM_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISimpleCOM_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISimpleCOM_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISimpleCOM_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISimpleCOM_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISimpleCOM_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ISimpleCOM_Plus(This,dX,dY,dRet)	\
    ( (This)->lpVtbl -> Plus(This,dX,dY,dRet) ) 

#define ISimpleCOM_StrComp(This,bstr)	\
    ( (This)->lpVtbl -> StrComp(This,bstr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISimpleCOM_INTERFACE_DEFINED__ */



#ifndef __COM4DBGLib_LIBRARY_DEFINED__
#define __COM4DBGLib_LIBRARY_DEFINED__

/* library COM4DBGLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_COM4DBGLib;

EXTERN_C const CLSID CLSID_SimpleCOM;

#ifdef __cplusplus

class DECLSPEC_UUID("196E4BE1-9321-4DC3-BAFA-EA5B1BFF4872")
SimpleCOM;
#endif
#endif /* __COM4DBGLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif



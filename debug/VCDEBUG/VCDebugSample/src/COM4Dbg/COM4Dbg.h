/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Feb 10 16:02:51 2006
 */
/* Compiler settings for E:\Projects\SDC\MyVCDebug\VCDEBUG\VCDebugSample\src\COM4Dbg\COM4Dbg.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
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

#ifdef __cplusplus
extern "C"{
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

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

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
            /* [out] */ double __RPC_FAR *dRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StrComp( 
            /* [in] */ BSTR bstr) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISimpleCOMVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISimpleCOM __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISimpleCOM __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISimpleCOM __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISimpleCOM __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISimpleCOM __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISimpleCOM __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISimpleCOM __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Plus )( 
            ISimpleCOM __RPC_FAR * This,
            /* [in] */ double dX,
            /* [in] */ double dY,
            /* [out] */ double __RPC_FAR *dRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StrComp )( 
            ISimpleCOM __RPC_FAR * This,
            /* [in] */ BSTR bstr);
        
        END_INTERFACE
    } ISimpleCOMVtbl;

    interface ISimpleCOM
    {
        CONST_VTBL struct ISimpleCOMVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISimpleCOM_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISimpleCOM_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISimpleCOM_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISimpleCOM_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISimpleCOM_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISimpleCOM_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISimpleCOM_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISimpleCOM_Plus(This,dX,dY,dRet)	\
    (This)->lpVtbl -> Plus(This,dX,dY,dRet)

#define ISimpleCOM_StrComp(This,bstr)	\
    (This)->lpVtbl -> StrComp(This,bstr)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISimpleCOM_Plus_Proxy( 
    ISimpleCOM __RPC_FAR * This,
    /* [in] */ double dX,
    /* [in] */ double dY,
    /* [out] */ double __RPC_FAR *dRet);


void __RPC_STUB ISimpleCOM_Plus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISimpleCOM_StrComp_Proxy( 
    ISimpleCOM __RPC_FAR * This,
    /* [in] */ BSTR bstr);


void __RPC_STUB ISimpleCOM_StrComp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif

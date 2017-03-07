/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat May 29 17:17:01 1999
 */
/* Compiler settings for D:\ ÈºÆ\Œƒµµ\–¥ È\FirstATL\FirstATL.idl:
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

#ifndef __FirstATL_h__
#define __FirstATL_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IMyclass_FWD_DEFINED__
#define __IMyclass_FWD_DEFINED__
typedef interface IMyclass IMyclass;
#endif 	/* __IMyclass_FWD_DEFINED__ */


#ifndef __Myclass_FWD_DEFINED__
#define __Myclass_FWD_DEFINED__

#ifdef __cplusplus
typedef class Myclass Myclass;
#else
typedef struct Myclass Myclass;
#endif /* __cplusplus */

#endif 	/* __Myclass_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IMyclass_INTERFACE_DEFINED__
#define __IMyclass_INTERFACE_DEFINED__

/* interface IMyclass */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMyclass;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("71FCBFF2-B140-42BB-8F32-27DCF40D6FF4")
    IMyclass : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SayHello( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SayGoodbye( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyclassVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMyclass __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMyclass __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMyclass __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMyclass __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMyclass __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMyclass __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMyclass __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SayHello )( 
            IMyclass __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SayGoodbye )( 
            IMyclass __RPC_FAR * This);
        
        END_INTERFACE
    } IMyclassVtbl;

    interface IMyclass
    {
        CONST_VTBL struct IMyclassVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyclass_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMyclass_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMyclass_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMyclass_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMyclass_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMyclass_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMyclass_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMyclass_SayHello(This)	\
    (This)->lpVtbl -> SayHello(This)

#define IMyclass_SayGoodbye(This)	\
    (This)->lpVtbl -> SayGoodbye(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyclass_SayHello_Proxy( 
    IMyclass __RPC_FAR * This);


void __RPC_STUB IMyclass_SayHello_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyclass_SayGoodbye_Proxy( 
    IMyclass __RPC_FAR * This);


void __RPC_STUB IMyclass_SayGoodbye_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMyclass_INTERFACE_DEFINED__ */



#ifndef __FIRSTATLLib_LIBRARY_DEFINED__
#define __FIRSTATLLib_LIBRARY_DEFINED__

/* library FIRSTATLLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_FIRSTATLLib;

EXTERN_C const CLSID CLSID_Myclass;

#ifdef __cplusplus

class DECLSPEC_UUID("DFB658CE-CDEE-4ED7-BBBA-9F262E6B6F0F")
Myclass;
#endif
#endif /* __FIRSTATLLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif

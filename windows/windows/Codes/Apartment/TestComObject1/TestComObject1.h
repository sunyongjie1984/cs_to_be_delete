/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jan 05 16:39:23 2006
 */
/* Compiler settings for C:\Àí½âcomÌ×¼ä\code\Apartment\TestComObject1\TestComObject1.idl:
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

#ifndef __TestComObject1_h__
#define __TestComObject1_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ITestInterface1_FWD_DEFINED__
#define __ITestInterface1_FWD_DEFINED__
typedef interface ITestInterface1 ITestInterface1;
#endif 	/* __ITestInterface1_FWD_DEFINED__ */


#ifndef __TestInterface1_FWD_DEFINED__
#define __TestInterface1_FWD_DEFINED__

#ifdef __cplusplus
typedef class TestInterface1 TestInterface1;
#else
typedef struct TestInterface1 TestInterface1;
#endif /* __cplusplus */

#endif 	/* __TestInterface1_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ITestInterface1_INTERFACE_DEFINED__
#define __ITestInterface1_INTERFACE_DEFINED__

/* interface ITestInterface1 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITestInterface1;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("516FAB03-BB53-4FB9-81BA-8E3191EC398D")
    ITestInterface1 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TestFunc1( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITestInterface1Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITestInterface1 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITestInterface1 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITestInterface1 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITestInterface1 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITestInterface1 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITestInterface1 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITestInterface1 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TestFunc1 )( 
            ITestInterface1 __RPC_FAR * This);
        
        END_INTERFACE
    } ITestInterface1Vtbl;

    interface ITestInterface1
    {
        CONST_VTBL struct ITestInterface1Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITestInterface1_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITestInterface1_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITestInterface1_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITestInterface1_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITestInterface1_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITestInterface1_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITestInterface1_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITestInterface1_TestFunc1(This)	\
    (This)->lpVtbl -> TestFunc1(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITestInterface1_TestFunc1_Proxy( 
    ITestInterface1 __RPC_FAR * This);


void __RPC_STUB ITestInterface1_TestFunc1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITestInterface1_INTERFACE_DEFINED__ */



#ifndef __TESTCOMOBJECT1Lib_LIBRARY_DEFINED__
#define __TESTCOMOBJECT1Lib_LIBRARY_DEFINED__

/* library TESTCOMOBJECT1Lib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_TESTCOMOBJECT1Lib;

EXTERN_C const CLSID CLSID_TestInterface1;

#ifdef __cplusplus

class DECLSPEC_UUID("9864C676-DF91-4C1F-8E2F-3B9723CC70C4")
TestInterface1;
#endif
#endif /* __TESTCOMOBJECT1Lib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif

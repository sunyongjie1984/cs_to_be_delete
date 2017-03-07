

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Fri Nov 18 19:17:56 2011
 */
/* Compiler settings for .\DemoServer.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
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

#ifndef __DemoServer_i_h__
#define __DemoServer_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDemoDCOM_FWD_DEFINED__
#define __IDemoDCOM_FWD_DEFINED__
typedef interface IDemoDCOM IDemoDCOM;
#endif 	/* __IDemoDCOM_FWD_DEFINED__ */


#ifndef __DemoDCOM_FWD_DEFINED__
#define __DemoDCOM_FWD_DEFINED__

#ifdef __cplusplus
typedef class DemoDCOM DemoDCOM;
#else
typedef struct DemoDCOM DemoDCOM;
#endif /* __cplusplus */

#endif 	/* __DemoDCOM_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IDemoDCOM_INTERFACE_DEFINED__
#define __IDemoDCOM_INTERFACE_DEFINED__

/* interface IDemoDCOM */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IDemoDCOM;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5C0E5491-5486-4AC5-9482-98E17EB3EB16")
    IDemoDCOM : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoSomethingRemote( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDemoDCOMVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDemoDCOM * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDemoDCOM * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDemoDCOM * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDemoDCOM * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDemoDCOM * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDemoDCOM * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDemoDCOM * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DoSomethingRemote )( 
            IDemoDCOM * This);
        
        END_INTERFACE
    } IDemoDCOMVtbl;

    interface IDemoDCOM
    {
        CONST_VTBL struct IDemoDCOMVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDemoDCOM_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDemoDCOM_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDemoDCOM_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDemoDCOM_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IDemoDCOM_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IDemoDCOM_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IDemoDCOM_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IDemoDCOM_DoSomethingRemote(This)	\
    ( (This)->lpVtbl -> DoSomethingRemote(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDemoDCOM_INTERFACE_DEFINED__ */



#ifndef __DemoServerLib_LIBRARY_DEFINED__
#define __DemoServerLib_LIBRARY_DEFINED__

/* library DemoServerLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_DemoServerLib;

EXTERN_C const CLSID CLSID_DemoDCOM;

#ifdef __cplusplus

class DECLSPEC_UUID("FC774D47-E524-4C2B-9C24-91D219773707")
DemoDCOM;
#endif
#endif /* __DemoServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif



/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Feb 10 16:02:51 2006
 */
/* Compiler settings for E:\Projects\SDC\MyVCDebug\VCDEBUG\VCDebugSample\src\COM4Dbg\COM4Dbg.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_ISimpleCOM = {0x7A30E1D0,0x7CCD,0x45BD,{0x98,0xAF,0xF2,0xF9,0xE0,0xB9,0x0F,0xC7}};


const IID LIBID_COM4DBGLib = {0x3E830A6A,0x152C,0x4F67,{0x95,0x37,0x91,0xE0,0x7A,0xD5,0xEC,0x24}};


const CLSID CLSID_SimpleCOM = {0x196E4BE1,0x9321,0x4DC3,{0xBA,0xFA,0xEA,0x5B,0x1B,0xFF,0x48,0x72}};


#ifdef __cplusplus
}
#endif


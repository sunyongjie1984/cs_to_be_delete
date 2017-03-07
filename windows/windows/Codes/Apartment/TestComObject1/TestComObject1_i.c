/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jan 05 16:39:23 2006
 */
/* Compiler settings for C:\Àí½âcomÌ×¼ä\code\Apartment\TestComObject1\TestComObject1.idl:
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

const IID IID_ITestInterface1 = {0x516FAB03,0xBB53,0x4FB9,{0x81,0xBA,0x8E,0x31,0x91,0xEC,0x39,0x8D}};


const IID LIBID_TESTCOMOBJECT1Lib = {0xAA727207,0x4883,0x499E,{0xB9,0x7B,0x35,0xE3,0x62,0xD8,0xA3,0x31}};


const CLSID CLSID_TestInterface1 = {0x9864C676,0xDF91,0x4C1F,{0x8E,0x2F,0x3B,0x97,0x23,0xCC,0x70,0xC4}};


#ifdef __cplusplus
}
#endif


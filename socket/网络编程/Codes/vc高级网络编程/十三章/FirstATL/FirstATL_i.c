/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat May 29 17:17:01 1999
 */
/* Compiler settings for D:\ ÈºÆ\Œƒµµ\–¥ È\FirstATL\FirstATL.idl:
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

const IID IID_IMyclass = {0x71FCBFF2,0xB140,0x42BB,{0x8F,0x32,0x27,0xDC,0xF4,0x0D,0x6F,0xF4}};


const IID LIBID_FIRSTATLLib = {0x00169723,0x36BD,0x4972,{0xAB,0x4D,0xDE,0x7F,0xB6,0x16,0xB4,0xC7}};


const CLSID CLSID_Myclass = {0xDFB658CE,0xCDEE,0x4ED7,{0xBB,0xBA,0x9F,0x26,0x2E,0x6B,0x6F,0x0F}};


#ifdef __cplusplus
}
#endif


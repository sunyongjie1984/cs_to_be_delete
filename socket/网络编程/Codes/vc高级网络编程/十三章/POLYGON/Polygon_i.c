/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat May 29 20:06:36 1999
 */
/* Compiler settings for E:\practice\POLYGON\Polygon.idl:
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

const IID IID_IPolyCtl = {0x2885EE04,0xA26B,0x11D1,{0xB4,0x9B,0x00,0xC0,0x4F,0x98,0xEF,0xE0}};


const IID LIBID_POLYGONLib = {0x2885EDF8,0xA26B,0x11D1,{0xB4,0x9B,0x00,0xC0,0x4F,0x98,0xEF,0xE0}};


const IID DIID__IPolyCtlEvents = {0x2885EE06,0xA26B,0x11D1,{0xB4,0x9B,0x00,0xC0,0x4F,0x98,0xEF,0xE0}};


const CLSID CLSID_PolyCtl = {0x2885EE05,0xA26B,0x11D1,{0xB4,0x9B,0x00,0xC0,0x4F,0x98,0xEF,0xE0}};


const CLSID CLSID_PolyProp = {0x2885EE07,0xA26B,0x11D1,{0xB4,0x9B,0x00,0xC0,0x4F,0x98,0xEF,0xE0}};


#ifdef __cplusplus
}
#endif


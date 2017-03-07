#define VC_EXTRALEAN							 // Exclude rarely-used stuff from headers
#include <windows.h>
#include <stdio.h>
#include <conio.h>							 // getche
#include <tchar.h>
#include "psapi.h"							 // PSAPI for EnumProcesses
#include <string.h>
#include <assert.h>
#include <winuser.h>

#pragma warning(disable:4786)				 // disable annoying C4786
#include <string>								 // STL string class
#include <list>								 // STL list class
using namespace std;							 // use STL

/*=========================================================================== 
    (c) Copyright 1999, Emmanuel KARTMANN, all rights reserved                 
  =========================================================================== 
    File           : GetServiceName.h
    $Header: $
    Author         : Emmanuel KARTMANN
    Creation       : Friday 9/24/99 4:53:29 PM
    Remake         : 
  ------------------------------- Description ------------------------------- 

           Declaration of the GetServiceName function

  ------------------------------ Modifications ------------------------------ 
    $Log: $  
  =========================================================================== 
*/


#ifndef GET_SERVICE_NAME_H
#define GET_SERVICE_NAME_H

#include <afxwin.h>
#include <stdlib.h>

CString GetServiceName(LPCTSTR lpszExecutablePath);

#endif // GET_SERVICE_NAME_H


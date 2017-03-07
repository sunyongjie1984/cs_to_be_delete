// Myclass.cpp : Implementation of CMyclass
#include "stdafx.h"
#include "FirstATL.h"
#include "Myclass.h"

/////////////////////////////////////////////////////////////////////////////
// CMyclass


STDMETHODIMP CMyclass::SayHello()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	AfxMessageBox("Welcom to use my class");

	return S_OK;
}

STDMETHODIMP CMyclass::SayGoodbye()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return S_OK;
}

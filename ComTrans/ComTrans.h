// ComTrans.h : main header file for the COMTRANS application
//

#if !defined(AFX_COMTRANS_H__9EE3ACAC_097A_4393_8FFF_85FEE66847C0__INCLUDED_)
#define AFX_COMTRANS_H__9EE3ACAC_097A_4393_8FFF_85FEE66847C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CComTransApp:
// See ComTrans.cpp for the implementation of this class
//

class CComTransApp : public CWinApp
{
public:
	CComTransApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComTransApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CComTransApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMTRANS_H__9EE3ACAC_097A_4393_8FFF_85FEE66847C0__INCLUDED_)

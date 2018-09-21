#if !defined(AFX_MYCOM_H__F2A6BD03_A158_4829_8AEF_A405A7382675__INCLUDED_)
#define AFX_MYCOM_H__F2A6BD03_A158_4829_8AEF_A405A7382675__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyCom.h : header file
//
#include "Pcomm.h" 

/////////////////////////////////////////////////////////////////////////////
// CMyCom window

class CMyCom : public CWnd
{
// Construction
public:
	CMyCom();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCom)
	//}}AFX_VIRTUAL

// Implementation
public:
	long ReadComData(char* buf, int length);
	void WriteComData(char* buf, int length);
	long GetComInLength();
	void FlushComBuffer(int n);
	void ColseCom(void);
	int InitCom();
	virtual ~CMyCom();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyCom)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCOM_H__F2A6BD03_A158_4829_8AEF_A405A7382675__INCLUDED_)

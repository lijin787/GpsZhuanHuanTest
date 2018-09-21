#if !defined(AFX_SETDLG_H__B4EE041F_1EF8_4D84_AA98_93D886EF3E8C__INCLUDED_)
#define AFX_SETDLG_H__B4EE041F_1EF8_4D84_AA98_93D886EF3E8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetDlg dialog

class CSetDlg : public CDialog
{
// Construction
public:
	CSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetDlg)
	enum { IDD = IDD_DIALOG1 };
	UINT	m_nK0;
	UINT	m_nK1;
	UINT	m_nK2;
	UINT	m_nK3;
	UINT	m_nK4;
	UINT	m_nK5;
	UINT	m_nK6;
	UINT	m_nK7;
	UINT	m_nK8;
	UINT	m_nK9;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETDLG_H__B4EE041F_1EF8_4D84_AA98_93D886EF3E8C__INCLUDED_)

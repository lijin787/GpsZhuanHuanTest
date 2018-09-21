// SetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ComTrans.h"
#include "SetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetDlg dialog


CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetDlg)
	m_nK0 = 0;
	m_nK1 = 0;
	m_nK2 = 0;
	m_nK3 = 0;
	m_nK4 = 0;
	m_nK5 = 0;
	m_nK6 = 0;
	m_nK7 = 0;
	m_nK8 = 0;
	m_nK9 = 0;
	//}}AFX_DATA_INIT
}


void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetDlg)
	DDX_Text(pDX, IDC_EDIT_K0, m_nK0);
	DDX_Text(pDX, IDC_EDIT_K1, m_nK1);
	DDX_Text(pDX, IDC_EDIT_K2, m_nK2);
	DDX_Text(pDX, IDC_EDIT_K3, m_nK3);
	DDX_Text(pDX, IDC_EDIT_K4, m_nK4);
	DDX_Text(pDX, IDC_EDIT_K5, m_nK5);
	DDX_Text(pDX, IDC_EDIT_K6, m_nK6);
	DDX_Text(pDX, IDC_EDIT_K7, m_nK7);
	DDX_Text(pDX, IDC_EDIT_K8, m_nK8);
	DDX_Text(pDX, IDC_EDIT_K9, m_nK9);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialog)
	//{{AFX_MSG_MAP(CSetDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetDlg message handlers

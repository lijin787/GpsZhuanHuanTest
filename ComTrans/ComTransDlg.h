// ComTransDlg.h : header file
//
//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES

#if !defined(AFX_COMTRANSDLG_H__1B860FCF_C5D0_428A_A9ED_836A32879AA1__INCLUDED_)
#define AFX_COMTRANSDLG_H__1B860FCF_C5D0_428A_A9ED_836A32879AA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyCom.h"


/////////////////////////////////////////////////////////////////////////////
// CComTransDlg dialog
#define PI 3.14159265
class CComTransDlg : public CDialog
{
// Construction
public:

	double m_dbFY;
	double m_dbPH;

	FILE *fp;
	BOOL m_bSaveFlag;
	double m_MBJL,m_lastMBJL;
	double m_JXSD;
	void dxToDl(double jd,double wd,double &x,double &y,double &z);
	void gpsTo84(double jd,double wd,double hh,double &px,double &py,double &pz);
	double m_MBGD,m_lastMBGD;
	double m_MBWD,m_lastMBWD;
	double m_MBJD,m_lastMBJD;
	double m_Time,m_lastTime,deltaTime;
	unsigned int m_nErrCount0,m_nErrCount1,m_nErrCount2,m_nErrCount3;
	double m_MBSD;
	double m_MBHX;
	int m_iWXCount;
	CComTransDlg(CWnd* pParent = NULL);	// standard constructor

	BOOL m_bThreadAlive;
	CMyCom m_Com;
	CWinThread* m_pThread;
	static UINT	CommThread(LPVOID pParam);
// Dialog Data
	//{{AFX_DATA(CComTransDlg)
	enum { IDD = IDD_COMTRANS_DIALOG };
	CMSComm	m_ctrlCom1;
	CMSComm	m_ctrlCom2;
	CString	m_strDDFY;
	CString	m_strDDGD;
	CString	m_strDDGZ;
	CString	m_strDDJD;
	CString	m_strDDPH;
	CString	m_strDDWD;
	CString	m_strDIS;
	CString	m_strMBFY;
	CString	m_strMBGD;
	CString	m_strMBJD;
	CString	m_strMBPH;
	CString	m_strMBWD;
	CString	m_strWX1;
	CString	m_strWX2;
	CString	m_strSudu;
	CString	m_strHX;
	CString	m_strStatic1;
	CString	m_strStatic2;
	double	m_dbDeltaFY;
	double	m_dbDeltaPH;
	CString m_strGPSTime;
	CString	m_strJXSD;
	CString	m_strSXSD;
	CString	m_strVX;
	CString	m_strVY;
	CString	m_strVZ;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComTransDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	double m_dbVX;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CComTransDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnOnCommMscomm1();
	virtual void OnOK();
	afx_msg void OnBtnSave();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtnAddfy();
	afx_msg void OnBtnAddph();
	afx_msg void OnBtnSubfy();
	afx_msg void OnBtnSubph();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	double deltaPH;
	double deltaFY;
	double m_dbTemp;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMTRANSDLG_H__1B860FCF_C5D0_428A_A9ED_836A32879AA1__INCLUDED_)

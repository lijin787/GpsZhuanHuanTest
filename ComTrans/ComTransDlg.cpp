// ComTransDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ComTrans.h"
#include "ComTransDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
//ȫ�ֱ��������ڴ������ݺͼ��㷽��
CByteArray hexData;
double g_DDJD,g_DDWD,g_DDGD,g_DDFY,g_DDPH,g_DDGZ;	//�������ȡ�γ�ȡ��߶ȡ�������ƫ������ת
double g_DDVX,g_DDVY,g_DDVZ;						//��ȡ�߲�����������ٶȣ����ڼ��㵼���������ٶ�
unsigned int g_iWXCount;							//��ϵ����յ���gps������
BOOL g_dataFlag = FALSE;							//����Ŀ��GPS���ǿ�����������ʾ�Ƿ�λ
BOOL m_bDataFlag;
UINT nIdEvent;

CRITICAL_SECTION g_csCP;
CRITICAL_SECTION g_csCP2;							//��Ʒ�ؼ�����α�ʾ
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComTransDlg dialog

CComTransDlg::CComTransDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComTransDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CComTransDlg)
	m_strDDFY = _T("");
	m_strDDGD = _T("");
	m_strDDGZ = _T("");
	m_strDDJD = _T("");
	m_strDDPH = _T("");
	m_strDDWD = _T("");
	m_strDIS = _T("");
	m_strMBFY = _T("");
	m_strMBGD = _T("");
	m_strMBJD = _T("");
	m_strMBPH = _T("");
	m_strMBWD = _T("");
	m_strWX1 = _T("");
	m_strWX2 = _T("");
	m_strSudu = _T("");
	m_strHX = _T("");
	m_strStatic1 = _T("");
	m_strStatic2 = _T("");
	m_dbDeltaFY = 0.0;
	m_dbDeltaPH = 0.0;
	m_strGPSTime= _T("");
	m_strJXSD = _T("");
	m_strSXSD = _T("");
	m_strVX = _T("");
	m_strVY = _T("");
	m_strVZ = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComTransDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComTransDlg)
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlCom1);
	DDX_Control(pDX, IDC_MSCOMM2, m_ctrlCom2);
	DDX_Text(pDX, IDC_STATIC_DDFY, m_strDDFY);
	DDX_Text(pDX, IDC_STATIC_DDGD, m_strDDGD);
	DDX_Text(pDX, IDC_STATIC_DDGZ, m_strDDGZ);
	DDX_Text(pDX, IDC_STATIC_DDJD, m_strDDJD);
	DDX_Text(pDX, IDC_STATIC_DDPH, m_strDDPH);
	DDX_Text(pDX, IDC_STATIC_DDWD, m_strDDWD);
	DDX_Text(pDX, IDC_STATIC_DIS, m_strDIS);
	DDX_Text(pDX, IDC_STATIC_MBFY, m_strMBFY);
	DDX_Text(pDX, IDC_STATIC_MBGD, m_strMBGD);
	DDX_Text(pDX, IDC_STATIC_MBJD, m_strMBJD);
	DDX_Text(pDX, IDC_STATIC_MBPH, m_strMBPH);
	DDX_Text(pDX, IDC_STATIC_MBWD, m_strMBWD);
	DDX_Text(pDX, IDC_STATIC_WX1, m_strWX1);
	DDX_Text(pDX, IDC_STATIC_WX2, m_strWX2);
	DDX_Text(pDX, IDC_STATIC_SUDU, m_strSudu);
	DDX_Text(pDX, IDC_STATIC_HX, m_strHX);
	DDX_Text(pDX, IDC_STATIC_GPSSTATE1, m_strStatic1);
	DDX_Text(pDX, IDC_STATIC_GPASTATE2, m_strStatic2);
	DDX_Text(pDX, IDC_EDIT_FY, m_dbDeltaFY);
	DDX_Text(pDX, IDC_EDIT_PH, m_dbDeltaPH);
	DDX_Text(pDX, IDC_STATIC_GPSTIME, m_strGPSTime);
	DDX_Text(pDX, IDC_STATIC_JXSD, m_strJXSD);
	DDX_Text(pDX, IDC_STATIC_SXSD, m_strSXSD);
	DDX_Text(pDX, IDC_STATIC_VX, m_strVX);
	DDX_Text(pDX, IDC_STATIC_VY, m_strVY);
	DDX_Text(pDX, IDC_STATIC_VZ, m_strVZ);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CComTransDlg, CDialog)
	//{{AFX_MSG_MAP(CComTransDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_ADDFY, OnBtnAddfy)
	ON_BN_CLICKED(IDC_BTN_ADDPH, OnBtnAddph)
	ON_BN_CLICKED(IDC_BTN_SUBFY, OnBtnSubfy)
	ON_BN_CLICKED(IDC_BTN_SUBPH, OnBtnSubph)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComTransDlg message handlers

BOOL CComTransDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_iWXCount = 0;
	m_bDataFlag = FALSE;
	m_MBHX = 0.0;
	m_dbFY = m_dbPH = 0.0;
	m_lastMBJL = m_MBJL = 0.0;
	m_lastMBJD = m_MBJD = m_lastMBWD = m_MBWD = m_lastMBGD = m_MBGD = m_MBSD = 0.0;
	m_Time = m_lastTime = 0.0;
	deltaFY = deltaPH = 0.0;
	m_JXSD = 0.0;
	m_dbVX =0.0;
	CTime curtime;
	CString logdir;

	g_DDJD=g_DDWD=g_DDGD=g_DDFY=g_DDPH=g_DDGZ=0;
	hexData.SetSize(76);
	hexData[63] = 0xc3;
	hexData[64] = 0xf8;
	InitializeCriticalSection(&g_csCP);
	InitializeCriticalSection(&g_csCP2);

	DWORD dwAttr = GetFileAttributes("d:\\��ϵ��������ļ�");
	if (dwAttr == -1)	//�ļ��в�����
	{
		CreateDirectory("d:\\��ϵ��������ļ�",NULL);
	}
	curtime = CTime::GetCurrentTime();
	logdir.Format("%d��%d��%d��%dʱ%d��%d��",(int)curtime.GetYear(),(int)curtime.GetMonth(),(int)curtime.GetDay(),(int)curtime.GetHour(),(int)curtime.GetMinute(),(int)curtime.GetSecond());
	logdir = "d:\\��ϵ��������ļ�\\"+logdir+".txt";
	m_bSaveFlag = FALSE;
	fp = fopen(logdir,"w");
	fprintf(fp,"%s\t	%s	%s	%s	%s	%s	%s	%s	%s	%s	%s	%s	%s  %s %s\n",
		"ʱ    ��","�ػ�  ����","�ػ� γ��","�ػ� �߶�","  �ػ� ƫ��","�ػ� ����","�ػ� ��ת","Ŀ�� ����",
		" Ŀ�� γ��","Ŀ�� �߶�","Ŀ�꺽��","Ŀ���ٶ�","��Ծ���","����ƫ��","���ḩ��");

	int nstaus=m_Com.InitCom();//��ʼ��422	
	if(nstaus<0)
		AfxMessageBox("422ͨѶ�˿��쳣");

	m_bThreadAlive=TRUE;
	m_pThread=AfxBeginThread(CommThread,this,THREAD_PRIORITY_HIGHEST);
	SetThreadAffinityMask(m_pThread->m_hThread, 2);			//������߳���CPU2������

	m_ctrlCom1.SetCommPort(3);
	if (!m_ctrlCom1.GetPortOpen())
	{
		m_ctrlCom1.SetPortOpen(TRUE);
	}
	else
		AfxMessageBox("Can not open com4");

	m_ctrlCom2.SetCommPort(4);
	if(!m_ctrlCom2.GetPortOpen())
		m_ctrlCom2.SetPortOpen(TRUE);
	else
		AfxMessageBox("Can not open com5");
//	m_ctrlCom2.SetInputMode(1);
//	m_ctrlCom2.SetSThreshold(1);
//	m_ctrlCom2.SetInputLen(0);					//0 ��ʾ���ջ������е��������ݣ����shi������������ض��ĸ���
//	m_ctrlCom2.GetInput();						//clear input buffer
	
	nIdEvent = SetTimer(1,100,NULL);
	if (nIdEvent == 0) 
	{
		AfxMessageBox("Create Timer error!");
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CComTransDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CComTransDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CComTransDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


UINT CComTransDlg::CommThread(LPVOID pParam)  //COMM�����߳�
{
	CComTransDlg* pT=(CComTransDlg*) pParam;

	LARGE_INTEGER NowFreq;
	LARGE_INTEGER NowTicket,BeginTick;
	UINT NeedTick;
	
	double m_fFTD=60.0;
	long iLen=0;
	char nRxBuf[4096];
	BYTE ndata[4096];
//	BYTE realData[63];
	int nRealData=0;
	int i,j;
	BYTE nCheckSum;
	unsigned int temp;


	
	QueryPerformanceFrequency(&NowFreq);
	NeedTick = UINT(m_fFTD/1000.0*NowFreq.QuadPart);
	QueryPerformanceCounter(&BeginTick);
	
	while(pT->m_bThreadAlive)
	{
		QueryPerformanceCounter(&NowTicket);  //��ʱ		
		if((NowTicket.QuadPart - BeginTick.QuadPart)<NeedTick)
			continue;				
		QueryPerformanceCounter(&BeginTick);
		nRealData++;

		iLen=pT->m_Com.GetComInLength();
		if(iLen>0)
		{
			pT->m_Com.ReadComData(nRxBuf, iLen);
			memcpy(ndata, nRxBuf, iLen);
			
			///////////////////////����
			for(i=0;i<iLen;i++)
			{
				if(ndata[i] == 0xc3 && ndata[i+1] == 0xf1)		//Ѱ��֡ͷ.
				{
					EnterCriticalSection(&g_csCP);

					nCheckSum = 0;

					for(j=0;j<8;j++)
					{
						nCheckSum += ndata[i+j];				//��������֡��У���
					}

					if(ndata[i+8] != nCheckSum)
						break;									//�����ϴ˴�Ӧ��continue,������һ����Ϣ�����ٶȺ������˴����Ժ��Բ�����Ϣ��
					else
					{
						//����gaodu����
						temp = ((ndata[i+5]&0x0007)<<8) + (ndata[i+4]&0x00ff);
						g_DDGD = temp * 5000.0/4096.0;
						//����x������ٶ�
						temp = ((ndata[i+7]&0x0007)<<8) + (ndata[i+6]&0x00ff);
						if ((ndata[i+7]&0x08)>>3)
						{
							//g_DDVX = -((~temp+1)*0.048828125);
							g_DDVX = temp * 0.048828125 - 100.0;						//100/2048//��ֵ�ǲ��룬����ֱ������
						}
						else
						{
							g_DDVX = temp * 0.048828125;
						}
						
					}
							

					nCheckSum = 0;
					for(j=9;j<17;j++)
					{
						nCheckSum += ndata[i+j];
					}
								
					if(ndata[i+17] != nCheckSum)
						break;
					else
					{
						//��zitai����
						temp = ((ndata[i+12]&0x000007)<<8) + (ndata[i+11]&0x0000ff);
						if((ndata[i+12]&0x08)>>3)
							//g_DDFY = -((~temp+1) * 180.0/2048);				//�����ò����ʾ��
							g_DDFY = temp*180.0/2048 - 180.0;					//2017.10.18��������Ϊ����ظ������޸�
						else													//ԭ����int����ռ32λ������ȡ����һʱ��λ
							g_DDFY = temp * 180.0/2048;							//��Ϊ1111�����Խ������������������Ľ��
																				//����Ϊ������0x1000��ȥ�յ����ڽ������˴�
																				//ֱ�ӽ������ȥ180��Ҳ���С�
						temp = ((ndata[i+14]&0x000007)<<8) + (ndata[i+13]&0x0000ff);
						if((ndata[i+14]&0x08)>>3)
							//g_DDPH = -((~temp+1) * 180.0/2048);
							g_DDPH = temp*180.0/2048 - 180.0;
						else
							g_DDPH = temp * 180.0/2048;
	

						temp = ((ndata[i+16]&0x000007)<<8) + (ndata[i+15]&0x0000ff);
						if((ndata[i+16]&0x08)>>3)
							//g_DDGZ = -((~temp+1) * 180.0/2048);
							g_DDGZ = temp*180.0/2048 - 180.0;
						else
							g_DDGZ = temp * 180.0/2048;		

					}
					nCheckSum = 0;
					for(j=27;j<35;j++)
						nCheckSum += ndata[i+j];
					if (ndata[i+35] != nCheckSum)
					{
						break;
					}
					else
					{
						g_iWXCount = (ndata[i+29]&0x7c)>>2;
					}
				
					nCheckSum = 0;
					for(j=36;j<44;j++)
						nCheckSum += ndata[i+j];
					if(ndata[i+44] != nCheckSum)
						break;
					else
					{
						//����weidu����
						temp = ((ndata[i+41]&0x0000007f)<<24) + ((ndata[i+40]&0x000000ff)<<16) + ((ndata[i+39]&0x000000ff)<<8) + (ndata[i+38]&0x000000ff);
						if((ndata[i+41]&0x80)>>7)
							g_DDWD = 0 - (temp * 2.0/2147483648.0);				//������Ϊ2rad,��γ�ȸ�������û�б䣬��Ϊ�����и�������֤����
						else
							g_DDWD = temp * 2.0/2147483648.0;

						//����y������ٶ�
						temp = ((ndata[i+43]&0x0007)<<8) + (ndata[i+42]&0x00ff);
						if ((ndata[i+43]&0x08)>>3)
						{
							//g_DDVY = -((~temp+1)*0.048828125);
							g_DDVY = temp * 0.048828125 - 100.0;						//100/2048
						}
						else
						{
							g_DDVY = temp * 0.048828125;
						}
					}
						
					nCheckSum = 0;
					for(j=45;j<53;j++)
						nCheckSum += ndata[i+j];
					if(ndata[i+53] != nCheckSum)
						break;
					else
					{
						//����jingdu����
						temp = ((ndata[i+50]&0x0000007f)<<24) + ((ndata[i+49]&0x000000ff)<<16) + ((ndata[i+48]&0x000000ff)<<8) + (ndata[i+47]&0x000000ff);
						if((ndata[i+50]&0x80)>>7)
							g_DDJD = 0 - (temp * 4.0/2147483648.0);				//������Ϊ4rad
						else
							g_DDJD = temp * 4.0/2147483648.0;

						//����z������ٶ�
						temp = ((ndata[i+52]&0x0007)<<8) + (ndata[i+51]&0x00ff);
						if ((ndata[i+52]&0x08)>>3)
						{
							//g_DDVZ = -((~temp+1)*0.048828125);
							g_DDVZ = temp * 0.048828125 - 100.0;						//100/2048
						}
						else
						{
							g_DDVZ = temp * 0.048828125;
						}
					}
					g_DDFY = g_DDFY/180*PI;
					g_DDPH = g_DDPH/180*PI;
					g_DDGZ = g_DDGZ/180*PI;
					if (g_iWXCount > 3) 
					{
						g_dataFlag = TRUE;
					}
					else
					{
						g_dataFlag = FALSE;
					}
					//Ϊ�˽��յ������ݴӴ���ԭ���������˴�������ʹ�õ�����ԭ�������������λ��
					for(int k=0;k<63;k++)
						hexData[k] = ndata[i+k];
					///////////////////////////////////////////////////////////////////////
					LeaveCriticalSection(&g_csCP);
			
					break;
				}

			}	


			
		}//////////////////////*/
		/*
		EnterCriticalSection(&g_csCP);
				g_DDJD =112.43/180.0*PI;
				//g_DDWD = nRealData;
				g_iWXCount = nRealData;
				g_DDGD = 0.0;
				g_DDFY = 0.0/180.0*PI;
				g_DDPH = 0.0/180.0*PI;
				g_DDGZ = 0.0/180.0*PI;
				//g_iWXCount = 5;
				g_dataFlag = TRUE;
				LeaveCriticalSection(&g_csCP);*/
		
		
	}


	return 0;
}

void CComTransDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	//�߳�ǿ����ֹ
	TerminateThread(m_pThread->m_hThread, 100);
	
	delete m_pThread;
	m_pThread=NULL;
	m_Com.ColseCom();

	fclose(fp);

	CDialog::OnClose();
}

BEGIN_EVENTSINK_MAP(CComTransDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CComTransDlg)
	ON_EVENT(CComTransDlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CComTransDlg::OnOnCommMscomm1() 
{
	// TODO: Add your control notification handler code here
	//���յ���̨���ݺ���н��������������Ч���м��㲢���������̨��
	COleSafeArray safeArray;
	COleVariant variant;
	long iLen;
	long i,iTemp;
	CString strTime;
	CString strSub;
	double tempFloat;
	unsigned char nRxByte[4096];
	unsigned char nCheckSum=0;

	double ddx,ddy,ddz,mbx,mby,mbz,xdx,xdy,xdz;		//������Ŀ�ꡢ���x,y,z
	double x0,y0,z0;								//���������������������ȡ�����ٶ������ߵ�ͶӰ
	ddx = ddy = ddz = mbx = mby = mbz = xdx = xdy = xdz = 0;
	double dbTemp;
	double vxTemp,vyTemp,vzTemp;					//�����ػ������ٶȵ��м����

	if(2 == m_ctrlCom1.GetCommEvent())
	{
		Sleep(3);
		variant=m_ctrlCom1.GetInput();
		safeArray = variant;
		iLen = safeArray.GetOneDimSize();
		for(i=0;i<iLen;i++)
			safeArray.GetElement(&i,nRxByte+i);
				//������̨������
		
		for(i=0;i<iLen;i++)
			{
				if (nRxByte[i] == 'G' && nRxByte[i+1] == 'P' && nRxByte[i+2] == 'G' && nRxByte[i+3] == 'G' && nRxByte[i+4] == 'A')
				{
					EnterCriticalSection(&g_csCP2);
					CString strTemp(nRxByte+i);

					AfxExtractSubString(strSub,(LPCTSTR)strTemp,1,',');
					//tempBuf = (char*)&nRxByte[i+7];			//ʱ�俪ʼ
					m_Time = atof(strSub.GetBuffer(16))+80000.0;
					deltaTime = m_Time - m_lastTime;

					//ʱ���޳�Ұ��
					if (fabs(deltaTime) > 5)				//ʱ���ȴ���5s��Ϊ��������
					{
						if (m_nErrCount0 < 5)				//�������С��5�Σ���Ϊ������Ұ��,��ʼ״̬�϶����
						{
							m_Time = m_lastTime;
							m_nErrCount0++;								//������֡������һ����������5ʱ��Ϊ��ֵ���ܴ���
						}
						else								//����5�κ󽫴�������Ϊ��ǰֵ���´ξͲ����ٴ�
							m_lastTime = m_Time;
						deltaTime = 9999.0;					//��������½����ʱ���Ϊ���������
					}
					else
					{
						m_nErrCount0 = 0;
						m_lastTime = m_Time;
					}
					strTime.Format("%6.2f",m_Time);
					m_strGPSTime=strTime;

					//tempBuf = (char*)&nRxByte[i+17];			//γ�ȿ�ʼ
					AfxExtractSubString(strSub,(LPCTSTR)strTemp,2,',');
					m_MBWD = atof(strSub.GetBuffer(16));
					iTemp = ((int)m_MBWD)/100;
					tempFloat = (m_MBWD - iTemp*100)/60;
					m_MBWD = iTemp + tempFloat;
					//�޳�Ұ�㴦�������ֵ����һֵ֡��𳬹���ֵ����Ϊ���ݴ��þ�ֵ������ֵ�����������ֹ�洢�ĵ�һ��ֵ���󣬸���������
					if (fabs(m_MBWD-m_lastMBWD) > 0.01)				//Ŀ���ٶȲ������500m/s������100ms�仯������50m����Ӧ0.00045��
					{
						if (m_nErrCount1 < 5) 
						{
							m_MBWD = m_lastMBWD;
							m_nErrCount1++;								//������֡������һ����������5ʱ��Ϊ��ֵ���ܴ���
						}
						else
							m_lastMBWD = m_MBWD;
					}
					else
					{
						m_nErrCount1 = 0;
						m_lastMBWD = m_MBWD;
					}
					//����ת��Ϊ����
					m_MBWD = m_MBWD*PI/180;

					//tempBuf = (char*)&nRxByte[i+33];			//���ȿ�ʼ
					AfxExtractSubString(strSub,(LPCTSTR)strTemp,4,',');
					m_MBJD = atof(strSub.GetBuffer(16));
					iTemp = ((int)m_MBJD)/100;
					tempFloat = (m_MBJD - iTemp*100)/60;
					m_MBJD = iTemp + tempFloat;

					if (fabs(m_MBJD-m_lastMBJD) > 0.01)				//Ŀ���ٶȲ������500m/s������100ms�仯������50m����Ӧ0.00045��
					{
						if (m_nErrCount2 < 5) 
						{
							m_MBJD = m_lastMBJD;
							m_nErrCount2++;								//������֡������һ����������5ʱ��Ϊ��ֵ���ܴ���
						}
						else
							m_lastMBJD = m_MBJD;
					}
					else
					{
						m_nErrCount2 = 0;
						m_lastMBJD = m_MBJD;
					}
					m_MBJD = m_MBJD*PI/180;
					//tempBuf = (char*)&nRxByte[i+52];			//������
					AfxExtractSubString(strSub,(LPCTSTR)strTemp,7,',');
					m_iWXCount = atoi(strSub.GetBuffer(16));
					if (m_iWXCount > 3)
					{
						m_bDataFlag = TRUE;
					}
					else
					{
						m_bDataFlag = FALSE;
					}
					//tempBuf = (char*)&nRxByte[i+59];			//���θ߶�
					AfxExtractSubString(strSub,(LPCTSTR)strTemp,9,',');
					m_MBGD = atof(strSub.GetBuffer(16));
					if (fabs(m_MBGD-m_lastMBGD) > 100)				//Ŀ���ٶȲ������500m/s������100ms�仯������50m
					{
						if (m_nErrCount3 < 5) 
						{
							m_MBGD = m_lastMBGD;
							m_nErrCount3++;								//������֡������һ����������5ʱ��Ϊ��ֵ���ܴ���
						}
						else
							m_lastMBGD = m_MBGD;
					}
					else
					{
						m_nErrCount3 = 0;
						m_lastMBGD = m_MBGD;
					}
					//tempBuf = (char*)&nRxByte[i+90];			//�汱����
					AfxExtractSubString(strSub,(LPCTSTR)strTemp,15,',');
					m_MBHX = atof(strSub.GetBuffer(16));
					//tempBuf = (char*)&nRxByte[i+108];			//�ٶ�km/h
					AfxExtractSubString(strSub,(LPCTSTR)strTemp,21,',');
					m_MBSD = atof(strSub.GetBuffer(16))*1000.0/3600.0;	//��λ��Ϊm/s
					LeaveCriticalSection(&g_csCP2);
					break;
				}
			}
	
				

		/*///////////////
		AfxExtractSubString(CString& rString,LPCTSTR lpszFullString,int iSubString,TCHAR chSep ='\n')
		
		///////////////*/
//		strTime = "0:0:0";
//		m_MBJD = 114.5/180.0*PI;
//		m_MBWD = 34.5/180.0*PI;
//		m_MBGD = 0.0 + count;		//����ֵ�����ڵ��Գ���

		// ����ؼ�����Σ�ע���߳�ͬ��
		EnterCriticalSection(&g_csCP);
		EnterCriticalSection(&g_csCP2);

		gpsTo84(g_DDJD,g_DDWD,g_DDGD,ddx,ddy,ddz);
		
		//���Ӳ��ԣ�Ŀ�꺣�θ߶��뵯��߶�һ��
		//m_MBGD=g_DDGD;

		gpsTo84(m_MBJD,m_MBWD,m_MBGD,mbx,mby,mbz);
		//����ϵ�µ��������
		xdx = mbx-ddx;
		xdy = mby-ddy;
		xdz = mbz-ddz;
		
		//���˵õ���������ֵ,Ȼ��ת����������λ�õĵ���ϵ
		//***************************************************
		//���Ǵ˴����ת�����ߵ����ԭ������λ�õĵ�������ϵ�����������
		//�ߵ������õĸ�����ƫ������ת���������ǰ״̬���ԭ��λ�õĵ�������ϵ�����춫����ֵ
		//�˴�ֻ��Ҫ�滻���溯���е�g_DDJD,g_DDWDΪ�ߵ����ԭ��ľ��Ⱥ�γ�ȼ���,�����ֳ���ԭ��ֵδ֪��δ����
		//******************************************************
		dxToDl(g_DDJD,g_DDWD,xdx,xdy,xdz);
		x0 = xdx;y0=xdy;z0=xdz;					//��������õ��ľ���������

		m_MBJL = sqrt(x0*x0 + y0*y0 + z0*z0);
		if (deltaTime < 0.0001)		//��ֹ�����������
		{
			m_JXSD = 99999.9;						//�޵�������ݣ��������ԵĴ���
		}
		else
		{
			m_JXSD = (m_MBJL-m_lastMBJL)/deltaTime;		//�����ٶ�����Ծ����΢�֣���Ҫ��֤
		}
		m_lastMBJL = m_MBJL;
	
		/*
		//����ƫ��
		ddx = xdx*cos(g_DDPH)-xdz*sin(g_DDPH);
		ddy = xdy;
		ddz = xdx*sin(g_DDPH)+xdz*cos(g_DDPH);
		//������ת
		mbx = ddx;
		mby = ddy*cos(g_DDGZ)+ddz*sin(g_DDGZ);
		mbz = -ddy*sin(g_DDGZ)+ddz*cos(g_DDGZ);
		//��������
		xdx = mbx*cos(g_DDFY)+mby*sin(g_DDFY);
		xdy = -mbx*sin(g_DDFY)+mby*cos(g_DDFY);
		xdz = mbz;
		*/
		//���½�����ϵת�����߲��齨ָ���ĵ���ϵ
		//�任˳���Ϊƫ����������������任˳���������ֱ����أ����뱣֤����˳����߲����һ��20170920��������ȷ��
		//����ƫ��
		ddx = xdx*cos(g_DDPH)-xdz*sin(g_DDPH);
		ddy = xdy;
		ddz = xdx*sin(g_DDPH)+xdz*cos(g_DDPH);
		//��������
		mbx = ddx*cos(g_DDFY)+ddy*sin(g_DDFY);
		mby = -ddx*sin(g_DDFY)+ddy*cos(g_DDFY);
		mbz = ddz;
		//������ת
		xdx = mbx;
		xdy = mby*cos(g_DDGZ)+mbz*sin(g_DDGZ);
		xdz = -mby*sin(g_DDGZ)+mbz*cos(g_DDGZ);

		//�����õ�Ŀ���ڵ������嵼��ϵ�µ�λ��
		
		//�Ӵ˴���ʼ���㵯��ϵ�µ�ƫ���͸����������͸�FKT	20160922
		//������ƫ�����Ѿ�����90��
		//�����Ǹ������Ѿ�����90��
		m_dbPH = asin(xdz/sqrt(xdx*xdx+xdz*xdz));					//ƫ����Ϊ��
		m_dbFY = asin(xdy/sqrt(xdx*xdx+xdy*xdy+xdz*xdz));			//������Ϊ��

		//����һ���ֶ������·��ĸ�����ƫ���Ĵ��룬����Ӧ��ʹ�á�
		m_dbPH += deltaPH*(PI/180.0);
		m_dbFY += deltaFY*(PI/180.0);
		//////////////////////////////////////////////////////

		//���ƫ��
		if (m_dbPH>=0)
		{
			iTemp = (long)(m_dbPH*(180/PI)/0.0439453125);
			hexData[65] = iTemp&0x00ff;
			hexData[66] = (iTemp&0x000700)>>8;
		}
		else
		{
			dbTemp = -m_dbPH;
			iTemp = (long)(dbTemp*(180/PI)/0.0439453125);
			iTemp = ~iTemp+1;										//��ֵ�ò����ʾ
			hexData[65] = iTemp&0x00ff;
			hexData[66] = ((iTemp&0x000700)>>8) | 0x08;
		}
		//�������
		if (m_dbFY>=0)
		{
			iTemp = (long)(m_dbFY*(180/PI)/0.0439453125);
			hexData[67] = iTemp&0x00ff;
			hexData[68] = (iTemp&0x000700)>>8;
		}
		else
		{
			dbTemp = -m_dbFY;
			iTemp = (long)(dbTemp*(180/PI)/0.0439453125);
			iTemp = ~iTemp+1;
			hexData[67] = iTemp&0x00ff;
			hexData[68] = ((iTemp&0x000700)>>8) | 0x08;
		}
		//�������,��16λ����,�޷��ţ����ֵ32km����������λΪ32000/(2^16-1)=0.4882887m,�ò���һ����0.48828125
		iTemp = (long)(m_MBJL/0.48828125);
		hexData[69] = iTemp&0x00ff;
		hexData[70] = (iTemp&0x0ff00)>>8 | 0xff;
		//��������ٶ�,��16λ���ݣ����λΪ����λ��0��1�������ֵ500m/s����������λΪ500/(2^15-1)=0.015259255,�ò���һ����0.0152587890625
		if (m_JXSD>=0)
		{
			iTemp = (long)(m_JXSD/0.0152587890625);
			hexData[71] = iTemp & 0x00ff;
			hexData[72] = (iTemp&0x007f00)>>8;
		}
		else
		{
			dbTemp = -m_JXSD;
			iTemp = (long)(m_JXSD/0.0152587890625);
			iTemp = ~iTemp+1;
			hexData[71] = iTemp & 0x00ff;
			hexData[72] = (iTemp&0x007f00)>>8 | 0x80;
		}
		//��������ٶ��ڵ�Ŀ���߷����ͶӰ,�߲��������ı��춫�µ��ٶ�ͶӰ�������ϡ�
		//����Ϊ�����ٶȳ��Ը�������ٳ���б�࣬Ȼ����ӡ�
		//�������
		vxTemp = g_DDVX*x0/m_MBJL;
		vyTemp = g_DDVY*y0/m_MBJL;
		vzTemp = g_DDVZ*z0/m_MBJL;
		//���
		m_dbVX = vxTemp+vyTemp+vzTemp;

		if (m_dbVX>=0)
		{
			iTemp = (long)(m_dbVX/0.0152587890625);
			hexData[73] = iTemp & 0x00ff;
			hexData[74] = (iTemp&0x007f00)>>8;
		}
		else
		{
			dbTemp = -m_dbVX;
			iTemp = (long)(m_dbVX/0.0152587890625);
			iTemp = ~iTemp+1;
			hexData[73] = iTemp & 0x00ff;
			hexData[74] = (iTemp&0x007f00)>>8 | 0x80;
		}
		
			for(i=0;i<12;i++)
				hexData[75] += hexData[63+i];
			//�ж�����GPS������������3�ٴ����ݣ���֤��������
			if (g_dataFlag && m_bDataFlag)
			{
				m_ctrlCom2.SetOutput(COleVariant(hexData));	
			}
			else
			{
				//do nothing
			}
			
	
		//��¼���ݵ��ļ�
		if (m_bSaveFlag) 
			fprintf(fp,"%s\t	%8f	%8f	%8f	%8f	%8f	%8f	%8f	%8f	%8f	%6.2f %8f %8f %8f %8f\n",
					strTime,g_DDJD*180/PI,g_DDWD*180/PI,g_DDGD,g_DDPH*180/PI,g_DDFY*180/PI,
					g_DDGZ*180/PI,m_MBJD*180/PI,m_MBWD*180/PI,m_MBGD,m_MBHX,m_MBSD,m_MBJL,m_dbPH*180/PI,m_dbFY*180/PI);
		LeaveCriticalSection(&g_csCP);
		LeaveCriticalSection(&g_csCP2);
	}
	else			//���ǽ��յ������¼�ֱ�ӷ���
		return;
	
}

void CComTransDlg::gpsTo84(double jd, double wd, double hh, double &px, double &py, double &pz)
{
	double a = 6378137.0;
	double b = 6356752.3142;
	double temp = b/a;
	double e = 1.0 - temp*temp;
	double w = sqrt(1.0 - e*sin(wd)*sin(wd));
	double n = a/w;

	px = (n+hh)*cos(wd)*cos(jd);
	py = (n+hh)*cos(wd)*sin(jd);
	pz = (n*(1-e)+hh)*sin(wd);
}

void CComTransDlg::dxToDl(double jd, double wd, double &x, double &y, double &z)
{
	double px,py,pz,temp;
	px = x*cos(jd)+y*sin(jd);
	py = -x*sin(jd)+y*cos(jd);
	pz = z;

	x = px*cos(wd)+pz*sin(wd);
	y = py;
	z = -px*sin(wd)+pz*cos(wd);

	temp = x;
	x = z;
	z = y;
	y = temp;

	//�˺�����Ϊ����������ֵ�����Ժ���ԭ��ı仯
}

void CComTransDlg::OnOK() 
{
	// TODO: Add extra validation here
		//�߳�ǿ����ֹ
	TerminateThread(m_pThread->m_hThread, 100);
	
	delete m_pThread;
	m_pThread=NULL;
	m_Com.ColseCom();

	fflush(fp);
	fclose(fp);

	CDialog::OnOK();
}

void CComTransDlg::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	if (m_bSaveFlag)
	{
		m_bSaveFlag = FALSE;
		fflush(fp);
		SetDlgItemText(IDC_BTN_SAVE,"��ʼ��¼");
	}
	else
	{
		m_bSaveFlag = TRUE;
		SetDlgItemText(IDC_BTN_SAVE,"ֹͣ��¼");
	}
}




void CComTransDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent) {
	case 1:
		EnterCriticalSection(&g_csCP2);
		EnterCriticalSection(&g_csCP);
		m_strMBJD.Format("%.6f��",m_MBJD*180.0/PI);
		m_strMBWD.Format("%.6f��",m_MBWD*180.0/PI);
		m_strMBGD.Format("%.1f��",m_MBGD);
		m_strMBPH.Format("%.6f��",m_dbPH*180.0/PI);
		m_strMBFY.Format("%.6f��",m_dbFY*180.0/PI);
		m_strJXSD.Format("%.6fm/s",m_JXSD);
		m_strHX.Format("%.2f��",m_MBHX);
		m_strSudu.Format("%.6fm/s",m_MBSD);
		m_strSXSD.Format("%.6fm/s",m_dbVX);
		m_strWX2.Format("%d��",m_iWXCount);
		if (m_bDataFlag)
		{
			m_strStatic2.Format("��λ");
		}
		else
		{
			m_strStatic2.Format("δ��λ");
		}
		
		
		
		m_strDDJD.Format("%.6f��",g_DDJD*180.0/PI);
		m_strDDWD.Format("%.6f��",g_DDWD*180.0/PI);
		m_strDDGD.Format("%.1f��",g_DDGD);
		m_strDDFY.Format("%.6f��",g_DDFY*180.0/PI);
		m_strDDPH.Format("%.6f��",g_DDPH*180.0/PI);
		m_strDDGZ.Format("%.6f��",g_DDGZ*180.0/PI);
		m_strDIS.Format("%3.4fǧ��",m_MBJL/1000);
		m_strWX1.Format("%d��",g_iWXCount);
		
		m_strVX.Format("%.6f",g_DDVX);
		m_strVY.Format("%.6f",g_DDVY);
		m_strVZ.Format("%.6f",g_DDVZ);
		if (g_dataFlag)
		{
			m_strStatic1.Format("��λ");
		}
		else
		{
			m_strStatic1.Format("δ��λ");
		}				
		
		
		LeaveCriticalSection(&g_csCP);
		LeaveCriticalSection(&g_csCP2);

		m_dbDeltaFY = deltaFY;
		m_dbDeltaPH = deltaPH;

		UpdateData(FALSE);
		break;
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}


void CComTransDlg::OnBtnAddfy() 
{
	// TODO: Add your control notification handler code here
	EnterCriticalSection(&g_csCP2);
	EnterCriticalSection(&g_csCP);
	deltaFY += 0.1;
	LeaveCriticalSection(&g_csCP);
	LeaveCriticalSection(&g_csCP2);
}

void CComTransDlg::OnBtnAddph() 
{
	// TODO: Add your control notification handler code here
	EnterCriticalSection(&g_csCP2);
	EnterCriticalSection(&g_csCP);
	deltaPH += 0.1;
	LeaveCriticalSection(&g_csCP);
	LeaveCriticalSection(&g_csCP2);
}

void CComTransDlg::OnBtnSubfy() 
{
	// TODO: Add your control notification handler code here
	EnterCriticalSection(&g_csCP2);
	EnterCriticalSection(&g_csCP);
	deltaFY -= 0.1;
	LeaveCriticalSection(&g_csCP);
	LeaveCriticalSection(&g_csCP2);
}

void CComTransDlg::OnBtnSubph() 
{
	// TODO: Add your control notification handler code here
	EnterCriticalSection(&g_csCP2);
	EnterCriticalSection(&g_csCP);
	deltaPH -= 0.1;
	LeaveCriticalSection(&g_csCP);
	LeaveCriticalSection(&g_csCP2);
}


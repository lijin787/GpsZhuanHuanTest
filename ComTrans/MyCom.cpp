// MyCom.cpp : implementation file
//

#include "stdafx.h"
#include "MyCom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MY_PORT 7
/////////////////////////////////////////////////////////////////////////////
// CMyCom

CMyCom::CMyCom()
{
}

CMyCom::~CMyCom()
{
}


BEGIN_MESSAGE_MAP(CMyCom, CWnd)
	//{{AFX_MSG_MAP(CMyCom)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyCom message handlers

int CMyCom::InitCom()
{
	int err=sio_open(MY_PORT);
	sio_ioctl(MY_PORT, B115200, P_EVEN | BIT_8 | STOP_1 );
	sio_baud(MY_PORT, 500000L);
	sio_flush (MY_PORT, 2 );
	return err;
}


void CMyCom::ColseCom()
{
	sio_close(MY_PORT);
}

void CMyCom::FlushComBuffer(int n)
{
	sio_flush (MY_PORT, 2 );
}

long CMyCom::GetComInLength()
{
	return sio_iqueue(MY_PORT);
}

void CMyCom::WriteComData(char *buf, int length)
{
	sio_write (MY_PORT, buf, length);
}

long CMyCom::ReadComData(char *buf, int length)
{
	sio_read(MY_PORT, buf, length);   
	return length;
}

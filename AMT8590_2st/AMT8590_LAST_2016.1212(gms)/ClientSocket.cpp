// ClientSocket.cpp : implementation file
//
// ����ö
// forcewin@popsmail.com

#include "stdafx.h"
#include "ClientSocket.h"
#include "Variable.h"			// ���� ���� ���� Ŭ���� �߰� 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}

#if 0
BEGIN_MESSAGE_MAP(CClientSocket, CSocket)
//{{AFX_MSG_MAP(CClientSocket)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

BOOL CClientSocket::Create(int address, CString szAddress, UINT nPortNo, int nReceiveSize)
{
	if (!CSocket::Create())
	{
		return FALSE;
	}

	CSocket::m_nTimeOut = 1;
	m_Check_Timeout = 0;


	if (!CSocket::Connect(szAddress, nPortNo))
	{
		CSocket::Close();
		return FALSE;
	}
	m_nReceiveLen  = 0;
 
	m_nReceiveSize = nReceiveSize;
//	m_byteReceive = new BYTE[m_nReceiveSize];
	
	m_naddress = address;

	mn_port = nPortNo;			// �߰�.

	return TRUE;
}

//BOOL CClientSocket::Create(int n_address, CString str_ip, int n_port, int n_timeout)
//{
//	if (!CSocket::Create())
//	{
//		return FALSE;
//	}
//
//	CSocket::m_nTimeOut = n_timeout;
//	if(!CSocket::Connect(str_ip, n_port))
//	{
//		CSocket::Close();
//		return FALSE;
//	}
//	
//	m_n_address = n_address;
//	return TRUE;
//}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSocket, CSocket)
	//{{AFX_MSG_MAP(CClientSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSocket member functions

void CClientSocket::OnReceive(int nErrorCode) 
{
	// ������ �б�

//	if (m_naddress >= 2)
//	{
		int i;
		memset(st_client[m_naddress].ch_rev, 0x00, 8192);
		// ������ �б�
 		for (i = 0;i < 10000; i++);
		
		st_client[m_naddress].n_rev_length = Receive(st_client[m_naddress].ch_rev, 8192);

		if( m_naddress == 11 )
		{
			int a  =10;
		}
// 		if( m_naddress == 10 )
// 		{
// 			int a  =10;
// 		}


		::SendMessage(st_handler.hWnd, WM_CLIENT_MSG+m_naddress, CLIENT_REV, m_naddress);	// ���� ���������� �޽��� �����Ͽ� ���� ȭ������ ��ȯ 
//	}
//	else
//	{
// 		m_nReceiveLen = Receive(m_byteReceive, m_nReceiveSize);
// 
// 		// ���� : SCM_RECEIVE
// 		g_Net.OnClientReceived( this );
//	}

	CSocket::OnReceive(nErrorCode);
}

int CClientSocket::Receive(void* lpBuf, int nBufLen, int nFlags) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CSocket::Receive(lpBuf, nBufLen, nFlags);
}

void CClientSocket::OnClose(int nErrorCode) 
{

//	if (m_naddress >= 2)
//	{
		st_client[m_naddress].n_rev_length = Receive(st_client[m_naddress].ch_rev, 8192);
		
		::PostMessage(st_handler.hWnd, WM_CLIENT_MSG_1+m_naddress, CLIENT_CLOSE, m_naddress);	// ���� ���������� �޽��� �����Ͽ� ���� ȭ������ ��ȯ 
//	}
//	else
//	{
//		g_Net.OnClientClosed( this );
//	}


	CSocket::OnClose(nErrorCode);
}

void CClientSocket::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CSocket::OnAccept(nErrorCode);
}

void CClientSocket::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	CSocket::OnConnect(nErrorCode);
}

BOOL CClientSocket::IsConnect()
{
	return 0;
}

BOOL CClientSocket::OnMessagePending() 
{
	// TODO: Add your specialized code here and/or call the base class
	MSG Message;
	
	if (::PeekMessage(&Message, NULL, WM_TIMER, WM_TIMER, PM_NOREMOVE))
	{
		m_Check_Timeout++;
		if (m_Check_Timeout > 10)
		{
			m_Check_Timeout = 0;
			CancelBlockingCall();
			Close();
		}
	}
	
	return CSocket::OnMessagePending();
}

BOOL CClientSocket::ConnectHelper(const SOCKADDR *lpSockAddr, int nSockAddrLen)
{
	CTime  curt, st;
	CTimeSpan span(0, 0, 0, m_nTimeOut);

	if (m_pbBlocking != NULL)
	{
		WSASetLastError(WSAEINPROGRESS);
		return  FALSE;
	}

	m_nConnectError = -1;

	if(!CAsyncSocket::ConnectHelper(lpSockAddr, nSockAddrLen))
	{
		if(GetLastError() == WSAEWOULDBLOCK)
		{
			st = CTime().GetCurrentTime();

			while(PumpMessages(FD_CONNECT))
			{
				if(m_nConnectError != -1)
				{
					WSASetLastError(m_nConnectError);
					return (m_nConnectError == 0);
				}

				curt = CTime().GetCurrentTime();
				
				if(curt > (st + span))
				{
					return FALSE;
				}
			}
		}
		return FALSE;
	}
	return TRUE;
}

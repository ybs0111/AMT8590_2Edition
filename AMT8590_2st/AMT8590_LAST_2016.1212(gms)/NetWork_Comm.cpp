// NetWork_Comm.cpp : implementation file
//

#include "stdafx.h"
#include "NetWork_Comm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetWork_Comm

CNetWork_Comm::CNetWork_Comm()
{
	int i;

	m_nSocketPort = 9898;
    m_szIPAddress = NET_DEFAULT_SOCKET_IP;
    m_wndParent   = NULL;
	m_nNetworkNo = 0;

	for (i = 0; i < 10; i++)
	{
		m_IsConnected[i] = FALSE;
	}

	m_byteReceiveData = new BYTE[NET_MAX_RECEIVE_SIZE];                         // ���۸� �ʱ�ȭ �Ѵ�.
}

CNetWork_Comm::~CNetWork_Comm()
{
	if(m_byteReceiveData)
		delete [] m_byteReceiveData;
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CNetWork_Comm, CSocket)
	//{{AFX_MSG_MAP(CNetWork_Comm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CNetWork_Comm member functions

BOOL CNetWork_Comm::Create(CWnd *pParentWnd)
{
	//int n_response;  // ��ȭ ���� ���� �÷��� //
	//CDialog_Message msg_dlg;

	if (TRUE == m_IsConnected[m_nNetworkNo])                   // �̹� ������ �Ǿ� �ִ� ���¶�� 
    {
        return FALSE;
    }

    if (!CSocket::Create())
	{
		return FALSE;
	}

	//2005.08.12 kimgangmin add  socket connect time out(?)
	m_Check_Timeout = 0;
	
	if (!CSocket::Connect(m_szIPAddress, m_nSocketPort))
	{
        CSocket::Close();
		return FALSE;
	}

    m_IsConnected[m_nNetworkNo] = TRUE;						// Ŭ���̾�Ʈ ����� ��쿡�� �̶� ������ �Ǿ��� �Ǵ�.

    m_wndParent = pParentWnd;

    return TRUE;
}

BOOL CNetWork_Comm::IsConnected()
{
	//if(m_IsConnected != TRUE && m_IsConnected != FALSE) m_IsConnected = FALSE;
	return m_IsConnected[m_nNetworkNo];
}

BOOL CNetWork_Comm::SendData(BYTE *pSendData, UINT nDataSize)
{
	if (FALSE == m_IsConnected[m_nNetworkNo]) //������°� �ƴ� ���� �������� �ʴ´�.
    {
        return FALSE;
   }

    m_nBytesBufferSize = (int)nDataSize;
    m_szSendData = pSendData;
    m_nBytesSent = Send(m_szSendData, m_nBytesBufferSize);
    
    return TRUE;
}

BOOL CNetWork_Comm::SetIPAddress(CString szIPAddress)
{
	if (TRUE == m_IsConnected[m_nNetworkNo])  //����� ���¶�� ip ���� �Ұ�..
    {
        return FALSE;
    }

    m_szIPAddress = szIPAddress;

    return TRUE;
}

BOOL CNetWork_Comm::SetSocketPort(UINT nSocketPort)
{
	if (TRUE == m_IsConnected[m_nNetworkNo])  //����� ���¶�� ��Ʈ ���� �Ұ�..
    {
        return FALSE;
    }

    m_nSocketPort = nSocketPort;

    return TRUE;
}

void CNetWork_Comm::OnSend(int nErrorCode) 
{
	//int n_response;  // ��ȭ ���� ���� �÷��� //
	//CDialog_Message msg_dlg;
	
	while (m_nBytesSent < m_nBytesBufferSize)
    {
        int dwBytes;

        if ((dwBytes = Send((BYTE*)m_szSendData + m_nBytesSent,
            m_nBytesBufferSize - m_nBytesSent)) == SOCKET_ERROR)
        {
            if (GetLastError() == WSAEWOULDBLOCK) break;
            else
            {
                TCHAR szError[256];
                wsprintf(szError, "Server Socket failed to send: %d", GetLastError());
                Close();
                Func.MsgLog (szError);
            }
        }
        else
        {
            m_nBytesSent += dwBytes;
        }
    }

    if (m_nBytesSent == m_nBytesBufferSize)
    {
        m_nBytesSent = m_nBytesBufferSize = 0;
    }
	
	CSocket::OnSend(nErrorCode);
}

void CNetWork_Comm::OnClose(int nErrorCode) 
{
	CSocket::OnClose(nErrorCode);
	
	if (m_nNetworkNo >= 0 && m_nNetworkNo < 10) //091113 �߰� ���� 
	{
		m_IsConnected[m_nNetworkNo] = FALSE;
	}

	m_wndParent->SendMessage(WM_NETWORK_MSG, SOCKETCLOSE, LPARAM(m_nNetworkNo));                  // ������ ����Ǿ��ٰ� �˸�
}

void CNetWork_Comm::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	BYTE* m_byteTempReceiveData;
	CString mstr_ReceiveData = _T(""); //, str_serverend;

	m_nReceiveDataSize = (UINT)Receive(m_byteReceiveData, NET_MAX_RECEIVE_SIZE);				// �����͸� �����Ѵ�

	m_byteTempReceiveData = new BYTE[m_nReceiveDataSize + 1];

	memcpy(m_byteTempReceiveData, m_byteReceiveData, m_nReceiveDataSize);

	m_byteTempReceiveData[m_nReceiveDataSize] = 0x00;	

	mstr_ReceiveData.Format("%s", m_byteTempReceiveData);

	if (mstr_ReceiveData.GetLength() == 0)
	{
		if (m_byteTempReceiveData)
		delete m_byteTempReceiveData;
		return;
	}

//	if (m_nNetworkNo != 1)			// 2K9/12/10
//	{
		//20100110 james st_other.str_n_rcv_msg.Format("[%s] %s", OnNetworkNameChange(m_nNetworkNo), mstr_ReceiveData);
//		st_msg.mstr_normal_msg.Format("[%d] %s", m_nNetworkNo, mstr_ReceiveData);
		sprintf(st_msg.c_normal_msg, "[%d] %s", m_nNetworkNo, mstr_ReceiveData);
		if (st_handler.cwnd_list != NULL)  st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
//	}

	if (m_byteTempReceiveData)
		delete m_byteTempReceiveData;
	
	CSocket::OnReceive(nErrorCode);
}

BOOL CNetWork_Comm::OnMessagePending() 
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

BOOL CNetWork_Comm::SetNetworkNumber(UINT n_network_no)
{
	if (TRUE == m_IsConnected[n_network_no])  //����� ���¶�� ���� �Ұ�..
    {
        return FALSE;
    }
	
    m_nNetworkNo = n_network_no;
	
    return TRUE;
}
// ServerSocket.cpp : implementation file
//
// ����ö
// forcewin@popsmail.com

#include "stdafx.h"
#include "ServerSocket.h"
#include "Variable.h"		// ���� ���� ���� Ŭ���� �߰� 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
	CServerItem *ServerItem;

	while(m_listClient.GetCount())
	{
		ServerItem = (CServerItem*)m_listClient.GetHead();
		ServerItem->Close();
		m_listClient.RemoveHead();
		delete ServerItem;
	}
}

// ���� ���� ����
//BOOL CServerSocket::Create(int n_address, int n_port) 
//{
//	if (!CSocket::Create(n_port, SOCK_STREAM))
//	{
//		return FALSE;
//	}
//
//	if (!CSocket::Listen())
//	{
//		return FALSE;
//	}
//
//	m_n_address = n_address;
//	return TRUE;
//}

BOOL CServerSocket::Create(UINT nPortNo, int nServerNo, int nReceiveDataLen) 
{
	if (!CSocket::Create(nPortNo, SOCK_STREAM))
	{
		return FALSE;
	}

	if (!CSocket::Listen())
	{
		return FALSE;
	}

	m_nReceiveDataLen = nReceiveDataLen;
	m_nServer = nServerNo;
	m_n_address = nServerNo;
	return TRUE;
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CServerSocket, CSocket)
	//{{AFX_MSG_MAP(CServerSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CServerSocket member functions

// Client ���� ����
void CServerSocket::OnAccept(int nErrorCode) 
{
	CServerItem* ServerItem = new CServerItem(this);

	if (CSocket::Accept(*ServerItem))
	{
		m_listClient.AddTail(ServerItem);

//		if (m_n_address < 2)
//		{
//			g_Net.OnServerAccept( this );
//		}
	}
	else
	{
		delete ServerItem;
	}
	
	CSocket::OnAccept(nErrorCode);
}

// Client ���� �ݱ�
void CServerSocket::CloseClient(CSocket* ServerItem)
{
	POSITION pos = m_listClient.Find(ServerItem);
	if (pos != NULL)
	{
		ServerItem->Close();
		m_listClient.RemoveAt(pos);
		delete ServerItem;
	}
}

// ��� Client�� ������ ����
void CServerSocket::SendClientAll(const void *lpBuf, int nBufLen, int nFlags)
{
	CServerItem *ServerItem;

	POSITION pos = m_listClient.GetHeadPosition();
	while (pos != NULL)
	{
		ServerItem = (CServerItem*)m_listClient.GetNext(pos);
		ServerItem->Send(lpBuf, nBufLen, nFlags);
	}

}

// Ư�� Client�� ������ ����
int CServerSocket::SendClientAt(CSocket* ServerItem, const void *lpBuf, int nBufLen, int nFlags)
{
	return ServerItem->Send(lpBuf, nBufLen, nFlags);
}

// ���ӵ� Client ����
int CServerSocket::GetClientCount()
{
	return m_listClient.GetCount();
}

// Client Object
CSocket* CServerSocket::GetClient(int nIndex)
{
	return (CSocket*)m_listClient.GetAt(m_listClient.FindIndex(nIndex));
}

void CServerSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CSocket::OnReceive(nErrorCode);
}

void CServerSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CSocket::OnClose(nErrorCode);
}
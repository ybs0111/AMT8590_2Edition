// ServerItem.cpp : implementation file
//
// ����ö
// forcewin@popsmail.com

#include "stdafx.h"
#include "handler.h"
#include "ServerSocket.h"
#include "Variable.h"		// ���� ���� ���� Ŭ���� �߰� 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerItem

CServerItem::CServerItem(CSocket* pServerSocket)
{
	m_ServerSocket = pServerSocket;
	m_nReceiveLen  = 0;

//	m_byteReceive = new BYTE[((CServerSocket*)m_ServerSocket)->m_nReceiveDataLen];

}

CServerItem::~CServerItem()
{

}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CServerItem, CSocket)
	//{{AFX_MSG_MAP(CServerItem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CServerItem member functions

// ���� �ݱ�
void CServerItem::OnClose(int nErrorCode) 
{
	CServerSocket* ServerSocket = (CServerSocket*)m_ServerSocket;
	
	// ���� ����
	ServerSocket->CloseClient(this);
	// ���̸� ��ġ �̵���Ŵ [2013.11.12]
	// ���� ���������� �޽��� �����Ͽ� ������ �����Ŵ
//	::PostMessage(st_handler.hWnd, WM_SERVER_MSG, SERVER_CLOSE, ServerSocket->m_n_address);
	
	CSocket::OnClose(nErrorCode);
	
}

// ���� ������ ó��
void CServerItem::OnReceive(int nErrorCode) 
{
	CServerSocket* ServerSocket = (CServerSocket*)m_ServerSocket;
	
//	if (ServerSocket->m_n_address >= 2)
//	{
		memset(&st_server[ServerSocket->m_n_address].ch_rev, 0, sizeof(st_server[ServerSocket->m_n_address].ch_rev));
		
		//	sprintf(st_server[ServerSocket->m_n_address].ch_rev,"%s","LOTID=AAA,LEFCNT=00,MGZID=,PARTID=");
		// ������ �б�
		st_server[ServerSocket->m_n_address].n_rev_length = Receive(st_server[ServerSocket->m_n_address].ch_rev, 8192);
		st_server[ServerSocket->m_n_address].ch_rev[st_server[ServerSocket->m_n_address].n_rev_length+1] = '\r';
		
		::SendMessage(st_handler.hWnd, WM_SERVER_MSG + ServerSocket->m_n_address, SERVER_REV, ServerSocket->m_n_address);	// ���� ���������� �޽��� �����Ͽ� ���� ȭ������ ��ȯ 	
//	}
//	else
//	{
//		m_nReceiveLen = Receive(m_byteReceive, ServerSocket->m_nReceiveDataLen);
//	
//		g_Net.OnServerReceived( this );
//	}
	
	CSocket::OnReceive(nErrorCode);

}

#if !defined(AFX_SERVERSOCKET_H__2A49E7C7_67E3_11D3_8401_006097663D30__INCLUDED_)
#define AFX_SERVERSOCKET_H__2A49E7C7_67E3_11D3_8401_006097663D30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerSocket.h : header file
//
#include "Afxmt.h"
//#include <afxmt.h>
#include "ServerItem.h"

/////////////////////////////////////////////////////////////////////////////
// CServerSocket command target

#define MAX_RECEIVE_LEN	4096

class CServerSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CServerSocket();
	virtual ~CServerSocket();

	// ���� ���� ����
//	BOOL Create(int n_address, int n_port);
	BOOL Create(UINT nPortNo, int nServerNo, int nReceiveDataLen=MAX_RECEIVE_LEN);

// Overrides
public:
	CCriticalSection cs;
	// ���ӵ� Client ����
	int GetClientCount();
	// Client Object
	CSocket* GetClient(int nIndex);

	// ��� Client�� ������ ����
	void SendClientAll(const void* lpBuf, int nBufLen, int nFlags=0);
	// Ư�� Client�� ������ ����
	int  SendClientAt(CSocket* ServerItem, const void* lpBuf, int nBufLen, int nFlags=0);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);

	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CServerSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	// Client ���� ����
	void CloseClient(CSocket* ServerItem);
	
	int m_n_address;
	
	int			m_nServer;
	int			m_nReceiveDataLen;	// �ִ� ���� ������ ����
	CPtrList m_listClient;	// Ŭ���̾�Ʈ ���� ����Ʈ ���
	
	friend CServerItem;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERSOCKET_H__2A49E7C7_67E3_11D3_8401_006097663D30__INCLUDED_)

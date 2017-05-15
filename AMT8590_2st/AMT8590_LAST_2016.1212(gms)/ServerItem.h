#if !defined(AFX_CLIENTSOCKET_H__2A49E7C8_67E3_11D3_8401_006097663D30__INCLUDED_)
#define AFX_CLIENTSOCKET_H__2A49E7C8_67E3_11D3_8401_006097663D30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerItem.h : header file
//
// ���̸� �߰� [2014.07.28]
#include <afxsock.h>

/////////////////////////////////////////////////////////////////////////////
// CServerItem command target

class CServerItem : public CSocket
{
// Attributes
public:

// Operations
public:
	CServerItem(CSocket* pServerSocket);
	virtual ~CServerItem();

// Overrides
public:
	BYTE*	m_byteReceive;	// ���� ����
	int		m_nReceiveLen;	// ���� ������ ����
	BYTE	m_by_rev[1024];	// ���� ����
	int		m_n_rev_length;
	
	CSocket* m_ServerSocket;	// ���� ����

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerItem)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CServerItem)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCKET_H__2A49E7C8_67E3_11D3_8401_006097663D30__INCLUDED_)

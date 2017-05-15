#if !defined(AFX_NETWORK_COMM_H__07DFF696_83DB_469F_B3C7_EF20F7326707__INCLUDED_)
#define AFX_NETWORK_COMM_H__07DFF696_83DB_469F_B3C7_EF20F7326707__INCLUDED_

#include "Variable.h"

#include "Public_Function.h"	// ���� ���� �� I/O ���� ���� Ŭ���� //

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetWork_Comm.h : header file
//
#define NET_DEFAULT_SOCKET_PORT         9898					// ����Ʈ�� �����ϴ� ��Ʈ ��ȣ 
#define NET_DEFAULT_SOCKET_IP           "167.125.26.240"		// ����Ʈ�� �����ϴ� IP ��巹�� 
#define NET_MAX_RECEIVE_SIZE			4096					// ������ �����Ҷ�

/////////////////////////////////////////////////////////////////////////////
// CNetWork_Comm command target

class CNetWork_Comm : public CSocket
{
// Attributes
//public:

// Operations
public:
	CNetWork_Comm();
	virtual ~CNetWork_Comm();

// Overrides
public:
	//20100110  james CString OnNetworkNameChange(int n_name);
	BOOL SetNetworkNumber(UINT n_network_no);
	int m_Check_Timeout;
	CWnd* m_wndParent;
	BOOL SendData(BYTE* pSendData, UINT nDataSize);
	BOOL IsConnected();
	BOOL Create(CWnd* pParentWnd);
	BOOL SetSocketPort(UINT nSocketPort=NET_DEFAULT_SOCKET_PORT);
	BOOL SetIPAddress(CString szIPAddress=NET_DEFAULT_SOCKET_IP);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetWork_Comm)
	public:
	virtual void OnSend(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual BOOL OnMessagePending();
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CNetWork_Comm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:	
	BYTE* m_szSendData;
	BOOL m_IsConnected[10];
	int m_nBytesBufferSize;
	int m_nBytesSent;

	//12355
	UINT m_nReceiveDataSize;                                    // ������ �������� ������ 
	BYTE* m_byteReceiveData;                                    // �����͸� �����Ͽ��� ��쿡 �����ϴ� ���� 

	UINT m_nSocketPort;
	CString m_szIPAddress;
	UINT m_nNetworkNo;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETWORK_COMM_H__07DFF696_83DB_469F_B3C7_EF20F7326707__INCLUDED_)

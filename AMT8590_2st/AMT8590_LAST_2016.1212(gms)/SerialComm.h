// FILE NAME : SerialComm.h
//
// Copyright (C) 1998-1999 Mirae Corporation
// All rights reserved.
//
// DIVISION    : LCD Test System Division
// CREATED BY  : Lee Kyu Il
// MODIFIED BY : Lee Jae Kwang
// REVISION    :
//     1> 1998. 6. 22 : Created by Lee Kyu Il
//     2> 1998. 10. 11 : Modified by Lee Jae Kwang
//     3> 1998. 11. 2 : Event/Error handling changed by Lee Jae Kwang
// DESCRIPTION :
//
// REFERENCE   :
// 
// SerialComm.h: interface for the SerialComm class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERIALCOMM_H__5A18D280_71E6_11D2_95E1_0020AF3856DB__INCLUDED_)
#define AFX_SERIALCOMM_H__5A18D280_71E6_11D2_95E1_0020AF3856DB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// A character was received and placed in the input buffer. 
#define WM_COMM_DATA	WM_USER+100
// The event character was received and placed in the input buffer.  
#define WM_COMM_EVENT	WM_USER+101

#define SERIAL_WAIT		0
#define SERIAL_NO_WAIT	1
#define SERIAL_TIME_INFINITE 0

class AFX_EXT_CLASS SerialComm : public CObject  
{
public:
	void MmdSerial_BufferClear();
	
	void MmdSerialSet_ReciveMode();
	SerialComm();
	virtual ~SerialComm();

	// ������ ����
	CWinThread*			m_Thread;

	// synchronisation ��ü ����
	CRITICAL_SECTION	*m_csCommunicationSync;
	BOOL				m_bThreadAlive;

	// �ڵ� ����
	HANDLE				m_hShutdownEvent;
	HANDLE				m_hComm;
	HANDLE				m_hWriteEvent;

	// �̺�Ʈ�� ���� �迭 ����
	HANDLE				m_hEventArray[3];

	// ����ü ����
	OVERLAPPED			m_ov;
	COMMTIMEOUTS		m_CommTimeouts;
	DCB					m_dcb;

	CWnd*				m_pOwner;

	// ��� ����̽� ��ȣ, ���� ������, �̺�Ʈ ��ü�� ���� ���� ����
	UINT				m_nPortNr;
	TCHAR*				m_szWriteBuffer;
	int					m_nWriteBufferSize;
	DWORD				m_dwCommEvents;
	UINT				m_nPortNum;

	// writing size current
	DWORD				m_nWriteSize;
	// read and write error flag
	int					m_nWriteError;
	int					m_nReadError;
	BOOL				m_nWriteCompleted;

	// ��� ��Ʈ �ʱ�ȭ
	void	MmdSerialInitializeObject ();
	void	MmdSerialDestroyObject ();
	BOOL	MmdSerialInitializePort(CWnd* pPortOwner, UINT portnr = 1,
				UINT baud = 19200, char parity = 'N',
				UINT databits = 8, UINT stopsbits = 1,
				UINT nBufferSize = 512, DWORD dwCommEvents = EV_RXCHAR | EV_CTS);

	// ��� �Լ�(PUBLIC)
	BOOL	MmdSerialStartMonitoring();
	BOOL	MmdSerialRestartMonitoring();
	BOOL	MmdSerialStopMonitoring();
	DWORD	MmdSerialGetWriteBufferSize();
	DWORD	MmdSerialGetCommEvents();
	DCB		MmdSerialGetDCB();
	int		MmdSerialWriteData(LPTSTR pData, int nSize,
				int nWaitFlag, int nTimeOut);
	UINT	MmdSerialGetPortNum();

protected:
	// ��� �Լ� (PROTECTED)
	void		MmdSerialErrorMessage(LPTSTR ErrorText);
	static UINT	MmdSerialSeperateThread(LPVOID pParam);
	static int	MmdSerialReceivePort(SerialComm* port, COMSTAT comstat);
	static int	MmdSerialWritePort(SerialComm* port);
	time_t		MmdSerialGetTime ();
};


class AFX_EXT_CLASS SerialCommNoThread : public CObject 
{
public:
	SerialCommNoThread();
	virtual ~SerialCommNoThread();

	HANDLE				m_hComm;

	OVERLAPPED			m_ov;
	COMMTIMEOUTS		m_CommTimeouts;
	DCB					m_dcb;

	// ��� ����̽� ��ȣ, ���� ������, �̺�Ʈ ��ü�� ���� ���� ����
	UINT				m_nPortNr;
	DWORD				m_dwCommEvents;
	UINT				m_nPortNum;

	TCHAR*				m_szWriteBuffer;
	int					m_nWriteBufferSize;
	DWORD				m_nWriteSize;


	// ��� ��Ʈ �ʱ�ȭ
	void	MmdSerialNoInitializeObject ();
	void	MmdSerialNoDestroyObject ();
	BOOL	MmdSerialNoInitializePort(UINT portnr = 1,
				UINT baud = 19200, char parity = 'N',
				UINT databits = 8, UINT stopsbits = 1,
				UINT nBufferSize = 512, DWORD dwCommEvents = EV_RXCHAR | EV_CTS);

	// ��� �Լ�(PUBLIC)
	int		MmdSerialNoWriteData(LPTSTR pData, int nSize, int nTimeOut);
	int		MmdSerialNoReadData(LPTSTR pData, int nSize, int nTimeOut);

	DWORD	MmdSerialNoGetWriteBufferSize();
	DWORD	MmdSerialNoGetCommEvents();
	DCB		MmdSerialNoGetDCB();
	UINT	MmdSerialNoGetPortNum();
	time_t	MmdSerialNoGetCurrentTime();


protected:
	// ��� �Լ� (PROTECTED)
	void		MmdSerialNoErrorMessage(LPTSTR ErrorText);
};
#endif // !defined(AFX_SERIALCOMM_H__5A18D280_71E6_11D2_95E1_0020AF3856DB__INCLUDED_)

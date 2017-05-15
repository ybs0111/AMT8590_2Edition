#pragma once

class CComm;

class CInterfaceGms
{
public:
	CString			m_strChann[5];

	DWORD			m_dwWaitTime[3];

	double			m_dChann[5];

	int				m_nThreadStep;
	int				m_nChann[2];
	int				m_nComPort;			// ��� ��Ʈ
	int				m_nBaudRate;		// ��� �ӵ�
	int				m_nDataBit;			// ������ ��Ʈ
	int				m_nStopBit;			// stop ��Ʈ
	int				m_nParityBit;		// parity ��Ʈ

	BYTE			m_byEnd;
	//kwlee	2016.0811
	int				m_nCommStep;
	int				m_nTimFlag;
	int				m_nAsdFlag;
	int				m_nPngFlag;
	
	int				m_nRetry;
	/////////////////////


	bool			m_bRevFlag;
	bool			m_bConnect;			// rs-232c ���� ����
	bool			m_bThread;

	HANDLE			m_thrHandle;

	CComm			*m_pCom;			// ��� class ������

	bool			OnOpen(int nPort, int nBaudRate, int nParityBit, int nDataBit, int nStopBit, BYTE byEnd);
	void			OnClose();
	void			OnDataSend(CString strData);
	void			OnDataRevice(CString strData);
	void			OnGmsDataCheck();

	//kwlee 2016.0821
	void            OnDataReceive(CString strData); 
	int				OnElectrostatic_Check();
	CString			OnSyncTime();
	CString			OnAutoSendReq();
	CString         OnDateFormat(CString strDate);
	//////////////

public:
	CInterfaceGms(void);
	~CInterfaceGms(void);
};

extern CInterfaceGms clsGms;
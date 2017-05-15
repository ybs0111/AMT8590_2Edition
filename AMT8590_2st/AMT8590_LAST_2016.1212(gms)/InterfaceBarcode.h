#pragma once

class CComm;


class CInterfaceBarcode
{
public:
	int				m_nBarcodeCount;

	DWORD			m_dwWaitTime[3];

	CString			m_strBarcode[100];

	int				m_nThreadStep;
	int				m_nComPort;			// ��� ��Ʈ
	int				m_nBaudRate;		// ��� �ӵ�
	int				m_nDataBit;			// ������ ��Ʈ
	int				m_nStopBit;			// stop ��Ʈ
	int				m_nParityBit;		// parity ��Ʈ

	BYTE			m_byEnd;

	bool			m_bConnect;			// rs-232c ���� ����
	bool			m_bThread;

	HANDLE			m_thrHandle;

	CComm			*m_pCom;			// ��� class ������

	bool			OnOpen(int nPort, int nBaudRate, int nParityBit, int nDataBit, int nStopBit, BYTE byEnd);
	void			OnClose();
	void			OnBarcodeReset();
	int				OnBarcodeCount();
	CString			OnBarcodeReadData(int nNum);
	void			OnDataSend(CString strData);
	void			OnDataRevice(CString strData);
public:
	CInterfaceBarcode(void);
	~CInterfaceBarcode(void);
};

extern CInterfaceBarcode clsBarcode;



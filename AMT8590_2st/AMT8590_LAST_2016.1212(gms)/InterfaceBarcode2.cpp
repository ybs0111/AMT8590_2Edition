#include "StdAfx.h"
#include "InterfaceBarcode2.h"
//#include "PublicFunction.h"
#include "Variable.h"
#include "Comm.h"

CInterfaceBarcode2 clsBarcode2;

UINT OnInterfaceBarcodeMessage2(LPVOID lParam);

CInterfaceBarcode2::CInterfaceBarcode2(void)
{
	m_nComPort		= -1;		// ��� ��Ʈ
	m_nBaudRate		= -1;		// ��� �ӵ�
	m_nDataBit		= -1;		// ������ ��Ʈ
	m_nStopBit		= -1;		// stop ��Ʈ
	m_nParityBit	= -1;		// parity ��Ʈ

	m_byEnd			=0x20;

	m_bConnect		= false;	// rs-232c ���� ����
	m_bThread		= false;
	m_bConnect		= false;

	m_thrHandle		= NULL;

	m_pCom			= NULL;		// ��� class ������
}


CInterfaceBarcode2::~CInterfaceBarcode2(void)
{
	if (m_thrHandle) 
	{
		m_bThread = false;
		while(WaitForSingleObject(m_thrHandle, 1500))
		{
			if (m_thrHandle == NULL) break;
		}
	}

	if (m_pCom != NULL)
	{
		delete m_pCom;
		m_pCom = NULL;
	}
}


UINT OnInterfaceBarcodeMessage2(LPVOID lParam)
{
	CInterfaceBarcode2 *pMsg = (CInterfaceBarcode2 *)lParam;

	CString strMsg;
	CString strTemp;
	int		nLength;
	BYTE	byData[100];

/*
	while(pMsg->m_bThread)
	{
		switch (pMsg->m_nThreadStep)
		{
			case 0:
				pMsg->m_dwWaitTime[0] = GetTickCount();

				pMsg->m_nThreadStep = 100;
				break;

			case 100:
				pMsg->m_dwWaitTime[1] = GetTickCount();
				pMsg->m_dwWaitTime[2] = pMsg->m_dwWaitTime[1] - pMsg->m_dwWaitTime[0];

				if (pMsg->m_dwWaitTime[2] <= (DWORD)0)
				{
					pMsg->m_dwWaitTime[0] = GetTickCount();
					break;
				}

				if (pMsg->m_dwWaitTime[2] > (DWORD)100)
				{
					if (pMsg->m_pCom->m_bRevFlag)
					{
						nLength = pMsg->m_pCom->m_nLength;
						if (nLength > 0 )
						{
							if (nLength > 100)
							{
								pMsg->m_pCom->Empty();
							}
							else
							{
								pMsg->m_pCom->ReadData(byData, nLength);

//								strTemp = clsFunc.OnCharToString((char*)byData, sizeof(byData));
								strMsg	= strTemp.Mid(0, nLength -1);

								pMsg->OnDataRevice(strMsg);
							}
						}
					}

					pMsg->m_nThreadStep = 0;
				}
				break;
		}
	}

	pMsg->m_thrHandle = NULL;
*/
	while(pMsg->m_bThread)
	{
		if (pMsg->m_pCom->m_bRevFlag)
		{
			nLength = pMsg->m_pCom->m_nLength;
			if (nLength > 0 )
			{
				if (nLength > 100)
				{
					pMsg->m_pCom->Empty();
				}
				else
				{
					pMsg->m_pCom->ReadData(byData, nLength);
					strTemp.Format("%s", byData);
					strMsg	= strTemp.Mid(0, nLength - 1);
					
					pMsg->OnDataRevice(strMsg);
				}
			}
		}
	}
	
	pMsg->m_thrHandle = NULL;
	return 0;
}


bool CInterfaceBarcode2::OnOpen(int nPort, int nBaudRate, int nParityBit, int nDataBit, int nStopBit, BYTE byEnd)
{
	if (m_pCom != NULL)
	{
		delete m_pCom;
		m_pCom = NULL;
	}

	m_pCom = new CComm;
	if (m_pCom->OpenSerial(nPort, nBaudRate, nDataBit, nStopBit, nParityBit))
	{
		m_bConnect		= true;
		m_nComPort		= nPort;
		m_nBaudRate		= nBaudRate;
		m_nParityBit	= nParityBit;
		m_nDataBit		= nDataBit;
		m_nStopBit		= nStopBit;

		m_pCom->m_byEnd	= byEnd;

		m_nThreadStep	= 0;
		m_bThread		= true;
		m_thrHandle		= AfxBeginThread(OnInterfaceBarcodeMessage2, this);

		return true;
	}
	else
	{
		// jtkim 20141117
		delete m_pCom;
		m_pCom = NULL;
	}

	m_bConnect = false;

	return false;
}


void CInterfaceBarcode2::OnClose()
{
	if (m_thrHandle) 
	{
		m_bThread = false;
		while(WaitForSingleObject(m_thrHandle, 1500))
		{
			if (m_thrHandle == NULL) break;

			Sleep(5);
		}
	}

	if (m_pCom != NULL)
	{
		m_pCom->CloseConnection();

		while(m_pCom->idComDev != NULL)
		{
			if (m_pCom->idComDev == NULL) break;

			Sleep(1);
		}
		delete m_pCom;
		m_pCom = NULL;

		m_bConnect = false;
	}
}


void CInterfaceBarcode2::OnDataSend(CString strData)
{
	BYTE byData[100];
	int  nLength = strData.GetLength();

	// com�� ����Ǿ� ���� ������
	if (m_pCom == NULL) return; 

	m_pCom->Empty(); // com buffer ����

//	clsFunc.OnStringToChar(strData, (char*)byData);
	sprintf((char*)byData, strData);

	byData[nLength] = 0x0D;

	m_pCom->WriteCommBlock((LPSTR)byData, nLength + 1);
}


void CInterfaceBarcode2::OnDataRevice(CString strData)
{
	if (strData == _T(""))
	{
		m_strBarcode[m_nBarcodeCount] = _T("BARCODE ERROR");
		m_nBarcodeCount++;
		st_sync.n_barcode_read_serial_num[1][CTL_LEFT] = -1;
		st_sync.n_barcode_read_serial_num[1][CTL_RIGHT] = -1;
	}
	else
	{
		if (m_nBarcodeCount >= 100) return;

		m_strBarcode[m_nBarcodeCount]	= strData;
		m_nBarcodeCount++;
		st_sync.n_barcode_read_serial_num[1][CTL_LEFT] = atoi(strData);
		st_sync.n_barcode_read_serial_num[1][CTL_RIGHT] = atoi(strData);
	}

	if (st_handler.cwnd_list != NULL)  
	{
		sprintf(st_msg.c_normal_msg, strData);
		st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG); 
	}
}

void CInterfaceBarcode2::OnBarcodeReset()
{
	m_nBarcodeCount = 0;
	m_pCom->Empty();
}


CString	CInterfaceBarcode2::OnBarcodeReadData(int nNum)
{
	return m_strBarcode[nNum];
}

int	CInterfaceBarcode2::OnBarcodeCount()
{
	return m_nBarcodeCount;
}

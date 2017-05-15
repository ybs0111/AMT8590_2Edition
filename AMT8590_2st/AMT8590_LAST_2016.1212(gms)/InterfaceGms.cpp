#include "StdAfx.h"
#include "InterfaceGms.h"
#include "Variable.h"
#include "Public_Function.h"
#include "Comm.h"

CInterfaceGms clsGms;

UINT OnInterfaceGmpMessage(LPVOID lParam);

CInterfaceGms::CInterfaceGms(void)
{
	m_nChann[0]		= 1;
	m_nChann[1]		= 0;
	m_nComPort		= -1;		// 통신 포트
	m_nBaudRate		= -1;		// 통신 속도
	m_nDataBit		= -1;		// 데이터 비트
	m_nStopBit		= -1;		// stop 비트
	m_nParityBit	= -1;		// parity 비트

	m_byEnd			=0x03;

	m_bConnect		= false;	// rs-232c 연결 상태
	m_bThread		= false;
	m_bConnect		= false;
	m_bRevFlag		= true;

	m_thrHandle		= NULL;

	m_pCom			= NULL;		// 통신 class 포인터
}


CInterfaceGms::~CInterfaceGms(void)
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
//////////////////
//kwlee 2016.0821
int CInterfaceGms::OnElectrostatic_Check()
{
	CString strTemp;
	CTime	time;
	
	int nFunRet = CTLBD_RET_PROCEED;
	
	switch(m_nCommStep)
	{
		case 0:
			if (m_nTimFlag != TRUE || m_nAsdFlag != TRUE || m_nPngFlag != FALSE)
			{
				if (m_nTimFlag != TRUE)
				{
					if (st_client[CLS_GMS].n_connect == CTL_YES)
					{
						m_nRetry		= 0;
						m_nCommStep = 1000;
					}
					else
					{
					
						m_dwWaitTime[0] = GetTickCount();

						::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + CLS_GMS, CLIENT_CONNECT, 0);

						m_nCommStep = 100;
					}
				}
				if (m_nAsdFlag != TRUE)
				{
					if (st_client[CLS_GMS].n_connect == CTL_YES)
					{
						m_nRetry		= 0;
						m_nCommStep = 2000;
					}
					else
					{
					
						m_dwWaitTime[0] = GetTickCount();

						::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + CLS_GMS, CLIENT_CONNECT, 0);

						m_nCommStep = 100;
					}
				}
				if (m_nPngFlag != FALSE)
				{
					if (st_client[CLS_GMS].n_connect == CTL_YES)
					{
						m_nRetry	= 0;
						m_nCommStep = 3000;
					}
					else
					{
						
						m_dwWaitTime[0]	= GetTickCount();
						::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + CLS_GMS, CLIENT_CONNECT, 0);

						m_nCommStep = 100;
					}
				}
			}
			break;

		case 100:
			if (st_client[CLS_GMS].n_connect == CTL_YES)
			{
				m_nCommStep = 0;
			}
			else
			{
				m_dwWaitTime[1] = GetTickCount();
				m_dwWaitTime[2] = m_dwWaitTime[1] - m_dwWaitTime[0];

				if (m_dwWaitTime[2] < 0)
				{
					m_dwWaitTime[0] = GetTickCount();
					break;
				}

				if (m_dwWaitTime[2] > WAIT_CONNECT)
				{
					m_nRetry++;

					if (m_nRetry > 3)
					{
						::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + CLS_GMS, CLIENT_CLOSE, 0);

						m_dwWaitTime[0] = GetTickCount();
					//	CTL_Lib.Alarm_Error_Occurrence(20000, dWARNING, _T("630000"));
						nFunRet = CTLBD_RET_ERROR;
						m_nCommStep = 200;
					}
					else
					{
						m_dwWaitTime[0] = GetTickCount();
						m_nCommStep = 200;
					}
				}
			}
			break;

		case 200:
			m_dwWaitTime[1] = GetTickCount();
			m_dwWaitTime[2] = m_dwWaitTime[1] - m_dwWaitTime[0];

			if (m_dwWaitTime[2] < 0)
			{
				m_dwWaitTime[0] = GetTickCount();
				break;
			}

			if (m_dwWaitTime[2] > WAIT_CLOSE)
			{
				m_nCommStep = 0;
			}
			break;

		case 1000:
			m_nRetry		= 0;
			m_dwWaitTime[0]	=	GetTickCount();

			st_client[CLS_GMS].strSend	=	OnSyncTime();

			::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + CLS_GMS, CLIENT_SEND, 0);

			m_nCommStep	= 1100;
			break;

		case 1100:
			m_dwWaitTime[1] = GetTickCount();
			m_dwWaitTime[2] = m_dwWaitTime[1] - m_dwWaitTime[0];

			if (m_nTimFlag == TRUE)
			{
				//::SendMessage(st_handler_info.hWnd, WM_CLIENT_MSG + GMS_NETWORK, CLIENT_CLOSE, 0);
				m_nCommStep = 0;
			}
			else
			{
				if (m_dwWaitTime[2] < 0)
				{
					m_dwWaitTime[0] = GetTickCount();
				}
				else if (m_dwWaitTime[2] >= WAIT_RCV)
				{
					m_nRetry++;

					if (m_nRetry > 3)
					{
						::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + CLS_GMS, CLIENT_CLOSE, 0);

						m_dwWaitTime[0] = GetTickCount();
					//	CTL_Lib.Alarm_Error_Occurrence(20000, dWARNING, _T("630001"));
						nFunRet = CTLBD_RET_ERROR;
						m_nCommStep = 1200;
					}
					else
					{
						m_dwWaitTime[0] = GetTickCount();

						::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + CLS_GMS, CLIENT_CLOSE, 0);
						m_nCommStep = 1200;
					}
				}
			}
			break;

		case 1200:
			m_dwWaitTime[1] = GetTickCount();
			m_dwWaitTime[2] = m_dwWaitTime[1] - m_dwWaitTime[0];

			if (m_dwWaitTime[2] < 0)
			{
				m_dwWaitTime[0] = GetTickCount();
				break;
			}

			if (m_dwWaitTime[2] > WAIT_CLOSE)
			{
				m_nCommStep = 0;
			}
			break;

		case 2000:
			m_nRetry		= 0;
			m_dwWaitTime[0]	=	GetTickCount();

			st_client[CLS_GMS].strSend	=	OnAutoSendReq();

			::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + CLS_GMS, CLIENT_SEND, 0);

			m_nCommStep	= 2100;
			break;

		case 2100:
			m_dwWaitTime[1] = GetTickCount();
			m_dwWaitTime[2] = m_dwWaitTime[1] - m_dwWaitTime[0];

			if (m_nAsdFlag == TRUE)
			{
				//::SendMessage(st_handler_info.hWnd, WM_CLIENT_MSG + GMS_NETWORK, CLIENT_CLOSE, 0);
				m_nCommStep = 0;
			}
			else
			{
				if (m_dwWaitTime[2] < 0)
				{
					m_dwWaitTime[0] = GetTickCount();
				}
				else if (m_dwWaitTime[2] >= WAIT_RCV)
				{
					m_nRetry++;

					if (m_nRetry > 3)
					{
						if (m_nRetry > 3)
						{
							::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + CLS_GMS, CLIENT_CLOSE, 0);

							m_dwWaitTime[0] = GetTickCount();
					//		CTL_Lib.Alarm_Error_Occurrence(20000, dWARNING, _T("630001"));
							nFunRet = CTLBD_RET_ERROR;
							m_nCommStep = 2200;
						}
						else
						{
							m_dwWaitTime[0] = GetTickCount();
							m_nCommStep = 2200;
						}
					}
				}
			}
			break;

		case 2200:
			m_dwWaitTime[1] = GetTickCount();
			m_dwWaitTime[2] = m_dwWaitTime[1] - m_dwWaitTime[0];

			if (m_dwWaitTime[2] < 0)
			{
				m_dwWaitTime[0] = GetTickCount();
				break;
			}

			if (m_dwWaitTime[2] > WAIT_CLOSE)
			{
				m_nCommStep = 0;
			}
			break;

		case 3000:
			m_nRetry		= 0;
			m_dwWaitTime[0]	=	GetTickCount();

			strTemp.Format(_T("%c%s%c"), STX, _T("PNGOK"), ETX);
			
			st_client[CLS_GMS].strSend	= strTemp;	
			
			::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + CLS_GMS, CLIENT_SEND, 0);

			m_nCommStep	= 3100;

			break;

		case 3100:
			m_nPngFlag		= FALSE;

			m_dwWaitTime[0] = GetTickCount();

			//::SendMessage(st_handler_info.hWnd, WM_CLIENT_MSG + GMS_NETWORK, CLIENT_CLOSE, 0);

			m_nCommStep = 3200;
			break;

		case 3200:
			m_dwWaitTime[1] = GetTickCount();
			m_dwWaitTime[2] = m_dwWaitTime[1] - m_dwWaitTime[0];

			if (m_dwWaitTime[2] < 0)
			{
				m_dwWaitTime[0] = GetTickCount();
				break;
			}

			if (m_dwWaitTime[2] > WAIT_CLOSE)
			{
				m_nCommStep = 0;
			}
			break;
	}
	return nFunRet;
}

CString CInterfaceGms::OnSyncTime()
{
	CString strData, strTemp;
	CTime	time;
	
	time	= CTime::GetCurrentTime();	
	
	strTemp.Format(_T("TIM  %04d%02d%02d%02d%02d%02d"),	time.GetYear(), time.GetMonth(), time.GetDay(), 
		time.GetHour(), time.GetMinute(), time.GetSecond());
	
	strData.Format(_T("%c%s%c"), STX, strTemp, ETX);
	
	return strData;
}

CString CInterfaceGms::OnAutoSendReq()
{
	CString strData;
	
	strData.Format(_T("%c%s%c"), STX, _T("ASD  "), ETX);
	
	return strData;
}
CString CInterfaceGms::OnDateFormat(CString strDate)
{
	CString strTemp;
	
	strDate.Insert(4, _T("-"));
	strDate.Insert(7, _T("-"));
	strDate.Insert(10, _T(" "));
	strDate.Insert(13, _T(":"));
	strDate.Insert(16, _T(":"));
	
	return strDate;
}
void CInterfaceGms::OnDataReceive(CString strMsg)
{
	int nHead =0;
	int nLength =0;
	int nPos =0;
	int nCh =0;
	int	i = 0;
	
	CString strTemp;
	CString strData;
	CString	strBuff[10];
	CString strLog = _T("");
	
	strMsg.TrimLeft(STX);
	strMsg.TrimRight(ETX);
	
	if (strMsg.GetLength() > 5)
	{
		strData	=	strMsg.Mid(0, 3);
		
		if (strData	==	_T("EOS"))
		{
			for (i=0; i<6; i++)
			{
				AfxExtractSubString(strBuff[i], strMsg, i, _T(','));
			}
			
			nCh			=	atoi(strBuff[2]);
			strTemp		=	OnDateFormat(strBuff[5]);
			st_gms_info.Chan = nCh;
			st_gms_info.strData             =   strData;
			st_gms_info.strEqpID[nCh-1]		=	strBuff[1];
			st_gms_info.strChan[nCh-1]      =   strBuff[2];
			st_gms_info.strValVolt[nCh-1]	=	strBuff[3];
			st_gms_info.strValRes[nCh-1]	=	strBuff[4];
			st_gms_info.strDateTime[nCh-1]	=	strTemp;
			
			strLog.Format("%s",strMsg);
			sprintf(st_msg.c_normal_msg, "%s", strLog);
			if (st_handler.cwnd_list != NULL)
			{
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG); 
			}

			//st_handler_info.cWndFtp->SendMessage(WM_WORK_DISPLAY, nCh-1);
		}
	}
	else
	{
		if (strMsg == _T("EOSOK"))
		{
			m_nTimFlag	=	TRUE;
			m_nAsdFlag	=	FALSE;
		}
		else if (strMsg == _T("ASDOK"))
		{
			m_nAsdFlag	=	TRUE;
		}
		else if (strMsg == _T("PNG  "))
		{
			m_nPngFlag	=	TRUE;
		}
		else
		{
			
		}
	}
	
	strData.Format(_T("[TTS_VNR_NETWORK] %s Receive"), strMsg);
	sprintf( st_msg.c_abnormal_msg, "%s", strData);
	
//	cLOG.OnLogEvent(LOG_SOCKET_, strData);
	st_handler.cwnd_list->SendMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // 동작 실패 출력
}

////////////////

UINT OnInterfaceGmsMessage(LPVOID lParam)
{
	CInterfaceGms *pMsg = (CInterfaceGms *)lParam;

	CString strMsg;
	CString strTemp;
	int		nLength;
	BYTE	byData[100];

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
						if (nLength > 0)
						{
							if (nLength > 100)
							{
								pMsg->m_pCom->Empty();
							}
							else
							{
								pMsg->m_pCom->ReadData(byData, nLength);

								strTemp.Format("%s", byData);
								strMsg	= strTemp.Mid(0, nLength);

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

	return 0;
}


bool CInterfaceGms::OnOpen(int nPort, int nBaudRate, int nParityBit, int nDataBit, int nStopBit, BYTE byEnd)
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
		m_thrHandle		= AfxBeginThread(OnInterfaceGmsMessage, this);

		return true;
	}
	else
	{
		delete m_pCom;
		m_pCom = NULL;
	}

	m_bConnect = false;

	return false;
}


void CInterfaceGms::OnClose()
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

//	AfxMessageBox(_T("End"));

	if (m_pCom != NULL)
	{
		m_pCom->CloseConnection();

		while(m_pCom->idComDev != NULL)
		{
			if (m_pCom->idComDev == NULL) break;

			Sleep(5);
		}

		delete m_pCom;
		m_pCom = NULL;

		m_bConnect = false;
	}
}


void CInterfaceGms::OnDataSend(CString strData)
{
	BYTE byData[100];
	int  nLength = strData.GetLength();

	// com이 연결되어 있지 않으면
	if (m_pCom == NULL) return; 

	m_pCom->Empty(); // com buffer 비우기

//	clsFunc.OnStringToChar(strData, (char*)byData);
	sprintf((char*)byData, strData);
	m_pCom->WriteCommBlock((LPSTR)byData, nLength);
}


void CInterfaceGms::OnDataRevice(CString strData)
{
	int     nLength;  // 데이터 총 길이 저장 변수 
	CString strBody;  // BODY 데이터 저장 변수 
	CString strTemp;
	
	int nChannel;
	double dValue;

	// **************************************************************************
	// 수신 데이터 최소 길이 검사한다 [24자리가 되야 한다.]
	// **************************************************************************
	nLength = strData.GetLength();
	if (nLength != 25) return;		
	// **************************************************************************
	
	strBody = strData.Mid(2, nLength - 3);  // [헤더+테일] 제거 
	strBody.TrimLeft(' ');
	strBody.TrimRight(' ');
	
	strTemp = strBody.Mid(11, 1);			// 채널.
	nChannel = atoi(strTemp);
	
	if (nChannel <= 0) return;

	strTemp = strBody.Mid(12, 5);
	dValue = atof(strTemp);
	
	m_dChann[nChannel-1] = dValue;	// 값을 넣는다.
	
	if (strBody.Mid(12, 2) == "OP")
	{
		m_strChann[nChannel-1] = _T("OPEN");
		m_dChann[nChannel-1] = -99999;	// 값을 넣는다.
	}
	else if (strBody.Mid(12, 2) == "OV")
	{
		m_strChann[nChannel-1] = _T("OVER");
		m_dChann[nChannel-1] = -99998;	// 값을 넣는다.
	}
	else
	{
		m_strChann[nChannel-1].Format(_T("%0.2f"), dValue);
	}

	m_nChann[0] = nChannel + 1;
	if (m_nChann[0] > 5)
	{
		m_nChann[0] = 1;
	}

	if (st_handler.cwnd_list != NULL)  //2010.1027 리스트 바 화면 존재
	{
		sprintf(st_msg.c_normal_msg, "[GMS] Recv_GmsData : %s",strData);
		st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG); 
	}
}

void CInterfaceGms::OnGmsDataCheck()
{
	CString strComm;

	if (m_nChann[0] == m_nChann[1])
	{
		m_dwWaitTime[1] = GetTickCount();
		m_dwWaitTime[2] = m_dwWaitTime[1] - m_dwWaitTime[0];

		if (m_dwWaitTime[2] <= 0)
		{
			m_dwWaitTime[0] = GetTickCount();

			return;
		}

		if (m_dwWaitTime[2] > 5000)
		{
			m_nChann[0] = m_nChann[0] + 1;
			strComm.Format(_T("%c%cP%-8sCH%d %c"), 0x10, 0x02, _T("SAMSUNG1"), m_nChann[0], 0x03);
			OnDataSend(strComm);
			m_dwWaitTime[0] = GetTickCount();
		}

		return;
	}

	m_nChann[1] = m_nChann[0];

	m_dwWaitTime[0] = GetTickCount();

	strComm.Format(_T("%c%cP%-8sCH%d %c"), 0x10, 0x02, _T("SAMSUNG1"), m_nChann[0], 0x03);
	OnDataSend(strComm);
}

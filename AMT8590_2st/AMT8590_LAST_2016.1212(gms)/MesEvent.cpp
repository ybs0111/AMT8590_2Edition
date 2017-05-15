// MesEvent.cpp: implementation of the CMesEvent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MesEvent.h"
#include "AMTLotManager.h"
#include "RunNetwork.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMesEvent	evMes;

CMesEvent::CMesEvent()
{
	// ����� ���� ��ȣ�� (WM_CLIENT_MSG_1)
	// - �迭 ��ȣ�� 0���� �����ϹǷ� (-1)��
	m_nArray = 0;

	// ���̸� ���� [2014.12.13]
	// ���Ͽ��� �о �ش� ���� �����ϵ��� ������
	/*
	// Ŭ���̾�Ʈ ���Ͽ� ���� ��Ʈ �� IP �Ҵ�
	st_client[m_nArray].n_port = 2000;
	st_client[m_nArray].str_ip = "127.0.0.1";
	*/

}

CMesEvent::~CMesEvent()
{
	OnClearMsgQueue();  // �޽��� ���ſ� ť Ŭ����

}

//==================================================================//
// ������ ����
//==================================================================//
void CMesEvent::OnSeq_RUN(void) 
{
	OnSeq_Init();     // ������ ���� ���� �ʱ�ȭ
	OnSeq_Execute();  // ������ ����
}

//==================================================================//
// ������ ���� ���� �ʱ�ȭ
//==================================================================//
void CMesEvent::OnSeq_Init(void) 
{
	if (m_bflag_INIT == true)	{
		return;
	}
	m_bflag_INIT = true;
	
	m_nStep_RUN = 0;	// [����] ���� ����
	
	// ť���� �޽��� �ϳ��� ���� ó�� �� ���
	m_nReqSearch	= CTL_GOOD;	// ť���� �޽��� ã�� �۾� �ʿ�
	m_nExecutedFunc	= 0;	// [����] �ٷ����� ������ �޽��� [Retry �۾��� ���]
	
	//m_sRcvData = "";
	m_sRcvData.Empty();
	
	OnClearMsgQueue();  // �޽��� ���ſ� ť Ŭ����
}

//==================================================================//
// ������ ����
//==================================================================//
void CMesEvent::OnSeq_Execute(void) 
{
	CString sRecvData;
	int nSendFunction;
	int nResp = 0;

	// ť���� ������ �޽����� ã�ƾ� �ϴ� ������� Ȯ��
	if (m_nReqSearch == CTL_GOOD)
	{
		// ť���� �޽����� �ϳ� ����
		nResp = OnGetFromQueue(sRecvData);
		if (nResp == MSG_EXIST)
		{
			nSendFunction	= atoi(sRecvData);	// �޽��� �����ؼ� ������ Id ���� ����
			OnCreate_SendFormat(nSendFunction);	// ������ �޽��� ����
			m_nExecutedFunc	= nSendFunction;	// ���� ������ �޽��� Id ����
			m_nReqStart		= REQ_CALL_;	// [Conv->MES] ������ �޽��� ���� ��û (OnRun_MesWork �Լ����� ����)

			m_nReqSearch = CTL_NO;	// ť���� �޽��� ã�� ��� ���
		}

		// ���̸� ���� [2014.12.13]
		/*
		nResp = OnGetFromQueue(nSendFunction);
		if (nResp == MSG_EXIST)
		{
			OnCreate_SendFormat(nSendFunction);
			m_nExecutedFunc = nSendFunction;

			m_nReqStart = REQ_CALL_;
			m_nReqSearch = CTL_NO;
		}
		*/
	}
	// ���ۿ� ������ �߻��� ��쿡�� Retry ���� ����
	// - �� ó���� ������ ���������� ����ϵ��� ��
	else if (m_nReqSearch == CTL_ERROR)
	{
		// ���̸� �ּ� ó��
		// ��Ʈ���̴� �ش� �Լ��ȿ��� ó���ϵ��� ��
		// - ��� ���� �˶��� ����� �� ���� �Ǿ� ������
		/*
		OnCreate_SendFormat(m_nExecutedFunc);
		
		m_nReqStart = REQ_CALL_;
		m_nReqSearch = CTL_NO;
		*/
		// ���̸� �߰� [2014.12.13]
		m_nReqSearch = CTL_GOOD;	// ť���� ������ �޽����� �ٽ� ã�ƾ� ��
	}

	// [Conv->MES] ������ �޽��� ���� ��û�� �߻��ϱ⸦ ��ٸ�
	if (m_nReqStart == REQ_CALL_)
	{
		OnRun_MesWork();	// [EQP<->MES] �޽��� ���� �� ó��
	}
}

//==================================================================//
// [->ť] ���� �޽��� ����
//==================================================================//
void CMesEvent::OnPutToQueue(int nzData) 
{
	CSingleLock pRecvQLock(&m_csPutQueue);
	pRecvQLock.Lock();
	
	// ���̸� �߰� [2014.12.13]
	// �Էµ� ������ (����->���ڿ�) ��ȯ
	m_sPutData.Format("%d", nzData);
	
	if (m_qReqData.size() == 0)
	{
		OnClearMsgQueue();
	}
	//m_qReqData.push(nzData);
	// ���̸� ���� [2014.12.13]
	m_qReqData.push(m_sPutData);
	
	pRecvQLock.Unlock();
}

//==================================================================//
// [<-ť] ���� �޽��� ������
//==================================================================//
//int CMesEvent::OnGetFromQueue(int &nzData) 
// ���̸� ���� [2014.12.13]
int CMesEvent::OnGetFromQueue(CString &spData) 
{
	CSingleLock pQLock(&m_csGetQueue);
	pQLock.Lock();
	
	int nRet = MSG_EMPTY;
	// ť�� �޽����� �����ϴ��� �˻�
	if (m_qReqData.size() == 0)
	{
		;
	}
	else
	{
		// ť�� ����� �޽��� ����
		//nzData = m_qReqData.front();
		// ���̸� ���� [2014.12.13]
		spData = m_qReqData.front();
		// ��ȯ�� �޽����� ť���� ������
		m_qReqData.pop();
		
		nRet = MSG_EXIST;
	}
	pQLock.Unlock();
	
	return nRet;
}

//==================================================================//
// [EQP<->MES] �޽��� ���� �� ó��
//==================================================================//
int CMesEvent::OnRun_MesWork() 
{
	// [�ʱ�ȭ] �Լ� ���� �÷��� (�۾���)
	int FuncRet = RET_PROCEED;

	CString sMsg;
	switch(m_nStep_RUN)
	{
	case 0:
		// [EQP<->MES] ����Ǿ� �ִ��� Ȯ��
		if (st_client[m_nArray].n_connect == CTL_YES)
		{
// 			m_nStep_RUN = 1000;
			::SendMessage(st_handler.hWnd, WM_CLIENT_MSG +m_nArray, CLIENT_CLOSE, m_nArray);
		}
		// �̿��� �����̸� ���� �۾� �õ�
		else
		{
			::PostMessage(st_handler.hWnd, WM_CLIENT_MSG +m_nArray, CLIENT_CONNECT, m_nArray);

			// ���� ���� �ð� ����
			m_lWaitResp[0] = GetCurrentTime();
			m_nStep_RUN = 100;
		}
		break;

	case 100:
		m_lWaitResp[1] = GetCurrentTime();
		m_lWaitResp[2] = m_lWaitResp[1] - m_lWaitResp[0];
		if (m_lWaitResp[2] < 0)
		{
			m_lWaitResp[0] = GetCurrentTime();
			break;
		}

		if (st_client[m_nArray].n_connect == CTL_YES)
		{
			m_nStep_RUN = 1000;
		}
		else
		{
			if (m_lWaitResp[2] > 5000)
			{
				m_nStep_RUN = 5000;	// ���� ��ȯ ����
			}
		}
		break;

	case 1000:
		// ��� ���� ����
		sMsg = st_client[m_nArray].chSendHead;
		PushSendMsg(sMsg);	// [EQP->LowerStream] �޽��� ����
		// �ٵ� ���� ����
		sMsg = st_client[m_nArray].chSendBody;
		PushSendMsg(sMsg);	// [EQP->LowerStream] �޽��� ����

		m_nIdx = st_client[m_nArray].nIndex;
		// ������ �޽����� ���� ���� ��ٸ� ���� �� ���� ����
		// - [0:default, 1:����, -1:����, 10:��������(��ٸ�), 11:�������]
		if ((st_client[m_nArray].stComm[m_nIdx]).nResponse == 10)
		{
			// Ÿ�Ӿƿ� �˻����� ���� [0:�˻���ʿ�, 1:�˻��ʿ�]
			if ((st_client[m_nArray].stComm[m_nIdx]).nTimeOut == 1)
			{
				//m_nStep_RUN = 1500;
				m_nStep_RUN = 1100;
			}
			else
			{
				//m_nStep_RUN = 1100;
				m_nStep_RUN = 1500;
			}
		}
		else
		{
			m_nStep_RUN = 4000;
		}
		break;

	case 1100:
		// ������ �޽����� ���� ���� üũ ���� �ð� ����
		m_lWaitResp[0] = GetCurrentTime();
		m_nStep_RUN = 1200;
		break;
		
	case 1200:
		m_lWaitResp[1] = GetCurrentTime();
		m_lWaitResp[2] = m_lWaitResp[1] - m_lWaitResp[0];
		if (m_lWaitResp[2] < 0)
		{
			m_lWaitResp[0] = GetCurrentTime();
			break;
		}
		
		// [EQP->MES] ���� �޽��� �Ľ� �Լ����� ������
		
		// ������ �޽����� ���� ���� ��ٸ� ���� �� ���� ����
		// - [0:default, 1:����, -1:����, 10:��������(��ٸ�), 11:�������]
		if ((st_client[m_nArray].stComm[m_nIdx]).nResponse == CTL_GOOD)
		{
			m_nStep_RUN = 4000;
		}
		else if ((st_client[m_nArray].stComm[m_nIdx]).nResponse == CTL_ERROR)
		{
			m_nStep_RUN = 5000;
		}
		else
		{
			// ��� Ÿ�� �ƿ� �߻�
			if (m_lWaitResp[2] > MES_TIME_OUT)
			{
				(st_client[m_nArray].stComm[m_nIdx]).nResponse = CTL_ERROR;
				m_nStep_RUN = 5000;
			}
		}
		break;
		
	case 1500:
		// [EQP->MES] ���� �޽��� �Ľ� �Լ����� ������
		
		// ������ �޽����� ���� ���� ��ٸ� ���� �� ���� ����
		// - [0:default, 1:����, -1:����, 10:��������(��ٸ�), 11:�������]
		if ((st_client[m_nArray].stComm[m_nIdx]).nResponse == CTL_GOOD)
		{
			m_nStep_RUN = 4000;
		}
		else if ((st_client[m_nArray].stComm[m_nIdx]).nResponse == CTL_ERROR)
		{
			m_nStep_RUN = 5000;
		}
		break;
		
		// ���� �Ϸ� ����
	case 4000:
		m_nReqSearch = CTL_GOOD;	// ť���� ������ �޽����� �ٽ� ã�ƾ� ��
		
		m_nReqStart = REPLY_CORRECT_;	// ���������� ����
		m_nStep_RUN = 0;
		FuncRet = RET_GOOD;
		break;
		
		// ���� ��ȯ ����
	case 5000:
		m_nReqSearch = CTL_ERROR;	// ReTry �۾��� �ʿ�
		
		m_nReqStart = REPLY_ERROR_;	// ���信 ���� �߻���
// 		m_nStep_RUN = 0;
// 		FuncRet = RET_ERROR;

		::SendMessage(st_handler.hWnd, WM_CLIENT_MSG +m_nArray, CLIENT_CLOSE, m_nArray);
		m_lWaitResp[0] = GetCurrentTime();
		m_nStep_RUN = 6000;
		break;

	case 6000:
		m_lWaitResp[1] = GetCurrentTime();
		m_lWaitResp[2] = m_lWaitResp[1] - m_lWaitResp[0];
		if (m_lWaitResp[2] < 0)
		{
			m_lWaitResp[0] = GetCurrentTime();
			break;
		}
		else if (m_lWaitResp[2] > 4000)
		{
			m_nStep_RUN = 0;
			FuncRet = RET_ERROR;
		}
		break;
	}
	return FuncRet;
}

//==================================================================//
// [MES->EQP] ���ŵ� �޽��� �����Ͽ� ó��
//==================================================================//
int CMesEvent::OnDivide_FromMES(int nzSocketNo, CString szCommand) 
{
	int nRet = 0;
	
	// ���ŵ� �����Ͱ� ������ ���� ����
	if (szCommand == "")
	{
		return -1;
	}
	// ���ŵ� �޽��� �α׿� ����
	m_sLogMsg.Format("Client_[%02d] Data Receive - %s", nzSocketNo, szCommand);
	cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
	
	CString sPart_Len, sPart_Body, sData_Process;
	int nPart_Len, nPart_Body, nLen_TotRcv;
	
	// ������ ��ɾ��� �ε��� ���� ����
	// - ������ ��ɾ ���� �������� Ȯ���ϱ� ����
	int nIdx = st_client[m_nArray].nIndex;
	
	m_sRcvData += szCommand;	// ���� �޽��� ������Ŵ

	do{
		nLen_TotRcv = m_sRcvData.GetLength();
		// �ּ��� ���̺�+������(1����) �̻��̾�� ��
		if (nLen_TotRcv > 16)
		{
			// �������� ���̺� ���
			sPart_Len = m_sRcvData.Mid(0,16);
			nPart_Len = atoi((LPCSTR)sPart_Len);
			// ���� �����ͺ� ���� ���
			sPart_Body = m_sRcvData.Mid(16);
			nPart_Body = sPart_Body.GetLength();
			
			// �������� ���ռ� �˻�
			// - ���̺��� ���ڰ� ���������� �˻�
			// : ���̺��� ù���ڸ� ����
			// : �� �κ��� ���������� �����Ǿ� �־�� ��
			if (sPart_Len.GetAt(0) >= '0' && sPart_Len.GetAt(0) <= '9')
			{
				// [���̺�+�����ͺ�] ©��
				sData_Process = m_sRcvData.Mid(0, nPart_Len +16);

				if (nPart_Body < nPart_Len)
				{
					nRet = -1;
					break;
				}

				// ���ŵ� �޽��� �߿��� ���� ó���� �޽����� ������ ���ڿ� ����
				// - ���ŵ� �����Ϳ��� ó���� ���ڿ���ŭ ������Ŵ
				// - ó���ϰ� ���� �����͸� ���� ������ ���Ҵ�
				m_sRcvData = m_sRcvData.Mid(nPart_Len +16);
				
				// ������ 2�� ���޾� (�پ) ������ ��� �̰����� ��ٷ� �Ľ��ϴ� �Լ� ȣ���ϸ� ������ �߻���
				// - ó���� ���ŵ� ��ɾ�� ó���Ǵµ� �ڿ� �پ ���ŵ� ��ɾ�� ó������ ���ϰ� ���� ��ɾ� ���ŵ� ��쿡 ó���ǰ� ��
				// - ��, ��ɾ �з��� ó���� �� ����
				// - ������ ���� �޽��� �ǰ�δ� [��ɾ�<->����] �����̹Ƿ� 2�� ��ɾ ���޾� ���ŵ��� �ʾ� ������ ����
				int nResp = OnAnalysis_MesData(sData_Process);
				if (nResp == RET_ERROR)
				{
					//m_sRcvData = "";
					
					// ���� ������ �Ľ� �۾� �� ���� �߻���
					// ������ �޽����� ���� ���� ��ٸ� ���� �� ���� ����
					// - [0:default, 1:����, -1:����, 10:��������(��ٸ�), 11:�������]
					(st_client[m_nArray].stComm[nIdx]).nResponse = CTL_ERROR;
				}
				else if (nResp == RET_GOOD)
				{
					m_sRcvData = "";

					// ���� ������ ���� �Ľ̵�
					// ������ �޽����� ���� ���� ��ٸ� ���� �� ���� ����
					// - [0:default, 1:����, -1:����, 10:��������(��ٸ�), 11:�������]
					(st_client[m_nArray].stComm[nIdx]).nResponse = CTL_GOOD;
				}

				m_sRcvData.Empty();
			}
			else
			{
				// ó���ؾ� �� �Ѱ��� ��ɾ� ���̺��� ���� �������� ���̰� ũ�鼭 ��ɾ� ���信 ������ �ִ� ���
				// - ������ ���۸� ��� ���� ���� �����ͺ��� ó���ǵ��� ��
				if (nPart_Body > nPart_Len)
				{
					// ���ݱ��� ���ŵ� �����ʹ� �����
					// - ���Ŀ� ���ŵǴ� �����ͺ��� ó���ǵ��� ��
					m_sRcvData.Empty();
				}
				// ���ŵ� �����Ͱ� ó�� �Ұ����� ������
				// - ���� ���� �޽����� ó���� ���� ������ ���Ͻ�Ŵ
				nRet = -1;
			}
		}
		// ��ɾ� �ּ� ���� ������ �������� ����
		// - �����͸� �� �����ؾ� ��
		else
		{
			nRet = -1;
		}
    }while (nRet != -1);
	
	return 0;
}

//==================================================================//
// ���ŵ� �޽��� �м� �۾�
//==================================================================//
int CMesEvent::OnAnalysis_MesData(CString szRcvData) 
{
	// ��� ���� ���� [���� �Ǵ� ã�� ���ڿ��� ��ȯ]
	CString sHeader = Func.OnFindInRcvMsg("FUNCTION_RPY=", szRcvData, " ");	// Ư���� ���ڿ� ������ ������ ��ȯ
	CString sBody[40], sTmp;
	int i=0, nChk=0, nLoop=0;

	// �۾� ���� ����
	// [Conv] ���񿡼� ����
	//2016.0915
	if (sHeader == "REWORK_LABEL_CCS")
	{
		// Ư���� ���ڿ� ������ ������ ��ȯ
		sBody[0]	= Func.OnFindInRcvMsg("LOT_ID=",	szRcvData, " ");
		sBody[1]	= Func.OnFindInRcvMsg("EQP_ID=",	szRcvData, " ");
		sBody[2]	= Func.OnFindInRcvMsg("RESULT=",	szRcvData, " ");
		sBody[3]	= Func.OnFindInRcvMsg("MSG=",		szRcvData, "END");
		if(sBody[2] == "PASS")
		{
		}
		else
		{
			if (st_handler.cwnd_list != NULL)
			{
				sprintf( st_msg.c_abnormal_msg, "%s", sBody[3]);
				alarm.mstr_svr_alarm = sBody[3];
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
			}
		}
	}	
	else if (sHeader == "LOT_CLOSE")
	{
		// Ư���� ���ڿ� ������ ������ ��ȯ
		sBody[0]	= Func.OnFindInRcvMsg("LOT_ID=",	szRcvData, " ");
		sBody[1]	= Func.OnFindInRcvMsg("PART_ID=",	szRcvData, " ");
		sBody[2]	= Func.OnFindInRcvMsg("LOT_QTY=",	szRcvData, " ");
		sBody[3]	= Func.OnFindInRcvMsg("TK_CODE=",	szRcvData, " ");
		sBody[4]	= Func.OnFindInRcvMsg("SERIAL=",	szRcvData, " ");
		sBody[5]	= Func.OnFindInRcvMsg("PPID=",		szRcvData, " ");
		sBody[6]	= Func.OnFindInRcvMsg("WWN=",		szRcvData, " ");
		sBody[7]	= Func.OnFindInRcvMsg("C_SERIAL=",	szRcvData, " ");
		sBody[8]	= Func.OnFindInRcvMsg("PSID=",		szRcvData, " ");
		sBody[9]	= Func.OnFindInRcvMsg("RESULT=",	szRcvData, " ");
		sBody[10]	= Func.OnFindInRcvMsg("MSG=",		szRcvData, " ");
	}
	// ������ ���ڵ� ���� üũ (����)
	// [Conv] ���񿡼� ����
	else if (sHeader == "PEBAG_CHECK")
	{
		// Ư���� ���ڿ� ������ ������ ��ȯ
		sBody[0]	= Func.OnFindInRcvMsg("SERIAL=",	szRcvData, " ");
		sBody[1]	= Func.OnFindInRcvMsg("PPID=",		szRcvData, " ");
		sBody[2]	= Func.OnFindInRcvMsg("WWN=",		szRcvData, " ");
		sBody[3]	= Func.OnFindInRcvMsg("C_SERIAL=",	szRcvData, " ");
		sBody[4]	= Func.OnFindInRcvMsg("PSID=",		szRcvData, " ");
		sBody[5]	= Func.OnFindInRcvMsg("RESULT=",	szRcvData, " ");	// (PASS/FAIL)
		sBody[6]	= Func.OnFindInRcvMsg("MSG=",		szRcvData, " ");
	}
	// ������ ���ڵ� ���� üũ (Ʈ���� ����)
	// [Conv] ���񿡼� ����
	else if (sHeader == "BRAND_PEBAG_CHECK")
	{
		// Ư���� ���ڿ� ������ ������ ��ȯ
		sBody[0]	= Func.OnFindInRcvMsg("LOT_ID=",	szRcvData, " ");
		sBody[1]	= Func.OnFindInRcvMsg("RESULT=",	szRcvData, " ");
		sBody[2]	= Func.OnFindInRcvMsg("MSG=",		szRcvData, " ");
		sBody[3]	= Func.OnFindInRcvMsg("SSD_CNT=",	szRcvData, " ");

		nLoop = atoi(sBody[3]);	// �ҷ��� ���� ���� ����
		for(i=0; i<nLoop; i++)
		{
			sTmp.Format("SRL%02d=", i +1);
			sBody[4+ i]	= Func.OnFindInRcvMsg(sTmp,	szRcvData, " ");
		}
	}
	// (PEBAG_CHECK) �Ϸ� ����
	// - �� ������ Ʈ���̿� ���� (PEBAG_CHECK) �Ŀ� ����
	// [Conv] ���񿡼� ����
	else if (sHeader == "PEBAG_COMPLETE")
	{
		// Ư���� ���ڿ� ������ ������ ��ȯ
		sBody[0]	= Func.OnFindInRcvMsg("RESULT=",	szRcvData, " ");
		sBody[1]	= Func.OnFindInRcvMsg("MSG=",		szRcvData, " ");
	}
	//==============================================================//
	// ���� ���񿡼� ���
	//==============================================================//
	// ���񿡼� Id ���� �귯���� ���� ����
	// New->(change)->End �������� ����
	// - New : Id ���ۿ� ���� �������� ���
	// - Change : Id ���۰� ����ǰų� �ش� ���� �ø��� ������ ����� ���
	// - End : �Ϸ� ����� ������� ���
	else if (sHeader == "BOAT_ID_MODIF")
	{
		// Ư���� ���ڿ� ������ ������ ��ȯ
		sBody[0]	= Func.OnFindInRcvMsg("LOT_ID=",		szRcvData, " ");
		sBody[1]	= Func.OnFindInRcvMsg("BOAT_ID=",		szRcvData, " ");
		sBody[2]	= Func.OnFindInRcvMsg("EQP_ID=",		szRcvData, " ");
		sBody[3]	= Func.OnFindInRcvMsg("SERIAL=",		szRcvData, " ");
		sBody[4]	= Func.OnFindInRcvMsg("MODIF_MODE=",	szRcvData, " ");
		sBody[5]	= Func.OnFindInRcvMsg("RESULT=",		szRcvData, " ");
		sBody[6]	= Func.OnFindInRcvMsg("MSG=",			szRcvData, "END");
		if(sBody[5] == "PASS")
		{
		}
		else
		{
			if (st_handler.cwnd_list != NULL)
			{
				sprintf( st_msg.c_abnormal_msg, "%s", sBody[6]);
				alarm.mstr_svr_alarm = sBody[6];
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
			}
		}
	}
	// �۾��� Ȯ�ο�
	// - �ø��� ������ �ƴµ� ���� ������ �� ��쿡 ���
	else if (sHeader == "PROD_SERIAL_INFO")
	{
		// Ư���� ���ڿ� ������ ������ ��ȯ
		sBody[0]	= Func.OnFindInRcvMsg("LOT_ID=",	szRcvData, " ");
		sBody[1]	= Func.OnFindInRcvMsg("BOAT_ID=",	szRcvData, " ");
		sBody[2]	= Func.OnFindInRcvMsg("EQP_ID=",	szRcvData, " ");
		sBody[3]	= Func.OnFindInRcvMsg("SERIAL=",	szRcvData, " ");
		sBody[4]	= Func.OnFindInRcvMsg("PART_ID=",	szRcvData, " ");
		sBody[5]	= Func.OnFindInRcvMsg("RESULT=",	szRcvData, " ");
		sBody[6]	= Func.OnFindInRcvMsg("MSG=",		szRcvData, " ");
	}
	// �۾��� Ȯ�ο�
	// - �ش� ���ۿ� � ���簡 ����ִ��� Ȯ�� �� ���
	else if (sHeader == "BOAT_ID_INFO")
	{
		// Ư���� ���ڿ� ������ ������ ��ȯ
		sBody[0]	= Func.OnFindInRcvMsg("LOT_ID=",	szRcvData, " ");
		sBody[1]	= Func.OnFindInRcvMsg("BOAT_ID=",	szRcvData, " ");
		sBody[2]	= Func.OnFindInRcvMsg("EQP_ID=",	szRcvData, " ");
		sBody[3]	= Func.OnFindInRcvMsg("SERIAL=",	szRcvData, " ");
		sBody[4]	= Func.OnFindInRcvMsg("PART_ID=",	szRcvData, " ");
		sBody[5]	= Func.OnFindInRcvMsg("RESULT=",	szRcvData, " ");
		sBody[6]	= Func.OnFindInRcvMsg("MSG=",		szRcvData, "END");
		if(sBody[5] == "PASS")
		{
		}
		else
		{
			if (st_handler.cwnd_list != NULL)
			{
				sprintf( st_msg.c_abnormal_msg, "%s", sBody[6]);
				alarm.mstr_svr_alarm = sBody[6];
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
			}
		}
	}
	// ���񿡼� ������ ������ ����Ǹ� ����
	else if (sHeader == "TOOL_CHANGE")
	{
		// Ư���� ���ڿ� ������ ������ ��ȯ
		sBody[0]	= Func.OnFindInRcvMsg("EQP_ID=",	szRcvData, " ");
		sBody[1]	= Func.OnFindInRcvMsg("TOOLID=",	szRcvData, " ");
		sBody[2]	= Func.OnFindInRcvMsg("RESULT=",	szRcvData, " ");
		sBody[3]	= Func.OnFindInRcvMsg("MSG=",		szRcvData, " ");
	}
	// TMS ������ ����� ���� ���� Ȯ��
	// - ������ �����ǿ� ������ ������ ���ϱ� ���Ͽ� ���� ó�� ���� �� ȣ��
	else if (sHeader == "TOOL_CHECK")
	{
		// Ư���� ���ڿ� ������ ������ ��ȯ
		sBody[0]	= Func.OnFindInRcvMsg("EQP_ID=",			szRcvData, " ");
		sBody[1]	= Func.OnFindInRcvMsg("CURRENT_TOOL_ID=",	szRcvData, " ");
		sBody[2]	= Func.OnFindInRcvMsg("PART_TOOL_ID=",		szRcvData, " ");
		sBody[3]	= Func.OnFindInRcvMsg("RESULT=",			szRcvData, " ");
		sBody[4]	= Func.OnFindInRcvMsg("MSG=",				szRcvData, " ");
	}
	//==============================================================//
	// �ʿ��ϸ� �ƹ����� ��� ����
	// (LOT_ID/SERIAL) ���� �� ���� �ϳ��� ��û
	// - �����ϴ� ������ �Է��ϰ� �������� �������� �����ϸ� ��
	// [Conv] ���񿡼� ����
	else if (sHeader == "PACKING_MASTER_INFO")
	{
		// Ư���� ���ڿ� ������ ������ ��ȯ
		sBody[0]	= Func.OnFindInRcvMsg("LOT_ID=",				szRcvData, " ");
		sBody[1]	= Func.OnFindInRcvMsg("PART_ID=",				szRcvData, " ");
		sBody[2]	= Func.OnFindInRcvMsg("LOT_STEP=",				szRcvData, " ");
		sBody[3]	= Func.OnFindInRcvMsg("LOT_QTY=",				szRcvData, " ");
		sBody[4]	= Func.OnFindInRcvMsg("S_BOX_MOQ=",				szRcvData, " ");
		sBody[5]	= Func.OnFindInRcvMsg("L_BOX_MOQ=",				szRcvData, " ");
		sBody[6]	= Func.OnFindInRcvMsg("PRODUCT_NAME=",			szRcvData, " ");
		sBody[7]	= Func.OnFindInRcvMsg("SSD_SIZE_X=",			szRcvData, " ");
		sBody[8]	= Func.OnFindInRcvMsg("SSD_SIZE_Y=",			szRcvData, " ");
		sBody[9]	= Func.OnFindInRcvMsg("TK_CODE=",				szRcvData, " ");
		// �߰���
		sBody[10]	= Func.OnFindInRcvMsg("TK_BOX_LENGTH=",			szRcvData, " ");
		sBody[11]	= Func.OnFindInRcvMsg("TK_BOX_WIDTH=",			szRcvData, " ");
		sBody[12]	= Func.OnFindInRcvMsg("TK_BOX_HEIGHT=",			szRcvData, " ");
		sBody[13]	= Func.OnFindInRcvMsg("TRAY_HEIGHT=",			szRcvData, " ");
		sBody[14]	= Func.OnFindInRcvMsg("TRAY_MARKING=",			szRcvData, " ");
		sBody[15]	= Func.OnFindInRcvMsg("TRAY_ARRAY_X=",			szRcvData, " ");
		sBody[16]	= Func.OnFindInRcvMsg("TRAY_ARRAY_Y=",			szRcvData, " ");
		sBody[17]	= Func.OnFindInRcvMsg("POCKET_PITCH_X=",		szRcvData, " ");
		sBody[18]	= Func.OnFindInRcvMsg("POCKET_PITCH_Y=",		szRcvData, " ");
		sBody[19]	= Func.OnFindInRcvMsg("ACCE_MAT_CODE=",			szRcvData, " ");
		sBody[20]	= Func.OnFindInRcvMsg("INNER_BOX_MAT_CODE=",	szRcvData, " ");
		sBody[21]	= Func.OnFindInRcvMsg("INNER_BOX_LENGTH=",		szRcvData, " ");
		sBody[22]	= Func.OnFindInRcvMsg("INNER_BOX_WIDTH=",		szRcvData, " ");
		sBody[23]	= Func.OnFindInRcvMsg("INNER_BOX_HEIGHT=",		szRcvData, " ");
		sBody[24]	= Func.OnFindInRcvMsg("DTBT_LABEL_MAT_CODE=",	szRcvData, " ");
		sBody[25]	= Func.OnFindInRcvMsg("PP_BAND_MAT_CODE=",		szRcvData, " ");
		sBody[26]	= Func.OnFindInRcvMsg("PP_BAND_SPEC_NO=",		szRcvData, " ");
		sBody[27]	= Func.OnFindInRcvMsg("TAPE_MAT_CODE=",			szRcvData, " ");
		sBody[28]	= Func.OnFindInRcvMsg("TAPE_SPEC_NO=",			szRcvData, " ");
		sBody[29]	= Func.OnFindInRcvMsg("EMPTY_BOX_MAT_CODE=",	szRcvData, " ");
		sBody[30]	= Func.OnFindInRcvMsg("EMPTY_BOX_SPEC_NO=",		szRcvData, " ");
		sBody[31]	= Func.OnFindInRcvMsg("RIBBON_MAT_CODE=",		szRcvData, " ");
		sBody[32]	= Func.OnFindInRcvMsg("DENSITY_LABEL_MAT_CODE=",	szRcvData, " ");
		sBody[33]	= Func.OnFindInRcvMsg("DENSITY_LABEL_VALUE=",	szRcvData, " ");
		sBody[34]	= Func.OnFindInRcvMsg("RESULT=",				szRcvData, " ");
		sBody[35]	= Func.OnFindInRcvMsg("MSG=",					szRcvData, " ");


		bool bLot = false;
		for ( int i = 0; i < g_lotMgr.GetLotCount(); i++)
		{
			if(g_lotMgr.GetLotAt(i).GetLotID() == sBody[0])
			{
				bLot = true;
				break;
			}
		}
		
		if( bLot == false )
		{
			g_lotMgr.OnNewLotIn(sBody[0], sBody[1]);
			g_lotMgr.GetLotByLotID(sBody[0]).SetMdlCapa( sBody[1].Mid(5,3) + "GB" );
			st_basic.mstr_device_name.MakeUpper();
			int aa = st_basic.mstr_device_name.Find(".TXT", 0);
			if( aa <= 0 )
			{ 
				if (st_handler.cwnd_list != NULL)
				{
					sprintf( st_msg.c_abnormal_msg, "%s can't find (.txt). check device name please", st_basic.mstr_device_name);
					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
				}
				return RET_ERROR;
			}
			CString strname = st_basic.mstr_device_name;
			strname.Replace(".TXT", "");

			////2015.0714
			st_work.m_strCurModel = strname;
			////

			//if(sBody[6] == "2.5") strname = "25INCH";

// 			g_lotMgr.GetLotByLotID(sBody[0]).SetLabelVisionModel( strname, ("_" + g_lotMgr.GetLotByLotID(sBody[0]).GetMdlCapa()) );
// 			
// 			if(sBody[1].GetAt(15) == 'A')//Only UPC Exist //America
// 			{
// 				if(g_lotMgr.GetLotByLotID(sBody[0]).GetMdlCapa() == _T("128GB") || 
// 					g_lotMgr.GetLotByLotID(sBody[0]).GetMdlCapa() == _T("256GB") ||
// 					g_lotMgr.GetLotByLotID(sBody[0]).GetMdlCapa() == _T("512GB"))
// 				{
// 					strname = "25INCHPRO";
// 				}
// 
// 				g_lotMgr.GetLotByLotID(sBody[0]).SetUpcEanType(true,false);
// 				g_lotMgr.GetLotByLotID(sBody[0]).SetTBtmVisionModel( strname, "_UPC" );
// 			}
// 			else if(sBody[1].GetAt(15) == 'E' || sBody[1].GetAt(15) == 'C' || sBody[1].GetAt(15) == 'K')//Europe,China,Korea Only EAN Exist
// 			{
// 				if(g_lotMgr.GetLotByLotID(sBody[0]).GetMdlCapa() == _T("128GB") || 
// 					g_lotMgr.GetLotByLotID(sBody[0]).GetMdlCapa() == _T("256GB") ||
// 					g_lotMgr.GetLotByLotID(sBody[0]).GetMdlCapa() == _T("512GB"))
// 				{
// 					strname = "25INCHPRO";
// 				}
// 				g_lotMgr.GetLotByLotID(sBody[0]).SetUpcEanType(false,true);	
// 				if(sBody[1].GetAt(15) == 'C')//china
// 				{
// 					g_lotMgr.GetLotByLotID(sBody[0]).SetTBtmVisionModel( strname, "_CHINA" );
// 				}
// 				else if(sBody[1].GetAt(15) == 'K')//china
// 				{
// 					g_lotMgr.GetLotByLotID(sBody[0]).SetTBtmVisionModel( strname, "_KOREA" );
// 				}
// 				else
// 				{
// 					g_lotMgr.GetLotByLotID(sBody[0]).SetTBtmVisionModel( strname, "" );
// 				}
// 			}
// 			else//Both of them exist
// 			{
// 				if(g_lotMgr.GetLotByLotID(sBody[0]).GetMdlCapa() == _T("128GB") || 
// 					g_lotMgr.GetLotByLotID(sBody[0]).GetMdlCapa() == _T("256GB") ||
// 					g_lotMgr.GetLotByLotID(sBody[0]).GetMdlCapa() == _T("512GB"))
// 				{
// 					strname = "25INCHPRO";
// 				}
// 				g_lotMgr.GetLotByLotID(sBody[0]).SetUpcEanType(true,true);
// 				g_lotMgr.GetLotByLotID(sBody[0]).SetTBtmVisionModel( strname, "" );
// 			}
			g_lotMgr.OnNewLotIn(sBody[0], sBody[1]);
			g_lotMgr.GetLotByLotID(sBody[0]).SetProductName(sBody[6]);
			g_lotMgr.GetLotByLotID(sBody[0]).SetLotEnd("NO");
			g_lotMgr.GetLotByLotID(sBody[0]).SetLotTime();
			g_lotMgr.GetLotByLotID(sBody[0]).SetDisLabelCode( sBody[24] );
			g_lotMgr.GetLotByLotID(sBody[0]).SetRibbonCode( sBody[31] );
			g_lotMgr.GetLotByLotID(sBody[0]).SetTotalModule( sBody[3] );
			g_lotMgr.GetLotByLotID(sBody[0]).SetDenLabelCode( sBody[32] );
			g_lotMgr.GetLotByLotID(sBody[0]).SetDenLabelCapa(sBody[33]);
		}

	}
	// Lot�� ������ �־� ���� �� �ݵ�� ����
	// [Conv] ���񿡼� ����
	else if (sHeader == "PK_XCLOSE")
	{
		// Ư���� ���ڿ� ������ ������ ��ȯ
		sBody[0]	= Func.OnFindInRcvMsg("LOT_ID=",	szRcvData, " ");
		sBody[1]	= Func.OnFindInRcvMsg("EQP_ID=",	szRcvData, " ");
		sBody[2]	= Func.OnFindInRcvMsg("RESULT=",	szRcvData, " ");
		sBody[3]	= Func.OnFindInRcvMsg("MSG=",		szRcvData, "END");
		if(sBody[2] == "PASS")
		{
		}
		else
		{
			if (st_handler.cwnd_list != NULL)
			{
				sprintf( st_msg.c_abnormal_msg, "%s", sBody[3]);
				alarm.mstr_svr_alarm = sBody[3];
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
			}
			return RET_ERROR;			
		}
	}
	else if (sHeader == "BRAND_DENSITY_LABEL_CCS")
	{
		// Ư���� ���ڿ� ������ ������ ��ȯ
		sBody[0]	= Func.OnFindInRcvMsg("LOT_ID=",	szRcvData, " ");
		sBody[1]	= Func.OnFindInRcvMsg("EQP_ID=",	szRcvData, " ");
		sBody[2]	= Func.OnFindInRcvMsg("RESULT=",	szRcvData, " ");
		sBody[3]	= Func.OnFindInRcvMsg("MSG=",		szRcvData, "END");
		if(sBody[2] == "PASS")
		{
		}
		else
		{
			if (st_handler.cwnd_list != NULL)
			{
				sprintf( st_msg.c_abnormal_msg, "%s", sBody[3]);
				alarm.mstr_svr_alarm = sBody[3];
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
			}
		}
	}
	else if (sHeader == "BRAND_DTBT_LABEL_CCS")
	{
		// Ư���� ���ڿ� ������ ������ ��ȯ
		sBody[0]	= Func.OnFindInRcvMsg("LOT_ID=",	szRcvData, " ");
		sBody[1]	= Func.OnFindInRcvMsg("EQP_ID=",	szRcvData, " ");
		sBody[2]	= Func.OnFindInRcvMsg("RESULT=",	szRcvData, " ");
		sBody[3]	= Func.OnFindInRcvMsg("MSG=",		szRcvData, "END");
		if(sBody[2] == "PASS")
		{
		}
		else
		{
			if (st_handler.cwnd_list != NULL)
			{
				sprintf( st_msg.c_abnormal_msg, "%s", sBody[3]);
				alarm.mstr_svr_alarm = sBody[3];
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
			}
		}
	}
	else if (sHeader == "BRAND_DTBT_LABEL_ISSUE")
	{
		sBody[0]	= Func.OnFindInRcvMsg("LOT_ID=",	szRcvData, " ");
		sBody[1]	= Func.OnFindInRcvMsg("EQP_ID=",	szRcvData, " ");
		sBody[2]	= Func.OnFindInRcvMsg("RESULT=",	szRcvData, " ");
		sBody[3]	= Func.OnFindInRcvMsg("SERIAL=",	szRcvData, " ");
		sBody[4]	= Func.OnFindInRcvMsg("MSG=",		szRcvData, "END");

		CString strSerialID = Func.OnBodyAnalysis( 0, szRcvData, "SERIAL");
		CString strFormat = Func.OnBodyAnalysis( 3, szRcvData, "FORMAT");
		if(sBody[2] == "PASS")
		{
			if(sBody[3] == g_RunNetwork.st_barcodenet[CTL_LEFT].m_cSerial/*st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_serial[CTL_LEFT]*/)
			{
				ClrSerial( CTL_LEFT );
				ClrBcrFormat( CTL_LEFT );
				SetSerial( CTL_LEFT, sBody[3] );
				SetBcrFormat( CTL_LEFT, strFormat );
			}
			else if(sBody[3] == g_RunNetwork.st_barcodenet[CTL_RIGHT].m_cSerial/*st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_serial[CTL_RIGHT]*/)
			{
				ClrSerial( CTL_RIGHT );
				ClrBcrFormat( CTL_RIGHT );
				SetSerial( CTL_RIGHT, sBody[3] );
				SetBcrFormat( CTL_RIGHT, strFormat );				
			}
			else
			{

				return RET_ERROR;
			}
		}
		else
		{
			if (st_handler.cwnd_list != NULL)
			{
				sprintf( st_msg.c_abnormal_msg, "%s", sBody[4]);
				alarm.mstr_svr_alarm = sBody[4];
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
			}
			return RET_ERROR;

		}
	}
// 	else if (sHeader == "BRAND_DTBT_LABEL_ISSUE_R_")
// 	{
// 		sBody[0]	= Func.OnFindInRcvMsg("LOT_ID=",	szRcvData, " ");
// 		sBody[1]	= Func.OnFindInRcvMsg("EQP_ID=",	szRcvData, " ");
// 		sBody[2]	= Func.OnFindInRcvMsg("RESULT=",	szRcvData, " ");
// 		sBody[3]	= Func.OnFindInRcvMsg("MSG=",		szRcvData, " ");
// 		CString strSerialID = Func.OnBodyAnalysis( 0, szRcvData, "SERIAL");
// 		CString strFormat = Func.OnBodyAnalysis( 3, szRcvData, "FORMAT");
// 		SetSerial( CTL_RIGHT, strSerialID );
// 		SetBcrFormat( CTL_RIGHT, strFormat );
// 	}
	else
	{
		return RET_ERROR;
	}
	return RET_GOOD;
}

//==================================================================//
// [EQP->MES] �޽��� ����
//==================================================================//
int CMesEvent::PushSendMsg(CString szMsg) 
{
	// ������ ���ڿ� ����
	sprintf(st_client[m_nArray].ch_send, szMsg);
	::SendMessage(st_handler.hWnd, WM_CLIENT_MSG +m_nArray, CLIENT_SEND, m_nArray);
	
	return 0;
}

//==================================================================//
// [EQP->TMS] ������ �޽��� ����
//==================================================================//
void CMesEvent::OnCreate_SendFormat(int nzIdx) 
{
	CString sFunction;
	CString sHead = "", sBody = "", sTemp = "", sSRL = "";
	int i, nLoop;
	// ���̸� �߰� [2014.12.14]
	CString sLotId, sBoatId, sSerial, sTboxid, sAcceid, sDensityid;

	// ���̸� �߰� [2014.11.11]
	// - ����� �߰��� ���� ���� ���� ��� ������� ��찡 �־� �߰���
	m_nStep_RUN = 0;

	switch(nzIdx)
	{
	case MES_REWORK_LABEL_CCS_INFO:
		sBody.Format("FUNCTION=REWORK_LABEL_CCS EQP_ID=%s SERIAL=%s DENSITY_MATL_CODE=%s TURNKEYBOX_MATL_CODE=%s OPER_ID=%s ",
			st_lamp.mstr_equip_id, st_mes_data.srt_SERIAL, st_mes_data.srt_DEN_LABEL_MAT_CODE, st_mes_data.srt_TURMKEY_BOX_CODE,"AUTO");
		sHead.Format("%016d ", sBody.GetLength());
		sprintf(st_client[m_nArray].chSendHead, sHead);
		sprintf(st_client[m_nArray].chSendBody, sBody);
		
		// ��� ���� �⺻ ���� ����
		st_client[m_nArray].nIndex = nzIdx;
		sFunction = "REWORK_LABEL_CCS_INFO";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chSendCmd, sFunction);
		sFunction = "REWORK_LABEL_CCS_INFO";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chResponse, sFunction);
		(st_client[m_nArray].stComm[nzIdx]).nEcho		= 11;
		(st_client[m_nArray].stComm[nzIdx]).nResponse	= 10;
		(st_client[m_nArray].stComm[nzIdx]).nTimeOut	= 1;
		break;

		// �۾� ���� ����
		// [Conv] ���񿡼� ����
	case MES_LOT_CLOSE:
		sBody.Format("FUNCTION=LOT_CLOSE LOT_ID=%s OPER_ID=%s GATE=%s RETRY=%s RETRY_CNT=%s ",
			st_mes_data.srt_LOT_ID, "AUTO", st_mes_data.srt_GATE, st_mes_data.srt_RETRY, st_mes_data.srt_RETRY_CNT);
		sHead.Format("%016d ", sBody.GetLength());
		sprintf(st_client[m_nArray].chSendHead, sHead);
		sprintf(st_client[m_nArray].chSendBody, sBody);

		// ��� ���� �⺻ ���� ����
		st_client[m_nArray].nIndex = nzIdx;
		sFunction = "LOT_CLOSE";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chSendCmd, sFunction);
		sFunction = "LOT_CLOSE";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chResponse, sFunction);
		(st_client[m_nArray].stComm[nzIdx]).nEcho		= 11;
		(st_client[m_nArray].stComm[nzIdx]).nResponse	= 10;
		(st_client[m_nArray].stComm[nzIdx]).nTimeOut	= 1;
		break;

		// ������ ���ڵ� ���� üũ (����)
		// [Conv] ���񿡼� ����
	case MES_PEBAG_CHECK:
		sBody.Format("FUNCTION=PEBAG_CHECK LOT_ID=%s SERIAL=%s PPID=%s WWN=%s C_SERIAL=%s PSID=%s RETRY=%s RETRY_CNT=%s ",
			st_mes_data.srt_LOT_ID, st_mes_data.srt_SERIAL, st_mes_data.srt_PPID, st_mes_data.srt_WWN, st_mes_data.srt_C_SERIAL, st_mes_data.srt_PSID, st_mes_data.srt_RETRY, st_mes_data.srt_RETRY_CNT);
		sHead.Format("%016d ", sBody.GetLength());
		sprintf(st_client[m_nArray].chSendHead, sHead);
		sprintf(st_client[m_nArray].chSendBody, sBody);

		// ��� ���� �⺻ ���� ����
		st_client[m_nArray].nIndex = nzIdx;
		sFunction = "PEBAG_CHECK";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chSendCmd, sFunction);
		sFunction = "PEBAG_CHECK";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chResponse, sFunction);
		(st_client[m_nArray].stComm[nzIdx]).nEcho		= 11;
		(st_client[m_nArray].stComm[nzIdx]).nResponse	= 10;
		(st_client[m_nArray].stComm[nzIdx]).nTimeOut	= 1;
		break;

		// ������ ���ڵ� ���� üũ (Ʈ���� ����)
		// [Conv] ���񿡼� ����
	case MES_BRAND_PEBAG_CHECK:
		sBody.Format("FUNCTION=BRAND_PEBAG_CHECK LOT_ID=%s SSD_CNT=%s ",
			st_mes_data.srt_LOT_ID, st_mes_data.srt_SSD_CNT);
		// ���� ������ŭ �ݺ�
		nLoop = atoi(st_mes_data.srt_SSD_CNT);
		for(i=0; i<nLoop; i++)
		{
			sBody += st_mes_data.srt_SRL[i];
		}
		sTemp.Format("RETRY=%s RETRY_CNT=%s ",
			st_mes_data.srt_RETRY, st_mes_data.srt_RETRY_CNT);
		sBody += sTemp;
		sHead.Format("%016d ", sBody.GetLength());
		sprintf(st_client[m_nArray].chSendHead, sHead);
		sprintf(st_client[m_nArray].chSendBody, sBody);

		// ��� ���� �⺻ ���� ����
		st_client[m_nArray].nIndex = nzIdx;
		sFunction = "BRAND_PEBAG_CHECK";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chSendCmd, sFunction);
		sFunction = "BRAND_PEBAG_CHECK";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chResponse, sFunction);
		(st_client[m_nArray].stComm[nzIdx]).nEcho		= 11;
		(st_client[m_nArray].stComm[nzIdx]).nResponse	= 10;
		(st_client[m_nArray].stComm[nzIdx]).nTimeOut	= 1;
		break;

		// (PEBAG_CHECK) �Ϸ� ����
		// - �� ������ Ʈ���̿� ���� (PEBAG_CHECK) �Ŀ� ����
		// [Conv] ���񿡼� ����
	case MES_PEBAG_COMPLETE:
		sBody.Format("FUNCTION=PEBAG_COMPLETE LOT_ID=%s RETRY=%s RETRY_CNT=%s ",
			st_mes_data.srt_LOT_ID, st_mes_data.srt_RETRY, st_mes_data.srt_RETRY_CNT);
		sHead.Format("%016d ", sBody.GetLength());
		sprintf(st_client[m_nArray].chSendHead, sHead);
		sprintf(st_client[m_nArray].chSendBody, sBody);

		// ��� ���� �⺻ ���� ����
		st_client[m_nArray].nIndex = nzIdx;
		sFunction = "PEBAG_COMPLETE";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chSendCmd, sFunction);
		sFunction = "PEBAG_COMPLETE";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chResponse, sFunction);
		(st_client[m_nArray].stComm[nzIdx]).nEcho		= 11;
		(st_client[m_nArray].stComm[nzIdx]).nResponse	= 10;
		(st_client[m_nArray].stComm[nzIdx]).nTimeOut	= 1;
		break;

		//==========================================================//
		// ���� ���񿡼� ���
		//==========================================================//
		// ���񿡼� Id ���� �귯���� ���� ����
		// New->(change)->End �������� ����
		// - New : Id ���ۿ� ���� �������� ���
		// - Change : Id ���۰� ����ǰų� �ش� ���� �ø��� ������ ����� ���
		// - End : �Ϸ� ����� ������� ���
	case MES_BOAT_ID_MODIF:
		sBody.Format("FUNCTION=BOAT_ID_MODIF LOT_ID=%s BOAT_ID=%s EQP_ID=%s SERIAL=%s MODIF_MODE=%s RETRY=%s RETRY_CNT=%s ",
			st_mes_data.srt_LOT_ID, st_mes_data.srt_BOAT_ID, st_lamp.mstr_equip_id, st_mes_data.srt_SERIAL, st_mes_data.srt_MODIF_MODE, st_mes_data.srt_RETRY, st_mes_data.srt_RETRY_CNT);
		sHead.Format("%016d ", sBody.GetLength());
		sprintf(st_client[m_nArray].chSendHead, sHead);
		sprintf(st_client[m_nArray].chSendBody, sBody);

		// ��� ���� �⺻ ���� ����
		st_client[m_nArray].nIndex = nzIdx;
		sFunction = "BOAT_ID_MODIF";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chSendCmd, sFunction);
		sFunction = "BOAT_ID_MODIF";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chResponse, sFunction);
		(st_client[m_nArray].stComm[nzIdx]).nEcho		= 11;
		(st_client[m_nArray].stComm[nzIdx]).nResponse	= 10;
		(st_client[m_nArray].stComm[nzIdx]).nTimeOut	= 1;
		break;

		// ���̸� �߰� [2014.12.14]
	case MES_BOAT_ID_MODIF_LIN_:
		sLotId.Format("%s",		st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_lot_id[CTL_LEFT]);
		sBoatId.Format("%d",	st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_idbuff_num[CTL_LEFT]);
		sSerial.Format("%s",	st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_serial[CTL_LEFT]);

		sBody.Format("FUNCTION=BOAT_ID_MODIF LOT_ID=%s BOAT_ID=%s EQP_ID=%s SERIAL=%s MODIF_MODE=NEW RETRY=NO RETRY_CNT=0 ",
			sLotId, sBoatId, st_lamp.mstr_equip_id, sSerial);
		sHead.Format("%016d ", sBody.GetLength());
		sprintf(st_client[m_nArray].chSendHead, sHead);
		sprintf(st_client[m_nArray].chSendBody, sBody);

		// ��� ���� �⺻ ���� ����
		st_client[m_nArray].nIndex = nzIdx;
		sFunction = "BOAT_ID_MODIF";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chSendCmd, sFunction);
		sFunction = "BOAT_ID_MODIF";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chResponse, sFunction);
		(st_client[m_nArray].stComm[nzIdx]).nEcho		= 11;
		(st_client[m_nArray].stComm[nzIdx]).nResponse	= 10;
		(st_client[m_nArray].stComm[nzIdx]).nTimeOut	= 1;
		break;

	case MES_BOAT_ID_MODIF_RIN_:
		sLotId.Format("%s",		st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_lot_id[CTL_RIGHT]);
		sBoatId.Format("%d",	st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_idbuff_num[CTL_RIGHT]);
		sSerial.Format("%s",	st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_serial[CTL_RIGHT]);
		
		sBody.Format("FUNCTION=BOAT_ID_MODIF LOT_ID=%s BOAT_ID=%s EQP_ID=%s SERIAL=%s MODIF_MODE=NEW RETRY=NO RETRY_CNT=0 ",
			sLotId, sBoatId, st_lamp.mstr_equip_id, sSerial);
		sHead.Format("%016d ", sBody.GetLength());
		sprintf(st_client[m_nArray].chSendHead, sHead);
		sprintf(st_client[m_nArray].chSendBody, sBody);
		
		// ��� ���� �⺻ ���� ����
		st_client[m_nArray].nIndex = nzIdx;
		sFunction = "BOAT_ID_MODIF";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chSendCmd, sFunction);
		sFunction = "BOAT_ID_MODIF";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chResponse, sFunction);
		(st_client[m_nArray].stComm[nzIdx]).nEcho		= 11;
		(st_client[m_nArray].stComm[nzIdx]).nResponse	= 10;
		(st_client[m_nArray].stComm[nzIdx]).nTimeOut	= 1;
		break;

	case MES_BOAT_ID_MODIF_LOUT_:
		sLotId.Format("%s",		st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD].c_lot_id[CTL_LEFT]);
		sBoatId.Format("%d",	st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD].n_idbuff_num[CTL_LEFT]);
		sSerial.Format("%s",	st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD].c_serial[CTL_LEFT]);
		
		sBody.Format("FUNCTION=BOAT_ID_MODIF LOT_ID=%s BOAT_ID=%s EQP_ID=%s SERIAL=%s MODIF_MODE=END RETRY=NO RETRY_CNT=0 ",
			sLotId, sBoatId, st_lamp.mstr_equip_id, sSerial);
		sHead.Format("%016d ", sBody.GetLength());
		sprintf(st_client[m_nArray].chSendHead, sHead);
		sprintf(st_client[m_nArray].chSendBody, sBody);
		
		// ��� ���� �⺻ ���� ����
		st_client[m_nArray].nIndex = nzIdx;
		sFunction = "BOAT_ID_MODIF";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chSendCmd, sFunction);
		sFunction = "BOAT_ID_MODIF";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chResponse, sFunction);
		(st_client[m_nArray].stComm[nzIdx]).nEcho		= 11;
		(st_client[m_nArray].stComm[nzIdx]).nResponse	= 10;
		(st_client[m_nArray].stComm[nzIdx]).nTimeOut	= 1;
		break;
		
	case MES_BOAT_ID_MODIF_ROUT_:
		sLotId.Format("%s",		st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD].c_lot_id[CTL_RIGHT]);
		sBoatId.Format("%d",	st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD].n_idbuff_num[CTL_RIGHT]);
		sSerial.Format("%s",	st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD].c_serial[CTL_RIGHT]);
		
		sBody.Format("FUNCTION=BOAT_ID_MODIF LOT_ID=%s BOAT_ID=%s EQP_ID=%s SERIAL=%s MODIF_MODE=END RETRY=NO RETRY_CNT=0 ",
			sLotId, sBoatId, st_lamp.mstr_equip_id, sSerial);
		sHead.Format("%016d ", sBody.GetLength());
		sprintf(st_client[m_nArray].chSendHead, sHead);
		sprintf(st_client[m_nArray].chSendBody, sBody);
		
		// ��� ���� �⺻ ���� ����
		st_client[m_nArray].nIndex = nzIdx;
		sFunction = "BOAT_ID_MODIF";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chSendCmd, sFunction);
		sFunction = "BOAT_ID_MODIF";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chResponse, sFunction);
		(st_client[m_nArray].stComm[nzIdx]).nEcho		= 11;
		(st_client[m_nArray].stComm[nzIdx]).nResponse	= 10;
		(st_client[m_nArray].stComm[nzIdx]).nTimeOut	= 1;
		break;

		// �۾��� Ȯ�ο�
		// - �ø��� ������ �ƴµ� ���� ������ �� ��쿡 ���
	case MES_PROD_SERIAL_INFO:
		sBody.Format("FUNCTION=PROD_SERIAL_INFO EQP_ID=%s SERIAL=%s RETRY=%s RETRY_CNT=%s ",
			st_lamp.mstr_equip_id, st_mes_data.srt_SERIAL, st_mes_data.srt_RETRY, st_mes_data.srt_RETRY_CNT);
		sHead.Format("%016d ", sBody.GetLength());
		sprintf(st_client[m_nArray].chSendHead, sHead);
		sprintf(st_client[m_nArray].chSendBody, sBody);

		// ��� ���� �⺻ ���� ����
		st_client[m_nArray].nIndex = nzIdx;
		sFunction = "PROD_SERIAL_INFO";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chSendCmd, sFunction);
		sFunction = "PROD_SERIAL_INFO";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chResponse, sFunction);
		(st_client[m_nArray].stComm[nzIdx]).nEcho		= 11;
		(st_client[m_nArray].stComm[nzIdx]).nResponse	= 10;
		(st_client[m_nArray].stComm[nzIdx]).nTimeOut	= 1;
		break;

		// �۾��� Ȯ�ο�
		// - �ش� ���ۿ� � ���簡 ����ִ��� Ȯ�� �� ���
	case MES_BOAT_ID_INFO:
		sBody.Format("FUNCTION=BOAT_ID_INFO BOAT_ID=%s EQP_ID=%s RETRY=%s RETRY_CNT=%s ",
			st_mes_data.srt_BOAT_ID, st_lamp.mstr_equip_id, st_mes_data.srt_RETRY, st_mes_data.srt_RETRY_CNT);
		sHead.Format("%016d ", sBody.GetLength());
		sprintf(st_client[m_nArray].chSendHead, sHead);
		sprintf(st_client[m_nArray].chSendBody, sBody);

		// ��� ���� �⺻ ���� ����
		st_client[m_nArray].nIndex = nzIdx;
		sFunction = "BOAT_ID_INFO";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chSendCmd, sFunction);
		sFunction = "BOAT_ID_INFO";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chResponse, sFunction);
		(st_client[m_nArray].stComm[nzIdx]).nEcho		= 11;
		(st_client[m_nArray].stComm[nzIdx]).nResponse	= 10;
		(st_client[m_nArray].stComm[nzIdx]).nTimeOut	= 1;
		break;

		// ���񿡼� ������ ������ ����Ǹ� ����
	case MES_TOOL_CHANGE:
		sBody.Format("FUNCTION=TOOL_CHANGE EQP_ID=%s TOOLID=%s RETRY=%s RETRY_CNT=%s ",
			st_lamp.mstr_equip_id, st_mes_data.srt_TOOLID, st_mes_data.srt_RETRY, st_mes_data.srt_RETRY_CNT);
		sHead.Format("%016d ", sBody.GetLength());
		sprintf(st_client[m_nArray].chSendHead, sHead);
		sprintf(st_client[m_nArray].chSendBody, sBody);
		
		// ��� ���� �⺻ ���� ����
		st_client[m_nArray].nIndex = nzIdx;
		sFunction = "TOOL_CHANGE";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chSendCmd, sFunction);
		sFunction = "TOOL_CHANGE";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chResponse, sFunction);
		(st_client[m_nArray].stComm[nzIdx]).nEcho		= 11;
		(st_client[m_nArray].stComm[nzIdx]).nResponse	= 10;
		(st_client[m_nArray].stComm[nzIdx]).nTimeOut	= 1;
		break;
		
		// TMS ������ ����� ���� ���� Ȯ��
		// - ������ �����ǿ� ������ ������ ���ϱ� ���Ͽ� ���� ó�� ���� �� ȣ��
	case MES_TOOL_CHECK:
		sBody.Format("FUNCTION=TOOL_CHECK EQP_ID=%s LOT_ID=%s RETRY=%s RETRY_CNT=%s ",
			st_lamp.mstr_equip_id, st_mes_data.srt_LOT_ID, st_mes_data.srt_RETRY, st_mes_data.srt_RETRY_CNT);
		sHead.Format("%016d ", sBody.GetLength());
		sprintf(st_client[m_nArray].chSendHead, sHead);
		sprintf(st_client[m_nArray].chSendBody, sBody);
		
		// ��� ���� �⺻ ���� ����
		st_client[m_nArray].nIndex = nzIdx;
		sFunction = "TOOL_CHECK";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chSendCmd, sFunction);
		sFunction = "TOOL_CHECK";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chResponse, sFunction);
		(st_client[m_nArray].stComm[nzIdx]).nEcho		= 11;
		(st_client[m_nArray].stComm[nzIdx]).nResponse	= 10;
		(st_client[m_nArray].stComm[nzIdx]).nTimeOut	= 1;
		break;
		//==========================================================//

		// �ʿ��ϸ� �ƹ����� ��� ����
		// (LOT_ID/SERIAL) ���� �� ���� �ϳ��� ��û
		// - �����ϴ� ������ �Է��ϰ� �������� �������� �����ϸ� ��
		// [Conv] ���񿡼� ����
	case MES_PACKING_MASTER_INFO:
		sBody.Format("FUNCTION=PACKING_MASTER_INFO LOT_ID=%s SERIAL=%s RETRY=%s RETRY_CNT=%s ",
			st_mes_data.srt_LOT_ID, st_mes_data.srt_SERIAL, st_mes_data.srt_RETRY, st_mes_data.srt_RETRY_CNT);
		sHead.Format("%016d ", sBody.GetLength());
		sprintf(st_client[m_nArray].chSendHead, sHead);
		sprintf(st_client[m_nArray].chSendBody, sBody);

		// ��� ���� �⺻ ���� ����
		st_client[m_nArray].nIndex = nzIdx;
		sFunction = "PACKING_MASTER_INFO";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chSendCmd, sFunction);
		sFunction = "PACKING_MASTER_INFO";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chResponse, sFunction);
		(st_client[m_nArray].stComm[nzIdx]).nEcho		= 11;
		(st_client[m_nArray].stComm[nzIdx]).nResponse	= 10;
		(st_client[m_nArray].stComm[nzIdx]).nTimeOut	= 1;
		break;

		// Lot�� ������ �־� ���� �� �ݵ�� ����
		// [Conv] ���񿡼� ����
	case MES_PK_XCLOSE:
		sBody.Format("FUNCTION=PK_XCLOSE LOT_ID=%s OPER_ID=%s EQP_ID=%s RETRY=%s RETRY_CNT=%s ",
			st_mes_data.srt_LOT_ID, "AUTO", st_lamp.mstr_equip_id, st_mes_data.srt_RETRY, st_mes_data.srt_RETRY_CNT);
		sHead.Format("%016d ", sBody.GetLength());
		sprintf(st_client[m_nArray].chSendHead, sHead);
		sprintf(st_client[m_nArray].chSendBody, sBody);

		// ��� ���� �⺻ ���� ����
		st_client[m_nArray].nIndex = nzIdx;
		sFunction = "PK_XCLOSE";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chSendCmd, sFunction);
		sFunction = "PK_XCLOSE";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chResponse, sFunction);
		(st_client[m_nArray].stComm[nzIdx]).nEcho		= 11;
		(st_client[m_nArray].stComm[nzIdx]).nResponse	= 10;
		(st_client[m_nArray].stComm[nzIdx]).nTimeOut	= 1;
		break;

	case MES_BRAND_DENSITY_LABEL_CCS:
		sBody.Format("FUNCTION=BRAND_DENSITY_LABEL_CCS LOT_ID=%s BOAT_ID=%s EQP_ID=%s SERIAL=%s DEN_LABEL_MAT_CODE=%s  RETRY=NO RETRY_CNT=0 ",
			st_mes_data.srt_LOT_ID, st_mes_data.srt_BOAT_ID, st_lamp.mstr_equip_id, st_mes_data.srt_C_SERIAL, st_mes_data.srt_DEN_LABEL_MAT_CODE);//, st_mes_data.srt_RETRY, st_mes_data.srt_RETRY_CNT);
		sHead.Format("%016d ", sBody.GetLength());
		sprintf(st_client[m_nArray].chSendHead, sHead);
		sprintf(st_client[m_nArray].chSendBody, sBody);
		
		// ��� ���� �⺻ ���� ����
		st_client[m_nArray].nIndex = nzIdx;
		sFunction = "BRAND_DENSITY_LABEL_CCS";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chSendCmd, sFunction);
		sFunction = "BRAND_DENSITY_LABEL_CCS";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chResponse, sFunction);
		(st_client[m_nArray].stComm[nzIdx]).nEcho		= 11;
		(st_client[m_nArray].stComm[nzIdx]).nResponse	= 10;
		(st_client[m_nArray].stComm[nzIdx]).nTimeOut	= 1;
		break;

	case MES_BRAND_DTBT_LABEL_CCS:
		sBody.Format("FUNCTION=BRAND_DTBT_LABEL_CCS LOT_ID=%s BOAT_ID=%s EQP_ID=%s SERIAL=%s DTBT_MAT_CODE=%s RIBBON_MAT_CODE=%s RETRY=NO RETRY_CNT=0 ",
			st_mes_data.srt_LOT_ID, st_mes_data.srt_BOAT_ID, st_lamp.mstr_equip_id, st_mes_data.srt_C_SERIAL, st_mes_data.srt_DTBT_MAT_CODE, st_mes_data.srt_RIBBON_MAT_CODE);//, st_mes_data.srt_RETRY, st_mes_data.srt_RETRY_CNT);
		sHead.Format("%016d ", sBody.GetLength());
		sprintf(st_client[m_nArray].chSendHead, sHead);
		sprintf(st_client[m_nArray].chSendBody, sBody);
		
		// ��� ���� �⺻ ���� ����
		st_client[m_nArray].nIndex = nzIdx;
		sFunction = "BRAND_DTBT_LABEL_CCS";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chSendCmd, sFunction);
		sFunction = "BRAND_DTBT_LABEL_CCS";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chResponse, sFunction);
		(st_client[m_nArray].stComm[nzIdx]).nEcho		= 11;
		(st_client[m_nArray].stComm[nzIdx]).nResponse	= 10;
		(st_client[m_nArray].stComm[nzIdx]).nTimeOut	= 1;
		break;

	case MES_BRAND_DTBT_LABEL_ISSUE_L_:
// 		sLotId.Format("%s",		st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_lot_id[CTL_LEFT]);
// 		sBoatId.Format("%d",	st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_idbuff_num[CTL_LEFT]);
// 		sSerial.Format("%s",	st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_serial[CTL_LEFT]);
		sLotId.Format("%s",		g_RunNetwork.st_barcodenet[CTL_LEFT].m_cLotid);
		sBoatId.Format("%s",	g_RunNetwork.st_barcodenet[CTL_LEFT].m_cBoatid);
		sSerial.Format("%s",	g_RunNetwork.st_barcodenet[CTL_LEFT].m_cSerial);
		sDensityid.Format("%s",	g_RunNetwork.st_barcodenet[CTL_LEFT].m_cDencode);
		sTboxid.Format("%s",	g_RunNetwork.st_barcodenet[CTL_LEFT].m_cTboxcode);
		sAcceid.Format("%s",	g_RunNetwork.st_barcodenet[CTL_LEFT].m_cAccecode);

// 		sBody.Format("FUNCTION=BRAND_DTBT_LABEL_ISSUE LOT_ID=%s BOAT_ID=%s EQP_ID=%s SERIAL=%s DTBT_LABEL_CODE=%s DTBT_RIBBON_CODE=%s MODE=YES RETRY=%s RETRY_CNT=%s ",
// 			sLotId, sBoatId, st_lamp.mstr_equip_id, sSerial, st_mes_data.srt_DTBT_LABEL_CODE, st_mes_data.srt_DTBT_RIBBON_CODE, st_mes_data.srt_RETRY, st_mes_data.srt_RETRY_CNT);
//2015.0322		
		sBody.Format("FUNCTION=BRAND_DTBT_LABEL_ISSUE LOT_ID=%s BOAT_ID=%s EQP_ID=%s SERIAL=%s DTBT_LABEL_CODE=%s DTBT_RIBBON_CODE=%s DENS_CODE=%s TURNKEY_CODE=%s TRAY_CODE=%s MODE=YES RETRY=%s RETRY_CNT=%s ",
			sLotId, sBoatId, st_lamp.mstr_equip_id, sSerial, st_mes_data.srt_DTBT_LABEL_CODE, st_mes_data.srt_DTBT_RIBBON_CODE, sDensityid, sTboxid, sAcceid, st_mes_data.srt_RETRY, st_mes_data.srt_RETRY_CNT);
		
		sHead.Format("%016d ", sBody.GetLength());
		sprintf(st_client[m_nArray].chSendHead, sHead);
		sprintf(st_client[m_nArray].chSendBody, sBody);
		
		// ��� ���� �⺻ ���� ����
		st_client[m_nArray].nIndex = nzIdx;
		sFunction = "BRAND_DTBT_LABEL_ISSUE";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chSendCmd, sFunction);
		sFunction = "BRAND_DTBT_LABEL_ISSUE";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chResponse, sFunction);
		(st_client[m_nArray].stComm[nzIdx]).nEcho		= 11;
		(st_client[m_nArray].stComm[nzIdx]).nResponse	= 10;
		(st_client[m_nArray].stComm[nzIdx]).nTimeOut	= 1;
		break;

	case MES_BRAND_DTBT_LABEL_ISSUE_R_:
// 		sLotId.Format("%s",		st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_lot_id[CTL_RIGHT]);
// 		sBoatId.Format("%d",	st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].n_idbuff_num[CTL_RIGHT]);
// 		sSerial.Format("%s",	st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD_RECV].c_serial[CTL_RIGHT]);
		sLotId.Format("%s",		g_RunNetwork.st_barcodenet[CTL_RIGHT].m_cLotid);
		sBoatId.Format("%s",	g_RunNetwork.st_barcodenet[CTL_RIGHT].m_cBoatid);
		sSerial.Format("%s",	g_RunNetwork.st_barcodenet[CTL_RIGHT].m_cSerial);
		sDensityid.Format("%s",	g_RunNetwork.st_barcodenet[CTL_RIGHT].m_cDencode);
		sTboxid.Format("%s",	g_RunNetwork.st_barcodenet[CTL_RIGHT].m_cTboxcode);
		sAcceid.Format("%s",	g_RunNetwork.st_barcodenet[CTL_RIGHT].m_cAccecode);

		
// 		sBody.Format("FUNCTION=BRAND_DTBT_LABEL_ISSUE LOT_ID=%s BOAT_ID=%s EQP_ID=%s SERIAL=%s DTBT_LABEL_CODE=%s DTBT_RIBBON_CODE=%s MODE=YES RETRY=%s RETRY_CNT=%s ",
// 			sLotId, sBoatId, st_lamp.mstr_equip_id, sSerial, st_mes_data.srt_DTBT_LABEL_CODE, st_mes_data.srt_DTBT_RIBBON_CODE, st_mes_data.srt_RETRY, st_mes_data.srt_RETRY_CNT);

//2015.0322	
		sBody.Format("FUNCTION=BRAND_DTBT_LABEL_ISSUE LOT_ID=%s BOAT_ID=%s EQP_ID=%s SERIAL=%s DTBT_LABEL_CODE=%s DTBT_RIBBON_CODE=%s DENS_CODE=%s TURNKEY_CODE=%s TRAY_CODE=%s MODE=YES RETRY=%s RETRY_CNT=%s ",
			sLotId, sBoatId, st_lamp.mstr_equip_id, sSerial, st_mes_data.srt_DTBT_LABEL_CODE, st_mes_data.srt_DTBT_RIBBON_CODE, sDensityid, sTboxid, sAcceid, st_mes_data.srt_RETRY, st_mes_data.srt_RETRY_CNT);
		
		sHead.Format("%016d ", sBody.GetLength());
		sprintf(st_client[m_nArray].chSendHead, sHead);
		sprintf(st_client[m_nArray].chSendBody, sBody);
		
		// ��� ���� �⺻ ���� ����
		st_client[m_nArray].nIndex = nzIdx;
		sFunction = "BRAND_DTBT_LABEL_ISSUE";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chSendCmd, sFunction);
		sFunction = "BRAND_DTBT_LABEL_ISSUE";
		sprintf((st_client[m_nArray].stComm[nzIdx]).chResponse, sFunction);
		(st_client[m_nArray].stComm[nzIdx]).nEcho		= 11;
		(st_client[m_nArray].stComm[nzIdx]).nResponse	= 10;
		(st_client[m_nArray].stComm[nzIdx]).nTimeOut	= 1;
		break;	
	}
}

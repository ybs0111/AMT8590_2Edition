// CimEvent.cpp: implementation of the CCimEvent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CimEvent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCimEvent	g_client_cim;

CCimEvent::CCimEvent()
{
	// ���Ͽ� ���� ����ü �迭 ����
	m_nArrayPos = 1;

	//m_sRcvData = "";
	m_sRcvData.Empty();

}

CCimEvent::~CCimEvent()
{
	OnClearMsgQueue();  // �޽��� ���ſ� ť Ŭ����

}

//==================================================================//
// ������ ����
//==================================================================//
void CCimEvent::OnSeq_RUN(void) 
{
	OnSeq_INIT();     // ������ ���� ���� �ʱ�ȭ
	OnSeq_Execute();  // ������ ����
}

//==================================================================//
// ������ ���� ���� �ʱ�ȭ
//==================================================================//
void CCimEvent::OnSeq_INIT(void) 
{
	if (m_bflag_INIT == true)	{
		return;
	}
	m_bflag_INIT = true;

	OnClearMsgQueue();  // �޽��� ���ſ� ť Ŭ����
}

//==================================================================//
// ������ ����
//==================================================================//
void CCimEvent::OnSeq_Execute(void) 
{
	CString sRecvData;
	int nResp = 0;

	// [EQP<->CIM} ����� ��쿡�� �޽��� ������ ó����
	if (st_client[m_nArrayPos].n_connect == CTL_YES)
	{
		// ť���� �޽��� �ϳ��� ����
		nResp = OnGetFromQueue(sRecvData);
		if (nResp == MSG_EXIST)
		{
			m_sLogMsg.Format("[Process Start] : %s", sRecvData);
			Func.On_LogFile_Add(99, m_sLogMsg);

			// ť���� ���� �޽��� ó����
			OnParseComplete((LPCSTR)sRecvData);  // CIM���� ���� �޽��� �Ľ�
		}
	}
}

//==================================================================//
// [->ť] ���� �޽��� ����
//==================================================================//
void CCimEvent::OnPutToQueue(CString szData) 
{
	CSingleLock pRecvQLock(&m_csPutQueue);
	pRecvQLock.Lock();

	if (m_qReqData.size() == 0)
	{
		OnClearMsgQueue();
	}
	m_qReqData.push(szData);

	pRecvQLock.Unlock();
}

//==================================================================//
// [<-ť] ���ŵ� �޽��� ������
//==================================================================//
int CCimEvent::OnGetFromQueue(CString &spData) 
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
		spData = m_qReqData.front();
		// ��ȯ�� �޽����� ť���� ������
		m_qReqData.pop();

		nRet = MSG_EXIST;
	}
	pQLock.Unlock();

	return nRet;
}

//==================================================================//
// [MES->CIM] ���ŵ� �޽��� �����Ͽ� ó��
//==================================================================//
int CCimEvent::OnDivide_FromCIM(int nzSocketNo, CString szCommand) 
{
	int nRet = 0;
	
	// ���ŵ� �����Ͱ� ������ ���� ����
	if (szCommand == "")
	{
		return -1;
	}
	// ���ŵ� �޽��� �α׿� ����
	m_sLogMsg.Format("Client_[%02d] Data Receive - %s", nzSocketNo, szCommand);
	Func.On_LogFile_Add(99, m_sLogMsg);
	
	// ���ŵ� �޽��� ������Ŵ
	// - ���� ��� (HD=000025,FUNC=INTERFACE,CONNECT=0,)
	m_sRcvData += szCommand;

	int nLen_TotRcv;
	CString sPart_Head, sPart_Len, sPart_Body, sData_Process;
	int nPart_Len = -1, nPart_Body = -1;

	do{
		// ���� ���ŵ� ���ڿ� ���� ���
		nLen_TotRcv = m_sRcvData.GetLength();

		// ���� �޽����� �ּ� ���� �˻�
		// - Mid() �Լ� ��� �� ���ڰ����� 0�� ���Ǹ� ���� ������ �� �ܿ��� ���� �߻���
		// : ���� ���ڿ��� Mid(0,?)�� ��� ������ Mid(4,?)�� ������ �߻���
		if (nLen_TotRcv > 10)
		{
			// �������� ����� ��� [ ���� ��� (HD=) ]
			sPart_Head	= m_sRcvData.Mid(0,3);
			// �������� ���̺� ��� [���� ��� (000025) ]
			sPart_Len	= m_sRcvData.Mid(3,6);
			// ������ �������� ���� ���� ����
			nPart_Len	= atoi((LPCSTR)sPart_Len);
			// ���� �����ͺ� ��� [ ���� ��� (FUNC=INTERFACE,CONNECT=0,) ]
			sPart_Body	= m_sRcvData.Mid(10);
			// Body(������) ���� ����
			nPart_Body	= sPart_Body.GetLength();

			// �������� ���ռ� �˻�
			// - ����� ���ڿ� �˻�
			// - ���̺��� ���ڰ� ���������� �˻�
			// : ���̺��� ù���ڸ� ����
			// : �� �κ��� ���������� �����Ǿ� �־�� ��
			if (sPart_Head == "HD=" &&
				m_sRcvData.GetAt(3) >= '0' && m_sRcvData.GetAt(3) <= '9')
			{
				// ������ �������� ���� ������ ������ ������ Ȯ��
				// - ������ �������� ���̴� �ּ� 1���� �̻��� �Ǿ�� ��
				if (nPart_Len < 1)
				{
					m_sRcvData.Empty();
					nRet = -1;
				}
				// ������ ���ڿ� ���̰� ����� ������ ���ڿ����� ũ��
				// - ��� �����͸� �����ؾ� �ϹǷ� �ϴ� ������
				if (nPart_Body < nPart_Len)
				{
					nRet = -1;
				}
				// ������ �ִ� ��쿡�� �ش� �޽����� ó������ ����
				if (nRet != 0)
				{
					break;
				}

				// ���� ������ [ó�� ����]
				// [���(9����)+��ɾ��] ���ڿ� ����
				sData_Process = m_sRcvData.Mid(0, nPart_Len +10);
				// ���� ���ŵ� ���ڿ� ���� ����
				nLen_TotRcv = sData_Process.GetLength();
				// ó���ϱ� ���� �̾Ƴ� �����ʹ� ������
				// - ���ŵ� �����Ϳ��� ó���� ���ڿ���ŭ ������Ŵ
				// - ó���ϰ� ���� �����͸� ���� ������ ���Ҵ�
				m_sRcvData = m_sRcvData.Mid(nLen_TotRcv);

				// �ϳ��� ��ɾ ť�� ����
				OnPutToQueue(sData_Process);
			}
			else
			{
				// ó���ؾ� �� �Ѱ��� ��ɾ� ���̺��� ���� �������� ���̰� ũ�鼭 ��ɾ� ���信 ������ �ִ� ���
				// - ������ ���۸� ��� ���� ���� �����ͺ��� ó���ǵ��� ��
				if (nPart_Body >= nPart_Len)
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
    }while(nRet != -1);

	return 0;
}

void CCimEvent::OnParseComplete(std::string strRecv) 
{
	// ó���� �޽����� �����̸� ������ ���Ͻ�Ŵ
	if (strRecv == "")
	{
		return;
	}

	// ó���� ��ɾ� ���� Ȯ��
	CString sFunc = OnPickOut_RcvMsg("FUNC", (LPCSTR)strRecv.c_str());

	// [CEID] : [EQ->HOST]���� ������ �޽����� ���� ����
	// [RCMD] : [HOST->EQ]���� ������ ����
	if (sFunc == "RCMD")
	{
		CString sRCMD = OnPickOut_RcvMsg("RCMD_NUM", (LPCSTR)strRecv.c_str());

		// �̰��� RCMD�� ���� ���� ���α׷� �۾�
		if (sRCMD == "_RCMD_BBAR")
		{

		}
	}
	// [HOS->EQP] ��Ʈ�� ��� ����
	else if (sFunc == "INTERFACE")
	{
		OnReceived_Interface(strRecv);
	}
	// [EQ->CIM->EQ] ��Ʈ�� ��忡 ���� ����
	else if (sFunc == "OPERATE")
	{
		OnReceived_Operate(strRecv);
	}
	// ���̸� �߰� [2013.09.25]
	// [CIM<->HOST] ���� ���� ����
	else if (sFunc == "HCON")
	{
		OnReceived_HCON(strRecv);	// [CIM<->HOST] ���� ���� ���� ����
	}
}

//==================================================================//
// [HOS->EQP] ��Ʈ�� ��� ����
//==================================================================//
void CCimEvent::OnReceived_Interface(std::string strRecv) 
{
	CString sFunc = OnPickOut_RcvMsg("CONNECT", (LPCSTR)strRecv.c_str());

	if (sFunc == "0")	// OFF LINE
	{
		st_work.nEQ_CtrlMode = MC_OFF_LINE;
	}
	else if (sFunc == "1")	// ONLINE LOCAL
	{
		st_work.nEQ_CtrlMode = MC_ON_LINE_LOCAL;
	}
	else if (sFunc == "2")	// ONLINE REMOTE
	{
		st_work.nEQ_CtrlMode = MC_ON_LINE_REMOTE;
	}

	// [0/1/2] �̿��� ���� ���͵� �ϴ� ����� ����� ������ ó����
	if (m_eWR == EWR_INTERFACE)	{
		m_eWR = EWR_NONE;
	}
}

//==================================================================//
// [EQ->CIM->EQ] ��Ʈ�� ��忡 ���� ���� ó��
// - [EQ<->CIM] ������ ���� ���� ���θ� ��Ʈ�� ��忡 ���� �������� ������
// : OFFLINE������ �޽����� ������ �ʿ䰡 ���� ������
// : ����� �ʿ� ������ ������� �ʾƵ� ��
//==================================================================//
void CCimEvent::OnReceived_Operate(std::string strRecv) 
{
	CString sFunc = OnPickOut_RcvMsg("CONNECT", (LPCSTR)strRecv.c_str());
	
	if (sFunc == "0")	// OFF LINE
	{
		st_handler.nEQ2CIM_SendPpossible = 1;
	}
	else if (sFunc == "1")	// ONLINE LOCAL
	{
		//st_handler.nEQ2CIM_SendPpossible = 1;
		// ���̸� ���� [2013.09.01]
		st_handler.nEQ2CIM_SendPpossible = 2;
	}
	else if (sFunc == "2")	// ONLINE REMOTE
	{
		st_handler.nEQ2CIM_SendPpossible = 2;
	}

	if (m_eWR == EWR_OPERATE)	{
		m_eWR = EWR_NONE;
	}
}

//==================================================================//
// [CIM<->HOST] ���� ���� ����
//==================================================================//
void CCimEvent::OnReceived_HCON(std::string strRecv) 
{
	CString sFunc = OnPickOut_RcvMsg("CONNECT", (LPCSTR)strRecv.c_str());
	
	// [CIM<->HOST] ���� ���� ���� [�̿���]
	if (sFunc == "0")
	{
		st_work.nLink_CIM2TMS = CTL_NO;
	}
	// [CIM<->HOST] ���� ���� ���� [����]
	else if (sFunc == "1")
	{
		st_work.nLink_CIM2TMS = CTL_YES;
	}

	if (m_eWR == EWR_HCON)	{
		m_eWR = EWR_NONE;
	}
}


//==================================================================//
// ���ϴ� ������ ������ �� ��ȯ
// ���̸� �߰� [2013.07.31]
// - int nzMidPos : �߶� ���ڿ�
// : ���� ���, ( "CONNECT=" ) ���� szLetter ���̸� nzMidPos ���� ( 8 ) ��
// - CString szLetter    : �˻縦 ������ ���� ���ڿ�
// - CString szSeparator : �˻縦 ������ ���� ���ڿ�
// - CString szRcvMsg    : �˻��� ���ڿ�
//==================================================================//
CString CCimEvent::OnAnalysisRcvMSG(int nzMidPos, CString szLetter, CString szSeparator, CString szRcvMsg, int nzMode) 
{
	int nPos[2], nLength;
	CString sFindVal = "";

	int nSkipPos;
	if (nzMode == 1)
	{
		nSkipPos = nzMidPos;
	}
	else
	{
		// ����� ������ ���ڿ� ���̴� [ã�����ڿ� ����] - [,]��
		// ���� ��� [RETURN_FLAG,OK] �����̸� ���� ���ϴ� �����ʹ� [OK] ��
		// �̷� ������ (+1) ����
		nSkipPos = nzMidPos+1;
	}

	nPos[0] = szRcvMsg.Find(szLetter, 0);
	nPos[1] = szRcvMsg.Find(szSeparator, nPos[0]);
	nLength = (nPos[1] - nPos[0]) - nSkipPos;
	if (nLength < 1)
	{
		// ���� ���ڿ� ��ȯ��Ŵ
		return sFindVal;
	}
	
	sFindVal = szRcvMsg.Mid(nPos[0]+nSkipPos, nLength);
	return sFindVal;
}

//==================================================================//
// [EQP->CIM] �޽��� ����
//==================================================================//
int CCimEvent::PushSendMsg(CString szMsg) 
{
	// ������ ���ڿ� ����
	sprintf(st_client[m_nArrayPos].ch_send, szMsg);

	// [EQP->CIM] �޽��� ���� ��û��
	//::PostMessage(st_handler.hWnd, WM_CLIENT_MSG_2, CLIENT_SEND, m_nArrayPos);
// 	::SendMessage(st_handler.hWnd, WM_CLIENT_MSG_2, CLIENT_SEND, m_nArrayPos);
	return 0;
}

//==================================================================//
// Ư���� ���ڿ� ������ ������ ��ȯ
// - szOrg : ���� ��� (HD=000025,FUNC=INTERFACE,CONNECT=0,)
//==================================================================//
CString CCimEvent::OnPickOut_RcvMsg(CString szFind, CString szOrg) 
{
	// �˻��� ���ڿ� ���� ����
	CString sFindChar;
	sFindChar  = szFind;
	sFindChar += "=";
	
	// ��ü ���ڿ����� ã���� �ϴ� ���ڿ��� �˻���
	int nFind	= szOrg.Find(sFindChar);
	// ������ ������ ������ ��ġ �˻���
	// - ã���� �ϴ� ���ڿ��� ���� ��ġ���� ã�� ������
	int nEnd	= szOrg.Find(",", nFind+1);
	
	if (nFind < 0 || nEnd < 0 ||
		nEnd <= (nFind + sFindChar.GetLength()))
	{
		return "";
	}
	
	CString sSearchChar;
	sSearchChar = szOrg.Mid(nFind + sFindChar.GetLength(), nEnd - (nFind + sFindChar.GetLength()));
	
	return sSearchChar;
}

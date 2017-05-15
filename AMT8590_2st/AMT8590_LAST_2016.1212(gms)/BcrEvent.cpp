// BcrEvent.cpp: implementation of the CBcrEvent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BcrEvent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CBcrEvent	evBCR;

CBcrEvent::CBcrEvent()
{

}

CBcrEvent::~CBcrEvent()
{

}

//==================================================================//
// ������ ����
//==================================================================//
void CBcrEvent::OnSeq_RUN(void) 
{
	OnSeq_INIT();     // ������ ���� ���� �ʱ�ȭ
	OnSeq_Execute();  // ������ ����
}

//==================================================================//
// ������ ���� ���� �ʱ�ȭ
//==================================================================//
void CBcrEvent::OnSeq_INIT(void) 
{
	if (m_bflag_INIT == true)	{
		return;
	}
	m_bflag_INIT = true;
	
	// ���� ���� �ʱ�ȭ
	m_nStep_LSSD	= 0;
	m_nStep_RSSD	= 0;
	m_nStep_TRIN	= 0;
	m_nStep_TROUT	= 0;

	int i=0;
	for(i=0; i<MAX_PORT; i++)
	{
		m_sRcvedData[i].Empty();	// ���� �޽��� ���� �ʱ�ȭ
	}
}

//==================================================================//
// ������ ����
//==================================================================//
void CBcrEvent::OnSeq_Execute(void) 
{
	if (m_nReq_LSSD == REQ_CALL_)
	{
		OnRun_LSSD();
	}
	else if (m_nReq_RSSD == REQ_CALL_)
	{
		OnRun_RSSD();
	}
	else if (m_nReq_TRIN == REQ_CALL_ ||
		m_nReq_TRIN == REQ_STOP_)
	{
		OnRun_TRIN();
	}
	else if (m_nReq_TROUT == REQ_CALL_ ||
		m_nReq_TROUT == REQ_STOP_)
	{
		OnRun_TROUT();
	}
}

int CBcrEvent::OnRun_LSSD() 
{
	// [�ʱ�ȭ] �Լ� ���� �÷��� (�۾���)
	int FuncRet = RET_PROCEED;

	CString sTemp;

	switch(m_nStep_LSSD)
	{
	case 0:
		// BCR �б� ��û ����
		::PostMessage(st_handler.hWnd, WM_DATA_SEND, PORT_BCR_LSSD_, 0);

		// st_serial.n_rec_chk[nzPort -1]	= FALSE;
		// �� �κ��� ���� �����ӿ��� �޽��� �����ϸ鼭 �����ϰ� ��
		// - OnSend_BcrRead() �Լ� ����
		// �޽��� ���� ���� �ð� ����
		m_lWait_LSSD[0] = GetCurrentTime();
		m_nStep_LSSD = 1100;
		break;

	case 1100:
		// ������ ��ٸ�
		if (st_serial.mn_rec_chk[PORT_BCR_LSSD_ -1] == CTL_YES)
		{
			sTemp = st_serial.mcomm_rec[PORT_BCR_LSSD_ -1];
			// �б� �۾� �����ߴ��� �˻�
			if (sTemp == "No-Read")
			{
				m_nStep_LSSD = 5000;	// ���� ��ȯ ����
			}
			else
			{
				m_nStep_LSSD = 4000;
			}
		}
		else
		{
			m_lWait_LSSD[1] = GetCurrentTime();
			m_lWait_LSSD[2] = m_lWait_LSSD[1] - m_lWait_LSSD[0];
			if (m_lWait_LSSD[2] < 0)
			{
				m_lWait_LSSD[0] = GetCurrentTime();
				break;
			}
			
			// 2�� ���� ��ٸ�
			if (m_lWait_LSSD[2] > 2000)
			{
				m_nStep_LSSD = 5000;	// ���� ��ȯ ����
			}
		}
		break;

	case 4000:
		m_nReq_LSSD	= REPLY_CORRECT_;
		
		m_nStep_LSSD = 0;
		FuncRet = RET_GOOD;
		break;
		
		// ���� ��ȯ ����
	case 5000:
		m_nReq_LSSD	= REPLY_ERROR_;
		
		m_nStep_LSSD = 0;
		FuncRet = RET_ERROR;
		break;
	}
	return FuncRet;
}

int CBcrEvent::OnRun_RSSD() 
{
	// [�ʱ�ȭ] �Լ� ���� �÷��� (�۾���)
	int FuncRet = RET_PROCEED;
	
	CString sTemp;
	
	switch(m_nStep_RSSD)
	{
	case 0:
		// BCR �б� ��û ����
		::PostMessage(st_handler.hWnd, WM_DATA_SEND, PORT_BCR_RSSD_, 0);
		
		// st_serial.n_rec_chk[nzPort -1]	= FALSE;
		// �� �κ��� ���� �����ӿ��� �޽��� �����ϸ鼭 �����ϰ� ��
		// - OnSend_BcrRead() �Լ� ����
		// �޽��� ���� ���� �ð� ����
		m_lWait_RSSD[0] = GetCurrentTime();
		m_nStep_RSSD = 1100;
		break;
		
	case 1100:
		// ������ ��ٸ�
		if (st_serial.mn_rec_chk[PORT_BCR_RSSD_ -1] == CTL_YES)
		{
			sTemp = st_serial.mcomm_rec[PORT_BCR_RSSD_ -1];
			// �б� �۾� �����ߴ��� �˻�
			if (sTemp == "No-Read")
			{
				m_nStep_RSSD = 5000;	// ���� ��ȯ ����
			}
			else
			{
				m_nStep_RSSD = 4000;
			}
		}
		else
		{
			m_lWait_RSSD[1] = GetCurrentTime();
			m_lWait_RSSD[2] = m_lWait_RSSD[1] - m_lWait_RSSD[0];
			if (m_lWait_RSSD[2] < 0)
			{
				m_lWait_RSSD[0] = GetCurrentTime();
				break;
			}
			
			// 2�� ���� ��ٸ�
			if (m_lWait_RSSD[2] > 2000)
			{
				m_nStep_RSSD = 5000;	// ���� ��ȯ ����
			}
		}
		break;
		
	case 4000:
		m_nReq_RSSD	= REPLY_CORRECT_;
		
		m_nStep_RSSD = 0;
		FuncRet = RET_GOOD;
		break;
		
		// ���� ��ȯ ����
	case 5000:
		m_nReq_RSSD	= REPLY_ERROR_;
		
		m_nStep_RSSD = 0;
		FuncRet = RET_ERROR;
		break;
	}
	return FuncRet;
}

// ��Ʈ ���� ���� �˻�� ���� �������� ���� �Լ����� �����
int CBcrEvent::OnRun_TRIN() 
{
	// [�ʱ�ȭ] �Լ� ���� �÷��� (�۾���)
	int FuncRet = RET_PROCEED;

	CString sTemp;
	int i=0, nPos;

	switch(m_nStep_TRIN)
	{
	case 0:
		// [1:BCR Continue]
		// (Self TEST) ��� �߰���
		// - �� ��忡���� ��� �޽��� ���� �ʿ� ����
		// - ���ڵ� ��ġ�� �̵��ϸ� �ڵ����� �о �ش� ���� ��������
		if (st_basic.nMode_BCR == 1)
		{
			// �ԷµǴ� �����͸� �޾Ƶ��̱� �����϶�� ��û��
			// - �ƹ����� �޾Ƶ��̸� ������ ������ �޾Ƶ��� �� �ֱ� ����
			st_serial.nDataAccept = REQ_ACCEPT_;
			// �����͸� ������ �迭 ��ġ ���� �ʱ�ȭ
			OnReset_WorkPosTRIN();
			
			// ���� �̵��� ������ ������
			m_nStep_TRIN = 2100;
		}
		// [0:BCR Step]
		else
		{
			// BCR �б� ��û ����
			::PostMessage(st_handler.hWnd, WM_DATA_SEND, PORT_BCR_TRIN_, 0);
			
			// st_serial.n_rec_chk[nzPort -1]	= FALSE;
			// �� �κ��� ���� �����ӿ��� �޽��� �����ϸ鼭 �����ϰ� ��
			// - OnSend_BcrRead() �Լ� ����
			// �޽��� ���� ���� �ð� ����
			m_lWait_TRIN[0] = GetCurrentTime();
			m_nStep_TRIN = 1100;
		}
		break;

	case 1100:
		// ������ ��ٸ�
		if (st_serial.mn_rec_chk[PORT_BCR_TRIN_ -1] == CTL_YES)
		{
			sTemp = st_serial.mcomm_rec[PORT_BCR_TRIN_ -1];
			// �б� �۾� �����ߴ��� �˻�
			if (sTemp == "No-Read")
			{
				m_nStep_TRIN = 5000;	// ���� ��ȯ ����
			}
			else
			{
				m_nStep_TRIN = 4000;
			}
		}
		else
		{
			m_lWait_TRIN[1] = GetCurrentTime();
			m_lWait_TRIN[2] = m_lWait_TRIN[1] - m_lWait_TRIN[0];
			if (m_lWait_TRIN[2] < 0)
			{
				m_lWait_TRIN[0] = GetCurrentTime();
				break;
			}

			// 2�� ���� ��ٸ�
			if (m_lWait_TRIN[2] > 2000)
			{
				m_nStep_TRIN = 5000;	// ���� ��ȯ ����
			}
		}
		break;

	case 2100:
		// ���� �̵��� �Ϸ��� ������
		if (m_nReq_TRIN == REQ_STOP_)
		{
			// ������ ���ڵ� ���� ������ ��ٸ��� ���� �ð� ����
			m_lWait_TRIN[0] = GetCurrentTime();
			m_nStep_TRIN = 2200;
		}
		break;

	case 2200:
		// ������ ���ڵ� �б� ���� �ð� ������
		m_lWait_TRIN[1] = GetCurrentTime();
		m_lWait_TRIN[2] = m_lWait_TRIN[1] - m_lWait_TRIN[0];
		if (m_lWait_TRIN[2] < 0)
		{
			m_lWait_TRIN[0] = GetCurrentTime();
			break;
		}

		if (m_lWait_TRIN[2] > 200)
		{
			// �ԷµǴ� ���ڵ� ���� �����϶�� ����
			st_serial.nDataAccept = REQ_FREE_;
			m_nStep_TRIN = 2300;
		}
		break;

	case 2300:
		// ��� ���ڵ� ���� ����
		if (m_nPos_TRIN >= (ID_BUFF_CNT_ -1))
		{
			// ���� ���ڵ� ������ŭ �ݺ�
			for(i=0; i<ID_BUFF_CNT_; i++)
			{
				sTemp.Format("%s", stBCR[PORT_BCR_TRIN_ -1].stMat[i].chData_IDBUF);
				// ���ڵ� ���� �߿� ������ �߻��� ���� �����ϴ��� Ȯ��
				nPos = sTemp.Find("No-Read");
				if (nPos != -1)
				{
					m_nStep_TRIN = 5000;
					break;
				}
			}

			m_nStep_TRIN = 4000;
		}
		// ��� ���ڵ� ���� ���� ���� (����)
		else
		{
			m_nStep_TRIN = 5000;
		}
		break;

	case 4000:
		m_nReq_TRIN	= REPLY_CORRECT_;

		m_nStep_TRIN = 0;
		FuncRet = RET_GOOD;
		break;

		// ���� ��ȯ ����
	case 5000:
		m_nReq_TRIN	= REPLY_ERROR_;

		m_nStep_TRIN = 0;
		FuncRet = RET_ERROR;
		break;
	}
	return FuncRet;
}

int CBcrEvent::OnRun_TROUT() 
{
	// [�ʱ�ȭ] �Լ� ���� �÷��� (�۾���)
	int FuncRet = RET_PROCEED;

	CString sTemp;
	int i=0, nPos;

	switch(m_nStep_TROUT)
	{
	case 0:
		// [1:BCR Continue]
		// (Self TEST) ��� �߰���
		// - �� ��忡���� ��� �޽��� ���� �ʿ� ����
		// - ���ڵ� ��ġ�� �̵��ϸ� �ڵ����� �о �ش� ���� ��������
		if (st_basic.nMode_BCR == 1)
		{
			// �ԷµǴ� �����͸� �޾Ƶ��̱� �����϶�� ��û��
			// - �ƹ����� �޾Ƶ��̸� ������ ������ �޾Ƶ��� �� �ֱ� ����
			st_serial.nDataAccept = REQ_ACCEPT_;
			// �����͸� ������ �迭 ��ġ ���� �ʱ�ȭ
			OnReset_WorkPosTROUT();
			
			// ���� �̵��� ������ ������
			m_nStep_TROUT = 2100;
		}
		// [0:BCR Step]
		else
		{
			// BCR �б� ��û ����
			::PostMessage(st_handler.hWnd, WM_DATA_SEND, PORT_BCR_TROUT_, 0);
			
			// st_serial.n_rec_chk[nzPort -1]	= FALSE;
			// �� �κ��� ���� �����ӿ��� �޽��� �����ϸ鼭 �����ϰ� ��
			// - OnSend_BcrRead() �Լ� ����
			// �޽��� ���� ���� �ð� ����
			m_lWait_TROUT[0] = GetCurrentTime();
			m_nStep_TROUT = 1100;
		}
		break;

	case 1100:
		// ������ ��ٸ�
		if (st_serial.mn_rec_chk[PORT_BCR_TROUT_ -1] == CTL_YES)
		{
			sTemp = st_serial.mcomm_rec[PORT_BCR_TROUT_ -1];
			// �б� �۾� �����ߴ��� �˻�
			if (sTemp == "No-Read")
			{
				m_nStep_TROUT = 5000;	// ���� ��ȯ ����
			}
			else
			{
				m_nStep_TROUT = 4000;
			}
		}
		else
		{
			m_lWait_TROUT[1] = GetCurrentTime();
			m_lWait_TROUT[2] = m_lWait_TROUT[1] - m_lWait_TROUT[0];
			if (m_lWait_TROUT[2] < 0)
			{
				m_lWait_TROUT[0] = GetCurrentTime();
				break;
			}

			// 2�� ���� ��ٸ�
			if (m_lWait_TROUT[2] > 2000)
			{
				m_nStep_TROUT = 5000;	// ���� ��ȯ ����
			}
		}
		break;

	case 2100:
		// ���� �̵��� �Ϸ��� ������
		if (m_nReq_TROUT == REQ_STOP_)
		{
			// ������ ���ڵ� ���� ������ ��ٸ��� ���� �ð� ����
			m_lWait_TROUT[0] = GetCurrentTime();
			m_nStep_TROUT = 2200;
		}
		break;

	case 2200:
		// ������ ���ڵ� �б� ���� �ð� ������
		m_lWait_TROUT[1] = GetCurrentTime();
		m_lWait_TROUT[2] = m_lWait_TROUT[1] - m_lWait_TROUT[0];
		if (m_lWait_TROUT[2] < 0)
		{
			m_lWait_TROUT[0] = GetCurrentTime();
			break;
		}

		if (m_lWait_TROUT[2] > 200)
		{
			// �ԷµǴ� ���ڵ� ���� �����϶�� ����
			st_serial.nDataAccept = REQ_FREE_;
			m_nStep_TROUT = 2300;
		}
		break;

	case 2300:
		// ��� ���ڵ� ���� ����
		if (m_nPos_TROUT >= (ID_BUFF_CNT_ -1))
		{
			// ���� ���ڵ� ������ŭ �ݺ�
			for(i=0; i<ID_BUFF_CNT_; i++)
			{
				sTemp.Format("%s", stBCR[PORT_BCR_TROUT_ -1].stMat[i].chData_IDBUF);
				// ���ڵ� ���� �߿� ������ �߻��� ���� �����ϴ��� Ȯ��
				nPos = sTemp.Find("No-Read");
				if (nPos != -1)
				{
					m_nStep_TROUT = 5000;
					break;
				}
			}

			m_nStep_TROUT = 4000;
		}
		// ��� ���ڵ� ���� ���� ���� (����)
		else
		{
			m_nStep_TROUT = 5000;
		}
		break;

	case 4000:
		m_nReq_TROUT	= REPLY_CORRECT_;

		m_nStep_TROUT = 0;
		FuncRet = RET_GOOD;
		break;

		// ���� ��ȯ ����
	case 5000:
		m_nReq_TROUT	= REPLY_ERROR_;

		m_nStep_TROUT = 0;
		FuncRet = RET_ERROR;
		break;
	}
	return FuncRet;
}

//==================================================================//
// [EQP<-BCR] ���ڵ� ������κ��� �޽��� ����
//==================================================================//
void CBcrEvent::OnRcvDataFromBCR(WPARAM ch, LPARAM port) 
{
	// ��Ʈ ���� ����
	int nPort = (int)port;
	int nLen;

	// ������ ���� �Է� [CR] �Է����� Ȯ��
	if (ch == 0x0a)
	{
		m_sRcvedData[nPort -1] += (char)ch;
		//m_sRcvedData[nPort-1].TrimLeft(' ');
		//m_sRcvedData[nPort-1].TrimRight(' ');
		st_serial.mcomm_rec[nPort -1] = m_sRcvedData[nPort -1];
		(m_sRcvedData[nPort -1]).Empty();

		m_sLogMsg.Format( "[RCV]BCR:%s", st_serial.mcomm_rec[nPort -1]);
		Func.On_LogFile_Add(99, m_sLogMsg);
		

		// ���� �޽����� ��ü ���� ���
		// �ּ� 3���� �̻� ���ŵǾ�� �������� �޽����� ����
		nLen = (st_serial.mcomm_rec[nPort -1]).GetLength();
		if (nLen > 2)
		{
			// CR+LF ������ ���ڿ��� ������
			st_serial.mcomm_rec[nPort -1] = (st_serial.mcomm_rec[nPort-1]).Mid(0, nLen-2);

			OnSet_2Struct(nPort);	// ����ü�� ���ŵ� �޽��� ����
			st_serial.mn_rec_chk[nPort -1] = TRUE;
		}
		else
		{
			st_serial.mn_rec_chk[nPort -1] = FALSE;
		}

		// ȭ�鿡 ���� �޽��� ��� ��û
		if (st_handler.cwnd_list != NULL)
		{
			sprintf(st_msg.c_normal_msg, st_serial.mcomm_rec[nPort -1]);
			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, BCR_PORT, RECEIVE_MSG);
		}
	}
	else
	{
		m_sRcvedData[port -1] += (char)ch;
	}
}

//==================================================================//
// ����ü�� ���ŵ� �޽��� ����
//==================================================================//
void CBcrEvent::OnSet_2Struct(int nzPort) 
{
	if (nzPort == PORT_BCR_TRIN_)
	{
		// [1:BCR Continue]
		if (st_basic.nMode_BCR == 1)
		{
			if (st_serial.nDataAccept == REQ_ACCEPT_)
			{
				sprintf(stBCR[nzPort -1].stMat[m_nPos_TRIN].chData_IDBUF, st_serial.mcomm_rec[nzPort -1]);
				
				// ������ ���� ������ ������ �迭 ��ġ ���
				(m_nPos_TRIN)++;
				// �ѹ��� �о�� �� (ID ����) ������ �ִ� 2����
				if ((m_nPos_TRIN) > (ID_BUFF_CNT_ -1))
				{
					m_nPos_TRIN = (ID_BUFF_CNT_ -1);
				}
			}
		}
		// [0:BCR Step]
		else
		{
			sprintf(stBCR[nzPort -1].stMat[m_nPos_TRIN].chData_IDBUF, st_serial.mcomm_rec[nzPort -1]);
			
			// ������ ���� ������ ������ �迭 ��ġ ���
			(m_nPos_TRIN)++;
			// �ѹ��� �о�� �� (ID ����) ������ �ִ� 2����
			if ((m_nPos_TRIN) > (ID_BUFF_CNT_ -1))
			{
				m_nPos_TRIN = (ID_BUFF_CNT_ -1);
			}
		}
	}
	else if (nzPort == PORT_BCR_TROUT_)
	{
		// [1:BCR Continue]
		if (st_basic.nMode_BCR == 1)
		{
			if (st_serial.nDataAccept == REQ_ACCEPT_)
			{
				sprintf(stBCR[nzPort -1].stMat[m_nPos_TROUT].chData_IDBUF, st_serial.mcomm_rec[nzPort -1]);
				
				// ������ ���� ������ ������ �迭 ��ġ ���
				(m_nPos_TROUT)++;
				// �ѹ��� �о�� �� (ID ����) ������ �ִ� 2����
				if ((m_nPos_TROUT) > (ID_BUFF_CNT_ -1))
				{
					m_nPos_TROUT = (ID_BUFF_CNT_ -1);
				}
			}
		}
		// [0:BCR Step]
		else
		{
			sprintf(stBCR[nzPort -1].stMat[m_nPos_TROUT].chData_IDBUF, st_serial.mcomm_rec[nzPort -1]);
			
			// ������ ���� ������ ������ �迭 ��ġ ���
			(m_nPos_TROUT)++;
			// �ѹ��� �о�� �� (ID ����) ������ �ִ� 2����
			if ((m_nPos_TROUT) > (ID_BUFF_CNT_ -1))
			{
				m_nPos_TROUT = (ID_BUFF_CNT_ -1);
			}
		}
	}
	else if (nzPort == PORT_BCR_LSSD_ ||
		nzPort == PORT_BCR_RSSD_)
	{
		sprintf(stBCR[nzPort -1].stMat[0].chData_SSD, st_serial.mcomm_rec[nzPort -1]);
	}
	// �Ŵ��� �������� (ID ����)�� ���縦 �б� ���ؼ��� ���� ������� �о�� ��
	// - 1) (ID ����) ����
	// - 2) ���� ����
	else if (nzPort == PORT_BCR_MANUAL_)
	{
		// USB Ÿ������ �����Ѵٰ� �Ͽ� ������
	}

	// ���� �����͸� ȭ�鿡 �����ֱ� ���ؼ��� �Ʒ� �κ� ����
	//st_handler.cwnd_main->PostMessage(WM_WORK_END, MAIN_CARRIER_MARK, 0);
}

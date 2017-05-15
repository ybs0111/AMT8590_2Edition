// XgemCommand.cpp: implementation of the CXgemCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XgemCommand.h"

#include "Variable.h"

// ���̸� �߰� [2013.11.13]
// CIM �޽��� ���� ���� �߰���
#include "CimEvent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CXgemCommand clsXgem;

CXgemCommand::CXgemCommand()
{
	m_hXgemInterfaceDlg = NULL;
}

CXgemCommand::~CXgemCommand()
{
	if (m_hXgemInterfaceDlg != NULL)
	{
		delete m_hXgemInterfaceDlg;
		m_hXgemInterfaceDlg = NULL;
	}
}

//==================================================================//
// [EQ->CIM] XGEM OCX �ʱ�ȭ �۾� ��û
// - ����� �̻��
// : CIM ���α׷� ����ÿ� �ڵ������� ó����
//==================================================================//
void CXgemCommand::XgemInitialize(CWnd *hWnd, CString strPath) 
{
	CString sHead, sFunc;

	m_hXgemInterfaceDlg = hWnd;

	sFunc = "FUNC=COMMUNICATION,CONFIG=" + strPath + ",";
	sHead.Format("HD=%06d,", sFunc.GetLength());

	g_client_cim.PushSendMsg(sHead+sFunc);
}

//==================================================================//
// [EQ->CIM] ��Ʈ�� ��� ���� ����
//==================================================================//
void CXgemCommand::XgemEqCtrlStatus(int nMode) 
{
	CString sHead, sFunc;

	if (nMode == 0)	// OFF_LINE
	{
		sFunc = "FUNC=OPERATE,CONNECT=0,";
	}
	else if (nMode == 1)	// ON_LINE_LOCAL
	{
		sFunc = "FUNC=OPERATE,CONNECT=1,";
	}
	else if (nMode == 2)	// ON_LINE_REMOTE
	{
		sFunc = "FUNC=OPERATE,CONNECT=2,";
	}
	else
	{
		return;
	}
	sHead.Format("HD=%06d,", sFunc.GetLength());

	g_client_cim.PushSendMsg(sHead+sFunc);
}

//==================================================================//
// [EQ->CIM] �߻��� �˶� ���� ����
//==================================================================//
void CXgemCommand::XgemAlarmStatus(CString strAlarmCode, int nStatus) 
{
	CString sHead, sFunc;

	sFunc.Format("FUNC=ALARM,CODE=%s,STATUS=%d,", strAlarmCode, nStatus);
	sHead.Format("HD=%06d,", sFunc.GetLength());

	g_client_cim.PushSendMsg(sHead+sFunc);
}

//==================================================================//
// [EQ->CIM] ���� ���� ���� ����
// dSTOP		0
// dRUN			1
// dJAM			2
// dLOTEND		3
// dINIT		4
// dWARNING		5
// dLOCK		6
// dIDLE		7
// dMAINT		8
//==================================================================//
void CXgemCommand::XgemMachineStatus(int nMode) 
{
	CString sHead, sFunc;

	sFunc.Format("FUNC=RUN_STATUS,STATUS=%d,EQID=%s,EQNO=%s,", nMode, st_lamp.mstr_equip_id, st_lamp.mstr_equip_no);
	sHead.Format("HD=%06d,", sFunc.GetLength());

	g_client_cim.PushSendMsg(sHead+sFunc);
}


//==================================================================//
// [EQ->CIM] ������ PPID ���� ����
// - ����� ������ ����ÿ��� ������ ���� �����ϰ� ����
//==================================================================//
void CXgemCommand::XgemPPID(CString strPPID, CString strPath) 
{
	CString sHead, sFunc;
	
	sFunc.Format("FUNC=PPID,PP_NAME=%s,METHOD=0,PP_PATH=%s,", strPPID, strPath);
	sHead.Format("HD=%06d,", sFunc.GetLength());

	g_client_cim.PushSendMsg(sHead+sFunc);
}

//==================================================================//
// [EQ->CIM] ������ PPID ���� ���� �� ����
//==================================================================//
void CXgemCommand::XgemRecipeChange() 
{
	CString sHead, sFunc, sTmp;
	sFunc = "";

	sFunc += "FUNC=CEID,CEID_NUM=1300,REPORT=1";
	sFunc += ",";
	sTmp.Format("REPORT=1,REP_01={CNT=03,[DA_01=01,%s],[DA_02=01,%s],[DA_03=01,%d]}",
		st_basic.sDvcName,
		st_basic.n_mode_interface,
		st_basic.n_mode_device);
	sFunc += sTmp;
	sHead.Format("HD=%06d,", sFunc.GetLength());
	
	g_client_cim.PushSendMsg(sHead+sFunc);
}

//==================================================================//
// [EQ->CIM] ������ PPID ���� �� ����
//==================================================================//
void CXgemCommand::XgemRecipeSelect() 
{
	CString sHead, sFunc, sTmp;
	sFunc = "";

	sFunc += "FUNC=CEID,CEID_NUM=1303,REPORT=1";
	sFunc += ",";
	sTmp.Format("REPORT=1,REP_01={CNT=03,[DA_01=01,%s],[DA_02=01,%s],[DA_03=01,%d]},",
		st_basic.sDvcName,
		st_basic.n_mode_interface,
		st_basic.n_mode_device);
	sFunc += sTmp;
	sHead.Format("HD=%06d,", sFunc.GetLength());
	
	g_client_cim.PushSendMsg(sHead+sFunc);
}

//==================================================================//
// [EQ->CIM] Lot ���� �� ����
//==================================================================//
void CXgemCommand::XgemLotStart() 
{

}

//==================================================================//
// [EQ->CIM] Lot ���� �� ����
//==================================================================//
void CXgemCommand::XgemLotEnd() 
{

}

//==================================================================//
// [EQ->CIM] TrackIn �۾� �� ����
//==================================================================//
void CXgemCommand::XgemTrayIn() 
{

}

//==================================================================//
// [EQ->CIM] TrackOut �۾� �� ����
//==================================================================//
void CXgemCommand::XgemTrayOut() 
{
	
}

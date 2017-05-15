// CimEvent.h: interface for the CCimEvent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIMEVENT_H__819DE402_D5C1_4DDE_BF95_CBE2FE5CD8D0__INCLUDED_)
#define AFX_CIMEVENT_H__819DE402_D5C1_4DDE_BF95_CBE2FE5CD8D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//==================================================================//
// �޽���ť ����ϱ� ���� �߰�
//==================================================================//
/*
#include <queue>  // ť �ڷᱸ��ü ���
using namespace std;
*/
#include <iostream>
#include <queue>
#include <string>
using namespace std;
//------------------------------------------------------------------//
#include "Afxmt.h"  // CCriticalSecton���� CSingleLock�� ����ϱ� ���� �߰�

#include <vector>

#include "Variable.h"

enum eWaitReply
{
	EWR_NONE,
	EWR_PROCESSSTATUS,
	EWR_PGET,
	EWR_DGET,	// ���̸� �߰� [2013.10.30]
	EWR_MASTERLOT,
	EWR_ENDLOT,
	EWR_LMVIN,
	EWR_LMVOU,
	EWR_EQPSTATUS,
	EWR_COLLECTDATA,
	EWR_BINCODESET,
	EWR_BBAR,
	EWR_OPERATE,
	EWR_INTERFACE,
	EWR_HCON,
};

class CCimEvent  
{
public:
	CCimEvent();
	virtual ~CCimEvent();


// Attributes
private:
	CCriticalSection m_csPutQueue;
	CCriticalSection m_csGetQueue;

	CString m_sLogMsg;
	CString m_sRcvData;

	eWaitReply m_eWR;

	int  m_nArrayPos;
	
// Attributes
public:
	bool m_bflag_INIT;

	//==============================================================//
	// �޽����� ������ ť ����
	//==============================================================//
	queue< CString> m_qReqData;  // ������ ������ ���ڿ� ���� ������ ť
	//--------------------------------------------------------------//
	
// Operations
private:
	
// Operations
public:
	void OnSeq_RUN(void);      // ������ ����
	void OnSeq_INIT(void);     // ������ ���� ���� �ʱ�ȭ
	void OnSeq_Execute(void);  // ������ ����

	//==============================================================//
	// �޽���ť �� ������ ���� ���� �κ�
	//==============================================================//
	inline OnClearMsgQueue()	{ while(m_qReqData.size()) m_qReqData.pop(); };  // �޽��� ���ſ� ť Ŭ����
	void OnPutToQueue(CString szData);   // ���ŵ� �޽����� ť�� ����
	int  OnGetFromQueue(CString &spData);  // ť�� �Էµ� ���ڿ� ��ȯ
	//--------------------------------------------------------------//
	int  OnDivide_FromCIM(int nzSocketNo, CString szCommand);	// [MES->CIM] ���ŵ� �޽��� �����Ͽ� ó��

	//==============================================================//
	// [EQP<-CIM] ���� ������ �Ľ��Ͽ� ó��
	//==============================================================//
	void OnParseComplete(std::string strRecv);

	void OnReceived_Interface(std::string strRecv);
	void OnReceived_Operate(std::string strRecv);
	void OnReceived_HCON(std::string strRecv);	// [CIM<->HOST] ���� ���� ���� ����

	// ���ϴ� ������ ������ �� ��ȯ
	CString OnAnalysisRcvMSG(int nzMidPos, CString szLetter, CString szSeparator, CString szRcvMsg, int nzMode=0);
	//--------------------------------------------------------------//

	void SetWaitReply(eWaitReply ewr)	{ m_eWR = ewr; }
	eWaitReply GetWaitReply()	{ return m_eWR; }

	int PushSendMsg(CString szMsg);	// [EQP->CIM] �޽��� ����
	CString OnPickOut_RcvMsg(CString szFind, CString szOrg);	// Ư���� ���ڿ� ������ ������ ��ȯ

};
extern CCimEvent	g_client_cim;

#endif // !defined(AFX_CIMEVENT_H__819DE402_D5C1_4DDE_BF95_CBE2FE5CD8D0__INCLUDED_)

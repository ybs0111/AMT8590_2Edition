// MesEvent.h: interface for the CMesEvent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESEVENT_H__02F160AB_99DE_4A60_8DBC_CE1CC05F6105__INCLUDED_)
#define AFX_MESEVENT_H__02F160AB_99DE_4A60_8DBC_CE1CC05F6105__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Variable.h"
#include "Public_Function.h"

//==================================================================//
// �޽���ť ����ϱ� ���� �߰�
// ���̸� �߰� [2014.12.11]
//==================================================================//
#include <iostream>
#include <queue>
#include <string>
using namespace std;
//------------------------------------------------------------------//
#include "Afxmt.h"  // CCriticalSecton���� CSingleLock�� ����ϱ� ���� �߰�
#include <vector>

class CMesEvent  
{
public:
	CMesEvent();
	virtual ~CMesEvent();

// Attributes
private:
	CCriticalSection m_csPutQueue;
	CCriticalSection m_csGetQueue;

	CString m_sLogMsg;
	CString m_sRcvData;

	int  m_nArray;

	int  m_nReqMesWork;

	int  m_nDataParse;
	long m_lWaitResp[3];
	
// Attributes
public:
	bool m_bflag_INIT;
	int  m_nStep_RUN;
	
	int  m_nReqStart;
	
	int  m_nIdx;
	
	int  m_nExecutedFunc;
	int  m_nReqSearch;
	// ���̸� �߰� [2014.12.13]
	CString m_sPutData;
	
	//==============================================================//
	// �޽����� ������ ť ����
	//==============================================================//
	//queue< int> m_qReqData;  // ������ ������ ���ڿ� ���� ������ ť
	// ���̸� �߰� [2014.12.13]
	queue< CString> m_qReqData;  // ������ ������ ���ڿ� ���� ������ ť
	//--------------------------------------------------------------//
	
// Operations
private:
	
// Operations
public:
	void OnSeq_RUN(void);      // ������ ����
	void OnSeq_Init(void);     // ������ ���� ���� �ʱ�ȭ
	void OnSeq_Execute(void);  // ������ ����

	//==============================================================//
	// �޽���ť �� ������ ���� ���� �κ�
	//==============================================================//
	inline OnClearMsgQueue()	{ while(m_qReqData.size()) m_qReqData.pop(); };  // �޽��� ���ſ� ť Ŭ����
	void OnPutToQueue(int nzData);   // ���ŵ� �޽����� ť�� ����
	//int  OnGetFromQueue(int &nzData);  // ť�� �Էµ� ���ڿ� ��ȯ
	// ���̸� ���� [2014.12.13]
	int  OnGetFromQueue(CString &spData);  // ť�� �Էµ� ���ڿ� ��ȯ
	//--------------------------------------------------------------//

	int  OnRun_MesWork();	// [EQP<->MES] �޽��� ���� �� ó��

	int OnDivide_FromMES(int nzSocketNo, CString szCommand);	// [MES->EQP] ���ŵ� �޽��� �����Ͽ� ó��
	int OnAnalysis_MesData(CString szRcvData);	// ���ŵ� �޽��� �м� �۾�

	int  PushSendMsg(CString szMsg);	// [EQP->MES] �޽��� ����

	void OnReq_MesWork()	{ m_nReqStart = REQ_CALL_; }
	int  OnGet_MesWork()	{ return m_nReqStart; }

	void OnCreate_SendFormat(int nzIdx);	// [EQP->TMS] ������ �޽��� ����

	CString		m_strBcrFormat[2];
	CString		m_strSerial[2];
	void		ClrSerial( int nSite) { m_strSerial[nSite] = ""; }
	void		SetSerial(int nSite, CString strSerial) { m_strSerial[nSite] = strSerial; }
	CString		GetSerial( int nSite) { return m_strSerial[nSite]; }
	void		ClrBcrFormat(int nSite) { m_strBcrFormat[nSite] = ""; }
	void		SetBcrFormat(int nSite, CString strBcrFormat) { m_strBcrFormat[nSite] = strBcrFormat; }
	CString		GetBcrFormat(int nSite) { return m_strBcrFormat[nSite];	}


};
extern CMesEvent	evMes;

#endif // !defined(AFX_MESEVENT_H__02F160AB_99DE_4A60_8DBC_CE1CC05F6105__INCLUDED_)

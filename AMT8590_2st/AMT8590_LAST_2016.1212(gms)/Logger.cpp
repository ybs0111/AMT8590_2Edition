// Logger.cpp: implementation of the CLogger class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Logger.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CLogger	cLOG;  // Ŭ���� ������ ����

CLogger::CLogger()
{

}

CLogger::~CLogger()
{

}

//==================================================================//
// Log Event ������ ���� ����
void CLogger::OnSetPathLogEvent() 
{
	//CString sMakeFolder = OnGet_CurrentFolder();  // ���� �۾� ���� ��ȯ

	// Log Creating Path Setting
/*	CString sMakeFolder;
	sMakeFolder = CONFIG_PATH_BASE_ + _T("\\SOCKET\\");
	m_cLogSocket.OnSetPath(sMakeFolder);

	sMakeFolder = CONFIG_PATH_BASE_ + _T("\\COMM\\");
	m_cLogComm.OnSetPath(sMakeFolder);

	sMakeFolder = CONFIG_PATH_BASE_ + _T("\\PGM\\");
	m_cLogPgm.OnSetPath(sMakeFolder);

	sMakeFolder = CONFIG_PATH_BASE_ + _T("\\XGEM\\");
	m_cLogXGem.OnSetPath(sMakeFolder);

	sMakeFolder = CONFIG_PATH_BASE_ + _T("\\SEQ\\");
	m_cLogSeq.OnSetPath(sMakeFolder);
	*/
}

//==================================================================//
// Log �޽��� �߰�
void CLogger::OnLogEvent(int nzLogType, CString szLogEvent) 
{
/*	CString sFileName;  // ������ Log ���ϸ�
	
	SYSTEMTIME  systime;
	GetLocalTime(&systime);

	// ���� ��� ���� �α�
	if (nzLogType == LOG_SOCKET_)
	{
		// ���� ��� ���� �α� �ۼ�
		sFileName.Format("%i\\%02i\\LOG_SOCKET_%02i%02i%02i.txt",
			systime.wYear,
			systime.wMonth,
			systime.wYear,
			systime.wMonth,
			systime.wDay);
		m_cLogSocket.OnChangeFile(sFileName);
		m_cLogSocket.OnWrite(szLogEvent);

		// ��ü ������ ���� �α� �ۼ�
		sFileName.Format("%i\\%02i\\LOG_SEQ_%02i%02i%02i.txt",
			systime.wYear,
			systime.wMonth,
			systime.wYear,
			systime.wMonth,
			systime.wDay);
		
		m_cLogSeq.OnChangeFile(sFileName);
		m_cLogSeq.OnWrite(szLogEvent);
	}
	// �ø��� ��� ���� �α�
	else if (nzLogType == LOG_COMM_)
	{
		sFileName.Format("%i\\%02i\\LOG_COMM_%02i%02i%02i.txt",
			systime.wYear,
			systime.wMonth,
			systime.wYear,
			systime.wMonth,
			systime.wDay);
		m_cLogComm.OnChangeFile(sFileName);
		m_cLogComm.OnWrite(szLogEvent);

		sFileName.Format("%i\\%02i\\LOG_SEQ_%02i%02i%02i.txt",
			systime.wYear,
			systime.wMonth,
			systime.wYear,
			systime.wMonth,
			systime.wDay);
		m_cLogSeq.OnChangeFile(sFileName);
		m_cLogSeq.OnWrite(szLogEvent);
	}
	// ȭ�� ���� ���� �α�
	else if (nzLogType == LOG_PGM_)
	{
		sFileName.Format("%i\\%02i\\LOG_PGM_%02i%02i%02i.txt",
			systime.wYear,
			systime.wMonth,
			systime.wYear,
			systime.wMonth,
			systime.wDay);
		m_cLogPgm.OnChangeFile(sFileName);
		m_cLogPgm.OnWrite(szLogEvent);

		sFileName.Format("%i\\%02i\\LOG_SEQ_%02i%02i%02i.txt",
			systime.wYear,
			systime.wMonth,
			systime.wYear,
			systime.wMonth,
			systime.wDay);
		m_cLogSeq.OnChangeFile(sFileName);
		m_cLogSeq.OnWrite(szLogEvent);
	}
	// XGEM ��� ���� �α�
	else if (nzLogType == LOG_XGEM_)
	{
		sFileName.Format("%i\\%02i\\LOG_XGEM_%02i%02i%02i.txt",
			systime.wYear,
			systime.wMonth,
			systime.wYear,
			systime.wMonth,
			systime.wDay);
		m_cLogXGem.OnChangeFile(sFileName);
		m_cLogXGem.OnWrite(szLogEvent);
	}
	// ������ ���� ���� �α�
	else if (nzLogType == LOG_SEQ_)
	{
		sFileName.Format("%i\\%02i\\LOG_SEQ_%02i%02i%02i.txt",
			systime.wYear,
			systime.wMonth,
			systime.wYear,
			systime.wMonth,
			systime.wDay);
		m_cLogSeq.OnChangeFile(sFileName);
		m_cLogSeq.OnWrite(szLogEvent);
	}
	*/
}

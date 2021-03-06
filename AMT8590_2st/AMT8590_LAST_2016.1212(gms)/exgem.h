#if !defined(AFX_EXGEM_H__9BB9EC76_B6A9_45F4_AF08_1AE724454B07__INCLUDED_)
#define AFX_EXGEM_H__9BB9EC76_B6A9_45F4_AF08_1AE724454B07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CeXGem wrapper class

class CeXGem : public CWnd
{
protected:
	DECLARE_DYNCREATE(CeXGem)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x2220f20c, 0x2fa3, 0x461c, { 0x84, 0xd4, 0x94, 0x8b, 0x6d, 0x7, 0xe7, 0x9b } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:
	CString GetIp();
	void SetIp(LPCTSTR);
	long GetPort();
	void SetPort(long);
	BOOL GetActive();
	void SetActive(BOOL);

// Operations
public:
	void AboutBox();
	long Initialize(LPCTSTR sCfg);
	long Start();
	long Stop();
	long Close();
	long MakeObject(long* pnObjectID);
	long SetList(long nObjectID, long nItemCount);
	long GetList(long nObjectID, long* pnItemCount);
	long GEMSetVariables(long nObjectID, long nVid);
	long SendSECSMessage(long nObjectID, long nStream, long nFunction, long nSysbyte);
	long GEMReqOffline();
	long GEMReqLocal();
	long GEMReqRemote();
	long GEMSetEstablish(long bState);
	long GEMSetParam(LPCTSTR sParamName, LPCTSTR sParamValue);
	long GEMGetParam(LPCTSTR sParamName, BSTR* psParamValue);
	long GEMEQInitialized(long nInitType);
	long GEMReqGetDateTime();
	long GEMRspGetDateTime(long nMsgId, LPCTSTR sSystemTime);
	long GEMRspDateTime(long nMsgId, long nResult);
	long GEMSetAlarm(long nID, long nState);
	long GEMRspRemoteCommand(long nMsgId, LPCTSTR sCmd, long nHCAck, long nCount, long* pnResult);
	long GEMRspChangeECV(long nMsgId, long nResult);
	long GEMSetECVChanged(long nCount, long* pnEcIds, BSTR* psEcVals);
	long GEMSetPPChanged(long nMode, LPCTSTR sPpid, long nSize, LPCTSTR sBody);
	long GEMSetPPFmtChanged(long nMode, LPCTSTR sPpid, LPCTSTR sMdln, LPCTSTR sSoftRev, long nCount, BSTR* psCCode, long* pnParamCount, BSTR* psParamNames);
	long GEMReqPPLoadInquire(LPCTSTR sPpid, long nLength);
	long GEMRspPPLoadInquire(long nMsgId, LPCTSTR sPpid, long nResult);
	long GEMReqPPSend(LPCTSTR sPpid, LPCTSTR sBody);
	long GEMRspPPSend(long nMsgId, LPCTSTR sPpid, long nResult);
	long GEMReqPP(LPCTSTR sPpid);
	long GEMRspPP(long nMsgId, LPCTSTR sPpid, LPCTSTR sBody);
	long GEMRspPPDelete(long nMsgId, long nCount, BSTR* psPpids, long nResult);
	long GEMRspPPList(long nMsgId, long nCount, BSTR* psPpids);
	long GEMReqPPFmtSend(LPCTSTR sPpid, LPCTSTR sMdln, LPCTSTR sSoftRev, long nCount, BSTR* psCCode, long* pnParamCount, BSTR* psParamNames);
	long GEMRspPPFmtSend(long nMsgId, LPCTSTR sPpid, long nResult);
	long GEMReqPPFmt(LPCTSTR sPpid);
	long GEMRspPPFmt(long nMsgId, LPCTSTR sPpid, LPCTSTR sMdln, LPCTSTR sSoftRev, long nCount, BSTR* psCCode, long* pnParamCount, BSTR* psParamNames);
	long GEMReqPPFmtVerification(LPCTSTR sPpid, long nCount, long* pnAck, BSTR* psSeqNumber, BSTR* psError);
	long GEMSetTerminalMessage(long nTid, LPCTSTR sMsg);
	long GEMSetVariable(long nCount, long* pnVid, BSTR* psValue);
	long GEMEnableLog(long bEnabled);
	long GEMSetLogOption(LPCTSTR sDriectory, LPCTSTR sPrefix, LPCTSTR sExtension, long nKeepDay, long bMakeDailyLog, long bMakeSubDirectory);
	long GEMSetEvent(long nEventID);
	long GEMGetVariable(long nCount, long* pnVid, BSTR* psValue);
	long GEMSetSpecificMessage(long nObjectID, LPCTSTR sMsgName);
	long GEMGetSpecificMessage(long nObjectID, long* pnRObjectID, LPCTSTR sMsgName);
	long GetAllStringItem(long nObjectID, BSTR* psValue);
	long SetAllStringItem(long nObjectID, LPCTSTR sValue);
	long GEMSetVarName(long nCount, BSTR* psVidName, BSTR* psValue);
	long GEMGetVarName(long nCount, BSTR* psVidName, BSTR* psValue);
	long CloseObject(long nObjectID);
	long GEMReqAllECInfo();
	long SetBinary(long nObjectID, short* pnValue, long nItemCount);
	long SetBool(long nObjectID, short* pnValue, long nItemCount);
	long SetU1(long nObjectID, short* pnValue, long nItemCount);
	long SetU2(long nObjectID, long* pnValue, long nItemCount);
	long SetU4(long nObjectID, double* prValue, long nItemCount);
	long SetU8(long nObjectID, double* prValue, long nItemCount);
	long SetI1(long nObjectID, short* pnValue, long nItemCount);
	long SetI2(long nObjectID, short* pnValue, long nItemCount);
	long SetI4(long nObjectID, long* plValue, long nItemCount);
	long SetI8(long nObjectID, long* plValue, long nItemCount);
	long SetF4(long nObjectID, float* prValue, long nItemCount);
	long SetF8(long nObjectID, double* prValue, long nItemCount);
	long SetAscii(long nObjectID, LPCTSTR pszValue, long nItemCount);
	long GetBinary(long nObjectID, short* pnValue, long* pnItemCount, long nSize);
	long GetBool(long nObjectID, short* pnValue, long* pnItemCount, long nSize);
	long GetU1(long nObjectID, short* pnValue, long* pnItemCount, long nSize);
	long GetU2(long nObjectID, long* pnValue, long* pnItemCount, long nSize);
	long GetU4(long nObjectID, double* prValue, long* pnItemCount, long nSize);
	long GetU8(long nObjectID, double* prValue, long* pnItemCount, long nSize);
	long GetI1(long nObjectID, short* pnValue, long* pnItemCount, long nSize);
	long GetI2(long nObjectID, short* pnValue, long* pnItemCount, long nSize);
	long GetI4(long nObjectID, long* pnValue, long* pnItemCount, long nSize);
	long GetI8(long nObjectID, long* pnValue, long* pnItemCount, long nSize);
	long GetF4(long nObjectID, float* prValue, long* pnItemCount, long nSize);
	long GetF8(long nObjectID, double* prValue, long* pnItemCount, long nSize);
	long GetAscii(long nObjectID, BSTR* psValue, long* pnItemCount);
	long GEMReqPPSendEx(LPCTSTR sPpid, LPCTSTR sRecipePath);
	long GEMRspPPEx(long nMsgId, LPCTSTR sPpid, LPCTSTR sRecipePath);
	long GEMRspPPSendEx(long nMsgId, LPCTSTR sPpid, LPCTSTR sRecipePath, long nResult);
	long GEMReqPPEx(LPCTSTR sPpid, LPCTSTR sRecipePath);
	long SetAsciiEx(long nObjectID, short* pnValue, long nItemCount);
	long GetAsciiEx(long nObjectID, short* pnValue, long* pnItemCount, long nSize);
	long GEMSetVariableEx(long nObjectID, long nVid);
	long GEMReqLoopback(long nCount, long* pnAbs);
	long GEMSetEventEnable(long nCount, long* pnCEIDs, long nEnable);
	long GEMSetAlarmEnable(long nCount, long* pnALIDs, long nEnable);
	long GEMGetEventEnable(long nCount, long* pnCEIDs, long* pnEnable);
	long GEMGetAlarmEnable(long nCount, long* pnALIDs, long* pnEnable);
	long GEMGetAlarmInfo(long nCount, long* pnALIDs, long* pnALCDs, BSTR* psALTXs);
	long GEMGetSVInfo(long nCount, long* pnSVIDs, BSTR* psMins, BSTR* psMaxs);
	long GEMGetECVInfo(long nCount, long* pnEcIds, BSTR* psNames, BSTR* psDefs, BSTR* psMins, BSTR* psMaxs, BSTR* psUnits);
	long GEMRspOffline(long nMsgId, long nAck);
	long GEMRspOnline(long nMsgId, long nAck);
	long GEMReqHostOffline();
	long GEMReqStartPolling(LPCTSTR sName, long nScanTime);
	long GEMReqStopPolling(LPCTSTR sName);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXGEM_H__9BB9EC76_B6A9_45F4_AF08_1AE724454B07__INCLUDED_)

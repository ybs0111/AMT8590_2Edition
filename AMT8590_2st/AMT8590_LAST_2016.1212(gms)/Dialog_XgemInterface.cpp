// Dialog_XgemInterface.cpp : implementation file
//

#include "stdafx.h"
#include "handler.h"
#include "Dialog_XgemInterface.h"

#include "AMTLotManager.h"
//#include "AClient_Xgem.h"
#include "Global.h"
#include "XGemClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_XgemInterface dialog


CDialog_XgemInterface::CDialog_XgemInterface(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_XgemInterface::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_XgemInterface)
	m_strLotID = _T("");
	m_strPartID = _T("");
	//}}AFX_DATA_INIT
	m_pFont				= NULL;
	m_nXgemOpenFlag		= CONNECT_NO;
	m_nXgemStartFlag	= CONNECT_NO;
}


void CDialog_XgemInterface::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_XgemInterface)
	DDX_Control(pDX, IDC_MSG_HOST_CONNECTOR, m_msgHostConnt);
	DDX_Control(pDX, IDC_MSG_MACHINE_STATUS, m_msgMachineStatus);
	DDX_Control(pDX, IDC_MSG_EQ_CONNECTOR, m_msgEqConnt);
	DDX_Control(pDX, IDC_EXGEMCTRL_GEM, m_hXgem);
	DDX_Text(pDX, IDC_EDIT1, m_strLotID);
	DDX_Text(pDX, IDC_EDIT2, m_strPartID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_XgemInterface, CDialog)
	//{{AFX_MSG_MAP(CDialog_XgemInterface)
	ON_BN_CLICKED(IDC_BUTTON_INITIALIZE, OnButtonInitialize)
	ON_BN_CLICKED(IDC_BUTTON_OFFLINE, OnButtonOffline)
	ON_BN_CLICKED(IDC_BUTTON_ONLINE_LOCAL, OnButtonOnlineLocal)
	ON_BN_CLICKED(IDC_BUTTON_ONLINE_REMOTE, OnButtonOnlineRemote)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_SET, OnButtonAlarmSet)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_CLEAR, OnButtonAlarmClear)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_RUN, OnButtonRun)
	ON_BN_CLICKED(IDC_BUTTON_LOTSTART, OnButtonLotstart)
	ON_BN_CLICKED(IDC_BUTTON_LOTEND, OnButtonLotend)
	ON_BN_CLICKED(IDC_BUTTON_PPID, OnButtonPpid)
	ON_BN_CLICKED(IDC_BUTTON_BUFFER_IN, OnButtonBufferIn)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_TRAY, OnButtonLoadTray)
	ON_BN_CLICKED(IDC_BUTTON_UNLOAD_TRAY, OnButtonUnloadTray)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_MESSAGE(SSM_CLICK, OnCellClick)
	ON_MESSAGE( WM_DRAW_DATA_XGEM, OnDraw_Data_Xgem)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_XgemInterface message handlers
BOOL CDialog_XgemInterface::Init()
{
	
	return TRUE;
}

void CDialog_XgemInterface::OnXGemInitialize(CString strpath)
{
	long nRet;
	
	nRet = m_hXgem.Initialize("C:\\XGem\\EqSample.cfg");

	if(nRet < 0)
	{
		MessageBox("XGem Initialize Failed");

		return;
	}
	m_nXgemOpenFlag	= CONNECT_YES;

	nRet = m_hXgem.Start();

	if(nRet < 0)
	{
		MessageBox("XGem Start Failed");
		
		return;
	}
	m_nXgemStartFlag = CONNECT_YES;
}

BOOL CDialog_XgemInterface::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_pFont = NULL;
	m_pFont = new CFont;
	m_pFont->CreateFont(12,8,0,0,900,0,0,0,0,0,0,DEFAULT_QUALITY,0,"Courier");

	OnLabelSet();

	OnInit_xgem_info();

	st_handler.cwnd_data_xgem = this;

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_XgemInterface::OnLabelSet()
{
	m_msgEqConnt.SetFont(m_pFont);
	m_msgEqConnt.SetWindowText("XGEM �� EQ");
	m_msgEqConnt.SetCenterText();
	m_msgEqConnt.SetColor(BLUE_D);
	m_msgEqConnt.SetGradientColor(BLUE_D);
	m_msgEqConnt.SetTextColor(WHITE_C);
	OnEqConnectStatus(CONNECT_NO);

	m_msgHostConnt.SetFont(m_pFont);
	m_msgHostConnt.SetWindowText("HOST �� XGEM");
	m_msgHostConnt.SetCenterText();
	m_msgHostConnt.SetColor(BLUE_D);
	m_msgHostConnt.SetGradientColor(BLUE_D);
	m_msgHostConnt.SetTextColor(WHITE_C);
	OnHostConnectStatus(CONNECT_NO);

	m_msgMachineStatus.SetFont(m_pFont);
	m_msgMachineStatus.SetWindowText("HOST �� XGEM");
	m_msgMachineStatus.SetCenterText();
	m_msgMachineStatus.SetColor(BLUE_D);
	m_msgMachineStatus.SetGradientColor(BLUE_D);
	m_msgMachineStatus.SetTextColor(WHITE_C);
	OnMachineStatus(MC_OFF_LINE);
}

void CDialog_XgemInterface::OnInit_xgem_info()
{
	TSpread* Grid;
	int row = 7;
	int col = 2;

	Grid = (TSpread*)GetDlgItem( IDC_CUSTOM_XGEM_INFO );
	Grid->SetBool(SSB_EDITMODEPERMANENT, TRUE);
	Grid->SetBool(SSB_SHOWCOLHEADERS, FALSE);
	Grid->SetBool(SSB_SHOWROWHEADERS, FALSE);
	Grid->SetBool(SSB_HORZSCROLLBAR, FALSE);
	Grid->SetBool(SSB_VERTSCROLLBAR, FALSE);
	Grid->SetMaxRows(row);
	Grid->SetMaxCols(col);

	Grid->SetColWidthInPixels(1, 160);
	Grid->SetColWidthInPixels(2, 630);

	for ( int iw = 0; iw < row; iw++)
	{
		Grid->SetRowHeightInPixels(iw + 1, 18 );
		GridFont( IDC_CUSTOM_XGEM_INFO, iw + 1, 1, 15 );
		GridFont( IDC_CUSTOM_XGEM_INFO, iw + 1, 2, 15 );
		GridControl( IDC_CUSTOM_XGEM_INFO, STATIC, iw + 1, 1, 0 );

		GridColor( IDC_CUSTOM_XGEM_INFO, iw + 1, 1, ORANGE_C, BLACK_C );
	}
//	GridMerge( IDC_CUSTOM_XGEM_INFO, 1, 1, 1, 2);
//	GridColor( IDC_CUSTOM_XGEM_INFO, 1, 1, BLACK, WHITE_C );
	GridData( IDC_CUSTOM_XGEM_INFO, 1, 1, ".cfg Info" );

	GridData( IDC_CUSTOM_XGEM_INFO, 2, 1, "LOT Info" );
	GridData( IDC_CUSTOM_XGEM_INFO, 3, 1, "Alarm" );
	GridData( IDC_CUSTOM_XGEM_INFO, 4, 1, "Buffer In" );
	GridData( IDC_CUSTOM_XGEM_INFO, 5, 1, "Load Tray" );
	GridData( IDC_CUSTOM_XGEM_INFO, 6, 1, "Unload Tray" );
	GridData( IDC_CUSTOM_XGEM_INFO, 7, 1, "PPID" );

	GridControl( IDC_CUSTOM_XGEM_INFO, STATIC, 4, 2, 0 );
	GridControl( IDC_CUSTOM_XGEM_INFO, STATIC, 5, 2, 0 );
	GridControl( IDC_CUSTOM_XGEM_INFO, STATIC, 6, 2, 0 );
	GridControl( IDC_CUSTOM_XGEM_INFO, STATIC, 7, 2, 0 );
	if( Grid != NULL )
	{
		Grid = NULL;
		delete Grid;
	}
}


void CDialog_XgemInterface::OnButtonInitialize() 
{
	g_xgem_client.SetGemInit();
	g_xgem_client.XgemInitialize();
	
}

void CDialog_XgemInterface::OnHostConnectStatus(int nStatus)
{
	switch(nStatus)
	{
		case CONNECT_NO:
			m_msgHostConnt.SetColor(GREEN_D);
			m_msgHostConnt.SetGradientColor(GREEN_D);
			m_msgHostConnt.SetTextColor(BLACK_C);
			break;

		case CONNECT_YES:
			m_msgHostConnt.SetColor(GREEN_C);
			m_msgHostConnt.SetGradientColor(GREEN_C);
			m_msgHostConnt.SetTextColor(BLACK_C);
			break;
	}
}

void CDialog_XgemInterface::OnEqConnectStatus(int nStatus)
{
	switch(nStatus)
	{
		case CONNECT_NO:
			m_msgEqConnt.SetColor(GREEN_D);
			m_msgEqConnt.SetGradientColor(GREEN_D);
			m_msgEqConnt.SetTextColor(BLACK_C);
			break;
			
		case CONNECT_YES:
			m_msgEqConnt.SetColor(GREEN_C);
			m_msgEqConnt.SetGradientColor(GREEN_C);
			m_msgEqConnt.SetTextColor(BLACK_C);
			break;
	}
}

void CDialog_XgemInterface::OnMachineStatus(int nStatus)
{
	switch(nStatus)
	{
		case MC_OFF_LINE:
			m_msgMachineStatus.SetWindowText("Off - Line");
			m_msgMachineStatus.SetColor(GREEN_D);
			m_msgMachineStatus.SetGradientColor(GREEN_D);
			m_msgMachineStatus.SetTextColor(BLACK_L);
			break;

		case MC_ON_LINE_LOCAL:
			m_msgMachineStatus.SetWindowText("On - Line(Local)");
			m_msgMachineStatus.SetColor(GREEN_C);
			m_msgMachineStatus.SetGradientColor(GREEN_C);
			m_msgMachineStatus.SetTextColor(BLACK_C);
			break;

		case MC_ON_LINE_REMOTE:
			m_msgMachineStatus.SetWindowText("On - Line(Remote)");
			m_msgMachineStatus.SetColor(GREEN_C);
			m_msgMachineStatus.SetGradientColor(GREEN_C);
			m_msgMachineStatus.SetTextColor(ORANGE_C);
			break;
	}
}

void CDialog_XgemInterface::OnButtonOffline() 
{
	g_xgem_client.SetGemState(0);
	g_xgem_client.XgemEqStatus(0);	
}

void CDialog_XgemInterface::OnButtonOnlineLocal() 
{
	g_xgem_client.SetGemState(1);	
	g_xgem_client.XgemEqStatus(1);
}

void CDialog_XgemInterface::OnButtonOnlineRemote() 
{
	g_xgem_client.SetGemState(2);	
	g_xgem_client.XgemEqStatus(2);
}

void CDialog_XgemInterface::OnButtonAlarmSet() 
{
	g_xgem_client.SetGemAlarmState("10001",1);
	g_xgem_client.XgemAlarmStatus();
	
}

void CDialog_XgemInterface::OnButtonAlarmClear() 
{
	g_xgem_client.SetGemAlarmState("10001",0);
	g_xgem_client.XgemAlarmStatus();
	
}

void CDialog_XgemInterface::OnButtonStop() 
{
	g_xgem_client.SetMachineStatus(MC_STOP);
	g_xgem_client.XgemMachineStatus();
	
}

void CDialog_XgemInterface::OnButtonRun() 
{
	g_xgem_client.SetMachineStatus(MC_RUN);
	g_xgem_client.XgemMachineStatus();	
}

void CDialog_XgemInterface::OnButtonLotstart() 
{
	UpdateData(TRUE);
	g_xgem_client.SetLotStartStatus(m_strLotID, m_strPartID);
	g_xgem_client.XgemLotStart();
	
}

void CDialog_XgemInterface::OnButtonLotend() 
{
	g_xgem_client.SetLotEndStatus(m_strLotID, m_strPartID);
	g_xgem_client.XgemLotEnd();
	
}

void CDialog_XgemInterface::OnButtonPpid() 
{
	CString strHead, strFunc, strPPid;
	CString strTmp;
//	char chtemp[2000];
	UpdateData(TRUE);
//	strFunc = "FUNC=PPID,MODE=0,NAME=UDIMM,BODY=
//	[Machine Serial] Name=BLINE2 
//	[Recipe] Name = UDIMM 
//	[Mode] Interface Mode=1 Device Mode=1 
//	[Time] NTO Time=5 BTO Time=5 HTO Time=5 HTO Max Min Time=15HTO Max Rate Time=5 
//	[Device] Type=0";
	strFunc = "FUNC=PPID_CHANGE,PP_NAME=UDIMM,PP_PATH=D:\\�ڷ�\\AMT8470 Parameter.TXT,";

	strHead.Format("HD=%06d,", strFunc.GetLength());	
	strPPid = strHead+strFunc;
	g_xgem_client.XgemSendPPID();

/*	strFunc += "[Machine Serial]";
	strFunc += "\r\n";
	strTmp.Format("Name=%c%s%c\r\n",'"', "E1-ST-B04", '"');
	strFunc += strTmp;
	strFunc += "\r\n";

	strFunc += "[Recipe]";
	strFunc += "\r\n";
	strTmp.Format("Name=%c%s%c\r\n",'"', "UDIMM", '"');
	strFunc += strTmp;
	strFunc += "\r\n";

	strFunc += "[Mode]";
	strFunc += "\r\n";
	strTmp.Format("Interface Mode=%c%s%c\r\n",'"', "1", '"');
	strFunc += strTmp;
	strTmp.Format("Device Mode=%c%s%c\r\n",'"', "1", '"');
	strFunc += strTmp;
	strFunc += "\r\n";

	strFunc += "[Time]";
	strFunc += "\r\n";
	strTmp.Format("NTO Time=%c%s%c\r\n",'"', "5", '"');
	strFunc += strTmp;
	strTmp.Format("BTO Time=%c%s%c\r\n",'"', "5", '"');
	strFunc += strTmp;
	strTmp.Format("HTO Time=%c%s%c\r\n",'"', "5", '"');
	strFunc += strTmp;
	strTmp.Format("HTO Max Min Time=%c%s%c\r\n",'"', "15", '"');
	strFunc += strTmp;
	strTmp.Format("HTO Max Rate Time=%c%s%c\r\n",'"', "5", '"');
	strFunc += strTmp;
	strFunc += "\r\n";

	strFunc += "[Device]";
	strFunc += "\r\n";
	strTmp.Format("Type=%c%s%c",'"', "0", '"');
	strFunc += strTmp;
	strFunc += ",";
*/
//	strHead.Format("HD=%06d,", strFunc.GetLength());
//	
//	sprintf(st_client_info[0].ch_send, strHead+strFunc);
}

void CDialog_XgemInterface::OnButtonBufferIn() 
{
//	int nCnt = st_basic.n_tray_x * st_basic.n_tray_y;
//	CString strBufferIn;
//	static int nstBufferNo = 0;
//	strBufferIn.Format( "FUNCTION=BUFFER_IN EQPID=SRS-01 LOTID=%s BUFFER_NO=%02d LAST_MDL=NO EMPTY_TRAY=NO POCKET_CNT=%d ", g_lotMgr.GetLotIDAt(0),
//		nstBufferNo + 1, nCnt );
//// 		strBufferIn.Format( "FUNCTION=BUFFER_IN EQPID=PS-GL LOTID=Y001000130 BUFFER_NO=%02d LAST_MDL=NO EMPTY_TRAY=YES POCKET_CNT=%d ", g_lotMgr.GetLotIDAt(0),
//// 			nstBufferNo + 1, nCnt );
//	for( int i=1; i<=nCnt; i++ )
//	{
//		int iIdx = i + nCnt * nstBufferNo;
//		CString strTemp;
//		strTemp.Format( " POCKET_%02d=(ARRAYSN=MZCPA2561127000%05d_3 SERIAL=S11ZNYAC5%05d PPID=KR0NMY6F018511CJ02%05d WWN= BIN=)", i,
//			iIdx, iIdx, iIdx );
//// 			strTemp.Format( " POCKET_%02d=NONE", i);
//		strBufferIn += strTemp;
//	}

//	st_xgem.m_str_bufferin.Format("%s", (LPCTSTR)strBufferIn );
//	g_client_xgem.SetBufferInInfo();
	
}

void CDialog_XgemInterface::OnButtonLoadTray() 
{
	st_xgem.m_str_buffer1_id = "15";
	st_xgem.m_str_buffer1_serial = "S1234Test1234";
	st_xgem.m_strBuf1TactTime = "7.43";
	st_xgem.m_str_buffer2_id = "17";
	st_xgem.m_str_buffer2_serial = "S5678Test5678";
	st_xgem.m_strBuf2TactTime = "6.78";

	g_xgem_client.XgemBufferMove();
	
}

void CDialog_XgemInterface::OnButtonUnloadTray() 
{
	// TODO: Add your control notification handler code here
	
}

BOOL CDialog_XgemInterface::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DestroyWindow();
}

void CDialog_XgemInterface::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(m_pFont != NULL)
	{
		delete m_pFont;
		m_pFont = NULL;
	}
	
	if (m_nXgemStartFlag == CONNECT_YES)
	{
		m_hXgem.Stop();
	}

	if (m_nXgemOpenFlag == CONNECT_YES)
	{
		m_hXgem.Close();
	}
	
	CDialog::OnClose();
}

void CDialog_XgemInterface::OnDestroy() 
{
	CDialog::OnDestroy();
	
	st_handler.cwnd_data_xgem = NULL;
	
}

BEGIN_EVENTSINK_MAP(CDialog_XgemInterface, CDialog)
    //{{AFX_EVENTSINK_MAP(CDialog_XgemInterface)
	ON_EVENT(CDialog_XgemInterface, IDC_EXGEMCTRL_GEM, 2 /* eGEMCommStateChanged */, OneGEMCommStateChangedExgemctrlGem, VTS_I4)
	ON_EVENT(CDialog_XgemInterface, IDC_EXGEMCTRL_GEM, 3 /* eGEMControlStateChanged */, OneGEMControlStateChangedExgemctrlGem, VTS_I4)
	ON_EVENT(CDialog_XgemInterface, IDC_EXGEMCTRL_GEM, 27 /* eXGEMStateEvent */, OneXGEMStateEventExgemctrlGem, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDialog_XgemInterface::OneGEMCommStateChangedExgemctrlGem(long nState) 
{
	// TODO: Add your control notification handler code here
	if (nState == Comm_Disabled)
	{
		OnHostConnectStatus(CONNECT_NO);
	}
	else if(nState == Comm_WaitCRFromHost)
	{
		OnHostConnectStatus(CONNECT_NO);
	}
	else if(nState == Comm_WaitDelay)
	{
	}
	else if(nState == Comm_WaitCRA)
	{
		OnHostConnectStatus(CONNECT_NO);
		OnMachineStatus(MC_OFF_LINE);
	}
	else if(nState == Comm_Communicating)
	{
		OnHostConnectStatus(CONNECT_YES);
		ShowWindow(SW_HIDE);
	}	
}

void CDialog_XgemInterface::OneGEMControlStateChangedExgemctrlGem(long nState) 
{
	// TODO: Add your control notification handler code here
	if (nState == Control_None)
	{
		OnMachineStatus(MC_OFF_LINE);
	}
	else if (nState == Control_EqOffline)
	{
		OnMachineStatus(MC_OFF_LINE);
	}
	else if (nState == Control_AttemptOnline)
	{
		OnMachineStatus(MC_ON_LINE_REMOTE);
	}
	else if (nState == Control_HostOffline)
	{
		OnMachineStatus(MC_OFF_LINE);
	}
	else if (nState == Control_Local)
	{
		OnMachineStatus(MC_ON_LINE_LOCAL);
	}
	else if (nState == Control_Remote)
	{
		OnMachineStatus(MC_ON_LINE_LOCAL);
	}	
}

void CDialog_XgemInterface::OneXGEMStateEventExgemctrlGem(long nState) 
{
	// TODO: Add your control notification handler code here
	if (nState == XGemState_Execute) 
	{
		//bEnable : 0(Disabled), 1(Enabled)
		m_hXgem.GEMSetEstablish(1);
		m_hXgem.GEMEQInitialized(1); 
	}	
}

void CDialog_XgemInterface::GridFont(UINT nID, int row, int col, int size)
{
	TSpread *Grid = (TSpread *)GetDlgItem(nID);
	HFONT font;
	CString strTemp;
	
	font = CreateFont(size, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, "����ü");
	Grid->SetFont(col, row, font, TRUE);

	if( Grid != NULL )
	{
		Grid = NULL;
		delete Grid;
	}
}

void CDialog_XgemInterface::GridMerge(UINT nID, int srow, int scol, int nrow, int ncol)
{
	TSpread *Grid = (TSpread*)GetDlgItem(nID);
	
	Grid->AddCellSpan(scol, srow, ncol, nrow);

	if( Grid != NULL )
	{
		Grid = NULL;
		delete Grid;
	}
}

void CDialog_XgemInterface::GridData(UINT nID, int row, int col, CString data)
{
	TSpread *Grid = (TSpread*)GetDlgItem(nID);

	char szBuf[1024];
	Grid->GetValue(col, row, szBuf);
	if( data == szBuf )
	{
		if( Grid != NULL )
		{
			Grid = NULL;
			delete Grid;
		}
		return;
	}

	Grid->SetValue(col, row, data);

	if( Grid != NULL )
	{
		Grid = NULL;
		delete Grid;
	}
}

void CDialog_XgemInterface::GridControl(UINT nID, int type, int row, int col, int pos)
{
	TSpread *Grid = (TSpread*)GetDlgItem(nID);
	
	SS_CELLTYPE CellType;
	SS_DATEFORMAT dateFormat = { TRUE, '/', IDF_DDMMYY, FALSE };
	SS_TIMEFORMAT tmFormat;
	double a = 0.5;

	switch (type)
	{
		case DATE:			
			Grid->SetTypeDate(&CellType, 0 , &dateFormat, NULL, NULL);
			break;

		case EDIT:
			Grid->SetTypeEdit(&CellType,ES_CENTER,60,SS_CHRSET_CHR,SS_CASE_NOCASE);
			break;

		case COMBO:
			// SetValue(col, row, data); data = ""0"(1����) data = "1"(2����) data = "2"(3����)
			Grid->SetTypeComboBox(&CellType, 0, m_strCombo);
			break;

		case BUTTON:
			if (pos == 0)
			{
				Grid->SetTypeButton(&CellType, SBS_DEFPUSHBUTTON, "Go", NULL, SUPERBTN_PICT_NONE,
					NULL, SUPERBTN_PICT_NONE, SUPERBTN_TYPE_NORMAL, 2, NULL);
			}
			else
			{
				Grid->SetTypeButton(&CellType, SBS_DEFPUSHBUTTON, "Read", NULL, SUPERBTN_PICT_NONE,
					NULL, SUPERBTN_PICT_NONE,SUPERBTN_TYPE_NORMAL, 2, NULL);
			}
			break;

		case STATIC:
			Grid->SetTypeStaticText(&CellType, SS_TEXT_CENTER | SS_TEXT_VCENTER);
			break;

		case TIME:
			tmFormat.b24Hour=TRUE;
			tmFormat.bSpin=FALSE;
			tmFormat.bSeconds=FALSE;
			tmFormat.cSeparator=':';
			Grid->SetTypeTime(&CellType, 0, &tmFormat, NULL, NULL);
			break;

		case PERCENT:
			Grid->SetTypePercentEx(&CellType,ES_LEFTALIGN,2,.01,100,".",0,0,0,0,1.001);
			break;

		case CHECK1:
			Grid->SetTypeCheckBox(&CellType,BS_CENTER, "", 
				"CheckUp", BT_BITMAP,
				"CheckDown", BT_BITMAP,
				"CheckFocusUp", BT_BITMAP,
				"CheckFocusDown", BT_BITMAP,
				"CheckDisabledUp", BT_BITMAP,
				"CheckDisabledDown", BT_BITMAP);
			break;

		case NUMBER:
			Grid->SetTypeNumberEx(&CellType,0, 0, 0, m_nNumMax,0,".",",",0,0,1,0,1.001);
			break;
	}
	
	Grid->SetCellType(col,row,&CellType);

	if( Grid != NULL )
	{
		Grid = NULL;
		delete Grid;
	}
}

void CDialog_XgemInterface::GridColor(UINT nID, int row, int col, COLORREF bk, COLORREF tk)
{
	TSpread *Grid = (TSpread*)GetDlgItem(nID);
	
	COLORREF bk_old, tk_old;
	Grid->GetColor(col, row, &bk_old, &tk_old);
	if( bk_old != bk || tk_old != tk )
	{
		Grid->SetColor(col, row, bk, tk);
		Grid->SetBackColorStyle(SS_BACKCOLORSTYLE_UNDERGRID);
	}

	if( Grid != NULL )
	{
		Grid = NULL;
		delete Grid;
	}
}


void CDialog_XgemInterface::OnCellClick( WPARAM wParam, LPARAM lParam )
{
	LPSS_CELLCOORD lpcc = (LPSS_CELLCOORD)lParam;

	if( wParam == IDC_CUSTOM_XGEM_INFO )
	{

	}
}

LRESULT CDialog_XgemInterface::OnDraw_Data_Xgem( WPARAM wParam,LPARAM lParam )
{
//	m_nSelectedLotIdx = -1;

	OnDisplay_XgemInfo();

	return 0;
}


void CDialog_XgemInterface::OnDisplay_XgemInfo()
{
	GridData( IDC_CUSTOM_XGEM_INFO, 1, 2, "" );
	GridData( IDC_CUSTOM_XGEM_INFO, 2, 2, "" );
	GridData( IDC_CUSTOM_XGEM_INFO, 3, 2, "" );
	GridData( IDC_CUSTOM_XGEM_INFO, 4, 2, "" );
	GridData( IDC_CUSTOM_XGEM_INFO, 5, 2, "" );
	GridData( IDC_CUSTOM_XGEM_INFO, 6, 2, "" );
	GridData( IDC_CUSTOM_XGEM_INFO, 7, 2, "" );

	GridData( IDC_CUSTOM_XGEM_INFO, 1, 2, st_xgem.m_str_xgmInit);
//	GridData( IDC_CUSTOM_XGEM_INFO, 2, 2, )
}
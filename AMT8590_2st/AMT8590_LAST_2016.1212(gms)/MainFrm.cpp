// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Handler.h"

#include "MainFrm.h"

// ******************************************************************************
// ��ȭ ���� �� �ܺ� Ŭ���� �߰�                                                 
// ******************************************************************************
#include "MenuHead.h"		// ȭ�鿡 ���� ��� ���ǵ� Ŭ���� �߰� 
#include "Dialog_Menu.h"	// �޴� ���� ��ȭ ���� Ŭ���� �߰� 
#include "Dialog_HandBarcode.h"
#include "Dialog_About.h"	// ���α׷� About ��ȭ ���� Ŭ���� �߰� 
#include "Dialog_Exit.h"	// ���� ���α׷� ���� ȭ�� Ŭ���� �߰� 
#include "Dialog_Pass_Check.h"
#include "Dialog_Infor.h"
#include "Dialog_Select.h"
#include "Dialog_Message.h"
#include "Dialog_KeyBoard.h"
#include "Dialog_Pass_Check.h"
#include "Public_Function.h"	// ���� ���� �� I/O ���� ���� Ŭ����
#include "RUN_IO_ReadWrite.h"

#include "ComizoaPublic.h"
#include "Cmmsdk.h"

#include "AVersion.h"

#include "io.h" 
#include "FAS_HSSI.h"
#include "FastechPublic_IO.h"

#include "SrcPart/APartShortkey.h"
#include "SrcPart/APartDatabase.h"
#include "SrcPart//PartFunction.h"
#include "SrcPart//APartHandler.h"

#include "COMI_Manager.h"

#include "AMTRegistry.h"
#include "Srcbase/ALocalization.h"

#include "MesEvent.h"
#include "CimEvent.h"
#include "BcrEvent.h"

#include "InterfaceBarcode2.h"
#include "InterfaceBarcode.h"
#include "InterfaceGms.h"

#include "ZebraPrint.h"
#include "VisionClient.h"
#include "VisionServer.h"
#include "BarcodeFormat.h"
#include "FrontServer.h"
#include "BtmClient.h"
#include "8570Client.h"
#include "Screen_Server_Network.h"
#include "AEC_Client.h"
#include "Screen_Set_Network.h"//2015,0109
#include "NextClient.h"
#include "AMTLotManager.h"
#include "XGemClient.h"
#include "SrcBase\ACriticalSection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

st_handler_param			st_handler;

st_setting_param			st_set;
st_message_param			st_msg;
st_time_param				st_time;
st_lamp_param				st_lamp;
st_basic_param				st_basic;
st_alarm_param				alarm;
st_gms_param                st_gms_info; //kwlee 2016.0821
st_dsp_alarm_param			st_alarm;
st_work_param				st_work;
st_modulemap_size			st_modulemap;
st_motor_param				st_motor[MOTOR_COUNT];
st_path_param				st_path;
st_nw_param					st_NW;
st_sync_param				st_sync;
st_ctlbd_param				st_ctlbd;
st_ctlbd_param				st_reco_ctlbd;  
st_serial_param				st_serial;
struct st_serial_info		rs_232;//20131115
st_linearmotion_param		st_linearmot[8];
st_coordmotion_param		st_coordmot[16];
st_barcode_param 			st_barcode;
st_ani_param				st_ani;//2014.0821
_st_Color				    g_Color;

CAnimate					m_Animate;

st_time_database			st_timedb;
st_alarm_database			st_alarmdb;
st_ground_database			st_grounddb;

st_buffer_database			st_bufferdb;

st_part_motor_info			st_motor_info;
st_part_info				st_part;
st_buffer_tray_param		st_buffer_tray[MAX_SITE_INFO];

st_boat_database			st_boatdb;
st_xgemdata					st_xgem;
st_vision					st_vis;
st_variable_param			st_var;
// ���̸� �߰� [2013.11.12]
// �Ҽ� ��� ���� ����ü �߰�
st_client_param	st_client[15];
st_server_param	st_server[15];

st_testreference_param      st_testreference;	// TEST SITEȭ�� ȯ�� ���� ���� ���� ����ü ���� 
st_test_param			st_test;			// �۾� ��� ���� ���� ����ü ����
tagBCR_PARAM	stBCR[5];
tagLOT_PARAM	stLOT[MAX_LOT_];
st_step_param				st_step;
st_other_param				st_other;
st_bcrinfo_param st_bcrinfo[4];
st_density_info_param st_density_info[6][4];
st_idbuffer_info_param	st_idbuff_info[MAX_SHIFT_DATA_NUM];

st_density_feeder st_den_feeder[6];
st_density_rbt st_den_rbt[2];
st_barcode_rbt st_bcr_rbt[2];
st_barcode_feeder st_bcr_feeder[4];
st_top_rbt_param st_top_rbt[2];
st_unload_rbt st_uld_rbt;
st_reject_rbt st_rej_rbt;
st_mes_data_param	st_mes_data;
tagPRODUCT_PARAM	stMapPk[13];
st_copy_data			*st_copydata;

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_NCLBUTTONDBLCLK()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCRBUTTONDBLCLK()
	ON_WM_NCRBUTTONDOWN()
	ON_COMMAND(ID_MAIN, OnMain)
	ON_COMMAND(ID_BASIC, OnBasic)
	ON_COMMAND(ID_SETTING, OnSetting)
	ON_COMMAND(ID_WAIT, OnWait)
	ON_COMMAND(ID_MOTOR, OnMotor)
	ON_COMMAND(ID_IO, OnIo)
	ON_COMMAND(ID_LIST, OnList)
	ON_COMMAND(ID_LEVEL, OnLevel)
	ON_COMMAND(ID_SAVE, OnSave)
	ON_COMMAND(ID_ALARM, OnAlarm)
	ON_COMMAND(ID_ABOUT, OnAbout)
	ON_COMMAND(ID_RESET, OnReset)
	ON_COMMAND(ID_LOCK, OnLock)
	ON_COMMAND(ID_EXIT, OnExit)
	ON_COMMAND(ID_MOT_TEACH, OnMotTeach)
	ON_WM_TIMER()
	ON_COMMAND(ID_MOT_SPEED, OnMotSpeed)
	ON_COMMAND(ID_SET_INTERFACE, OnSetInterface)
	ON_COMMAND(ID_SET_MAINTENANCE, OnSetMaintenance)
	ON_COMMAND(ID_ADMIN, OnAdmin)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_LIST_OPER, OnListOper)
	ON_COMMAND(ID_LIST_DATAVIEW, OnListDataview)
	ON_COMMAND(ID_FILE_EDITOR, OnFileEditor)
	ON_WM_NCMBUTTONDBLCLK()
	ON_COMMAND(ID_SET_BARCODE, OnSetBarcode)
	ON_COMMAND(ID_ECSERVER, OnEcserver)
	ON_COMMAND(ID_SET_NETWORK, OnSetNetwork)//2015,0109
	ON_WM_COPYDATA()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_FORM_CHANGE, OnViewChangeMode)					// Post Message�� ���� ȭ�� ��ȯ ����� ����� ���� �޽��� ����
	ON_MESSAGE(WM_MAINFRAME_WORK, OnMainframe_Work)
	ON_MESSAGE(WM_MAIN_EVENT, OnMainMessageEvent)					// �̺�Ʈ ���� �޽���
	ON_MESSAGE(WM_MAIN_XEVENT, OnMainMessageXCloseEvent)					// �̺�Ʈ ���� �޽���
//	ON_MESSAGE(WM_COMM_DATA, OnCommunication)						// RS-232C �ø��� ��Ʈ ���� �޽���
	ON_MESSAGE(WM_COMM_EVENT, OnCommunicationEvent)					// RS-232C �ø��� ��Ʈ �̺�Ʈ ���� �޽���
	ON_MESSAGE(WM_DATA_SEND, OnDataSend)							// RS-232C �ø��� ��Ʈ ���� ������ �۽� �޽���
	ON_MESSAGE(WM_SERIAL_PORT, OnSerialPort)	//20131210
	ON_MESSAGE(WM_CLIENT_MSG_1, OnCommand_Client_1)					// server
	ON_MESSAGE(WM_CLIENT_MSG_2, OnCommand_Client_2)					// Rear Client
	ON_MESSAGE(WM_CLIENT_MSG_3, OnCommand_Client_3)					// g_8570_client
	ON_MESSAGE(WM_CLIENT_MSG_4, OnCommand_Client_4)					// g_next_client
	ON_MESSAGE(WM_CLIENT_MSG_5, OnCommand_Client_5)					// clsEC_Client
	ON_MESSAGE(WM_CLIENT_MSG_6, OnCommand_Client_6)					// ���� ���õ� �۾�(Reserved)
	ON_MESSAGE(WM_COMM_WORK, OnBcrCommSerial)					// Network���õ� �۾��� ����Ѵ�.
	ON_MESSAGE(WM_CLIENT_MSG_7, OnZebraPrint_Client_1)				// jtkim barcode print 
	ON_MESSAGE(WM_CLIENT_MSG_8, OnZebraPrint_Client_2)				// jtkim barcode print 
	ON_MESSAGE(WM_CLIENT_MSG_9, OnZebraPrint_Client_3)				// jtkim barcode print 
	ON_MESSAGE(WM_CLIENT_MSG_10, OnZebraPrint_Client_4)				// jtkim barcode print 
	ON_MESSAGE(WM_CLIENT_MSG_11, OnLabel_Client)						// jtkim barcode print 
	ON_MESSAGE(WM_CLIENT_MSG_12, OnBarcode_Client)					// jtkim barcode print 
	ON_MESSAGE(WM_CLIENT_MSG_13, OnTop_Client)						// jtkim barcode print 
	ON_MESSAGE(WM_CLIENT_MSG_14, OnBottom_Client)					// jtkim barcode print 
// 	ON_MESSAGE(WM_CLIENT_MSG_11, OnBcrFormat1_Client)				// jtkim barcode print 
// 	ON_MESSAGE(WM_CLIENT_MSG_12, OnBcrFormat2_Client)				// jtkim barcode print 
// 	ON_MESSAGE(WM_CLIENT_MSG_13, OnBcrFormat3_Client)				// jtkim barcode print 
// 	ON_MESSAGE(WM_CLIENT_MSG_14, OnBcrFormat4_Client)				// jtkim barcode print 
	ON_MESSAGE(WM_SERVER_MSG_1, OnCommand_Server_1)					// Front Server
	ON_MESSAGE(WM_SERVER_MSG_3, OnZebraPrint_Server_1)				// jtkim barcode print //2014,1104 ysj WM_SERVER_MSG_2 -> 3
	ON_MESSAGE(WM_SERVER_MSG_4, OnZebraPrint_Server_2)				// jtkim barcode print //2014,1104 ysj WM_SERVER_MSG_3 -> 4
	ON_MESSAGE(WM_SERVER_MSG_5, OnZebraPrint_Server_3)				// jtkim barcode print //2014,1104 ysj WM_SERVER_MSG_4 -> 5
	ON_MESSAGE(WM_SERVER_MSG_6, OnZebraPrint_Server_4)				// jtkim barcode print //2014,1104 ysj WM_SERVER_MSG_5 -> 6
	ON_MESSAGE(WM_SERVER_MSG_7, OnLabel_Server)						// jtkim barcode print 
	ON_MESSAGE(WM_SERVER_MSG_8, OnBarcode_Server)					// jtkim barcode print 
	ON_MESSAGE(WM_SERVER_MSG_9, OnTop_Server)						// jtkim barcode print 
	ON_MESSAGE(WM_SERVER_MSG_10, OnBottom_Server)					// jtkim barcode print 


END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	g_db.ChangeSection( ST_STOP );
	st_timedb.mnSectionBuffer = dSTOP;

//	FAS_IO.mn_simulation_mode = 0;
//	COMI.mn_simulation_mode = 0;

	OnMain_Var_Default_Set();

	MyJamData.On_Alarm_Info_Load();

	//==============================================================//
	// [�ʱ�ȭ] ���� ���� ����
	// ���̸� �߰� [2014.08.26]
	//==============================================================//
	int i=0;
	for(i=0; i<15; i++)
	{
		m_pClient[i] = NULL;
		m_pServer[i] = NULL;
		
		st_client[i].n_connect = CTL_NO;
		st_server[i].n_connect = CTL_NO;
	}
	//--------------------------------------------------------------//


	nSmaCount1 = nSmaCount2 = 0;

	for ( int j = 0; j < 10; j++)
	{
		nSmaCount3[j] = nSmaServer[j] = 0;
	}
	
	m_timeLastDay = AMTRegistry::RegReadTime();

	cLOG.OnSetPathLogEvent();
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CString str_temp;
	int i = 0, j = 0;

	st_handler.hWnd = GetSafeHwnd() ;  // ���� �����ӿ� ���� �ڵ� ���� ����

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_wndToolBar.SetBorders(1, 1, 1, 1);

	if (!m_wndToolBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndToolBar.ModifyStyle(0, TBSTYLE_FLAT);

	m_wndToolBar.LoadTrueColorToolBar(TOOLBAR_DRAW_BUTTON_WIDTH,
								   IDB_TOOLBAR_DRAW,
		                           IDB_TOOLBAR_DRAW_HOT,
								   IDB_TOOLBAR_DRAW_DISABLED);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_TOP);
	EnableDocking(CBRS_ALIGN_TOP);
//	DockControlBar(&m_wndToolBar);					// Docking ����� �ƴϴ�.

	// **************************************************************************
    // Text ���� Icon ������ ����
    // **************************************************************************
	SIZE size1={32, 32}, size2={62, 49};
	m_wndToolBar.SetSizes(size2, size1);
	// **************************************************************************

	// **************************************************************************
    // Ÿ��Ʋ ���� ��� Initial Dialog bar ����
    // **************************************************************************
	if (!m_wndTitleBar.Create(this, IDD_DIALOG_TITLE, CBRS_ALIGN_TOP, IDD_DIALOG_TITLE))
	{
		TRACE0("Failed to create my init bar\n");
		return -1;      // fail to create
	}
	st_handler.cwnd_title = &m_wndTitleBar;
	// **************************************************************************
	
	mcls_m_basic.OnAdmin_Data_Load();
	mcls_m_basic.OnMotorSpeed_Set_Data_Load();
	mcls_m_basic.OnBasic_Data_Load();							// ������ ���� ���� ���� ������ �ε��ϴ� �Լ�
	mcls_m_basic.OnWaitTime_Data_Load();
	mcls_m_basic.OnMaintenance_Data_Load();
	mcls_m_basic.OnInterface_Data_Load();//20131115
//	mcls_m_basic.OnBarcode_Label_Data_Load();

	//////////////////////////////////////////////////////////////////////////
	st_var.n_using_barcode = -1;


	if( st_basic.nBcrFeederUse[2] == CTL_YES && st_basic.nBcrFeederUse[3] == CTL_YES )
	{
		st_var.n_use_barcode[2] = EMBS_PASS;
		st_var.n_use_barcode[3] = EMBS_PASS;
		st_var.n_using_barcode = 1;
	}
	else if( st_basic.nBcrFeederUse[0] == CTL_YES && st_basic.nBcrFeederUse[1] == CTL_YES )
	{
		st_var.n_use_barcode[0] = EMBS_PASS;
		st_var.n_use_barcode[1] = EMBS_PASS;
		st_var.n_using_barcode = 0;
	}
	
	if( st_var.n_using_barcode == -1 )
	{
		st_basic.nBcrFeederUse[2] = CTL_YES;
		st_basic.nBcrFeederUse[3] = CTL_YES;
		st_var.n_use_barcode[2] = EMBS_PASS;
		st_var.n_use_barcode[3] = EMBS_PASS;
		st_var.n_using_barcode = 1;
	}
	//////////////////////////////////////////////////////////////////////////

	// **************************************************************************
    // ����Ʈ ���� ��� Initial Dialog bar ����
	// -> ���� �� �ؿ� ��ġ�ϵ��� �Ϸ��� �� �κ��� ���� �� ���� �κ� ���� �ø���.
    // **************************************************************************
	if (!m_wndListBar.Create(this, IDD_DIALOG_LIST, CBRS_ALIGN_BOTTOM, IDD_DIALOG_LIST))
	{
		TRACE0("Failed to create my information bar\n");
		return -1;      // fail to create
	}
	st_handler.cwnd_list = &m_wndListBar;
	// **************************************************************************

	g_ver.SetVersion();
	
	// **************************************************************************
    // ���� ���α׷��� ���� Ÿ��Ʋ ���� ���
    // ************************************************************************** 
	SetWindowText( g_ver.GetStrVersion() );	// Ÿ��Ʋ ���� ��� 
	CenterWindow();					// ���� ���� ���α׷��� �� �߾ӿ� ��ġ
	// **************************************************************************

	// **************************************************************************
    // ���� ���� �� I/O ���� �ʱ�ȭ �� ��� ��Ʈ Ŭ���� �۾� �����Ѵ�        
    // **************************************************************************
	g_ioMgr.IO_Board_Initialize();				// IO ���� ���̺귯�� �ʱ�ȭ �Լ�
	RUN_IO_ReadWrite.Init_Total_IORead(0);
	g_ioMgr.OnSet_IO_Out_Port_Clear();			// I/O ������ ��� ��Ʈ �ʱ�ȭ �Լ�
	
	g_comiMgr.SetMotBoardInit( COMI.Initialize_MotBoard(st_path.mstr_motor) );	// MOTOR ���� �ʱ�ȭ ���� �˻��Ѵ�
	if( st_handler.mn_virtual_mode )
		g_comiMgr.SetMotBoardInit( BD_GOOD );

	if (st_handler.cwnd_list != NULL)
	{
		st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, MACHINE_INFO);
	}

	if (st_handler.cwnd_title != NULL)	
	{
		st_handler.cwnd_title->PostMessage(WM_STATUS_CHANGE, MACHINE_STATUS, dSTOP); 
		st_handler.cwnd_title->PostMessage(WM_STATUS_CHANGE, DEVICE_MODE, 0);
		st_handler.cwnd_title->PostMessage(WM_STATUS_CHANGE, LEVEL_MODE, 0);
		st_handler.cwnd_title->PostMessage(WM_STATUS_CHANGE, ONLINE_MODE, 0);
		st_handler.cwnd_title->PostMessage(WM_STATUS_CHANGE, EMPTYTRAY_MODE, 0);
		st_handler.cwnd_title->PostMessage(WM_STATUS_CHANGE, XGEM_MODE, dSTOP); 

		if(st_basic.mn_outconv == CTL_YES)
			st_handler.cwnd_title->PostMessage(WM_STATUS_CHANGE, CONV_MODE, 2);
		else
		{
			if(st_basic.mn_outtbox == 0)
				st_handler.cwnd_title->PostMessage(WM_STATUS_CHANGE, CONV_MODE, 0);
			else
				st_handler.cwnd_title->PostMessage(WM_STATUS_CHANGE, CONV_MODE, 1);
		}
	}

	g_comiMgr.OnMain_Motor_Setting();
	
	OnMain_Thread_Creating();
	
	OnMain_Port_Create();					// Serial Port�� �����Ѵ�.

//
//
//	st_client[7].str_ip = "127.0.0.1";
//	st_client[7].n_port = 20001;
//
//	st_client[8].str_ip = "127.0.0.1";
//	st_client[8].n_port = 20001;
//
//	st_client[9].str_ip = "127.0.0.1";
//	st_client[9].n_port = 20001;
//
//	st_server[0].n_port = 9900;
//	st_server[1].n_port = 9901;
//	st_server[2].n_port = 9902;
//	st_server[3].n_port = 9903;
//	st_server[4].n_port = 9904;
//	st_server[5].n_port = 9905;
// 	st_server[6].n_port = 9906;
// 	st_server[7].n_port = 9907;
// 	st_server[8].n_port = 9908;
// 	st_server[9].n_port = 9909;

	st_client[CLS_OTHERS].str_ip = "127.0.0.1";
	st_client[CLS_OTHERS].n_port = 10056;


	// **************************************************************************
    // �ʱ�ȭ ���� ȭ������ ��ȯ�Ͽ� ��� �ʱ�ȭ �۾� �����Ѵ�                   
    // **************************************************************************
	::PostMessage(st_handler.hWnd, WM_FORM_CHANGE, 1, 3);  // �ʱ�ȭ ���� ȭ�� ��ȯ 
// 	::SendMessage(st_handler.hWnd, WM_CLIENT_MSG_1, CLIENT_CONNECT, 0);// CLS_ECSERVER���� Ŭ���̾�Ʈ
	::SendMessage(st_handler.hWnd, WM_CLIENT_MSG_2, CLIENT_CONNECT, 1);// CLS_BOTTOM
	::SendMessage(st_handler.hWnd, WM_CLIENT_MSG_3, CLIENT_CONNECT, 2);// CLS_8570
// 	::SendMessage(st_handler.hWnd, WM_CLIENT_MSG_4, CLIENT_CONNECT, 3);// CLS_NEXT
// 	::SendMessage(st_handler.hWnd, WM_CLIENT_MSG_5, CLIENT_CONNECT, 4);// CLS_FORMAT
	::SendMessage(st_handler.hWnd, WM_CLIENT_MSG_6, CLIENT_CONNECT, 5);// CLS_OTHERS
	::SendMessage(st_handler.hWnd, WM_CLIENT_MSG_7, CLIENT_CONNECT, 6);// CLS_BCR_PRINTER1
	::SendMessage(st_handler.hWnd, WM_CLIENT_MSG_8, CLIENT_CONNECT, 7);// CLS_BCR_PRINTER2	
	::SendMessage(st_handler.hWnd, WM_CLIENT_MSG_9, CLIENT_CONNECT, 8);// CLS_BCR_PRINTER3
	::SendMessage(st_handler.hWnd, WM_CLIENT_MSG_10, CLIENT_CONNECT, 9);// CLS_BCR_PRINTER4
	::PostMessage(st_handler.hWnd, WM_SERVER_MSG_1, SERVER_CONNECT, 0); // EC SERVER1
	::PostMessage(st_handler.hWnd, WM_SERVER_MSG_2, SERVER_CONNECT, 1); // EC SERVER2
	::PostMessage(st_handler.hWnd, WM_SERVER_MSG_3, SERVER_CONNECT, 2); // barcode print
	::PostMessage(st_handler.hWnd, WM_SERVER_MSG_4, SERVER_CONNECT, 3); // barcode print
	::PostMessage(st_handler.hWnd, WM_SERVER_MSG_5, SERVER_CONNECT, 4); // barcode print
	::PostMessage(st_handler.hWnd, WM_SERVER_MSG_6, SERVER_CONNECT, 5); // barcode print
	::PostMessage(st_handler.hWnd, WM_SERVER_MSG_7, SERVER_CONNECT, 6); // Label Vision
	::PostMessage(st_handler.hWnd, WM_SERVER_MSG_8, SERVER_CONNECT, 7); // Barcode
	::PostMessage(st_handler.hWnd, WM_SERVER_MSG_9, SERVER_CONNECT, 8); // Top
	::PostMessage(st_handler.hWnd, WM_SERVER_MSG_10, SERVER_CONNECT, 9); // Btm
	

	// **************************************************************************

	SetTimer(TMR_MAIN_REFRESH, 500, NULL);  // ����Ʈ ���� ���� Ÿ�̸�
	SetTimer(TMR_FILE_CREATE, 1000, NULL);  // ����Ʈ ���� ���� Ÿ�̸�
// 	SetTimer(TMR_SMEMA_REAR_CHK, 2000, NULL);
	SetTimer(TMR_GMS_CHK, 10000*60*32, NULL);
	SetTimer(TMR_MAT_CHK, 60000, NULL);
	if (st_handler.cwnd_title != NULL)	
	{
		st_handler.cwnd_title->PostMessage(WM_STATUS_CHANGE, SMEMA_ONOFF, 0);
	}

	::PostMessage(st_handler.hWnd, WM_MAINFRAME_WORK, 1005, 0);//Xgem
	// �׽�Ʈ��.
//	st_handler.mn_level_teach =  TRUE;//2014,0606 ybs

	if( st_handler.cwnd_title )
		st_handler.cwnd_title->PostMessage(WM_STATUS_CHANGE, LEVEL_MODE, 0);

	st_handler.cwnd_data_lot = NULL;
	st_handler.cwnd_data_testsite = NULL;
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if ( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE | WS_SYSMENU | WS_MAXIMIZEBOX;
	cs.style &= ~FWS_ADDTOTITLE;								// ȭ�� Ÿ��Ʋ ���� ���� �����ϵ��� ��Ÿ�� ���� 
	cs.lpszClass=((CHandlerApp*)AfxGetApp())->GetClassName();	// ���� ���� ���α׷��� ���� Ŭ���� �̸��� ��´�(Need for Single Instance)

	if (cs.hMenu != NULL)
	{
		::DestroyMenu(cs.hMenu);
		cs.hMenu = NULL;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnNcLButtonDblClk(UINT nHitTest, CPoint point) 
{
	//Ÿ��Ʋ�ٸ� Ŭ�� ������ ���Ͻ�Ų��.
	if (nHitTest == HTCAPTION) return;
	
	CFrameWnd::OnNcLButtonDblClk(nHitTest, point);
}

void CMainFrame::OnNcLButtonDown(UINT nHitTest, CPoint point) 
{
	//Ÿ��Ʋ�ٸ� Ŭ�� ������ ���Ͻ�Ų��.
	if (nHitTest == HTCAPTION) return;
	
	CFrameWnd::OnNcLButtonDown(nHitTest, point);
}

void CMainFrame::OnNcRButtonDblClk(UINT nHitTest, CPoint point) 
{
	//Ÿ��Ʋ�ٸ� Ŭ�� ������ ���Ͻ�Ų��.
	if (nHitTest == HTCAPTION) return;
	
	CFrameWnd::OnNcRButtonDblClk(nHitTest, point);
}

void CMainFrame::OnNcRButtonDown(UINT nHitTest, CPoint point) 
{
	//Ÿ��Ʋ�ٸ� Ŭ�� ������ ���Ͻ�Ų��.
	if (nHitTest == HTCAPTION) return;
	
	CFrameWnd::OnNcRButtonDown(nHitTest, point);
}

void CMainFrame::OnNcMButtonDblClk(UINT nHitTest, CPoint point) 
{
	if(nHitTest == HTCAPTION)		// Ÿ��Ʋ�� ����Ŭ���̸� ����
		return;
	
	//     if(nHitTest == HTMAXBUTTON)    // MAX��ư Ŭ���̸� ����
	//         return;		
	
	CFrameWnd::OnNcMButtonDblClk(nHitTest, point);
}

//SysCommand�� �ִ�ȭ�� ���ƾ� ..
// void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
// {	
//     if(nID == SC_MAXIMIZE)    // �ִ�ȭ ����̸� ����		
//         return;
// 	
//     CMDIFrameWnd::OnSysCommand(nID, lParam);
// 	
// }


BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->hwnd == m_wndToolBar.m_hWnd)
	{
		if (m_wndToolBar.IsFloating())  // ���ٰ� �÷��� �� ��쿡 �ٽ� ȭ�� ��ܿ� ���� 
		{
			m_wndToolBar.EnableDocking(CBRS_ALIGN_TOP);
			EnableDocking(CBRS_ALIGN_TOP);
			DockControlBar(&m_wndToolBar);
		}
	}


	g_ShortKey.CheckKeyboard( pMsg );
	
	return CFrameWnd::PreTranslateMessage(pMsg);
}

void CMainFrame::OnMain() 
{
	// **************************************************************************
    // ȭ�� �� ��ȯ �Ұ����� ���� �˻��Ѵ�.                                      
    // **************************************************************************
	// int nmenu_chk = OnMenu_Change_Checking(); // �޴� ��� ���� ���� �˻� �Լ�
	// if (nmenu_chk != TRUE)  return;
	
	if (GetActiveView()->IsKindOf(RUNTIME_CLASS(CScreen_Main)))   return;
	OnSwitchToForm(IDW_SCREEN_MAIN);
}

void CMainFrame::OnBasic() 
{
	// **************************************************************************
    // ȭ�� �� ��ȯ �Ұ����� ���� �˻��Ѵ�.
    // **************************************************************************
	int nmenu_chk = OnMenu_Change_Checking(); // �޴� ��� ���� ���� �˻� �Լ�
	if (nmenu_chk != TRUE)  return;
	
	if (st_handler.mn_level_teach !=  TRUE)
	{
		if (st_handler.mn_level_maint !=  TRUE) 
		{
			OnLevel();
			if (st_handler.mn_level_teach !=  TRUE)
			{
				if (st_handler.mn_level_maint !=  TRUE)  return;
			}
		}
	}
	
	if (GetActiveView()->IsKindOf(RUNTIME_CLASS(CScreen_Basic)))   return;
	OnSwitchToForm(IDW_SCREEN_BASIC);
}

void CMainFrame::OnSetting() 
{
	CDialog_Menu menu_dlg;
	// **************************************************************************
    // ȭ�� �� ��ȯ �Ұ����� ���� �˻��Ѵ�.                                      
    // **************************************************************************
	int nmenu_chk = OnMenu_Change_Checking(); // �޴� ��� ���� ���� �˻� �Լ�
	if (nmenu_chk != TRUE)  return;
	
	// **************************************************************************
	// �޴� ��� �Ұ����� ��쿡 ���� ���� �˻��Ѵ�                              
	// -> ����Ʈ ��� �Ǵ� ƼĪ ��尡 �����Ǿ� �ִ��� �˻�                      
	// **************************************************************************
	if (st_handler.mn_level_teach !=  TRUE)
	{
		if (st_handler.mn_level_maint !=  TRUE) 
		{
			OnLevel();
			if (st_handler.mn_level_teach !=  TRUE)
			{
				if (st_handler.mn_level_maint !=  TRUE)  return;
			}
		}
	}
	// **************************************************************************
	 
// 	if (GetActiveView()->IsKindOf(RUNTIME_CLASS(CScreen_Set_Maintenance)))   return;
// 	OnSwitchToForm(IDW_SCREEN_SET_MAINTENANCE);	
//
	st_msg.mstr_parent_menu = "Setting Screen";  // ���� ���õ� �� �޴� ���� ����
	int nResponse = menu_dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}

}

void CMainFrame::OnWait() 
{
	// **************************************************************************
    // ȭ�� �� ��ȯ �Ұ����� ���� �˻��Ѵ�.                                      
    // **************************************************************************
	int nmenu_chk = OnMenu_Change_Checking(); // �޴� ��� ���� ���� �˻� �Լ�
	if (nmenu_chk != TRUE)  return;
	
	// **************************************************************************
	// �޴� ��� �Ұ����� ��쿡 ���� ���� �˻��Ѵ�                              
	// -> ����Ʈ ��� �Ǵ� ƼĪ ��尡 �����Ǿ� �ִ��� �˻�                      
	// **************************************************************************
	if (st_handler.mn_level_teach !=  TRUE)
	{
		if (st_handler.mn_level_maint !=  TRUE) 
		{
			OnLevel();
			if (st_handler.mn_level_teach !=  TRUE)
			{
				if (st_handler.mn_level_maint !=  TRUE)  return;
			}
		}
	}
	// **************************************************************************
	
	if (GetActiveView()->IsKindOf(RUNTIME_CLASS(CScreen_Wait_Time)))   return;
	OnSwitchToForm(IDW_SCREEN_WAIT_TIME);
}

void CMainFrame::OnMotor() 
{
	int nRet, nRet2;

	CDialog_Menu menu_dlg;
	
	int nmenu_chk = OnMenu_Change_Checking(); // �޴� ��� ���� ���� �˻� �Լ�
	if (nmenu_chk != TRUE)  return;
	
	// **************************************************************************
	// �޴� ��� �Ұ����� ��쿡 ���� ���� �˻��Ѵ�                              
	// -> ����Ʈ ��� �Ǵ� ƼĪ ��尡 �����Ǿ� �ִ��� �˻�                      
	// **************************************************************************
	if (st_handler.mn_level_teach !=  TRUE)
	{
//		if (st_handler.mn_level_maint !=  TRUE) 
//		{
			OnLevel();
			if (st_handler.mn_level_teach !=  TRUE)
			{
				return;
//				if (st_handler.mn_level_maint !=  TRUE)  return;
			}
//		}
	}
	// **************************************************************************

	nRet = g_ioMgr.get_in_bit(st_io.i_front_select_switch_chk, IO_OFF);
	nRet2 = g_ioMgr.get_in_bit(st_io.i_rear_select_switch_chk, IO_OFF);
	
	if (nRet == IO_ON && nRet2 == IO_ON)
	{			
		return;
	}
	
	st_msg.mstr_parent_menu = "Motor Screen";  // ���� ���õ� �� �޴� ���� ����
	int nResponse = menu_dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
}

void CMainFrame::OnIo() 
{
	int nRet, nRet2;
	// **************************************************************************
    // ȭ�� �� ��ȯ �Ұ����� ���� �˻��Ѵ�.                                      
    // **************************************************************************
	int nmenu_chk = OnMenu_Change_Checking(); // �޴� ��� ���� ���� �˻� �Լ�
	if (nmenu_chk != TRUE)  return;
	
	// **************************************************************************
	// �޴� ��� �Ұ����� ��쿡 ���� ���� �˻��Ѵ�                              
	// -> ����Ʈ ��� �Ǵ� ƼĪ ��尡 �����Ǿ� �ִ��� �˻�                      
	// **************************************************************************
	if (st_handler.mn_level_teach !=  TRUE)
	{
		if (st_handler.mn_level_maint !=  TRUE) 
		{
			OnLevel();
			if (st_handler.mn_level_teach !=  TRUE)
			{
				if (st_handler.mn_level_maint !=  TRUE)  return;
			}
		}
	}
	// **************************************************************************
	
	nRet = g_ioMgr.get_in_bit(st_io.i_front_select_switch_chk, IO_OFF);
	nRet2 = g_ioMgr.get_in_bit(st_io.i_rear_select_switch_chk, IO_OFF);
	
	if (nRet == IO_ON && nRet2 == IO_ON)
	{			
		return;
	}

	if (GetActiveView()->IsKindOf(RUNTIME_CLASS(CScreen_IO)))   return;
	OnSwitchToForm(IDW_SCREEN_IO);
}

void CMainFrame::OnList() 
{
	CDialog_Menu menu_dlg;
	
	int nmenu_chk = OnMenu_Change_Checking(); // �޴� ��� ���� ���� �˻� �Լ�
	if (nmenu_chk != TRUE)  return;
	
	// ������ ���� �ְ� ����. -�̻�� �븮- 2K4/11/05/ViboX
	/* ************************************************************************** */
	/* �޴� ��� �Ұ����� ��쿡 ���� ���� �˻��Ѵ�                               */
	/* -> ����Ʈ ��� �Ǵ� ƼĪ ��尡 �����Ǿ� �ִ��� �˻�                       */
	/* ************************************************************************** */
	if (st_handler.mn_level_teach !=  TRUE)
	{
		if (st_handler.mn_level_maint !=  TRUE) 
		{
			OnLevel();
			if (st_handler.mn_level_teach !=  TRUE)
			{
				if (st_handler.mn_level_maint !=  TRUE)  return;
			}
		}
	}
	/* ************************************************************************** */
	
	st_msg.mstr_parent_menu = "List Screen";  // ���� ���õ� �� �޴� ���� ����
	int nResponse = menu_dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
}

void CMainFrame::OnLevel() 
{
	int n_response;  // ��ȭ ���ڿ� ���� ���� �� ���� ���� ���� 
	
	/* ************************************************************************** */
    /* ȭ�� �� ��ȯ �Ұ����� ���� �˻��Ѵ�.                                       */
    /* ************************************************************************** */
	if (st_handler.mn_menu_lock != FALSE)  return;
	if (st_handler.mn_system_lock != FALSE)  return;  // ���� �ý��� Lock ������ ��� ���� 
	
	st_handler.mstr_pass_level = "LevelChange";
	
	CDialog_Pass_Check pass_dlg;
	
	n_response = pass_dlg.DoModal();
	
	if (n_response == IDOK)
	{
		
	}
	else if (n_response == IDCANCEL)
	{
		
	}
}

void CMainFrame::OnSave() 
{
	int n_response;  // ��ȭ ���� ���� �÷���
	
	/* ************************************************************************** */
    /* ȭ�� �� ��ȯ �Ұ����� ���� �˻��Ѵ�.                                       */
    /* ************************************************************************** */
	if (st_handler.mn_menu_lock != FALSE)  return;
	if (st_handler.mn_system_lock != FALSE)  return;  // ���� �ý��� Lock ������ ��� ���� 
	
	CDialog_Select  select_dlg;
	
	st_msg.mstr_confirm_msg = _T("Main : All Setting Data Save?");
	
	n_response = select_dlg.DoModal();
	
	if (n_response == IDOK)
	{
		st_handler.mn_menu_lock = TRUE;
		
		OnExitData_Saving();					// ȭ�鿡 ������ ��� ������ ���� �Լ�
		
		st_handler.mn_menu_lock = FALSE;
	}
	else if (n_response == IDCANCEL)
	{
		
	}
}

void CMainFrame::OnAlarm() 
{
	/* ************************************************************************** */
    /* ��޸��� �˶� ȭ�� ����Ѵ�                                                */
	/* -> ���� �˶� ȭ�� ��µ� ��쿡�� �ش� ȭ�鿡 ��Ŀ���� ����                */
    /* ************************************************************************** */
	if (mp_alarm_dlg != NULL)  mp_alarm_dlg->SetFocus();
	else
	{
		mp_alarm_dlg = new CDialog_Alarm;
		mp_alarm_dlg->Create(this);
		mp_alarm_dlg->ShowWindow(SW_SHOW);
	}
	/* ************************************************************************** */
}

void CMainFrame::OnAbout() 
{
	CDialog_About about_dlg;
	//2012,1015 ybs
	st_handler.mn_menu_lock = FALSE;
	st_handler.mn_system_lock = FALSE;
	
	// **************************************************************************
    // ȭ�� �� ��ȯ �Ұ����� ���� �˻��Ѵ�.
    // **************************************************************************
	if (st_handler.mn_system_lock != FALSE)  return;  // ���� �ý��� Lock ������ ��� ���� 
	// **************************************************************************
	
	int nResponse = about_dlg.DoModal();
	
	if (nResponse == IDOK)
	{
//		ShellExecute( NULL, NULL, TEXT("UpdateList.txt"), NULL, TEXT("ReadMe"), SW_SHOW );
	}
}

void CMainFrame::OnReset() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnLock() 
{
	int n_response;  // ��ȭ ���� ���� �÷���
	
	CDialog_Pass_Check  pass_chk_dlg;
	
	// **************************************************************************
	// �޴� ��� �Ұ����� ��쿡 ���� ���� �˻��Ѵ�                              
	// -> ����Ʈ ��� �Ǵ� ƼĪ ��尡 �����Ǿ� �ִ��� �˻�                      
	// **************************************************************************
	if (st_handler.mn_level_teach !=  TRUE)
	{
		if (st_handler.mn_level_maint !=  TRUE) 
		{
			OnLevel();
			if (st_handler.mn_level_teach !=  TRUE)
			{
				if (st_handler.mn_level_maint !=  TRUE)  return;
			}
		}
	}
	// **************************************************************************
	
	st_handler.mstr_pass_level=_T("SystemLock");  // ��ȣ ���� ����
	
	n_response = pass_chk_dlg.DoModal();
	
	if (n_response == IDOK)
	{
		::PostMessage(st_handler.hWnd, WM_FORM_CHANGE, FORM_NAME, 2);  // ���� �����ӿ� SYSTEM LOCK ȭ�� ��� ��û
		
		if (st_handler.cwnd_list != NULL)
		{
//			st_msg.mstr_normal_msg = "System Locking.";
			st_msg.mstr_barcode = "System Locking.";
// 			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
			Func.On_LogFile_Add(LOG_TOTAL, st_msg.mstr_barcode);
		}
	}
	else if (n_response == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
}

void CMainFrame::OnExit() 
{
	int mn_response;  // ��ȭ ���ڿ� ���� ���� �� ���� ���� ���� 
	
	// **************************************************************************
    // ȭ�� �� ��ȯ �Ұ����� ���� �˻��Ѵ�.                                      
    // **************************************************************************
	if (st_handler.mn_menu_lock != FALSE)	return;
	if (st_handler.mn_system_lock != FALSE)  return;  // ���� �ý��� Lock ������ ��� ���� 
	
	CDialog_Select select_dlg;
	CDialog_Message msg_dlg;

	// **************************************************************************
	// ���� ��� ���°� STOP �������� �˻�                                       
	// **************************************************************************
	if (COMI.mn_run_status != dSTOP)
	{
		st_msg.str_fallacy_msg = _T("SSD Auto Sorter is active.");
		mn_response = msg_dlg.DoModal();
		if (mn_response == IDOK)  return ;
	} 
	// **************************************************************************

	st_handler.mn_level_teach =  FALSE;
	st_handler.mn_level_maint =  FALSE;
	st_handler.mn_level_ver = FALSE;//2014,0606 ybs

	// **************************************************************************
	// �޴� ��� �Ұ����� ��쿡 ���� ���� �˻��Ѵ�                              
	// -> ����Ʈ ��� �Ǵ� ƼĪ ��尡 �����Ǿ� �ִ��� �˻�                      
	// **************************************************************************
	if (st_handler.mn_level_teach !=  TRUE)
	{
		if (st_handler.mn_level_maint !=  TRUE) 
		{
			OnLevel();
			if (st_handler.mn_level_teach !=  TRUE)
			{
				if (st_handler.mn_level_maint !=  TRUE)  return;
			}
		}
	}
	// **************************************************************************
		
	// **************************************************************************
    // ���� ���α׷� ���� ȭ�� ���                                              
    // **************************************************************************
	CDialog_Exit  dlg;
	
	mn_response = dlg.DoModal();
	
	if (mn_response == IDOK)     
	{
		sprintf(st_msg.c_normal_msg, "[Exit OK]");
		//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
		Func.On_LogFile_Add(LOG_TOTAL, st_msg.c_normal_msg);

		st_timedb.mnTime_Section	= dSTOP;		
		st_timedb.mole_date			= COleDateTime::GetCurrentTime();
		
//		g_db.DB_Write_Time(st_timedb);

		All_Stop = 1 ;				// ������ ���� ���� ���� ���� �ʱ�ȭ
		OnMain_Thread_Destroy();	// ������ ���� �Լ�

		OnMain_Motor_Destroy();						//��� ���� ���� ����.
		mcls_m_basic.OnDaily_Count_Save();			// Daily Data Save 2K4/08/20/ViboX
		
		OnExitData_Saving();						// ȭ�鿡 ������ ��� ������ ���� �Լ�
		mcls_m_basic.OnDaily_Count_Save();			// Daily Data Save 2K4/08/20/ViboX
		
		// ��� ��ٴ�.
		g_ioMgr.set_out_bit(st_io.o_door_lock,					IO_OFF);
		OnMain_Port_Close();			// ������ �ø��� ��Ʈ ���� �Լ�

		CView* pOldActiveView = GetActiveView();	// ���� ȭ�鿡 ��µ� �� ���� ���� (save old view)
		
		pOldActiveView->ShowWindow(SW_HIDE);		// ������ ��µ� �並 ����� (hide the old)
		pOldActiveView->DestroyWindow();			// ������ ��µ� �並 �ı���Ų�� (Old View Destroy ��Ű�� ���Ͽ� �߰�)
		pOldActiveView = NULL;						// ������ ��µ� �信 ���� ���� ���� ���� �ʱ�ȭ 
		
		delete	pOldActiveView;						// ������ ��µ� �� ������ �����Ѵ� (kill old view)

		CFrameWnd::OnClose();
	}
}

int CMainFrame::OnMenu_Change_Checking()
{
	int nRet;
	
	nRet = TRUE;  // �ʱ� ���� �� ���� 
	
	// **************************************************************************
    // ȭ�� �� ��ȯ �Ұ����� ���� �˻��Ѵ�.                                      
    // **************************************************************************
	if (st_handler.mn_menu_lock != FALSE)	nRet = FALSE;
	if (st_handler.mn_system_lock != FALSE)  nRet = FALSE;  // ���� �ý��� Lock ������ ��� ���� 
	
	// **************************************************************************
	// ���� ��� ���°� STOP �������� �˻�                                       
	// **************************************************************************
	if (COMI.mn_run_status != dSTOP && COMI.mn_run_status != dLOCK)
	{
//		st_msg.mstr_normal_msg = _T("Handler is active. Stop first.");
		sprintf(st_msg.c_normal_msg, "Handler is active. Stop first.");
// 		if (st_handler.cwnd_list != NULL)  st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG); 
		Func.On_LogFile_Add(LOG_TOTAL, st_msg.c_normal_msg);
		
		nRet = FALSE;
	}
	// **************************************************************************
	
	return nRet;
}

void CMainFrame::OnSwitchToForm(int nForm)
{
	// **************************************************************************
    // ȭ�� �� ��ȯ �Ұ����� ���� �˻��Ѵ�.                                      
    // **************************************************************************
	if (st_handler.mn_menu_lock != FALSE)	return;
	if (st_handler.mn_system_lock != FALSE)  return;		// ���� �ý��� Lock ������ ��� ���� 

	CView* pOldActiveView = GetActiveView();			// ���� ȭ�鿡 ��µ� �� ���� ���� (save old view)
	CView* pNewActiveView = (CView*)GetDlgItem(nForm);  // ���� ����� �� ���� ���� (get new view)

	if (pNewActiveView == NULL)							// ���� ����� �䰡 ���� ��µ��� �ʾҴ��� �˻� (if it hasn't been created yet)
	{
		switch (nForm)			// �信 ������ ID ���� �� (these IDs are the dialog IDs of the view but can use anything)
		{
		case IDW_SCREEN_MAIN:				// ���� ȭ�� 
			pNewActiveView = (CView*)new CScreen_Main;
			break;
		case IDW_SCREEN_LOCK:				// System Lock ȭ��
			pNewActiveView = (CView*)new CScreen_Lock;
			break;
		case IDW_SCREEN_INIT:				// �ʱ�ȭ ȭ�� 
			pNewActiveView = (CView*)new CScreen_Initial;
			break;
		case IDW_SCREEN_BASIC:				// Basic ȭ��
			pNewActiveView = (CView*)new CScreen_Basic;
			break;
		case IDW_SCREEN_SET_MAINTENANCE:	// ����Ʈ ȭ�� 
			pNewActiveView = (CView*)new CScreen_Set_Maintenance;
			break;
//
		case IDW_SCREEN_WAIT_TIME:			// ��� �ð� ȭ�� 
 			pNewActiveView = (CView*)new CScreen_Wait_Time;
 			break;
		case IDW_SCREEN_MOTOR_TEACH:		// Motor Teach ȭ��
			pNewActiveView = (CView*)new CScreen_Motor;
			break;
		case IDW_SCREEN_MOTOR_SPEED:		// Motor Speed ȭ�� 
			pNewActiveView = (CView*)new CScreen_Motor_Speed;
			break;

		case IDW_SCREEN_LIST_OPERATION:		// ���۷��̼� ���� ��� ȭ�� 
			pNewActiveView = (CView*)new CScreen_List_Operation;
			break;

		case IDW_SCREEN_LIST_DATA_VIEW:			// ������ ���� ���� ��� ȭ�� 
			pNewActiveView = (CView*)new CScreen_List_Data_View;
			break;

		case IDW_SCREEN_SET_BARCODE:	// Barcode ȭ�� 
			pNewActiveView = (CView*)new CScreen_Set_Barcode;
			break;

		case IDW_SCREEN_IO:					// I/O ��� ȭ�� 
			pNewActiveView = (CView*)new CScreen_IO;
			break;

		case IDW_SCREEN_ADMINISTRATOR:		// ADMINISTRATOR ��� ȭ�� 
			pNewActiveView = (CView*)new CScreen_Admin;
			break;
		case IDW_SCREEN_FILE_EDITOR:		// File Editor ��� ȭ�� 
			pNewActiveView = (CView*)new CScreen_File_Editor;
			break;

		case IDW_SCREEN_ECSERVER:
			pNewActiveView = (CView*)new CScreen_Server_Network;
			break;

		////2015,0109
		case IDW_SCREEN_SET_NETWORK:	// Network ȭ�� 
			pNewActiveView = (CView*)new CScreen_Set_Network;
			break;

		////
		}

		CCreateContext context;  // ���ο� �信 ��ť��Ʈ Attach ( attach the document to the new view)
		context.m_pCurrentDoc = pOldActiveView->GetDocument();

		pNewActiveView->Create(NULL, NULL, 0L, CFrameWnd::rectDefault, this, nForm, &context);
		pNewActiveView->OnInitialUpdate();       // ���� ������ ����� ������ �� �κ��� ���ش�.
	}

//  ���� ������ ���.
//	pOldActiveView->ShowWindow(SW_HIDE);	// ������ ��µ� �並 ����� (hide the old)
//	pOldActiveView->DestroyWindow();		// ������ ��µ� �並 �ı���Ų�� (Old View Destroy ��Ű�� ���Ͽ� �߰�)
//	pOldActiveView = NULL;					// ������ ��µ� �信 ���� ���� ���� ���� �ʱ�ȭ 
//	
//	pNewActiveView->OnInitialUpdate();      // �ı��Ǵ� ������ �ٲ� ������ ���� ��µǴ� �信�� ���� ���ؼ� �̸��� �� ����.
//	SetActiveView(pNewActiveView);			// ���� ��µ� �並 ��Ƽ�� ��� ���� (change the active view)
//	pNewActiveView->ShowWindow(SW_SHOW);	// ���ο� �並 ��� (show the new window)
//
//	::SetWindowLong(pNewActiveView->m_hWnd, GWL_ID, AFX_IDW_PANE_FIRST);  // gotta have it
//	RecalcLayout();							// �������� �����Ѵ� (adjust frame)
//	delete	pOldActiveView;					// ������ ��µ� �� ������ �����Ѵ� (kill old view)
//
//  ���� ���.
	SetActiveView(pNewActiveView);			// ���� ��µ� �並 ��Ƽ�� ��� ���� (change the active view)
	pNewActiveView->ShowWindow(SW_SHOW);	// ���ο� �並 ��� (show the new window)

	pOldActiveView->ShowWindow(SW_HIDE);	// ������ ��µ� �並 ����� (hide the old)
	pOldActiveView->DestroyWindow();		// ������ ��µ� �並 �ı���Ų�� (Old View Destroy ��Ű�� ���Ͽ� �߰�)
	pOldActiveView = NULL;					// ������ ��µ� �信 ���� ���� ���� ���� �ʱ�ȭ 

	::SetWindowLong(pNewActiveView->m_hWnd, GWL_ID, AFX_IDW_PANE_FIRST);  // gotta have it
	RecalcLayout();							// �������� �����Ѵ� (adjust frame)
	delete	pOldActiveView;					// ������ ��µ� �� ������ �����Ѵ� (kill old view)
	
	st_handler.mn_menu_num = nForm; 

	// **************************************************************************
	// ���� ȭ�� ���� Ÿ��Ʋ�ٿ� ����Ѵ�.                                       
	// **************************************************************************
	if (st_handler.cwnd_title != NULL)   st_handler.cwnd_title->PostMessage(WM_STATUS_CHANGE, FORM_NAME, nForm);
	// **************************************************************************
}

// ******************************************************************************
// ����� ���� �޽����� ���� �� ȭ�� ��ȯ �Լ�                                   
// ******************************************************************************
LRESULT CMainFrame::OnViewChangeMode(WPARAM wParam,LPARAM lParam)
{

	if( GetActiveView() == NULL )
	{
		int a = 1;
		return 0;
	}
	int mn_chg_num = wParam;  // �� ȭ�鿡 ���� ID �� ���� 
	
	// **************************************************************************
    // ȭ�� �� ��ȯ �Ұ����� ���� �˻��Ѵ�.                                      
	// -> �˶� ȭ���� ������ ȭ�鿡 ���ؼ��� �޴� ��� ���� ���� �˻�            
    // **************************************************************************
	if (mn_chg_num != 9)  
	{
		if (st_handler.mn_menu_lock != FALSE)  return 0;
		if (st_handler.mn_system_lock != FALSE)  return 0;  // ���� �ý��� Lock ������ ��� ���� 
	}
	// **************************************************************************
	
	switch(mn_chg_num)
	{
	case 1: 
		if (lParam==1)  OnMain();					// ���� ȭ�� ��ȯ 
		else if (lParam==2)							// System Locking ȭ�� ��ȯ 
		{
			if (GetActiveView()->IsKindOf(RUNTIME_CLASS(CScreen_Lock)))   return 0;
			OnSwitchToForm(IDW_SCREEN_LOCK) ;
		}
		else if (lParam==3)							// �ʱ�ȭ ȭ�� ��ȯ 
		{
			if (GetActiveView()->IsKindOf(RUNTIME_CLASS(CScreen_Initial)))   return 0;
			OnSwitchToForm(IDW_SCREEN_INIT) ;
		}
		break;
	case 2: 
		OnBasic();									// ������ ȭ�� ��ȯ 
		break;
 	case 3:
 		if (lParam==1)       OnSetMaintenance();	// ����Ʈ ȭ�� ��ȯ 
// 		else if (lParam==2)  OnSetInterface();		// Interface ���� ���� ȭ�� ��ȯ
		else if (lParam==3)  OnSetBarcode();
 		else if (lParam==4)  OnSetNetwork();		//2015,0109 Network ȭ�� ��ȯ.
		break;
 	case 4 :
 		OnWait();
 		break;
 	case 5 : 
 		if (lParam==1)       OnMotTeach();			// ���� ��ġ ȭ�� ��ȯ 
 		else if (lParam==2)	 OnMotSpeed();			// ���� �ӵ� ȭ�� ��ȯ 
 		break;
	case 6 :
		if (lParam==1)       OnListOper();			// Operation ��� ����Ʈ ȭ�� ��ȯ 
// 		else if (lParam == 2)OnListDataview();

		break;
	case 7 : 
		if (lParam==1)       OnAlarm();				// �˶� ȭ�� ��ȯ 
		else if (lParam==2)  OnAlarm_Destroy();		// �˶� ȭ�� ���� �Լ�
		break;
	case 8 : 
		if (lParam==1)       OnAdmin();				// Administrator ȭ�� ��ȯ 
		else if (lParam==2)  OnFileEditor();		// File Editor ȭ�� ��ȯ.
		else if (lParam==3)  OnEcserver();		// Server Network ȭ�� ��ȯ.
		break;
	default:
		break;
	}
	
	return 0 ;
}
// ******************************************************************************

void CMainFrame::OnMain_Path_Set()
{
	CString strTempPath;

// 	CString mstr_basic;			// �⺻ ���� ���� ���� ����+���ϸ� ���� ����
// 	
// 	CString mstr_path_dvc;		// ����̽��� ƼĪ ���� ���� ���� ���� ���� ���� ����
// 	CString mstr_socket_lot;	// ���Ϻ�...
// 	CString mstr_socket_day;	// ���Ϻ�...
// 	CString mstr_socket_month;	// ���Ϻ�...
// 	CString mstr_socket_shift;	// ���Ϻ�...
// 	CString mstr_path_alarm;	// ��� �˶� ���� ���� ���� ���� ����
// 	CString mstr_path_op;		// ���۷����� ���� ���� ���� ���� ����
// 	CString mstr_path_tray;		// Tray�� ���� ���� ���� ���� ���� ���� ����
// 	CString mstr_path_serial;	// Socket ���� ���� ���� ���� ���� ���� ����
// 	
// 	CString mstr_path_file;		// ���� ���� ���� ���� ����
// 	CString mstr_path_back;		// BACKUP ���� ���� ���� ���� ����
// 	
// 	CString mstr_file_basic;	// �⺻ ���� ���� ���� ���ϸ� ���� ����
// 	CString mstr_file_wait;		// ��� �ð� ���� ���� ���ϸ� ���� ����
// 	
// 	CString mstr_operation;		// Operation Log ���� ���� ����.
// 	CString mstr_interface;		// Interface Log ���� ���� ����.
// 	CString mstr_machine;		// Machine Log ���� ���� ����.
// 	CString mstr_barcode;		// Barcode Log ���� ���� ����.
// 	CString mstr_gpib;			// Total Log ���� ���� ����.
// 	CString mstr_total;			// Total Log ���� ���� ����.
// 	
// 	CString mstr_io_map;		// IO MAP ���� ��ġ ����.
// 	
// 	CString mstr_handler;

// [Folder_Data]
// Alarm=C:\\AMT8500\\Alarm\\
// Bmp=C:\\AMT8500\\Bmp\\
// Data=C:\\AMT8500\\Data\\
// Device=C:\\AMT8500\\Device\\
// Log=C:\\AMT8500\\Log\\
// Setting=C:\\AMT8500\\Setting\\;

	CString strAlarmPath;
	CString strBmpPath;
	CString strDataPath;
	CString strDevicePath;
	CString strLogPath;
	CString strSettingPath;
	CString strModelPath;
	char chr_data[100];

	CString str_LoadFile;       // �ӽ� ���� ����
	
	FILE    *fp ;
	int     existence;
	
	str_LoadFile = "C:\\AMT8590\\Setting\\PathInfo.TXT";
	
	existence = access(str_LoadFile, 0);
	
	if (!existence)
	{
		if ((fp=fopen(str_LoadFile,"rb")) == NULL)
		{
			if (st_handler.cwnd_list != NULL)
			{
				sprintf(st_msg.c_normal_msg, "[%s] file open error.", str_LoadFile);
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // ���� ���� ��� ��û
				Func.On_LogFile_Add(LOG_TOTAL, st_msg.c_normal_msg);
			}
			return ;
		}
	}
	else
	{
		if (st_handler.cwnd_list != NULL)
		{
			sprintf(st_msg.c_normal_msg, "[%s] file is not exist.", str_LoadFile);
// 			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // ���� ���� ��� ��û
			Func.On_LogFile_Add(LOG_TOTAL, st_msg.c_normal_msg);
		}
		return;
	}

	:: GetPrivateProfileString("Folder_Data", "Alarm",		"D:\\AMTLOG\\Alarm\\", chr_data, 100, ".\\PathInfo.TXT");
	strAlarmPath = chr_data;
	strAlarmPath.TrimLeft(' ');               
	strAlarmPath.TrimRight(' ');

	:: GetPrivateProfileString("Folder_Data", "Bmp",		"C:\\AMT8590\\Bmp\\", chr_data, 100, ".\\PathInfo.TXT");
	strBmpPath = chr_data;
	strBmpPath.TrimLeft(' ');               
	strBmpPath.TrimRight(' ');

	:: GetPrivateProfileString("Folder_Data", "Data",		"C:\\AMT8590\\Data\\", chr_data, 100, ".\\PathInfo.TXT");
	strDataPath = chr_data;
	strDataPath.TrimLeft(' ');               
	strDataPath.TrimRight(' ');

	:: GetPrivateProfileString("Folder_Data", "Device",		"C:\\AMT8590\\Device\\", chr_data, 100, ".\\PathInfo.TXT");
	strDevicePath = chr_data;
	strDevicePath.TrimLeft(' ');               
	strDevicePath.TrimRight(' ');

	:: GetPrivateProfileString("Folder_Data", "Log",		"D:\\AMTLOG\\Log\\", chr_data, 100, ".\\PathInfo.TXT");
	strLogPath = chr_data;
	strLogPath.TrimLeft(' ');               
	strLogPath.TrimRight(' ');

	:: GetPrivateProfileString("Folder_Data", "Setting",	"C:\\AMT8590\\Setting\\", chr_data, 100, ".\\PathInfo.TXT");
	strSettingPath = chr_data;
	strSettingPath.TrimLeft(' ');               
	strSettingPath.TrimRight(' ');

	:: GetPrivateProfileString("Folder_Data", "Model",		"C:\\AMT8590\\Setting\\ModelName\\", chr_data, 100, ".\\PathInfo.TXT");
	strModelPath = chr_data;
	strModelPath.TrimLeft(' ');               
	strModelPath.TrimRight(' ');

// 	st_path.mstr_reg_model = _T(strSettingPath + "RegModel.TXT");
// 	Func.CreateFolder(strSettingPath);

	st_path.mstr_basic =			_T(strSettingPath + "BasicTerm.TXT");		// ȯ�� ���� ���� ���� ���Ͽ� ���� ���� ���� 
	Func.CreateFolder(st_path.mstr_basic);

	st_path.mstr_basic_folder =		_T(strSettingPath);					// ȯ�� ���� ���� ���� ���Ͽ� ���� ���� ���� 

	st_path.mstr_path_dvc =		_T(strDevicePath);						// ����̽��� ƼĪ ���� ���� ���� ���� ���� ����
	Func.CreateFolder(st_path.mstr_path_dvc);

	st_path.mstr_motor =			_T(strSettingPath + "AMT8590.cme2");

	st_path.mstr_file_basic =		_T("BasicTerm");								// �⺻ ���� ���� ���� ���ϸ� ����
	st_path.mstr_file_wait =		_T("WaitTime");									// ��� �ð� ���� ���� ���ϸ� ����

	CString FolderPath;
	
	st_path.mstr_path_alarm =		_T(strBmpPath);									// ��� �˶� ���� ���� ���� ����
	Func.CreateFolder(st_path.mstr_path_alarm);
	
	st_path.mstr_path_file =		_T("C:\\AMT8590\\");							// ���� ���� ���� ����
	st_path.mstr_path_back =		_T("c:\\BackUp\\");									// BACKUP ���� ���� ���� ����
	Func.CreateFolder(st_path.mstr_path_back);
	
	st_path.mstr_operation =		_T(strLogPath + "Operation\\");			// Operation Log ���Ͽ� ���� ���� ���� 
	Func.CreateFolder(st_path.mstr_operation);
	
	st_path.mstr_interface =		_T(strLogPath + "Interface");			// Interface Log ���Ͽ� ���� ���� ���� 
	Func.CreateFolder(st_path.mstr_interface);

	st_path.mstr_tcpip =		_T(strLogPath + "Tcpip");			// Interface Log ���Ͽ� ���� ���� ���� 
	Func.CreateFolder(st_path.mstr_tcpip);	
	
	st_path.mstr_machine   =		_T(strLogPath + "Machine");				// Machine Log ���Ͽ� ���� ���� ���� 
	Func.CreateFolder(st_path.mstr_machine);
	
	st_path.mstr_barcode   =		_T(strLogPath + "Barcode\\");				// Machine Log ���Ͽ� ���� ���� ���� 
	Func.CreateFolder(st_path.mstr_barcode);
	
	st_path.mstr_total     =		_T(strLogPath + "Total");				// Total Log ���Ͽ� ���� ���� ���� 
	Func.CreateFolder(st_path.mstr_total);

	st_path.mstr_uph     =		_T(strLogPath + "UPH\\UPH\\");				// Total Log ���Ͽ� ���� ���� ���� 
	Func.CreateFolder(st_path.mstr_uph);

	st_path.mstr_uph_total     =		_T(strLogPath + "UPH\\Total\\");				// Total Log ���Ͽ� ���� ���� ���� 
	Func.CreateFolder(st_path.mstr_uph_total);
	
	st_path.mstr_reject     =		_T(strLogPath + "UPH\\Reject\\");				// Total Log ���Ͽ� ���� ���� ���� 
	Func.CreateFolder(st_path.mstr_reject);

	st_path.str_log_path	=		_T(strLogPath + "EqLog\\");	
	Func.CreateFolder(st_path.str_log_path);

	st_path.str_lot_data_path	=	_T(strLogPath + "Time\\");	
	Func.CreateFolder(st_path.str_lot_data_path);

	Func.CreateFolder(strLogPath + "AlarmCodeDebug\\");
	Func.CreateFolder(strAlarmPath + "Daily\\");
	//2013,0306
	Func.CreateFolder(strAlarmPath + "UnderDaily\\");

	///////20131115
	st_path.str_interface_folder = _T("c:\\AMT8590\\File\\File.TXT"); //20120516
	Func.CreateFolder(st_path.str_interface_folder);
	//
	
	/////
	//kwlee 2016.0821
	st_path.mstr_gms_path	=	_T(strLogPath + "Gms\\");	
	Func.CreateFolder(st_path.mstr_gms_path);
	//

	////2014,1217 ysj
	st_path.str_eqp_log_path = _T("c:\\EQP_LOG\\");
	Func.CreateFolder(st_path.str_eqp_log_path);
	////

	st_path.mstr_io_map				= _T(strSettingPath + "AMT8590_IO_MAP.xls");
	st_path.mstr_motor_axis_map		= _T(strSettingPath + "AMT8590_MOTOR_AXIS_MAP.xls");
	if ( g_local.GetLocalType() == LOCAL_ENG ) st_path.mstr_motor_axis_map		= _T(strSettingPath + "AMT8590_MOTOR_AXIS_MAP_ENG.xls");
	st_path.mstr_motor_part_map		= _T(strSettingPath + "AMT8590_MOTOR_PART_MAP.xls");
	if ( g_local.GetLocalType() == LOCAL_ENG ) st_path.mstr_motor_part_map		= _T(strSettingPath + "AMT8590_MOTOR_PART_MAP_ENG.xls");
	st_path.mstr_io_part_map		= _T(strSettingPath + "AMT8590_IO_PART_MAP.xls");
	st_path.mstr_wait_time_map		= _T(strSettingPath + "AMT8590_WAITTIME_MAP.xls");
	if ( g_local.GetLocalType() == LOCAL_ENG ) st_path.mstr_wait_time_map		= _T(strSettingPath + "AMT8590_WAITTIME_MAP_ENG.xls");

	////2015.0221
	st_path.mstr_recipe_path = _T("C:\\XGEM\\AMT8590\\AMT8590\\XWork\\Recipe\\");
	Func.CreateFolder(st_path.mstr_recipe_path);
	////

	//2015.0513
	st_path.mstr_eqp_file =		_T("C:\\EQP_LOG\\");							// ���� ���� ���� ����
	Func.CreateFolder(st_path.mstr_eqp_file);
	
	st_path.mstr_xgem_path =	_T(st_path.mstr_eqp_file + "Comm\\");
	Func.CreateFolder(st_path.mstr_xgem_path);
	st_path.mstr_error_path =	_T(st_path.mstr_eqp_file + "Error\\");
	Func.CreateFolder(st_path.mstr_error_path);
	st_path.mstr_event_path =	_T(st_path.mstr_eqp_file + "Event\\");
	Func.CreateFolder(st_path.mstr_event_path);
	st_path.mstr_product_path =	_T(st_path.mstr_eqp_file + "Product\\");
	Func.CreateFolder(st_path.mstr_product_path);
	st_path.mstr_mat_path =	_T(st_path.mstr_eqp_file + "Mat\\");
	Func.CreateFolder(st_path.mstr_mat_path);

	fclose(fp);

}

void CMainFrame::OnMain_Var_Default_Set()
{
	int i = 0, j = 0, mn_chk = 0;
	CString mstr_temp;
	OnMain_Path_Set();

	nElectrostaticCheckStep = 0;
	nElectChannel = 1;

	mn_BarcodeSetValueChangeStep = 0;//20131115

	for (i = 0; i < MAXSITE; i++)
	{
		st_handler.mn_init_state[i] = CTL_NO;
	}

	mp_alarm_dlg = NULL;
	mp_msg_dlg = NULL;
	mp_xmsg_dlg = NULL;

	mn_new_lot_in_step  = 0;
	mn_lot_name_step = 0;

	for (i = 0; i < 3; i++)
	{
		st_handler.mstr_lot_name[i] = "";
	}

	nElectrostaticCheckStep = 0;					// ������ Ȯ�� ���� Ŭ����.
	nElectChannel = 1;						// ������ Ȯ�� ä�� 1~5

	st_ctlbd.n_motorbd_init_end = CTLBD_NO; 
	g_comiMgr.SetMotBoardInit( false );

	CString str_load_device, str_chk_ext;
	int mn_pos;
	char chr_data[50];
	char chr_buf[50];
	
	:: GetPrivateProfileString("BasicData", "Device_Type", "", chr_data, 50, st_path.mstr_basic);
	str_load_device = chr_data;
	str_load_device.TrimLeft(' ');               
	str_load_device.TrimRight(' ');
	
	mn_pos = str_load_device.Find(".");								// Ȯ���� ��ġ �˻�
	if (mn_pos == -1)
		st_basic.mstr_device_name = str_load_device + _T(".TXT");	// Ȯ���� �߰�
	else 
	{
		str_chk_ext = str_load_device.Mid(mn_pos);					// ���� Ȯ���� ����
		if (str_chk_ext != _T(".TXT"))  
			st_basic.mstr_device_name = _T("DEFAULT.TXT");			// �ʱ� ����̽� ���ϸ� ����
		else 
			st_basic.mstr_device_name = str_load_device;				// ����̽� ���ϸ� ����
	}

	:: GetPrivateProfileString("BasicData", "Virtual_Mode", "0", chr_data, 10, st_path.mstr_basic);
	mn_chk = atoi(chr_data);
	if (mn_chk < 0 || mn_chk > 1)
	{
		st_handler.mn_virtual_mode = 0;
		mstr_temp = LPCTSTR(_itoa(st_handler.mn_virtual_mode, chr_buf, 10)) ;
		:: WritePrivateProfileString("BasicData", "Virtual_Mode", LPCTSTR(mstr_temp), st_path.mstr_basic);
	}
	else  st_handler.mn_virtual_mode = mn_chk;

	//2013,1028
//	st_handler.mn_virtual_mode = 0;

	:: GetPrivateProfileString("BasicData", "Virtual_Supply", "0", chr_data, 10, st_path.mstr_basic);
	mn_chk = atoi(chr_data);
	if (mn_chk < 0 || mn_chk > 1)
	{
		st_handler.mn_virtual_supply = 0;
		mstr_temp = LPCTSTR(_itoa(st_handler.mn_virtual_supply, chr_buf, 10)) ;
		:: WritePrivateProfileString("BasicData", "Virtual_Supply", LPCTSTR(mstr_temp), st_path.mstr_basic);
	}
	else  st_handler.mn_virtual_supply = mn_chk;

	//2013,1028
	st_handler.mn_virtual_supply = 0;
	
	:: GetPrivateProfileString("BasicData", "Buffer_In", "0", chr_data, 10, st_path.mstr_basic);
	mn_chk = atoi(chr_data);
	if (mn_chk < 0 || mn_chk > 1)
	{
		st_handler.mn_buffer_in = 0;
		mstr_temp = LPCTSTR(_itoa(st_handler.mn_buffer_in, chr_buf, 10)) ;
		:: WritePrivateProfileString("BasicData", "Buffer_In", LPCTSTR(mstr_temp), st_path.mstr_basic);
	}
	else  st_handler.mn_buffer_in = mn_chk;

	//2013,1028
	st_handler.mn_buffer_in = 0;

	//2013,0715
	:: GetPrivateProfileString("BasicData", "FullInline_Mode", "0", chr_data, 10, st_path.mstr_basic);
	mn_chk = atoi(chr_data);
	if (mn_chk < 0 || mn_chk > 1)
	{
		st_handler.mn_fullinline_mode = 0;
		mstr_temp = LPCTSTR(_itoa(st_handler.mn_fullinline_mode, chr_buf, 10)) ;
		:: WritePrivateProfileString("BasicData", "FullInline_Mode", LPCTSTR(mstr_temp), st_path.mstr_basic);
	}
	else  st_handler.mn_fullinline_mode = mn_chk;

	//2013,1028
	st_handler.mn_fullinline_mode = 1;
	
// 	:: GetPrivateProfileString("BasicData", "PICKER_POSITION_0", "0", chr_data, 10, st_path.mstr_basic);
// 	st_handler.md_picker_position[0] = atof(chr_data);
// 
// 	:: GetPrivateProfileString("BasicData", "PICKER_POSITION_1", "0", chr_data, 10, st_path.mstr_basic);
// 	st_handler.md_picker_position[1] = atof(chr_data);
// 
// 	:: GetPrivateProfileString("BasicData", "PICKER_POSITION_2", "0", chr_data, 10, st_path.mstr_basic);
// 	st_handler.md_picker_position[2] = atof(chr_data);
// 
// 	:: GetPrivateProfileString("BasicData", "PICKER_POSITION_3", "0", chr_data, 10, st_path.mstr_basic);
// 	st_handler.md_picker_position[3] = atof(chr_data);
// 
// 	:: GetPrivateProfileString("BasicData", "TRAY_PLACE_OFFSET_0", "0", chr_data, 10, st_path.mstr_basic);
// 	st_handler.md_tray_place_offset[0] = atof(chr_data);
// 
// 	:: GetPrivateProfileString("BasicData", "TRAY_PLACE_OFFSET_1", "0", chr_data, 10, st_path.mstr_basic);
// 	st_handler.md_tray_place_offset[1] = atof(chr_data);
// 
// 	ReadBasicData_Int( st_handler.mn_retest_cnt, "RETEST_CNT", 1, 0, 3, st_path.mstr_basic );
// 	ReadBasicData_Int( st_handler.mn_beat_cnt, "BEAT_CNT", 0, 0, 3, st_path.mstr_basic );
// 	ReadBasicData_Int( st_handler.mn_AutoSocketOff_Cnt, "AUTO_SOCKET_OFF_CNT", 5, 0, 10, st_path.mstr_basic );
// 
// 	ReadBasicData_Int( st_handler.mn_cokIndex[COKINDEX_GS1], "COKINDEX_GS1", -1, -1, 5, st_path.mstr_basic );
// 	ReadBasicData_Int( st_handler.mn_cokIndex[COKINDEX_GS2], "COKINDEX_GS2", -1, -1, 5, st_path.mstr_basic );
// 	ReadBasicData_Int( st_handler.mn_cokIndex[COKINDEX_MSATA], "COKINDEX_MSATA", -1, -1, 5, st_path.mstr_basic );
// 	ReadBasicData_Int( st_handler.mn_cokIndex[COKINDEX_25_REVERSE], "COKINDEX_25_REVERSE", -1, -1, 5, st_path.mstr_basic );
// 	ReadBasicData_Int( st_handler.mn_cokIndex[COKINDEX_25_FRONT], "COKINDEX_25_FRONT", -1, -1, 5, st_path.mstr_basic );

// 	for( i=0; i<COMMON_TEACHING_MAX; i++ )
// 	{
// 		CString strKeyName;
// 		strKeyName.Format( "COMMON_TEACHING_%02d", i );
// 		ReadBasicData_Double( st_handler.md_common_teaching[i], strKeyName, 0.0f, -4000.0f, 4000.0f, st_path.mstr_basic );
// 	}

	mcls_m_basic.On_Teach_Data_Load();
	
	//2015.0313
	CString strVal;
	for ( j = 0; j < 6; j++)
	{
		strVal.Format( "CAPADENSITY_%02d", j );
		st_handler.m_strDensityCapa[j] = AMTRegistry::RegReadString( REG_VAL_CAPADENSITY, strVal, "" ).c_str();
	}
	for ( j = 0; j < 6; j++)
	{
		strVal.Format( "DENSITY_%02d", j );
		st_handler.m_strDensityLabel[j] = AMTRegistry::RegReadString( REG_VAL_DENSITY, strVal, "" ).c_str();
	}
	for ( j = 0; j < 4; j++)
	{
		strVal.Format( "BCR_LABEL_%02d", j );
		st_handler.m_strDistributionLabel[j] = AMTRegistry::RegReadString( REG_VAL_BCR, strVal, "" ).c_str();
		strVal.Format( "BCR_RIBBON_%02d", j );
		st_handler.m_strDistributionRibbon[j] = AMTRegistry::RegReadString( REG_VAL_BCR, strVal, "" ).c_str();

// 		strVal.Format( "BCR_SD_%02d", j );
// 		st_barcode.mn_labelset_sd[j] = AMTRegistry::RegReadInt( REG_VAL_LABEL_BCR_SD, strVal);
// 		strVal.Format( "BCR_LT_%02d", j );
// 		st_barcode.mn_labelset_lt[j] = AMTRegistry::RegReadInt( REG_VAL_LABEL_BCR_LT, strVal);
// 		strVal.Format( "BCR_LHX_%02d", j );
// 		st_barcode.mn_labelset_lhx[j] = AMTRegistry::RegReadInt( REG_VAL_LABEL_BCR_LHX, strVal);
// 		strVal.Format( "BCR_LHY_%02d", j );
// 		st_barcode.mn_labelset_lhy[j] = AMTRegistry::RegReadInt( REG_VAL_LABEL_BCR_LHY, strVal);
// 		strVal.Format( "BCR_MODE_%02d", j );
// 		st_barcode.mn_Prt_Mode[j] = AMTRegistry::RegReadInt( REG_VAL_LABEL_BCR_MODE, strVal);
// 		strVal.Format( "BCR_COMPLETE_%02d", j );
// 		st_barcode.mn_Prt_complete_use[j] = AMTRegistry::RegReadInt( REG_VAL_LABEL_BCR_COMPLETE, strVal);
	}

	for (i = 0; i < 3; i++)
	{
		st_handler.mstr_lot_name[i] = "";
		st_var.m_var_reject[i] = CTL_NO;//reject reset
	}

	st_NW.mb_buffer_in_received = true;

	st_basic.n_retry_cnt = 3;

	st_handler.mn_emptyout_cnt = 0; //ybs
	st_handler.mn_emptynext_cnt = 0;//2012,1128
	st_handler.mn_emptyin_cnt = 0;//2012,1128
	st_handler.mb_rej_3stacker = FALSE;

	st_handler.mn_smema_front = CTL_NO;

	//2013,0307
	st_handler.mn_robot_motorX_safety = CTL_NO;

	if (st_handler.cwnd_title != NULL)	
	{
		st_handler.cwnd_title->PostMessage(WM_STATUS_CHANGE, SMEMA_ONOFF, 0);
	}



	st_handler.mn_curr_back_conv = 0;
	st_handler.mn_smema_rear_run = 1;
	st_handler.n_auto_serial_create = 0;
	nRearSmemaStep = 0;

	st_handler.mn_unload_cycle = CTL_NO;
	st_handler.mn_load_cycle = CTL_NO;	

	st_handler.mn_chk_lotend = CTL_NO;
	st_handler.mn_smema_rear = CTL_NO;

	alarm.mb_bcr_error = false;
	alarm.mn_bcr_num = 0;
	alarm.mn_emo_alarm = FALSE;

	st_work.mstr_op_id = "12345678";

	for(i=0; i<2; i++)
	{
		m_Animate.m_ID_Buffer1.m_bGlass[i] = FALSE;	
		m_Animate.m_ID_Buffer2.m_bGlass[i] = FALSE;	
		m_Animate.m_ID_Buffer3.m_bGlass[i] = FALSE;	
		m_Animate.m_ID_Buffer4.m_bGlass[i] = FALSE;	
		m_Animate.m_ID_Buffer5.m_bGlass[i] = FALSE;	

		m_Animate.m_ID_Buffer1.m_bSkip[i] = FALSE;
		m_Animate.m_ID_Buffer2.m_bSkip[i] = FALSE;
		m_Animate.m_ID_Buffer3.m_bSkip[i] = FALSE;
		m_Animate.m_ID_Buffer4.m_bSkip[i] = FALSE;
		m_Animate.m_ID_Buffer5.m_bSkip[i] = FALSE;
		
		m_Animate.m_ID_Move_CV1.m_bGlass[i] = FALSE;
	}

	st_work.n_IDBuffer_Info = -1;//2014.1110
// 	st_var.n_newlotin = CTL_NO;
	st_handler.mn_curr_back_conv = 0;
	st_handler.mn_manual_lable = CTL_NO;
	st_var.n_lotstart = ID_LOT_EMPTY;

	st_handler.mn_8580_top = 0;
	st_handler.mn_8580_btm = 0;
	st_handler.m_strVisModel = "";

	st_var.n_use_vis_density = CTL_NO;
	st_var.n_use_vis_top = CTL_NO;
	for(i=0; i<4; i++)
	{
		st_handler.m_bstart[i] = true;
		st_var.n_bcrid_error[i] = CTL_NO;//2015.0327
	}

	for(i=0; i<6; i++)
	{
		st_var.n_use_density_flag[i] = CTL_YES;
		st_var.n_use_density_count[i] = 0;
		st_var.n_err_density_flag[i] = CTL_NO;
	}

	st_var.n_use_density_key = CTL_NO;
	st_var.n_use_top_skip = CTL_NO;

	st_var.mn_new_density_flag = CTL_NO;
	st_var.mn_new_density_count = 0;
	st_var.mn_check_density_flag = CTL_NO;
	st_var.mn_check_density_count = 0;
	
	st_var.n_using_barcode = -1;
	//2016.0615
	if( st_basic.nBcrFeederUse[2] == CTL_YES && st_basic.nBcrFeederUse[3] == CTL_YES )
	{
		st_var.n_use_barcode[2] = EMBS_PASS;
		st_var.n_use_barcode[3] = EMBS_PASS;
		st_var.n_using_barcode = 1;
	}
	else if( st_basic.nBcrFeederUse[0] == CTL_YES && st_basic.nBcrFeederUse[1] == CTL_YES )
	{
		st_var.n_use_barcode[0] = EMBS_PASS;
		st_var.n_use_barcode[1] = EMBS_PASS;
		st_var.n_using_barcode = 0;
	}
	
	if( st_var.n_using_barcode == -1 )
	{
		st_basic.nBcrFeederUse[2] = CTL_YES;
		st_basic.nBcrFeederUse[3] = CTL_YES;
		st_var.n_use_barcode[2] = EMBS_PASS;
		st_var.n_use_barcode[3] = EMBS_PASS;
		st_var.n_using_barcode = 1;
	}
	

	st_work.mn_run_down = CTL_NO;
	st_work.mn_chg_job = CTL_NO;
	st_work.mn_jam = CTL_NO;
	st_handler.m_dwJamStartTime = GetCurrentTime();
	st_var.n_next_down = CTL_NO;
	st_var.n_tboxmv_forming_cv_mode = CTL_NO;
	st_var.n_tboxmv_sealing_cv_mode = CTL_NO;
	
	st_var.mn_lotend_density_flag = CTL_NO;

	st_handler.mn_model_change = CTL_NO;
	
// 	st_work.n_BTMIDBuffer_Info = -1;//2014.1110				

//	OnIsExistDvcFie();	// �۾��� �𵨸��� �����ϴ��� Ȯ��
	
	//2015.0530	
	st_work.n_mat_density[0] = AMTRegistry::RegReadInt( REG_KEY_COUNT, REG_VAL_COUNT_DENSITY_1 );
	st_work.n_mat_density[1] = AMTRegistry::RegReadInt( REG_KEY_COUNT, REG_VAL_COUNT_DENSITY_2 );
	st_work.n_mat_density[2] = AMTRegistry::RegReadInt( REG_KEY_COUNT, REG_VAL_COUNT_DENSITY_3 );
	st_work.n_mat_density[3] = AMTRegistry::RegReadInt( REG_KEY_COUNT, REG_VAL_COUNT_DENSITY_4 );
	st_work.n_mat_density[4] = AMTRegistry::RegReadInt( REG_KEY_COUNT, REG_VAL_COUNT_DENSITY_5 );
	st_work.n_mat_density[5] = AMTRegistry::RegReadInt( REG_KEY_COUNT, REG_VAL_COUNT_DENSITY_6 );

	st_work.n_mat_bcr[0] = AMTRegistry::RegReadInt( REG_KEY_COUNT, REG_VAL_COUNT_BCR_1 );
	st_work.n_mat_bcr[1] = AMTRegistry::RegReadInt( REG_KEY_COUNT, REG_VAL_COUNT_BCR_2 );
	st_work.n_mat_bcr[2] = AMTRegistry::RegReadInt( REG_KEY_COUNT, REG_VAL_COUNT_BCR_3 );
	st_work.n_mat_bcr[3] = AMTRegistry::RegReadInt( REG_KEY_COUNT, REG_VAL_COUNT_BCR_4 );
	
	st_work.n_mat_ribbon[0] = AMTRegistry::RegReadInt( REG_KEY_COUNT, REG_VAL_COUNT_RIBBON_1 );
	st_work.n_mat_ribbon[1] = AMTRegistry::RegReadInt( REG_KEY_COUNT, REG_VAL_COUNT_RIBBON_2 );
	st_work.n_mat_ribbon[2] = AMTRegistry::RegReadInt( REG_KEY_COUNT, REG_VAL_COUNT_RIBBON_3 );
	st_work.n_mat_ribbon[3] = AMTRegistry::RegReadInt( REG_KEY_COUNT, REG_VAL_COUNT_RIBBON_4 );
	

	for ( i =0; i < 6; i++)
	{
		if( st_work.n_mat_density[i] <= 0) st_work.n_mat_density[i] = 2000;
	}
	for ( i =0; i < 4; i++)
	{
		if( st_work.n_mat_bcr[i] <= 0) st_work.n_mat_bcr[i] = 3000;
		if( st_work.n_mat_ribbon[i] <= 0) st_work.n_mat_ribbon[i] = 5000;
	}


	//3�ֺ� ����
	Func.DeleteOldFiles(st_path.mstr_total, 21);
	Func.DeleteOldFiles(st_path.mstr_interface, 21);
	Func.DeleteOldFiles(st_path.mstr_machine, 21);
	Func.DeleteOldFiles(st_path.mstr_tcpip, 21);

	nXgemStep = 0;

	st_handler.m_strNewPartNmber = "";

	//2015.0726
// 	st_handler.m_nConformVisAfterModelChange = CTL_NO;
	st_handler.m_nLotServer = CTL_NO;
	st_handler.m_nRearOut = CTL_NO;

	for ( int kk = 0; kk < 4; kk++)
	{
		clsZebra.SetDarkness_TCP(kk);
		clsZebra.LabelTop_TCP(kk);
		clsZebra.OnPrintAnswerMode(2, 0, kk);
		clsZebra.Rewind_Mode_TCP(kk);
		st_handler.m_nConformVisAfterModelChange[i] = CTL_NO;
	}

	//2016.0919
	st_work.n_jamcode_flag = CTL_NO;
	//2016.0927
	st_handler.mn_mute_on = CTL_NO;
	g_ioMgr.set_out_bit(st_io.o_out_mute_on_lamp, IO_OFF);
	g_ioMgr.set_out_bit(st_io.o_out_mute_off_lamp, IO_ON);
	//2016.1031
	st_handler.mn_device_type = -1;
}	

void CMainFrame::OnMotTeach() 
{
	// **************************************************************************
    // ȭ�� �� ��ȯ �Ұ����� ���� �˻��Ѵ�.                                      
    // **************************************************************************
	int nmenu_chk = OnMenu_Change_Checking(); // �޴� ��� ���� ���� �˻� �Լ�
	if (nmenu_chk != TRUE)  return;
	
	// **************************************************************************
	// �޴� ��� �Ұ����� ��쿡 ���� ���� �˻��Ѵ�                              
	// -> ����Ʈ ��� �Ǵ� ƼĪ ��尡 �����Ǿ� �ִ��� �˻�                      
	// **************************************************************************
	if (st_handler.mn_level_teach !=  TRUE)
	{
		if (st_handler.mn_level_maint !=  TRUE) 
		{
			OnLevel();
			if (st_handler.mn_level_teach !=  TRUE)
			{
				if (st_handler.mn_level_maint !=  TRUE)  return;
			}
		}
	}
	// **************************************************************************
	
	if (GetActiveView()->IsKindOf(RUNTIME_CLASS(CScreen_Motor)))   return;
	OnSwitchToForm(IDW_SCREEN_MOTOR_TEACH);
}

//==================================================================//
// �۾��� �𵨸��� �����ϴ��� Ȯ��
//==================================================================//
int CMainFrame::OnIsExistDvcFie() 
{
	// [�ʱ�ȭ] �Լ� ���� �÷��� (�۾���)
	int FuncRet = RET_PROCEED;

	//==============================================================//
	// ����̽� ������ ����� ������ �����ϴ��� �˻�
	// - ƼĪ ���� ����Ǿ� ����
	//==============================================================//
	CString sLoadDvc;	// �ε��� ����̽��� ����
	CString sExtension;	// ���� Ȯ���� ����
	int nPos;
	char chData[50];

	// �ε��� ����̽� ������ �������� �˻�
	if (st_basic.sDvcName == "")
	{
		::GetPrivateProfileString("BasicData", "DeviceType", "-1", chData, 50, st_path.mstr_basic);
		sLoadDvc = chData;
		sLoadDvc.TrimLeft(' ');
		sLoadDvc.TrimRight(' ');

		// Ȯ���� ��ġ �˻�
		nPos = sLoadDvc.Find(".TXT");
		if (nPos == -1)
		{
			st_basic.sDvcName = sLoadDvc + ".TXT";
		}
		else
		{
			sExtension = sLoadDvc.Mid(nPos);  // Ȯ���� ���� ����
			// Ȯ���ڰ� Ʋ���� �⺻ ����̽����� ����
			if (sExtension != ".TXT")
			{
				st_basic.sDvcName = "DEFAULT.TXT";

				if (st_handler.cwnd_list != NULL)
				{
					sprintf(st_msg.c_normal_msg, "[DEVICE FILE[DEFAULT.DAT]] The error happened at a file Exist-1.");
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
					Func.On_LogFile_Add(LOG_TOTAL, st_msg.c_normal_msg);
				}
			}
			else
			{
				st_basic.sDvcName = sLoadDvc;
			}
		}
	}
	//--------------------------------------------------------------//

	//==============================================================//
	// ����̽� ������ �����ϴ��� Ȯ��
	//==============================================================//
	CFileFind finder;
	
	BOOL bFlag = finder.FindFile(st_path.mstr_path_dvc + st_basic.sDvcName);
	finder.Close();

	if (bFlag == 1)
	{
		// ���������� ����̽� ������ ������
	}
	else
	{
		if (st_handler.cwnd_list != NULL)
		{
			sprintf(st_msg.c_normal_msg, "[Device Type File Not Exist] The error happened at a file Exist-1.");
// 			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
			Func.On_LogFile_Add(LOG_TOTAL, st_msg.c_normal_msg);
		}

		// ������ �������� �ʴ´ٰ� ��� �˶��� ��½�Ŵ
		g_ioMgr.set_out_bit(st_io.o_buzzer_1, IO_ON);

		// 900005 0 21 "����Ϸ��� Device Type�� ������ ���ϰ�ο� �����ϴ�[Device Type ���� Copy���]."
//		alarm.mstr_code		= "900005";
//		alarm.mn_count_mode	= 0;
//		alarm.mn_type_mode	= eWARNING;
//		COMI.mn_run_status	= dWARNING;
		CTL_Lib.Alarm_Error_Occurrence(660, CTL_dWARNING, "900005" );

		FuncRet = RET_ERROR;
	}
	//--------------------------------------------------------------//

	return FuncRet;
}


LRESULT CMainFrame::OnMainframe_Work(WPARAM wParam, LPARAM lParam)
{	
	int mn_command_num = wParam;  // ��Ʈ��ũ �۾��� �� ���� ����

	int mn_inter = lParam;
	
	switch (mn_command_num)
	{		
	case 2:		// ������ ȭ�鿡�� ������ Ȯ��
		SetTimer(TMR_MAIN_ELEC_CHK, 100, NULL);
		break;
				
	case 1001:
		OnMainFrame_SelectMessageDisplay();
		break;

	case 1002://ybs
// 		SetTimer(TMR_SMEMA_CLIENT1, 2000, NULL);
// 		SetTimer(TMR_SMEMA_CLIENT2, 2000, NULL);
// 		SetTimer(TMR_SMEMA_CLIENT2, 2000, NULL);
// 		SetTimer(TMR_SMEMA_SERVER, 2000, NULL);
// 		KillTimer(TMR_SMEMA_CLIENT1);
// 		KillTimer(TMR_SMEMA_CLIENT2);
// 		KillTimer(TMR_SMEMA_CLIENT2);
// 		KillTimer(TMR_SMEMA_SERVER);
		break;

	case 1003:
		mn_ServerStep = 0;
		mn_Sinterface = mn_inter;
// 		SetTimer(TMR_SERVERM_CHK, 100, NULL);

	case 1004:
		OnMainFrame_RejectMessageDisplay();
		break;

	case 1005:
		SetTimer(TMR_XGEM_CHK, 1400, 0);
		break;

	case 1006:
		OnMain_Alarm_Mysql_Write();
		break;

	}
	
	return 0;
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	CString str_display_time;
	int n_hour, n_minute, n_second;
	int n_min_temp;	// �� �ð� [��] ���� ���� 
	int n_year, n_month, n_day;				// ��, ��, �� ���� ����
	int nRet;

	int nIndexMin = 0, nIndexSec = 0;
	int nCyclexMin = 0, nCycleSec = 0;

	CString strTimeLog;
	CString mstr_temp;

	CString mStartTime, mEndTime; 
//	char cStartTime[60], cEndTime[60];

	COleDateTime cur_time;
	CTime bin_time;

	if (nIDEvent == TMR_MAIN_REFRESH)
	{
		CTime cur = CTime::GetCurrentTime();
		CTimeSpan diff = cur - st_handler.m_tRef;

		st_handler.m_tRef = cur;

		switch(COMI.mn_run_status)
		{			
		case dRUN://2013,0215
			if(st_work.mn_tl_status == dSELFCHECK)
			{//dSTOP
// 				if( g_lotMgr.GetLotCount() > 0 ) st_work.mn_chg_job = CTL_YES;
// 				else							 st_work.mn_chg_job = CTL_NO;

				if(st_work.mn_chg_job == CTL_YES)
				{
					st_handler.m_tC = st_handler.m_tC + diff;
					st_handler.m_tDC = st_handler.m_tDC + diff;
				}
				st_handler.m_tI = st_handler.m_tI + diff;
				st_handler.m_tDI = st_handler.m_tDI + diff;
			}
			else
			{
				st_handler.m_tR = st_handler.m_tR + diff;
				st_handler.m_tDR = st_handler.m_tDR + diff;
			}
			break;

		case dWARNING:
		case dJAM:		
			st_handler.m_tJ = st_handler.m_tJ + diff;
			st_handler.m_tDJ = st_handler.m_tDJ + diff;
			break;

		case dLOCK:
			st_handler.m_tM = st_handler.m_tM + diff;
			st_handler.m_tDM = st_handler.m_tDM + diff;
			break;
		
		case dLOTEND:												// Lot End �ÿ��� Stop���� �ð��� �ø���.
		case dSTOP:
			if( st_work.mn_jam == CTL_YES ) 
			{
				if( GetCurrentTime() - st_handler.m_dwJamStartTime <= 0 )
				{
					st_handler.m_dwJamStartTime = GetCurrentTime();
				}
				if( GetCurrentTime() - st_handler.m_dwJamStartTime > 60*3*1000 )
				{
					st_work.mn_jam = CTL_READY;
				}				
				st_handler.m_tJ = st_handler.m_tJ + diff;
				st_handler.m_tDJ = st_handler.m_tDJ + diff;
			}
			else if( st_work.mn_jam == CTL_READY )
			{
				st_handler.m_tM = st_handler.m_tM + diff;
				st_handler.m_tDM = st_handler.m_tDM + diff;
			}
			else
			{
				if(st_work.mn_tl_status == dSELFCHECK)
				{
					st_handler.m_tI = st_handler.m_tI + diff;
					st_handler.m_tDI = st_handler.m_tDI + diff;
				}
				else
				{
					st_handler.m_tS = st_handler.m_tS + diff;
					st_handler.m_tDS = st_handler.m_tDS + diff;
				}
			}
			break;
		}

		if (st_handler.cwnd_main != NULL)
		{//2013,0215
			if(st_work.mn_tl_status == dSELFCHECK)
			{
				st_handler.cwnd_main->PostMessage(WM_WORK_END, MAIN_TIMEINFO, dSTOP);
				st_handler.cwnd_main->PostMessage(WM_WORK_END, MAIN_TIMEINFO, dRUN);
			}
			else
			{
				st_handler.cwnd_main->PostMessage(WM_WORK_END, MAIN_TIMEINFO, COMI.mn_run_status);
			}
		}
	}
	else if (nIDEvent == TMR_MAT_CHK)
	{
		//2016.1123
		//////////////////////////////////////////////////////////////////////////////////////
		if( COMI.mn_run_status == dRUN )
		{
			nRet = g_ioMgr.get_in_bit(st_io.i_front_top_machine_stop_signal_chk, IO_ON);
			if( nRet == IO_ON )
			{
				sprintf(st_msg.c_normal_msg, "Handler stopped because AMT8580S door is opened.");
				Func.On_LogFile_Add(LOG_TOTAL, st_msg.c_normal_msg);
			}
		}
		//////////////////////////////////////////////////////////////////////////////////////


		//2015.0530
		CString strmat;
		int nDen[6]={0,};
		nDen[0] = 2000 - st_work.n_mat_density[0];
		if(nDen[0] <= 0) nDen[0] = 2000;
		nDen[1] = 2000 - st_work.n_mat_density[1];
		if(nDen[10] <= 0) nDen[1] = 2000;
		nDen[2] = 2000 - st_work.n_mat_density[2];
		if(nDen[2] <= 0) nDen[2] = 2000;
		nDen[3] = 2000 - st_work.n_mat_density[3];
		if(nDen[3] <= 0) nDen[3] = 2000;
		nDen[4] = 2000 - st_work.n_mat_density[4];
		if(nDen[4] <= 0) nDen[4] = 2000;
		nDen[5] = 2000 - st_work.n_mat_density[5];
		if(nDen[5] <= 0) nDen[5] = 2000;
		
		int nBcr1[2] = {0,};
		int nBcr2[2] = {0,};
		int nRin1[2] = {0,};
		int nRin2[2] = {0,};
		nBcr1[0] = 3000 - st_work.n_mat_bcr[0];
		if(nBcr1[0] <= 0) nBcr1[0] = 3000;
		nBcr1[1] = 3000 - st_work.n_mat_bcr[1];
		if(nBcr1[1] <= 0) nBcr1[1] = 3000;
		
		nBcr2[0] = 3000 - st_work.n_mat_bcr[2];
		if(nBcr2[0] <= 0) nBcr2[0] = 3000;
		nBcr2[1] = 3000 - st_work.n_mat_bcr[3];
		if(nBcr2[1] <= 0) nBcr2[1] = 3000;
		
		nRin1[0] = 5000 - st_work.n_mat_ribbon[0];
		if(nRin1[0] <= 0) nRin1[0] = 5000;
		nRin1[1] = 5000 - st_work.n_mat_ribbon[1];
		if(nRin1[1] <= 0) nRin1[1] = 5000;
		nRin2[0] = 5000 - st_work.n_mat_ribbon[2];
		if(nRin2[0] <= 0) nRin2[0] = 5000;
		nRin2[1] = 5000 - st_work.n_mat_ribbon[3];
		if(nRin2[1] <= 0) nRin2[1] = 5000;
		
		
		strmat.Format("DENSITY1, %d, %d", st_work.n_mat_density[0], nDen[0]);
		Func.On_LogFile_Add(LOG_MAT, strmat, 2);
		strmat.Format("DENSITY2, %d, %d", st_work.n_mat_density[1], nDen[1]);
		Func.On_LogFile_Add(LOG_MAT, strmat, 1);
		strmat.Format("DENSITY3, %d, %d", st_work.n_mat_density[2], nDen[2]);
		Func.On_LogFile_Add(LOG_MAT, strmat, 1);
		strmat.Format("DENSITY4, %d, %d", st_work.n_mat_density[3], nDen[3]);
		Func.On_LogFile_Add(LOG_MAT, strmat, 1);
		strmat.Format("DENSITY5, %d, %d", st_work.n_mat_density[4], nDen[4]);
		Func.On_LogFile_Add(LOG_MAT, strmat, 1);
		strmat.Format("DENSITY6, %d, %d", st_work.n_mat_density[5], nDen[5]);
		Func.On_LogFile_Add(LOG_MAT, strmat, 1);
		strmat.Format("BCR1, %d, %d", st_work.n_mat_bcr[0], nBcr1[0]);
		Func.On_LogFile_Add(LOG_MAT, strmat, 1);
		strmat.Format("BCR2, %d, %d", st_work.n_mat_bcr[1], nBcr1[1]);
		Func.On_LogFile_Add(LOG_MAT, strmat, 1);
		strmat.Format("BCR3, %d, %d", st_work.n_mat_bcr[2], nBcr2[0]);
		Func.On_LogFile_Add(LOG_MAT, strmat, 1);			
		strmat.Format("BCR4, %d, %d", st_work.n_mat_bcr[3], nBcr2[1]);
		Func.On_LogFile_Add(LOG_MAT, strmat, 1);			
		strmat.Format("RIBBON1, %d, %d", st_work.n_mat_ribbon[0], nRin1[0]);
		Func.On_LogFile_Add(LOG_MAT, strmat, 1);
		strmat.Format("RIBBON2, %d, %d", st_work.n_mat_ribbon[1], nRin1[1]);
		Func.On_LogFile_Add(LOG_MAT, strmat, 1);
		strmat.Format("RIBBON3, %d, %d", st_work.n_mat_ribbon[2], nRin2[0]);
		Func.On_LogFile_Add(LOG_MAT, strmat, 1);		
		strmat.Format("RIBBON4, %d, %d", st_work.n_mat_ribbon[2], nRin2[0]);
		Func.On_LogFile_Add(LOG_MAT, strmat, 1);		


		AMTRegistry::RegWriteInt( REG_KEY_COUNT, REG_VAL_COUNT_DENSITY_1, st_work.n_mat_density[0] );
		AMTRegistry::RegWriteInt( REG_KEY_COUNT, REG_VAL_COUNT_DENSITY_2, st_work.n_mat_density[1] );
		AMTRegistry::RegWriteInt( REG_KEY_COUNT, REG_VAL_COUNT_DENSITY_3, st_work.n_mat_density[2]);
		AMTRegistry::RegWriteInt( REG_KEY_COUNT, REG_VAL_COUNT_DENSITY_4, st_work.n_mat_density[3]);
		AMTRegistry::RegWriteInt( REG_KEY_COUNT, REG_VAL_COUNT_DENSITY_5, st_work.n_mat_density[4]);
		AMTRegistry::RegWriteInt( REG_KEY_COUNT, REG_VAL_COUNT_DENSITY_6, st_work.n_mat_density[5]);

		AMTRegistry::RegWriteInt( REG_KEY_COUNT, REG_VAL_COUNT_BCR_1, st_work.n_mat_bcr[0]);
		AMTRegistry::RegWriteInt( REG_KEY_COUNT, REG_VAL_COUNT_BCR_2, st_work.n_mat_bcr[1]);
		AMTRegistry::RegWriteInt( REG_KEY_COUNT, REG_VAL_COUNT_BCR_3, st_work.n_mat_bcr[2]);
		AMTRegistry::RegWriteInt( REG_KEY_COUNT, REG_VAL_COUNT_BCR_4, st_work.n_mat_bcr[3]);

		AMTRegistry::RegWriteInt( REG_KEY_COUNT, REG_VAL_COUNT_RIBBON_1, st_work.n_mat_ribbon[0]);
		AMTRegistry::RegWriteInt( REG_KEY_COUNT, REG_VAL_COUNT_RIBBON_2, st_work.n_mat_ribbon[1]);
		AMTRegistry::RegWriteInt( REG_KEY_COUNT, REG_VAL_COUNT_RIBBON_3, st_work.n_mat_ribbon[2]);
		AMTRegistry::RegWriteInt( REG_KEY_COUNT, REG_VAL_COUNT_RIBBON_4, st_work.n_mat_ribbon[3]);

	}
	else if (nIDEvent == TMR_SERVERM_CHK)
	{
		nRet = OnServerInterace(mn_Sinterface);
		if (nRet == CTLBD_RET_GOOD)
		{
			KillTimer(TMR_SERVERM_CHK);
		}
		else if (nRet == CTLBD_RET_ERROR)
		{
			KillTimer(TMR_SERVERM_CHK);
		}
	}	
	else if (nIDEvent == TMR_FILE_CREATE)
	{

		// **********************************************************************
		// ���� ���� �� �ʿ��� �ð� �����Ѵ�                                     
		// **********************************************************************
		cur_time = COleDateTime::GetCurrentTime();

		COleDateTimeSpan span( 0, 22, 0, 0 ); // �Ϸ�.
		COleDateTime timeLastDay( m_timeLastDay );
		COleDateTime timeSpan = COleDateTime::GetCurrentTime() - span;
		if( timeSpan >= timeLastDay )
		{
			Func.OnDailyDataSave();
			Func.UnloadDataClear();
			Func.OnDayDataReset();

			COleDateTimeSpan span2( 1, 0, 0, 0 );
			timeSpan += span2;
			timeSpan.GetAsSystemTime( m_timeLastDay );
			m_timeLastDay.wHour = 0;
			m_timeLastDay.wMinute = 0;
			m_timeLastDay.wSecond = 0;
			m_timeLastDay.wMilliseconds = 0;

			AMTRegistry::RegWriteTime( m_timeLastDay );
		}
		
		n_hour = cur_time.GetHour();
		n_minute = cur_time.GetMinute();
		n_second = cur_time.GetSecond();

		n_year = cur_time.GetYear();  
		n_month = cur_time.GetMonth();  
		n_day = cur_time.GetDay();  

// 		if (n_hour == 21 && n_minute >= 59 && n_second >= 59)
// 		{
// 			Func.OnDailyDataSave();
// 			Func.OnDayDataReset();
// 		}

		n_min_temp = n_hour * 60 + n_minute;

		// ������ Ȯ���� ���� �ð� Ȯ��.
		if (n_second == 0)
		{
			if ( n_min_temp % st_basic.mn_electrostatic_check_gap == 0)
			{
//				SetTimer(TMR_MAIN_ELEC_CHK, 200, NULL);

				//kwlee 2016.0821
				st_gms_info.strMsg[1] = st_gms_info.strMsg[0];
				//SetTimer(TMR_MAIN_ELEC_CHK, 200, NULL);
				//OnWriteGmsLog(); 

				//OnGmsDataSave();
			}
		}
		if ( n_hour != 22 && n_second == 0 )
		{
			if ( n_min_temp % 60 == 0)
			{
				Func.UnloadDataClear();
			}
		}

	}
	else if (nIDEvent == TMR_MAIN_ELEC_CHK)
	{
		//kwlee 2016.0821
		//nRet = OnElectrostatic_Check();
// 		nRet = clsGms.OnElectrostatic_Check(); 
// 		
// 		if (nRet == CTLBD_RET_ERROR)
// 		{
// 			KillTimer(TMR_MAIN_ELEC_CHK);
// 		}
	}
	/////////20131115
	else if (nIDEvent == TMR_BCR_SETTING)
	{
		nRet = OnBarcode_SetValue_Change();
		
		if (nRet == CTLBD_RET_GOOD)
		{
			KillTimer(TMR_BCR_SETTING);
		}
		else if (nRet == CTLBD_RET_ERROR)
		{
			KillTimer(TMR_BCR_SETTING);
		}
	}
	/////////
	else if( nIDEvent == TMR_SMEMA_REAR_CHK)
	{
		nRet = OnRear_Smema_Check();
		if (1 || nRet == CTLBD_RET_GOOD)
		{
			KillTimer(TMR_SMEMA_REAR_CHK);
		}
		else if (nRet == CTLBD_RET_ERROR)
		{
			KillTimer(TMR_SMEMA_REAR_CHK);
		}
	}
	else if (nIDEvent == TMR_GMS_CHK)
	{
		clsGms.OnGmsDataCheck();
	}
	else if( nIDEvent == TMR_SMEMA_CLIENT1)//ybs
	{
		if( st_client[CLS_BOTTOM].n_connect == CTL_YES) KillTimer(TMR_SMEMA_CLIENT1);
		KillTimer(TMR_SMEMA_CLIENT1);
		return;
		nSmaCount1++;
		if( nSmaCount1 > 3)
		{
			nSmaCount1 = 0;
			KillTimer(TMR_SMEMA_CLIENT1);
			return;
		}
		::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + CLS_BOTTOM, CLIENT_CONNECT, CLS_BOTTOM);	
	}
	else if( nIDEvent == TMR_SMEMA_CLIENT2)
	{
// 		if( st_client[CLS_8570].n_connect == CTL_YES) KillTimer(TMR_SMEMA_CLIENT2);
// 		KillTimer(TMR_SMEMA_CLIENT2);
// 		return;
// 		nSmaCount2++;
// 		if( nSmaCount2 > 3)
// 		{
// 			nSmaCount2 = 0;
// 			KillTimer(TMR_SMEMA_CLIENT2);
// 			return;
// 		}
// 		::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + CLS_8570, CLIENT_CONNECT, CLS_8570);	
	}
	else if( nIDEvent == TMR_SMEMA_CLIENT3)
	{
// 		for ( int i = CLS_BCR_PRINTER1; i < CLS_VIS_DENSITY; i++)
// 		{
// 			if( st_client[i].n_connect == CTL_NO)
// 			{
// 				nSmaCount3[i]++;
// 				if( nSmaCount3[i] > 3)
// 				{
// 					nSmaCount3[i] = 0;
// 					KillTimer(TMR_SMEMA_CLIENT2);
// 					break;
// 				}
// 				::SendMessage(st_handler.hWnd, WM_CLIENT_MSG + i, CLIENT_CONNECT, i);
// 				break;
// 			}
// 			KillTimer(TMR_SMEMA_CLIENT3);
// 		}
	}
	else if( nIndexSec == TMR_SMEMA_SERVER )
	{
// 		for ( int j = 0; j < 3; j++)
// 		{
// 			if( st_server[j].n_connect == CTL_NO)
// 			{
// 				nSmaCount3[j]++;
// 				if( nSmaCount3[j] > 3)
// 				{
// 					nSmaCount3[j] = 0;
// 					KillTimer(TMR_SMEMA_SERVER);
// 					break;
// 				}
// 				::SendMessage(st_handler.hWnd, WM_SERVER_MSG + j, SERVER_CONNECT, j);
// 				break;
// 			}
// 			KillTimer(TMR_SMEMA_SERVER);
// 		}
		
	}
	////2015.0221
	else if (nIDEvent == TMR_XGEM_CHK)
	{
		nRet = OnXgmInterface();
		if (nRet == CTLBD_RET_GOOD)
		{
			KillTimer(TMR_XGEM_CHK);
		}
		else if (nRet == CTLBD_RET_ERROR)
		{
			KillTimer(TMR_XGEM_CHK);
		}
	}	
	////

	CFrameWnd::OnTimer(nIDEvent);
}
//kwlee 2016.0821
void CMainFrame::OnWriteGmsLog()
{
	//kwlee 2016.0706
	CString strLog;
	if (st_gms_info.strData ==	_T("EOS"))
	{
		if (st_gms_info.strChan[0] == "1" && st_gms_info.strChan[7] == "8")
		{		
			for (int i =0; i<8; i++)
			{
				strLog.Format("Channel : %s Volt : %s", st_gms_info.strChan[i], st_gms_info.strValVolt[i]);
				Func.On_LogFile_Add( LOG_GMS, strLog, 1);
			}
		}
	}
}
///

int CMainFrame::OnRear_Smema_Check()
{
	int nFuncRet = CTLBD_RET_PROCEED;

	switch(nRearSmemaStep)
	{
	case 0:
//		if(g_ioMgr.get_in_bit( st_io.i_rear_shuttle_aline_request_signal_chk, IO_ON) == IO_ON ||
//			g_ioMgr.get_in_bit( st_io.i_rear_shuttle_bline_request_signal_chk, IO_ON) == IO_ON )
//		{
//			m_dwTime_RearSmema = GetCurrentTime();
			nRearSmemaStep = 1000;
//		}
//		else// if(g_ioMgr.get_in_bit( st_io.i_rear_shuttle_aline_request_signal_chk, IO_ON) == IO_OFF && g_ioMgr.get_in_bit( st_io.i_rear_shuttle_bline_request_signal_chk, IO_ON == IO_OFF))
//		{
//			m_dwTime_RearSmema = GetCurrentTime();
//			nRearSmemaStep = 2000;
//		}
		break;

	case 1000:
//		if( GetCurrentTime() - m_dwTime_RearSmema < 0 ) m_dwTime_RearSmema = GetCurrentTime();
//		if( GetCurrentTime() - m_dwTime_RearSmema < 1000) break;
//		if(g_ioMgr.get_in_bit( st_io.i_rear_shuttle_aline_request_signal_chk, IO_ON) == IO_ON ||
//			g_ioMgr.get_in_bit( st_io.i_rear_shuttle_bline_request_signal_chk, IO_ON == IO_ON) )
//		{
//			if( st_handler.mn_smema_rear_run != 1)
//			{
//				st_handler.mn_smema_rear_run = 1;
//				if( st_handler.cwnd_title !=NULL)
//				{
//					st_handler.cwnd_title->PostMessage(WM_STATUS_CHANGE, SMEMA_ONOFF, 0);
//				}
//			}
//		}
		nRearSmemaStep = 0;
		break;

	case 2000:
//		if( GetCurrentTime() - m_dwTime_RearSmema < 0 ) m_dwTime_RearSmema = GetCurrentTime();
//		if( GetCurrentTime() - m_dwTime_RearSmema < 1000) break;
//		if(g_ioMgr.get_in_bit( st_io.i_rear_shuttle_aline_request_signal_chk, IO_ON) == IO_OFF &&
//			g_ioMgr.get_in_bit( st_io.i_rear_shuttle_bline_request_signal_chk, IO_ON) == IO_OFF )
//		{
//			if( st_handler.mn_smema_rear_run != 0)
//			{
//				st_handler.mn_smema_rear_run = 0;
//				if( st_handler.cwnd_title !=NULL)
//				{
//					st_handler.cwnd_title->PostMessage(WM_STATUS_CHANGE, SMEMA_ONOFF, 0);
//				}
//			}
//		}
		nRearSmemaStep = 0;
		break;
	}

	return nFuncRet;

}

// int CMainFrame::OnElectrostatic_Check()
// {
// 	int nFunRet = CTLBD_RET_PROCEED;
// 	int i;
// 
// 	// �ø��� ��Ʈ�� �������� �ʾҴٸ� �׳� �н�...
// 	if (st_handler.mnSerial_Port_Creating[GMS_PORT-1] != CTL_YES)
// 	{
// 		return CTLBD_RET_GOOD;
// 	}
// 	
// 	switch (nElectrostaticCheckStep)
// 	{
// 	case 0:
// 		strElectCommand.Format("%c%cP%-8sCH%d %c", 0x10, 0x02, "SAMSUNG1", nElectChannel, 0x03);
// 		st_serial.mstr_snd[GMS_PORT-1] = strElectCommand;
// 		st_work.mn_elec_serial_work = CTL_READY;
// 		lElectSerialTime[0] = GetCurrentTime();
// 		OnDataSend(GMS_PORT, 0);
// 		nElectrostaticCheckStep = 100;
// 		break;
// 		
// 	case 100:
// 		if (st_work.mn_elec_serial_work == CTL_YES)				// ���� �Ϸ�
// 		{
// 			nElectrostaticCheckStep = 200;
// 		}
// 		else if (st_work.mn_elec_serial_work == CTL_NO)			// ������ �Ϸ�
// 		{
// 			nFunRet = CTLBD_RET_ERROR;
// 			nElectrostaticCheckStep = 0;
// 		}
// 		else													// �̵����� �ƴҶ�...
// 		{
// 			lElectSerialTime[1] = GetCurrentTime();
// 			lElectSerialTime[2] = lElectSerialTime[1] - lElectSerialTime[0];
// 			
// 			if (lElectSerialTime[2] > 100000)					// 10�� ���
// 			{
// 				nFunRet = CTLBD_RET_ERROR;
// 				nElectrostaticCheckStep = 0;
// 			}
// 			else if(lElectSerialTime[2] < 0)//2013,0608
// 			{
// 				lElectSerialTime[0] = GetCurrentTime();
// 			}
// 		}
// 		break;
// 		
// 	case 200:
// 		if (nElectChannel == 5)									// ������ ä�α��� ������...
// 		{
// 			nElectChannel = 1;									// �����ϰ�.
// 			nElectrostaticCheckStep = 300;
// 		}
// 		else if (nElectChannel < 5)
// 		{
// 			nElectChannel++;
// 			nElectrostaticCheckStep = 0;
// 		}
// 		break;
// 		
// 	case 300:
// 		st_grounddb.mole_date = COleDateTime::GetCurrentTime();
// 		Func.DB_Write_Ground(st_grounddb);			// �����Ѵ�.
// 		
// 		for (i = 0; i < 5; i++)
// 		{
// 			if (st_work.mdReadElectData[i]  > st_basic.md_electrostatic_value)		// ������ + ������ �⺻�� ���� ũ��
// 			{
// 				nFunRet = CTLBD_RET_ERROR;
// 				nElectrostaticCheckStep = 0;
// 				break;
// 			}
// 		}
// 		
// 		// �����̴ϱ� ����.
// 		for (i = 0; i < 5; i++)
// 		{
// 			st_work.mdReadElectData[i] = 0;
// 			st_grounddb.mstrChannel[i] = "";
// 		}
// 		
// 		nElectrostaticCheckStep = 0;
// 		nFunRet = CTLBD_RET_GOOD;
// 		break;
// 	}
// 	
// 	return nFunRet;
// }

void CMainFrame::OnMotSpeed() 
{
	// **************************************************************************
    // ȭ�� �� ��ȯ �Ұ����� ���� �˻��Ѵ�.                                      
    // **************************************************************************
	int nmenu_chk = OnMenu_Change_Checking(); // �޴� ��� ���� ���� �˻� �Լ�
	if (nmenu_chk != TRUE)  return;
	
	// **************************************************************************
	// �޴� ��� �Ұ����� ��쿡 ���� ���� �˻��Ѵ�                              
	// -> ����Ʈ ��� �Ǵ� ƼĪ ��尡 �����Ǿ� �ִ��� �˻�                      
	// **************************************************************************
	if (st_handler.mn_level_teach !=  TRUE)
	{
		if (st_handler.mn_level_maint !=  TRUE) 
		{
			OnLevel();
			if (st_handler.mn_level_teach !=  TRUE)
			{
				if (st_handler.mn_level_maint !=  TRUE)  return;
			}
		}
	}
	// **************************************************************************
	
	if (GetActiveView()->IsKindOf(RUNTIME_CLASS(CScreen_Motor_Speed)))   return;
	OnSwitchToForm(IDW_SCREEN_MOTOR_SPEED);	
}

void CMainFrame::OnSetInterface() 
{
// 	// **************************************************************************
//     // ȭ�� �� ��ȯ �Ұ����� ���� �˻��Ѵ�.                                      
//     // **************************************************************************
// 	int nmenu_chk = OnMenu_Change_Checking(); // �޴� ��� ���� ���� �˻� �Լ�
// 	if (nmenu_chk != TRUE)  return;
// 	
// 	// **************************************************************************
// 	// �޴� ��� �Ұ����� ��쿡 ���� ���� �˻��Ѵ�                              
// 	// -> ����Ʈ ��� �Ǵ� ƼĪ ��尡 �����Ǿ� �ִ��� �˻�                      
// 	// **************************************************************************
// 	if (st_handler.mn_level_teach !=  TRUE)
// 	{
// 		if (st_handler.mn_level_maint !=  TRUE) 
// 		{
// 			OnLevel();
// 			if (st_handler.mn_level_teach !=  TRUE)
// 			{
// 				if (st_handler.mn_level_maint !=  TRUE)  return;
// 			}
// 		}
// 	}
// 	// **************************************************************************
// 	
// 	if (GetActiveView()->IsKindOf(RUNTIME_CLASS(CScreen_Set_Interface)))   return;
// 	OnSwitchToForm(IDW_SCREEN_SET_INTERFACE);	
}

void CMainFrame::OnSetMaintenance() 
{
	// **************************************************************************
    // ȭ�� �� ��ȯ �Ұ����� ���� �˻��Ѵ�.                                      
    // **************************************************************************
	int nmenu_chk = OnMenu_Change_Checking(); // �޴� ��� ���� ���� �˻� �Լ�
	if (nmenu_chk != TRUE)  return;
	
// 	// **************************************************************************
// 	// �޴� ��� �Ұ����� ��쿡 ���� ���� �˻��Ѵ�                              
// 	// -> ����Ʈ ��� �Ǵ� ƼĪ ��尡 �����Ǿ� �ִ��� �˻�                      
// 	// **************************************************************************
// 	if (st_handler.mn_level_teach !=  TRUE)
// 	{
// 		if (st_handler.mn_level_maint !=  TRUE) 
// 		{
// 			OnLevel();
// 			if (st_handler.mn_level_teach !=  TRUE)
// 			{
// 				if (st_handler.mn_level_maint !=  TRUE)  return;
// 			}
// 		}
// 	}
	// **************************************************************************
	
	if (GetActiveView()->IsKindOf(RUNTIME_CLASS(CScreen_Set_Maintenance)))   return;
	OnSwitchToForm(IDW_SCREEN_SET_MAINTENANCE);	
}
////2015,0109
void CMainFrame::OnSetNetwork()
{
	/* ************************************************************************** */
    /* ȭ�� �� ��ȯ �Ұ����� ���� �˻��Ѵ�.                                       */
    /* ************************************************************************** */
	int nmenu_chk = OnMenu_Change_Checking(); // �޴� ��� ���� ���� �˻� �Լ�
	if (nmenu_chk != TRUE)  return;
	
	/* ************************************************************************** */
	/* �޴� ��� �Ұ����� ��쿡 ���� ���� �˻��Ѵ�                               */
	/* -> ����Ʈ ��� �Ǵ� ƼĪ ��尡 �����Ǿ� �ִ��� �˻�                       */
	/* ************************************************************************** */
	//	if (st_ICT.n_level_teach !=  TRUE)
	//	{
	//		if (st_ICT.n_level_maint !=  TRUE)  return;
	//	}
	/* ************************************************************************** */
	
	if(GetActiveView()->IsKindOf(RUNTIME_CLASS(CScreen_Set_Network)))   return;
	OnSwitchToForm(IDW_SCREEN_SET_NETWORK);
}
////
void CMainFrame::OnSetBarcode() 
{
	/* ************************************************************************** */
    /* ȭ�� �� ��ȯ �Ұ����� ���� �˻��Ѵ�.                                       */
    /* ************************************************************************** */
	int nmenu_chk = OnMenu_Change_Checking(); // �޴� ��� ���� ���� �˻� �Լ�
	if (nmenu_chk != TRUE)  return;
	
	/* ************************************************************************** */
	/* �޴� ��� �Ұ����� ��쿡 ���� ���� �˻��Ѵ�                               */
	/* -> ����Ʈ ��� �Ǵ� ƼĪ ��尡 �����Ǿ� �ִ��� �˻�                       */
	/* ************************************************************************** */
	//	if (st_ICT.n_level_teach !=  TRUE)
	//	{
	//		if (st_ICT.n_level_maint !=  TRUE)  return;
	//	}
	/* ************************************************************************** */
	
	if(GetActiveView()->IsKindOf(RUNTIME_CLASS(CScreen_Set_Barcode)))   return;
	OnSwitchToForm(IDW_SCREEN_SET_BARCODE);
}

void CMainFrame::OnAdmin() 
{
	// **************************************************************************
    // ȭ�� �� ��ȯ �Ұ����� ���� �˻��Ѵ�.                                      
    // **************************************************************************
	int nmenu_chk = OnMenu_Change_Checking(); // �޴� ��� ���� ���� �˻� �Լ�
	if (nmenu_chk != TRUE)  return;
	
	// **************************************************************************
	// �޴� ��� �Ұ����� ��쿡 ���� ���� �˻��Ѵ�                              
	// -> ����Ʈ ��� �Ǵ� ƼĪ ��尡 �����Ǿ� �ִ��� �˻�                      
	// **************************************************************************
	if (st_handler.mn_level_teach !=  TRUE)
	{
		if (st_handler.mn_level_maint !=  TRUE) 
		{
			OnLevel();
			if (st_handler.mn_level_teach !=  TRUE)
			{
				if (st_handler.mn_level_maint !=  TRUE)  return;
			}
		}
	}
	// **************************************************************************
	
	if (GetActiveView()->IsKindOf(RUNTIME_CLASS(CScreen_Admin)))   return;
	OnSwitchToForm(IDW_SCREEN_ADMINISTRATOR);
}



void CMainFrame::OnMain_Thread_Creating()
{
	// **********************************************************************
	// ����ġ �˻� ���� ���� ������ �����Ѵ�                                 
	// **********************************************************************
	m_thread[THREAD_HANDLER_CHK]=AfxBeginThread(OnThread_Handler_Check, this);
	if (m_thread[THREAD_HANDLER_CHK] != NULL) 	
		hThrHandle[THREAD_HANDLER_CHK] = m_thread[THREAD_HANDLER_CHK]->m_hThread;
	// **********************************************************************

	// **********************************************************************
	// Ÿ�� ���� ��� ���� ���� ������ �����Ѵ�                              
	// **********************************************************************
	m_thread[THREAD_TOWER_LAMP_CHK]=AfxBeginThread(OnThread_Tower_Lamp_Check, this);
	if (m_thread[THREAD_TOWER_LAMP_CHK] != NULL) 	
		hThrHandle[THREAD_TOWER_LAMP_CHK] = m_thread[THREAD_TOWER_LAMP_CHK]->m_hThread;
	// **********************************************************************
	
	// **********************************************************************
	// ��� ���� �� �߻��� �˶� ����ϱ� ���� ������ �����Ѵ�                
	// **********************************************************************
	m_thread[THREAD_ALARM_DISPLAY]=AfxBeginThread(OnThread_Alarm_Display, this);
	if (m_thread[THREAD_ALARM_DISPLAY] != NULL) 	
		hThrHandle[THREAD_ALARM_DISPLAY] = m_thread[THREAD_ALARM_DISPLAY]->m_hThread;
	// **********************************************************************	

	// **********************************************************************
	//  IO ������ ���� �����带 �����Ѵ�.                         
	// **********************************************************************
	m_thread[THREAD_IO]=AfxBeginThread(OnThread_IO,this);
	if (m_thread[THREAD_IO] != NULL) 	
		hThrHandle[THREAD_IO] = m_thread[THREAD_IO]->m_hThread;
	// **********************************************************************

	m_thread[THREAD_NETWORK] = AfxBeginThread( OnThread_Network, this );
	if( m_thread[THREAD_NETWORK] != NULL )
		hThrHandle[THREAD_NETWORK] = m_thread[THREAD_NETWORK]->m_hThread;

	m_thread[THREAD_MOTORS] = AfxBeginThread( OnThread_Motors, this );
	if( m_thread[THREAD_MOTORS] != NULL )
		hThrHandle[THREAD_MOTORS] = m_thread[THREAD_MOTORS]->m_hThread;
}

void CMainFrame::OnMain_Thread_Destroy()
{
	for( int i=0; i<THREAD_COUNT; i++ )
	{
		if (hThrHandle[i])  // ������ ����
		::WaitForSingleObject(hThrHandle[i], 1500);
	}
}

///////////////20131115
LRESULT CMainFrame::OnSerialPort(WPARAM wParam,LPARAM lParam)
{
	if(wParam == CTL_YES)
	{
		OnMain_Port_Create();
	}
	else if(wParam == CTL_NO)
	{
		OnMain_Port_Close();
	}
	return 0;
}
///////////////

void CMainFrame::OnMain_Port_Create()
{
//	char parity;
	int i;
//	DWORD dwCommEvents[MAX_PORT];

	for ( i = 0; i < 3; i++)
	{
  		OnOpen(i);
	}
	return;

//	for (i = 0; i < MAX_PORT; i++)
//	{		
//		if (st_handler.mnSerial_Port_Creating[i] == CTL_NO)		// �����Ǿ� ���� ��������, �����Ѵ�.
//		{
//			// **************************************************************************
//			//  ��Ʈ �����Ѵ�                                                    
//			// **************************************************************************
//			dwCommEvents[i] = m_ports[i].MmdSerialGetCommEvents();  // �ø��� �̺�Ʈ ����
//			dwCommEvents[i] = 0;
//			dwCommEvents[i] |= EV_CTS;
//			dwCommEvents[i] |= EV_RXCHAR;
//// 		
//// 			if ( i == 0 )
//// 			{			
//// 				if (m_ports[i].MmdSerialInitializePort(this, i + 1, 9600, 78, 8, 1, 1024, dwCommEvents[i])) 
//// 					m_ports[i].MmdSerialStartMonitoring();
//// 				else 
//// 					st_serial.mstr_port_chk[i] = "NOT FOUND";				
//// 			}
//// 			else
//// 			{
//// 				if (m_ports[i].MmdSerialInitializePort(this, i + 1, 57600, 78, 8, 1, 1024, dwCommEvents[i])) 
//// 					m_ports[i].MmdSerialStartMonitoring();
//// 				else 
//// 					st_serial.mstr_port_chk[i] = "NOT FOUND";				
//// 			}
////////20131210
//			switch(rs_232.n_serial_parity[i])
//			{
//				case 0:
//					parity = 'N';
//					break;
//		
//				case 1:
//					parity = 'O';
//					break;
//
//				case 2:
//					parity = 'E';
//					break;						
//					
//				default:
//					parity = 'N';
//					break;
//			}
//
//			if (m_ports[i].MmdSerialInitializePort(this, rs_232.n_serial_port[i], rs_232.n_serial_baudrate[i], parity, rs_232.n_serial_data[i], rs_232.n_serial_stop[i], 1024, dwCommEvents[i])) 
//				m_ports[i].MmdSerialStartMonitoring();
//			else 
//				st_serial.mstr_port_chk[i] = "NOT FOUND";
////////
//
//			mstr_received[i].Empty();  // ���� �޽��� �ӽ� ���� ���� �ʱ�ȭ
//			// **************************************************************************
//			
//			if (st_serial.mstr_port_chk[i] == "NOT FOUND")
//			{
//				st_handler.mnSerial_Port_Creating[i] = CTL_READY;
//			}
//			else
//			{
//				st_handler.mnSerial_Port_Creating[i] = CTL_YES;
//			}
//		}
//	}
}

void CMainFrame::OnExitData_Saving()
{
	st_handler.mn_menu_lock = TRUE;
	
	if (st_handler.cwnd_basic != NULL)				// BASIC ȭ�� ����
	{
		st_handler.cwnd_basic->SendMessage(WM_BASIC_APPLY, 0, 0);					// BASIC DATA APPLY ��û
	}
	else if (st_handler.cwnd_maintenance != NULL)	// Tower Lamp ȭ�� ����
	{
		st_handler.cwnd_maintenance->SendMessage(WM_MAINTENANCE_APPLY, 0, 0);		// Tower Lamp DATA APPLY ��û
	}
	else if (st_handler.cwnd_testreference != NULL)	// Test Reference ȭ�� ����
	{
		st_handler.cwnd_testreference->SendMessage(WM_TESTREFERENCE_APPLY, 0, 0);	// Test Reference DATA APPLY ��û
	}
	else if (st_handler.cwnd_waittime != NULL)		// Wait Time ȭ�� ����
	{
		st_handler.cwnd_waittime->SendMessage(WM_WAITTIME_APPLY, 0, 0);				// Wait Time DATA APPLY ��û
	}
	else if (st_handler.cwnd_motorspeed != NULL)	// Motor Speed ȭ�� ����
	{
		st_handler.cwnd_motorspeed->SendMessage(WM_MOTORSPEED_APPLY, 0, 0);			// Motor Speed DATA APPLY ��û
	}
	
	/* ************************************************************************** */
    /* ȭ�鿡 ������ ��� ������ ���Ͽ� �����Ѵ�                                  */
	/* -> ���α׷� ���� �������� ���۷����Ͱ� ������ ���� ���� �����ϴ� ��� ��� */
	/* -> ��� ���� �߿� ���� �����Ǵ��� ���� ���� ���� �����ȴ�                */
    /* ************************************************************************** */
	mcls_m_basic.OnBasic_Data_Save();				// ���� ������ ����� Basic ���� ������ ���Ͽ� �����ϴ� �Լ�
	mcls_m_basic.OnWaitTime_Data_Save();			// ���� ������ ����� Wait Time ���� ������ ���Ͽ� �����ϴ� �Լ�
	mcls_m_basic.OnMotorSpeed_Set_Data_Save();		// ���� ������ ����� Motor Speed ���� ������ ���Ͽ� �����ϴ� �Լ�.
	mcls_m_basic.On_Teach_Data_Save();
	mcls_m_basic.OnMaintenance_Data_Save();
	mcls_m_basic.OnInterface_Data_Save();//20131115
//	mcls_m_basic.OnBarcode_Label_Data_Save();

	st_handler.mn_menu_lock = FALSE;
}

void CMainFrame::OnMain_Port_Close()
{
	int i;
	// **************************************************************************
	// ������ RS-232C �ø��� ��Ʈ �����Ѵ�                                       
	// -> ������ RS-232C �ø��� ��Ʈ�� �ٸ� ȭ�鿡�� ����ϰ��� �� ��쿡��      
	//    �ݵ�� ��� �� �κ��� ��Ʈ�� �ϴ� ������ �� ����ؾ� �Ѵ�              
	//  : �̹� �ش� RS-232C �ø��� ��Ʈ ���� ���¿��� �ٽ� �� �� ���� �����̴�   
	// **************************************************************************

	for ( i = 0; i < 3; i++)
	{
		OnClose(i);
	}
// 	if(st_serial.b_Manual_Port_close == CTL_NO)
// 	{
//		for(i = 0; i < MAX_PORT; i++)	//20120620
//		{
//			if(st_handler.mnSerial_Port_Creating[i] == CTL_YES)
//			{
//				m_ports[i].MmdSerialDestroyObject();
//				st_serial.mstr_port_chk[i] = "NOT FOUND";
//				st_handler.mnSerial_Port_Creating[i] = CTL_NO;
//			}	
//		}
// 	}

}

void CMainFrame::OnMain_Motor_Destroy()
{

}

LRESULT CMainFrame::OnMainMessageEvent(WPARAM wParam, LPARAM lParam)
{
	int i = 0;
	CString strTemp;
	
	if (wParam == CTL_YES)
	{
		if (mp_msg_dlg != NULL && IsWindow(mp_msg_dlg->m_hWnd))
		{
			mp_msg_dlg->SetFocus();	// ��ȭ���ڸ� Ȱ��ȭ
			mp_msg_dlg->OnEventMsg_Text_Set();
			if(lParam == 2)
				g_ioMgr.set_out_bit(st_io.o_buzzer_2, IO_ON);
		}
		else
		{
			mp_msg_dlg = new CDialog_Event_Msg;
			mp_msg_dlg->Create();
			mp_msg_dlg->ShowWindow(SW_SHOW);
			g_ioMgr.set_out_bit(st_io.o_buzzer_off_lamp, IO_ON);
			if (st_lamp.mn_buzzer_mode == CTL_YES)
			{
				if(lParam == 1)
					g_ioMgr.set_out_bit(st_io.o_buzzer_2, IO_ON);
				else
					g_ioMgr.set_out_bit(st_io.o_buzzer_2, IO_ON);

			}

		}

	}
	else if (wParam == CTL_NO)
	{
		for (i = 0; i < 3; i++)
		{
			st_msg.mstr_event_msg[i] = "";
		}
		
		if (mp_msg_dlg != NULL && IsWindow(mp_msg_dlg->m_hWnd))
		{
			mp_msg_dlg->ShowWindow(SW_HIDE);
			mp_msg_dlg->DestroyWindow();
			delete mp_msg_dlg;
			mp_msg_dlg = NULL;
		}
		
		g_ioMgr.set_out_bit(st_io.o_buzzer_off_lamp, IO_OFF);
		if (st_lamp.mn_buzzer_mode == CTL_YES)
			g_ioMgr.set_out_bit(st_io.o_buzzer_2, IO_OFF);
	}
	
	return 0;
}

void CMainFrame::OnMainFrame_SelectMessageDisplay()
{
	int ReturnVal;
	
	CDialog_Select select_dlg;
	
	st_msg.mstr_confirm_msg = _T(st_handler.mstrSelectMessage);
	ReturnVal = select_dlg.DoModal();
	
	if (ReturnVal == IDOK)
	{
		st_handler.mnSelectMessage = 1;
	}
	else
	{
		st_handler.mnSelectMessage = 2;
	}
}


void CMainFrame::OnMainFrame_RejectMessageDisplay()
{
	int ReturnVal;
	
	CDialog_Select select_dlg;
	
	g_ioMgr.set_out_bit(st_io.o_buzzer_1, IO_ON);
	st_msg.mstr_confirm_msg = _T(st_handler.mstrRejectMessage);
	ReturnVal = select_dlg.DoModal();
	
	if (ReturnVal == IDOK)
	{
		st_handler.mnRejectMessage = 1;
	}
	else
	{
		st_handler.mnRejectMessage = 2;
	}
	g_ioMgr.set_out_bit(st_io.o_buzzer_1, IO_OFF);
}

// ******************************************************************************
// RS-232C �ø��� ��Ʈ ���� �Լ�                                                 
// ******************************************************************************
LONG CMainFrame::OnCommunication(WPARAM port, LPARAM ch)
{
//	// **************************************************************************
//    // RS-232C �ø��� ��Ʈ �˻��Ѵ�                                              
//    // **************************************************************************
//	if (port <= 0 || port > MAX_PORT)  // COMM ��Ʈ �˻�
//		return -1;
//	// **************************************************************************
//    
//	if (ch == -1)  // �б� ����
//	{
//		if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
//		{
////			st_serial.mcomm_err[port-1] = _T("[���� ������] �ø��� ��Ʈ �б� ���� �߻�");
//			st_serial.mcomm_err[port-1] = _T("[RCV DATA] Serial port read error.");
//			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, port, RECEIVE_MSG);  // ���� �޽��� ��� ��û
//		}
//
//		st_serial.mn_rec_chk[port-1] = COM_ERROR;  // ���� ���� �÷��� ����
//		return 0;
//	}
//	else if (ch == -2)  // ���� ����
//	{
//		if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
//		{
////			st_serial.mcomm_err[port-1] = _T("[���� ������] �ø��� ��Ʈ ���� ���� �߻�");
//			st_serial.mcomm_err[port-1] = _T("[RCV DATA] Serial port write error.");
//			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, port, SEND_MSG);  // ���� �޽��� ��� ��û
//		}
//
//		st_serial.mn_rec_chk[port-1] = COM_ERROR;  // ���� ���� �÷��� ����
//		return 0;
//	}
//
//	if (port == GMS_PORT)
//	{
//		OnMain_Rcv_GMS(port, ch);
//	}
//	/////20131115
//	else if (port == BCR_PORT || port == BCR_PORT2)
//	{
//		OnMain_Rcv_BCR(port, ch);
//	}
//	else if (port == BCR_PORT3 || port == BCR_PORT4 || port == BCR_PORT5 || port == BCR_PORT6)
//	{
//		OnMain_Rcv_LabelPrinter(port, ch);
//	}

	/////

	return 0;
}
// ******************************************************************************

// ******************************************************************************
// RS-232C �ø��� ��Ʈ �̺�Ʈ ���� �Լ�                                          
// ******************************************************************************
LONG CMainFrame::OnCommunicationEvent(WPARAM port, LPARAM event)
{
	// **************************************************************************
    // �̺�Ʈ ������ �ø��� ��Ʈ ��Ʈ �˻��Ѵ�                                   
    // **************************************************************************
	if (port <= 0 || port > MAX_PORT)  // COMM ��Ʈ �˻�
		return -1;
	// **************************************************************************

	if (event & EV_BREAK)
		Func.MsgLog ("EV_BREAK event");
	else if (event & EV_CTS)
		Func.MsgLog ("EV_CTS event");
	else if (event & EV_DSR)
		Func.MsgLog ("EV_DSR event");
	else if (event & EV_ERR)
		Func.MsgLog ("EV_ERR event");
	else if (event & EV_RING)
		Func.MsgLog ("EV_RING event");
	else if (event & EV_RLSD)
		Func.MsgLog ("EV_RLSD event");
	else if (event & EV_RXCHAR)
		Func.MsgLog ("EV_RXCHAR event");
	else if (event & EV_RXFLAG)
		Func.MsgLog ("EV_RXFLAG event");
	else if (event & EV_TXEMPTY)
		Func.MsgLog ("EV_TXEMPTY event");

	return 0;
}
// ******************************************************************************

// ******************************************************************************
// RS-232C �ø��� ��Ʈ�� ���� �޽��� ���� �Լ�                                   
// -> wParam : �޽��� ������ ��Ʈ �ѹ�                                           
// ******************************************************************************
LRESULT CMainFrame::OnDataSend(WPARAM wParam, LPARAM lParam)
{	
	int port = wParam; 
	int pos = lParam;
	int i = 0;
	CString data, temp;
	
	switch(port)
	{
		case GMS_PORT:
		case BCR_PORT:
		case BCR_PORT2:
		case BCR_PORT3:
		case BCR_PORT4:
		case BCR_PORT5:
		case BCR_PORT6:
//			OnMain_Snd_Serial(wParam, lParam);
			break;
	}
	return 0;
}

void CMainFrame::OnMain_Snd_Serial(WPARAM wParam, LPARAM lParam)
{
//	int n_serial_chk;  // ������ �۽� �÷���
//	
//	char buf[1024];
//	
//	// **************************************************************************
//	// �۽� ������ �ӽ� ���� ���� �ʱ�ȭ                                         
//	// **************************************************************************
//	memset(&buf, 0, sizeof(buf));
//	//buf[0] = '\0';
//	// **************************************************************************
//	
//	// **************************************************************************
//	// �۽� ������ �� �������� �� ����/���� ���� ���� �����Ѵ�                 
//	// **************************************************************************
//	//(st_serial.str_snd[wParam-1]).TrimLeft(' ');
//	//(st_serial.str_snd[wParam-1]).TrimRight(' ');
//	// **************************************************************************
//	
//	// **************************************************************************
//	// �۽� ������ ������ ���� �˻��Ѵ�                                          
//	// **************************************************************************
//	if (st_serial.mstr_snd[wParam-1] == _T(""))  // �۽� ������ ���� �˻�
//	{
//		if (st_handler.cwnd_list != NULL)       // ����Ʈ �� ȭ�� ����
//		{
////			st_serial.mcomm_err[wParam-1] = _T("[�۽� ������] ���� ������ ���� ���� �߻�");
//			st_serial.mcomm_err[wParam-1] = _T("[Send Data Error] DATA Empty transfer error.");
//			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, wParam, SEND_MSG);  // ���� �޽��� ��� ��û
//		}
//		
//		st_serial.mn_snd_chk[wParam-1] = COM_ERROR;  // �۽� ���� �÷��� ����
//		return;
//	}
//	// **************************************************************************
//	
//	st_serial.mcomm_snd[wParam-1] = st_serial.mstr_snd[wParam-1];  
//	sprintf(buf, st_serial.mstr_snd[wParam-1]);  // �۽� ������ ����
//	
//	// **************************************************************************
//	// �Էµ� �۽� ������ �ø��� ��Ʈ�� ���� �����Ѵ�                            
//	// **************************************************************************
//	n_serial_chk = (m_ports[wParam-1]).MmdSerialWriteData(buf, strlen(buf), SERIAL_WAIT, SERIAL_TIME_INFINITE);
//	
//	if (n_serial_chk == 0)        // ���� �۽�
//	{
//		//if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
//		//    st_handler.cwnd_list->PostMessage(WM_LIST_DATA, wParam, 2);  // �۽� �޽��� ��� ��û
//		
//		st_serial.mn_snd_chk[wParam-1] = CTL_YES;
//	}
//	else if (n_serial_chk == -1)  // ���� ����
//	{
//		if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
//		{
////			st_serial.mcomm_err[wParam-1] = _T("[�۽� ������] �ø��� ��Ʈ ���� ���� �߻�");
//			st_serial.mcomm_err[wParam-1] = _T("[TR DATA] Serial Port write error.");
//			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, wParam, SEND_MSG);  // ���� �޽��� ��� ��û
//		}
//		
//		st_serial.mn_snd_chk[wParam-1] = -1;  
//	}
//	else if (n_serial_chk == -2)  // TIME OUT
//	{
//		if (st_handler.cwnd_list != NULL)  // ����Ʈ �� ȭ�� ����
//		{
////			st_serial.mcomm_err[wParam-1] = _T("[�۽� ������] �ø��� ��Ʈ TIME OUT �߻�");
//			st_serial.mcomm_err[wParam-1] = _T("[TR DATA] Serial port TIME OUT.");
//			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, wParam, SEND_MSG);  // ���� �޽��� ��� ��û
//		}
//		
//		st_serial.mn_snd_chk[wParam-1] = -2;
//	}
//	// **************************************************************************
}


void CMainFrame::OnMain_Rcv_GMS(WPARAM port, LPARAM ch)
{
//	CString str_check;
//	int nRet;
//	
//	if (ch == 0x03)  // ������ ������ �˻�
//	{
//		mstr_received[port-1] += (char)ch;
//		mstr_received[port-1].TrimLeft(' ');
//		mstr_received[port-1].TrimRight(' ');
//		
//		st_serial.mstr_rec[port-1] = mstr_received[port-1];
//		
////		st_msg.mstr_normal_msg = mstr_received[port-1];
//		sprintf(st_msg.c_normal_msg, mstr_received[port-1]);
//		st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
//		
//		(mstr_received[port-1]).Empty();
//		
//		nRet = Func.OnElect_CheckData(st_serial.mstr_rec[port-1]);
//		
//		if (nRet == CTLBD_RET_GOOD)
//		{
//			st_work.mn_elec_serial_work = CTL_YES;		// �������� �亯�� �Դ�.
//			st_serial.mn_rec_chk[port-1] = TRUE;
//		}
//		else if (nRet == CTLBD_RET_ERROR)			// ���̰� �ȸ¾Ƽ� ����.
//		{
//			st_work.mn_elec_serial_work = CTL_NO;		// ���������� �亯�� �Դ�.
//			st_serial.mn_rec_chk[port-1] = FALSE;
//		}
//		
//		st_serial.mcomm_rec[port-1] = st_serial.mstr_rec[port-1];  // ����Ʈ ȭ�鿡 ����� ���� ������ ����
//	}
//	else
//	{
//		mstr_received[port-1] += (char)ch;
//	}
}	

void CMainFrame::OnClose() 
{
	OnExit();
}

void CMainFrame::OnDestroy() 
{
	/* ************************************************************************** */
	/* ���� ��޸��� �˶� ȭ�� �������� �ʾҴٸ� �� ���� �۾�                     */
	/* -> mp_modal_dlg : �˶� ȭ�鿡 ���� ������ ���� ����                        */
	/* ************************************************************************** */
	if (mp_alarm_dlg)
	{
		OnAlarm_Destroy();			// �˶� ȭ�� ���� �Լ� */
		delete this;
	}
	if(mp_msg_dlg)
	{
		mp_msg_dlg->DestroyWindow();
		delete mp_msg_dlg;
		mp_msg_dlg = NULL;
		
	}
	if(mp_xmsg_dlg)
	{
		mp_xmsg_dlg->DestroyWindow();
		delete mp_xmsg_dlg;
		mp_xmsg_dlg = NULL;
	}
	/* ************************************************************************** */
	// ���̸� �߰� [2014.08.12]
	// ���� ���� ���� ����
	int i;
	for(i=0; i<15; i++)
	{
		if (m_pServer[i] != NULL)
		{
			delete m_pServer[i];
			m_pServer[i] = NULL;
		}
		
		if (m_pClient[i] != NULL)
		{
			delete m_pClient[i];
			m_pClient[i] = NULL;
		}
	}
	
	OnMain_Port_Close();			// ������ �ø��� ��Ʈ ���� �Լ�
	
	KillTimer(TMR_MAIN_REFRESH);	// Time ��� Ÿ�̸� ����
	KillTimer(TMR_FILE_CREATE);
	KillTimer(TMR_GMS_CHK);
	KillTimer(TMR_MAT_CHK);

	CFrameWnd::OnDestroy();
}

void CMainFrame::OnAlarm_Destroy()
{
	if (mp_alarm_dlg)
	{
		if (mp_alarm_dlg->IsWindowVisible())
		{
			mp_alarm_dlg->DestroyWindow();
		}
		
		if (st_handler.mn_alarm_screen != FALSE)  // �˶� ȭ�� ���
			st_handler.mn_alarm_screen = FALSE;
	}
}


void CMainFrame::OnListOper() 
{
	/* ************************************************************************** */
    /* ȭ�� �� ��ȯ �Ұ����� ���� �˻��Ѵ�.                                       */
    /* ************************************************************************** */
	int nmenu_chk = OnMenu_Change_Checking(); // �޴� ��� ���� ���� �˻� �Լ�
	if (nmenu_chk != TRUE)  return;
	
	/* ************************************************************************** */
	/* �޴� ��� �Ұ����� ��쿡 ���� ���� �˻��Ѵ�                               */
	/* -> ����Ʈ ��� �Ǵ� ƼĪ ��尡 �����Ǿ� �ִ��� �˻�                       */
	/* ************************************************************************** */
	//	if (st_ICT.n_level_teach !=  TRUE)
	//	{
	//		if (st_ICT.n_level_maint !=  TRUE)  return;
	//	}
	/* ************************************************************************** */
	
	if(GetActiveView()->IsKindOf(RUNTIME_CLASS(CScreen_List_Operation)))   return;
	OnSwitchToForm(IDW_SCREEN_LIST_OPERATION);
}

void CMainFrame::OnListDataview() 
{
	/* ************************************************************************** */
    /* ȭ�� �� ��ȯ �Ұ����� ���� �˻��Ѵ�.                                       */
    /* ************************************************************************** */
	int nmenu_chk = OnMenu_Change_Checking(); // �޴� ��� ���� ���� �˻� �Լ�
	if (nmenu_chk != TRUE)  return;
	
	/* ************************************************************************** */
	/* �޴� ��� �Ұ����� ��쿡 ���� ���� �˻��Ѵ�                               */
	/* -> ����Ʈ ��� �Ǵ� ƼĪ ��尡 �����Ǿ� �ִ��� �˻�                       */
	/* ************************************************************************** */
	//	if (st_ICT.n_level_teach !=  TRUE)
	//	{
	//		if (st_ICT.n_level_maint !=  TRUE)  return;
	//	}
	/* ************************************************************************** */
	
	if(GetActiveView()->IsKindOf(RUNTIME_CLASS(CScreen_List_Data_View)))   return;
	OnSwitchToForm(IDW_SCREEN_LIST_DATA_VIEW);
}

void CMainFrame::OnFileEditor() 
{
	// **************************************************************************
    // ȭ�� �� ��ȯ �Ұ����� ���� �˻��Ѵ�.                                      
    // **************************************************************************
	int nmenu_chk = OnMenu_Change_Checking(); // �޴� ��� ���� ���� �˻� �Լ�
	if (nmenu_chk != TRUE)  return;
	
	// **************************************************************************
	// �޴� ��� �Ұ����� ��쿡 ���� ���� �˻��Ѵ�                              
	// -> ����Ʈ ��� �Ǵ� ƼĪ ��尡 �����Ǿ� �ִ��� �˻�                      
	// **************************************************************************
	if (st_handler.mn_level_teach !=  TRUE)
	{
		if (st_handler.mn_level_maint !=  TRUE) 
		{
			OnLevel();
			if (st_handler.mn_level_teach !=  TRUE)
			{
				if (st_handler.mn_level_maint !=  TRUE)  return;
			}
		}
	}
	// **************************************************************************
	
	if (GetActiveView()->IsKindOf(RUNTIME_CLASS(CScreen_File_Editor)))   return;
	OnSwitchToForm(IDW_SCREEN_FILE_EDITOR);	
}

void CMainFrame::OnEcserver()
{
	// **************************************************************************
    // ȭ�� �� ��ȯ �Ұ����� ���� �˻��Ѵ�.                                      
    // **************************************************************************
	int nmenu_chk = OnMenu_Change_Checking(); // �޴� ��� ���� ���� �˻� �Լ�
	if (nmenu_chk != TRUE)  return;
	
	// **************************************************************************
	// �޴� ��� �Ұ����� ��쿡 ���� ���� �˻��Ѵ�                              
	// -> ����Ʈ ��� �Ǵ� ƼĪ ��尡 �����Ǿ� �ִ��� �˻�                      
	// **************************************************************************
	if (st_handler.mn_level_teach !=  TRUE)
	{
		if (st_handler.mn_level_maint !=  TRUE) 
		{
			OnLevel();
			if (st_handler.mn_level_teach !=  TRUE)
			{
				if (st_handler.mn_level_maint !=  TRUE)  return;
			}
		}
	}
	// **************************************************************************
	
	if (GetActiveView()->IsKindOf(RUNTIME_CLASS(CScreen_Server_Network)))   return;
	OnSwitchToForm(IDW_SCREEN_ECSERVER);	
}


/////////20131115
void CMainFrame::OnMain_Rcv_BCR(WPARAM port, LPARAM ch)
{
//	CString str_check;
//	int nRet;
//	
//	if (ch == 0x03)  // ������ ������ �˻�
//	{
//		//mstr_received[port-1] += (char)ch;
//		mstr_received[port-1].TrimLeft(' ');
//		mstr_received[port-1].TrimRight(' ');
//		
//		st_serial.mstr_rec[port-1] = mstr_received[port-1];
//		
//		sprintf(st_msg.c_normal_msg, mstr_received[port-1]);
//		st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
//		
//		(mstr_received[port-1]).Empty();
//		
//		nRet = Func.OnBCR_CheckData(st_serial.mstr_rec[port-1]);
//		
//		if (nRet == CTLBD_RET_GOOD)
//		{
//			st_work.n_barcode_recive = CTL_YES;		// �������� �亯�� �Դ�.
//			st_serial.mn_rec_chk[port-1] = TRUE;
//		}
//		else if (nRet == CTLBD_RET_ERROR)					// ���̰� �ȸ¾Ƽ� ����.
//		{
//			st_work.strBarcodeRecive = "NoRead";
//			st_work.n_barcode_recive = CTL_NO;		// ���������� �亯�� �Դ�.
//			st_serial.mn_rec_chk[port-1] = FALSE;
//		}
//		
//		st_serial.mcomm_rec[port-1] = st_serial.mstr_rec[port-1];  // ����Ʈ ȭ�鿡 ����� ���� ������ ����
//	}
//	else
//	{
//		mstr_received[port-1] += (char)ch;
//	}
//	
}


void CMainFrame::OnMain_Rcv_LabelPrinter(WPARAM port, LPARAM ch)
{
	CString str_check;
	int nRet;
	
	if (ch == 0x03)   // ������ ������ �˻� [ETX]
	{
		mstr_received[port-1] += (char)ch;
		mstr_received[port-1].TrimLeft(' ');
		mstr_received[port-1].TrimRight(' ');
		
		st_serial.mstr_rec[port-1] = mstr_received[port-1];

		sprintf(st_msg.c_normal_msg, mstr_received[port-1]);
		st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
		
		(mstr_received[port-1]).Empty();
		
		nRet = Func.OnLabel_CheckData(st_serial.mstr_rec[port-1], port-1);
		
		if (nRet == CTLBD_RET_GOOD)
		{
			st_work.n_label_recive[port-1] = CTL_YES;		// �������� �亯�� �Դ�.
			st_serial.mn_rec_chk[port-1] = TRUE;
		}
		else if (nRet == CTLBD_RET_ERROR)
		{
			st_work.n_label_recive[port-1] = CTL_NO;		// ���������� �亯�� �Դ�.
			st_serial.mn_rec_chk[port-1] = FALSE;
		}
	}
	//////////////////////////////////////////////////////// 20120707
	else if(ch == 0x5d)   // "]"
	{
		/////////////// 20120906
		mstr_received[port-1] += (char)ch;
		st_serial.mstr_rec[port-1] = mstr_received[port-1];
		
		str_check.Empty();
		AfxExtractSubString(str_check, mstr_received[port-1], 3, ' ');//st_serial.comm_rec[port], 2, ' ');
		str_check.TrimLeft(' ');
		str_check.TrimLeft(' ');
		mstr_received[port-1].Empty();
		
		if (str_check == "COMPLETED")
		{
			sprintf(st_msg.c_normal_msg, mstr_received[port-1]);
			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0 , NORMAL_MSG);
			st_serial.mn_rec_chk[port-1] = TRUE;
			st_barcode.b_print_complete[port-1] = TRUE;
		}
		else
		{
			st_serial.mn_rec_chk[port-1] = FALSE;
			st_barcode.b_print_complete[port-1] = FALSE;
		}
	}
	else
	{
		mstr_received[port] += (char)ch;
	}
}



int CMainFrame::OnBarcode_SetValue_Change()
{
	int nFunRet = CTLBD_RET_PROCEED;

	CString strBcrCommand;

	switch ( mn_BarcodeSetValueChangeStep )
	{
	case 0:
		strBcrCommand.Format("%csMN SetAccessMode 3 7A99FDC6%c", 0x02, 0x03);
		st_serial.mstr_snd[BCR_PORT-1] = strBcrCommand;
		::PostMessage(st_handler.hWnd, WM_DATA_SEND, BCR_PORT, 0);

		mn_BarcodeSetValueChangeStep = 10;
		break;

	case 10:
		if ( st_work.str_barcode_success == "SAN SETACCESSMODE 1" )
		{
			mn_BarcodeSetValueChangeStep = 100;
		}
		else
		{
			st_msg.str_fallacy_msg = _T("BCR ������ �����Ͽ����ϴ�. �ٽ� �ϼ���.");
			::PostMessage(st_handler.hWnd, WM_MAINFRAME_WORK, 1000, 0);

			mn_BarcodeSetValueChangeStep = 0;
			return CTLBD_RET_GOOD;
		}
		break;

	case 100:	// �Ÿ�
		strBcrCommand.Format("%csWN CAMFocPos %X%c", 0x02, st_basic.n_distance, 0x03);
		st_serial.mstr_snd[BCR_PORT-1] = strBcrCommand;
		::PostMessage(st_handler.hWnd, WM_DATA_SEND, BCR_PORT, 0);

		mn_BarcodeSetValueChangeStep = 110;
		break;

	case 110:
		if ( st_work.str_barcode_success == "SWA CAMFOCPOS" )
		{
			mn_BarcodeSetValueChangeStep = 200;
		}
		else
		{
			st_msg.str_fallacy_msg = _T("BCR ������ �����Ͽ����ϴ�. �ٽ� �ϼ���.");
			::PostMessage(st_handler.hWnd, WM_MAINFRAME_WORK, 1000, 0);

			mn_BarcodeSetValueChangeStep = 0;
			return CTLBD_RET_GOOD;
		}
		break;
	
	case 200:	// ���� �ӵ�
		strBcrCommand.Format("%csWN CAMShutterTime %X%c", 0x02, st_basic.n_shutter_time, 0x03);
		st_serial.mstr_snd[BCR_PORT-1] = strBcrCommand;
		::PostMessage(st_handler.hWnd, WM_DATA_SEND, BCR_PORT, 0);
		
		mn_BarcodeSetValueChangeStep = 210;
		break;
		
	case 210:
		if ( st_work.str_barcode_success == "SWA CAMSHUTTERTIME" )
		{
			mn_BarcodeSetValueChangeStep = 300;
		}
		else
		{
			st_msg.str_fallacy_msg = _T("BCR ������ �����Ͽ����ϴ�. �ٽ� �ϼ���.");
			::PostMessage(st_handler.hWnd, WM_MAINFRAME_WORK, 1000, 0);
			
			mn_BarcodeSetValueChangeStep = 0;
			return CTLBD_RET_GOOD;
		}
		break;
		
	case 300:	// ����
// 		strBcrCommand.Format("%csWN CAMBrightness %X%c", 0x02, st_basic.n_brightness, 0x03);
// 		st_serial.mstr_snd[BCR_PORT-1] = strBcrCommand;
// 		::PostMessage(st_handler.hWnd, WM_DATA_SEND, BCR_PORT, 0);
// 		
		mn_BarcodeSetValueChangeStep = 310;
		break;
		
	case 310:
// 		if ( st_work.str_barcode_success == "SWA CAMBRIGHTNESS" )
// 		{
			mn_BarcodeSetValueChangeStep = 400;
// 		}
// 		else
// 		{
// 			st_msg.str_fallacy_msg = _T("BCR ������ �����Ͽ����ϴ�. �ٽ� �ϼ���.");
// 			::PostMessage(st_handler.hWnd, WM_MAINFRAME_WORK, 1000, 0);
// 			
// 			mn_BarcodeSetValueChangeStep = 0;
// 			return CTLBD_RET_GOOD;
// 		}
		break;

	case 400:	// ���
		strBcrCommand.Format("%csWN CAMContrast %X%c", 0x02, st_basic.n_contrast, 0x03);
		st_serial.mstr_snd[BCR_PORT-1] = strBcrCommand;
		::PostMessage(st_handler.hWnd, WM_DATA_SEND, BCR_PORT, 0);

		mn_BarcodeSetValueChangeStep = 410;
		break;
		
	case 410:
		if ( st_work.str_barcode_success == "SWA CAMCONTRAST" )
		{
			mn_BarcodeSetValueChangeStep = 500;
		}
		else
		{
			st_msg.str_fallacy_msg = _T("BCR ������ �����Ͽ����ϴ�. �ٽ� �ϼ���.");
			::PostMessage(st_handler.hWnd, WM_MAINFRAME_WORK, 1000, 0);

			mn_BarcodeSetValueChangeStep = 0;
			return CTLBD_RET_GOOD;
		}
		break;	

	case 500:	// ���ڵ� ����
		strBcrCommand.Format("%csWN D1DDMinModSize %X%c", 0x02, OnMain_writeFloat(st_basic.d_1d_width), 0x03);// 20130611 kjh
		st_serial.mstr_snd[BCR_PORT-1] = strBcrCommand;
		::PostMessage(st_handler.hWnd, WM_DATA_SEND, BCR_PORT, 0);
		
		mn_BarcodeSetValueChangeStep = 510;
		break;

	case 510:
		if ( st_work.str_barcode_success == "SWA D1DDMINMODSIZE" )
		{
			mn_BarcodeSetValueChangeStep = 900;
		}
		else
		{
			st_msg.str_fallacy_msg = _T("BCR ������ �����Ͽ����ϴ�. �ٽ� �ϼ���.");
			::PostMessage(st_handler.hWnd, WM_MAINFRAME_WORK, 1000, 0);
			
			mn_BarcodeSetValueChangeStep = 0;
			return CTLBD_RET_GOOD;
		}
		break;

	case 900:	// ����
		strBcrCommand.Format("%csMN mEEwriteall%c", 0x02, 0x03);
		st_serial.mstr_snd[BCR_PORT-1] = strBcrCommand;
		::PostMessage(st_handler.hWnd, WM_DATA_SEND, BCR_PORT, 0);
		
		mn_BarcodeSetValueChangeStep = 910;
		break;
		
	case 910:
		if ( st_work.str_barcode_success == "SAN MEEWRITEALL 1" )
		{
			mn_BarcodeSetValueChangeStep = 1000;
		}
		else
		{
			st_msg.str_fallacy_msg = _T("BCR ������ �����Ͽ����ϴ�. �ٽ� �ϼ���.");
			::PostMessage(st_handler.hWnd, WM_MAINFRAME_WORK, 1000, 0);

			mn_BarcodeSetValueChangeStep = 0;
			return CTLBD_RET_GOOD;
		}
		break;
		
	case 1000:	// Run Mode
		strBcrCommand.Format("%csMN Run%c", 0x02, 0x03);
		st_serial.mstr_snd[BCR_PORT-1] = strBcrCommand;
		::PostMessage(st_handler.hWnd, WM_DATA_SEND, BCR_PORT, 0);
		
		mn_BarcodeSetValueChangeStep = 1010;
		break;
		
	case 1010:
		if ( st_work.str_barcode_success == "SAN RUN 1" )
		{
			mn_BarcodeSetValueChangeStep = 1100;
		}
		else
		{
			st_msg.str_fallacy_msg = _T("BCR ������ �����Ͽ����ϴ�. �ٽ� �ϼ���.");
			::PostMessage(st_handler.hWnd, WM_MAINFRAME_WORK, 1000, 0);

			mn_BarcodeSetValueChangeStep = 0;
			return CTLBD_RET_GOOD;
		}
		break;
		
	case 1100:
//		sprintf(st_msg.c_normal_msg, "���ڵ� ���� �Ϸ�.");
		st_msg.mstr_barcode = "BCR Setting completed.";
// 		st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
		Func.On_LogFile_Add(LOG_TOTAL, st_msg.mstr_barcode);

		nFunRet = CTLBD_RET_GOOD;
		mn_BarcodeSetValueChangeStep = 0;
		break;
	}

	return nFunRet;
}

int CMainFrame::OnMain_writeFloat(float f)
{ 
	UINT32 u;
	int sign; 
	int exponent; 
	int significand; 
	
	// Extract bits  
	u = *(UINT32*)&f; 
	
	// Extract sign 
	sign = (u & 0x80000000) >> 31;     //  1 bit 
	
	// Extract exponent 
	exponent = (u & 0x7F800000) >> 23; //  8 bit 
	exponent -= 127;                   // exponent bias 
	
	// Extract significand 
	significand = (u & 0x007FFFFF);    // 23 bit 
	significand |= 0x00800000;         // implicit leading bit with value 1 
	
	return u;
}
//////////

/////////////////////////////////////////////////////////////////////////////////////
// ���� ���� Ŭ����
// ���̸� �߰� [2013.11.12]
/////////////////////////////////////////////////////////////////////////////////////

//==================================================================//
// [EQP<->MES] ��� ���
//==================================================================//
LRESULT CMainFrame::OnCommand_Client_1(WPARAM wParam, LPARAM lParam)
{
	CString sSnd, sRcv, sTmp;

	int nStatus	= (int)wParam;
	int nAddr	= (int)lParam;

	switch(nStatus)
	{
	case CLIENT_CONNECT:
		// DISCONNECT �ÿ� ���� �۾� �õ�
		if (st_client[nAddr].n_connect == CTL_NO)
		{
			m_pClient[nAddr] = new CClientSocket;  // ���� ����

			// - Create(int n_address, CString str_ip, int n_port, int n_timeout);
			if (m_pClient[nAddr]->Create(nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port))//, 1000))
			{
				st_client[nAddr].n_connect = CTL_YES;
				sTmp.Format("Client_[%02d] Connect Success.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);

				if (st_handler.cwnd_list != NULL)
				{
					//sprintf( st_msg.mstr_barcode, "%s", sTmp);
					st_msg.mstr_barcode.Format("%s", sTmp); 
					//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					Func.On_LogFile_Add(LOG_TOTAL, st_msg.mstr_barcode);
				}
				m_sLogMsg = sTmp;
				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			else
			{
				// ������ ���� �ν��Ͻ� ����
				delete m_pClient[nAddr];
				m_pClient[nAddr] = NULL;

				st_client[nAddr].n_connect = CTL_NO;
				sTmp.Format("Client_[%02d] Connect Fail.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);

				if (st_handler.cwnd_list != NULL)
				{
					//sprintf( st_msg.mstr_barcode, "%s", sTmp);
					//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
					st_msg.mstr_barcode.Format("%s", sTmp); 
					Func.On_LogFile_Add(LOG_TOTAL, st_msg.mstr_barcode);
				}
				m_sLogMsg = sTmp;
				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
		}
		break;

	case CLIENT_CLOSE:
		// ������ �����Ŵ
		if (st_client[nAddr].n_connect == CTL_YES)
		{
			delete m_pClient[nAddr];
			m_pClient[nAddr] = NULL;

			st_client[nAddr].n_connect = CTL_NO;
			sTmp.Format("Client_[%02d] Close.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);

			if (st_handler.cwnd_list != NULL)
			{
				//sprintf( st_msg.mstr_barcode, "%s", sTmp);
				//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
				st_msg.mstr_barcode.Format("%s", sTmp); 
				Func.On_LogFile_Add(LOG_TOTAL, st_msg.mstr_barcode);
			}
			m_sLogMsg = sTmp;
			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
		}
		break;

	case CLIENT_SEND:
		sSnd.Format("%s", st_client[nAddr].ch_send);

		if (st_client[nAddr].n_connect == CTL_YES)
		{
			m_pClient[nAddr]->Send(sSnd, sSnd.GetLength(), 0);
			sTmp.Format("Client_[%02d] Data Send    - %s", nAddr, sSnd);

			// ���̸� �ּ� ó�� [2012.10.04]
			/*
			if (st_handler.cwnd_list != NULL)
			{
				sprintf(st_other.str_op_msg, sTmp);
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
			}
			*/
			m_sLogMsg = sTmp;
			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			Func.On_LogFile_Add(99, m_sLogMsg);
			Func.On_LogFile_Add(LOG_TCPIP, m_sLogMsg);
// 			if (st_handler.cwnd_list != NULL)
// 			{
// 				sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 			}
		}
		else
		{
			m_sLogMsg.Format("Client_[%02d] Not ConnectData Send - %s", nAddr, sSnd);
			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			Func.On_LogFile_Add(99, m_sLogMsg);
		}
		break;

	case CLIENT_REV:
		// ���ŵ� �����͸� ���̸�ŭ �޾Ƶ���
		sTmp.Format("%s", st_client[nAddr].ch_rev);
		sRcv = sTmp.Mid(0, st_client[nAddr].n_rev_length);

		m_sLogMsg.Format("Client_[%02d] Data Receive - %s", nAddr, sRcv);
		cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);

// 		clsBcrFormatClient.OnDataReceive(sTmp);	// [MES->EQP] ��o��A��E ������AAo ��������CI���� A������

		//2014,1229
		evMes.OnDivide_FromMES(nAddr, sRcv);	// [MES->EQP] ���ŵ� �޽��� �����Ͽ� ó��

		Func.On_LogFile_Add(99, m_sLogMsg);
		Func.On_LogFile_Add(LOG_TCPIP, m_sLogMsg);
// 		if (st_handler.cwnd_list != NULL)
// 		{
// 			sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 		}
		break;

		// ���̸� �߰� [2014.08.13]
	case CLIENT_RECONNECT:
		// DISCONNECT �ÿ� ���� �۾� �õ�
		if (st_client[nAddr].n_connect == CTL_NO)
		{
			SetTimer(TMR_MES_, 5000, NULL);
		}
		break;
	}
	return 0;
}

//==================================================================//
// [EQP<->CIM] ��� ���
//==================================================================//
LRESULT CMainFrame::OnCommand_Client_2(WPARAM wParam, LPARAM lParam)
{
	CString sSnd, sRcv, sTmp, sHead;

	int nStatus	= (int)wParam;
	int nAddr	= (int)lParam;

	switch(nStatus)
	{
	case CLIENT_CONNECT:
		// DISCONNECT �ÿ� ���� �۾� �õ�
		if (st_client[nAddr].n_connect == CTL_NO)
		{
			m_pClient[nAddr] = new CClientSocket;  // ���� ����
			
			// �ý��� ���� �������� ���� �õ�
			// - ���� ��巹�� ���ÿ��� ("127.0.0.1")
			//if (m_pClient[nAddr]->Create(nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port, 1000))
			// ���̸� ���� [2013.11.23]
			if (m_pClient[nAddr]->Create(nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port))//, 1000))
			{
				st_client[nAddr].n_connect = CTL_YES;
				sTmp.Format("Client_[%02d] Connect Success.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);

				if (st_handler.cwnd_list != NULL)
				{
					//sprintf( st_msg.mstr_barcode, "%s", sTmp);
					//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					st_msg.mstr_barcode.Format("%s", sTmp); 
					Func.On_LogFile_Add(LOG_TOTAL, st_msg.mstr_barcode);
				}
				m_sLogMsg = sTmp;
				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			else
			{
				// ������ ���� �ν��Ͻ� ����
				delete m_pClient[nAddr];
				m_pClient[nAddr] = NULL;

				st_client[nAddr].n_connect = CTL_NO;
				sTmp.Format("Client_[%02d] Connect Fail.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);

				if (st_handler.cwnd_list != NULL)
				{
					//sprintf( st_msg.mstr_barcode, "%s", sTmp);
					//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
					st_msg.mstr_barcode.Format("%s", sTmp); 
					Func.On_LogFile_Add(LOG_TOTAL, st_msg.mstr_barcode);
				}
				m_sLogMsg = sTmp;
				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
		}
		break;

	case CLIENT_CLOSE:
		// ������ �����Ŵ
		if (st_client[nAddr].n_connect == CTL_YES)
		{
			delete m_pClient[nAddr];
			m_pClient[nAddr] = NULL;
			
			st_client[nAddr].n_connect = CTL_NO;
			sTmp.Format("Client_[%02d] Close.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);

			if (st_handler.cwnd_list != NULL)
			{
				//sprintf( st_msg.mstr_barcode, "%s", sTmp);
				//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
				st_msg.mstr_barcode.Format("%s", sTmp); 
				Func.On_LogFile_Add(LOG_TOTAL, st_msg.mstr_barcode);
			}
			m_sLogMsg = sTmp;
			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
		}
		SetTimer(TMR_SMEMA_CLIENT1, 5000, 0);
		break;
		
	case CLIENT_SEND:
		sSnd.Format("%s", st_client[nAddr].ch_send);

		if (st_client[nAddr].n_connect == CTL_YES)
		{
			m_pClient[nAddr]->Send(sSnd, sSnd.GetLength(), 0);
			sTmp.Format("Client_[%02d] Data Send    - %s", nAddr, sSnd);

			// ���̸� �ּ� ó�� [2012.10.04]
			/*
			if (st_handler.cwnd_list != NULL)
			{
				sprintf(st_other.str_op_msg, sTmp);
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
			}
			*/
			m_sLogMsg = sTmp;
			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			Func.On_LogFile_Add(99, m_sLogMsg);
			Func.On_LogFile_Add(LOG_MACHINE, m_sLogMsg);
// 			if (st_handler.cwnd_list != NULL)
// 			{
// 				sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 			}
		}
		else
		{
			m_sLogMsg.Format("Client_[%02d] Not ConnectData Send - %s", nAddr, sSnd);
			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			Func.On_LogFile_Add(99, m_sLogMsg);
		}
		break;
		
	case CLIENT_REV:
		// ���ŵ� �����͸� ���̸�ŭ �޾Ƶ���
		sTmp.Format("%s", st_client[nAddr].ch_rev);
		sRcv = sTmp.Mid(0, st_client[nAddr].n_rev_length);
		
		m_sLogMsg.Format("Client_[%02d] Data Receive - %s", nAddr, sRcv);
		cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);

		g_btm_client.OnDataReceive(sRcv);
		Func.On_LogFile_Add(LOG_MACHINE, m_sLogMsg);
		Func.On_LogFile_Add(99, m_sLogMsg);
// 		if (st_handler.cwnd_list != NULL)
// 		{
// 			sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 		}
		break;

		// ���̸� �߰� [2014.08.13]
	case CLIENT_RECONNECT:
		// DISCONNECT �ÿ� ���� �۾� �õ�
		if (st_client[nAddr].n_connect == CTL_NO)
		{
//			SetTimer(TMR_CIM_, 5000, NULL);
		}
		break;
	}
	return 0;
}

LRESULT CMainFrame::OnCommand_Client_3(WPARAM wParam, LPARAM lParam)
{
	CString sSnd, sRcv, sTmp, sHead;

	int nStatus	= (int)wParam;
	int nAddr	= (int)lParam;

	switch(nStatus)
	{
	case CLIENT_CONNECT:
		// DISCONNECT �ÿ� ���� �۾� �õ�
		if (st_client[nAddr].n_connect == CTL_NO)
		{
			m_pClient[nAddr] = new CClientSocket;  // ���� ����
			
			// �ý��� ���� �������� ���� �õ�
			// - ���� ��巹�� ���ÿ��� ("127.0.0.1")
			//if (m_pClient[nAddr]->Create(nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port, 1000))
			// ���̸� ���� [2013.11.23]
			if (m_pClient[nAddr]->Create(nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port))//, 1000))
			{
				st_client[nAddr].n_connect = CTL_YES;
				sTmp.Format("Client_[%02d] Connect Success.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);

				if (st_handler.cwnd_list != NULL)
				{
					//sprintf( st_msg.mstr_barcode, "%s", sTmp);
					//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					st_msg.mstr_barcode.Format("%s", sTmp); 
					Func.On_LogFile_Add(LOG_TOTAL, st_msg.mstr_barcode);
				}
				m_sLogMsg = sTmp;
				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			else
			{
				// ������ ���� �ν��Ͻ� ����
				delete m_pClient[nAddr];
				m_pClient[nAddr] = NULL;

				st_client[nAddr].n_connect = CTL_NO;
				sTmp.Format("Client_[%02d] Connect Fail.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);

				if (st_handler.cwnd_list != NULL)
				{
// 					sprintf( st_msg.mstr_barcode, "%s", sTmp);
					//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
					st_msg.mstr_barcode.Format("%s", sTmp); 
					Func.On_LogFile_Add(LOG_TOTAL, st_msg.mstr_barcode);
				}
				m_sLogMsg = sTmp;
				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
		}
		break;

	case CLIENT_CLOSE:
		// ������ �����Ŵ
		if (st_client[nAddr].n_connect == CTL_YES)
		{
			delete m_pClient[nAddr];
			m_pClient[nAddr] = NULL;
			
			st_client[nAddr].n_connect = CTL_NO;
			sTmp.Format("Client_[%02d] Close.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);

			if (st_handler.cwnd_list != NULL)
			{
				//sprintf( st_msg.mstr_barcode, "%s", sTmp);
				//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
				st_msg.mstr_barcode.Format("%s", sTmp); 
				Func.On_LogFile_Add(LOG_TOTAL, st_msg.mstr_barcode);
			}
			m_sLogMsg = sTmp;
			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
		}
		SetTimer(TMR_SMEMA_CLIENT1, 5000, 0);
		break;
		
	case CLIENT_SEND:
		sSnd.Format("%s", st_client[nAddr].ch_send);

		if (st_client[nAddr].n_connect == CTL_YES)
		{
			m_pClient[nAddr]->Send(sSnd, sSnd.GetLength(), 0);
			sTmp.Format("Client_[%02d] Data Send    - %s", nAddr, sSnd);

			// ���̸� �ּ� ó�� [2012.10.04]
			/*
			if (st_handler.cwnd_list != NULL)
			{
				sprintf(st_other.str_op_msg, sTmp);
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
			}
			*/
			m_sLogMsg = sTmp;
			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			Func.On_LogFile_Add(99, m_sLogMsg);
			Func.On_LogFile_Add(LOG_MACHINE, m_sLogMsg);
// 			if (st_handler.cwnd_list != NULL)
// 			{
// 				sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 			}
		}
		else
		{
			m_sLogMsg.Format("Client_[%02d] Not ConnectData Send - %s", nAddr, sSnd);
			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			Func.On_LogFile_Add(99, m_sLogMsg);
			if (st_handler.cwnd_list != NULL)
			{
				//sprintf( st_msg.mstr_barcode, "%s", m_sLogMsg);
				//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
				st_msg.mstr_barcode.Format("%s", sTmp); 
				Func.On_LogFile_Add(LOG_TOTAL, st_msg.mstr_barcode);
			}
		}
		break;
		
	case CLIENT_REV:
		// ���ŵ� �����͸� ���̸�ŭ �޾Ƶ���
		sTmp.Format("%s", st_client[nAddr].ch_rev);
		sRcv = sTmp.Mid(0, st_client[nAddr].n_rev_length);
		
		m_sLogMsg.Format("Client_[%02d] Data Receive - %s", nAddr, sRcv);
		//cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);

		g_8570_client.OnDataReceive(sRcv);
		Func.On_LogFile_Add(LOG_MACHINE, m_sLogMsg);
		Func.On_LogFile_Add(99, m_sLogMsg);
// 		if (st_handler.cwnd_list != NULL)
// 		{
// 			sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 		}
		break;

		// ���̸� �߰� [2014.08.13]
	case CLIENT_RECONNECT:
		// DISCONNECT �ÿ� ���� �۾� �õ�
		if (st_client[nAddr].n_connect == CTL_NO)
		{
			SetTimer(TMR_CIM_, 5000, NULL);
		}
		break;
	}
	return 0;
}

LRESULT CMainFrame::OnCommand_Client_4(WPARAM wParam, LPARAM lParam)
{
	CString sSnd, sRcv, sTmp, sHead;

	int nStatus	= (int)wParam;
	int nAddr	= (int)lParam;

	switch(nStatus)
	{
	case CLIENT_CONNECT:
		// DISCONNECT �ÿ� ���� �۾� �õ�
		if (st_client[nAddr].n_connect == CTL_NO)
		{
			m_pClient[nAddr] = new CClientSocket;  // ���� ����
			
			// �ý��� ���� �������� ���� �õ�
			// - ���� ��巹�� ���ÿ��� ("127.0.0.1")
			//if (m_pClient[nAddr]->Create(nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port, 1000))
			// ���̸� ���� [2013.11.23]
			if (m_pClient[nAddr]->Create(nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port))//, 1000))
			{
				st_client[nAddr].n_connect = CTL_YES;
				sTmp.Format("Client_[%02d] Connect Success.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);

				if (st_handler.cwnd_list != NULL)
				{
					//sprintf( st_msg.mstr_barcode, "%s", sTmp);
					//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					st_msg.mstr_barcode.Format("%s", sTmp); 
					Func.On_LogFile_Add(LOG_TOTAL, st_msg.mstr_barcode);
				}
				m_sLogMsg = sTmp;
				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			else
			{
				// ������ ���� �ν��Ͻ� ����
				delete m_pClient[nAddr];
				m_pClient[nAddr] = NULL;

				st_client[nAddr].n_connect = CTL_NO;
				sTmp.Format("Client_[%02d] Connect Fail.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);

				if (st_handler.cwnd_list != NULL)
				{
					//sprintf( st_msg.mstr_barcode, "%s", sTmp);
					//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
					st_msg.mstr_barcode.Format("%s", sTmp); 
					Func.On_LogFile_Add(LOG_TOTAL, st_msg.mstr_barcode);
				}
				m_sLogMsg = sTmp;
				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
		}
		break;

	case CLIENT_CLOSE:
		// ������ �����Ŵ
		if (st_client[nAddr].n_connect == CTL_YES)
		{
			delete m_pClient[nAddr];
			m_pClient[nAddr] = NULL;
			
			st_client[nAddr].n_connect = CTL_NO;
			sTmp.Format("Client_[%02d] Close.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);

			if (st_handler.cwnd_list != NULL)
			{
				//sprintf( st_msg.mstr_barcode, "%s", sTmp);
				//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
				st_msg.mstr_barcode.Format("%s", sTmp); 
				Func.On_LogFile_Add(LOG_TOTAL, st_msg.mstr_barcode);
			}
			m_sLogMsg = sTmp;
			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
		}
		break;
		
	case CLIENT_SEND:
		sSnd.Format("%s", st_client[nAddr].ch_send);

		if (st_client[nAddr].n_connect == CTL_YES)
		{
			m_pClient[nAddr]->Send(sSnd, sSnd.GetLength(), 0);
			sTmp.Format("Client_[%02d] Data Send    - %s", nAddr, sSnd);

			// ���̸� �ּ� ó�� [2012.10.04]
			/*
			if (st_handler.cwnd_list != NULL)
			{
				sprintf(st_other.str_op_msg, sTmp);
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
			}
			*/
			m_sLogMsg = sTmp;
			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			Func.On_LogFile_Add(LOG_MACHINE, m_sLogMsg);
			Func.On_LogFile_Add(99, m_sLogMsg);
// 			if (st_handler.cwnd_list != NULL)
// 			{
// 				sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 			}
		}
		else
		{
			m_sLogMsg.Format("Client_[%02d] Not ConnectData Send - %s", nAddr, sSnd);
			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			Func.On_LogFile_Add(99, m_sLogMsg);
// 			if (st_handler.cwnd_list != NULL)
// 			{
// 				sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 			}
		}
		break;
		
	case CLIENT_REV:
		// ���ŵ� �����͸� ���̸�ŭ �޾Ƶ���
		sTmp.Format("%s", st_client[nAddr].ch_rev);
		sRcv = sTmp.Mid(0, st_client[nAddr].n_rev_length);
		
		m_sLogMsg.Format("Client_[%02d] Data Receive - %s", nAddr, sRcv);
		cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);

//		g_client_cim.OnDivide_FromCIM(nAddr, sRcv);	// [MES->CIM] ���ŵ� �޽��� �����Ͽ� ó��
		g_next_client.OnDataReceive(sRcv);
		Func.On_LogFile_Add(LOG_MACHINE, m_sLogMsg);
		Func.On_LogFile_Add(99, m_sLogMsg);
// 		if (st_handler.cwnd_list != NULL)
// 		{
// 			sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 		}
		break;

		// ���̸� �߰� [2014.08.13]
	case CLIENT_RECONNECT:
		// DISCONNECT �ÿ� ���� �۾� �õ�
		if (st_client[nAddr].n_connect == CTL_NO)
		{
			SetTimer(TMR_CIM_, 5000, NULL);
		}
		break;
	}
	return 0;
}

LRESULT CMainFrame::OnCommand_Client_5(WPARAM wParam, LPARAM lParam)
{
	CString sSnd, sRcv, sTmp, sHead;

	int nStatus	= (int)wParam;
	int nAddr	= (int)lParam;

	switch(nStatus)
	{
	case CLIENT_CONNECT:
		// DISCONNECT �ÿ� ���� �۾� �õ�
		if (st_client[nAddr].n_connect == CTL_NO)
		{
			m_pClient[nAddr] = new CClientSocket;  // ���� ����
			
			// �ý��� ���� �������� ���� �õ�
			// - ���� ��巹�� ���ÿ��� ("127.0.0.1")
			//if (m_pClient[nAddr]->Create(nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port, 1000))
			// ���̸� ���� [2013.11.23]
			if (m_pClient[nAddr]->Create(nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port))//, 1000))
			{
				st_client[nAddr].n_connect = CTL_YES;
				sTmp.Format("Client_[%02d] Connect Success.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);

				if (st_handler.cwnd_list != NULL)
				{
					//sprintf( st_msg.mstr_barcode, "%s", sTmp);
					//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					st_msg.mstr_barcode.Format("%s", sTmp); 
					Func.On_LogFile_Add(LOG_TOTAL, st_msg.mstr_barcode);
				}
				m_sLogMsg = sTmp;
				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			else
			{
				// ������ ���� �ν��Ͻ� ����
				delete m_pClient[nAddr];
				m_pClient[nAddr] = NULL;

				st_client[nAddr].n_connect = CTL_NO;
				sTmp.Format("Client_[%02d] Connect Fail.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);

				if (st_handler.cwnd_list != NULL)
				{
					//sprintf( st_msg.mstr_barcode, "%s", sTmp);
					//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
					st_msg.mstr_barcode.Format("%s", sTmp); 

					Func.On_LogFile_Add(LOG_TOTAL, st_msg.mstr_barcode);
				}
				m_sLogMsg = sTmp;
				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
		}
		break;

	case CLIENT_CLOSE:
		// ������ �����Ŵ
		if (st_client[nAddr].n_connect == CTL_YES)
		{
			delete m_pClient[nAddr];
			m_pClient[nAddr] = NULL;
			
			st_client[nAddr].n_connect = CTL_NO;
			sTmp.Format("Client_[%02d] Close.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);

			if (st_handler.cwnd_list != NULL)
			{
				//sprintf( st_msg.mstr_barcode, "%s", sTmp);
				//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
				st_msg.mstr_barcode.Format("%s", sTmp); 
				Func.On_LogFile_Add(LOG_TOTAL, st_msg.mstr_barcode);
			}
			m_sLogMsg = sTmp;
			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
		}
		break;
		
	case CLIENT_SEND:
		sSnd.Format("%s", st_client[nAddr].ch_send);

		if (st_client[nAddr].n_connect == CTL_YES)
		{
			m_pClient[nAddr]->Send(sSnd, sSnd.GetLength(), 0);
			sTmp.Format("Client_[%02d] Data Send    - %s", nAddr, sSnd);

			// ���̸� �ּ� ó�� [2012.10.04]
			/*
			if (st_handler.cwnd_list != NULL)
			{
				sprintf(st_other.str_op_msg, sTmp);
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
			}
			*/
			m_sLogMsg = sTmp;
			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			Func.On_LogFile_Add(LOG_MACHINE, m_sLogMsg);
			Func.On_LogFile_Add(99, m_sLogMsg);
// 			if (st_handler.cwnd_list != NULL)
// 			{
// 				sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 			}
		}
		else
		{
			m_sLogMsg.Format("Client_[%02d] Not ConnectData Send - %s", nAddr, sSnd);
			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			Func.On_LogFile_Add(99, m_sLogMsg);
// 			if (st_handler.cwnd_list != NULL)
// 			{
// 				sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 			}
		}
		break;
		
	case CLIENT_REV:
		// ���ŵ� �����͸� ���̸�ŭ �޾Ƶ���
		sTmp.Format("%s", st_client[nAddr].ch_rev);
		sRcv = sTmp.Mid(0, st_client[nAddr].n_rev_length);
		
		m_sLogMsg.Format("Client_[%02d] Data Receive - %s", nAddr, sRcv);
		cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
		Func.On_LogFile_Add(LOG_MACHINE, m_sLogMsg);
		Func.On_LogFile_Add(99, m_sLogMsg);
// 		if (st_handler.cwnd_list != NULL)
// 		{
// 			sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 		}

		clsEC_Client.OnDataReceive(sRcv);	// [MES->CIM] ���ŵ� �޽��� �����Ͽ� ó��
		break;

		// ���̸� �߰� [2014.08.13]
	case CLIENT_RECONNECT:
		// DISCONNECT �ÿ� ���� �۾� �õ�
		if (st_client[nAddr].n_connect == CTL_NO)
		{
			SetTimer(TMR_CIM_, 5000, NULL);
		}
		break;
	}
	return 0;
}

LRESULT CMainFrame::OnCommand_Client_6(WPARAM wParam, LPARAM lParam)
{
	CString sSnd, sRcv, sTmp, sHead;

	int nStatus	= (int)wParam;
	int nAddr	= (int)lParam;

	switch(nStatus)
	{
	case CLIENT_CONNECT:
		// DISCONNECT �ÿ� ���� �۾� �õ�
		if (st_client[nAddr].n_connect == CTL_NO)
		{
			m_pClient[nAddr] = new CClientSocket;  // ���� ����
			
			// �ý��� ���� �������� ���� �õ�
			// - ���� ��巹�� ���ÿ��� ("127.0.0.1")
			//if (m_pClient[nAddr]->Create(nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port, 1000))
			// ���̸� ���� [2013.11.23]
			if (m_pClient[nAddr]->Create(nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port))//, 1000))
			{
				st_client[nAddr].n_connect = CTL_YES;
				sTmp.Format("Client_[%02d] Connect Success.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);

				if (st_handler.cwnd_list != NULL)
				{
					//sprintf( st_msg.mstr_barcode, "%s", sTmp);
					//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					st_msg.mstr_barcode.Format("%s", sTmp); 

					Func.On_LogFile_Add(LOG_TOTAL, st_msg.mstr_barcode);
				}
				m_sLogMsg = sTmp;
				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			else
			{
				// ������ ���� �ν��Ͻ� ����
				delete m_pClient[nAddr];
				m_pClient[nAddr] = NULL;

				st_client[nAddr].n_connect = CTL_NO;
				sTmp.Format("Client_[%02d] Connect Fail.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);

				if (st_handler.cwnd_list != NULL)
				{
					//sprintf( st_msg.mstr_barcode, "%s", sTmp);
					//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
					st_msg.mstr_barcode.Format("%s", sTmp); 
					Func.On_LogFile_Add(LOG_TOTAL, st_msg.mstr_barcode);
				}
				m_sLogMsg = sTmp;
				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
		}
		break;

	case CLIENT_CLOSE:
		// ������ �����Ŵ
		if (st_client[nAddr].n_connect == CTL_YES)
		{
			delete m_pClient[nAddr];
			m_pClient[nAddr] = NULL;
			
			st_client[nAddr].n_connect = CTL_NO;
			sTmp.Format("Client_[%02d] Close.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);

			if (st_handler.cwnd_list != NULL)
			{
				//sprintf( st_msg.mstr_barcode, "%s", sTmp);
				//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
				st_msg.mstr_barcode.Format("%s", sTmp); 
				Func.On_LogFile_Add(LOG_TOTAL, st_msg.mstr_barcode);
			}
			m_sLogMsg = sTmp;
			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
		}
		break;
		
	case CLIENT_SEND:
		sSnd.Format("%s", st_client[nAddr].ch_send);

		if (st_client[nAddr].n_connect == CTL_YES)
		{
			m_pClient[nAddr]->Send(sSnd, sSnd.GetLength(), 0);
			sTmp.Format("Client_[%02d] Data Send    - %s", nAddr, sSnd);

			// ���̸� �ּ� ó�� [2012.10.04]
			/*
			if (st_handler.cwnd_list != NULL)
			{
				sprintf(st_other.str_op_msg, sTmp);
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
			}
			*/
			m_sLogMsg = sTmp;
			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			Func.On_LogFile_Add(LOG_MACHINE, m_sLogMsg);
			Func.On_LogFile_Add(99, m_sLogMsg);
// 			if (st_handler.cwnd_list != NULL)
// 			{
// 				sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 			}
		}
		else
		{
			m_sLogMsg.Format("Client_[%02d] Not ConnectData Send - %s", nAddr, sSnd);
			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			Func.On_LogFile_Add(99, m_sLogMsg);
// 			if (st_handler.cwnd_list != NULL)
// 			{
// 				sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 			}
		}
		break;
		
	case CLIENT_REV:
		// ���ŵ� �����͸� ���̸�ŭ �޾Ƶ���
		sTmp.Format("%s", st_client[nAddr].ch_rev);
		sRcv = sTmp.Mid(0, st_client[nAddr].n_rev_length);
		
		m_sLogMsg.Format("Client_[%02d] Data Receive - %s", nAddr, sRcv);
		cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
		Func.On_LogFile_Add(LOG_MACHINE, m_sLogMsg);
		Func.On_LogFile_Add(99, m_sLogMsg);
// 		if (st_handler.cwnd_list != NULL)
// 		{
// 			sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 		}
		g_xgem_client.OnDataAnalysis(sRcv);	// [MES->CIM] ���ŵ� �޽��� �����Ͽ� ó��
		break;

		// ���̸� �߰� [2014.08.13]
	case CLIENT_RECONNECT:
		// DISCONNECT �ÿ� ���� �۾� �õ�
		if (st_client[nAddr].n_connect == CTL_NO)
		{
			SetTimer(TMR_CIM_, 5000, NULL);
		}
		break;
	}
	return 0;
}

//==================================================================//
// TCP/IP (����) �˸� ó��
//==================================================================//
LRESULT CMainFrame::OnCommand_Server_1(WPARAM wParam, LPARAM lParam)
{
	CString sSnd, sRcv, sTmp;

	int nStatus	= (int)wParam;
	int nAddr	= (int)lParam;
	int nCount;
	CString sHead, sFunc;

	switch(nStatus)
	{
	case SERVER_CONNECT:
		// DISCONNECT �ÿ� ���� �۾� �õ�
		if (st_server[nAddr].n_connect == CTL_NO)
		{
			m_pServer[nAddr] = new CServerSocket;	// ���� ����

//			if (m_pServer[nAddr]->Create(nAddr, st_server[nAddr].n_port))
			if (m_pServer[nAddr]->Create(st_server[nAddr].n_port, nAddr))
			{
				// ���̸� �߰� [2013.11.12]
				st_server[nAddr].n_connect = CTL_YES;

				if (st_handler.cwnd_list != NULL)
				{
					sTmp.Format("Listening. Server [%02d]..", nAddr);
// 					sprintf( st_msg.mstr_barcode, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);
				}
				m_sLogMsg.Format("Listening. Server [%02d]..", nAddr);
				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
		}
		break;

	case SERVER_CLOSE:
		// ������ �����Ŵ
		if (st_server[nAddr].n_connect == CTL_YES)
		{
			st_server[nAddr].n_connect = CTL_NO;

			// ���̸� �߰� [2013.11.12]
			if (st_handler.cwnd_list != NULL)
			{
				sTmp.Format("Closed. Server [%02d]..", nAddr);
				//sprintf( st_msg.c_normal_msg, "%s", sTmp);
				//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
				Func.On_LogFile_Add(LOG_TOTAL, sTmp);			
			}
			m_sLogMsg.Format("Closed. Server [%02d]..", nAddr);
			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
		}
		SetTimer(TMR_SMEMA_SERVER, 5000, 0);
		break;

	case SERVER_SEND:
		sSnd.Format("%s", st_server[nAddr].ch_send);

		// ������ �����Ͱ� �����ϴ��� Ȯ��
		if (sSnd != "")
		{
			if (st_server[nAddr].n_connect == CTL_YES)
			{
				// ����Ǿ� �ִ� Ŭ���̾�Ʈ ���� ����
				nCount = m_pServer[nAddr]->GetClientCount();
				// [����->Ŭ���̾�Ʈ] ������ ����
				m_pServer[nAddr]->SendClientAt(m_pServer[nAddr]->GetClient(nCount-1), sSnd, sSnd.GetLength());

				/*
				if (st_handler.cwnd_list != NULL)
				{
					sTmp.Format("[SSend] [%02d] %s", nAddr, sSnd);
					sprintf(st_other.str_op_msg, sTmp);
					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
				}
				*/
				m_sLogMsg.Format("[SSend] [%02d] %s", nAddr, sSnd);
				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				Func.On_LogFile_Add(LOG_MACHINE, m_sLogMsg);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			else
			{
				m_sLogMsg.Format("[SSend Fail] (not Connected %02d) %s", nAddr, sSnd);
				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
		}
		else
		{
			m_sLogMsg.Format("[SSend Fail] [Empty Data %02d] %s", nAddr, sSnd);
			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
		}
		break;

	case SERVER_REV:
		// ���ŵ� �����͸� ���̸�ŭ �޾Ƶ���
		sTmp.Format("%s", st_server[nAddr].ch_rev);
		sRcv = sTmp.Mid(0, st_server[nAddr].n_rev_length);

		m_sLogMsg.Format("[SRcv] [%02d] %s", nAddr, sRcv);
		cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
		Func.On_LogFile_Add(LOG_MACHINE, m_sLogMsg);

		g_front_server.OnDataReceive(sRcv);
		Func.On_LogFile_Add(99, m_sLogMsg);
// 		if (st_handler.cwnd_list != NULL)
// 		{
// 			sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 			st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 		}
		break;

	case SERVER_CLIENT_COMM:
		if (st_server[nAddr].n_connect == CTL_NO)
		{
			st_server[nAddr].n_connect = CTL_YES;

			// ���̸� �߰� [2013.11.12]
// 			if (st_handler.cwnd_list != NULL)
// 			{
// 				sTmp.Format("Connected. Server [%02d]..", nAddr);
// 				sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 			}
			m_sLogMsg.Format("Connected. Server [%02d]..", nAddr);

			Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
		}
		break;
	}
	return 0;
}

//==================================================================//
// Zebra print ��� ���
//==================================================================//
LRESULT CMainFrame::OnZebraPrint_Client_1(WPARAM wParam, LPARAM lParam)
{
	CString sSnd, sRcv, sTmp;

	int nStatus	= (int)wParam;
	int nAddr	= (int)lParam;

// 	st_client[nAddr].str_ip = "192.168.1.101";
// 	st_client[nAddr].n_port = 9100;

	switch(nStatus)
	{
		case CLIENT_CONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_client[nAddr].n_connect == CTL_NO)
			{
				m_pClient[nAddr] = new CClientSocket;  // ���� ����

				// - Create(int n_address, CString str_ip, int n_port, int n_timeout);
				if (m_pClient[nAddr]->Create(nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port))//, 1))
				{
					st_client[nAddr].n_connect = CTL_YES;
					sTmp.Format("Client_[%02d] Connect Success.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);

					Func.On_LogFile_Add(LOG_TOTAL, sTmp);
// 					if (st_handler.cwnd_list != NULL)
// 					{
						//sprintf( st_msg.c_normal_msg, "%s", sTmp);
						//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 					}
					//m_sLogMsg = sTmp;
					//cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
				else
				{
					// ������ ���� �ν��Ͻ� ����
					delete m_pClient[nAddr];
					m_pClient[nAddr] = NULL;

					st_client[nAddr].n_connect = CTL_NO;
					sTmp.Format("Client_[%02d] Connect Fail.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);

// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf( st_msg.c_abnormal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
// 					}
// 					m_sLogMsg = sTmp;
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
			}
			break;

		case CLIENT_CLOSE:
			// ������ �����Ŵ
			if (st_client[nAddr].n_connect == CTL_YES)
			{
				delete m_pClient[nAddr];
				m_pClient[nAddr] = NULL;

				st_client[nAddr].n_connect = CTL_NO;
				sTmp.Format("Client_[%02d] Close.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
				Func.On_LogFile_Add(LOG_TOTAL, sTmp);

// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
// 				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;

		case CLIENT_SEND:
			sSnd.Format("%s", st_client[nAddr].ch_send);

			if (st_client[nAddr].n_connect == CTL_YES)
			{
				m_pClient[nAddr]->Send(sSnd, sSnd.GetLength(), 0);
				sTmp.Format("Client_[%02d] Data Send    - %s", nAddr, sSnd);

				// ���̸� �ּ� ó�� [2012.10.04]
				/*
				if (st_handler.cwnd_list != NULL)
				{
					sprintf(st_other.str_op_msg, sTmp);
					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
				}
				*/
				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			else
			{
				m_sLogMsg.Format("Client_[%02d] Not ConnectData Send - %s", nAddr, sSnd);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			break;

		case CLIENT_REV:
			// ���ŵ� �����͸� ���̸�ŭ �޾Ƶ���
			sTmp.Format("%s", st_client[nAddr].ch_rev);
			sRcv = sTmp.Mid(0, st_client[nAddr].n_rev_length);

			m_sLogMsg.Format("Client_[%02d] Data Receive - %s", nAddr, sRcv);
// 			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			if (Func.m_pZebra[0] != NULL)
			{
				Func.m_pZebra[0]->OnPrintStatus(sRcv, st_client[nAddr].n_port);//2014,1125 ysj
				Func.m_pZebra[0]->OnPrintComplete(sRcv);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			break;

			// ���̸� �߰� [2014.08.13]
		case CLIENT_RECONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_client[nAddr].n_connect == CTL_NO)
			{
				SetTimer(TMR_MES_, 5000, NULL);
			}
			break;
	}
	return 0;
}


//==================================================================//
// Zebra print ��� ���
//==================================================================//
LRESULT CMainFrame::OnZebraPrint_Client_2(WPARAM wParam, LPARAM lParam)
{
	CString sSnd, sRcv, sTmp;

	int nStatus	= (int)wParam;
	int nAddr	= (int)lParam;

	switch(nStatus)
	{
		case CLIENT_CONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_client[nAddr].n_connect == CTL_NO)
			{
				m_pClient[nAddr] = new CClientSocket;  // ���� ����

				// - Create(int n_address, CString str_ip, int n_port, int n_timeout);
				if (m_pClient[nAddr]->Create(nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port))//, 1))
				{
					st_client[nAddr].n_connect = CTL_YES;
					sTmp.Format("Client_[%02d] Connect Success.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);

// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 					}
// 					m_sLogMsg = sTmp;
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
				else
				{
					// ������ ���� �ν��Ͻ� ����
					delete m_pClient[nAddr];
					m_pClient[nAddr] = NULL;

					st_client[nAddr].n_connect = CTL_NO;
					sTmp.Format("Client_[%02d] Connect Fail.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);

// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf( st_msg.c_abnormal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
// 					}
// 					m_sLogMsg = sTmp;
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
			}
			break;

		case CLIENT_CLOSE:
			// ������ �����Ŵ
			if (st_client[nAddr].n_connect == CTL_YES)
			{
				delete m_pClient[nAddr];
				m_pClient[nAddr] = NULL;

				st_client[nAddr].n_connect = CTL_NO;
				sTmp.Format("Client_[%02d] Close.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
				Func.On_LogFile_Add(LOG_TOTAL, sTmp);

// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
// 				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;

		case CLIENT_SEND:
			sSnd.Format("%s", st_client[nAddr].ch_send);

			if (st_client[nAddr].n_connect == CTL_YES)
			{
				m_pClient[nAddr]->Send(sSnd, sSnd.GetLength(), 0);
				sTmp.Format("Client_[%02d] Data Send    - %s", nAddr, sSnd);

				// ���̸� �ּ� ó�� [2012.10.04]
				/*
				if (st_handler.cwnd_list != NULL)
				{
					sprintf(st_other.str_op_msg, sTmp);
					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
				}
				*/
				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			else
			{
				m_sLogMsg.Format("Client_[%02d] Not ConnectData Send - %s", nAddr, sSnd);
//				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			break;

		case CLIENT_REV:
			// ���ŵ� �����͸� ���̸�ŭ �޾Ƶ���
			sTmp.Format("%s", st_client[nAddr].ch_rev);
			sRcv = sTmp.Mid(0, st_client[nAddr].n_rev_length);

			m_sLogMsg.Format("Client_[%02d] Data Receive - %s", nAddr, sRcv);
// 			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			if (Func.m_pZebra[1] != NULL)
			{
				Func.m_pZebra[1]->OnPrintStatus(sRcv, st_client[nAddr].n_port);//2014,1125 ysj
				Func.m_pZebra[1]->OnPrintComplete(sRcv);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			break;

			// ���̸� �߰� [2014.08.13]
		case CLIENT_RECONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_client[nAddr].n_connect == CTL_NO)
			{
				SetTimer(TMR_MES_, 5000, NULL);
			}
			break;
	}
	return 0;
}


//==================================================================//
// Zebra print ��� ���
//==================================================================//
LRESULT CMainFrame::OnZebraPrint_Client_3(WPARAM wParam, LPARAM lParam)
{
	CString sSnd, sRcv, sTmp;

	int nStatus	= (int)wParam;
	int nAddr	= (int)lParam;

	switch(nStatus)
	{
		case CLIENT_CONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_client[nAddr].n_connect == CTL_NO)
			{
				m_pClient[nAddr] = new CClientSocket;  // ���� ����

				// - Create(int n_address, CString str_ip, int n_port, int n_timeout);
				if (m_pClient[nAddr]->Create(nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port))//, 1))
				{
					st_client[nAddr].n_connect = CTL_YES;
					sTmp.Format("Client_[%02d] Connect Success.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);

// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 					}
// 					m_sLogMsg = sTmp;
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
				else
				{
					// ������ ���� �ν��Ͻ� ����
					delete m_pClient[nAddr];
					m_pClient[nAddr] = NULL;

					st_client[nAddr].n_connect = CTL_NO;
					sTmp.Format("Client_[%02d] Connect Fail.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);

// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf( st_msg.c_abnormal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
// 					}
// 					m_sLogMsg = sTmp;
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
			}
			break;

		case CLIENT_CLOSE:
			// ������ �����Ŵ
			if (st_client[nAddr].n_connect == CTL_YES)
			{
				delete m_pClient[nAddr];
				m_pClient[nAddr] = NULL;

				st_client[nAddr].n_connect = CTL_NO;
				sTmp.Format("Client_[%02d] Close.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
				Func.On_LogFile_Add(LOG_TOTAL, sTmp);

// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
// 				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;

		case CLIENT_SEND:
			sSnd.Format("%s", st_client[nAddr].ch_send);

			if (st_client[nAddr].n_connect == CTL_YES)
			{
				m_pClient[nAddr]->Send(sSnd, sSnd.GetLength(), 0);
				sTmp.Format("Client_[%02d] Data Send    - %s", nAddr, sSnd);

				// ���̸� �ּ� ó�� [2012.10.04]
				/*
				if (st_handler.cwnd_list != NULL)
				{
					sprintf(st_other.str_op_msg, sTmp);
					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
				}
				*/
				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			else
			{
				m_sLogMsg.Format("Client_[%02d] Not ConnectData Send - %s", nAddr, sSnd);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			break;

		case CLIENT_REV:
			// ���ŵ� �����͸� ���̸�ŭ �޾Ƶ���
			sTmp.Format("%s", st_client[nAddr].ch_rev);
			sRcv = sTmp.Mid(0, st_client[nAddr].n_rev_length);

			m_sLogMsg.Format("Client_[%02d] Data Receive - %s", nAddr, sRcv);
// 			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			if (Func.m_pZebra[2] != NULL)
			{
				Func.m_pZebra[2]->OnPrintStatus(sRcv, st_client[nAddr].n_port);//2014,1125 ysj
				Func.m_pZebra[2]->OnPrintComplete(sRcv);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			break;

			// ���̸� �߰� [2014.08.13]
		case CLIENT_RECONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_client[nAddr].n_connect == CTL_NO)
			{
				SetTimer(TMR_MES_, 5000, NULL);
			}
			break;
	}
	return 0;
}


//==================================================================//
// Zebra print ��� ���
//==================================================================//
LRESULT CMainFrame::OnZebraPrint_Client_4(WPARAM wParam, LPARAM lParam)
{
	CString sSnd, sRcv, sTmp;

	int nStatus	= (int)wParam;
	int nAddr	= (int)lParam;

	switch(nStatus)
	{
		case CLIENT_CONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_client[nAddr].n_connect == CTL_NO)
			{
				m_pClient[nAddr] = new CClientSocket;  // ���� ����

				// - Create(int n_address, CString str_ip, int n_port, int n_timeout);
				if (m_pClient[nAddr]->Create(nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port))//, 1))
				{
					st_client[nAddr].n_connect = CTL_YES;
					sTmp.Format("Client_[%02d] Connect Success.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);

// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 					}
// 					m_sLogMsg = sTmp;
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
				else
				{
					// ������ ���� �ν��Ͻ� ����
					delete m_pClient[nAddr];
					m_pClient[nAddr] = NULL;

					st_client[nAddr].n_connect = CTL_NO;
					sTmp.Format("Client_[%02d] Connect Fail.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);

// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf( st_msg.c_abnormal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
// 					}
// 					m_sLogMsg = sTmp;
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
			}
			break;

		case CLIENT_CLOSE:
			// ������ �����Ŵ
			if (st_client[nAddr].n_connect == CTL_YES)
			{
				delete m_pClient[nAddr];
				m_pClient[nAddr] = NULL;

				st_client[nAddr].n_connect = CTL_NO;
				sTmp.Format("Client_[%02d] Close.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
				Func.On_LogFile_Add(LOG_TOTAL, sTmp);

// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
// 				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;

		case CLIENT_SEND:
			sSnd.Format("%s", st_client[nAddr].ch_send);

			if (st_client[nAddr].n_connect == CTL_YES)
			{
				m_pClient[nAddr]->Send(sSnd, sSnd.GetLength(), 0);
				sTmp.Format("Client_[%02d] Data Send    - %s", nAddr, sSnd);

				// ���̸� �ּ� ó�� [2012.10.04]
				/*
				if (st_handler.cwnd_list != NULL)
				{
					sprintf(st_other.str_op_msg, sTmp);
					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
				}
				*/
				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			else
			{
				m_sLogMsg.Format("Client_[%02d] Not ConnectData Send - %s", nAddr, sSnd);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			break;

		case CLIENT_REV:
			// ���ŵ� �����͸� ���̸�ŭ �޾Ƶ���
			sTmp.Format("%s", st_client[nAddr].ch_rev);
			sRcv = sTmp.Mid(0, st_client[nAddr].n_rev_length);

			m_sLogMsg.Format("Client_[%02d] Data Receive - %s", nAddr, sRcv);
// 			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			if (Func.m_pZebra[3] != NULL)
			{
				Func.m_pZebra[3]->OnPrintStatus(sRcv, st_client[nAddr].n_port);//2014,1125 ysj
				Func.m_pZebra[3]->OnPrintComplete(sRcv);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			break;

			// ���̸� �߰� [2014.08.13]
		case CLIENT_RECONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_client[nAddr].n_connect == CTL_NO)
			{
				SetTimer(TMR_MES_, 5000, NULL);
			}
			break;
	}
	return 0;
}


//==================================================================//
// label vision ��� ���
//==================================================================//
LRESULT CMainFrame::OnLabel_Client(WPARAM wParam, LPARAM lParam)
{
	CString sSnd, sRcv, sTmp;

	int nStatus	= (int)wParam;
	int nAddr	= (int)lParam;

	switch(nStatus)
	{
		case CLIENT_CONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_client[nAddr].n_connect == CTL_NO)
			{
				m_pClient[nAddr] = new CClientSocket;  // ���� ����

				// - Create(int n_address, CString str_ip, int n_port, int n_timeout);
				if (m_pClient[nAddr]->Create(nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port))//, 1000))
				{
					st_client[nAddr].n_connect = CTL_YES;
					sTmp.Format("Client_[%02d] Connect Success.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);

// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 					}
// 					m_sLogMsg = sTmp;
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
				else
				{
					// ������ ���� �ν��Ͻ� ����
					delete m_pClient[nAddr];
					m_pClient[nAddr] = NULL;

					st_client[nAddr].n_connect = CTL_NO;
					sTmp.Format("Client_[%02d] Connect Fail.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);

// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf( st_msg.c_abnormal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
// 					}
// 					m_sLogMsg = sTmp;
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
			}
			break;

		case CLIENT_CLOSE:
			// ������ �����Ŵ
			if (st_client[nAddr].n_connect == CTL_YES)
			{
				delete m_pClient[nAddr];
				m_pClient[nAddr] = NULL;

				st_client[nAddr].n_connect = CTL_NO;
				sTmp.Format("Client_[%02d] Close.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
				Func.On_LogFile_Add(LOG_TOTAL, sTmp);

// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
// 				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;

		case CLIENT_SEND:
			sSnd.Format("%s", st_client[nAddr].ch_send);

			if (st_client[nAddr].n_connect == CTL_YES)
			{
				m_pClient[nAddr]->Send(sSnd, sSnd.GetLength(), 0);
				sTmp.Format("Client_[%02d] Data Send    - %s", nAddr, sSnd);

				// ���̸� �ּ� ó�� [2012.10.04]
				/*
				if (st_handler.cwnd_list != NULL)
				{
					sprintf(st_other.str_op_msg, sTmp);
					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
				}
				*/
				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			else
			{
				m_sLogMsg.Format("Client_[%02d] Not ConnectData Send - %s", nAddr, sSnd);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			break;

		case CLIENT_REV:
			// ���ŵ� �����͸� ���̸�ŭ �޾Ƶ���
			sTmp.Format("%s", st_client[nAddr].ch_rev);
			sRcv = sTmp.Mid(0, st_client[nAddr].n_rev_length);

			m_sLogMsg.Format("Client_[%02d] Data Receive - %s", nAddr, sRcv);
// 			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);

			if (Func.m_pVsClient[EVP_DENSITY] != NULL)
			{
				Func.m_pVsClient[EVP_DENSITY]->OnDataReceive(sRcv);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			break;

			// ���̸� �߰� [2014.08.13]
		case CLIENT_RECONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_client[nAddr].n_connect == CTL_NO)
			{
				SetTimer(TMR_MES_, 5000, NULL);
			}
			break;
	}
	return 0;
}


//==================================================================//
// barcode vision ��� ���
//==================================================================//
LRESULT CMainFrame::OnBarcode_Client(WPARAM wParam, LPARAM lParam)
{
	CString sSnd, sRcv, sTmp;

	int nStatus	= (int)wParam;
	int nAddr	= (int)lParam;

	switch(nStatus)
	{
		case CLIENT_CONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_client[nAddr].n_connect == CTL_NO)
			{
				m_pClient[nAddr] = new CClientSocket;  // ���� ����

				// - Create(int n_address, CString str_ip, int n_port, int n_timeout);
				if (m_pClient[nAddr]->Create(nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port))//, 1000))
				{
					st_client[nAddr].n_connect = CTL_YES;
					sTmp.Format("Client_[%02d] Connect Success.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);

// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 					}
// 					m_sLogMsg = sTmp;
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
				else
				{
					// ������ ���� �ν��Ͻ� ����
					delete m_pClient[nAddr];
					m_pClient[nAddr] = NULL;

					st_client[nAddr].n_connect = CTL_NO;
					sTmp.Format("Client_[%02d] Connect Fail.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);

// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf( st_msg.c_abnormal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
// 					}
// 					m_sLogMsg = sTmp;
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
			}
			break;

		case CLIENT_CLOSE:
			// ������ �����Ŵ
			if (st_client[nAddr].n_connect == CTL_YES)
			{
				delete m_pClient[nAddr];
				m_pClient[nAddr] = NULL;

				st_client[nAddr].n_connect = CTL_NO;
				sTmp.Format("Client_[%02d] Close.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
				Func.On_LogFile_Add(LOG_TOTAL, sTmp);

// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
// 				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;

		case CLIENT_SEND:
			sSnd.Format("%s", st_client[nAddr].ch_send);

			if (st_client[nAddr].n_connect == CTL_YES)
			{
				m_pClient[nAddr]->Send(sSnd, sSnd.GetLength(), 0);
				sTmp.Format("Client_[%02d] Data Send    - %s", nAddr, sSnd);

				// ���̸� �ּ� ó�� [2012.10.04]
				/*
				if (st_handler.cwnd_list != NULL)
				{
					sprintf(st_other.str_op_msg, sTmp);
					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
				}
				*/
				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			else
			{
				m_sLogMsg.Format("Client_[%02d] Not ConnectData Send - %s", nAddr, sSnd);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			break;

		case CLIENT_REV:
			// ���ŵ� �����͸� ���̸�ŭ �޾Ƶ���
			sTmp.Format("%s", st_client[nAddr].ch_rev);
			sRcv = sTmp.Mid(0, st_client[nAddr].n_rev_length);

			m_sLogMsg.Format("Client_[%02d] Data Receive - %s", nAddr, sRcv);
// 			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);

			if (Func.m_pVsClient[EVP_BARCODE] != NULL)
			{
				Func.m_pVsClient[EVP_BARCODE]->OnDataReceive(sRcv);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			break;

			// ���̸� �߰� [2014.08.13]
		case CLIENT_RECONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_client[nAddr].n_connect == CTL_NO)
			{
				SetTimer(TMR_MES_, 5000, NULL);
			}
			break;
	}
	return 0;
}

//==================================================================//
// top vision ��� ���
//==================================================================//
LRESULT CMainFrame::OnTop_Client(WPARAM wParam, LPARAM lParam)
{
	CString sSnd, sRcv, sTmp;

	int nStatus	= (int)wParam;
	int nAddr	= (int)lParam;

	switch(nStatus)
	{
		case CLIENT_CONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_client[nAddr].n_connect == CTL_NO)
			{
				m_pClient[nAddr] = new CClientSocket;  // ���� ����

				// - Create(int n_address, CString str_ip, int n_port, int n_timeout);
				if (m_pClient[nAddr]->Create(nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port))//, 1000))
				{
					st_client[nAddr].n_connect = CTL_YES;
					sTmp.Format("Client_[%02d] Connect Success.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);

// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 					}
// 					m_sLogMsg = sTmp;
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
				else
				{
					// ������ ���� �ν��Ͻ� ����
					delete m_pClient[nAddr];
					m_pClient[nAddr] = NULL;

					st_client[nAddr].n_connect = CTL_NO;
					sTmp.Format("Client_[%02d] Connect Fail.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);

// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf( st_msg.c_abnormal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
// 					}
// 					m_sLogMsg = sTmp;
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
			}
			break;

		case CLIENT_CLOSE:
			// ������ �����Ŵ
			if (st_client[nAddr].n_connect == CTL_YES)
			{
				delete m_pClient[nAddr];
				m_pClient[nAddr] = NULL;

				st_client[nAddr].n_connect = CTL_NO;
				sTmp.Format("Client_[%02d] Close.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
				Func.On_LogFile_Add(LOG_TOTAL, sTmp);

// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
// 				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;

		case CLIENT_SEND:
			sSnd.Format("%s", st_client[nAddr].ch_send);

			if (st_client[nAddr].n_connect == CTL_YES)
			{
				m_pClient[nAddr]->Send(sSnd, sSnd.GetLength(), 0);
				sTmp.Format("Client_[%02d] Data Send    - %s", nAddr, sSnd);
				Func.On_LogFile_Add(99, sTmp);

// 				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			else
			{
				m_sLogMsg.Format("Client_[%02d] Not ConnectData Send - %s", nAddr, sSnd);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			break;

		case CLIENT_REV:
			// ���ŵ� �����͸� ���̸�ŭ �޾Ƶ���
			sTmp.Format("%s", st_client[nAddr].ch_rev);
			sRcv = sTmp.Mid(0, st_client[nAddr].n_rev_length);

			m_sLogMsg.Format("Client_[%02d] Data Receive - %s", nAddr, sRcv);
// 			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);

			if (Func.m_pVsClient[EVP_TOP_POS] != NULL)
			{
				Func.m_pVsClient[EVP_TOP_POS]->OnDataReceive(sRcv);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			break;

			// ���̸� �߰� [2014.08.13]
		case CLIENT_RECONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_client[nAddr].n_connect == CTL_NO)
			{
				SetTimer(TMR_MES_, 5000, NULL);
			}
			break;
	}
	return 0;
}

///////////////////
//kwlee 2016.0821
LRESULT CMainFrame::OnGms_Client(WPARAM wParam, LPARAM lParam)
{
	CString strMsg;
	CString sTmp;
	CString strRcv,strSend;
	int nLength;
	
	switch(wParam)
	{
	case CLIENT_CONNECT:
		// DISCONNECT �ÿ� ���� �۾� �õ�
		if (st_client[CLS_GMS].n_connect == CTL_NO)
		{
			m_pClient[CLS_GMS] = new CClientSocket;  // ���� ����
			
			// - Create(int n_address, CString str_ip, int n_port, int n_timeout);
			if (m_pClient[CLS_GMS]->Create(CLS_GMS, st_client[CLS_GMS].str_ip, st_client[CLS_GMS].n_port, 1))
			{
				st_client[CLS_GMS].n_connect = CTL_YES;
				sTmp.Format("GMS Client_[%02d] Connect Success.. IP = %s , Port = %d", CLS_GMS, st_client[CLS_GMS].str_ip, st_client[CLS_GMS].n_port);
				
				if (st_handler.cwnd_list != NULL)
				{
					sprintf( st_msg.c_normal_msg, "%s", sTmp);
					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
				}
				//	m_sLogMsg = sTmp;
				//	cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			else
			{
				// ������ ���� �ν��Ͻ� ����
				delete m_pClient[CLS_GMS];
				m_pClient[CLS_GMS] = NULL;
				
				st_client[CLS_GMS].n_connect = CTL_NO;
				sTmp.Format("GMS Client_[%02d] Connect Fail.. IP = %s , Port = %d", CLS_GMS, st_client[CLS_GMS].str_ip, st_client[CLS_GMS].n_port);
				
				if (st_handler.cwnd_list != NULL)
				{
					sprintf( st_msg.c_abnormal_msg, "%s", sTmp);
					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
				}
				//	m_sLogMsg = sTmp;
				//	cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
		}
		break;
		
		
	case CLIENT_CLOSE:
		if (m_pClient[CLS_GMS] != NULL)
		{
			st_client[CLS_GMS].n_connect = CTL_NO;
			delete m_pClient[CLS_GMS];
			m_pClient[CLS_GMS] = NULL;
		}
		break;
		
	case CLIENT_SEND:
		if (st_client[CLS_GMS].n_connect == CTL_YES)
		{
			if (m_pClient[CLS_GMS] == NULL) return 0;
			//	strSend.Format("%s",st_client[CLIENT_GMS].ch_send);
			
			sprintf(st_client[CLS_GMS].ch_send,st_client[CLS_GMS].strSend);
			
			//st_client[CLIENT_GMS].strSend.Format("%s",st_client[CLIENT_GMS].ch_send);
			nLength = st_client[CLS_GMS].strSend.GetLength();
			
			m_pClient[CLS_GMS]->Send(st_client[CLS_GMS].ch_send, nLength);
			
			sTmp.Format(_T("[TTS_VNR_NETWORK] %s Send"),st_client[CLS_GMS].strSend);
			sprintf(st_msg.c_normal_msg, "%s", sTmp);
			
			if (st_handler.cwnd_list != NULL)
			{
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG); 
			}
			//	m_sLogMsg = sTmp;
			//	cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
		}
		break;
		
	case CLIENT_REV:
		//clsGms.OnDataReceive(st_client[CLIENT_GMS].strRev);
		
		strRcv.Format("%s", st_client[CLS_GMS].ch_rev);
		//clsGms.OnDataReceive(st_client[CLIENT_GMS].strRev);
		clsGms.OnDataReceive(strRcv);
		break;
		
	}
	
	return 0;
}
//////////////////////

//==================================================================//
// bottom vision ��� ���
//==================================================================//
LRESULT CMainFrame::OnBottom_Client(WPARAM wParam, LPARAM lParam)
{
	CString sSnd, sRcv, sTmp;

	int nStatus	= (int)wParam;
	int nAddr	= (int)lParam;

	switch(nStatus)
	{
		case CLIENT_CONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_client[nAddr].n_connect == CTL_NO)
			{
				m_pClient[nAddr] = new CClientSocket;  // ���� ����

				// - Create(int n_address, CString str_ip, int n_port, int n_timeout);
				if (m_pClient[nAddr]->Create(nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port))//, 1000))
				{
					st_client[nAddr].n_connect = CTL_YES;
					sTmp.Format("Client_[%02d] Connect Success.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);

// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 					}
// 					m_sLogMsg = sTmp;
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
				else
				{
					// ������ ���� �ν��Ͻ� ����
					delete m_pClient[nAddr];
					m_pClient[nAddr] = NULL;

					st_client[nAddr].n_connect = CTL_NO;
					sTmp.Format("Client_[%02d] Connect Fail.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);

// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf( st_msg.c_abnormal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽��� ��� ��û
// 					}
// 					m_sLogMsg = sTmp;
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
			}
			break;

		case CLIENT_CLOSE:
			// ������ �����Ŵ
			if (st_client[nAddr].n_connect == CTL_YES)
			{
				delete m_pClient[nAddr];
				m_pClient[nAddr] = NULL;

				st_client[nAddr].n_connect = CTL_NO;
				sTmp.Format("Client_[%02d] Close.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
				Func.On_LogFile_Add(LOG_TOTAL, sTmp);

// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
// 				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;

		case CLIENT_SEND:
			sSnd.Format("%s", st_client[nAddr].ch_send);

			if (st_client[nAddr].n_connect == CTL_YES)
			{
				m_pClient[nAddr]->Send(sSnd, sSnd.GetLength(), 0);
				sTmp.Format("Client_[%02d] Data Send    - %s", nAddr, sSnd);

				// ���̸� �ּ� ó�� [2012.10.04]
				/*
				if (st_handler.cwnd_list != NULL)
				{
					sprintf(st_other.str_op_msg, sTmp);
					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
				}
				*/
				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			else
			{
				m_sLogMsg.Format("Client_[%02d] Not ConnectData Send - %s", nAddr, sSnd);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			break;

		case CLIENT_REV:
			// ���ŵ� �����͸� ���̸�ŭ �޾Ƶ���
			sTmp.Format("%s", st_client[nAddr].ch_rev);
			sRcv = sTmp.Mid(0, st_client[nAddr].n_rev_length);

			m_sLogMsg.Format("Client_[%02d] Data Receive - %s", nAddr, sRcv);
// 			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);

			if (Func.m_pVsClient[EVP_BTM_POS] != NULL)
			{
				Func.m_pVsClient[EVP_BTM_POS]->OnDataReceive(sRcv);
				Func.On_LogFile_Add(99, m_sLogMsg);
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", m_sLogMsg);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
// 				}
			}
			break;

			// ���̸� �߰� [2014.08.13]
		case CLIENT_RECONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_client[nAddr].n_connect == CTL_NO)
			{
				SetTimer(TMR_MES_, 5000, NULL);
			}
			break;
	}
	return 0;
}


//==================================================================//
// Get Barcode Format1 from server
//==================================================================//
// LRESULT CMainFrame::OnBcrFormat1_Client(WPARAM wParam, LPARAM lParam)
// {
// 	CString sSnd, sRcv, sTmp;
// 
// 	int nStatus	= (int)wParam;
// 	int nAddr	= (int)lParam;
// 
// 	switch(nStatus)
// 	{
// 		case CLIENT_CONNECT:
// 			// DISCONNECT ��A���� ������a AU���� ��A���
// 			if (st_client[nAddr].n_connect == CTL_NO)
// 			{
// 				m_pClient[nAddr] = new CClientSocket;  // ��OAI ��y����
// 
// 				// - Create(int n_address, CString str_ip, int n_port, int n_timeout);
// 				if (m_pClient[nAddr]->Create(nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port))//, 1000))
// 				{
// 					st_client[nAddr].n_connect = CTL_YES;
// 					sTmp.Format("BcrFormat1_Client_[%02d] Connect Success.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
// 
// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ������AAo Aa��A ��aA��
// 					}
// 					m_sLogMsg = sTmp;
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 				}
// 				else
// 				{
// 					// ��y����CN ��OAI AI����AI���� C��A|
// 					delete m_pClient[nAddr];
// 					m_pClient[nAddr] = NULL;
// 
// 					st_client[nAddr].n_connect = CTL_NO;
// 					sTmp.Format("BcrFormat1_Client_[%02d] Connect Fail.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
// 
// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf( st_msg.c_abnormal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // ������AAo Aa��A ��aA��
// 					}
// 					m_sLogMsg = sTmp;
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 				}
// 			}
// 			break;
// 
// 		case CLIENT_CLOSE:
// 			// ������aA�� A����a��AA��
// 			if (st_client[nAddr].n_connect == CTL_YES)
// 			{
// 				delete m_pClient[nAddr];
// 				m_pClient[nAddr] = NULL;
// 
// 				st_client[nAddr].n_connect = CTL_NO;
// 				sTmp.Format("BcrFormat1_Client_[%02d] Close.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
// 
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ������AAo Aa��A ��aA��
// 				}
// 				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 			}
// 			break;
// 
// 		case CLIENT_SEND:
// 			sSnd.Format("%s", st_client[nAddr].ch_send);
// 
// 			if (st_client[nAddr].n_connect == CTL_YES)
// 			{
// 				m_pClient[nAddr]->Send(sSnd, sSnd.GetLength(), 0);
// 				sTmp.Format("BcrFormat1_Client_[%02d] Data Send    - %s", nAddr, sSnd);
// 
// 				// ��OAI���� AO���� A������ [2012.10.04]
// 				/*
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf(st_other.str_op_msg, sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ������AAo Aa��A ��aA��
// 				}
// 				*/
// 				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 			}
// 			else
// 			{
// 				m_sLogMsg.Format("BcrFormat1_Client_[%02d] Not ConnectData Send - %s", nAddr, sSnd);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 			}
// 			break;
// 
// 		case CLIENT_REV:
// 			// ��o��A��E ���AIAI��| ����AI����A�� ����������eAO
// 			sTmp.Format("%s", st_client[nAddr].ch_rev);
// 			sRcv = sTmp.Mid(0, st_client[nAddr].n_rev_length);
// 
// 			m_sLogMsg.Format("BcrFormat1_Client[%02d] Data Receive - %s", nAddr, sRcv);
// 			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 
// 			if (Func.m_pBctFmtClient[0] != NULL)
// 			{
// 				Func.m_pBctFmtClient[0]->OnDataReceive(sRcv);
// 			}
// 			break;
// 
// 			// ��OAI���� A���Ƣ� [2014.08.13]
// 		case CLIENT_RECONNECT:
// 			// DISCONNECT ��A���� ������a AU���� ��A���
// 			if (st_client[nAddr].n_connect == CTL_NO)
// 			{
// 				SetTimer(TMR_MES_, 5000, NULL);
// 			}
// 			break;
// 	}
// 	return 0;
// }
// 
// //==================================================================//
// // Get Barcode Format2 from server
// //==================================================================//
// LRESULT CMainFrame::OnBcrFormat2_Client(WPARAM wParam, LPARAM lParam)
// {
// 	CString sSnd, sRcv, sTmp;
// 
// 	int nStatus	= (int)wParam;
// 	int nAddr	= (int)lParam;
// 
// 	switch(nStatus)
// 	{
// 		case CLIENT_CONNECT:
// 			// DISCONNECT ��A���� ������a AU���� ��A���
// 			if (st_client[nAddr].n_connect == CTL_NO)
// 			{
// 				m_pClient[nAddr] = new CClientSocket;  // ��OAI ��y����
// 
// 				// - Create(int n_address, CString str_ip, int n_port, int n_timeout);
// 				if (m_pClient[nAddr]->Create(nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port))//, 1000))
// 				{
// 					st_client[nAddr].n_connect = CTL_YES;
// 					sTmp.Format("BcrFormat2_Client_[%02d] Connect Success.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
// 
// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ������AAo Aa��A ��aA��
// 					}
// 					m_sLogMsg = sTmp;
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 				}
// 				else
// 				{
// 					// ��y����CN ��OAI AI����AI���� C��A|
// 					delete m_pClient[nAddr];
// 					m_pClient[nAddr] = NULL;
// 
// 					st_client[nAddr].n_connect = CTL_NO;
// 					sTmp.Format("BcrFormat2_Client_[%02d] Connect Fail.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
// 
// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf( st_msg.c_abnormal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // ������AAo Aa��A ��aA��
// 					}
// 					m_sLogMsg = sTmp;
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 				}
// 			}
// 			break;
// 
// 		case CLIENT_CLOSE:
// 			// ������aA�� A����a��AA��
// 			if (st_client[nAddr].n_connect == CTL_YES)
// 			{
// 				delete m_pClient[nAddr];
// 				m_pClient[nAddr] = NULL;
// 
// 				st_client[nAddr].n_connect = CTL_NO;
// 				sTmp.Format("BcrFormat2_Client_[%02d] Close.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
// 
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ������AAo Aa��A ��aA��
// 				}
// 				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 			}
// 			break;
// 
// 		case CLIENT_SEND:
// 			sSnd.Format("%s", st_client[nAddr].ch_send);
// 
// 			if (st_client[nAddr].n_connect == CTL_YES)
// 			{
// 				m_pClient[nAddr]->Send(sSnd, sSnd.GetLength(), 0);
// 				sTmp.Format("BcrFormat2_Client_[%02d] Data Send    - %s", nAddr, sSnd);
// 
// 				// ��OAI���� AO���� A������ [2012.10.04]
// 				/*
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf(st_other.str_op_msg, sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ������AAo Aa��A ��aA��
// 				}
// 				*/
// 				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 			}
// 			else
// 			{
// 				m_sLogMsg.Format("BcrFormat2_Client_[%02d] Not ConnectData Send - %s", nAddr, sSnd);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 			}
// 			break;
// 
// 		case CLIENT_REV:
// 			// ��o��A��E ���AIAI��| ����AI����A�� ����������eAO
// 			sTmp.Format("%s", st_client[nAddr].ch_rev);
// 			sRcv = sTmp.Mid(0, st_client[nAddr].n_rev_length);
// 
// 			m_sLogMsg.Format("BcrFormat2_Client[%02d] Data Receive - %s", nAddr, sRcv);
// 			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 
// 			if (Func.m_pBctFmtClient[1] != NULL)
// 			{
// 				Func.m_pBctFmtClient[1]->OnDataReceive(sRcv);
// 			}
// 			break;
// 
// 			// ��OAI���� A���Ƣ� [2014.08.13]
// 		case CLIENT_RECONNECT:
// 			// DISCONNECT ��A���� ������a AU���� ��A���
// 			if (st_client[nAddr].n_connect == CTL_NO)
// 			{
// 				SetTimer(TMR_MES_, 5000, NULL);
// 			}
// 			break;
// 	}
// 	return 0;
// }
// 
// //==================================================================//
// // Get Barcode Format2 from server
// //==================================================================//
// LRESULT CMainFrame::OnBcrFormat3_Client(WPARAM wParam, LPARAM lParam)
// {
// 	CString sSnd, sRcv, sTmp;
// 
// 	int nStatus	= (int)wParam;
// 	int nAddr	= (int)lParam;
// 
// 	switch(nStatus)
// 	{
// 		case CLIENT_CONNECT:
// 			// DISCONNECT ��A���� ������a AU���� ��A���
// 			if (st_client[nAddr].n_connect == CTL_NO)
// 			{
// 				m_pClient[nAddr] = new CClientSocket;  // ��OAI ��y����
// 
// 				// - Create(int n_address, CString str_ip, int n_port, int n_timeout);
// 				if (m_pClient[nAddr]->Create(nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port))//, 1000))
// 				{
// 					st_client[nAddr].n_connect = CTL_YES;
// 					sTmp.Format("BcrFormat3_Client_[%02d] Connect Success.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
// 
// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ������AAo Aa��A ��aA��
// 					}
// 					m_sLogMsg = sTmp;
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 				}
// 				else
// 				{
// 					// ��y����CN ��OAI AI����AI���� C��A|
// 					delete m_pClient[nAddr];
// 					m_pClient[nAddr] = NULL;
// 
// 					st_client[nAddr].n_connect = CTL_NO;
// 					sTmp.Format("BcrFormat3_Client_[%02d] Connect Fail.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
// 
// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf( st_msg.c_abnormal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // ������AAo Aa��A ��aA��
// 					}
// 					m_sLogMsg = sTmp;
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 				}
// 			}
// 			break;
// 
// 		case CLIENT_CLOSE:
// 			// ������aA�� A����a��AA��
// 			if (st_client[nAddr].n_connect == CTL_YES)
// 			{
// 				delete m_pClient[nAddr];
// 				m_pClient[nAddr] = NULL;
// 
// 				st_client[nAddr].n_connect = CTL_NO;
// 				sTmp.Format("BcrFormat3_Client_[%02d] Close.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
// 
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ������AAo Aa��A ��aA��
// 				}
// 				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 			}
// 			break;
// 
// 		case CLIENT_SEND:
// 			sSnd.Format("%s", st_client[nAddr].ch_send);
// 
// 			if (st_client[nAddr].n_connect == CTL_YES)
// 			{
// 				m_pClient[nAddr]->Send(sSnd, sSnd.GetLength(), 0);
// 				sTmp.Format("BcrFormat3_Client_[%02d] Data Send    - %s", nAddr, sSnd);
// 
// 				// ��OAI���� AO���� A������ [2012.10.04]
// 				/*
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf(st_other.str_op_msg, sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ������AAo Aa��A ��aA��
// 				}
// 				*/
// 				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 			}
// 			else
// 			{
// 				m_sLogMsg.Format("BcrFormat3_Client_[%02d] Not ConnectData Send - %s", nAddr, sSnd);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 			}
// 			break;
// 
// 		case CLIENT_REV:
// 			// ��o��A��E ���AIAI��| ����AI����A�� ����������eAO
// 			sTmp.Format("%s", st_client[nAddr].ch_rev);
// 			sRcv = sTmp.Mid(0, st_client[nAddr].n_rev_length);
// 
// 			m_sLogMsg.Format("BcrFormat3_Client[%02d] Data Receive - %s", nAddr, sRcv);
// 			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 
// 			if (Func.m_pBctFmtClient[2] != NULL)
// 			{
// 				Func.m_pBctFmtClient[2]->OnDataReceive(sRcv);
// 			}
// 			break;
// 
// 			// ��OAI���� A���Ƣ� [2014.08.13]
// 		case CLIENT_RECONNECT:
// 			// DISCONNECT ��A���� ������a AU���� ��A���
// 			if (st_client[nAddr].n_connect == CTL_NO)
// 			{
// 				SetTimer(TMR_MES_, 5000, NULL);
// 			}
// 			break;
// 	}
// 	return 0;
// }
// 
// //==================================================================//
// // Get Barcode Format2 from server
// //==================================================================//
// LRESULT CMainFrame::OnBcrFormat4_Client(WPARAM wParam, LPARAM lParam)
// {
// 	CString sSnd, sRcv, sTmp;
// 
// 	int nStatus	= (int)wParam;
// 	int nAddr	= (int)lParam;
// 
// 	switch(nStatus)
// 	{
// 		case CLIENT_CONNECT:
// 			// DISCONNECT ��A���� ������a AU���� ��A���
// 			if (st_client[nAddr].n_connect == CTL_NO)
// 			{
// 				m_pClient[nAddr] = new CClientSocket;  // ��OAI ��y����
// 
// 				// - Create(int n_address, CString str_ip, int n_port, int n_timeout);
// 				if (m_pClient[nAddr]->Create(nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port))//, 1000))
// 				{
// 					st_client[nAddr].n_connect = CTL_YES;
// 					sTmp.Format("BcrFormat4_Client_[%02d] Connect Success.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
// 
// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ������AAo Aa��A ��aA��
// 					}
// 					m_sLogMsg = sTmp;
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 				}
// 				else
// 				{
// 					// ��y����CN ��OAI AI����AI���� C��A|
// 					delete m_pClient[nAddr];
// 					m_pClient[nAddr] = NULL;
// 
// 					st_client[nAddr].n_connect = CTL_NO;
// 					sTmp.Format("BcrFormat4_Client_[%02d] Connect Fail.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
// 
// 					if (st_handler.cwnd_list != NULL)
// 					{
// 						sprintf( st_msg.c_abnormal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // ������AAo Aa��A ��aA��
// 					}
// 					m_sLogMsg = sTmp;
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 				}
// 			}
// 			break;
// 
// 		case CLIENT_CLOSE:
// 			// ������aA�� A����a��AA��
// 			if (st_client[nAddr].n_connect == CTL_YES)
// 			{
// 				delete m_pClient[nAddr];
// 				m_pClient[nAddr] = NULL;
// 
// 				st_client[nAddr].n_connect = CTL_NO;
// 				sTmp.Format("BcrFormat4_Client_[%02d] Close.. IP = %s , Port = %d", nAddr, st_client[nAddr].str_ip, st_client[nAddr].n_port);
// 
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ������AAo Aa��A ��aA��
// 				}
// 				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 			}
// 			break;
// 
// 		case CLIENT_SEND:
// 			sSnd.Format("%s", st_client[nAddr].ch_send);
// 
// 			if (st_client[nAddr].n_connect == CTL_YES)
// 			{
// 				m_pClient[nAddr]->Send(sSnd, sSnd.GetLength(), 0);
// 				sTmp.Format("BcrFormat4_Client_[%02d] Data Send    - %s", nAddr, sSnd);
// 
// 				// ��OAI���� AO���� A������ [2012.10.04]
// 				/*
// 				if (st_handler.cwnd_list != NULL)
// 				{
// 					sprintf(st_other.str_op_msg, sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ������AAo Aa��A ��aA��
// 				}
// 				*/
// 				m_sLogMsg = sTmp;
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 			}
// 			else
// 			{
// 				m_sLogMsg.Format("BcrFormat2_Client_[%02d] Not ConnectData Send - %s", nAddr, sSnd);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 			}
// 			break;
// 
// 		case CLIENT_REV:
// 			// ��o��A��E ���AIAI��| ����AI����A�� ����������eAO
// 			sTmp.Format("%s", st_client[nAddr].ch_rev);
// 			sRcv = sTmp.Mid(0, st_client[nAddr].n_rev_length);
// 
// 			m_sLogMsg.Format("BcrFormat4_Client[%02d] Data Receive - %s", nAddr, sRcv);
// 			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
// 
// 			if (Func.m_pBctFmtClient[3] != NULL)
// 			{
// 				Func.m_pBctFmtClient[3]->OnDataReceive(sRcv);
// 			}
// 			break;
// 
// 			// ��OAI���� A���Ƣ� [2014.08.13]
// 		case CLIENT_RECONNECT:
// 			// DISCONNECT ��A���� ������a AU���� ��A���
// 			if (st_client[nAddr].n_connect == CTL_NO)
// 			{
// 				SetTimer(TMR_MES_, 5000, NULL);
// 			}
// 			break;
// 	}
// 	return 0;
// }

//==================================================================//
// TCP/IP (����) �˸� ó��
//==================================================================//
LRESULT CMainFrame::OnZebraPrint_Server_1(WPARAM wParam, LPARAM lParam)
{
	CString sSnd, sRcv, sTmp;

	int nStatus	= (int)wParam;
	int nAddr	= (int)lParam;
	int nCount;
	CString sHead, sFunc;

	switch(nStatus)
	{
		case SERVER_CONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_server[nAddr].n_connect == CTL_NO)
			{
				m_pServer[nAddr] = new CServerSocket;	// ���� ����

//				if (m_pServer[nAddr]->Create(nAddr, st_server[nAddr].n_port))
				if (m_pServer[nAddr]->Create(st_server[nAddr].n_port, nAddr))
				{
					// ���̸� �߰� [2013.11.12]
					st_server[nAddr].n_connect = CTL_YES;

					if (st_handler.cwnd_list != NULL)
					{
						sTmp.Format("Listening. Server [%02d]..", nAddr);
// 						sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
						Func.On_LogFile_Add(LOG_TOTAL, sTmp);
					}
// 					m_sLogMsg.Format("Listening. Server [%02d]..", nAddr);
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
			}
			break;

		case SERVER_CLOSE:
			// ������ �����Ŵ
			if (st_server[nAddr].n_connect == CTL_YES)
			{
				st_server[nAddr].n_connect = CTL_NO;

				// ���̸� �߰� [2013.11.12]
				if (st_handler.cwnd_list != NULL)
				{
					sTmp.Format("Closed. Server [%02d]..", nAddr);
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);
				}
// 				m_sLogMsg.Format("Closed. Server [%02d]..", nAddr);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;

		case SERVER_SEND:
			sSnd.Format("%s", st_server[nAddr].ch_send);

			// ������ �����Ͱ� �����ϴ��� Ȯ��
			if (sSnd != "")
			{
				if (st_server[nAddr].n_connect == CTL_YES)
				{
					// ����Ǿ� �ִ� Ŭ���̾�Ʈ ���� ����
					nCount = m_pServer[nAddr]->GetClientCount();
					// [����->Ŭ���̾�Ʈ] ������ ����
					m_pServer[nAddr]->SendClientAt(m_pServer[nAddr]->GetClient(nCount-1), sSnd, sSnd.GetLength());

					/*
					if (st_handler.cwnd_list != NULL)
					{
						sTmp.Format("[SSend] [%02d] %s", nAddr, sSnd);
						sprintf(st_other.str_op_msg, sTmp);
						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					}
					*/
// 					m_sLogMsg.Format("[SSend] [%02d] %s", nAddr, sSnd);
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
				else
				{
					m_sLogMsg.Format("[SSend Fail] (not Connected %02d) %s", nAddr, sSnd);
					//cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
					Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
				}
			}
			else
			{
				m_sLogMsg.Format("[SSend Fail] [Empty Data %02d] %s", nAddr, sSnd);
				//cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
			}
			break;

		case SERVER_REV:
			// ���ŵ� �����͸� ���̸�ŭ �޾Ƶ���
			sTmp.Format("%s", st_server[nAddr].ch_rev);
			sRcv = sTmp.Mid(0, st_server[nAddr].n_rev_length);

			m_sLogMsg.Format("[SRcv_PrintSvr1] [%02d] %s", nAddr, sRcv);
			//cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);

			Func.On_LogFile_Add(99, m_sLogMsg);
			if (Func.m_pZebra[0] != NULL)
			{
				Func.m_pZebra[0]->OnPrintComplete(sRcv);
			}
			break;

		case SERVER_CLIENT_COMM:
			if (st_server[nAddr].n_connect == CTL_NO)
			{
				st_server[nAddr].n_connect = CTL_YES;

				// ���̸� �߰� [2013.11.12]
				if (st_handler.cwnd_list != NULL)
				{
					sTmp.Format("Connected. Server [%02d]..", nAddr);
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);
				}
// 				m_sLogMsg.Format("Connected. Server [%02d]..", nAddr);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;
	}
	return 0;
}


//==================================================================//
// TCP/IP (����) �˸� ó��
//==================================================================//
LRESULT CMainFrame::OnZebraPrint_Server_2(WPARAM wParam, LPARAM lParam)
{
	CString sSnd, sRcv, sTmp;

	int nStatus	= (int)wParam;
	int nAddr	= (int)lParam;
	int nCount;
	CString sHead, sFunc;

	switch(nStatus)
	{
		case SERVER_CONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_server[nAddr].n_connect == CTL_NO)
			{
				m_pServer[nAddr] = new CServerSocket;	// ���� ����

//				if (m_pServer[nAddr]->Create(nAddr, st_server[nAddr].n_port))
				if (m_pServer[nAddr]->Create(st_server[nAddr].n_port, nAddr))
				{
					// ���̸� �߰� [2013.11.12]
					st_server[nAddr].n_connect = CTL_YES;

					if (st_handler.cwnd_list != NULL)
					{
						sTmp.Format("Listening. Server [%02d]..", nAddr);
						//sprintf( st_msg.c_normal_msg, "%s", sTmp);
						//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
						Func.On_LogFile_Add(LOG_TOTAL, sTmp);
					}
					//m_sLogMsg.Format("Listening. Server [%02d]..", nAddr);
					//cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
			}
			break;

		case SERVER_CLOSE:
			// ������ �����Ŵ
			if (st_server[nAddr].n_connect == CTL_YES)
			{
				st_server[nAddr].n_connect = CTL_NO;

				// ���̸� �߰� [2013.11.12]
				if (st_handler.cwnd_list != NULL)
				{
					sTmp.Format("Closed. Server [%02d]..", nAddr);
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);
				}
// 				m_sLogMsg.Format("Closed. Server [%02d]..", nAddr);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;

		case SERVER_SEND:
			sSnd.Format("%s", st_server[nAddr].ch_send);

			// ������ �����Ͱ� �����ϴ��� Ȯ��
			if (sSnd != "")
			{
				if (st_server[nAddr].n_connect == CTL_YES)
				{
					// ����Ǿ� �ִ� Ŭ���̾�Ʈ ���� ����
					nCount = m_pServer[nAddr]->GetClientCount();
					// [����->Ŭ���̾�Ʈ] ������ ����
					m_pServer[nAddr]->SendClientAt(m_pServer[nAddr]->GetClient(nCount-1), sSnd, sSnd.GetLength());

					/*
					if (st_handler.cwnd_list != NULL)
					{
						sTmp.Format("[SSend] [%02d] %s", nAddr, sSnd);
						sprintf(st_other.str_op_msg, sTmp);
						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					}
					*/
					m_sLogMsg.Format("[SSend] [%02d] %s", nAddr, sSnd);
					//cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
					Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
				}
				else
				{
					m_sLogMsg.Format("[SSend Fail] (not Connected %02d) %s", nAddr, sSnd);
					//cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
					Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
				}
			}
			else
			{
				m_sLogMsg.Format("[SSend Fail] [Empty Data %02d] %s", nAddr, sSnd);
				//cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
			}
			break;

		case SERVER_REV:
			// ���ŵ� �����͸� ���̸�ŭ �޾Ƶ���
			sTmp.Format("%s", st_server[nAddr].ch_rev);
			sRcv = sTmp.Mid(0, st_server[nAddr].n_rev_length);

			m_sLogMsg.Format("[SRcv_PrintSvr2] [%02d] %s", nAddr, sRcv);
			//cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			
			Func.On_LogFile_Add(99, m_sLogMsg);

			if (Func.m_pZebra[1] != NULL)
			{
				Func.m_pZebra[1]->OnPrintComplete(sRcv);
			}
			break;

		case SERVER_CLIENT_COMM:
			if (st_server[nAddr].n_connect == CTL_NO)
			{
				st_server[nAddr].n_connect = CTL_YES;

				// ���̸� �߰� [2013.11.12]
				if (st_handler.cwnd_list != NULL)
				{
					sTmp.Format("Connected. Server [%02d]..", nAddr);
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);
				}
// 				m_sLogMsg.Format("Connected. Server [%02d]..", nAddr);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;
	}
	return 0;
}


//==================================================================//
// TCP/IP (����) �˸� ó��
//==================================================================//
LRESULT CMainFrame::OnZebraPrint_Server_3(WPARAM wParam, LPARAM lParam)
{
	CString sSnd, sRcv, sTmp;

	int nStatus	= (int)wParam;
	int nAddr	= (int)lParam;
	int nCount;
	CString sHead, sFunc;

	switch(nStatus)
	{
		case SERVER_CONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_server[nAddr].n_connect == CTL_NO)
			{
				m_pServer[nAddr] = new CServerSocket;	// ���� ����

//				if (m_pServer[nAddr]->Create(nAddr, st_server[nAddr].n_port))
				if (m_pServer[nAddr]->Create(st_server[nAddr].n_port, nAddr))
				{
					// ���̸� �߰� [2013.11.12]
					st_server[nAddr].n_connect = CTL_YES;

					if (st_handler.cwnd_list != NULL)
					{
						sTmp.Format("Listening. Server [%02d]..", nAddr);
// 						sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
						Func.On_LogFile_Add(LOG_TOTAL, sTmp);
					}
// 					m_sLogMsg.Format("Listening. Server [%02d]..", nAddr);
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
			}
			break;

		case SERVER_CLOSE:
			// ������ �����Ŵ
			if (st_server[nAddr].n_connect == CTL_YES)
			{
				st_server[nAddr].n_connect = CTL_NO;

				// ���̸� �߰� [2013.11.12]
				if (st_handler.cwnd_list != NULL)
				{
					sTmp.Format("Closed. Server [%02d]..", nAddr);
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);
				}
// 				m_sLogMsg.Format("Closed. Server [%02d]..", nAddr);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;

		case SERVER_SEND:
			sSnd.Format("%s", st_server[nAddr].ch_send);

			// ������ �����Ͱ� �����ϴ��� Ȯ��
			if (sSnd != "")
			{
				if (st_server[nAddr].n_connect == CTL_YES)
				{
					// ����Ǿ� �ִ� Ŭ���̾�Ʈ ���� ����
					nCount = m_pServer[nAddr]->GetClientCount();
					// [����->Ŭ���̾�Ʈ] ������ ����
					m_pServer[nAddr]->SendClientAt(m_pServer[nAddr]->GetClient(nCount-1), sSnd, sSnd.GetLength());

					/*
					if (st_handler.cwnd_list != NULL)
					{
						sTmp.Format("[SSend] [%02d] %s", nAddr, sSnd);
						sprintf(st_other.str_op_msg, sTmp);
						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					}
					*/
					m_sLogMsg.Format("[SSend] [%02d] %s", nAddr, sSnd);
					//cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
					Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
				}
				else
				{
					m_sLogMsg.Format("[SSend Fail] (not Connected %02d) %s", nAddr, sSnd);
					//cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
					Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
				}
			}
			else
			{
				m_sLogMsg.Format("[SSend Fail] [Empty Data %02d] %s", nAddr, sSnd);
				//cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
			}
			break;

		case SERVER_REV:
			// ���ŵ� �����͸� ���̸�ŭ �޾Ƶ���
			sTmp.Format("%s", st_server[nAddr].ch_rev);
			sRcv = sTmp.Mid(0, st_server[nAddr].n_rev_length);

			m_sLogMsg.Format("[SRcv_PrintSvr3] [%02d] %s", nAddr, sRcv);
			//cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			
			Func.On_LogFile_Add(99, m_sLogMsg);

			if (Func.m_pZebra[2] != NULL)
			{
				Func.m_pZebra[2]->OnPrintComplete(sRcv);
			}
			break;

		case SERVER_CLIENT_COMM:
			if (st_server[nAddr].n_connect == CTL_NO)
			{
				st_server[nAddr].n_connect = CTL_YES;

				// ���̸� �߰� [2013.11.12]
				if (st_handler.cwnd_list != NULL)
				{
					sTmp.Format("Connected. Server [%02d]..", nAddr);
					//sprintf( st_msg.c_normal_msg, "%s", sTmp);
					//st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);
				}
// 				m_sLogMsg.Format("Connected. Server [%02d]..", nAddr);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;
	}
	return 0;
}


//==================================================================//
// TCP/IP (����) �˸� ó��
//==================================================================//
LRESULT CMainFrame::OnZebraPrint_Server_4(WPARAM wParam, LPARAM lParam)
{
	CString sSnd, sRcv, sTmp;

	int nStatus	= (int)wParam;
	int nAddr	= (int)lParam;
	int nCount;
	CString sHead, sFunc;

	switch(nStatus)
	{
		case SERVER_CONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_server[nAddr].n_connect == CTL_NO)
			{
				m_pServer[nAddr] = new CServerSocket;	// ���� ����

//				if (m_pServer[nAddr]->Create(nAddr, st_server[nAddr].n_port))
				if (m_pServer[nAddr]->Create(st_server[nAddr].n_port, nAddr))
				{
					// ���̸� �߰� [2013.11.12]
					st_server[nAddr].n_connect = CTL_YES;

					if (st_handler.cwnd_list != NULL)
					{
						sTmp.Format("Listening. Server [%02d]..", nAddr);
// 						sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
						Func.On_LogFile_Add(LOG_TOTAL, sTmp);
					}
// 					m_sLogMsg.Format("Listening. Server [%02d]..", nAddr);
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
			}
			break;

		case SERVER_CLOSE:
			// ������ �����Ŵ
			if (st_server[nAddr].n_connect == CTL_YES)
			{
				st_server[nAddr].n_connect = CTL_NO;

				// ���̸� �߰� [2013.11.12]
				if (st_handler.cwnd_list != NULL)
				{
					sTmp.Format("Closed. Server [%02d]..", nAddr);
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);
				}
// 				m_sLogMsg.Format("Closed. Server [%02d]..", nAddr);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;

		case SERVER_SEND:
			sSnd.Format("%s", st_server[nAddr].ch_send);

			// ������ �����Ͱ� �����ϴ��� Ȯ��
			if (sSnd != "")
			{
				if (st_server[nAddr].n_connect == CTL_YES)
				{
					// ����Ǿ� �ִ� Ŭ���̾�Ʈ ���� ����
					nCount = m_pServer[nAddr]->GetClientCount();
					// [����->Ŭ���̾�Ʈ] ������ ����
					m_pServer[nAddr]->SendClientAt(m_pServer[nAddr]->GetClient(nCount-1), sSnd, sSnd.GetLength());

					/*
					if (st_handler.cwnd_list != NULL)
					{
						sTmp.Format("[SSend] [%02d] %s", nAddr, sSnd);
						sprintf(st_other.str_op_msg, sTmp);
						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					}
					*/
					m_sLogMsg.Format("[SSend] [%02d] %s", nAddr, sSnd);
					Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
				else
				{
					m_sLogMsg.Format("[SSend Fail] (not Connected %02d) %s", nAddr, sSnd);
					Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
			}
			else
			{
				m_sLogMsg.Format("[SSend Fail] [Empty Data %02d] %s", nAddr, sSnd);
				Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;

		case SERVER_REV:
			// ���ŵ� �����͸� ���̸�ŭ �޾Ƶ���
			sTmp.Format("%s", st_server[nAddr].ch_rev);
			sRcv = sTmp.Mid(0, st_server[nAddr].n_rev_length);

			m_sLogMsg.Format("[SRcv_PrintSvr4] [%02d] %s", nAddr, sRcv);
			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			
			Func.On_LogFile_Add(99, m_sLogMsg);

			if (Func.m_pZebra[3] != NULL)
			{
				Func.m_pZebra[3]->OnPrintComplete(sRcv);
			}
			break;

		case SERVER_CLIENT_COMM:
			if (st_server[nAddr].n_connect == CTL_NO)
			{
				st_server[nAddr].n_connect = CTL_YES;

				// ���̸� �߰� [2013.11.12]
				if (st_handler.cwnd_list != NULL)
				{
					sTmp.Format("Connected. Server [%02d]..", nAddr);
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);
				}
// 				m_sLogMsg.Format("Connected. Server [%02d]..", nAddr);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;
	}
	return 0;
}


//==================================================================//
// TCP/IP (����) �˸� ó��
//==================================================================//
LRESULT CMainFrame::OnLabel_Server(WPARAM wParam, LPARAM lParam)
{
	CString sSnd, sRcv, sTmp;

	int nStatus	= (int)wParam;
	int nAddr	= (int)lParam;
	int nCount;
	CString sHead, sFunc;

	switch(nStatus)
	{
		case SERVER_CONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_server[nAddr].n_connect == CTL_NO)
			{
				m_pServer[nAddr] = new CServerSocket;	// ���� ����

//				if (m_pServer[nAddr]->Create(nAddr, st_server[nAddr].n_port))
				if (m_pServer[nAddr]->Create(st_server[nAddr].n_port, nAddr))
				{
					// ���̸� �߰� [2013.11.12]
					st_server[nAddr].n_connect = CTL_YES;

					if (st_handler.cwnd_list != NULL)
					{
						sTmp.Format("Listening. Server [%02d]..", nAddr);
// 						sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
						Func.On_LogFile_Add(LOG_TOTAL, sTmp);
					}
// 					m_sLogMsg.Format("Listening. Server [%02d]..", nAddr);
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
			}
			break;

		case SERVER_CLOSE:
			// ������ �����Ŵ
			if (st_server[nAddr].n_connect == CTL_YES)
			{
				st_server[nAddr].n_connect = CTL_NO;

				// ���̸� �߰� [2013.11.12]
				if (st_handler.cwnd_list != NULL)
				{
					sTmp.Format("Closed. Server [%02d]..", nAddr);
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);
				}
// 				m_sLogMsg.Format("Closed. Server [%02d]..", nAddr);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;

		case SERVER_SEND:
			sSnd.Format("%s", st_server[nAddr].ch_send);

			// ������ �����Ͱ� �����ϴ��� Ȯ��
			if (sSnd != "")
			{
				if (st_server[nAddr].n_connect == CTL_YES)
				{
					// ����Ǿ� �ִ� Ŭ���̾�Ʈ ���� ����
					nCount = m_pServer[nAddr]->GetClientCount();
					// [����->Ŭ���̾�Ʈ] ������ ����
					if(nCount < 1 ) break;
					m_pServer[nAddr]->SendClientAt(m_pServer[nAddr]->GetClient(nCount-1), sSnd, sSnd.GetLength());

					/*
					if (st_handler.cwnd_list != NULL)
					{
						sTmp.Format("[SSend] [%02d] %s", nAddr, sSnd);
						sprintf(st_other.str_op_msg, sTmp);
						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					}
					*/
					m_sLogMsg.Format("[SSend] [%02d] %s", nAddr, sSnd);
					Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
				else
				{
					m_sLogMsg.Format("[SSend Fail] (not Connected %02d) %s", nAddr, sSnd);
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
					Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
				}
			}
			else
			{
				m_sLogMsg.Format("[SSend Fail] [Empty Data %02d] %s", nAddr, sSnd);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
			}
			break;

		case SERVER_REV:
			// ���ŵ� �����͸� ���̸�ŭ �޾Ƶ���
			sTmp.Format("%s", st_server[nAddr].ch_rev);
			sRcv = sTmp.Mid(0, st_server[nAddr].n_rev_length);

			m_sLogMsg.Format("[SRcv] [%02d] %s", nAddr, sRcv);
// 			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);

			if (Func.m_pVsServer[0] != NULL)
			{
				Func.m_pVsServer[0]->OnDataReceive(0, sRcv);
			}
			break;

		case SERVER_CLIENT_COMM:
			if (st_server[nAddr].n_connect == CTL_NO)
			{
				st_server[nAddr].n_connect = CTL_YES;

				// ���̸� �߰� [2013.11.12]
				if (st_handler.cwnd_list != NULL)
				{
					sTmp.Format("Connected. Server [%02d]..", nAddr);
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);
				}
// 				m_sLogMsg.Format("Connected. Server [%02d]..", nAddr);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;
	}
	return 0;
}


//==================================================================//
// TCP/IP (����) �˸� ó��
//==================================================================//
LRESULT CMainFrame::OnBarcode_Server(WPARAM wParam, LPARAM lParam)
{
	CString sSnd, sRcv, sTmp;

	int nStatus	= (int)wParam;
	int nAddr	= (int)lParam;
	int nCount;
	CString sHead, sFunc;

	switch(nStatus)
	{
		case SERVER_CONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_server[nAddr].n_connect == CTL_NO)
			{
				m_pServer[nAddr] = new CServerSocket;	// ���� ����

//				if (m_pServer[nAddr]->Create(nAddr, st_server[nAddr].n_port))
				if (m_pServer[nAddr]->Create(st_server[nAddr].n_port, nAddr))
				{
					// ���̸� �߰� [2013.11.12]
					st_server[nAddr].n_connect = CTL_YES;

					if (st_handler.cwnd_list != NULL)
					{
						sTmp.Format("Listening. Server [%02d]..", nAddr);
// 						sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
						Func.On_LogFile_Add(LOG_TOTAL, sTmp);
					}
					m_sLogMsg.Format("Listening. Server [%02d]..", nAddr);
					Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
			}
			break;

		case SERVER_CLOSE:
			// ������ �����Ŵ
			if (st_server[nAddr].n_connect == CTL_YES)
			{
				st_server[nAddr].n_connect = CTL_NO;

				// ���̸� �߰� [2013.11.12]
				if (st_handler.cwnd_list != NULL)
				{
					sTmp.Format("Closed. Server [%02d]..", nAddr);
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);
				}
// 				m_sLogMsg.Format("Closed. Server [%02d]..", nAddr);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;

		case SERVER_SEND:
			sSnd.Format("%s", st_server[nAddr].ch_send);

			// ������ �����Ͱ� �����ϴ��� Ȯ��
			if (sSnd != "")
			{
				if (st_server[nAddr].n_connect == CTL_YES)
				{
					// ����Ǿ� �ִ� Ŭ���̾�Ʈ ���� ����
					nCount = m_pServer[nAddr]->GetClientCount();
					// [����->Ŭ���̾�Ʈ] ������ ����
					m_pServer[nAddr]->SendClientAt(m_pServer[nAddr]->GetClient(nCount-1), sSnd, sSnd.GetLength());

					/*
					if (st_handler.cwnd_list != NULL)
					{
						sTmp.Format("[SSend] [%02d] %s", nAddr, sSnd);
						sprintf(st_other.str_op_msg, sTmp);
						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					}
					*/
					m_sLogMsg.Format("[SSend] [%02d] %s", nAddr, sSnd);
					Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
				else
				{
					m_sLogMsg.Format("[SSend Fail] (not Connected %02d) %s", nAddr, sSnd);
					Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
			}
			else
			{
				m_sLogMsg.Format("[SSend Fail] [Empty Data %02d] %s", nAddr, sSnd);
				Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;

		case SERVER_REV:
			// ���ŵ� �����͸� ���̸�ŭ �޾Ƶ���
			sTmp.Format("%s", st_server[nAddr].ch_rev);
			sRcv = sTmp.Mid(0, st_server[nAddr].n_rev_length);

			m_sLogMsg.Format("[SRcv] [%02d] %s", nAddr, sRcv);
			Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
// 			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);

			if (Func.m_pVsServer[1] != NULL)
			{
				Func.m_pVsServer[1]->OnDataReceive(1, sRcv);
			}
			break;

		case SERVER_CLIENT_COMM:
			if (st_server[nAddr].n_connect == CTL_NO)
			{
				st_server[nAddr].n_connect = CTL_YES;

				// ���̸� �߰� [2013.11.12]
				if (st_handler.cwnd_list != NULL)
				{
					sTmp.Format("Connected. Server [%02d]..", nAddr);
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);
				}
// 				m_sLogMsg.Format("Connected. Server [%02d]..", nAddr);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;
	}
	return 0;
}


//==================================================================//
// TCP/IP (����) �˸� ó��
//==================================================================//
LRESULT CMainFrame::OnTop_Server(WPARAM wParam, LPARAM lParam)
{
	CString sSnd, sRcv, sTmp;

	int nStatus	= (int)wParam;
	int nAddr	= (int)lParam;
	int nCount;
	CString sHead, sFunc;

	switch(nStatus)
	{
		case SERVER_CONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_server[nAddr].n_connect == CTL_NO)
			{
				m_pServer[nAddr] = new CServerSocket;	// ���� ����

//				if (m_pServer[nAddr]->Create(nAddr, st_server[nAddr].n_port))
				if (m_pServer[nAddr]->Create(st_server[nAddr].n_port, nAddr))
				{
					// ���̸� �߰� [2013.11.12]
					st_server[nAddr].n_connect = CTL_YES;

					if (st_handler.cwnd_list != NULL)
					{
						sTmp.Format("Listening. Server [%02d]..", nAddr);
// 						sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
						Func.On_LogFile_Add(LOG_TOTAL, sTmp);
					}
// 					m_sLogMsg.Format("Listening. Server [%02d]..", nAddr);
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
			}
			break;

		case SERVER_CLOSE:
			// ������ �����Ŵ
			if (st_server[nAddr].n_connect == CTL_YES)
			{
				st_server[nAddr].n_connect = CTL_NO;

				// ���̸� �߰� [2013.11.12]
				if (st_handler.cwnd_list != NULL)
				{
					sTmp.Format("Closed. Server [%02d]..", nAddr);
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);
				}
// 				m_sLogMsg.Format("Closed. Server [%02d]..", nAddr);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;

		case SERVER_SEND:
			sSnd.Format("%s", st_server[nAddr].ch_send);

			// ������ �����Ͱ� �����ϴ��� Ȯ��
			if (sSnd != "")
			{
				if (st_server[nAddr].n_connect == CTL_YES)
				{
					// ����Ǿ� �ִ� Ŭ���̾�Ʈ ���� ����
					nCount = m_pServer[nAddr]->GetClientCount();
					// [����->Ŭ���̾�Ʈ] ������ ����
					if(nCount < 1 ) break;
					m_pServer[nAddr]->SendClientAt(m_pServer[nAddr]->GetClient(nCount-1), sSnd, sSnd.GetLength());

					/*
					if (st_handler.cwnd_list != NULL)
					{
						sTmp.Format("[SSend] [%02d] %s", nAddr, sSnd);
						sprintf(st_other.str_op_msg, sTmp);
						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					}
					*/
					m_sLogMsg.Format("[SSend] [%02d] %s", nAddr, sSnd);
					Func.On_LogFile_Add(99, m_sLogMsg);
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
				else
				{
					m_sLogMsg.Format("[SSend Fail] (not Connected %02d) %s", nAddr, sSnd);
					Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
			}
			else
			{
				m_sLogMsg.Format("[SSend Fail] [Empty Data %02d] %s", nAddr, sSnd);
				Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;

		case SERVER_REV:
			// ���ŵ� �����͸� ���̸�ŭ �޾Ƶ���
			sTmp.Format("%s", st_server[nAddr].ch_rev);
			sRcv = sTmp.Mid(0, st_server[nAddr].n_rev_length);

			m_sLogMsg.Format("[SRcv] [%02d] %s", nAddr, sRcv);
			Func.On_LogFile_Add(99, m_sLogMsg);
// 			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);

			if (Func.m_pVsServer[2] != NULL)
			{
				Func.m_pVsServer[2]->OnDataReceive(2, sRcv);
			}
			break;

		case SERVER_CLIENT_COMM:
			if (st_server[nAddr].n_connect == CTL_NO)
			{
				st_server[nAddr].n_connect = CTL_YES;

				// ���̸� �߰� [2013.11.12]
				if (st_handler.cwnd_list != NULL)
				{
					sTmp.Format("Connected. Server [%02d]..", nAddr);
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);
				}
// 				m_sLogMsg.Format("Connected. Server [%02d]..", nAddr);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;
	}
	return 0;
}


//==================================================================//
// TCP/IP (����) �˸� ó��
//==================================================================//
LRESULT CMainFrame::OnBottom_Server(WPARAM wParam, LPARAM lParam)
{
	CString sSnd, sRcv, sTmp;

	int nStatus	= (int)wParam;
	int nAddr	= (int)lParam;
	int nCount;
	CString sHead, sFunc;

	switch(nStatus)
	{
		case SERVER_CONNECT:
			// DISCONNECT �ÿ� ���� �۾� �õ�
			if (st_server[nAddr].n_connect == CTL_NO)
			{
				m_pServer[nAddr] = new CServerSocket;	// ���� ����

//				if (m_pServer[nAddr]->Create(nAddr, st_server[nAddr].n_port))
				if (m_pServer[nAddr]->Create(st_server[nAddr].n_port, nAddr))
				{
					// ���̸� �߰� [2013.11.12]
					st_server[nAddr].n_connect = CTL_YES;

					if (st_handler.cwnd_list != NULL)
					{
						sTmp.Format("Listening. Server [%02d]..", nAddr);
// 						sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
						Func.On_LogFile_Add(LOG_TOTAL, sTmp);
					}
// 					m_sLogMsg.Format("Listening. Server [%02d]..", nAddr);
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
			}
			break;

		case SERVER_CLOSE:
			// ������ �����Ŵ
			if (st_server[nAddr].n_connect == CTL_YES)
			{
				st_server[nAddr].n_connect = CTL_NO;

				// ���̸� �߰� [2013.11.12]
				if (st_handler.cwnd_list != NULL)
				{
					sTmp.Format("Closed. Server [%02d]..", nAddr);
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);
				}
// 				m_sLogMsg.Format("Closed. Server [%02d]..", nAddr);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;

		case SERVER_SEND:
			sSnd.Format("%s", st_server[nAddr].ch_send);

			// ������ �����Ͱ� �����ϴ��� Ȯ��
			if (sSnd != "")
			{
				if (st_server[nAddr].n_connect == CTL_YES)
				{
					// ����Ǿ� �ִ� Ŭ���̾�Ʈ ���� ����
					nCount = m_pServer[nAddr]->GetClientCount();
					// [����->Ŭ���̾�Ʈ] ������ ����
					if(nCount < 1 ) break;
					m_pServer[nAddr]->SendClientAt(m_pServer[nAddr]->GetClient(nCount-1), sSnd, sSnd.GetLength());

					/*
					if (st_handler.cwnd_list != NULL)
					{
						sTmp.Format("[SSend] [%02d] %s", nAddr, sSnd);
						sprintf(st_other.str_op_msg, sTmp);
						st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					}
					*/
					m_sLogMsg.Format("[SSend] [%02d] %s", nAddr, sSnd);
					Func.On_LogFile_Add(99, m_sLogMsg);
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
				else
				{
					m_sLogMsg.Format("[SSend Fail] (not Connected %02d) %s", nAddr, sSnd);
					Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
// 					cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
				}
			}
			else
			{
				m_sLogMsg.Format("[SSend Fail] [Empty Data %02d] %s", nAddr, sSnd);
				Func.On_LogFile_Add(LOG_TOTAL, m_sLogMsg);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;

		case SERVER_REV:
			// ���ŵ� �����͸� ���̸�ŭ �޾Ƶ���
			sTmp.Format("%s", st_server[nAddr].ch_rev);
			sRcv = sTmp.Mid(0, st_server[nAddr].n_rev_length);

			m_sLogMsg.Format("[SRcv] [%02d] %s", nAddr, sRcv);
			Func.On_LogFile_Add(99, m_sLogMsg);
// 			cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);

			if (Func.m_pVsServer[3] != NULL)
			{
				Func.m_pVsServer[3]->OnDataReceive(3, sRcv);
			}
			break;

		case SERVER_CLIENT_COMM:
			if (st_server[nAddr].n_connect == CTL_NO)
			{
				st_server[nAddr].n_connect = CTL_YES;

				// ���̸� �߰� [2013.11.12]
				if (st_handler.cwnd_list != NULL)
				{
					sTmp.Format("Connected. Server [%02d]..", nAddr);
// 					sprintf( st_msg.c_normal_msg, "%s", sTmp);
// 					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // �޽��� ��� ��û
					Func.On_LogFile_Add(LOG_TOTAL, sTmp);
				}
// 				m_sLogMsg.Format("Connected. Server [%02d]..", nAddr);
// 				cLOG.OnLogEvent(LOG_SOCKET_, m_sLogMsg);
			}
			break;
	}
	return 0;
}



LRESULT CMainFrame::OnBcrCommSerial(WPARAM wParam,LPARAM lParam)
{
	int mn_comm = wParam; 
	int port = lParam;
	switch(mn_comm)
	{
	case 2:
		OnClear(port);
		break;

	case 3:
		OnClose(port);
		break;

	case 4:
		OnOpen(port);
		break;

	case 5:
		OnReadCount(port);
		break;
	}
	return 0;
}

void CMainFrame::OnClear(int nPort) 
{
	// TODO: Add your control notification handler code here
	if( nPort == BCR_PORT - 1)   clsBarcode.OnBarcodeReset();
	else						 clsBarcode2.OnBarcodeReset();
}

void CMainFrame::OnClose(int nPort) 
{
	// TODO: Add your control notification handler code here
	if( nPort == GMS_PORT - 1)	  clsGms.OnClose();
	else if( nPort == BCR_PORT-1) clsBarcode.OnClose();
	else						  clsBarcode2.OnClose();
}

void CMainFrame::OnOpen(int nPort) 
{
	// TODO: Add your control notification handler code here
	if( nPort == GMS_PORT - 1)		clsGms.OnOpen(GMS_PORT, 9600, NOPARITY, 8, ONESTOPBIT, 0x03);
	else if( nPort == BCR_PORT-1)	clsBarcode.OnOpen(BCR_PORT, 9600, NOPARITY, 8, ONESTOPBIT, 0x03);
	else if( nPort == BCR_PORT2-1)	clsBarcode2.OnOpen(BCR_PORT2, 9600, NOPARITY, 8, ONESTOPBIT, 0x03);
}

void CMainFrame::OnReadCount(int nPort) 
{
	// TODO: Add your control notification handler code here
	int nCount;
	CString strTemp;

	if( nPort == BCR_PORT-1) nCount = clsBarcode.OnBarcodeCount();
	else					 nCount = clsBarcode2.OnBarcodeCount();

	strTemp.Format("%d", nCount);
	if(st_handler.cwnd_list != NULL)
	{
		sprintf(st_msg.c_normal_msg, strTemp);
		st_handler.cwnd_list->SendMessage(WM_LIST_DATA, 0, NORMAL_MSG);  // ���� �Ϸ� ��� ��û
	}
}

void CMainFrame::OnGmsDataSave()
{
	int i;
	st_grounddb.mole_date = COleDateTime::GetCurrentTime();
	
	for (i=0; i<5; i++)
	{
		st_grounddb.mstrChannel[i] = clsGms.m_strChann[i];
	}

	Func.DB_Write_Ground(st_grounddb);			// �����Ѵ�.
}


int CMainFrame::OnServerInterace( int nInterface)
{
	int nFunRet = CTLBD_RET_PROCEED;

//	FUNCTION=BRAND_DTBT_LABEL_ISSUE LOT_ID=X005600447 BOAT_ID=01 EQP_ID=AP-01 SERIAL=S21GNWAFB00052T 
// 	DTBT_LABEL_CODE=Q550-003629 DTBT_RIBBON_CODE=Q550-002237 MODE=NEW RETRY=0 RETRY_CNT=0

	CString str_lotid = "X00QR30450";//"X005C00447";
	CString str_boatid = "34";
	CString str_Serial = "S1SMNSAFC07070X";//"S1SRNYAF900202D";
	
	CString str_labelcode = "Q550-002482";//"LA68-00037A";	
	CString str_ribboncode = "Q550-001004";//"Q550-0002236";

	CString str_labelmatcode = "Q550-00248";//"Q310-221183";

	CString str_dtntmatcode = "Q550-002482";//"LA96-2144";
	CString str_ribboncode1 = "Q550-001004";//"LA96-2141";

	CString str_oper = "08025454";

	switch(mn_ServerStep)
	{
	case 0:
		mn_ServerStep = 10;
		break;

	case 10:
		if(st_client[CLS_ECSERVER].n_connect == CTL_NO )
		{

			m_dwServerTime = GetCurrentTime();
			mn_ServerStep = 20;
			::SendMessage(st_handler.hWnd, WM_CLIENT_MSG_1, CLIENT_CONNECT, 0);
		}
		else
		{
			mn_ServerStep = 100;
		}
		break;

	case 20:
		if(GetCurrentTime() - m_dwServerTime < 0 ) m_dwServerTime = GetCurrentTime();
		else if( GetCurrentTime() - m_dwServerTime > 5000) 
		{
			mn_ServerStep = 10;
		}
		break;

	case 100:
		if(nInterface == 1)
			clsBcrFormatClient.OnBrandDensityLabelIssue(0, str_lotid, str_boatid, str_Serial, "0","0");
		else if(nInterface == 2)
			clsBcrFormatClient.OnBrandBcrLabelIssue(0, str_lotid, str_boatid, str_Serial,str_labelcode, str_ribboncode, "NEW", "0","0");
		else if(nInterface == 3)
			clsBcrFormatClient.OnBrandDensityLabelCCS(0, str_lotid, str_boatid, str_Serial,str_labelmatcode, "0","0");
		else if(nInterface == 4)
		{
//			clsBcrFormatClient.OnBrandDTBTLabelCCS(0, str_lotid, str_boatid, str_Serial,str_dtntmatcode, str_ribboncode1, "0","0");
			if	   ( st_idbuff_info[0].n_exist[0] == 1) str_Serial.Format("%s", st_idbuff_info[0].c_serial[0]);
			else if( st_idbuff_info[0].n_exist[1] == 1) str_Serial.Format("%s", st_idbuff_info[0].c_serial[1]);
			else if( st_idbuff_info[1].n_exist[0] == 1) str_Serial.Format("%s", st_idbuff_info[1].c_serial[0]);
			else if( st_idbuff_info[1].n_exist[1] == 1) str_Serial.Format("%s", st_idbuff_info[1].c_serial[1]);
			else if( st_idbuff_info[2].n_exist[0] == 1) str_Serial.Format("%s", st_idbuff_info[2].c_serial[0]);
			else if( st_idbuff_info[2].n_exist[1] == 1) str_Serial.Format("%s", st_idbuff_info[2].c_serial[1]);
			nFunRet = CTLBD_RET_GOOD;
			mn_ServerStep = 0;
			if (st_handler.cwnd_list != NULL)
			{
				sprintf(st_msg.c_normal_msg, "NO Serial int Test Site.");
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
			}

			break;
			clsBcrFormatClient.OnBrandDTBTLabelCCS(0, str_lotid, str_boatid, str_Serial, st_handler.m_strLabelCode[0], st_handler.m_strRibbonCode[0], "0","0");
		}
		else if(nInterface == 5)
			clsBcrFormatClient.PX_XClose(0, str_lotid, str_oper, "0", "0");
		else if( nInterface == 6)
			clsBcrFormatClient.OnProdSerial_Info(0, str_lotid, str_boatid, str_Serial, "NO", st_mes_data.srt_RETRY_CNT);
		else if( nInterface == 7 )
			clsBcrFormatClient.OnBoatID_Info(0, str_boatid, "NO", st_mes_data.srt_RETRY_CNT);
		else if( nInterface == 8 )
			clsBcrFormatClient.OnPacking_Master_Info(0, str_lotid, str_Serial, "NO", "0");
		else if( nInterface == 9 )
		{
			int nBoat = st_idbuff_info[SHIFT_IDBUFF_INDEX_ULD].n_idbuff_num[0];
			clsEC_Client.OnBoatIDModify(CLS_FORMAT, str_lotid, str_boatid, 
				str_Serial, "END", "NO", "0");
		}

			//clsBcrFormatClient.OnBoatIDModify(0, str_lotid, str_boatid, str_Serial, "NEW", "NO", "0");

		
// 		clsBcrFormatClient.SetSerialIn();

		mn_ServerStep = 200;
		m_dwServerTime = GetCurrentTime();
		break;
		

	case 200:
		if(GetCurrentTime() - m_dwServerTime < 0 ) m_dwServerTime = GetCurrentTime();
// 		if( clsBcrFormatClient.GetSerialInReceived() )
// 		{
// 			mn_ServerStep = 1000;
// 		}
		if(GetCurrentTime() - m_dwServerTime > 1000) mn_ServerStep = 1000;
		break;

		
	case 1000:
		nFunRet = CTLBD_RET_GOOD;
		mn_ServerStep = 0;
		break;
	}


	return nFunRet;

}

////2015.0413
int CMainFrame::OnXgmInterface()
{
	int nFunRet = CTLBD_RET_PROCEED;
	
	switch(nXgemStep)
	{
	case 0:
		nXgemStep = 100;
		break;
		
	case 100:
		if( st_basic.mn_mode_xgem == CTL_YES )
		{
			CWnd* m_pWnd = CWnd::FindWindow(NULL,"1");
			CWnd* m_pWnd1 = CWnd::FindWindow(NULL,"XgemInterface");
			if(m_pWnd){
				//������ Program�� Ȱ��ȭ ��Ų��.
				m_pWnd->SetForegroundWindow(); 	
				m_pWnd->ShowWindow(SW_RESTORE);	
			}
			else if(m_pWnd1){
				//������ Program�� Ȱ��ȭ ��Ų��.
				m_pWnd1->SetForegroundWindow(); 	
				m_pWnd1->ShowWindow(SW_RESTORE);	
			}
			else{
				//WinExec("C:\\AMT8520\\bin\\XgemInterface.exe",SW_SHOW);
				::ShellExecute(NULL, NULL, "C:\\AMT8590\\bin\\XgemInterface.exe", NULL, NULL, SW_SHOWNORMAL);
			}
			lXgemTime[0] = GetCurrentTime();
			nXgemStep = 200;
		}
		else
		{
			nFunRet = CTLBD_RET_ERROR;
			nXgemStep = 0;
		}
		break;
		
		
	case 200:
		if(GetCurrentTime() - lXgemTime[0] > 5000) nXgemStep = 300;
		else if(GetCurrentTime() - lXgemTime[0] < 0 ) lXgemTime[0] = GetCurrentTime();
		
		break;
		
	case 300:
		g_xgem_client.XgemInitialize();
		lXgemTime[0] = GetCurrentTime();
		nXgemStep = 400;
		break;
		
	case 400:
		if(GetCurrentTime() - lXgemTime[0] > 3000) nXgemStep = 500;
		else if(GetCurrentTime() - lXgemTime[0] < 0 ) lXgemTime[0] = GetCurrentTime();
		break;
		
	case 500:
		Func.OnSavePPID();
		lXgemTime[0] = GetCurrentTime();
		nXgemStep = 600;
		break;
		
	case 600:
		if(GetCurrentTime() - lXgemTime[0] > 2000) nXgemStep = 1000;
		else if(GetCurrentTime() - lXgemTime[0] < 0 ) lXgemTime[0] = GetCurrentTime();
		break;
		
	case 1000:
		//		g_client_ec.OnSendToolInform(true);
		nFunRet = CTLBD_RET_GOOD;
		nXgemStep = 0;
		break;
	}
	
	
	return nFunRet;
	
}
////


LRESULT CMainFrame::OnMainMessageXCloseEvent(WPARAM wParam, LPARAM lParam)
{
	int i = 0;
	CString strTemp;
	
	if (wParam == CTL_YES)
	{
		if (mp_xmsg_dlg != NULL && IsWindow(mp_xmsg_dlg->m_hWnd))
		{
			mp_xmsg_dlg->SetFocus();	// ��ȭ���ڸ� Ȱ��ȭ
			mp_xmsg_dlg->OnEventMsg_Text_Set();
		}
		else
		{
			mp_xmsg_dlg = new CDialog_Event_XClose;
			mp_xmsg_dlg->Create();
			mp_xmsg_dlg->ShowWindow(SW_SHOW);
			g_ioMgr.set_out_bit(st_io.o_buzzer_off_lamp, IO_ON);
			if (st_lamp.mn_buzzer_mode == CTL_YES)
				g_ioMgr.set_out_bit(st_io.o_buzzer_3, IO_ON);
		}
		
	}
	else if (wParam == CTL_NO)
	{
		for (i = 0; i < 3; i++)
		{
			st_msg.mstr_event_xmsg[i] = "";
		}
		
		if (mp_xmsg_dlg != NULL && IsWindow(mp_xmsg_dlg->m_hWnd))
		{
			mp_xmsg_dlg->ShowWindow(SW_HIDE);
			mp_xmsg_dlg->DestroyWindow();
			delete mp_xmsg_dlg;
			mp_xmsg_dlg = NULL;
		}
		
		g_ioMgr.set_out_bit(st_io.o_buzzer_off_lamp, IO_OFF);
		if (st_lamp.mn_buzzer_mode == CTL_YES)
			g_ioMgr.set_out_bit(st_io.o_buzzer_3, IO_OFF);
	}
	
	return 0;
}

BOOL CMainFrame::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	COPYDATASTRUCT cds;	
	
	switch( pCopyDataStruct->dwData)
	{ 
	case WM_PARTID_DATA:
		{					
			g_cs.EnterCriticalSection();
			st_copydata = new st_copy_data;			
			st_copydata->mn_mdl = 19;
			
			CString strPartID;
			strPartID.Format("%s", g_lotMgr.GetLotAt(0).GetPartID());
			strPartID.TrimLeft(' '); strPartID.TrimRight(' ');
			strPartID.TrimLeft(); strPartID.TrimRight();			
			
			memset(st_copydata->str_partid, 0x00, sizeof(st_copydata->str_partid));
			sprintf(st_copydata->str_partid,"%s", (LPCTSTR)strPartID);
			
			cds.dwData = WM_MDL_PART_DATA;
			cds.cbData = sizeof(st_copy_data);
			cds.lpData = st_copydata;
			
			HWND hwnd = ::FindWindow(NULL,"RegModel");
			if (hwnd!= NULL)
			{
				HANDLE handle = AfxGetInstanceHandle();
				::SendMessage(hwnd, WM_COPYDATA, (WPARAM)handle, (LPARAM)&cds);
			}
			else
			{
				if (st_handler.cwnd_list != NULL)
				{
					sprintf(st_msg.c_abnormal_msg, "RegModel.exe can't find program(C:\\AMT859\\BIN\\RegModel.exe");
					st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // �޽AAo Aa�A �aA�
					
				}
			}
			
			delete st_copydata;
			g_cs.LeaveCriticalSection();			
		}
		break;	
	}
	
	return CFrameWnd::OnCopyData(pWnd, pCopyDataStruct);
}

//2016.0919
void CMainFrame::OnMain_Alarm_Mysql_Write() 
{
	// TODO: Add your control notification handler code here
	g_cs.EnterCriticalSection();
	CString		strTmp[6];
	CTime time = CTime::GetCurrentTime();
	
	strTmp[1].Format("%04d/%02d/%02d %02d:%02d:%02d",	st_work.t_jamcode_start.GetYear(), 
		st_work.t_jamcode_start.GetMonth(),
		st_work.t_jamcode_start.GetDay(),
		st_work.t_jamcode_start.GetHour(),
		st_work.t_jamcode_start.GetMinute(),
		st_work.t_jamcode_start.GetSecond());
	
	strTmp[2].Format("%04d/%02d/%02d %02d:%02d:%02d",	st_work.t_jamcode_end.GetYear(), 
		st_work.t_jamcode_end.GetMonth(),
		st_work.t_jamcode_end.GetDay(),
		st_work.t_jamcode_end.GetHour(),
		st_work.t_jamcode_end.GetMinute(),
		st_work.t_jamcode_end.GetSecond());
	strTmp[3] = alarm.str_lastcode;
	strTmp[4] = st_alarm.mstr_cur_msg; //"Loadng ���� ������ Ȯ���� �ּ���.";
	strTmp[5].Format("%d", st_work.t_jamcode_end - st_work.t_jamcode_start);
	
	
	if(Mysql.MySql_Open("localhost", "root", "1111", 3306))
	{
		// amt database ����
		if(Mysql.Database_Select("AMT8590"))
		{
			//  lot_data table ���� 
			if(Mysql.Table_Select("AMT8590", "JAMCODE"))
			{
				// lot_data table�� ������ �߰�
				Mysql.Record_Add("JAMCODE", strTmp);
			}
			else
			{
				// table�� ������ ���� table �߰�
				if(Mysql.Table_Create("AMT8590", "JAMCODE", 6, Mysql.m_str_jamcode_table_name, Mysql.m_n_jamcode_table_type, Mysql.m_n_jamcode_table_num))
				{
					// lot_data table�� ������ �߰�
					Mysql.Record_Add("JAMCODE", strTmp);
				}
			}
		}
		else
		{
			// amt database�� ������ database �߰�
			if(Mysql.Database_Create("AMT8590"))
			{
				// lot_data table ���� �߰� 
				if(Mysql.Table_Create("AMT8590", "JAMCODE", 6, Mysql.m_str_jamcode_table_name, Mysql.m_n_jamcode_table_type, Mysql.m_n_jamcode_table_num))
				{
					Mysql.Record_Add("JAMCODE", strTmp);
				}
			}
		}
	}
	
	Mysql.MySql_Close();
	g_cs.LeaveCriticalSection();
}

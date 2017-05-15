#ifndef _VARIABLE_h__
#define _VARIABLE_h__

#include "Alg_Mysql.h"
#include "CtlBd_Variable.h"
/////////////////////////////////////////////////////////
//DLL ������ ���濹�� //2011.1007 �߰� 
/////////////////////////////////////////////////////////
#define BD_NO		0  //� ������ Ŭ����� ���� 
#define BD_YES		1  //� ������ ��û�� ����

#define CONV_SINGLE 0
#define CONV_BOTH	1

#define WM_SEND_COPY_DATA	   1
#define WM_MDL_PART_DATA       2

#define	WM_PARTID_DATA		   1

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//motor, i/O ������� ���ϰ��� �� �͸� ����Ѵ�  
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//2013,1001
#define CHINA_VER   0


#define BD_ERROR    -1
#define BD_PROCEED  0
#define BD_GOOD		1
#define BD_RETRY	2
#define BD_SAFETY	3

#define TRAY_X                  0
#define TRAY_Y                  1

#define MAX_TRAYCELL			20

#define M_ROBOT_DENSITY_INDEX			0
#define M_ROBOT_BARCODE_INDEX			1

#define BINCHECK_SKIP           0    // BIN ������ �˻����� ���� 

//SOCKET DATA����.
#define LOT_DATA			0	// �ش� LOT����...
#define DAY_DATA			1	// ����
#define MONTH_DATA			2	// ���
#define SHIFT_DATA			3	// �� Shift

//2013,1106
#define TEST_SITE_CNT			5
#define SITE_COK_CNT			12
#define SITE_SOCKET_CNT			12
#define INSERT_CNT				3
#define MAX_MODULE				2
#define MAX_BUFFDVC				2

#define HOOKCLAMP_CNT			3
#define LDCLAMP_CNT				4
#define BUFFER_CNT				8


#define TSITE_COK_CNT		60	//2013,1106
#define TSITE_SOCKET_CNT	12
#define TSITE_INSERT_CNT	15//30    15*4
#define COK_TYPE_CNT		6


#define CONNECT_NO				0
#define CONNECT_YES				1

#define MC_OFF_LINE				0
#define MC_ON_LINE_LOCAL		1
#define MC_ON_LINE_REMOTE		2
//////////////////////////////////////////////////////////////////////////
#define D_INFOSIZE			4		//����� ������ ����Ұ���..
#define D_EXIST				0		//���� ���� ����
#define D_BIN				1		//�� ��� ����
#define D_RE_CNT			2		//����Ʈ�� Ƚ�� ����
#define D_SCR_BIN			3		//ȭ�鿡 ǥ���� �� ��� ����
// ==============================================================
enum ENUM_DEVICE_TYPE
{
	DT_25EVO,
	DT_25PRO,
	DT_MSATA,
	DT_M2,
	DT_LAPTOP,
};

enum GTRAY_SITE
{
	SITE_DENSITY,
	SITE_BARCODE1,
	SITE_BARCODE2,
	SITE_TOP_VISION,
	SITE_UNLOAD,
	SITE_ELV,
	SITE_CONV,
	SITE_ROBOT,
};

enum NETCLIENT
{
	CLS_ECSERVER	= 0,
	CLS_BOTTOM,
	CLS_8570,
	CLS_NEXT,
	CLS_FORMAT,
	CLS_OTHERS,
	CLS_BCR_PRINTER1,
	CLS_BCR_PRINTER2,
	CLS_BCR_PRINTER3,
	CLS_BCR_PRINTER4,
	CLS_VIS_DENSITY,
	CLS_VIS_BARCODE,
	CLS_VIS_TOP,
	CLS_VIS_BTM,
	CLS_GMS, //kwlee 2016.0821
	CLS_MAX_CLIENT,
};

enum NETSERVER
{
	SVR_FRONT,
	SVR_NEXT,
	SVR_PRINTER1,
	SVR_PRINTER2,
	SVR_PRINTER3,
	SVR_PRINTER4,
	SVR_VISION1,
	SVR_VISION2,
	SVR_VISION3,
	SVR_VISION4,
};


enum PICKERJOBTYPE
{
	PLACE,
	PICK,
};

enum ENUM_INIT_SITE
{
	INIT_TOP_IDBUFFER,
	INIT_BTM_IDBUFFER,
	INIT_IDBUFFER_EL,
	INIT_DENDITY_FEEDER,
	INIT_DENDITY_ROBOT,
	INIT_BARCODE_FEEDER,
	INIT_BARCODE_ROBOT,
	INIT_ROLLER_ROBOT,
	INIT_TOP_VISION,
	INIT_UNLOAD_ROBOT,
	INIT_UNLOAD_CONVEYOR,

	MAXSITE,
};

enum BUFFERTYPE
{
	BTBUFFER=0,
	BTBOX,
};

enum TOPBUFFERPOSTYPE
{
	TOPBPOS12=0,
	TOPBPOS34,
	TOPBPOS56,
	TOPBPOS78,
	TOPMAX_BUFFER_POS,
};

enum BTMBUFFERPOSTYPE
{
	BTMBPOS12=0,
	BTMBPOS34,
};
///////////////////////////////////////

#define MAX_SITE_INFO		13

///////////////////////////////////////
enum NET_RECEIVED
{
	NR_NONE,
	NR_WAITING,
	NR_RECEIVED,
	NR_FAIL,
};

enum NET_VISION_RECEIVED
{
	NVR_NONE,
	NVR_PASS,
	NVR_FAIL,
};

enum EFB
{
	FB_NONE,
	FORWARD,
	BACKWARD,
};

enum RDPP
{
	RDP_NONE,
	RDP_PICK,
	RDP_PLACE,
};

enum EUD
{
	FU_NONE,
	FU_DOWN,
	FU_UP,
};

enum ENUM_STEP_CYL
{
	ESTEP_CYL_START=0,
	ESTEP_CYL_MOVE=10,
	ESTEP_CYL_CHK=20,
	ESTEP_CYL_FINISH=30,
};
enum ENUM_ROLLER_ROBOT_INIT
{
	ERRI_START,
	ERRI_CHECK_ROBOT_CHK,
	ERRI_ROLLING_BACK,
	ERRI_ROLLING_BACK_CHK,
	ERRI_HOMECHK_ROLLING1,
	ERRI_HOMECHK_WAIT,
	ERRI_HOMECHK_DONE,
	ERRI_HOMECHK_ROLLING2,
	ERRI_HOMECHK_ROLL,
	ERRI_HOMECHK_ROLL_SAFETY,
	
	ERRI_FINISH,
};

enum ENUM_ROLLING_SITE
{
	ERS_1 = 0,
	ERS_2,
	ERS_3,
};

enum ENUM_ROLLING_LR_POS
{
	ERLP_LEFT = 0,
	ERLP_RIGHT,
};

enum ENUM_HOOK_FWDBWD_SITE
{
	EHS_HFB_LD1,
	EHS_HFB_LD2,
};

enum ENUM_LDCLAMP_SITE
{
	EHS_LCS_LD12,
	EHS_LCS_LD34,
	EHS_LCS_LD56,
	EHS_LCS_LD78,
};

enum ECW
{
	ECW_NONE,
	ECW_WORK,
};

enum ENUM_COMM_STEP
{
	ECOMM_NONE,
	ECOMM_START,
	ECOMM_CONNECT,	// jtkim	tcp/ip ������� üũ
	ECOMM_CONNECT_CHK,		// jtkim    tcp/ip �����û 
	ECOMM_CONNECT_WAIT,
	ECOMM_INSP,			// jtkim	barcode print 
	ECOMM_INSP_COM,		// jtkim	label ����Ϸ� üũ 
	ECOMM_INSP_COM_WAIT,	
	ECOMM_READY,
	ECOMM_MOVE,
	ECOMM_RECV,
	ECOMM_RECV_RETRY,
	ECOMM_FINISH,
};

enum EBPO //ENUM_BCR_PRINT_OUT
{
	EBPO_NONE,
	EBPO_WORK,
};

enum ENUM_BCROUT_STEP
{
	EBOS_NONE=0,
	EBOS_START=10,
	EBOS_CONNECT=20,	// jtkim	tcp/ip ������� üũ
	EBOS_CONNECT_CHK=30,		// jtkim    tcp/ip �����û 
	EBOS_CONNECT_WAIT=40,
	EBOS_PRINT=50,			// jtkim	barcode print 
	EBOS_PRINT_COM=60,		// jtkim	label ����Ϸ� üũ 
	EBOS_PRINT_COM_WAIT=70,
	EBOS_MOVE=80,
	EBOS_FINISH=100,
};

enum ENUM_VISION_POS
{
	EVP_DENSITY=0,
	EVP_BARCODE,
	EVP_TOP_POS,
	EVP_BTM_POS,
};

//enum idbuffer_move_info_shift //id buffer�� �̵��ϸ鼭 ������ ������ ���� �� �����ϸ鼭 ����Ʈ�Ѵ� 
//{	SHIFT_IDBUFF_INPUT_INDEX = 0, //2014.1002
//
//	SHIFT_IDBUFF_INDEX_DENSITY,
//	SHIFT_IDBUFF_INDEX_BCR1,	
//	SHIFT_IDBUFF_INDEX_BCR2,
//	SHIFT_IDBUFF_INDEX_TOP,
//	SHIFT_IDBUFF_INDEX_ULD,
//
//	SHIFT_IDBUFF_INDEX_ULD_SEND,
//	SHIFT_IDBUFF_INDEX_ULD_RECV,
//
//	SHIFT_IDBUFF_SITE_ALL_CHK
//};

#define RCVY_MAX_SITE		20

enum RECOVERY_SITE
{
	RCVY_DENSITY_RBT		= 0,
	RCVY_BARCODE1			= 1,
	RCVY_BARCODE2			= 2,
	RCVY_TOPVISION			= 3,
	RCVY_ULDROBOT			= 4,
	RCVY_ULDCONVEYOR		= 5,


};

#define REQ_FREE_		0
#define REQ_ACCEPT_		10

#define PORT_BCR_LSSD_		1
#define PORT_BCR_RSSD_		2
#define PORT_BCR_TRIN_		3
#define PORT_BCR_TROUT_		4
#define PORT_BCR_MANUAL_	5

#define BIN_CLEARBIN			-1
#define BIN_PASS				1
#define BIN_REJECT				2
#define BIN_HTO					3
#define BIN_NTO					4
#define BIN_BTO					5
#define BIN_RETEST				6
#define BIN_BP					7
#define BIN_ALL					10

#define MAIN_BUFFER_DSP			34
#define MAIN_RETEST_DSP			35
#define MAIN_REJECT_DSP			36
#define MAIN_LOB_TRAY_DSP		37
#define MAIN_TRAY_DSP			38
#define MAIN_PICKER_INFO_DSP	39
#define MAIN_CUSTOMER_DSP		40
#define MAIN_AIR_BLOW			67		

#define MC_STOP					0
#define MC_RUN					1
#define MC_ALARM				2
#define MC_WARNING				3
#define MD_IDLE					4

enum LOG_TYPE
{ 
	LOG_OPERATION = 0,
	LOG_TESTINTERFACE,
	LOG_TCPIP,
	LOG_MACHINE,
	LOG_DEBUG,
	LOG_BARCODE,
	LOG_TIME,
	LOG_AUTOSOCKETOFF,
	LOG_WORK,
	LOG_ADJUSTMENT,
	LOG_HISTORY,
	LOG_PICK_FAIL,
	LOG_RUN_STOP,
	LOG_MOTOR,
	LOG_DISABLE,
	LOG_TEST,
	LOG_UPH,
	LOG_UPH_TOT,
	LOG_REJECT,
	LOG_COMM,
	LOG_ERROR,
	LOG_EVENT,
	LOG_MAT,
	LOG_PRODUCT,
	LOG_GMS, //kwlee 2016.0821
	LOG_TOTAL = 99
};

// *****************************************************************************
// ����� ���� �޽��� ID ����                                                   
// *****************************************************************************
#define WM_FORM_CHANGE				WM_USER+200   // ȭ���� ��ȯ�� �� �ش� ��ȯ ���� ������ �����ϱ� ���� ����� ���� �޽��� 
#define WM_STATUS_CHANGE			WM_USER+201   // Ÿ��Ʋ �� ȭ������ ���۵� �޽��� ��½�Ű�� ���� ����� ���� �޽��� �߰� 
#define WM_LIST_DATA				WM_USER + 6   // ��� �޽��� ��� ����Ʈ ��ȭ ���ڿ� 

#define WM_DATA_SEND				WM_USER + 7   // Data�� �����ϱ� ���� ȭ�鿡�� ������ �����ϱ� ���� ������ ����� ���� �Լ�
#define WM_WORK_END					WM_USER + 8   // �׽�Ʈ �۾� �Ϸ� �� ������ ���� ȭ�鿡 ��½�Ű�� ���� ����� ���� �޽��� �߰� 
#define WM_SCRAP_DSP				WM_USER + 9

#define WM_BASIC_APPLY				WM_USER + 10  // BASIC DATA�� APPLY ��Ű�� ���� ����� ���� �޽��� �߰� 
#define WM_MAINTENANCE_APPLY		WM_USER + 11  // Maintenance DATA�� APPLY ��Ű�� ���� ����� ���� �޽��� �߰�
#define WM_TESTREFERENCE_APPLY		WM_USER + 12
#define WM_INTERFACE_APPLY			WM_USER + 13
#define	WM_WAITTIME_APPLY			WM_USER + 14  // Wait Time DATA�� APPLY ��Ű�� ���� ����� ���� �޽��� �߰� 

#define	WM_MOTORTEACH_APPLY			WM_USER + 15
#define	WM_SHIFTER_APPLY			WM_USER + 16
#define	WM_MOTORSPEED_APPLY			WM_USER + 17

#define WM_SERIAL_PORT				WM_USER + 18
#define WM_NETWORK_MSG				WM_USER + 19

#define WM_MAINFRAME_WORK			WM_USER + 20
#define WM_WORK_MSG					WM_USER + 21

#define DIAGNOSE_START				WM_USER + 22
#define DIAGNOSE_END				WM_USER + 23

#define SELF_DIAGNOSE_END			WM_USER + 25
#define	WM_MAIN_EVENT				WM_USER + 26
#define WM_TRACKOUT_DSP				WM_USER + 27

#define WM_RECEIVED_NEW_LOT			WM_USER + 36
#define WM_DRAW_LOT_TIME			WM_USER + 37
#define WM_DRAW_WORK_SITE			WM_USER + 38

#define	WM_MAIN_XEVENT				WM_USER + 88
#define WM_COMM_WORK				WM_USER + 99


enum ENUM_WM_MESSAGE
{
	WM_DRAW_UI_MAIN					= WM_USER + 39,
	WM_DRAW_DATA_MAIN,
	WM_DRAW_DATA_LOT,
	WM_DRAW_DATA_TESTSITE,
	WM_MOTOR_COMPLETION,
	WM_SOCKET_ACCEPT,

	WM_INIT_BTN,

	WM_CHANGE_VIEW_TYPE,
	WM_DRAW_DATA_XGEM,
};

enum ENUM_DRAW_UI_MAIN
{
   // 20131202

	EDDC_SITE,
	EDDC_COKSTACKER,
	
	EDDT_INIT,
	EDDT_DVC_INIT,
	EDDT_REJ_FLOOR,
	EDDT_SEL_TRAY,	
	EDDT_BINTRAY_0,
	EDDT_BINTRAY_1,
	EDDT_BINTRAY_2, //ybs
	
	EDDT_CONVV,
	EDDT_LOAD,
	EDDT_BCR,
	EDDT_LDELV,
	EDDT_ULDELV,
	EDDT_UNLOAD,
	EDDT_UNLOAD_PLACE,
	EDDT_UNLOAD_ACONV,
	EDDT_UNLOAD_BCONV,
	EDDT_RETEST,
	
	EDDR_PICKER,
	EDDR_SORTER_PICKER,
	
	EDDS_TESTSITE,
	EDDS_VIDEO,
	
	EDDN_NETUSABLE,
	
	//
};

enum ENUM_CHANGE_VIEW_TYPE
{
	ECVT_TESTSITE,
	ECVT_MODULE,
};

enum ENUM_NET_STATE
{
	ENS_NONE,
	ENS_RECEIVED,
	ENS_SENDED,
	ENS_RECV_RPY,
};
#define MAX_BUF_LEN			4095

struct st_other_param 
{
	CString str_op_msg;			// ����Ʈ ȭ�� ��� ���� ���� �޽��� ���� ����
	CString str_normal_msg;		// ����Ʈ ȭ�� ��� ���� ���� �޽��� ���� ����
	CString str_abnormal_msg;	// ����Ʈ ȭ�� ��� ���� ���� �޽��� ���� ����
	
	CString str_fallacy_msg;	// ���� �޽��� ��ȭ ���� Ÿ��Ʋ ���� ����
	CString str_typing_msg;		// Ű���� ��ȭ ���� Ÿ��Ʋ ���� ����
	
	CString str_pass_level;		// ��ȣ ���� ���� ����
	CString str_password;		// ��ȣ ���� ����
	
	CString str_parent_menu;	// �ָ޴� �̸� ���� ����
	
	char c_normal_msg[MAX_BUF_LEN];
	char c_abnormal_msg[MAX_BUF_LEN];
	// jtkim �߰� [20120306]
	char c_op_msg[MAX_BUF_LEN];
	
	////////////////////////////////2K10/02/09/ViboX////////////////////////////////////////
	int		n_prev_step[100];			// ���� step (���� �Ǿ����� ���� ����)
	CString	str_history_step[100];		// step_history �� 50���� �ش��ϴ� step�� ����
	CString str_last_change_date[100];	// ���� step���� ����Ǵ� ������ �ð�
};
extern  st_other_param  st_other;

typedef struct st_material_info
{
	int  nExist_IDBUF;
	char chData_IDBUF[100];
	
	int  nExist_SSD;
	char chData_SSD[100];
}st_material;

struct tagBCR_PARAM
{
	st_material	stMat[2];	// �Ѳ����� �о�� �� ���簡 �ִ� 2����
};
extern tagBCR_PARAM	stBCR[5];

enum
{
	MSG_EXIST,
	MSG_EMPTY,
};

enum SOCKET_CLIENT
{
	CLIENT_CONNECT,
	CLIENT_CLOSE,
	CLIENT_SEND,
	CLIENT_REV,
	// ���̸� �߰� [2013.11.27]
	CLIENT_RECONNECT,
	CLIENT_ACCEPT        =5, //kwlee 2016.0821
};

enum SOCKET_SERVER
{
	SERVER_CONNECT,
	SERVER_CLOSE,
	SERVER_SEND,
	SERVER_REV,
	SERVER_CLIENT_COMM,
};

// ���̸� �߰� [2014.08.14]
enum COMM_PARAM
{
	REQ_NONE_,
	REQ_CALL_,
    REQ_STOP_,
	REPLY_ERROR_,
	REPLY_CORRECT_,
};

#define COMM_TIME_OUT				5000

#define MES_LOT_CLOSE 0
#define MES_PEBAG_CHECK 1
#define MES_BRAND_PEBAG_CHECK 2
#define MES_PEBAG_COMPLETE 3
#define MES_BOAT_ID_MODIF 4
#define MES_BRAND_DTBT_LABEL_ISSUE 5
#define MES_BRAND_WEIGHT_SBOX_ISSUE 6
#define MES_LBOX_ISSUE 7
#define MES_AUTO_SHIP 8
#define MES_PROD_SERIAL_INFO 9
#define MES_BOAT_ID_INFO 10
#define MES_SBOX_INFO 11
#define MES_PACKING_MASTER_INFO 12
#define MES_PK_XCLOSE 13
#define MES_TOOL_CHANGE 14
#define MES_TOOL_CHECK 15
#define MES_BRAND_DENSITY_LABEL_CCS 16
#define MES_BRAND_DTBT_LABEL_CCS 17
// ���̸� �߰� [2014.12.14]
#define MES_BOAT_ID_MODIF_LIN_		18
#define MES_BOAT_ID_MODIF_RIN_		19
#define MES_BOAT_ID_MODIF_LOUT_		20
#define MES_BOAT_ID_MODIF_ROUT_		21
#define MES_BOAT_ID_MODIF_LCNG_		22
#define MES_BOAT_ID_MODIF_RCNG_		23
#define MES_BRAND_DTBT_LABEL_ISSUE_L_ 24
#define MES_BRAND_DTBT_LABEL_ISSUE_R_ 25
#define MES_REWORK_LABEL_CCS_INFO	26

#define MAX_MSG_CNT		30
// ���̸� �߰� [2014.12.13]
#define MES_TIME_OUT				20000

//kwlee 2016.0821
#define WAIT_CONNECT					5000
#define WAIT_RCV						30000
#define WAIT_CLOSE						300
// *****************************************************************************
//  Main Screen ��¿� �޼��� ����                                              
// *****************************************************************************
enum ENUM_MAIN_SCR_MSG//2014.1029 //2014,1217 ysj 
{
	MAIN_IDBUFF_INPUT_INDEX = 0,
	MAIN_IDBUFF_INDEX_DENSITY,
	MAIN_IDBUFF_INDEX_BCR1,
	MAIN_IDBUFF_INDEX_BCR2,
	MAIN_IDBUFF_INDEX_TOP,
	MAIN_IDBUFF_INDEX_ULD,
	MAIN_INDEXTIME,
	MAIN_TIMEINFO,
	MAIN_COUNTINFO,
	MAIN_IDBUFF_INDEX_ULD_BTM,
	MAIN_IDBUFF_INDEX_ULD_CLAMP,
	MAIN_IDBUFF_INDEX_ULD_LOAD, 
	MAIN_IDBUFF_INDEX_ULD_UNLOAD,
	MAIN_IDBUFF_INDEX_ULD_NEXT, 
	MAIN_LOTINFO,
	MAIN_ANI_MOVE_DISPLAY,
};


// *****************************************************************************
#define VARIABLE_INIT		0

#define GMS_PORT			1
//////////20131115
#define BCR_PORT            2
#define BCR_PORT2           3
#define BCR_PORT3           4
#define BCR_PORT4           5
#define BCR_PORT5           6
#define BCR_PORT6           7

#define MAX_PORT			3

//////////20131115
#define COM_PORT			0
#define COM_BAUDRATE		1
#define COM_DATA			2
#define COM_STOP			3
#define COM_PARITY			4
//////////

#define NETWORK_CLIENT_1		1

#define COM_ERROR			-1		// ���� �޽���


#define IO_OFF				0
#define IO_ON				1

#define TMR_IO_CHECK				9

// �޴��� ȭ�鿡�� ����Ѵ�.

#define HOMING				1
#define MOVING				2
#define POS_MOVING			4

// ******************************************************************************
// ��� ���� ���� �� �ʿ��� �޽��� ����                                          
// ******************************************************************************
#define dSTOP			0
#define dRUN			1
#define dJAM			2
#define dLOTEND			3
#define dINIT			4
#define dWARNING		5
#define dLOCK			6
#define dSELFCHECK		7
#define dMAINT			8
#define dWAIT			9	// �������ε� ���簡��� �� ��
#define dREINSTATE		10
#define dRESTORE		11 //2013,1023

#define eWARNING		0
#define eRUNNING		1
#define eSTOP			2
#define eERROR			3

// *****************************************************************************
//  Title Bar ��¿� �޼��� ����                                                
// *****************************************************************************
#define FORM_NAME			1
#define MACHINE_STATUS		2
#define RETEST_MODE			3
#define DEVICE_MODE			4
#define LEVEL_MODE			5
#define FRONT_KEY_MODE		6
#define REAR_KEY_MODE		7
#define ONLINE_MODE			8
#define EMPTYTRAY_MODE		9
#define SMEMA_ONOFF			9
#define CONV_MODE			10

#define INTERFACE_MODE		10
#define BARCODE_MODE		11
#define SOCKETOFF_MODE		12
#define TESTDUMP_MODE		13
#define DEVICE_NAME			14
#define TAMS_ONLINE			15 //james 2010.0922 TAMS online �Ǵ� Off line�� ���Ѵ� 
#define MES_CONNECT_STATUS  16
// ���̸� �߰� [2013.09.25]
#define HOST_CNNT_STATUS	17
#define BCR_READ_MODE       18
#define XGEM_MODE			19

// *****************************************************************************
//  List Box ��¿� �޼��� ����                                                 
// *****************************************************************************
#define RECEIVE_MSG			1
#define SEND_MSG			2
#define NORMAL_MSG			3
#define ABNORMAL_MSG		4

#define MACHINE_INFO		5
#define DEVICE_INFO			6

#define TCPIP_MSG			7

#define	EQP_MSG				8

#define SOCKETCLOSE			14

// ******************************************************************************
// I/O ��� ���� �� ��Ʈ �ִ� ���� �����Ѵ�                                      
// ******************************************************************************
#define MAX_IN			716
#define MAX_IO			716

// ******************************************************************************
//  MOTOR ���� ���� ���� �����Ѵ�                                                
// ******************************************************************************
#define PLUS			1
#define MINUS			0

// ******************************************************************************
// ���� �׽�Ʈ �� ���� ���� ���� �����Ѵ�                                        
// ******************************************************************************
#define TESTSIZE		10

// ******************************************************************************
// SOCKET DATA����.
#define LOADTRAY_ROW	1
#define LOADTRAY_COL	4
#define UNLOADTRAY_ROW	1
#define UNLOADTRAY_COL	4
#define REJECTTRAY_ROW	5
#define REJECTTRAY_COL	5

#define BUFFERMAXSIZE	20		// ���� ������ ��� ���� ����[0][x] �� ��� ��/�� ����[1][x]�� ������ 

#define BIN_GOOD		1
#define BIN_REJECT		2

//MOT Speed Setting  
#define	MOT_SPD_VEL			0
#define	MOT_SPD_ACC			1
#define MOT_SPD_DEC			2
#define MOT_SPD_JOG			3
#define MOT_SPD_ORG			4
#define MOT_SPD_FEEDRATE	5
#define MOT_SPD_INTERACC	6

//motor sensor 
#define MOT_SENS_HOME		0
#define MOT_SENS_ELM		1
#define MOT_SENS_ELP		2
#define MOT_SENS_SD			3 //slow down sensor 

#define MOT_RTY_CNT			4	//�Ľ��� ����� ���� ������ �� �õ��ϴ� Ƚ��

// #define MOT_TIMEOUT			90000   //1���� time out�� ������ �����Ѵ�  //Ȩ üũ�� ��� 

//������ �޼��� �����û�� 
#define MOT_ERR_MSG			1
#define MOT_ERR_CODE		2

///////////////////////////////////
// IO Board Define
//////////////////////////////////

#define RET_PROCEED		0
#define RET_GOOD		1
#define RET_ERROR		2
#define RET_RETRY		3
#define RET_DOOROPEN	4		// Door Open�� �Ǿ� ����. 2K6/06/20/ViboX
#define RET_REJECT		5
#define RET_SKIP		6

///////////////////////////////////////////
// Control Board(IO, Motor) Board Define
///////////////////////////////////////////

#define HANDLER_BACKUP_DATA_RW	29
#define DATA_READ    0
#define DATA_WRITE   1

// Į�� ����
#define SKY_C					RGB(187, 250, 255)
#define SKY_D					RGB(0, 255, 255)
#define SKY_L					RGB(128, 255, 255)
#define NOR_C					RGB(164, 164, 164)
#define NOR_L					RGB(190, 190, 190)
#define RED_C					RGB(255, 0, 0)
#define RED_L					RGB(255, 150, 150)
#define RED_D					RGB(80, 20, 0)
#define RED_A					RGB(200, 0, 0)
#define BLUE_C					RGB(0, 0, 255)
#define BLUE_A					RGB(0, 0, 200)
#define WHITE_C					RGB(255, 255, 255)
#define BLACK_C					RGB(25, 1, 1)
#define BLACK_L					RGB(62, 55, 55)
#define YELLOW_C				RGB(255,255,0)
#define YELLOW_D				RGB(128, 128, 0)
#define YELLOW_DD				RGB(64, 64, 0)
#define YELLOW_L				RGB(255, 255, 128)
#define GREEN_C					RGB(0,255,0)
#define GREEN_B					RGB(0,255,64)
#define GREEN_L					RGB(150,255,150)
#define GREEN_D					RGB(0,100,20)
#define DSERBLE_BC				RGB(210,210,230)
#define TEXT_BC					RGB(220,230,210)
#define OK_BC					RGB(0, 0, 255)
#define NG_BC					RGB(255, 0, 0)
#define RESULT_BC				RGB(40, 1, 1)
#define ORANGE_C				RGB(0xFF, 0x68, 0x20)
#define ORANGE_L				RGB(255, 200, 128)
#define BLACK					RGB(0, 0, 0)
#define BLUE_D					RGB(0, 0, 128)
#define BLUE				    RGB(0, 0, 255)
#define GRAY_C					RGB(192, 192, 192)
//#define BLUE_L					RGB(150, 150, 255)
#define BLUE_L					RGB(124, 139, 252)
#define ON_C					RGB(0, 255, 0)
#define OFF_C					RGB(0, 150, 0)
#define NG_C					0x0000FF
#define OK_C					0xFF00
#define BLACK_GC				0x00
#define YELLOW_GC				0xFFFF
#define TEST_BC					RGB(194, 231, 150)
#define IN_BC					RGB(204, 153, 255)
#define PINK_D					RGB(252, 233, 218)
#define COL_PUPLE				RGB(204,102,204)

#define COL_COK_0				RED_L
#define COL_COK_1				ORANGE_L
#define COL_COK_2				YELLOW_L
#define COL_COK_3				GREEN_L
#define COL_COK_4				BLUE_L
#define COL_COK_5				COL_PUPLE


//Grid ���� 
#define DATE					0
#define EDIT					1
#define COMBO					2
#define BUTTON					3
#define STATIC					4
#define TIME					5
#define PERCENT					6
#define CHECK1					7
#define NUMBER					8
#define NUMBER1					9

#define IO_IN					1
#define IO_OUT					0
#define IO_NONE					2

// Client ���� Event
#define CLIENT_REV_MSG			WM_USER+1103
//==================================================================//
// ���� ����� ���� �߰���
// ���̸� �߰� [2013.11.12]
//==================================================================//
#define WM_CLIENT_MSG			WM_USER +500
#define WM_CLIENT_MSG_1			WM_USER +500//CLS_ECSERVER����
#define WM_CLIENT_MSG_2			WM_USER +501//CLS_BOTTOM, 

#define WM_CLIENT_MSG_3			WM_USER +502//CLS_8570 
#define WM_CLIENT_MSG_4			WM_USER +503//CLS_NEXT 
#define WM_CLIENT_MSG_5			WM_USER +504//CLS_FORMAT 
#define WM_CLIENT_MSG_6			WM_USER +505//CLS_OTHERS 
#define WM_CLIENT_MSG_7			WM_USER +506//CLS_BCR_PRINTER1 
#define WM_CLIENT_MSG_8			WM_USER +507//CLS_BCR_PRINTER2 
#define WM_CLIENT_MSG_9			WM_USER +508//CLS_BCR_PRINTER3
#define WM_CLIENT_MSG_10		WM_USER +509//CLS_BCR_PRINTER4
#define WM_CLIENT_MSG_11		WM_USER +510//Denduty
#define WM_CLIENT_MSG_12		WM_USER +511//bcr
#define WM_CLIENT_MSG_13		WM_USER +512//top 
#define WM_CLIENT_MSG_14		WM_USER +513//btm 

 
#define WM_ZEBRA_CLIENT_MSG_1	WM_USER +506
#define WM_ZEBRA_CLIENT_MSG_2	WM_USER +507
#define WM_ZEBRA_CLIENT_MSG_3	WM_USER +508
#define WM_ZEBRA_CLIENT_MSG_4	WM_USER +509

#define WM_SERVER_MSG			WM_USER +550
#define WM_SERVER_MSG_1			WM_USER +550
#define WM_SERVER_MSG_2			WM_USER +551//OnZebraPrint_Server_1
#define WM_SERVER_MSG_3			WM_USER +552//OnZebraPrint_Server_2
#define WM_SERVER_MSG_4			WM_USER +553//OnZebraPrint_Server_3
#define WM_SERVER_MSG_5			WM_USER +554//OnZebraPrint_Server_4
#define WM_SERVER_MSG_6			WM_USER +555//OnLabel_Server
#define WM_SERVER_MSG_7			WM_USER +556//OnBarcode_Server
#define WM_SERVER_MSG_8			WM_USER +557//OnTop_Server
#define WM_SERVER_MSG_9			WM_USER +558//OnBottom_Server
#define WM_SERVER_MSG_10		WM_USER +559
#define WM_SERVER_MSG_11		WM_USER +560
#define WM_SERVER_MSG_12		WM_USER +561

#define WM_ZEBRA_SERVER_MSG_1	WM_USER +551
#define WM_ZEBRA_SERVER_MSG_2	WM_USER +552
#define WM_ZEBRA_SERVER_MSG_3	WM_USER +553
#define WM_ZEBRA_SERVER_MSG_4	WM_USER +554

// *****************************************************************************
//  ��Ʈ�� �޼��� ���� ����ʿ��� BPC�� ������ �޼���.
// *****************************************************************************
#define NW_TRACK_IN						95
#define NW_PCBOX_TIMEOUT				96
#define NW_PCBOX_OFF					12
#define NW_TRACK_OUT					97
#define NW_BPC_BUFFER_READY				151
#define NW_BPC_BUFFER_IN				152
// *****************************************************************************

////////////////////////////////////////////////////////////////////////////////
// AMT8480 ����
////////////////////////////////////////////////////////////////////////////////
#define NW_LOT_DISPLAY					25		// ������ �ش� LOT�� ������ ��û�Ͽ�, �̸� �������� Test ��� ���� �� ���� ���� Ȱ��
#define NW_LOT_DISPLAY_RPY				46		
#define NW_DELETE_SCRAP					109		// ������ ����� �ҷ� ������ ���� ��.
#define NW_DELETE_SCRAP_RPY				110
#define NW_SORTER_LOT_END				111		// Sorter���� ������ Lot End�� ���� ���� ó���� ��.
#define NW_SORTER_LOT_END_RPY			112
// *****************************************************************************
//  ��Ʈ�� �޼��� ���� BPC�ʿ��� ���� ������ �޼���.
// *****************************************************************************
#define NW_TEMP_CONTROL					93
#define NW_PCBOX_START					31
#define NW_PGM_START					60
#define NW_PCBOX_END					32
// *****************************************************************************
// *****************************************************************************
//  ��Ʈ�� �޼��� ���� BPC<->EPC ���� �ְ�޴� �޼���.
// *****************************************************************************
#define NW_PCBOX_STATUS					98
#define NW_PCBOX_DOWN					99
#define NW_LOT_CANCEL					30

#define NW_PCBOX_STATUS_SEND			102
#define NW_PCBOX_DOWN_SEND				103
#define NW_LOT_CANCEL_SEND				104
// *****************************************************************************

// *****************************************************************************
//  ��Ʈ�� �޼��� ����. ��� ���.
// *****************************************************************************
#define NW_BUFFER_READY					201
#define NW_BUFFER_IN					202
#define NW_RETEST_REQ					219

#define NW_SOCKET_CHK_SEND				214
#define NW_BUFFER_READY_SEND			215
#define NW_BUFFER_IN_SEND				216

#define NW_BUFFER_IN_RPY				217
#define NW_BUFFER_READY_RPY				218
#define NW_RETEST_REQ_RPY				220
// *****************************************************************************

#define NW_TRACK_IN_RPY					203
#define NW_PCBOX_TIMEOUT_RPY			204
#define NW_PCBOX_OFF_RPY				206
#define NW_LAST_RETEST_RPY				207
#define NW_TRACK_OUT_RPY				208		// ������� EPC�� �亯

#define NW_PCBOX_STATUS_RPY				209
#define NW_PCBOX_DOWN_RPY				210
#define NW_LOT_CANCEL_RPY				211
#define NW_VIDEO_SELECT_RPY				213		// ������� ���� ������ �κ�.

#define NW_BOOT_OK						221
#define NW_NEW_LOT_IN					222
#define NW_NEW_LOT_IN_SEND				223
#define NW_NEW_LOT_IN_RPY				224

#define NW_LOT_NAME						225
#define NW_LOT_NAME_RPY					226

#define NW_BLOT_COUNT					231
#define NW_BLOT_COUNT_RPY				232

#define NW_BPC_BUFFER_READY_RPY			233
#define NW_BPC_BUFFER_IN_RPY			234

#define NW_LABEL_INFO					301		// ������ �ش� LOT�� ������ ��û�Ͽ�, �̸� �������� Test ��� ���� �� ���� ���� Ȱ��
#define NW_LABEL_INFO_RPY				302		// ������ �ش� LOT�� ������ ��û�Ͽ�, �̸� �������� Test ��� ���� �� ���� ���� Ȱ��

#define NW_VERSION_UPDATE_RPY			990
#define NW_INVALID_FUNCTION				999


// ���ϴ� VLCA/320/420�� ��� �������ݵ�.
// *****************************************************************************
//  ��Ʈ�� �޼��� ���� ����ʿ��� BPC�� ������ �޼���.
// *****************************************************************************
#define NW_LOT_START_RPY				1
//#define NW_LOT_CANCEL_RPY				2
#define NW_PCBOX_START_RPY				3
#define NW_PCBOX_END_RPY				4
#define NW_PCBOX_CHANGE_RPY				5
#define NW_ENABLE_RPY					6
#define NW_DISABLE_RPY					7
#define NW_SLOT_MASK_RPY				8
#define NW_LOT_START_ENABLE_RPY			9
#define NW_PCBOX_REMOVE_RPY				10
#define NW_PCBOX_ERROR_RPY				11
#define NW_UNLOAD_COMPT					13
#define NW_CANCEL_END					14
#define NW_LOT_END						15
#define NW_PCBOX_DISABLE				16
#define NW_VIDEO_TIMEOUT				17
#define NW_HOLD_TIMEOUT					18
#define NW_PCBOX_LOT_INFO				19
#define NW_FAIL_INFO_SEND				20
#define NW_FAIL_REGNUMBER_REQUEST		21
#define NW_FAIL_INFO_SERACH				22
#define NW_FAIL_INFO_SAVE				23
#define NW_FAIL_INFO_DELETE				24
#define NW_EQP_LOT_START				26
#define NW_EQP_LOT_CANCEL				27
#define NW_EQP_LOT_END					28
#define NW_PCBOX_OFF_CHECK				100		// ���� �߰���. 2K11/03/02/ViboX
#define NW_POWER_OFF_CHECK_RPY			101
#define NW_EQP_ENABLE_RPY				200
#define NW_EQP_DISABLE_RPY				201
#define NW_EQP_ENABLE					200
#define NW_EQP_DISABLE					201
#define NW_LOT_START					29
#define NW_PCBOX_CHANGE					33
#define NW_ENABLE						34
#define NW_DISABLE						35
#define NW_SLOT_MASK					36
#define NW_LOT_START_ENABLE				37
#define NW_PCBOX_REMOVE					38
#define NW_PCBOX_ERROR					39
#define NW_PCBOX_LOT_INFO_RPY			40
#define NW_FAIL_INFO_SEND_RPY			41
#define NW_FAIL_REGNUMBER_REQUEST_RPY	42
#define NW_FAIL_INFO_SERACH_RPY			43
#define NW_FAIL_INFO_SAVE_RPY			44
#define NW_FAIL_INFO_DELETE_RPY			45
#define NW_EQP_LOT_START_RPY			47
#define NW_EQP_LOT_CANCEL_RPY			48
#define NW_EQP_LOT_END_RPY				49
#define NW_PCBOX_ENABLE					50
#define NW_POWER_CONTROL_ON				71
#define NW_POWER_CONTROL_OFF			72
#define NW_POWER_OFF					82
#define NW_VIDEO_TIMEOUT_RPY			91
#define NW_POWER_OFF_RPY				92

#define MAX_GMS_CHANNEL					8 //kwlee 2016.0821

enum ENUM_WAIT_TIME
{
	E_WAIT_HOOK_CLAMP,
	E_WAIT_HOOK_FWDBWD,
	E_WAIT_DREEL_PAPER_FWDBWD,
	E_WAIT_FEEDER_LOCK,
	E_WAIT_FEEDER_VACUUM,
	E_WAIT_BCR_VACUUM_FWDBWD,
	E_WAIT_BCR_GUIDE_FWDBWD,
	E_WAIT_BCR_GUIDE_UPDOWN,
	E_WAIT_BCR_VACUUM,
	E_WAIT_BCR_EJECT,
	E_WAIT_BCR_PLATE_UPDOWN,
	E_WAIT_BCR_PLATE_VACUUM,
	E_WAIT_BCR_PLATE_EJECT,
	E_WAIT_BCR_REJECT_UPDOWN,
	E_WAIT_BCR_PICK_VACUUM,
	E_WAIT_BCR_PLACE_EJECT,
	E_WAIT_ROLLING_FWDBWD,
	E_WAIT_UNLOAD_PICKER,
	E_WAIT_UNLOAD_VACUUM,
	E_WAIT_CONVEYOR_FWDBWD,
	E_WAIT_CONVEYOR_VACUUM,
	E_WAIT_CONVEYOR_DVC_CHK,
	E_WAIT_CONVEYOR_MOVE,
	E_WAIT_TRIGGER_TIME,
	E_WAIT_BCR_OUT,

	E_WAIT_MAX = 30,
};

enum ENUM_COKINDEX
{
	COKINDEX_GS1,
	COKINDEX_GS2,
	COKINDEX_MSATA,
	COKINDEX_25_REVERSE,
	COKINDEX_25_FRONT,
	MAX_COKINDEX,
};


//==================================================================//
// �α� Ÿ�� ����
// : ���̸� �߰� [2012.02.10]
//==================================================================//
#define LOG_SOCKET_		0x01
#define LOG_SEQ_		0x02
#define LOG_COMM_		0x04
#define LOG_XGEM_		0x08
#define LOG_PGM_		0x10

// ���̸� �߰� [2013.11.28]
#define CONFIG_PATH_BASE_		(CString)"d:\\AMTLOG"
 

#define DOOR_CNT_		4

#define LD_PICKER_			4

#define DATA_TYPE_				2
#define TYPE_FLAG_				0
#define TYPE_SEN_				1

#define WORK_PICK_				0
#define WORK_PLACE_				1
#define WORK_UPDATE_			2


enum
{
	TRACE_PK_RETURN_	= 0,
	TRACE_PK_LOWER_		= 1,
	TRACE_PK_ELEV_		= 2,	// TRACKIN
	TRACE_PK_BTMACCY_	= 3,
	TRACE_PK_SSD_		= 4,
	TRACE_PK_TOPACCY_	= 5,
	TRACE_PK_TRACKOUT_	= 6,
	TRACE_DUMP_RBT_		= 7,
	TRACE_SSD_BUFF_		= 8,
	TRACE_FLIP_RBT_		= 9,
	TRACE_LOAD_RBT_		= 10,
	TRACE_BTMACCY_RBT_	= 11,
	TRACE_TOPACCY_RBT_	= 12,
};

enum
{
	ADUST_NOT_		= 0,
	ADUST_OK_		= 1,
	ADUST_NEED_		= 2,
};

enum
{
	WORK_NONE_			= 0,
	WORK_INPUT_			= 1,
	WORK_AVOID_			= 2,
	WORK_REMOVE_		= 3,
	WORK_READY_			= 4,
	WORK_SUPPLY_		= 5,
	WORK_SUPPLY_OK_		= 6,
	WORK_VAC_OFF_		= 7,
	WORK_VAC_OFF_OK_	= 8,
	WORK_INPUT_CANCEL_	= 9,
	WORK_COMPLETE_		= 10,
};

#define VAR_INIT_			0

typedef struct st_SSD_INFO
{
	// �Ϲ����� Socket Off ������ ����
	int  nIdBuffUsing;	// Id ���� ��� ���� [0:�̻��, 1:���]
	
	int  nWorkCount;	// ������� �۾��� ���� ����
	int  nProductType;	// �۾��ϴ� ���� ����
	int  nNeedTurn;		// Turn �۾� �ʿ����� ����
	
	char chLotId[100];				// Lot ����
	char chPartId[100];				// Part ����
	char chFromConvId[100];			// Ssd �����̾�� ���� ��ǰ ��ȣ
	char chSerialId[100];			// ���� ���񿡼� BCR�� ���� ��ǰ ��ȣ
	char chBuffId_TrackIn[100];		// Id ���� ID
	char chBuffId_TrackOut[100];	// Id ���� ID
	
	int  nIdBuffExist;	// Id ���� ���� ���� [0:������, 1:����]
	int  nBtmAccyExist;	// Bottom Accy ���� ���� [0:������, 1:����]
	int  nSsdExist;		// SSD ���� ���� [0:������, 1:����]
	int  nTopAccyExist;	// Top Accy ���� ���� [0:������, 1:����]
	
	int  nByPass;		// �۾����� Bypass ������ ���������� ���� ���� [0:�۾�����, 1:ByPass]
	int  nLastModule;	// ������ ���������� ���� ���� [0:Default, 1:Lot����, 2:Lot������, 3:Lost���]
	int  nIsAdjust;		// ���Ա⿡�� �䱸�ϴ� ������� �����ߴ��� ���� [0:not Adjust, 1:Adjust, 2:ReAdjust]
}st_SSD;

struct tagPRODUCT_PARAM
{
	int nPicker[DATA_TYPE_][LD_PICKER_];
	
	// �¿� ������ ��쿡�� [0:Left, 1:Right]
	// �ε� ������ ��쿡�� [�������� 0~4]
	st_SSD	stPocket[LD_PICKER_];
};
extern tagPRODUCT_PARAM	stMapPk[13];
// *****************************************************************************
// ȭ�� ���� ���� �⺻ ������ ���� ����ü ���� ����                             
// *****************************************************************************
struct st_handler_param
{
	int n_dryrun_density;
	int n_only_work_bcr1;
	int n_only_work_density;
	int n_without_smema_8580_mc;
	int n_without_barcode_read;
	int n_without_network;
	int n_without_idbuffer;

	int n_without_density_label_rbt;
	int n_without_bcr1_rbt;
	int n_without_bcr2_rbt;
	int n_without_top_vision_rbt;
	int n_without_smema_btm_8580s;
	int n_auto_serial_create;

	/////////////////////////////////////////////////////////////////////////////

	int mn_menu_num;				// �� ȭ�鿡 ������ ȭ�� ��ȣ ���� ���� 
	int mn_alarm_screen;			// ���� �˶� ȭ���� ��µǾ��� �ִ����� ���� ���� ���� ���� 

	BOOL b_program_exit;			// ���α׷��� ���������°��� Ȯ���Ѵ�.
	
	// *************************************************************************
	// ȭ�鿡 ���� �ڵ� ���� ���� ���� ����                                     
	// *************************************************************************
	HWND hWnd;						// ���� ������ �ڵ� ���� ����
	CWnd *cwnd_title;				// Ÿ��Ʋ ��� ȭ�� �ڵ� ���� ����
	CWnd *cwnd_list;				// ����Ʈ ��� ȭ�� �ڵ� ���� ����

	CWnd *cwnd_main;				// ���� ȭ�� �ڵ� ���� ����
	CWnd *cwnd_basic;				// BASIC ȭ�� �ڵ� ���� ����
	CWnd *cwnd_maintenance;			// Maintenance ȭ�� �ڵ� ���� ����
	CWnd *cwnd_testreference;		// Test Reference ȭ�� �ڵ� ���� ����
	CWnd *cwnd_interface;			// Interface ȭ�� �ڵ� ���� ����
	CWnd *cwnd_waittime;			// Wait Time ȭ�� �ڵ� ���� ����
	CWnd *cwnd_init;
	CWnd *cwnd_barcode;
	CWnd *cwnd_rack_info;

	CWnd *cwnd_motorteach;			// motor teaching ȭ�� �ڵ� ���� ����
	CWnd *cwnd_motorspeed;			// Motor Speed ȭ�� �ڵ� ���� ����
	CWnd *cwnd_diagnose;

	CWnd *cwnd_motor;

	CWnd *cwnd_motorAxis;
	CWnd *cwnd_motor_with_io;

	CWnd* cwnd_data_lot;
	CWnd* cwnd_data_testsite;
	CWnd* cwnd_data_xgem;// 2013,1028

	// *************************************************************************		

	// *************************************************************************
	// ��� ���� ���� ���� ���� ����                                            
	// *************************************************************************
	int mn_initial;					// �ʱ�ȭ �۾� �Ϸ� �÷���
	int mn_initial_end;
	int mn_manual;

	int mn_menu_lock;				// �޴� ��� ���� ���� �÷��� 
	int mn_system_lock;				// SYSTEM LOCK ���� �÷���
	int mn_switch_lock;				// Dialog�� �� �ִ� ���� �÷��� (Start Switch Lock)

	CString mstr_pass_level;
	int mn_level_maint;				// ����Ʈ ����(Level 1) ���� �÷���
	int mn_level_teach;				// ƼĪ ����(Level 2) ���� �÷���
	int mn_level_speed;				// ���ǵ� ����(Level 3) ���� �÷���
	int mn_level_admin;				// Admin ����(Level 4) ���� �÷���
	int mn_level_ver;				//2014,0606 ybs

	int mn_init_state[MAXSITE];		// �ʱ�ȭ �Ϸ� �÷���
	int mn_Rcvy_state[RCVY_MAX_SITE];		// �ʱ�ȭ �Ϸ� �÷���
	int mn_initial_error;

	int mn_status;					// ��� �������̳�
	int mn_reinstatement;

	int mn_safety;

	CTimeSpan m_tR;		//Run Time
	CTimeSpan m_tI;		//Idle Time
	CTimeSpan m_tC;		//Lot Change Time
	CTimeSpan m_tJ;		//Jam Time
	CTimeSpan m_tS;		//Stop Time

	CTimeSpan m_tM;		//Maint Time
	CTimeSpan m_tT;		//Test Time
	CTimeSpan m_tPT;	//Prev Test Time
	CTimeSpan m_tIT;	//Index Time
	CTimeSpan m_tPIT;	//Prev Index Time
	CTimeSpan m_tCT;	//Cycle Time
	CTimeSpan m_tPCT;	//Prev Cycle Time
	CTime m_tRef;
	
	CTimeSpan m_tDR;	//Run Time
	CTimeSpan m_tDI;
	CTimeSpan m_tDC;
	CTimeSpan m_tDRB;	//Run Time
	CTimeSpan m_tDRW;	//Run Time
	CTimeSpan m_tDJ;	//Jam Time
	CTimeSpan m_tDS;	//Stop Time
	CTimeSpan m_tDM;	//Maint Time

	int mn_motor_init_check;
	int n_initiailze;

	int mnSerial_Port_Creating[MAX_PORT];

	CString mstrSelectMessage;
	int mnSelectMessage;
	CString mstrRejectMessage;
	int mnRejectMessage;

	CString mstr_lot_name[3];		// ���� ��� �ȿ� �ִ� LOT NAME�� BUFFER_READY���� ������� LOT NAME�� ���Ѵ�.
	int mn_comm_lot_name_chk;

	int mn_virtual_mode;
	int mn_virtual_supply;
	int mn_virtual_idbuffer;
	double md_picker_position[4];
	double md_tray_place_offset[2];
	double md_common_teaching[COMMON_TEACHING_MAX];
	int mn_cokIndex[MAX_COKINDEX];

	int mn_retest_cnt;
	int mn_beat_cnt;
	int mn_AutoSocketOff_Cnt;

	CString str_main_lot;
	CString str_main_part;
	CString str_main_last;
	CString str_main_bypass;
	
	int mn_emptyout_cnt;	
	int mn_emptyin_cnt;
	int mn_emptynext_cnt;
	int mn_buffer_in;
	BOOL mb_rej_3stacker;
	int mn_cok_change;

	int mn_temp_pogo_type;
	int mn_temp_alignBuffer_type;

	//2013,0213
	int mn_cok_chgstate[3];
	int mn_mirror_type;//2016.0510 1th,2th

	int mn_robot_motorX_safety;
	int mn_robot_motorRej_safety;

	//2013,0715
	int mn_fullinline_mode;
	CString m_strProcessID;
	CString m_strRPropEnd;
	int m_iPLotInfo;		// 2013,0910

	int m_bRestore;

	int mn_smema_load;
	int mn_smema_stop;
	int mn_backup_smema[3];

	int mn_smema_front;
	int mn_smema_rear;

	int mn_curr_unload_conv;//A,B
	int mn_curr_back_conv;


	int mn_smema_rear_run;

	int mn_reject[2];
	int mn_unload_cycle;
	int mn_load_cycle;

	int mn_chk_lotend;
	int mn_reworkcnt;//2016.0919

	int nEQ2CIM_SendPpossible;
	
	int mn_lot_label_info;
	int mn_receive;

	int mn_Density;
	int mn_Barcode;
	int mn_top;
	int mn_Bottom;

	int mn_BcrOutAllow1;
	int mn_BcrOutAllow2;

	CString m_strLotID[2];

	CString m_strBcr1BoatID[2];
	CString m_strBcr2BoatID[2];

	CString m_strBcr1Serial[2];
	CString m_strBcr2Serial[2];

	CString m_strBcrBoatID[4];
	CString m_strBcrSerial[4];

	CString m_strLabelCode[4];
	CString m_strRibbonCode[4];

	////2014,1226
	CString m_strDensityLabel[6];
	CString m_strDensityCapa[6];
	CString m_strDistributionLabel[4];
	CString m_strDistributionRibbon[4];
	////

	int mn_Top_Vision[6];
	int mn_Btm_Vision[2];

	CString m_strDensityInfo[6];
	CString m_strBcrInfo[4];

	int mn_pickup_elv[2][2];
	//[0][0] btm -> req [0][1] : ready
	//[1][0] btm -> clamp on ->req [1][1] ; clamp off req
	//btm2 [1][0] -> free   NO�� �ٲٰ� UP �̵� 

	int mn_move_buffer[2][2];//BTM buffer
	//[0][0] btm2 -> req [0][1] : ready
	//[1][0] btm2 -> clamp on ->req [1][1] ; clamp off req
	//btm2 [1][0] -> free   NO�� �ٲٰ� �̵� 

	CString m_strCapa;
	int mn_OutElv_work;

	bool m_bPrint_Pickup[6];
	int mn_front_ready;
	int mn_btm_ready;
	int	mn_d_piclplce;

	int mn_density_viscnt;
	CString m_strNewLot;
	CString m_strVisModel;

	int nCommand[2];
	int nComplete[2];

	int mn_Lotcnt;

	int mn_unloadtact;

	int mn_manual_lable;

	////2015.0114
	int  nModeManual;
	int nDetect_DoorOpen[6];
	////

	long m_lBcrOutTime[4];
	int mn_stdtimetact[10];

	DWORD	m_dwTimeOverDensity[6];

	int m_nTotal;
	CString m_strLabelCapa[100];

	DWORD	m_dwBcrOutTime[4];
	bool m_bBcrTimeOutError[4];

	int mn_8580_top;
	int mn_8580_btm;

	CString m_strAlarmMsg;
	bool m_bstart[4];
	DWORD m_dwJamStartTime;

	int m_nRemote;
	CString m_xgemstrErrMsg;

	CString m_strLogEvent;
	int mn_model_change;

	CString m_strNewPartNmber;

	//barcode //2015.0607
	int m_nBcrRbtResult[2];

	int m_nConformVisAfterModelChange[4];
	int m_nLotServer;

	int m_nRearOut;
	int mn_UnloadOut;
	int mn_safety_area;
	int mn_mute_on;
	int mn_DenRetry;

	int mn_device_type;//2016.1031 backup

} ;
extern  st_handler_param  st_handler;

//kwlee 2016.0821
struct st_gms_param
{
	CString		strValVolt[MAX_GMS_CHANNEL];
	CString		strValRes[MAX_GMS_CHANNEL];
	CString		strEqpID[MAX_GMS_CHANNEL];
	CString		strDateTime[MAX_GMS_CHANNEL];
	CString     strChan[MAX_GMS_CHANNEL];
	CStringArray	ArValVolt[MAX_GMS_CHANNEL];
	CStringArray	ArValRes[MAX_GMS_CHANNEL];
	COleDateTime	oleTime[MAX_GMS_CHANNEL];
	CString strData;
	CString strMsg[2];
	int    Chan;
};
extern st_gms_param st_gms_info;
// *****************************************************************************
//  ���� ���� ����
// *****************************************************************************
struct st_setting_param
{
	int mn_text_r[2][2];
	int mn_text_g[2][2];
	int mn_text_b[2][2];
	
	int mn_grid_r[2][2];
	int mn_grid_g[2][2];
	int mn_grid_b[2][2];

	int n_inputindex_premove_mm_value; //2014.1120 ��� ���� �̵� ���⸦ ������ �ϱ����� �߰� 
};
extern  st_setting_param  st_set;
// *****************************************************************************

// *****************************************************************************
//  ��� ������ Sync ���� ����
// *****************************************************************************
struct st_sync_param
{
	int n_inputindex_moveindex_clamp_exchange_req; //2014.1120 input index�� ���۸� density ��ġ�� ������ ������ move index�� �ͼ� �̸� ���� ���� �� �ֵ��� �÷��׸� ����Ѵ� 
	bool m_bPrint_ready[6];//Density Feeder�� �غ�����

	//ID Buffer [0]*: buffer ���� [1]*:box ����
	int mn_ibuffer_in[2][2];
	int mn_top_ibuffer_work[2][4][2]; //*[4]* ��ġ
	int mn_btm_ibuffer_work[2][2][2]; //*[4]* ��ġ
	int mn_ibuffer_out[2][2];//elevator
	
	int mn_add_fail;
	
	int mn_rbuffer_station[2];		// APCT�� ���� ������ �����.

	int n_scrap_serial;

	int n_loadbuffer_work[4]; //[0]:req [1]:response CTL_READY,CTL_FREE  Conv->Load Buffer
	                             //[1] :   [1][*]                              Load->Elev Buffer
	int n_loadelev_work[4];   //[0]Elev-> load Buffer L_READY,CTL_FREE 
	                          //[1] Load Buffer ����  
	
	int n_loaderpick_work[4];// [0] Pickrbt->Load Elv  [1] = Load Elv -> Pickrbt [2]:elv pos
	
	int n_unloaderplace_work[4];// [0] Pickrbt->UnLoad Elv  [1] = UnLoad Elv -> Pickrbt


	int n_unloadelev_work[2];   //[*]-> 0:Unload Buffer Rbt 1:Unload Elv [*][0]:0->Pcker no,req,ready,exchange   [*][1]: 0:�̵� ��ġ
	
	int n_unloadbuffer_work[4]; //[*]-> 0:Picker Rbt 1:Unload Elv :req [*][0]:0->Pcker no,req,ready,exchange   [*][1]: 0:�̵� ��ġ
	                               //[*][2] => 0:wait(��� �۾� ����), WORK_TSRBT_START(�׽�Ʈ ������), WORK_XYRBT_START(XY �κ�Ʈ ������)




	int n_tsrbt_phbuff_tsmove_req[2][3]; //[*] => 0:left, 1:right PH [*][0]:no,req,ready,exchange, [*][1]:0->test left , 1->test right 
										 //[*][2] => 0:wait(��� �۾� ����), WORK_TSRBT_START(�׽�Ʈ ������), WORK_XYRBT_START(XY �κ�Ʈ ������)
	////////////////////////2014.1111
	int n_smema_input_index_req; //8580 ���� ����Ͽ� ���۸� �޴´� 
	int n_top_load1_work_req; //idbuffer index move�� input site�� ���۸� ��û�Ѵ� 

	int n_density_moveindex_shift_req; //density�� �۾��� �����ų�, ���۰� �غ���� �ʾ����� ���� ������ ���� ���� �� 
	  
	int n_density_work_req;
	int n_bcr_1_work_req;
	int n_bcr_2_work_req;
	int n_topvision_work_req;
	int n_unload_elevator_req; //�̰����� btm robot�� �۾��� ��û�Ѵ� 

		int n_unload_sub_elev_req;//req:pick ready:down



	int n_unload_rbt_work_req;

	int n_barcode_read_serial_num[2][2];

	int n_bcr_vision_req;
	int n_bcr_reject_req;

	//2016.0908
	int n_Move_conv;
	int	n_Out_conv;
};
extern  st_sync_param  st_sync;
// *****************************************************************************

// *****************************************************************************
//  �޼��� ����
// *****************************************************************************
struct st_message_param
{
	int mn_pad_dialog;
	int mn_dot_use;
	CString mstr_pad_high_limit;
	CString mstr_pad_low_limit;
	CString mstr_keypad_val;

	CString mstr_keypad_msg;
	CString mstr_keyboard_msg;

	CString str_fallacy_msg;		// ���� �޼���.
	CString mstr_confirm_msg;		// Ȯ�� �޼���
	CString mstr_typing_msg;		// Ű���� �޼���

	CString mstr_parent_menu;

	CString mstr_password;

	CString mstr_barcode;

	char c_normal_msg[5000];
	char c_abnormal_msg[5000];
	char c_eqp_msg[5000];

	CString mstr_send;
	CString mstr_recive;

	CString mstr_rpy_msg[10];

	CString mstr_event_msg[3];
	CString mstr_event_xmsg[3];

	CString str_step_savefile_name;
	CString str_step_savefile_path;

	char n_select_buffer;

	CString mstr_handbarcode_msg;
} ;
extern  st_message_param  st_msg;
// *****************************************************************************

// ******************************************************************************
// ���� ��θ� ���� ����ü ���� ����                                             
// ******************************************************************************
struct st_path_param 
{
	CString str_handler;
	CString str_path_back;

	CString mstr_basic;			// �⺻ ���� ���� ���� ����+���ϸ� ���� ����
	CString mstr_basic_folder;	// �⺻ ���� ���� ���� ����+���ϸ� ���� ����

	CString mstr_path_dvc;		// ����̽��� ƼĪ ���� ���� ���� ���� ���� ���� ����
	CString mstr_path_alarm;	// ��� �˶� ���� ���� ���� ���� ����
	
	CString mstr_path_file;		// ���� ���� ���� ���� ����
	CString mstr_path_back;		// BACKUP ���� ���� ���� ���� ����
	
	CString mstr_file_basic;	// �⺻ ���� ���� ���� ���ϸ� ���� ����
	CString mstr_file_wait;		// ��� �ð� ���� ���� ���ϸ� ���� ����
	
	CString mstr_operation;		// Operation Log ���� ���� ����.
	CString mstr_interface;		// Interface Log ���� ���� ����.
	CString mstr_tcpip;
	CString mstr_machine;		// Machine Log ���� ���� ����.
	CString mstr_barcode;		// Barcode Log ���� ���� ����.
	CString mstr_total;			// Total Log ���� ���� ����.
	CString mstr_uph;
	CString mstr_uph_total;
	CString mstr_reject;
	CString str_log_path;
	CString str_lot_data_path;
	
	CString mstr_io_map;		// IO MAP ���� ��ġ ����.
	CString mstr_motor;
	
	CString mstr_handler;

	CString mstr_io_part_map;
	CString mstr_motor_part_map;
	CString mstr_motor_axis_map;
	CString mstr_wait_time_map;

	CString str_interface_folder;//20131115
	CString str_Model_List_folder;

	CString str_eqp_log_path;//2014,1217 ysj EQP_LOG save
	CString mstr_recipe_path;//2015.0221

	//�̰��������û����
	CString mstr_eqp_file;		// ���� ���� ���� ���� ����
	CString mstr_xgem_path;
	CString mstr_error_path;
	CString mstr_event_path;
	CString mstr_product_path;
	CString mstr_mat_path;
	CString mstr_gms_path; //kwlee 2016.0821
	CString mstr_reg_model;
} ;
extern  st_path_param  st_path;
// ******************************************************************************

// ******************************************************************************
// I/O ���� ��� �ð� �� ����Ʈ �ð� ���� ����ü ����                            
// ******************************************************************************
struct st_time_param 
{
	int n_wait_time[E_WAIT_MAX][2];
	int n_limit_time[E_WAIT_MAX];
} ;
extern  st_time_param  st_time;
// ******************************************************************************

// *****************************************************************************
//  Tower Lamp ȭ�鿡 ���� ���� ���� ����ü ���� ����                           
// *****************************************************************************
struct st_lamp_param
{
	int mn_lamp_r[8];			// RED ���� ���� ���� ����
	int mn_lamp_y[8];			// YELLOW ���� ���� ���� ����
	int mn_lamp_g[8];			// GREEN ���� ���� ���� ����
	
	CString mstr_equip_no;		// ��� ȣ�� ���� ����
	CString mstr_equip_id;	// ��� �ڵ� ���� ����
	
	int mn_buzzer_mode;			// ���� ��� ��� ���� ����
	
	int mn_lamp_wait_time;		// ���� FLACKER �ð� ���� ����
	int mn_lamp_change_time;	// ���� ���� �ð� ���� ����
} ;
extern  st_lamp_param  st_lamp;
// *****************************************************************************

// ******************************************************************************
// ������ ȭ�� ȯ�� ���� ���� ���� ����ü ����                                   
// ******************************************************************************
struct st_basic_param 
{
	int nManualSpeed;
	int nRunSpeed;


	int n_bcr_Mode;//2014.0823
	int n_mode_device;

//	int n_mode_run;
	int n_retry_cnt;

	int n_mode_jig;

	int n_degree;
	int n_pick_type;

	int mn_mode_run;			// ��� ���� ��� ���� ����		(1:ON LINE	0:OFF LINE)
	int mn_mode_xgem;
	int mn_mode_rcmd;
	CString mstr_revipe_name;
	
	int mn_bypass_mode;

	int mn_device_type;
	
	int n_day_start_time;		// Data ��Ͽ�.. �Ϸ��� ���� �ð�...
	int n_day_shift_time;		// Data ��Ͽ�.. Shift �ð�...
			
	CString mstr_device_name;	// ���õ� ����̽� ���� ���� ����
	int mn_alarm_delay_time;
	
	int mn_electrostatic_check_gap;
	double md_electrostatic_value;

	int mn_network_wait_time;		// Network ��� �ð�
	int mn_network_retry_cnt;		// Network Retry Ƚ��

	int mn_time_out;
	int mn_robot_init_time;
		
	int mn_mode_unconv; //0:�ϳ��� 1:�ΰ�

	///////20131115
	int n_distance;
	int n_shutter_time;
	int n_brightness;
	int n_contrast;
	double d_1d_width;	
	int n_bcr_background;
	int n_illumination;
	int n_image_rotate;
	int n_1d2d_select;
	int n_1d2d_background;
	///////

	int n_Rework_Tray_x;
	int n_Rework_Tray_y;

	int n_mode_interface;
	int n_mode_retest;

	int nMode_BCR;//[0:BCR Step, 1:BCR Continue]
	int nNCH;

	int mn_Density_Device_Type;
	int mn_Label_vision_paper;
	int mn_Label_Print_Error_Cnt;
	int mn_Label_Print_Total_Error_Cnt;//2015.0211
	CString mstr_vision_model_name1;
	CString mstr_vision_model_name2;
	CString mstr_vision_model_name3;
	CString mstr_vision_model_name4;
	int n_vision_model_index1;
	int n_vision_model_index2;
	int n_vision_model_index3;
	int n_vision_model_index4;
	int n_mode_label;
	int mn_label_type;
	CString mstr_label_name;

	int nBcrFeederUse[4];


	CString sDvcName;
	int nDensityFeederUse[6];
	int nBcrFeelUse[4];

	int nVisionUse[4];//2014.1104
	int nLabelSelect; //2014,1125 ysj 1: 77mm, 0: 55mm

	int mn_leftbcr;
	int mn_rightbcr;

	int mn_outconv;
	int mn_ECServerUse;

	int mn_outtbox;
	int mn_overtime_density;

	int nTopVisionSkip;
	int nTopVisionSkipCnt;
	int nRejectOffset;

	CString n_str_capa1label;
	CString n_str_capa2label;
	CString	n_str_capa3label;

	int mn_limit_bcr_time;
	int mn_auto_vision_mdl;

	CString mstr_bcr_model;
	CString mstr_btm_model;

	int mn_rework_ccs_mode;
	int mn_vision_density_skip;
} ;
extern  st_basic_param  st_basic;
// ******************************************************************************


struct st_barcode_param 
{
	int nApplyButton[5];
	int mn_labelset_sd[4];
	int mn_labelset_lt[4];
	int mn_labelset_lhx[4];
	int mn_labelset_lhy[4];
	int mn_Prt_Mode[4];
	int mn_Prt_complete_use[4];

	bool b_print_complete[MAX_PORT];
	int n_barcode_hs_cnt;
	int n_barcode_hs_paper_out_error[MAX_PORT];
	int n_barcode_hs_pause_error[MAX_PORT];
	int n_barcode_hs_head_up_error[MAX_PORT];
	int n_barcode_hs_ribbon_out_error[MAX_PORT];
	int n_barcode_hs_print_mode[MAX_PORT];

	CString new_barcode_info[2];//2014,1125 ysj

} ;
extern  st_barcode_param  st_barcode;

////2014.0821
struct st_ani_param 
{
	double dAniEncoder[10];
	int nSelectMotPos[10];
	BOOL bSelectCylinder[99];
};
extern  st_ani_param  st_ani;
////


struct _st_Color
{
	COLORREF	colorWhite;
	COLORREF	colorRed;
	COLORREF	colorYellow;
	COLORREF	colorGreen;
	COLORREF	colorBlue;
	COLORREF	colorBlack;
	COLORREF	colorLightGray;
	COLORREF	colorDarkGray;
	COLORREF	colorGray;
	COLORREF	colorTitle;
	COLORREF	colorLightBlue;
	COLORREF	colorViolet;
	COLORREF	colorLightYellow;
	COLORREF	colorOrange;
	COLORREF	colorLightRed;
	COLORREF	colorLightGreen;
	COLORREF	colorBrown;
	
	CBrush		brushWhite;
	CBrush		brushRed;
	CBrush		brushYellow;
	CBrush		brushGreen;
	CBrush		brushBlue;
	CBrush		brushLightBlue;
	CBrush		brushBlack;
	CBrush		brushLightGray;
	CBrush		brushDarkGray;
	CBrush		brushGray;
	CBrush		brushTitle;
	CBrush		brushViolet;
	CBrush		brushLightYellow;
	CBrush		brushOrange;
	CBrush		brushLightRed;
	CBrush		brushLightGreen;
	CBrush		brushBrown;
};
extern _st_Color			g_Color;

// ******************************************************************************
// �߻��� �˶� ���� ������ ���� ����ü ����                                      
// ******************************************************************************
struct st_alarm_param 
{
	CStringList mstr_list_jam;	// �߻��� Jam Code�� ����Ʈ
	CStringList mstr_list_jam_time;	//alarm �߻��ð� ���� ����Ʈ
	CString mstr_code;			// �߻��� �˶� �ڵ� ���� ����
	CString str_lastcode;
	char mc_code[10];
	CString mstr_pcode;			// �߻��� �˶� �ڵ� ���� ����
	int mn_count_mode;			// �˶� ī��Ʈ �÷��� (0:�˶� ī��Ʈ ������    1:�˶� ī��Ʈ ����)
	int mn_type_mode;			// �˶� ���� ���� ���� (0:���    1:���༺    2:��� ����)
	
	long stl_cur_alarm_time;	// �˶� �߻� �ð� ���� ����
	int stl_prev_code;			// �ٷ� �� �߻��� �˶� �ڵ� ���� ����
	long stl_prev_alarm_time;	// �ٷ� �� �߻��� �˶� �߻� �ð� ���� ����
	long stl_alarm_start_time;	// ���� ��ư�� ���������� �߻� �ð� ���� ����
	
	int mn_alarm_occured;		// �˶� �߻� Ƚ�� ���� ����
	int mn_alarm_occured_day;	// �˶� �߻� Ƚ�� ���� ����

	int mn_reset_status;		// Alarm Reset Status
	bool mb_bcr_error;
	int mn_bcr_num;
	int mn_emo_alarm;            // EMO���� �˶��� �ѹ��� �߻��ϵ��� �ϱ� ����!!
	int mn_svr_alarm;
	CString mstr_svr_alarm;
} ;
extern  st_alarm_param  alarm;
// ******************************************************************************

// ******************************************************************************
// �˶� ������ ���� ����ü ����                                                  
// ******************************************************************************
struct st_dsp_alarm_param 
{
	// **************************************************************************
	// �˶� ���� ǥ�� ��ũ [��� ��ġ], [ũ��], [Į��] ���� ����                 
	// **************************************************************************
	int mn_Offset;
	int mn_Cy;
	int mn_Cx;
	int mn_LineWidth;
	int mn_R;
	int mn_G;
	int mn_B;
	// **************************************************************************
	
	// **************************************************************************
	// ȭ�鿡 ����� �˶� ���� ���� ����                                         
	// **************************************************************************
	int mn_action_cnt;            // ����� �˶� ��ġ ���� ���� ���� ����
	CString mstr_style;           // �˶� ��� ���� ���� ����
	CString mstr_bmp_file;        // �˶� ǥ�� �׸� ���� ���� ����
	CString mstr_repair_msg;      // �˶� ��ġ ���� ���� ����
	// **************************************************************************
	
	// **************************************************************************
	// ���Ͽ� ����� �˶� ���� ���� ����                                         
	// **************************************************************************
	CString mstr_e_content[2000];  // ���Ͽ��� �ε��� �� ���� ���� ���� ����
	CString mstr_e_code[2000];     // �˶� �ڵ� ���� ����
	CString mstr_e_state[2000];    // �˶� ���� ���� ����
	CString mstr_e_part[2000];     // �˶� �߻� ���� ���� ����
	CString mstr_e_msg[2000];      // ���� ���� �˶� �޽��� ���� ����
	// **************************************************************************
	
	int mn_e_list;
	
	// **************************************************************************
	// ���� �߻��� �˶� ���� ����                                                
	// **************************************************************************
	int mn_cur_state;				// �˶� ���� ���� �÷���
	CString mstr_cur_state;			// �˶� ���
	CString mstr_cur_msg;			// �߻��� �˶� �޽��� ���� ����
} ;
extern  st_dsp_alarm_param  st_alarm;
// ******************************************************************************

// ******************************************************************************
// ��� ���� ���� �÷��� ���� ���� ����ü ����                                   
// ******************************************************************************
struct st_work_param 
{
	int nMdlInputCount[2][2];	// [Prime, Cum][Lot, Daily]
	int nMdlPassCount[2][2];
	int nMdlFailCount[2][2];
	int nMdlHtoCount[2][2];
	int nMdlBtoCount[2][2];
	int nMdlNtoCount[2][2];
	int nMdlRejectCount[2][2];
	float fMdlyield[2][2];

	// **************************************************************************
	// ��� ���� �� �߻��ϴ� �ð� ���� ���� ���� ��� ����                       
	// **************************************************************************

	int mn_elec_serial_work;
	// **************************************************************************

	////���͵��� ����  // 0:Front Shifter, 1:Rear Shifter, 2:Front Buffer, 3:Read Buffer
	int n_sync_reinstate;
	int mn_reinstatement_mode;					// 0:����Ŭ��&�Ϸ� , 1:stop��ȯ��//����� , 2:��ŸƮ Ű ���� ����, 3:������ ...., ���ͿϷ��� 0 �׸��� �� ���� 
	double md_reinstatement_Pos[2][100];				// 0: Ld Elev., 1: Tray Transfer, 2: Robot X, 3: Robot Y, 4: Robot Z, 5: Robot Pitch, 6: Uld Elev.
// 	double md_reinstatement_pos[100];				// 0: Ld Elev., 1: Tray Transfer, 2: Robot X, 3: Robot Y, 4: Robot Z, 5: Robot Pitch, 6: Uld Elev.
	int md_reinstatement_cyl[100];
	int	mn_glipperr_updn;
	int	mn_tray_guide[3];
	int	mn_tray_pusher[3];//1���� ����
	int	mn_site_pogo[2][5];
	int mn_transfer_cyl;
	

	//////////////////////////////////////////////////////////////////////////
	
	int	mn_site_hookclamp[3];
	int	mn_site_hookunclamp[3];

	int	mn_site_hookfwd[2];
	int	mn_site_hookbwd[2];

	int	mn_site_ldclamp[4];
	int	mn_site_ldunclamp[4];


	int	mn_site_uld_hookfwd[2];
	int	mn_site_uld_hookbwd[2];

	int	mn_site_uld_hookclamp[2];
	int	mn_site_uld_hookunclamp[2];

	int	mn_site_uldclamp[2];
	int	mn_site_uldunclamp[2];

	int	mn_btm_stopper;

	int	mn_site_elvclamp;
	int	mn_site_elvunclamp;

	int mn_site_density_fwdreel[6];
	int mn_site_density_bwdreel[6];

	int mn_site_density_fwdlock[6];
	int mn_site_density_bwdlock[6];

	int mn_site_bcr_lock[4];

	int mn_bcr_m1top_vac_fwdback[2];
	int mn_bcr_m1btm_vac_fwdback[2];
	int mn_bcr_m2top_vac_fwdback[2];
	int mn_bcr_m2btm_vac_fwdback[2];

	int mn_bcr_plate_updn[4];
	int mn_bcr_box_updn;

	int mn_bcr_m1guide_fwdback[2];
	int mn_bcr_m2guide_fwdback[2];
	int mn_bcr_m1guide_updown[2];
	int mn_bcr_m2guide_updown[2];

	int mn_rolling_fwdback[2];
	int mn_m1rotate_fwdback[2];
	int mn_m2rotate_fwdback[2];

	int	mn_recycle_pusher_forward;
	int	mn_recycle_pusher_backward;




	//2016.0510
	//////////////////////////////////////////////////////////////////////////
	int mn_bcr_mtop_vac_fwdback[2];
	int mn_bcr_mbtm_vac_fwdback[2];
	int mn_mrotate_fwdback[2];

	//////////////////////////////////////////////////////////////////////////
	

	int	mn_rotator_onoff;

	int	mn_sorter_picker_updn[4];


	int mn_xyz_safety;

	int mn_reinstate_xyz_robot;
	int mn_reinstate_reject_robot;
	int mn_reinstate_tester_robot[2];
	int mn_reinstate_stacker_robot[3];

	int n_back_type;		//�̵������ ����� ���� ��ġ����, teach�����ͷ� �̵�����

	double mdReadElectData[5];

	int mn_tl_status;					// Ÿ������ ���� ���� ���� ���� (O:STOP 1:RUN(IN PCB) 2:ALARM 3:MAINT 4:INIT 5:RUN(NO PCB))
	int mn_chg_job;//2015.0327
	int mn_jam;//2015.0327
	int mn_run_down;

	CString mstr_client_rev_msg[3];

	int		mn_prev_step[100];			// ���� step (���� �Ǿ����� ���� ����)
	CString	mstr_history_step[100];		// step_history �� 50���� �ش��ϴ� step�� ����
	CString	mstr_history_step_back_up[100];		// step_history �� 50���� �ش��ϴ� step�� ����
	CString mstr_last_change_date[100];	// ���� step���� ����Ǵ� ������ �ð�

	double d_reinstatement_x_pos;		//���͵� ���� x ��ġ��
	double d_reinstatement_y_pos;		//���͵� ���� y ��ġ��
	double d_reinstatement_z_pos;		//���͵� ���� z ��ġ��

	char cPLotName[MAX_PLOT][50];	// P_LOT 2013,0910
	int nPLotInputCount[MAX_PLOT][3];	// P_LOT 2013,0910
	int nPLotPassCount[MAX_PLOT][3];	// P_LOT 2013,0910
	int nPLotFailCount[MAX_PLOT][3];	// P_LOT 2013,0910
	double fPLotYield[MAX_PLOT][3];	// P_LOT 2013,0910
	bool m_bPLotDel;
	int nPLotCnt;

	////20131115
	int n_barcode_recive;
	CString strBarcodeRecive;

	////
	CString str_barcode_success;//20131115

	int nLink_CIM2TMS;
	// ������ ��Ʈ�� ��� ���� [MC_OFF_LINE, MC_ON_LINE_LOCAL, MC_ON_LINE_REMOTE]
	int nEQ_CtrlMode;
	// ���̸� �߰� [2014.08.16]
	CString sLotId_Open;
	CString sLotId_Cancel;
	CString sLotId_Scrap;
	CString sLotId_LotEnd;
	
	CString sLotId_Label;
	int nCnt_ReqLabel;
	
	CString sLotId_TrackIn;
	CString sLotId_TrackOut;
	CString sLotId_TrackModify;

	bool b_run_slmulation_md;

	CString mstrID_Buffer_Serial[10];
	int n_label_recive[MAX_PORT];

	CString mstr_op_id;
	CString mstr_format_retry;

	CStringList strlabelFormat;
	int n_lotdisply_qty;
	int	mn_uld_picker_updn[2];
	int	mn_uld_pusher_buf[2];

	int mn_rej_picker_updn;
	int n_IDBuffer_Info;
	int n_Btm_IDBuffer_Info;//2014,1217 ysj

	int n_mat_density[6];//2000 2015.0529
	int n_mat_bcr[4]; //3000
	int n_mat_ribbon[4]; //5000


	int m_nMdlTotal;
	int m_nCboSelModel;
	CString m_strModelName[100];
	CString m_strCurModel;
	int m_nNmModel;//ahepfaud
	CStringList m_strModel[50][200];//[m_nNmModel][Partnum]

	//2016.0919
	CTime t_jamcode_start;
	CTime t_jamcode_end;	
	int	  n_jamcode_flag;
} ;
extern  st_work_param  st_work;
#define MAX_LOT_	5	// �ִ� LOT ����

// ���̸� �߰� [2014.03.18]
struct tagLOT_PARAM
{
	int nCnt_Good;
	int nCnt_Scrap;
	
	CString sLotNo;
	CString sEqpId;
	CString sOperId;
	
	CString sScrapCode[100];
	CString sScrapQty[100];
	
	CString sSerial;
};
extern tagLOT_PARAM	stLOT[MAX_LOT_];



//////////////////////////
#define PICKER_LDULD_POS			   0
#define PICKER_LOAD_POS				   1
#define PICKER_BARCODE_POS			   2
#define PICKER_DVC_PICK_POS			   3
#define PICKER_PICKER_ROBOT_POS		   4
#define PICKER_DVC_PLACE_POS		   5
#define PICKER_UNLOAD_POS			   6
//////////////////////////
#define CONV_A						   0
#define CONV_B						   1
//////////////////////////

#define NETWORK_CNT						2

#define NETWORK_ECSERVER				0
#define NETWORK_NMACHINE				1

// ******************************************************************************
//  TEST REFERENCEȭ�� ȯ�� ���� ���� ���� ����ü ����                           
// ******************************************************************************
// ******************************************************************************

struct st_modulemap_size
{
//	int nDeviceRobotPicker[4][PICKER_NUM];			// 0:Pickerinfo, 1:bin����, 2:retest count, 3:Array
	int LoadBufferState[LOADTRAY_ROW][LOADTRAY_COL]; 
	int LoadElvState[LOADTRAY_ROW][LOADTRAY_COL]; 
	int UnloadElvState[UNLOADTRAY_ROW][UNLOADTRAY_COL]; 
	int UnloadBufferState[LOADTRAY_ROW][UNLOADTRAY_COL]; 
	int RejectTrayState[REJECTTRAY_ROW][REJECTTRAY_COL]; 
	int LoadBcrData[LOADTRAY_ROW][LOADTRAY_COL];//BCR

	CString ReciveBcrData[LOADTRAY_ROW][LOADTRAY_COL];

} ;
extern  st_modulemap_size  st_modulemap;

// ******************************************************************************
// RS-232C �ø��� ��� ���� ���� ����ü ����                                     
// ******************************************************************************
struct st_serial_param 
{
	int mn_snd_chk[MAX_PORT];         // ������ �۽� �Ϸ� �÷���
	int mn_rec_chk[MAX_PORT];         // ������ ���� �Ϸ� �÷���
	
	CString mstr_port_chk[MAX_PORT];  // �ø��� ��Ʈ ���� ���� ���� ����
	
	CString mstr_snd[MAX_PORT];       // �۽� �޽��� ���� ����
	CString mstr_rec[MAX_PORT];       // ���� �޽��� ���� ����
	
	CString mcomm_snd[MAX_PORT];      // ����Ʈ ȭ�� ��� �۽� �޽��� ���� ����
	CString mcomm_rec[MAX_PORT];      // ����Ʈ ȭ�� ��� ���� �޽��� ���� ����
	CString mcomm_err[MAX_PORT];      // ����Ʈ ȭ�� ��� ���� �޽��� ���� ����

	int nDataAccept;    // ������ �޾Ƶ��̶�� �÷���

	bool b_Manual_Port_close;
} ;
extern  st_serial_param  st_serial;
// ******************************************************************************

///////20131115
struct st_serial_info
{
	int			n_serial_port[10];		// serial port....
	int			n_serial_baudrate[10];	// serial baudrate....
	int			n_serial_data[10];		// serial data....
	int			n_serial_stop[10];		// serial stop....
	int			n_serial_parity[10];	// serial parity.....
	
};
extern struct st_serial_info rs_232;
//////

struct st_nw_param
{
	int			mnID;

	CString		mstr_full_msg[10];
	CString		mstr_header_msg[2];
	CString		mstr_data_msg[2];
	CString		mstr_function[2];
	CString		mstr_lot_id[2];
	CString		mstr_lot_no[2];
	CString		mstr_eqp_id[2];
	CString		mstr_oper_cnt[2];
	CString		mstr_oper_id[2];
	CString		mstr_oper_info[2];
	CString		mstr_pcbox_id[2];
	CString		mstr_serial[2];

	CString		mstr_pcbox_cnt[2];
	CString		mstr_pcbox_info[2];
	CString		mstr_lot_qty[2];
	CString		mstr_slot[2];
	CString		mstr_step_cnt[2];
	CString		mstr_part_id[2];
	CString		mstr_cycle_id[2];
	CString		mstr_temp[2];
	CString		mstr_result[2];
	CString		mstr_qty[2];
	CString		mstr_test_result[2];
	CString		mstr_novideo_cnt[2];
	CString		mstr_fail_no[2];
	CString		mstr_fail_cnt[2];
	CString		mstr_fail_log[2];
	CString		mstr_fail_slot[2];
	CString		mstr_fail_type[2];
	CString		mstr_fail_desc[2];
	CString		mstr_fail_code[2];
	CString		mstr_retest_no[2];
	CString		mstr_retest_id[2];
	CString		mstr_retest_flag[2];
	CString		mstr_slot_no[2];
	CString		mstr_test_idx[2];
	CString		mstr_fail_regnumber[2];
	CString		mstr_error_log[2];
	CString		mstr_scrap_cnt[2];
	CString		mstr_scrap_info[2];

	CString		mstr_pcbox[2][150];
	
	CString		mstr_msg[2];
	
	CString		mstr_buffer_rcv_data[10][100];
	int			mn_rcv_data[10];
	int			mn_find_data[10];
	
	CString		mstr_client_rev;
	CString     mstr_client_send;
	
	// ��� ����ϴ� �������ݿ� ����.
	CString		mstr_m_eqp_id[2];
	CString		mstr_m_buffer_no[2];
	CString		mstr_m_station[2];
	CString		mstr_m_lot_no[2];
	CString		mstr_m_part_no[2];
	CString		mstr_m_last_module[2];
	CString		mstr_m_bypass[2];
	CString		mstr_m_mode[2];
	CString		mstr_m_module_cnt[2];
	CString		mstr_m_module_data[20][2];
	CString		mstr_m_retestcheck[2];

	CString		mstr_pct_bypass[2];
	
	CString		mstr_m_socket_off[2];

	CString		mstr_new_lot_no[2];

	CString		mstr_bpc_buffer_ready;
	CString		mstr_bpc_buffer_in;

	bool		mb_buffer_in_received;

	CString		mstr_buffer_in_recv;
	CString		mstr_buffer_in_temp;

	int mn_scrap_info_flag;

	CString		mstr_format_retry[2];

	CString		mstr_Print_Data[99999];
	CString     mstr_Label_Pasing[99999];//20140215
	CString		mstr_Recive_Data[99999];
	CString		mstr_Unkown1[99999];
	CString		mstr_1Position[99999];
	CString		mstr_1Contents[99999];
	CString		mstr_2Position[99999];
	CString		mstr_2Contents[99999];
	CString		mstr_3Position[99999];
	CString		mstr_3Contents[99999];
	CString		mstr_3Position_back[99999];
	CString		mstr_3Contents_back[99999];
	CString		mstr_4Position[99999];
	CString		mstr_4Contents[99999];
	CString		mstr_2DPosition[99999];
	CString		mstr_2DContents[99999];
	CString		mstr_Unkown2[99999];
	CString		mstr_LotNoPosition[99999];
	CString		mstr_LotNoContents[99999];
	CString		mstr_Recive_PartNo[99999];
	
	///��ġ����
	CString		mstr_1PosX_1[99999];
	CString		mstr_2PosX_1[99999];
	CString		mstr_3PosX_1[99999];
	CString		mstr_3PosX_back_1[99999];
	CString		mstr_4PosX_1[99999];
	CString		mstr_2DPosX_1[99999];
	CString		mstr_Unkown2PosX_1[99999];
	CString		mstr_LotNoPosX_1[99999];
	
	CString		mstr_1PosY_1[99999];
	CString		mstr_2PosY_1[99999];
	CString		mstr_3PosY_1[99999];
	CString		mstr_3PosY_back_1[99999];
	CString		mstr_4PosY_1[99999];
	CString		mstr_2DPosY_1[99999];
	CString		mstr_Unkown2PosY_1[99999];
	CString		mstr_LotNoPosY_1[99999];
	///����
	CString		mstr_1Contents_1[99999];
	CString		mstr_2Contents_1[99999];
	CString		mstr_3Contents_1[99999];
	CString		mstr_3Contents_back_1[99999];
	CString		mstr_4Contents_1[99999];
	CString		mstr_2DContents_1[99999];
	CString		mstr_LotNoContents_1[99999];
	CString		mstr_Unkown2_1[99999];
	
	CString		mstr_1Contents_2[99999];
	CString		mstr_2Contents_2[99999];
	CString		mstr_3Contents_2[99999];
	CString		mstr_3Contents_back_2[99999];
	CString		mstr_4Contents_2[99999];
	CString		mstr_2DContents_2[99999];
	CString		mstr_LotNoContents_2[99999];
	
	///��������
	CString		mstr_1Wid_1[99999];
	CString		mstr_2Wid_1[99999];
	CString		mstr_3Wid_1[99999];
	CString		mstr_3Wid_back_1[99999];
	CString		mstr_4Wid_1[99999];
	CString		mstr_2DWid_1[99999];
	CString		mstr_LotNoWid_1[99999];
	CString		mstr_Unkown2Wid_1[99999];
	
	CString		mstr_1High_1[99999];
	CString		mstr_2High_1[99999];
	CString		mstr_3High_1[99999];
	CString		mstr_3High_back_1[99999];
	CString		mstr_4High_1[99999];
	CString		mstr_2DHigh_1[99999];
	CString		mstr_LotNoHigh_1[99999];
	CString		mstr_Unkown2High_1[99999];
	
	CString		mstr_1Etc_1[99999];
	CString		mstr_2Etc_1[99999];
	CString		mstr_3Etc_1[99999];
	CString		mstr_3Etc_back_1[99999];
	CString		mstr_4Etc_1[99999];
	CString		mstr_2DEtc_1[99999];
	CString		mstr_2DEtc_2[99999];
	CString		mstr_LotNoEtc_1[99999];
	CString		mstr_Unkown2Etc_1[99999];
   
};
extern st_nw_param st_NW;
// ******************************************************************************

struct st_time_database
{
	int				mndb;
	
	COleDateTime	mole_date;
	
	CString			mstrlot_no;
	CString			mstrpart_no;
	
	int				mnTime_Section;
	int				mnTime_Time;
	int				mnMode;
	
	int				mnSectionBuffer;
};
extern struct st_time_database st_timedb;

struct st_alarm_database
{
	int				mndb;
	
	COleDateTime	mole_date;
	
	CString			mstrlot_no;
	CString			mstrpart_no;
	
	CString			mstrAlarmCode;
	CString			mstrAlarmMsg;
};
extern struct st_alarm_database st_alarmdb;

struct st_ground_database
{
	int				mndb;
	
	COleDateTime	mole_date;
	
	CString			mstrChannel[5];
};
extern struct st_ground_database st_grounddb;

struct st_buffer_database
{
	int				mndb;
	
	COleDateTime	mole_date;
	CString			mstrlot_no;
	CString			mstrpart_no;
	int				mnbuffer_pos;
	int				mnlast_module;
	int				mnbypass;
	int				mnmodule_cnt;
	int				mnretest;
};
extern struct st_buffer_database		st_bufferdb;

struct st_boat_database
{
	int				mndb;
	
	COleDateTime	mole_date;
	CString			mstrlot_no;
	CString			mstrpart_no;

	int				mn_boat_id;
	int				mn_product_id;
	int				mn_pcb_cnt;
	int				mn_bin[8];		// 4 * 2 �Ǵ� 2 * 4�� ������ ���� ���� Boat��. Bin�� 1(0), 2(1), 4(2), 8(3), �����ҷ�(4), ġ���ҷ�(5), UnKnown(6).
};
extern struct st_boat_database		st_boatdb;

struct st_buffer_tray_param
{
	int nDeviceExistence[4][3][100];
	char cModuleData[3][90][50];
	int nArrayInfo[3][90];
	char cSerialNumber[3][90][20];
	char cLotNumber[3][90][20];
	char cTestResult[3][90][20];
	char cArrayInfo[3][90][20];

	char cTotalLotNumber[40];
	char cTotalPartNumber[40];
	char cModuleCnt[5];
	int nRetestMdlCnt[2];			// 0 : HTO, BTO, 1: NTO
	int nLastModule;
	int nByPass;

	int nTrayExistence;
};
extern st_buffer_tray_param	st_buffer_tray[MAX_SITE_INFO];

typedef struct comm_param_info
{
	char chSendCmd[100];	// ������ �޽��� ��� ���� (���ڿ�)
	char chResponse[100];	// ������ �޽����� ��� ���� (���ڿ�)
	// ������ �޽����� ���� ���� ���� �� ���� ����
	// - [0:default, 1:����, -1:����, 10:�����ʿ�, 11:���ں��ʿ�]
	int nEcho;
	// ������ �޽����� ���� ���� ��ٸ� ���� �� ���� ����
	// - [0:default, 1:����, -1:����, 10:��������(��ٸ�), 11:�������]
	int nResponse;
	int nTimeOut;	// Ÿ�Ӿƿ� �˻����� ���� [0:�˻���ʿ�, 1:�˻��ʿ�]
	
	char chReceiveCmd[100];	// ���ŵ� �޽��� ���� (���ڿ�)
}comm_param;

struct st_client_param
{
	CString str_ip;		// ���� IP �ּ�
	CString strSend;
	int n_port;
	int n_connect;		// ���� ���� ����
	
	int n_rev_length;	// ���� ���ڿ� ����
	char ch_rev[8192];	// ���� ���ڿ�
	char ch_send[8192];	// �۽� ���ڿ�

	char chSendHead[40];	// ������ ��� ����
	char chSendBody[4096];	// ������ �ٵ� ����
	
	int	n_rev_info;		// client ���� ���..... (0:�ٷ� 1: ������)
	int n_client_no;	// (0:��, 1:�Ｚ)

	// ���̸� �߰� [2014.11.01]
	int nIndex;	// ������ �޽����� �ε��� ��ȣ
	comm_param	stComm[MAX_MSG_CNT];
};
extern st_client_param	st_client[15];

struct st_server_param
{
	CString str_ip;	// �Ұ� IP �ּ�
	int n_port;
	int n_connect;	// ���� ���� ����
	
	int n_send_length;	// �۽� ���ڿ� ����
	int n_rev_length;	// ���� ���ڿ� ����
	char ch_rev[4096];	// ���� ���ڿ�
	char ch_send[4096];	// �۽� ���ڿ�
	
	char chSendHead[40];	// ������ ��� ����
	char chSendBody[4096];	// ������ �ٵ� ����
	
	// ���̸� �߰� [2014.11.01]
	int nIndex;	// ������ �޽����� �ε��� ��ȣ
	comm_param	stComm[MAX_MSG_CNT];
};
extern st_server_param	st_server[15];

struct st_mes_data_param
{
	CString srt_LOT_ID;
	CString srt_PART_ID;
	CString srt_LotQty;
	CString srt_GATE;
	CString srt_RETRY;
	CString srt_RETRY_CNT;
	CString srt_SERIAL;
	CString srt_PPID;
	CString srt_WWN;
	CString srt_C_SERIAL;
	CString srt_PSID;
	CString srt_TK_CODE;
	CString srt_BOAT_ID;
	CString srt_MODIF_MODE;
	CString srt_DTBT_LABEL_CODE;
	CString srt_DTBT_RIBBON_CODE;
	CString srt_MODE;
	CString srt_WEIGHT;
	CString srt_DTBT_LABEL_SERIAL;
	CString srt_S_BOX_CNT;
	CString srt_S_BOX_LABEL_SERIAL;
	CString srt_L_BOX_ID;
	CString srt_MO_CLOSE_TIME;
	CString srt_S_BOX_ID;
	CString srt_TOOLID;
	CString srt_DEN_LABEL_MAT_CODE;
	CString srt_DTBT_MAT_CODE;
	CString srt_RIBBON_MAT_CODE;
	CString srt_SSD_CNT;
	CString srt_PROD_SRLNO;
	CString srt_PIECE_PROD_ID;
	CString srt_WWN_SRLNO;
	CString srt_CUST_SRLNO;
	CString srt_PHYS_SECRTY_ID;
	CString srt_DENSITY_Type;
	CString srt_TURMKEY_BOX_CODE;

	CString srt_SRL[25];
};
extern st_mes_data_param	st_mes_data;


// ******************************************************************************
//  TEST REFERENCEȭ�� ȯ�� ���� ���� ���� ����ü ����                           
// ******************************************************************************
struct st_testreference_param 
{//james 2010,0719 ���� ���ۿ� ���
	int n_absolute_yield;
	int n_relative_yield;
	int n_continuity_count;
	int n_apply_count; 
	
	int n_bin_num[5][10]; //2011.0119 [BINNUM + 2];		 //james 2010,0708 ���� ������ + 2 ���� , //n_bin_num[BINNUM];				// Combine BIN ���� ����
	int n_bin_num_backup[10]; //2011.0119 [BINNUM + 2];//���� ������� ���� //james 2010,0708 ���� ������ + 2 ���� n_bin_num_backup[BINNUM];		// Back up�� Combine BIN ���� ����
	
	
	//jame 2010.1108 �߰� 
	int n_bin_move_num[5][10]; //2011.0119 [BINNUM + 2];		 //james 2010,0708 ���� ������ + 2 ���� , //n_bin_num[BINNUM];				// Combine BIN ���� ����
	int n_bin_move_num_backup[10]; //2011.0119 [BINNUM + 2];//���� ������� ���� //james 2010,0708 ���� ������ + 2 ���� n_bin_num_backup[BINNUM];		// Back up�� Combine BIN ���� ����
	
	
	int n_mode_socketoff[4];	// Socket Off ���� ���� ����
	
	int n_socketoff_reason[8];  //james 2010,0719 //���Ͽ��� ���� auto, mnanual off 
	
	long n_contact_limit_cnt;			// ���� ���� �ִ� ��� Ƚ�� ���� ����
	long n_off_time_w;					// OFF LINE �׽�Ʈ ��� �ð� ���� ����
	long n_test_eot_time_l;				// �׽�Ʈ EOT ����Ʈ �ð� ���� ����
	int n_offline_bin_set[8];
	
	int n_conti_fail_bin[8];		// ���� Fail Bin ���� ����
	int n_conti_fail_cnt;
	int n_manual_retest_rail[4];
	
	int n_DCStart_WaitTime;				// dc test
	
	double nDCSocketStatus[TESTSIZE][2];		// 0:FAIL, 1:PASS
	
	int n_bin_mode; //��õ, ������ => 0:normal, 1:dda_1, 2:dda_2, 3:other
	//û ��        => 0:normal, 1:dda_1, 2:FNC,   3:MCP
	
	int n_binmode_chk_change[4]; //2010.1026 
	
	// ���� �߰� ��. 2K11/03/02/ViboX
	int n_lot_fail_rate_mode;
	int n_total_fail_rate_mode;
	
	int n_lot_fail_apply_count;
	int n_total_fail_apply_count;
	
	int n_lot_fail_check_count[8];
	int n_total_fail_check_count[8];
	int n_lot_good_check_count[8];
	int n_total_good_check_count[8];
	
	int n_lot_fail_yield;
	int n_total_fail_yield;
	
	float f_lot_fail_yield[8];
	float f_total_fail_yield[8];
	
	//2011.0316
	int n_retest_fail_cnt; //dc retest�� �� Ƚ���� �����Ͽ� ������ �̻��̸� �����߻����� �̿��� ���� ��û 
	int n_dcfailbin_retest_count[8]; //dc fail bin retest count
	
	// ���̸� �߰� [2013.10.01]
	int nDCSocketDevision;
	CString sDCSocketDevision;
	CString sDCTesterModel;
	
	// 2K13/10/28/ViboX û�ְ� �߰�.
	//2012.0328 
	int n_tot_rel_yield_cj;
	int n_tot_rel_apply_count_cj;
	int n_tot_rel_retest_include_cj;
	
	int n_lately_yield_cj;
	int n_lately_count_cj;
	int n_lately_test_count_cj;
	
	int n_dcfail_gap;           // 2K12/11/08/ViboX
	
//	std::string		m_strFailHistory[TESTSIZE];
	
} ;
extern  st_testreference_param  st_testreference;

// ******************************************************************************
//  �۾� ��� ���� ���� ����ü ����                                              
// ******************************************************************************

struct st_test_param 
{//james 2010,0719 ���� ���ۿ� ��� 
	
	int n_socket_good[TESTSIZE];
	int n_socket_reject[TESTSIZE];
	
	int n_socket_data[6][10][10]; //2011.0119 [TESTSIZE + 2][BINNUM + 2];//james 2010,0708 ������ +2�� ���� n_socket_data[6][TESTSIZE + 1][BINNUM + 1];	// (LOT, DAY, MONTH, SHIFT��), ���� ��ȣ, BIN�ѹ�.
	int n_socket_screen_data[6][10][10]; //2011.0119 [TESTSIZE + 2][BINNUM + 2];//james 2010,0708 ������ +2�� ���� n_socket_screen_data[6][TESTSIZE + 1][BINNUM + 1];	// (LOT, DAY, MONTH, SHIFT��), ���� ��ȣ, BIN�ѹ�.
	
} ;
extern  st_test_param  st_test; 








#define BT_REAR_BUFFER			0
#define BT_FRONT_BUFFER			1
#define BT_PICKER				2
#define BT_RETEST_BUFFER		3
#define BT_REJECT_BUFFER		4
#define BT_LOB_BUFFER			5
#define BT_TRAY_1				6
#define BT_TRAY_2				7
#define BT_CUSTOMER_BUFFER		8
#define BT_AIRBLOW_BOX			9
#define BT_LENGTH_VARIABLE		10
#define BT_SAFETY_ZONE			11

struct st_part_motor_info
{
	int				n_part_cnt;
	int				n_part_axis_cnt[20];
	int				n_part_axis[20][12];
	
	int				n_axis_pos_num[20][12];
	int				n_axis_minus_el[20][12];
	int				n_axis_plus_el[20][12];
	int				n_axis_home[20][12];
	int				n_axis_sd[20][12];
	int				n_axis_direction[20][12];
	int				n_axis_account[20][12];
	
	CString			str_part_info[20];
	CString			str_part_name[20];
	
	CString			str_part_axis_name[20][12];
	CString			str_axis_pos_name[20][12][32];
	CString			str_axis_pos_info[20][12][32];
};
extern struct st_part_motor_info st_motor_info;

struct st_part_info
{
	CString		str_part_info[20];
};
extern struct st_part_info st_part;

// struct st_xgemdata
// {
// 	CString m_str_xgmInit;
// 	CString m_str_bufferin;
// 	CString m_str_loadtray;
// 	CString m_str_unloadtray;
// };
// extern st_xgemdata st_xgem;

struct st_vision
{
	int n_RetDensity[2];
	int n_RetBarcode[4];
	int m_TopVisoon;
	int m_BtmVIsion;
};
extern st_vision st_vis;

//��񿡼� ����� ���� ���� 
struct st_step_param
{
	int n_main[MAX_STEP]; //main_runstep
	int n_sub[MAX_STEP];  //main�ȿ��� ����� sub step

	int n_init[MAX_STEP]; //�ʱ�ȭ�� ����ϴ� step 

	int n_main_recovery[MAX_STEP]; 
	int n_sub_recovery[MAX_STEP]; 

	int n_ManualMoveCV[MAX_STEP];//20140929
	int n_ManualTransferYZ[MAX_STEP];//20140929
	int n_ManualPusherYZ[MAX_STEP];//20140929
	int n_ManualIDBuffer_Setplate[MAX_STEP];//20140929
	int n_ManualIDBuffer_Input[MAX_STEP];//20140929
	int n_ManualIDBuffer_Move[MAX_STEP];//20140929
	int n_ManualSealing[MAX_STEP];//20140929
	int n_ManualBtmIDBuffer_Left[MAX_STEP];//20140929
	int n_ManualBtmIDBuffer_Right[MAX_STEP];//20140929
	int n_ManualBtmIDBuffer_Left_Place[MAX_STEP];//20140929
	int n_ManualBtmIDBuffer_Right_Place[MAX_STEP];//20140929




	int n_sub1_ManualMoveCV[MAX_STEP];//20140929
	int n_sub2_ManualMoveCV[MAX_STEP];//20140929
	int n_sub1_ManualTransferYZ[MAX_STEP];//20140929
	int n_sub2_ManualTransferYZ[MAX_STEP];//20140929
	int n_sub_ManualPusherYZ[MAX_STEP];//20140929
	int n_sub1_ManualIDBuffer_Input[MAX_STEP];//20140929
	int n_sub2_ManualIDBuffer_Input[MAX_STEP];//20140929
	int n_sub_ManualSealing[MAX_STEP];//20140929
	int n_sub1_ManualBtmIDBuffer_Left[MAX_STEP];//20140929
	int n_sub2_ManualBtmIDBuffer_Left[MAX_STEP];//20140929
	int n_sub1_ManualBtmIDBuffer_Right[MAX_STEP];//20140929
	int n_sub2_ManualBtmIDBuffer_Right[MAX_STEP];//20140929

/*
	//������ ���� ���� ����
	int tbox_stacker[2]; //left, right 
	int tbox_conveyor[2];
	int tbox_vision_;
	int tbox_forming[2];
	int tbox_safety;
	int tbox_switch;

	//���Ա� ���� ���� ����
	int seal_conveyor_move;
	int seal_transfer;
	int seal_idbuffer_move[2];
	int seal_tbox[5]; //[0]:����޴¿���, [1]:�������¿���,[2]:�Ѳ����ºκ�,[3]:���̵�Ŀ�����ºκ� ����ǰ, [4]:�����۷� ��⿵�� 
*/
	
} ;
extern  st_step_param   st_step;

struct st_variable_param
{ 
	int n_event_inputindex_premove_right_start_flag; //2014.1120 ��� ���� �̵� ���⸦ ������ �ϱ����� �߰� 
	int n_event_moveindex_premove_right_start_flag; //index move�� �̵� �ϸ鼭 Ǯ���� �� 
/////////////////////////////////////////////////////
//2014.1111 james ///////////////////////////////////
	int n_last_module_flag;
/////////////////////////////////////////////////////
	int n_bcr_read_input_flag;
	int n_bcr_read_output_flag;

	int n_newLabelType_flag;

	int n_boatid_in_flag;
	int n_boatid_out_flag;

	int n_mdl_change;

	int n_use_vis_density;
	int n_use_vis_top;

	int n_err_density_flag[6];
	int n_using_barcode;
	int n_use_barcode[4];
	int n_use_density_flag[6];
	int n_use_density_count[6];
	int n_use_density_key;
	int n_use_top_skip;
	int n_bcrid_error[4];
	int n_next_down;
	
	int n_newlotin;
	int n_densityccs;
	int n_bcrccs;
	int n_lotstart; //0:lot wait,1:lot start, 2:lot end 
	int n_lotend_flag[20]; //�� ����Ʈ�� lot end�� ���� 
	int n_lotstart_count;
	
	int mn_new_density_flag;
	int mn_new_density_count;
	int mn_check_density_flag;
	int mn_check_density_count;
	int mn_lotend_density_flag;


	 int n_tboxmv_forming_cv_mode; //forming MC Site //0:left�� ���, 1:right�� ���, 2:�ΰ��� ��� 
	int n_tboxmv_sealing_cv_mode; //sealing MC site //0:left�� ���, 1:right�� ���, 2:�ΰ��� ���


	//id buffer fix clamp������ idbuffer ��/�� ������ ���´�.
	int n_idbuffer_inputindex_gripper_exist_info[2]; //gripper�� ������ �ִ� ������ �ִ�2�� ��/�� ������ ���´�

//	int n_idbuffer_setplate_exist_info[2]; //gripper�� ������ �ִ� ������ �ִ�2�� ��/�� ������ ���´�
//	int n_top_idbuffer_fix_clamp_exist_info[4][2]; //[0]:fix 1 2��, [1]:fix1,2 2ea, [2]:fix2 2ea, [3]:fix3�� 2ea	
//	int n_top_idbuffer_mvindex_gripper_exist_info[8]; //gripper�� ������ �ִ� ������ �ִ� 8�� ��/�� ������ ���´�


	//top id buffer ��/�� ���� 
	//id buffer : �� 10��, (set plate 2��[0]~[1],  fix clamp 8��) : [2] ~[9]
	//tbox check(��ǰüũ) : �� 10��, (set plate 2��, seal 6��, output buffer 2�� ) :[10]~[19]
	//ssdüũ(�Ǽ��縮) : �� 2��(setplate 2��) :[20],[21],
	//index move gripper���� : �� 8��, ������ ���� [22]~[29]

	int n_top_idbuffer_exist_status_check_info[30]; //�� 30���� ���� �÷��� ����
	int n_temp_top_idbuffer_exist_status_check_info[30]; //�� 30���� ���� �÷��� �ӽ� ���� ���� 
	int n_top_idbuffer_io_status_read_chk_data[30]; //�� 30���� i/o �������� ����

	


	//bottom id buffer ��/�� ���� 
	int n_btm_idbuffer_exist_check_info[8]; //left gripper [0],[1], right gripper [2],[3], main fix clamp  [4],[5], init fix clamp [6],[7]
	int n_btm_idbuffer_io_status_read_chk_data[8]; //��8���� i/o �������� ����
	int n_temp_btm_idbuffer_exist_status_check_info[8];
 

	//���� �۾����� ���� 
	int n_tbox_receive_count; //forming MC ���� t box ���� 
	int n_ssd_receive_count; //loader ��񿡼� ���� ssd ���� 

	int n_tbox_work_count; //�۾��� t box ����
	int n_tbox_output_count; //label MC�� ���� t box ���� 
	

	//���̵� fold �۾��� left/right ���� ���� 
	int n_index_move_sidecover_fold_flag; //0�� left, 1:right

	long l_handler_recovery_flag[4]; //2010,0727 
	//[0]=>������� ���� ���(0:������� ���� ����, 1:������尡 ���� ����(�̶��� �ʱ�ȭ�� �������θ� ��� ��  �ִ�) 
	//[1]=>�ʱ�ȭ�� ������� ���� ��/�� Ȯ�� (0:������� ���þ���, 1:������� ����)
	//[2]=>���� ��� ���� �ð� ���� 
	//[3]=>�ʱ�ȭ�� ������� ���ýð� 

	char c_lot_id_sealing_mc[3][30]; //[0]:���� lot ���� , [1]:������ �� ����� ����, [2]: �ٷ��� ���� lot ���� 

	int n_newbcr_format;

	//2015.0529
	int n_var_mat_density[6];
	int n_var_mat_bcr[4];
	int n_var_mat_ribbon[4];
	int m_var_reject[3];
	int m_var_all_reject;
};
extern  st_variable_param  st_var; //0:load tray,1:bin1,2:bin2,3:bin3,4:bin4,5:upper buffer,6:lower buffer

enum 
{
	BCR_1,
	BCR_2,
	BCR_3,
	BCR_4,
};


struct st_bcrinfo_param
{
	char m_cLotid[30];
	char m_cBoatid[4];
	char m_cSerial[30];
	char m_cLabelcode[30];
	char m_cRibboncode[30];
	char m_cMode[10];
	char m_cRetry[10];
	char m_cCnt[10];


	char m_recvFormat[1000];
};
extern st_bcrinfo_param st_bcrinfo[4];

enum vis_density_info
{
	DENSITY_PICKPOS,
	DENSITY_READY1,
	DENSITY_READY2,
	DENSITY_RECEIVE
};

struct st_density_info_param
{
	char m_cDen_capa[30];
	char m_cDen_2D[30];
	char m_cDen_mdl[30];
	int nResult;
};
extern st_density_info_param st_density_info[6][4];


#define MAX_SHIFT_DATA_NUM 20
#define MAX_IO_STATUS_WAIT 100
#define STEP_SUB 100

enum lot_status_id_info //�� ������ �̵��Ǹ鼭 ������ ����Ʈ �Ѵ� 
{
	ID_LOT_EMPTY = 0, ID_LOT_START, ID_LOT_WORKING, ID_LOT_END  
};
enum idbuff_site
{
	CTL_LEFT =0, CTL_RIGHT, CTL_DUAL
};

//st_handler.mn_smema_front
//M_TOPID_LD1 //2
//M_TOPID_LD2 //8
//void CRun_Top_IDBuffer_Works::Run_Move_RecvIDBuffer()
enum idbuffer_move_info_shift //id buffer�� �̵��ϸ鼭 ������ ������ ���� �� �����ϸ鼭 ����Ʈ�Ѵ� 
{	
	SHIFT_IDBUFF_INDEX_ULD_RECV = 0, //add start by kwlee 2015.0109
	SHIFT_IDBUFF_INPUT_INDEX , //2014.1002
	SHIFT_IDBUFF_INDEX_DENSITY,
	SHIFT_IDBUFF_INDEX_BCR1,	
	SHIFT_IDBUFF_INDEX_BCR2,
	SHIFT_IDBUFF_INDEX_TOP,
	SHIFT_IDBUFF_INDEX_ULD,
	SHIFT_IDBUFF_INDEX_ULD_SEND,
	SHIFT_IDBUFF_SITE_ALL_CHK
};

enum idbuffer_unload_move_info_shift //id buffer�� �̵��ϸ鼭 ������ ������ ���� �� �����ϸ鼭 ����Ʈ�Ѵ� 
{	
	SHIFT_IDBUFF_INDEX_ULD_BTM = 9,
	SHIFT_IDBUFF_INDEX_ULD_CLAMP,
	SHIFT_IDBUFF_INDEX_ULD_LOAD,
	SHIFT_IDBUFF_INDEX_ULD_UNLOAD,
	SHIFT_IDBUFF_INDEX_ULD_NEXT,

	SHIFT_IDBUFF_UNLOAD_SITE_ALL_CHK
};


struct st_label_param
{
	char c_mdl_id[30];
	char c_lblCapa[30];
	char c_lbl2D[30]; 
	bool bExist;
	bool bOut;
	int nState;//2:fail 1:pass
}st_label;

struct st_bcr_param
{
	char c_lot_id[30];
	char c_serial[30];
	char c_Format[4000];
	bool bExist;
	bool bOut;
	int nState;//2:fail 1:pass

	int nCommand;	// jtkim 20141115 �� ���� ��û......
	int nComplete;	// jtkim 20141115 �� ���� ��û Ȯ�οϷ�....

}st_bcr;

struct st_barcode2_param
{
	char c_lot_id[2][30];

}st_barcode2;

struct st_top_param
{
	char c_model_id[30];
	int nState;
}st_top;

struct st_btm_param
{
	char c_model_id[30];
	int nState;
}st_btm;

//struct st_btm_rbt
//{
//	st_btm_param st_btm;
//};
//extern st_btm_rbt st_btm[2];

struct st_unload_rbt
{
	st_btm_param st_btm[2];
	bool bPick[2];
	int n_exist[2];
};
extern st_unload_rbt st_uld_rbt;


struct st_top_rbt_param
{
	struct st_top_param st_top;
	int nState;
};
extern st_top_rbt_param st_top_rbt[2];


struct st_barcode_feeder
{
	st_bcr_param st_bcr;
//	bool bPick;
};
extern st_barcode_feeder st_bcr_feeder[4];

struct st_barcode_rbt
{
	st_bcr_param st_bcr[2];
	bool bPick[2];
};
extern st_barcode_rbt st_bcr_rbt[2];


struct st_density_feeder
{
	st_label_param st_label;
// 	bool bPick;
};
extern st_density_feeder st_den_feeder[6];

struct st_density_rbt
{
	st_label_param st_label;
	bool bPick;
	int nBin;
};
extern st_density_rbt st_den_rbt[2];

struct st_reject_rbt
{
	st_bcr_param st_bcr;
	bool bPick[4];	
};
extern st_reject_rbt st_rej_rbt;

struct st_idbuffer_info_param //2013.0912 �߰� 
{ 
	//������ 	int n_init_flag; //�ʱ�ȭ ���� ����, �̰� CTL_NO �̸� �ʱ�ȭ�� ������� ���� ���۷�, Ȥ�� ���簡 ������ ����ó���Ͽ� ������ 
	
	int n_last_module[2]; //0:lot�� ���� ����Ǵ� id buffer, 1: lot start ���� �Ǵ� ����, 2:lot start�� ���� �������� ���� �Ǵ� ����  , 3:lot end flag 
	int n_skip_flag[2]; //�� ������ �۾��� ��ŵ�ϴ� ������ ���۸� �׳� ��������� 
	int n_idbuffer[2]; //[0]left, [1]right buffer 1��/0�� 
	int n_idbuff_num[2];  //id buffer�� ��ȣ, ���� ���ڵ� ������ �� 
	int n_exist[2]; //������/���� //������ [2][*]: [0]:left, [1]:right,  ssd tray
	int n_mode; //0:left, 1:rigth,2:dual ��� mode
	int n_bypass[2];//1 : btpass//2014,1102 ybs
	int n_lotstatus[2];
	
	int n_totalcnt; //lot ���۽� ���� ��ü ���� 	
	int n_count[2]; //�۾��� ���� //������ [2][*]: [0]:left, [1]:right,  ssd tray
	int n_out_count[2]; //�۾��� ���� //������ [2][*]: [0]:left, [1]:right, ssd tray
	
	char c_lot_id[2][30];
	char c_part_num[2][30];
	char c_serial[2][30];
// 	char c_visionmodel[30];	
	char c_var[2][30];	//2014,1102 ybs
	char c_product_id[2][30];//2014,1102 ybs
// 	char c_fmtBcr[2][1000];
	char c_acce_code[2][30];
	char c_tbox_code[2][30];

	int nRetLabel;
	int nBcr1[2];//CTL_GOOD, CTL_ERROR ����üũ
	int nBcr2[2];//CTL_GOOD, CTL_ERROR ����üũ
	int nTop_vis[2];
	int nBtm_vis;

	// jtkim 20141115 
	int nBcrPos[2];		// barcode label ������ġ Ȯ���ϱ� ����.......
	int nBcrExist[2];	// barcode label pickup,���� ����.....

	st_label_param st_label[2];
	st_bcr_param st_barcode1[2];
	st_bcr_param st_barcode2[2];
	st_top_param st_top[2];
	st_btm_param st_uld_rbt;

	//2015.0211
	int n_RetVision[2];//[0]LEFT [1]RIGHT
	//1111 (BCR1:BCR2:TOP:BOTTOM)
	// ->1000 | 0100 | 0010 | 0001 1:GOOD 2:BAD 0:NOT OR READY
	
	
};
extern st_idbuffer_info_param	st_idbuff_info[MAX_SHIFT_DATA_NUM]; //2014.1107 [11]; //����� ���� 32��(1~32), ID Buffer�� ���� ������ ������ �ִ�


struct st_xgemdata
{
	CString m_str_xgmInit;
	CString m_str_connect;
	CString m_str_bufferin;
	CString m_str_loadtray;
	CString m_str_unloadtray;
	
	CString m_str_onSocket;
	CString m_str_offSocket;
	CString m_str_machine_status;
	CString m_str_lotid;
	CString m_str_part_id;
	CString m_str_alarm;
	CString m_str_ppid;
	CString m_str_buffer1_id;
	CString m_str_buffer2_id;
	CString m_str_buffer1_serial;
	CString m_str_buffer2_serial;
	CString	m_strBuf1TactTime;
	CString	m_strBuf2TactTime;
	
	long	m_lTactTime;
	long	m_lBuf1TactTime;
	long	m_lBuf2TactTime;
	long	m_lTotCnt;
	long	m_lPassCnt;
	long	m_lFailCnt;
	int		m_nSokXpos;
	int		m_nSokYpos;
	
};
extern st_xgemdata st_xgem;


struct st_copy_data
{
	int		mn_mdl;	
	char	str_partid[100];
};
extern struct st_copy_data	*st_copydata;

#endif


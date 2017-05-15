// Dialog_Motor_Axis_1.cpp : implementation file
//

#include "stdafx.h"
#include "handler.h"
#include "Dialog_Motor_Axis_1.h"
#include "Public_Function.h"
#include "Cmmsdk.h"
#include "Dialog_KeyPad.h"

#include "CtlBd_Function.h"
#include "CtlBd_Library.h"

#include "SrcPart/PartFunction.h"
#include "SrcBase/ALocalization.h"
#include "Run_Motors.h"
#include "COMI_Manager.h"
#include "IO_Manager.h"
#include "SrcPart/APartHandler.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_Motor_Axis_1 dialog
#define TM_STATUS_CHECK		100
#define TM_POSITION_CHECK	200

CDialog_Motor_Axis_1::CDialog_Motor_Axis_1(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Motor_Axis_1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_Motor_Axis_1)
	//}}AFX_DATA_INIT
	m_n_move_mode = 0;
}


void CDialog_Motor_Axis_1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Motor_Axis_1)
	DDX_Control(pDX, IDC_BTN_APPLY, m_btn_apply);
	DDX_Control(pDX, IDC_BTN_RIGHT, m_btn_right);
	DDX_Control(pDX, IDC_BTN_LEFT, m_btn_left);
	DDX_Control(pDX, IDC_BTN_HOME, m_btn_home);
	DDX_Control(pDX, IDC_GROUP_AXIS_INFO, m_group_axis_info);
	DDX_Control(pDX, IDC_GROUP_MOTOR, m_group_motor);
	DDX_Control(pDX, IDC_GROUP_MOVE, m_group_move);
	DDX_Control(pDX, IDC_BTN_EMG, m_btn_emg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_Motor_Axis_1, CDialog)
	//{{AFX_MSG_MAP(CDialog_Motor_Axis_1)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_EMG, OnBtnEmg)
	ON_BN_CLICKED(IDC_BTN_HOME, OnBtnHome)
	ON_BN_CLICKED(IDC_BTN_APPLY, OnBtnApply)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_MESSAGE(SSM_CLICK  , OnCellClick)
	ON_MESSAGE(WMU_CHILD_LBUTTON_DOWN, OnUserLButtonDown)
	ON_MESSAGE(WMU_CHILD_LBUTTON_UP, OnUserLButtonUp)
	ON_MESSAGE( WM_MOTOR_COMPLETION, OnMotorCompletion)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Motor_Axis_1 message handlers

BOOL CDialog_Motor_Axis_1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
// 	m_p_font = NULL;
// 	m_p_font = new CFont;
// 	m_p_font->CreateFont(14,0,0,0,900,0,0,0,0,0,0,ANTIALIASED_QUALITY,0,"MS Sans Serif");

	m_d_data = 0;
	
// 	Data_Init( 0 );
// 
// 	Init_Grid_Pos();
// 	Init_Grid_Info();
// 	Init_Label();
 	Init_Group();
// 	Init_Digit();
// 	Init_Radio();
//	Init_Button();

	if (COMI.mn_motorbd_init_end)
	{
		SetTimer(TM_STATUS_CHECK, 100, NULL);
		SetTimer(TM_POSITION_CHECK, 100, NULL);
	}

	st_handler.cwnd_motorAxis = this;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_Motor_Axis_1::Init_Group()
{
	CSxLogFont main_font(15,FW_SEMIBOLD,false,"Arial");
	
	m_group_motor.SetFont(main_font);
	m_group_motor.SetCatptionTextColor(RGB(145,25,0));
	m_group_motor.SetFontBold(TRUE);
	m_group_motor.SetWindowText(m_str_axis_name);

	m_group_move.SetFont(main_font);
	m_group_move.SetCatptionTextColor(RGB(145,25,0));
	m_group_move.SetFontBold(TRUE);
	m_group_move.SetWindowText("Move");

	m_group_axis_info.SetFont(main_font);
	m_group_axis_info.SetCatptionTextColor(RGB(145,25,0));
	m_group_axis_info.SetFontBold(TRUE);
	m_group_axis_info.SetWindowText("Position Information");
}

void CDialog_Motor_Axis_1::Init_Button()
{
	short	shBtnColor = 30;
	CString strTmp;

	m_btn_emg.SetFont(Func.mp_motoraxis1_font);
	m_btn_emg.SetIcon(IDI_EMG_STOP);
	m_btn_emg.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btn_emg.SetButtonColor(1);
	strTmp.Format("%s Emergency Step", m_str_axis_name);
	m_btn_emg.SetTooltipText(strTmp);

// 	if (m_str_axis_name == "BIN 1 Z" ||
// 		m_str_axis_name == "BIN 2 Z" ||
// 		m_str_axis_name == "REJECT Z" ||
// 		m_str_axis_name == "ROBOT Z")
// 	{
// 		m_btn_left.SetIcon(IDI_UP);
// 	}
// 	else if( m_str_axis_name == "BIN 1 R" ||
// 		m_str_axis_name == "BIN 2 R" ||
// 		m_str_axis_name == "REJECT R" )
// 	{
// 		m_btn_left.SetIcon( IDI_UP );
// 	}
// 	else if( m_str_axis_name == "ROBOT X" )
// 	{
// 		m_btn_left.SetIcon( IDI_LEFT );
// 	}
// 	else
// 	{
// 		m_btn_left.SetIcon(IDI_DN);
// 	}

	///////20131115
	if (m_str_axis_name == "Roller Index X" || m_str_axis_name == "Density Vision X" || m_str_axis_name == "Reject X" || m_str_axis_name == "BCR Vision X" || m_str_axis_name == "Bottom X" || m_str_axis_name == "Top X" || m_str_axis_name == "Top LD 2" || m_str_axis_name == "Bottom ULD 1")
	{
		m_btn_left.SetIcon(IDI_RIGHT);
	}
	else if(m_str_axis_name == "BCR Attach  X" || m_str_axis_name == "Attach X" || m_str_axis_name == "Top LD 1" || m_str_axis_name == "Bottom ULD 2")
	{
		m_btn_left.SetIcon( IDI_LEFT );
	}
	else if (m_str_axis_name == "Rolling 1" || m_str_axis_name == "Rolling 2" || m_str_axis_name == "Attach Y" || m_str_axis_name == "Unload Robot Y" || m_str_axis_name == "EL")
	{
		m_btn_left.SetIcon(IDI_DN);
	}
	else if (m_str_axis_name == "Rolling Pusher" || m_str_axis_name == "Attach Z1" || m_str_axis_name == "Attach Z2" || m_str_axis_name == "Robot Z" || m_str_axis_name == "Stacker Z" || m_str_axis_name == "BCR Attach  Z1" || m_str_axis_name == "BCR Attach  Z2" || m_str_axis_name == "Box Guide Pitch")
	{
		m_btn_left.SetIcon(IDI_UP);
	}
	else if (m_str_axis_name == "CV Pitch" || m_str_axis_name == "BCR Attach  Y")
	{
		m_btn_left.SetIcon(IDI_DN);
	}
	else if (m_str_axis_name == "BCR Feeder1" || m_str_axis_name == "BCR Feeder2" || m_str_axis_name == "BCR Feeder3" || m_str_axis_name == "BCR Feeder4")
	{
		m_btn_left.SetIcon(IDI_DN);
	}

	
	
///////	
	m_btn_left.SetTag(IDC_BTN_LEFT);
	m_btn_left.SetFont(Func.mp_motoraxis1_font);
	m_btn_left.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btn_left.SetButtonColor(1);

// 	if (m_str_axis_name == "BIN 1 Z" ||
// 		m_str_axis_name == "BIN 2 Z" ||
// 		m_str_axis_name == "REJECT Z" ||
// 		m_str_axis_name == "ROBOT Z" )
// 	{
// 		m_btn_right.SetIcon(IDI_DN);
// 	}
// 	else if( m_str_axis_name == "ROBOT X" )
// 	{
// 		m_btn_right.SetIcon( IDI_RIGHT );
// 	}
// 	else
// 	{
// 		m_btn_right.SetIcon(IDI_UP);
// 	}

	///////20131115
	if (m_str_axis_name == "Roller Index X" || m_str_axis_name == "Density Vision X" || m_str_axis_name == "Reject X" || m_str_axis_name == "BCR Vision X" || m_str_axis_name == "Bottom X" || m_str_axis_name == "Top X" || m_str_axis_name == "Top LD 2" || m_str_axis_name == "Bottom ULD 1")
	{
		m_btn_right.SetIcon( IDI_LEFT );
	}
	else if(m_str_axis_name == "BCR Attach  X" || m_str_axis_name == "Attach X" || m_str_axis_name == "Top LD 1" || m_str_axis_name == "Bottom ULD 2")
	{
		m_btn_right.SetIcon( IDI_RIGHT );
	}
	else if (m_str_axis_name == "Rolling 1" || m_str_axis_name == "Rolling 2" || m_str_axis_name == "Attach Y" || m_str_axis_name == "Unload Robot Y" || m_str_axis_name == "EL")
	{
		m_btn_right.SetIcon(IDI_UP);
	}
	else if (m_str_axis_name == "Rolling Pusher" || m_str_axis_name == "Attach Z1" || m_str_axis_name == "Attach Z2" || m_str_axis_name == "Robot Z" || m_str_axis_name == "Stacker Z" || m_str_axis_name == "BCR Attach  Z1" || m_str_axis_name == "BCR Attach  Z2" || m_str_axis_name == "Box Guide Pitch")
	{
		m_btn_right.SetIcon(IDI_DN);
	}
	else if (m_str_axis_name == "CV Pitch" || m_str_axis_name == "BCR Attach  Y")
	{
		m_btn_right.SetIcon(IDI_UP);
	}
	else if (m_str_axis_name == "BCR Feeder1" || m_str_axis_name == "BCR Feeder2" || m_str_axis_name == "BCR Feeder3" || m_str_axis_name == "BCR Feeder4")
	{
		m_btn_right.SetIcon(IDI_UP);
	}
	


///////	
	m_btn_right.SetTag(IDC_BTN_RIGHT);
	m_btn_right.SetFont(Func.mp_motoraxis1_font);
	m_btn_right.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btn_right.SetButtonColor(1);

	m_btn_home.SetTag(IDC_BTN_HOME);
	m_btn_home.SetFont(Func.mp_motoraxis1_font);
	m_btn_home.SetIcon(IDI_HOME);
	m_btn_home.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btn_home.SetButtonColor(1);
}

void CDialog_Motor_Axis_1::Init_Label()
{

}

void CDialog_Motor_Axis_1::Init_Radio()
{

}

void CDialog_Motor_Axis_1::Init_Digit()
{

}

void CDialog_Motor_Axis_1::Init_Grid_Pos()
{
	int   i, j;
	CString str_tmp;
	m_grid_motor_pos = (TSpread*)GetDlgItem(IDC_CUSTOM_MOTOR_POS);

	//m_p_grid.GridReset(m_grid_motor_pos);
	// �빮�� 
	m_p_grid.GridCellSelectDisplay(m_grid_motor_pos, TRUE);
	
	m_p_grid.GridRowHeader(m_grid_motor_pos, FALSE);
	m_p_grid.GridColHeader(m_grid_motor_pos, TRUE);
	m_p_grid.GridHorizontal(m_grid_motor_pos, FALSE);
	m_p_grid.GridVertical(m_grid_motor_pos, TRUE);
	m_p_grid.GridAutoSize(m_grid_motor_pos, FALSE);
	m_p_grid.GridAutoSize(m_grid_motor_pos, FALSE);
	m_p_grid.GridCellRows(m_grid_motor_pos, m_n_position_num);
	m_p_grid.GridCellCols(m_grid_motor_pos, 4);
	
	for(i=0; i<m_n_position_num+1; i++)
	{
		m_p_grid.GridCellHeight_L(m_grid_motor_pos, i, 30);
		for(j=0; j<4; j++)
		{
			
			switch(j)
			{
				case 0:
					m_p_grid.GridCellWidth_L(m_grid_motor_pos, j+1, 25);
					break;
				case 1:
					m_p_grid.GridCellWidth_L(m_grid_motor_pos, j+1, 15);
					break;
				case 2:
					m_p_grid.GridCellWidth_L(m_grid_motor_pos, j+1, 11);
					break;
				case 3:
					m_p_grid.GridCellWidth_L(m_grid_motor_pos, j+1, 11);
					break;
			}
			m_p_grid.GridCellControlStatic(m_grid_motor_pos, i, j+1);
		}
	}
	
	m_p_grid.GridCellFont(m_grid_motor_pos, 0, 1, "MS Sans Serif", 12);
	m_p_grid.GridCellColor(m_grid_motor_pos, 0, 1, BLACK_C, YELLOW_C);
	m_p_grid.GridCellText(m_grid_motor_pos, 0, 1, "-");
	
	m_p_grid.GridCellFont(m_grid_motor_pos, 0, 2, "MS Sans Serif", 12);
	m_p_grid.GridCellColor(m_grid_motor_pos, 0, 2, BLACK_C, YELLOW_C);
	m_p_grid.GridCellText(m_grid_motor_pos, 0, 2, "Positon");
	
	m_p_grid.GridCellFont(m_grid_motor_pos, 0, 3, "MS Sans Serif", 12);
	m_p_grid.GridCellColor(m_grid_motor_pos, 0, 3, BLACK_C, YELLOW_C);
	m_p_grid.GridCellText(m_grid_motor_pos, 0, 3, "Move");
	
	m_p_grid.GridCellFont(m_grid_motor_pos, 0, 4, "MS Sans Serif", 15);
	m_p_grid.GridCellColor(m_grid_motor_pos, 0, 4, BLACK_C, YELLOW_C);
	m_p_grid.GridCellText(m_grid_motor_pos, 0, 4, "Read");
	
	for(i=0; i<m_n_position_num; i++)
	{
		m_p_grid.GridCellColor(m_grid_motor_pos, i+1, 1, BLACK_C, YELLOW_C);
		m_p_grid.GridCellText(m_grid_motor_pos, i+1, 1, m_str_position_name[i]);
		
		m_p_grid.GridCellFont(m_grid_motor_pos, i+1, 2, "MS Sans Serif", 10);
		m_p_grid.GridCellColor(m_grid_motor_pos, i+1, 2, GREEN_L, BLACK_C);
		str_tmp.Format("%.3f", m_d_position[i][1]);
		m_p_grid.GridCellText(m_grid_motor_pos, i+1, 2, str_tmp);
		
		m_p_grid.GridCellFont(m_grid_motor_pos, i+1, 3, "MS Sans Serif", 15);
		m_p_grid.GridCellColor(m_grid_motor_pos, i+1, 3, TEXT_BC, BLUE_C);
		m_p_grid.GridCellText(m_grid_motor_pos, i+1, 3, "Go.");
		
		m_p_grid.GridCellFont(m_grid_motor_pos, i+1, 4, "MS Sans Serif", 15);
		m_p_grid.GridCellColor(m_grid_motor_pos, i+1, 4, TEXT_BC, RED_C);
		m_p_grid.GridCellText(m_grid_motor_pos, i+1, 4, "Read.");
	}

	if( m_grid_motor_pos != NULL )
	{
		m_grid_motor_pos = NULL;
		delete m_grid_motor_pos;
	}
}

void CDialog_Motor_Axis_1::Data_Apply()
{
	int i;
	
	for(i=0; i<m_n_position_num; i++)
	{
		st_motor[m_n_axis].d_pos[i]		= m_d_position[i][1];
	}
}

void CDialog_Motor_Axis_1::Data_Backup()
{
	int i;
	
	for(i=0; i<m_n_position_num; i++)
	{
		m_d_position[i][0]	= m_d_position[i][1];
	}
}

int CDialog_Motor_Axis_1::Data_Comparison()
{
	int i;
	int Ret = CTLBD_RET_GOOD;
	
	for(i=0; i<m_n_position_num; i++)
	{
		if (m_d_position[i][0] != m_d_position[i][1])
		{
			return CTLBD_RET_ERROR;
		}
	}
	
	return CTLBD_RET_GOOD;
}

void CDialog_Motor_Axis_1::Data_HistoryLog()
{
	int i;
	CString str_msg;
	
	for(i=0; i<m_n_position_num; i++)
	{
		if (m_d_position[i][0] != m_d_position[i][1])
		{
			//str_msg.Format( "[%s] Axis Change %.3f -> %.3f", m_str_axis_name, m_d_position[i][0], m_d_position[i][1]);
			str_msg.Format( "[%s] Axis Change [%s] %.3f -> %.3f", m_str_axis_name, m_str_position_name[i], m_d_position[i][0], m_d_position[i][1]);
			Func.On_LogFile_Add(0, str_msg);
		}
	}
}

void CDialog_Motor_Axis_1::Data_Recovery()
{
	int i;
	
	for(i=0; i<m_n_position_num; i++)
	{
		m_d_position[i][1]	= m_d_position[i][0];
	}

}

void CDialog_Motor_Axis_1::Data_Init( int iSelected )
{
	int i;
	
	m_n_move_mode		= 0;
	m_n_axis			= st_motor_info.n_part_axis[m_n_part][iSelected];
	m_n_position_num	= st_motor_info.n_axis_pos_num[m_n_part][iSelected];
	
	for(i=0; i<m_n_position_num; i++)
	{
		m_str_position_name[i]	= st_motor_info.str_axis_pos_name[m_n_part][iSelected][i];
		m_str_position_bmp[i]	= st_motor_info.str_axis_pos_info[m_n_part][iSelected][i];
	}
	
	m_str_axis_name = st_motor_info.str_part_axis_name[m_n_part][iSelected];
	m_n_minus_el	= st_motor_info.n_axis_minus_el[m_n_part][iSelected];
	m_n_plus_el		= st_motor_info.n_axis_plus_el[m_n_part][iSelected];
	m_n_home		= st_motor_info.n_axis_home[m_n_part][iSelected];
	m_n_sd			= st_motor_info.n_axis_sd[m_n_part][iSelected];
	
	for(i=0; i<m_n_position_num; i++)
	{
		m_d_position[i][1]	= st_motor[m_n_axis].d_pos[i];
	}
	
	Data_Backup();
}

void CDialog_Motor_Axis_1::MotorStatusCheck()
{
	TSpread* m_gridMotInfo; 
	m_gridMotInfo = (TSpread*)GetDlgItem(IDC_CUSTOM_MOTOR_INFO);

	if (m_n_home == 0)
	{
		if (m_n_sd == 1)
		{
			if (m_n_minus_el == 1)
			{
				if (COMI.Get_MotIOSensor(m_n_axis, MOT_SENS_ELM) == CTLBD_RET_GOOD)
				{
					m_p_grid.GridCellColor(m_gridMotInfo, 2, 1, RED_C, WHITE_C);
				}
				else
				{
					m_p_grid.GridCellColor(m_gridMotInfo, 2, 1, BLACK_L, WHITE_C);
				}
			}
			
			if (COMI.Get_MotIOSensor(m_n_axis, MOT_SENS_SD) == CTLBD_RET_GOOD)
			{
				m_p_grid.GridCellColor(m_gridMotInfo, 2, 3, RED_C, WHITE_C);
			}
			else
			{
				m_p_grid.GridCellColor(m_gridMotInfo, 2, 3, BLACK_L, WHITE_C);
			}
			
			if (m_n_plus_el == 1)
			{
				if (COMI.Get_MotIOSensor(m_n_axis, MOT_SENS_ELP) == CTLBD_RET_GOOD)
				{
					m_p_grid.GridCellColor(m_gridMotInfo, 2, 5, RED_C, WHITE_C);
				}
				else
				{
					m_p_grid.GridCellColor(m_gridMotInfo, 2, 5, BLACK_L, WHITE_C);
				}
			}
		}
		else
		{
			if (m_n_minus_el == 1)
			{
				if (COMI.Get_MotIOSensor(m_n_axis, MOT_SENS_ELM) == CTLBD_RET_GOOD)
				{
					m_p_grid.GridCellColor(m_gridMotInfo, 2, 1, RED_C, WHITE_C);
				}
				else
				{
					m_p_grid.GridCellColor(m_gridMotInfo, 2, 1, BLACK_L, WHITE_C);
				}
			}
			
			if (m_n_plus_el == 1)
			{
				if (COMI.Get_MotIOSensor(m_n_axis, MOT_SENS_ELP) == CTLBD_RET_GOOD)
				{
					m_p_grid.GridCellColor(m_gridMotInfo, 2, 4, RED_C, WHITE_C);
				}
				else
				{
					m_p_grid.GridCellColor(m_gridMotInfo, 2, 4, BLACK_L, WHITE_C);
				}
			}
		}
	}
	else
	{
		if (m_n_minus_el == 1)
		{
			if (COMI.Get_MotIOSensor(m_n_axis, MOT_SENS_ELM) == CTLBD_RET_GOOD)
			{
				m_p_grid.GridCellColor(m_gridMotInfo, 2, 1, RED_C, WHITE_C);
			}
			else
			{
				m_p_grid.GridCellColor(m_gridMotInfo, 2, 1, BLACK_L, WHITE_C);
			}
		}
		
		if (COMI.Get_MotIOSensor(m_n_axis, MOT_SENS_HOME) == CTLBD_RET_GOOD)
		{
			m_p_grid.GridCellColor(m_gridMotInfo, 2, 3, RED_C, WHITE_C);
		}
		else
		{
			m_p_grid.GridCellColor(m_gridMotInfo, 2, 3, BLACK_L, WHITE_C);
		}
		
		if (m_n_plus_el == 1)
		{
			if (COMI.Get_MotIOSensor(m_n_axis, MOT_SENS_ELP) == CTLBD_RET_GOOD)
			{
				m_p_grid.GridCellColor(m_gridMotInfo, 2, 5, RED_C, WHITE_C);
			}
			else
			{
				m_p_grid.GridCellColor(m_gridMotInfo, 2, 5, BLACK_L, WHITE_C);
			}
		}
	}

	if (COMI.Get_MotPower(m_n_axis) == CTLBD_RET_GOOD)
	{
		m_p_grid.GridCellColor(m_gridMotInfo, 4, 1, RED_C, WHITE_C);
	}
	else
	{
		m_p_grid.GridCellColor(m_gridMotInfo, 4, 1, BLACK_L, WHITE_C);
	}

	if (COMI.Get_MotAlarmStatus(m_n_axis) == CTLBD_RET_GOOD)
	{
		m_p_grid.GridCellColor(m_gridMotInfo, 6, 1, BLACK_L, WHITE_C);
	}
	else
	{
		m_p_grid.GridCellColor(m_gridMotInfo, 6, 1, RED_C, WHITE_C);
	}


	if( m_gridMotInfo != NULL )
	{
		m_gridMotInfo = NULL;
		delete m_gridMotInfo;
	}
}

void CDialog_Motor_Axis_1::MotorPositionCheck()
{
//	m_dgt_current_pos.SetVal(COMI.Get_MotCurrentPos(st_part.n_motor_axis[MOTOR_PART]));
	CString str_tmp;

	TSpread* m_gridMotInfo;
	m_gridMotInfo = (TSpread*)GetDlgItem(IDC_CUSTOM_MOTOR_INFO);

	str_tmp.Format("%.3f", g_comiMgr.Get_MotCurrentPos(m_n_axis));
	m_p_grid.GridCellText(m_gridMotInfo, 8, 3, str_tmp);

	if( m_gridMotInfo != NULL )
	{
		m_gridMotInfo = NULL;
		delete m_gridMotInfo;
	}
}

void CDialog_Motor_Axis_1::OnCellClick(WPARAM wParam, LPARAM lParam)
{
	LPSS_CELLCOORD lpcc = (LPSS_CELLCOORD)lParam;
	CDialog_Message msg_dlg;

	CString strTmp, strChange, str_file;
	CString str_tmp, str_data;
	double value;
	int nResponse;

	CString strText;
	
	CDialog_KeyPad	pad_dlg;
	
	if (st_handler.mn_menu_lock) return;

	if (wParam == IDC_CUSTOM_MOTOR_POS)
	{
		if (lpcc->Row == 0) return;

		m_grid_motor_pos = (TSpread*)GetDlgItem(IDC_CUSTOM_MOTOR_POS);
		
		m_n_cmd_row	= lpcc->Row;
		m_n_cmd_col	= lpcc->Col;

		switch(lpcc->Col)
		{
		case 1:
			str_file.Format("C:\\AMT8590\\Bmp\\%s", m_str_position_bmp[lpcc->Row-1]);
			m_p_bmp_view.Load(str_file);
			
			Invalidate(FALSE);
			break;

		case 2:				
			strText = m_p_grid.GridCellText(m_grid_motor_pos, lpcc->Row, lpcc->Col - 1);
			st_msg.mstr_keypad_msg.Format("[%s Motor] %s set", m_str_axis_name, strText);

			strTmp = m_p_grid.GridCellText(m_grid_motor_pos, lpcc->Row, lpcc->Col);
			st_msg.mstr_keypad_val = strTmp;
			
			strTmp = KeyPad.GetNumEditString_D(COMI.md_limit_position[m_n_axis][0], COMI.md_limit_position[m_n_axis][1], double(atof(st_msg.mstr_keypad_val)), st_msg.mstr_keypad_msg);
			
			if( AMotor::CheckTeachSafety( m_n_axis, lpcc->Row-1, atof(strTmp) ) == false )
			{
				m_strTempMSG = "�� ƼĪ���� ������ ���� �ֽ��ϴ�. ����Ͻðڽ��ϱ�?";
				if ( g_local.GetLocalType() == LOCAL_ENG ) m_strTempMSG = _T("It might dangerous this teaching value. Do you want to continue?");
				if( DoModal_Select( m_strTempMSG ) != IDOK )
				{
					g_ioMgr.set_out_bit(st_io.o_buzzer_1, IO_ON);
					break;
				}
			}
			m_d_position[lpcc->Row-1][1] = atof(strTmp);
			m_p_grid.GridCellText(m_grid_motor_pos, lpcc->Row, lpcc->Col, strTmp);
			break;

		case 3:
			{
				if (COMI.mn_motorbd_init_end != TRUE)  
				{
					if (DoModal_Msg( g_local.Get("L_M_0000") ) == IDOK)
						return ;
				}
				
				m_p_grid.GridCellText(m_grid_motor_pos, lpcc->Row, lpcc->Col, "ing...");
				m_p_grid.GridCellColor(m_grid_motor_pos, lpcc->Row, lpcc->Col, NOR_C, BLACK_C);
				
				double dMotGotoPos = m_d_position[lpcc->Row-1][1];
				GETMOTOR( (ENUM_MOTOR)m_n_axis ).SetMotGotoPos( dMotGotoPos );
				
				nResponse = Func.OnMotor_Go_Check(m_n_axis, dMotGotoPos);
				
				if (nResponse != IDOK)
				{
					MotorCompletion(m_n_cmd_row, m_n_cmd_col);
					return;
				}
				
				if (dMotGotoPos < 0)
				{
					MotorCompletion(m_n_cmd_row, m_n_cmd_col);
					//return;  //ybs
				}
				
				if (st_handler.mn_menu_lock != TRUE)
				{
					st_handler.mn_menu_lock = TRUE;
				}
				// =============================================================================
				
				GETMOTOR( (ENUM_MOTOR)m_n_axis ).MotorStepClear();
				//2014,0108
// 				if(m_n_axis == MOTOR_PICKER_X)
// 				{
// 					if( g_ioMgr.get_in_bit( st_io.i_safety_test_zpos1_chk, IO_ON) == IO_OFF &&
// 						g_ioMgr.get_in_bit( st_io.i_safety_test_zpos2_chk, IO_ON) == IO_OFF &&
// 						g_ioMgr.get_in_bit( st_io.i_safety_test_zpos3_chk, IO_ON) == IO_OFF &&
// 						g_ioMgr.get_in_bit( st_io.i_safety_test_zpos4_chk, IO_ON) == IO_OFF &&
// 						g_ioMgr.get_in_bit( st_io.i_safety_test_zpos5_chk, IO_ON) == IO_OFF )
// 					{
// 						//040008 0 A " "Loading Buffer Z Move Safety Check Error."
// 						CTL_Lib.Alarm_Error_Occurrence( 400, CTL_dWARNING, "040001" );
// 						return;
// 					}
// 					
// 				}
				GETMOTOR( (ENUM_MOTOR)m_n_axis ).MotorMoveStart( dMotGotoPos, st_basic.nManualSpeed, MMMODE_MANUAL );
				str_tmp.Format( "[%s] Axis Move start -> %.3f", m_str_axis_name, dMotGotoPos);
				Func.On_LogFile_Add(0, str_tmp);

			}
			
			break;

		case 4:
			if (COMI.mn_motorbd_init_end != TRUE)  
			{
				if (DoModal_Msg( g_local.Get("L_M_0000") ) == IDOK)
					return ;
			}
		
			value = g_comiMgr.Get_MotCurrentPos(m_n_axis);  // FASTECH ���� Ư�� ���� Ŀ��Ʈ ��ġ ���� �Լ� //
			
			nResponse = Func.On_Encoder_Check(value);

			if (nResponse == CTL_YES)
			{
				if( AMotor::CheckTeachSafety( m_n_axis, lpcc->Row-1, value ) == false )
				{
					m_strTempMSG = "�� ƼĪ���� ������ ���� �ֽ��ϴ�. ����Ͻðڽ��ϱ�?";
					if ( g_local.GetLocalType() == LOCAL_ENG ) m_strTempMSG = _T("It might dangerous this teaching value. Do you want to continue?");
					if( DoModal_Select( m_strTempMSG ) != IDOK )
					{
						g_ioMgr.set_out_bit(st_io.o_buzzer_1, IO_ON);
						break;
					}
				}
				m_d_position[lpcc->Row-1][1] = value;
				strTmp.Format("%.3f", m_d_position[lpcc->Row-1][1]);
				m_p_grid.GridCellText(m_grid_motor_pos, lpcc->Row, 2, strTmp);	
			}
			//MotorCompletion(m_n_cmd_row, m_n_cmd_col);
			break;
		}

		if( m_grid_motor_pos != NULL )
		{
			m_grid_motor_pos = NULL;
			delete m_grid_motor_pos;
		}
	}
	else if (wParam == IDC_CUSTOM_MOTOR_INFO)
	{
		m_grid_motor_info = (TSpread*)GetDlgItem(IDC_CUSTOM_MOTOR_INFO);

		switch(lpcc->Row)
		{
		case 3:
		case 4:
			// Motor Power
			switch(lpcc->Col)
			{
			case 3:
			case 4:
				if (COMI.mn_motorbd_init_end != TRUE)  
				{
					if (DoModal_Msg( g_local.Get("L_M_0000") ) == IDOK)
					return ;
				}
				strTmp.Format("[Motor] (%s)_Axis Power Off", m_str_axis_name);
				Func.On_LogFile_Add(99, strTmp);
				Func.On_LogFile_Add(0, strTmp);
				
				COMI.Set_MotPower(m_n_axis, FALSE);
				break;
				
			case 5:
			case 6:
				if (COMI.mn_motorbd_init_end != TRUE)  
				{
					if (DoModal_Msg( g_local.Get("L_M_0000") ) == IDOK)
						return ;
				}
				strTmp.Format("[Motor] (%s)_Axis Power Off", m_str_axis_name);
				Func.On_LogFile_Add(99, strTmp);
				Func.On_LogFile_Add(0, strTmp);
				
				COMI.Set_MotPower(m_n_axis, TRUE);
				break;
			}
			break;
			
		case 5:
		case 6:
			// Alarm Reset
			if (lpcc->Col == 3 || lpcc->Col == 4 || lpcc->Col == 5 || lpcc->Col == 6)
			{
				if (COMI.mn_motorbd_init_end != TRUE)  
				{
					if (DoModal_Msg( g_local.Get("L_M_0000") ) == IDOK)
						return ;
				}
				
				strTmp.Format("[Motor] (%s)_Axis Alarm Clear", m_str_axis_name);
				Func.On_LogFile_Add(99, strTmp);
				Func.On_LogFile_Add(0, strTmp);
				
				COMI.Set_MotAlarmClear(m_n_axis);
			}
			break;
			
		case 8:
			// Motor Move
			switch(lpcc->Col)
			{
			case 1:
				if (m_n_move_mode != 0)
				{
					m_n_move_mode = 0;
					
					m_p_grid.GridCellColor(m_grid_motor_info, 8, 1, RED_C, BLACK_C);
					m_p_grid.GridCellColor(m_grid_motor_info, 8, 2, BLACK_L, YELLOW_C);
				}
				break;
				
			case 2:
				if (m_n_move_mode != 1)
				{
					m_n_move_mode = 1;
					
					m_p_grid.GridCellColor(m_grid_motor_info, 8, 1, BLACK_L, YELLOW_C);
					m_p_grid.GridCellColor(m_grid_motor_info, 8, 2, RED_C, BLACK_C);
				}
				break;
				
			case 5:
			case 6:
				strTmp.Format("%.3f", m_d_data);
				st_msg.mstr_keypad_msg.Format("[Jog Data]  set");
				st_msg.mstr_keypad_val = strTmp;
				
				strTmp = KeyPad.GetNumEditString_D((double)0.001, (double)10, double(atoi(st_msg.mstr_keypad_val)), st_msg.mstr_keypad_msg);
				
				m_d_data = atof(strTmp);
				m_p_grid.GridCellText(m_grid_motor_info, 8, 5, strTmp);
				break;
				
			}
			break;
		}

		if( m_grid_motor_info != NULL )
		{
			m_grid_motor_info = NULL;
			delete m_grid_motor_info;
		}
	}
}

void CDialog_Motor_Axis_1::MotorCompletion(int nrow, int ncol)
{
	if( nrow < 0 || ncol < 0 )
		return;

	m_grid_motor_pos = (TSpread*)GetDlgItem(IDC_CUSTOM_MOTOR_POS);
	
	if (ncol == 3)
	{
		m_p_grid.GridCellText(m_grid_motor_pos, nrow, ncol, "Go.");
		m_p_grid.GridCellColor(m_grid_motor_pos, nrow, ncol, TEXT_BC, BLUE_C);
	}
	else
	{
		m_p_grid.GridCellText(m_grid_motor_pos, nrow, ncol, "Read.");
		m_p_grid.GridCellColor(m_grid_motor_pos, nrow, ncol, TEXT_BC, RED_C);
	}

	if( m_grid_motor_pos != NULL )
	{
		m_grid_motor_pos = NULL;
		delete m_grid_motor_pos;
	}
}

void CDialog_Motor_Axis_1::OnButtonControl(BOOL b_flag)
{

}

void CDialog_Motor_Axis_1::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	CDC *pDC;

	// TODO: Add your message handler code here

	pDC = GetDlgItem(IDC_BMP_VIEW)->GetDC();
	GetDlgItem(IDC_BMP_VIEW)->GetWindowRect(rect);
	
	m_p_bmp_view.Show(pDC, CPoint(0, 0), CPoint(rect.Width(), rect.Height()), 0,0);
	
	ReleaseDC(pDC);
	// Do not call CDialog::OnPaint() for painting messages
}

void CDialog_Motor_Axis_1::Init_Grid_Info()
{
	int   i, j;
	CString str_tmp;

	m_grid_motor_info = (TSpread*)GetDlgItem(IDC_CUSTOM_MOTOR_INFO);
	
	//m_p_grid.GridReset(m_grid_motor_info);
	// �빮�� 
	m_p_grid.GridCellSelectDisplay(m_grid_motor_info, TRUE);
	
	m_p_grid.GridRowHeader(m_grid_motor_info, FALSE);
	m_p_grid.GridColHeader(m_grid_motor_info, FALSE);
	m_p_grid.GridHorizontal(m_grid_motor_info, FALSE);
	m_p_grid.GridVertical(m_grid_motor_info, FALSE);
	m_p_grid.GridAutoSize(m_grid_motor_info, FALSE);
	m_p_grid.GridAutoSize(m_grid_motor_info, FALSE);
	m_p_grid.GridCellRows(m_grid_motor_info, 8);
	m_p_grid.GridCellCols(m_grid_motor_info, 6);
	
	for(i=0; i<8; i++)
	{
		m_p_grid.GridCellHeight_L(m_grid_motor_info, i+1, 20);
		for(j=0; j<6; j++)
		{
			m_p_grid.GridCellWidth_L(m_grid_motor_info, j+1, 9.5);
	
			m_p_grid.GridCellControlStatic(m_grid_motor_info, i+1, j+1);
		}
	}

	if (m_n_home == 0)
	{
		if (m_n_sd == 1)
		{
			if (m_n_minus_el == 1)
			{
				m_p_grid.GridCellMerge(m_grid_motor_info, 1, 1, 1, 2);
				m_p_grid.GridCellFont(m_grid_motor_info, 1, 1, "MS Sans Serif", 12);
				m_p_grid.GridCellColor(m_grid_motor_info, 1, 1, BLUE_D, WHITE_C);
				m_p_grid.GridCellText(m_grid_motor_info, 1, 1, "�� ML");
				
				m_p_grid.GridCellMerge(m_grid_motor_info, 2, 1, 1, 2);
				m_p_grid.GridCellFont(m_grid_motor_info, 2, 1, "MS Sans Serif", 12);
				m_p_grid.GridCellColor(m_grid_motor_info, 2, 1, BLACK_L, WHITE_C);
				m_p_grid.GridCellText(m_grid_motor_info, 2, 1, "");
			}
			
			m_p_grid.GridCellMerge(m_grid_motor_info, 1, 3, 1, 2);
			m_p_grid.GridCellFont(m_grid_motor_info, 1, 3, "MS Sans Serif", 12);
			m_p_grid.GridCellColor(m_grid_motor_info, 1, 3, BLUE_D, WHITE_C);
			m_p_grid.GridCellText(m_grid_motor_info, 1, 3, "SD");
			
			m_p_grid.GridCellMerge(m_grid_motor_info, 2, 3, 1, 2);
			m_p_grid.GridCellFont(m_grid_motor_info, 2, 3, "MS Sans Serif", 12);
			m_p_grid.GridCellColor(m_grid_motor_info, 2, 3, BLACK_L, WHITE_C);
			m_p_grid.GridCellText(m_grid_motor_info, 2, 3, "");

			if (m_n_plus_el == 1)
			{
				m_p_grid.GridCellMerge(m_grid_motor_info, 1, 5, 1, 2);
				m_p_grid.GridCellFont(m_grid_motor_info, 1, 5, "MS Sans Serif", 12);
				m_p_grid.GridCellColor(m_grid_motor_info, 1, 5, BLUE_D, WHITE_C);
				m_p_grid.GridCellText(m_grid_motor_info, 1, 5, "�� PL");
				
				m_p_grid.GridCellMerge(m_grid_motor_info, 2, 5, 1, 2);
				m_p_grid.GridCellFont(m_grid_motor_info, 2, 5, "MS Sans Serif", 12);
				m_p_grid.GridCellColor(m_grid_motor_info, 2, 5, BLACK_L, WHITE_C);
				m_p_grid.GridCellText(m_grid_motor_info, 2, 5, "");
			}
		}
		else
		{
			if (m_n_minus_el == 1)
			{
				m_p_grid.GridCellMerge(m_grid_motor_info, 1, 1, 1, 3);
				m_p_grid.GridCellFont(m_grid_motor_info, 1, 1, "MS Sans Serif", 12);
				m_p_grid.GridCellColor(m_grid_motor_info, 1, 1, BLUE_D, WHITE_C);
				m_p_grid.GridCellText(m_grid_motor_info, 1, 1, "- ML");
				
				m_p_grid.GridCellMerge(m_grid_motor_info, 2, 1, 1, 3);
				m_p_grid.GridCellFont(m_grid_motor_info, 2, 1, "MS Sans Serif", 12);
				m_p_grid.GridCellColor(m_grid_motor_info, 2, 1, BLACK_L, WHITE_C);
				m_p_grid.GridCellText(m_grid_motor_info, 2, 1, "");
			}
			
			if (m_n_plus_el == 1)
			{
				m_p_grid.GridCellMerge(m_grid_motor_info, 1, 4, 1, 3);
				m_p_grid.GridCellFont(m_grid_motor_info, 1, 4, "MS Sans Serif", 12);
				m_p_grid.GridCellColor(m_grid_motor_info, 1, 4, BLUE_D, WHITE_C);
				m_p_grid.GridCellText(m_grid_motor_info, 1, 4, "�� PL");
				
				m_p_grid.GridCellMerge(m_grid_motor_info, 2, 4, 1, 3);
				m_p_grid.GridCellFont(m_grid_motor_info, 2, 4, "MS Sans Serif", 12);
				m_p_grid.GridCellColor(m_grid_motor_info, 2, 4, BLACK_L, WHITE_C);
				m_p_grid.GridCellText(m_grid_motor_info, 2, 4, "");
			}
		}
	}
	else
	{
		if (m_n_minus_el == 1)
		{
			m_p_grid.GridCellMerge(m_grid_motor_info, 1, 1, 1, 2);
			m_p_grid.GridCellFont(m_grid_motor_info, 1, 1, "MS Sans Serif", 12);
			m_p_grid.GridCellColor(m_grid_motor_info, 1, 1, BLUE_D, WHITE_C);
			m_p_grid.GridCellText(m_grid_motor_info, 1, 1, "�� ML");
			
			m_p_grid.GridCellMerge(m_grid_motor_info, 2, 1, 1, 2);
			m_p_grid.GridCellFont(m_grid_motor_info, 2, 1, "MS Sans Serif", 12);
			m_p_grid.GridCellColor(m_grid_motor_info, 2, 1, BLACK_L, WHITE_C);
			m_p_grid.GridCellText(m_grid_motor_info, 2, 1, "");
		}
		
		m_p_grid.GridCellMerge(m_grid_motor_info, 1, 3, 1, 2);
		m_p_grid.GridCellFont(m_grid_motor_info, 1, 3, "MS Sans Serif", 12);
		m_p_grid.GridCellColor(m_grid_motor_info, 1, 3, BLUE_D, WHITE_C);
		m_p_grid.GridCellText(m_grid_motor_info, 1, 3, "HOME");
		
		m_p_grid.GridCellMerge(m_grid_motor_info, 2, 3, 1, 2);
		m_p_grid.GridCellFont(m_grid_motor_info, 2, 3, "MS Sans Serif", 12);
		m_p_grid.GridCellColor(m_grid_motor_info, 2, 3, BLACK_L, WHITE_C);
		m_p_grid.GridCellText(m_grid_motor_info, 2, 3, "");

		if (m_n_plus_el == 1)
		{
			m_p_grid.GridCellMerge(m_grid_motor_info, 1, 5, 1, 2);
			m_p_grid.GridCellFont(m_grid_motor_info, 1, 5, "MS Sans Serif", 12);
			m_p_grid.GridCellColor(m_grid_motor_info, 1, 5, BLUE_D, WHITE_C);
			m_p_grid.GridCellText(m_grid_motor_info, 1, 5, "�� PL");
			
			m_p_grid.GridCellMerge(m_grid_motor_info, 2, 5, 1, 2);
			m_p_grid.GridCellFont(m_grid_motor_info, 2, 5, "MS Sans Serif", 12);
			m_p_grid.GridCellColor(m_grid_motor_info, 2, 5, BLACK_L, WHITE_C);
			m_p_grid.GridCellText(m_grid_motor_info, 2, 5, "");
		}
	}

	m_p_grid.GridCellMerge(m_grid_motor_info, 3, 1, 1, 2);
	m_p_grid.GridCellFont(m_grid_motor_info, 3, 1, "MS Sans Serif", 12);
	m_p_grid.GridCellColor(m_grid_motor_info, 3, 1, BLUE_D, WHITE_C);
	m_p_grid.GridCellText(m_grid_motor_info, 3, 1, "Motor Power");
	
	m_p_grid.GridCellMerge(m_grid_motor_info, 4, 1, 1, 2);
	m_p_grid.GridCellFont(m_grid_motor_info, 4, 1, "MS Sans Serif", 12);
	m_p_grid.GridCellColor(m_grid_motor_info, 4, 1, BLACK_L, WHITE_C);
	m_p_grid.GridCellText(m_grid_motor_info, 4, 1, "");

	m_p_grid.GridCellMerge(m_grid_motor_info, 3, 3, 2, 2);
	m_p_grid.GridCellFont(m_grid_motor_info, 3, 3, "MS Sans Serif", 12);
	m_p_grid.GridCellColor(m_grid_motor_info, 3, 3, TEXT_BC, RED_C);
	m_p_grid.GridCellText(m_grid_motor_info, 3, 3, "Power Off");

	m_p_grid.GridCellMerge(m_grid_motor_info, 3, 5, 2, 2);
	m_p_grid.GridCellFont(m_grid_motor_info, 3, 5, "MS Sans Serif", 12);
	m_p_grid.GridCellColor(m_grid_motor_info, 3, 5, TEXT_BC, RED_C);
	m_p_grid.GridCellText(m_grid_motor_info, 3, 5, "Power On");


	m_p_grid.GridCellMerge(m_grid_motor_info, 5, 1, 1, 2);
	m_p_grid.GridCellFont(m_grid_motor_info, 5, 1, "MS Sans Serif", 12);
	m_p_grid.GridCellColor(m_grid_motor_info, 5, 1, BLUE_D, WHITE_C);
	m_p_grid.GridCellText(m_grid_motor_info, 5, 1, "Motor Alarm");
	
	m_p_grid.GridCellMerge(m_grid_motor_info, 6, 1, 1, 2);
	m_p_grid.GridCellFont(m_grid_motor_info, 6, 1, "MS Sans Serif", 12);
	m_p_grid.GridCellColor(m_grid_motor_info, 6, 1, BLACK_L, WHITE_C);
	m_p_grid.GridCellText(m_grid_motor_info, 6, 1, "");

	m_p_grid.GridCellMerge(m_grid_motor_info, 5, 3, 2, 4);
	m_p_grid.GridCellFont(m_grid_motor_info, 5, 3, "MS Sans Serif", 12);
	m_p_grid.GridCellColor(m_grid_motor_info, 5, 3, TEXT_BC, RED_C);
	m_p_grid.GridCellText(m_grid_motor_info, 5, 3, "Alarm Reset");

	m_p_grid.GridCellMerge(m_grid_motor_info, 7, 1, 1, 2);
	m_p_grid.GridCellFont(m_grid_motor_info, 7, 1, "MS Sans Serif", 12);
	m_p_grid.GridCellColor(m_grid_motor_info, 7, 1, BLUE_D, WHITE_C);
	m_p_grid.GridCellText(m_grid_motor_info, 7, 1, "Motor Move");
	
	m_p_grid.GridCellFont(m_grid_motor_info, 8, 1, "MS Sans Serif", 12);
	m_p_grid.GridCellColor(m_grid_motor_info, 8, 1, RED_C, BLACK_C);
	m_p_grid.GridCellText(m_grid_motor_info, 8, 1, "Jog");

	m_p_grid.GridCellFont(m_grid_motor_info, 8, 2, "MS Sans Serif", 12);
	m_p_grid.GridCellColor(m_grid_motor_info, 8, 2, BLACK_L, YELLOW_C);
	m_p_grid.GridCellText(m_grid_motor_info, 8, 2, "Distance");

	m_p_grid.GridCellMerge(m_grid_motor_info, 7, 3, 1, 2);
	m_p_grid.GridCellFont(m_grid_motor_info, 7, 3, "MS Sans Serif", 12);
	m_p_grid.GridCellColor(m_grid_motor_info, 7, 3, BLUE_D, WHITE_C);
	m_p_grid.GridCellText(m_grid_motor_info, 7, 3, "Current Position");
	
	m_p_grid.GridCellMerge(m_grid_motor_info, 8, 3, 1, 2);
	m_p_grid.GridCellFont(m_grid_motor_info, 8, 3, "MS Sans Serif", 12);
	m_p_grid.GridCellColor(m_grid_motor_info, 8, 3, WHITE_C, BLACK_C);
	m_p_grid.GridCellText(m_grid_motor_info, 8, 3, "0");

	m_p_grid.GridCellMerge(m_grid_motor_info, 7, 5, 1, 2);
	m_p_grid.GridCellFont(m_grid_motor_info, 7, 5, "MS Sans Serif", 12);
	m_p_grid.GridCellColor(m_grid_motor_info, 7, 5, BLUE_D, WHITE_C);
	m_p_grid.GridCellText(m_grid_motor_info, 7, 5, "Move Distance (mm)");
	
	m_p_grid.GridCellMerge(m_grid_motor_info, 8, 5, 1, 2);
	m_p_grid.GridCellFont(m_grid_motor_info, 8, 5, "MS Sans Serif", 12);
	m_p_grid.GridCellColor(m_grid_motor_info, 8, 5, WHITE_C, BLACK_C);
	str_tmp.Format("%.2f", m_d_data);
	m_p_grid.GridCellText(m_grid_motor_info, 8, 5, str_tmp);

	if( m_grid_motor_info != NULL )
	{
		m_grid_motor_info = NULL;
		delete m_grid_motor_info;
	}
}

void CDialog_Motor_Axis_1::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
		case TM_STATUS_CHECK:	MotorStatusCheck();		break;
		case TM_POSITION_CHECK:	MotorPositionCheck();	break;
	}

	CDialog::OnTimer(nIDEvent);
}

void CDialog_Motor_Axis_1::OnDestroy() 
{
	Data_HistoryLog();
	Data_Apply();
	
// 	if (m_p_font != NULL)
// 	{
// 		delete m_p_font;
// 		m_p_font = NULL;
// 	}
	
	KillTimer(TM_STATUS_CHECK);
	KillTimer(TM_POSITION_CHECK);

	st_handler.cwnd_motorAxis = NULL;

	CDialog::OnDestroy();
}

void CDialog_Motor_Axis_1::OnBtnEmg() 
{
	//m_b_stop_req = TRUE;	// ESTOP ��û �÷���
	GETMOTOR( (ENUM_MOTOR)m_n_axis ).SetStopReq( true );
}

// **********************************************************************
// OnUserLButtonDown() : ��ư�� WM_LBUTTONDOWN �̺�Ʈ �ڵ鷯�Դϴ�.
// CButton Ŭ������ WM_LBUTTONDOWN �̺�Ʈ�� �������� �����Ƿ� CButtonST
// �̶�� Ŭ������ �����Ͽ� WM_LBUTTONDOWN �̺�Ʈ�� �����Ŀ� User-event��
// CSxMotionDlg Ŭ������ �����ϴ� ����� ���Ͽ����ϴ�.
// **********************************************************************
LONG CDialog_Motor_Axis_1::OnUserLButtonDown(WPARAM wParam, LPARAM lParam)
{
	CDialog_Message msg_dlg;
	CString strTmp;
	double dPos;
	int		nRet;
	
	nRet = Func.DoorOpenCheckSpot();
	
// 	if (nRet == CTLBD_RET_ERROR)
// 		return 0;

	// Velocity-Move(Jog) ����϶��� WM_LBUTTONDOWN �̺�Ʈ�� ó���Ѵ�. //
	// Rel/Abs Position Mode������ WM_LBUTTONUP �̺�Ʈ���� �̼� ����� //
	// ó���Ѵ�.                                                       //
	CButtonST *pButton = (CButtonST *)lParam;

	nRet = pButton->GetTag();

	if (pButton->GetTag() == IDC_BTN_LEFT)
	{ // "Jog (-)" ��ư�� ���� ���...
		if (m_n_move_mode == 0)
		{
			nRet = CTL_Lib.Motor_SafetyCheck(3, m_n_axis, 0);
			
			if (nRet == CTLBD_RET_ERROR)
			{
				return 0;
			}
			
			OnButtonControl(FALSE);
			dPos =  g_comiMgr.Get_MotCurrentPos(m_n_axis);

			strTmp.Format("[Motor] (%s)Axis (%.3f) + Jog Move", m_str_axis_name, dPos);
			Func.On_LogFile_Add(99, strTmp);
			Func.On_LogFile_Add(0, strTmp);
			EMOTRET motRet = GETMOTOR( (ENUM_MOTOR)m_n_axis ).JogMoveStart( MINUS );
			
			if( motRet == MOTRET_ERROR )		cmmErrShowLast(GetSafeHwnd());
			else								st_handler.mn_menu_lock = FALSE;
		}
		else
		{
			// ���� �̵����� ���� üũ �߰� �ؾߵ�......
			OnButtonControl(FALSE);							// ��ư ��Ȱ��ȭ
			
			double dMotGotoPos		= g_comiMgr.Get_MotCurrentPos(m_n_axis) - m_d_data;
			double dMotGotoSpeed	= (COMI.md_spd_jog[m_n_axis] / COMI.md_spd_vel[m_n_axis][0]) * 100;

			strTmp.Format("[Motor] (%s)_Axis (%.3f) - Data Move", m_str_axis_name, m_d_data);
			Func.On_LogFile_Add(99, strTmp);
			Func.On_LogFile_Add(0, strTmp);

			GETMOTOR( (ENUM_MOTOR)m_n_axis ).MotorStepClear();
			GETMOTOR( (ENUM_MOTOR)m_n_axis ).MotorMoveStart( dMotGotoPos, st_basic.nManualSpeed, MMMODE_DISTANCE );
		}
	}
	else if (pButton->GetTag() == IDC_BTN_RIGHT)
	{ 
		if (m_n_move_mode == 0)
		{
			nRet = CTL_Lib.Motor_SafetyCheck(3, m_n_axis, 0);
			
			if (nRet == CTLBD_RET_ERROR)
				return 0;
			
			OnButtonControl(FALSE);						// ��ư ��Ȱ��ȭ
			
			dPos =  g_comiMgr.Get_MotCurrentPos(m_n_axis);

			strTmp.Format("[Motor] (%s)Axis (%.3f) + Jog Move", m_str_axis_name, dPos);
			Func.On_LogFile_Add(99, strTmp);
			Func.On_LogFile_Add(0, strTmp);
			
			EMOTRET motRet = GETMOTOR( (ENUM_MOTOR)m_n_axis ).JogMoveStart( PLUS );
			
			if( motRet == MOTRET_ERROR )		cmmErrShowLast(GetSafeHwnd());
			else								st_handler.mn_menu_lock = FALSE;
		}
		else
		{
			// ���� �̵����� ���� üũ �߰� �ؾߵ�......				
			OnButtonControl(FALSE);						// ��ư ��Ȱ��ȭ
			
			double dMotGotoPos		= g_comiMgr.Get_MotCurrentPos(m_n_axis) + m_d_data;
			double dMotGotoSpeed	= (COMI.md_spd_jog[m_n_axis] / COMI.md_spd_vel[m_n_axis][0]) * 100;

			strTmp.Format("[Motor] (%s)_Axis (%.3f) + Data Move", m_str_axis_name, m_d_data);
			Func.On_LogFile_Add(99, strTmp);
			Func.On_LogFile_Add(0, strTmp);

			GETMOTOR( (ENUM_MOTOR)m_n_axis ).MotorStepClear();
			GETMOTOR( (ENUM_MOTOR)m_n_axis ).MotorMoveStart( dMotGotoPos, st_basic.nManualSpeed, MMMODE_DISTANCE );
		}
	}

	return 0;
}

LONG CDialog_Motor_Axis_1::OnUserLButtonUp(WPARAM wParam, LPARAM lParam)
{	
	CDialog_Message msg_dlg;
	CString strTmp;
	double dPos;
	int		nRet;


	// Velocity-Move(Jog) ����϶��� WM_LBUTTONDOWN �̺�Ʈ�� ó���Ѵ�. //
	// Rel/Abs Position Mode������ WM_LBUTTONUP �̺�Ʈ���� �̼� ����� //
	// ó���Ѵ�.                                                       //
	CButtonST *pButton = (CButtonST *)lParam;

	nRet = pButton->GetTag();

	if (pButton->GetTag() == IDC_BTN_LEFT)
	{ // "Jog (-)" ��ư�� ���� ���...
		if (m_n_move_mode == 0)
		{
			dPos =  g_comiMgr.Get_MotCurrentPos(m_n_axis);
			strTmp.Format("[Motor] (%s)Axis (%.3f) - Jog Stop", m_str_axis_name, dPos);
			Func.On_LogFile_Add(99, strTmp);
			Func.On_LogFile_Add(0, strTmp);
			
			cmmSxStop(m_n_axis, FALSE, TRUE);  // ���� �̵� ���� �Լ� 
			
			OnButtonControl(TRUE);	
		}
	}
	else if (pButton->GetTag() == IDC_BTN_RIGHT)
	{ 
		if (m_n_move_mode == 0)
		{
			dPos =  g_comiMgr.Get_MotCurrentPos(m_n_axis);
			strTmp.Format("[Motor] (%s)Axis (%.3f) + Jog Stop", m_str_axis_name, dPos);
			Func.On_LogFile_Add(99, strTmp);
			Func.On_LogFile_Add(0, strTmp);
			
			cmmSxStop(m_n_axis, FALSE, TRUE);  // ���� �̵� ���� �Լ� 
			
			OnButtonControl(TRUE);	
		}
	}
	return 0;
}

void CDialog_Motor_Axis_1::OnBtnHome() 
{
	CString strTmp;

	OnButtonControl(FALSE);  // ��� ��Ʈ�� ȭ�� ��� ���� �Լ�
	
	// ==============================================================================
	// �޴� ��� �Ұ����ϵ��� �÷��� �����Ѵ�                                    
	// -> ���� ���� ���� �߿� �ٸ� �޴� ���� ���۽�Ű�� �������� �� �ֱ� �����̴�
	// -> st_handler.i_menu_lock   : �޴� ��� ���� ���� �÷���                  
	//  : ���� �������� �޴� ��ȯ �κп��� �� �÷��� �˻��ϰ� �ȴ�               
	// ==============================================================================
	if (st_handler.mn_menu_lock != TRUE)
	{
		st_handler.mn_menu_lock = TRUE;
	}
	// ==============================================================================
	
	strTmp.Format("[Motor] (%s)_Axis Home Move", m_str_axis_name);
	Func.On_LogFile_Add(99, strTmp);
	Func.On_LogFile_Add(0, strTmp);
	
	GETMOTOR( (ENUM_MOTOR)m_n_axis ).MotorStepClear();
	GETMOTOR( (ENUM_MOTOR)m_n_axis ).MotorHomeStart();

	// ���� ���� ���� Ÿ�̸�
}

void CDialog_Motor_Axis_1::OnBtnApply() 
{
	Data_HistoryLog();
	Data_Apply();
}

LRESULT CDialog_Motor_Axis_1::OnMotorCompletion(WPARAM wParam,LPARAM lParam)
{
	if (st_handler.mn_menu_lock != FALSE)
	{
		st_handler.mn_menu_lock = FALSE;
	}
	// ==============================================================================

	if( wParam != MMMODE_MANUAL )
		return 0;
	
	OnButtonControl(TRUE);  // ��� ��Ʈ�� ȭ�� ��� ���� �Լ� //
	MotorCompletion(m_n_cmd_row, m_n_cmd_col);

	return 0;
}

void CDialog_Motor_Axis_1::SetDataForSelected( int iSelected )
{
	Data_Init( iSelected );

	Init_Grid_Pos();
	Init_Grid_Info();
	Init_Label();
	//Init_Group();
	Init_Digit();
	Init_Radio();
	Init_Button();
}

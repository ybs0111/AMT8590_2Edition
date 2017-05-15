// Dialog_Title.cpp : implementation file
//

#include "stdafx.h"
#include "Handler.h"
#include "Dialog_Title.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_Title dialog


CDialog_Title::CDialog_Title()
{
	//{{AFX_DATA_INIT(CDialog_Title)
	//}}AFX_DATA_INIT
	n_smemaonoff = 0;
}

void CDialog_Title::DoDataExchange(CDataExchange* pDX)
{
	CInitDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Title)
	DDX_Control(pDX, IDC_TITLE_XGEM, m_title_xgem);
	DDX_Control(pDX, IDC_TITLE_CONVEYOR_INOFF, m_title_conveyor_inline_mode);
	DDX_Control(pDX, IDC_TITLE_ONLINE_MODE, m_title_online_mode);
	DDX_Control(pDX, IDC_TITLE_REAR_KEY_MODE, m_title_rear_key);
	DDX_Control(pDX, IDC_TITLE_FRONT_KEY_MODE, m_title_front_key);
	DDX_Control(pDX, IDC_TITLE_LEVEL_MODE, m_title_level_mode);
	DDX_Control(pDX, IDC_TITLE_DEVICE_MODE, m_title_device_mode);
	DDX_Control(pDX, IDC_MSG_STATUS_INFO, m_msg_status_info);
	DDX_Control(pDX, IDC_MSG_FORM_NAME, m_msg_form_name);
	DDX_Control(pDX, IDC_GIF_TITLE_LOGO, m_gif_title_logo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_Title, CInitDialogBar)
	//{{AFX_MSG_MAP(CDialog_Title)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_STATUS_CHANGE,OnStatusDataUpdate)  // Ÿ��Ʋ �� ȭ������ ���۵� �޽��� ��½�Ű�� ���� ����� ���� �޽��� �߰� 
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Title message handlers

BOOL CDialog_Title::OnInitDialogBar() 
{
	CInitDialogBar::OnInitDialogBar();
	
	// **************************************************************************
	// ��Ʈ�ѿ� ������ ��Ʈ �����Ѵ�
	// **************************************************************************
	mp_title_font = NULL;
	mp_title_font = new CFont;
	mp_title_font->CreateFont(15,0,0,0,900,0,0,0,0,0,0,ANTIALIASED_QUALITY,0,"MS Sans Serif");
	// **************************************************************************
	
	OnTitle_Lable_Set();
	OnTitle_Picture_Set(); // Ÿ��Ʋ �� ȭ�鿡 ���� GIF �׸� ���� �ε� �Լ�
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_Title::OnDestroy() 
{
	// **************************************************************************
	// ������ ��Ʈ ���� �����Ѵ�
	// **************************************************************************
	delete mp_title_font;
	mp_title_font = NULL;
	// **************************************************************************

	CInitDialogBar::OnDestroy();
}

LRESULT CDialog_Title::OnStatusDataUpdate(WPARAM wParam,LPARAM lParam)
{
	int mn_change;			// PostMessage�� ���� ���ŵ� �޽��� ID ���� ���� 
	
	mn_change = lParam;						// ��ɾ� ID ���� ���� 
	
	if(wParam == FORM_NAME)					// ȭ�� �� ��ȯ�� ��� 
	{
		OnTitle_Form_Name_Change(mn_change);// ���� ��µ� �� ȭ�� �̸� ���� ��� �Լ�
	}
	else if(wParam == MACHINE_STATUS)		// ��� ���� ���� ������ ��� 
	{
		OnTitle_Status_Change(mn_change);
	}
	else if(wParam == DEVICE_MODE)			// Device Mode
	{
		OnTitle_Device_mode_Display(mn_change);
	}
	else if(wParam == LEVEL_MODE)
	{
		OnTitle_Level_mode_Display();
	}
	else if(wParam == FRONT_KEY_MODE)
	{
		OnTitle_Front_Key_Display(mn_change);
	}
	else if(wParam == REAR_KEY_MODE)
	{
		OnTitle_Rear_Key_Display(mn_change);
	}
	else if(wParam == CONV_MODE)
	{
		OnTitle_Conv_Inline_Display(mn_change);
	}
	else if(wParam == ONLINE_MODE)
	{
		OnTitle_Online_Mode_Display();
	}
	else if(wParam == SMEMA_ONOFF)
	{
//		OnTitle_EmptyTray_Mode_Display();
	}
	else if(wParam == XGEM_MODE)
	{
		OnTitle_Xgem_mode_Display(mn_change);
	}
	
	return 0;
}

void CDialog_Title::OnTitle_Picture_Set()
{
	if (m_gif_title_logo.Load(MAKEINTRESOURCE(IDR_GIF_N_LOGO),_T("GIF")))
		m_gif_title_logo.Draw();
}

void CDialog_Title::OnTitle_Lable_Set()
{
	m_msg_form_name.SetAlignment(CNewLabel::HORZ_LEFT | CNewLabel::VERT_CENTER);
	m_msg_form_name.SetTextColor(RGB(0, 0, 0));
	m_msg_form_name.SetBkColor(RGB(181, 182, 140));
	m_msg_form_name.SetFontBold(TRUE);
	m_msg_form_name.SetFontName("MS Sans Serif");
	m_msg_form_name.SetFontSize(12);
	
	m_msg_status_info.SetFont(mp_title_font);
	m_msg_status_info.SetCenterText();
	m_msg_status_info.SetColor(RGB(255,255,255));
	m_msg_status_info.SetGradientColor(RGB(0,255,0));
	m_msg_status_info.SetTextColor(RGB(255,255,255));

	m_title_device_mode.SetFont(mp_title_font);
	m_title_device_mode.SetCenterText();
	m_title_device_mode.SetColor(RGB(0,0,255));
	m_title_device_mode.SetGradientColor(RGB(0,0,0));
	m_title_device_mode.SetTextColor(RGB(255,255,255));
	
	m_title_level_mode.SetFont(mp_title_font);
	m_title_level_mode.SetCenterText();
	m_title_level_mode.SetColor(RGB(0,0,255));
	m_title_level_mode.SetGradientColor(RGB(0,0,0));
	m_title_level_mode.SetTextColor(RGB(255,255,255));

// 	m_title_bcr_mode.SetFont(mp_title_font);
// 	m_title_bcr_mode.SetCenterText();
// 	m_title_bcr_mode.SetColor(RGB(0,0,255));
// 	m_title_bcr_mode.SetGradientColor(RGB(0,0,0));
// 	m_title_bcr_mode.SetTextColor(RGB(255,255,255));

	m_title_front_key.SetFont(mp_title_font);
	m_title_front_key.SetCenterText();
	m_title_front_key.SetColor(RGB(0,0,255));
	m_title_front_key.SetGradientColor(RGB(0,0,0));
	m_title_front_key.SetTextColor(RGB(255,255,255));

	m_title_rear_key.SetFont(mp_title_font);
	m_title_rear_key.SetCenterText();
	m_title_rear_key.SetColor(RGB(0,0,255));
	m_title_rear_key.SetGradientColor(RGB(0,0,0));
	m_title_rear_key.SetTextColor(RGB(255,255,255));
	
	m_title_conveyor_inline_mode.SetFont(mp_title_font);
	m_title_conveyor_inline_mode.SetCenterText();
	m_title_conveyor_inline_mode.SetColor(RGB(0,0,255));
	m_title_conveyor_inline_mode.SetGradientColor(RGB(0,0,0));
	m_title_conveyor_inline_mode.SetTextColor(RGB(255,255,255));

	m_title_online_mode.SetFont(mp_title_font);
	m_title_online_mode.SetCenterText();
	m_title_online_mode.SetColor(RGB(0,0,255));
	m_title_online_mode.SetGradientColor(RGB(0,0,0));
	m_title_online_mode.SetTextColor(RGB(255,255,255));	

	m_title_xgem.SetFont(mp_title_font);
	m_title_xgem.SetCenterText();
	m_title_xgem.SetColor(RGB(0,0,255));
	m_title_xgem.SetGradientColor(RGB(0,0,0));
	m_title_xgem.SetTextColor(RGB(255,255,255));
// 
// 	m_title_emptytray_mode.SetFont(mp_title_font);
// 	m_title_emptytray_mode.SetCenterText();
// 	m_title_emptytray_mode.SetColor(RGB(0,0,255));
// //	m_title_emptytray_mode.SetGradientColor(RGB(0,0,0));
// 	m_title_emptytray_mode.SetTextColor(RGB(255,255,255));	
}

void CDialog_Title::OnTitle_Form_Name_Change(int nViewID)
{
	CString mstr_form_name;  // ���� ������ ȭ�� ���� ���� ���� 
	
	switch(nViewID)
	{
	case IDW_SCREEN_MAIN:
		mstr_form_name = _T("\n");
		mstr_form_name += _T(" Screen: Main");
		break;
	case IDW_SCREEN_LOCK:
		mstr_form_name = _T("\n");
		mstr_form_name += _T(" Screen: System Lock");
		break;
	case IDW_SCREEN_INIT:
		mstr_form_name = _T("\n");
		mstr_form_name += _T(" Screen: Initial");
		break;
	case IDW_SCREEN_BASIC :
		mstr_form_name = _T("\n");
		mstr_form_name += _T(" Screen: Basic");
		break;
	case IDW_SCREEN_SET_MAINTENANCE :
		mstr_form_name = _T(" Menu: Setting");
		mstr_form_name += _T("\n");
		mstr_form_name += _T(" Screen: Maintenance");
		break;
	case IDW_SCREEN_WAIT_TIME :
		mstr_form_name += _T("\n");
		mstr_form_name += _T(" Screen: Wait Time");
		break;
	case IDW_SCREEN_MOTOR_TEACH:
		mstr_form_name = _T(" Menu: Motor");
		mstr_form_name += _T("\n");
		mstr_form_name += _T(" Screen: Teach");
		break;
	case IDW_SCREEN_MOTOR_SPEED :
		mstr_form_name = _T(" Menu: Motor");
		mstr_form_name += _T("\n");
		mstr_form_name += _T(" Screen: Speed");
		break;

// 	case IDW_SCREEN_MOTOR_WITH_IO:
// 		mstr_form_name = _T(" Menu: Motor");
// 		mstr_form_name += _T("\n");
// 		mstr_form_name += _T(" Screen: With IO");
// 		break;

	case IDW_SCREEN_LIST_OPERATION :
		mstr_form_name = _T(" Menu: List");
		mstr_form_name += _T("\n");
		mstr_form_name += _T(" Screen: Operation");
		break;
	case IDW_SCREEN_LIST_DATA_VIEW:
		mstr_form_name = _T(" Menu: List");
		mstr_form_name += _T("\n");
		mstr_form_name += _T(" Screen: Data View");
		break;
	case IDW_SCREEN_IO :
		mstr_form_name = _T("\n");
		mstr_form_name += _T(" Screen: I/O");
		break;
	case IDW_SCREEN_ADMINISTRATOR :
		mstr_form_name = _T("\n");
		mstr_form_name += _T(" Screen: ADMINISTRATOR");
		break;
	case IDW_SCREEN_FILE_EDITOR:
		mstr_form_name = _T("\n");
		mstr_form_name += _T(" Screen: File Editor");
		break;
	default:
		mstr_form_name = _T(" ERROR: SCREEN VIEW ID");
		break;
	}
	
	m_msg_form_name.SetText(_T(mstr_form_name));
}

void CDialog_Title::OnTitle_Status_Change(int n_status)
{
	switch(n_status)
	{
	case dSTOP :		// STOP ����
		m_msg_status_info.SetWindowText(_T("STOP"));
		m_msg_status_info.SetTextColor(RGB(255,0,0));
		break;
	case dRUN :			// RUN ����
		m_msg_status_info.SetWindowText(_T("RUN"));
		m_msg_status_info.SetTextColor(RGB(0, 0, 255));
		break;
	case dJAM :			// ALARM ����
		m_msg_status_info.SetWindowText(_T("ALARM"));
		m_msg_status_info.SetTextColor(RGB(255,0,0));
		break;
	case dWARNING :		// ALARM ����
		m_msg_status_info.SetWindowText(_T("ALARM"));
		m_msg_status_info.SetTextColor(RGB(255,0,0));
		break;
	case dMAINT :		// MAINT ����
		m_msg_status_info.SetWindowText(_T("MAINT"));
		m_msg_status_info.SetTextColor(RGB(0,0,200));
		break;
	case dINIT :		// INIT ����
		m_msg_status_info.SetWindowText(_T("INIT"));
		m_msg_status_info.SetTextColor(RGB(50,100,150));
		break;
	case dLOTEND :		// LOT END ����
		m_msg_status_info.SetWindowText(_T("LOTEND"));
		m_msg_status_info.SetTextColor(RGB(50,100,150));
		break;
	case dLOCK :		// LOCK ����
		m_msg_status_info.SetWindowText(_T("LOCK"));
		m_msg_status_info.SetTextColor(RGB(50,100,150));
		break;
// 	case dSELFCHECK :	// SELFCHECK ����
// 		m_msg_status_info.SetWindowText(_T("SELFCHECK"));
// 		m_msg_status_info.SetTextColor(RGB(50,100,150));
// 		break;
	default :
		break;
	}
	
	m_msg_status_info.SetColor(RGB(255,255,255));
	m_msg_status_info.SetGradientColor(RGB(0,255,0));
}

void CDialog_Title::OnTitle_Device_mode_Display(int n_device)
{
	CString str_device;   // �ӽ� ���� ����

	switch(st_basic.n_mode_device)
	{
	case 0:
		m_title_device_mode.SetColor(RGB(255,0,0));
		str_device = _T("WITHOUT DEVICE");
		break;
	case 1:
		m_title_device_mode.SetColor(RGB(0,0,255));
		str_device = _T("WITH DEVICE");
		break;
	default:
		m_title_device_mode.SetColor(RGB(255,0,0));
		str_device = _T("ERROR");
		break;
	}

	m_title_device_mode.SetWindowText(_T(str_device));
}

void CDialog_Title::OnTitle_Level_mode_Display()
{
	CString str_level;   // �ӽ� ���� ����
	
	if (st_handler.mn_level_teach == TRUE)
	{
		m_title_level_mode.SetColor(RGB(255,0,0));
		str_level = _T("LEVEL 2 (Teaching Mode)");
	}
	else if (st_handler.mn_level_maint == TRUE)
	{
		m_title_level_mode.SetColor(RGB(255,0,0));
		str_level = _T("LEVEL 1 (Maint Mode)");
	}
	else
	{
		m_title_level_mode.SetColor(RGB(0,0,255));
		str_level = _T("LEVEL 0 (Operation Mode)");
	}
	
	m_title_level_mode.SetWindowText(_T(str_level));
}

void CDialog_Title::OnTitle_Front_Key_Display(int n_key)
{
	CString str_key;   // �ӽ� ���� ����
	
	switch(n_key)
	{
	case 0:
		m_title_front_key.SetColor(RGB(255,0,0));
		str_key = _T("Front : Manual Mode");
		break;
	case 1:
		m_title_front_key.SetColor(RGB(0,0,255));
		str_key = _T("Front : Auto Mode");
		break;
	default:
		m_title_front_key.SetColor(RGB(255,0,0));
		str_key = _T("Front : Error");
		break;
	}
	
	m_title_front_key.SetWindowText(_T(str_key));
}

void CDialog_Title::OnTitle_Rear_Key_Display(int n_key)
{
	CString str_key;   // �ӽ� ���� ����
	
	switch(n_key)
	{
	case 0:
		m_title_rear_key.SetColor(RGB(255,0,0));
		str_key = _T("Rear : Manual Mode");
		break;
	case 1:
		m_title_rear_key.SetColor(RGB(0,0,255));
		str_key = _T("Rear : Auto Mode");
			break;
	default:
		m_title_rear_key.SetColor(RGB(255,0,0));
		str_key = _T("Rear : Error");
		break;
	}
	
	m_title_rear_key.SetWindowText(_T(str_key));
}

void CDialog_Title::OnTitle_Conv_Inline_Display(int n_key)
{
	CString str_key;   // �ӽ� ���� ����
	
	switch(n_key)
	{
	case 0:
		m_title_conveyor_inline_mode.SetColor(RGB(255,0,0));
		str_key = _T("CONV:Manual(Reject)");
		break;
	case 1:
		m_title_conveyor_inline_mode.SetColor(RGB(255,0,0));
		str_key = _T("CONV:Manual(Conv)");
		break;
	case 2:
		m_title_conveyor_inline_mode.SetColor(RGB(0,0,255));
		str_key = _T("CONV:Inline Mode");
		break;
	default:
		m_title_conveyor_inline_mode.SetColor(RGB(255,0,0));
		str_key = _T("CONV:Error");
		break;
	}
	
	m_title_conveyor_inline_mode.SetWindowText(_T(str_key));
}

void CDialog_Title::OnTitle_Online_Mode_Display()
{
	CString str_online;   // �ӽ� ���� ����
	
	switch(st_basic.mn_mode_run)
	{
	case 0:
		m_title_online_mode.SetColor(RGB(255,0,0));
		str_online = _T("OFFLINE");
		break;
	case 1:
		m_title_online_mode.SetColor(RGB(0,0,255));
		str_online = _T("ONLINE");
		break;
	default:
		m_title_online_mode.SetColor(RGB(255,0,0));
		str_online = _T("ERROR");
		break;
	}
	
	m_title_online_mode.SetWindowText(_T(str_online));
}

void CDialog_Title::OnTitle_EmptyTray_Mode_Display()
{
	CString str_empty;   // �ӽ� ���� ����
	
	switch(st_handler.mn_smema_rear_run)
	{
	case 0:
		n_smemaonoff = 1;
		m_title_emptytray_mode.SetColor(RGB(255,0,0));
		str_empty = "NEXT Smema Off";//.Format("EMPTY OUT : %d IN: %d",st_handler.mn_emptyout_cnt,st_handler.mn_emptyin_cnt);
		SetTimer( TMR_SMEMA_OFF, 1000, NULL);
		break;
	case 1:
		KillTimer( TMR_SMEMA_OFF );
		m_title_emptytray_mode.SetColor(RGB(0,0,255));
		str_empty = "NEXT Machine On";//.Format("EMPTY OUT : %d IN: %d",st_handler.mn_emptyout_cnt,st_handler.mn_emptyin_cnt);
		break;
	default:
		m_title_emptytray_mode.SetColor(RGB(255,0,0));
		str_empty = _T("ERROR");
		break;
	}
	
	m_title_emptytray_mode.SetWindowText(_T(str_empty));
}

void CDialog_Title::OnTimer(UINT nIDEvent) 
{
// 	if( nIDEvent == TMR_SMEMA_OFF )
// 	{
// 		if( n_smemaonoff == 1)
// 		{
// 			n_smemaonoff = 0;
// 			m_title_emptytray_mode.SetColor(RGB(255, 0, 0));
// 		}
// 		else
// 		{
// 			n_smemaonoff = 1;
// 			m_title_emptytray_mode.SetColor(RGB( 0, 0,255));
// 		}
// 		Invalidate(false);
// 	}	
	CInitDialogBar::OnTimer(nIDEvent);
}

void CDialog_Title::OnBuildBCRMode()
{
	CString SBCRMode;
	
	if (m_nBCR_Mode == st_basic.n_bcr_Mode)
	{
		return;
	}
	m_nBCR_Mode = st_basic.n_bcr_Mode;
	
	switch(st_basic.n_bcr_Mode)
	{
	case 0:
		SBCRMode = _T("Step by Step");
// 		m_title_bcr_mode.SetColor(RGB(255,0,0));
// 		m_title_bcr_mode.SetWindowText(_T(SBCRMode));
		break;
		
	case 1:
		SBCRMode = _T("Continuity");
// 		m_title_bcr_mode.SetColor(RGB(0,0, 255));
// 		m_title_bcr_mode.SetWindowText(_T(SBCRMode));
		break;
	}
}


void CDialog_Title::OnTitle_Xgem_mode_Display(int n_gem)
{
	CString str_device;   // �ӽ� ���� ����
	
	switch(n_gem)
	{
	case 0:
		m_title_xgem.SetColor(RGB(255,0,0));
		str_device = _T("Xgem-Off");
		break;
	case 1:
		m_title_xgem.SetColor(RGB(0,0,255));
		str_device = _T("Xgem-On");
		break;
	default:
		m_title_xgem.SetColor(RGB(255,0,0));
		str_device = _T("ERROR");
		break;
	}
	
	m_title_xgem.SetWindowText(_T(str_device));
}

